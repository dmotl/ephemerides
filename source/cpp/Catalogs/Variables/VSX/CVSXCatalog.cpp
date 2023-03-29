/*!
*  \file      CVSXCatalogObject.cpp
*  \author    David Motl
*  \date      2022-12-19
*
*  \copyright
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted
*  provided that the following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions
*      and the following disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list
*      of conditions and the following disclaimer in the documentation and/or other materials provided
*      with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of its contributors may be used
*      to endorse or promote products derived from this software without specific prior written
*      permission.
*/
#include "CVSXCatalog.h"

#include "CCatalogObject.h"

#define _USE_MATH_DEFINES
#define LINE_MAX 160

#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <iostream>

static const char magic_str[4] = "VSX";

/*
1547583 ZTF J000000.14+721413.7        0   0.00061 +72.23716 EW                               18.804 r      (  0.438 r      2458388.7556       0.2991500

*/

static int getInt(const char* buf, int start, int length, bool* ok = nullptr)
{
	assert(length < 16);

	char tmp[16];
	char* tmp_ptr = tmp;
	const char* buf_ptr = buf + start;
	for (int j = 0; j < length && *buf_ptr != '\0'; ++j)
		*tmp_ptr++ = *buf_ptr++;
	*tmp_ptr = '\0';
	int retval = strtol(tmp, &tmp_ptr, 10);
	if (ok)
		*ok = tmp_ptr != tmp;
	return retval;
}

static double getDouble(const char* buf, int start, int length, bool* ok = nullptr)
{
	assert(length < 32);

	char tmp[32];
	char* tmp_ptr = tmp;
	const char* buf_ptr = buf + start;
	for (int j = 0; j < length && *buf_ptr != '\0'; ++j)
		*tmp_ptr++ = *buf_ptr++;
	*tmp_ptr = '\0';
	double retval = strtod(tmp, &tmp_ptr);
	if (ok)
		*ok = tmp_ptr != tmp;
	return retval;
}

static std::string getStdString(const char* buf, int start, int length)
{
	int j = 0;
	const char* buf_ptr = buf + start;
	while (j < length && *buf_ptr != '\0')
		++buf_ptr, ++j;
	return std::string(buf + start, j);
}

bool CVSXCatalog::open(tCancelledFn cbCancelled, tSetProgressMaxFn cbSetProgressRange, tSetProgressValueFn cbSetProgressValue)
{
	reset();

	QFile file(m_filePath);
	if (file.open(QIODevice::ReadOnly)) {
		size_t size = file.size();
		m_data = QByteArray(size, Qt::Uninitialized);
		if (file.read(m_data.data(), size) == size) {
			cbSetProgressRange(size);
			int i = 0;
			size_t offset = 0;
			const char* buffer = m_data.constData();
			while (*buffer != '\0') {
				const char* buf = buffer;
				size_t len = strcspn(buffer, "\r\n");
				size_t line_length = len + strspn(buffer + len, "\r\n");
				buffer += line_length;
				offset += line_length;
				if (len >= 144 && buf[44] == '.' && buf[54] == '.' && buf[131] == '.' && buf[144] == '.') {
					int OID = getInt(buf, 0, 8);
					int varFlag = buf[39] - '0';
					bool ra_ok = false, de_ok = false, ep_ok = false, per_ok = false;
					double RAdeg = getDouble(buf, 41, 9, &ra_ok);
					double DEdeg = getDouble(buf, 51, 9, &de_ok);
					double epoch = getDouble(buf, 124, 12, &ep_ok);
					double period = getDouble(buf, 139, 12, &per_ok);
					if (OID > 0 && varFlag == 0 && ra_ok && de_ok && ep_ok && per_ok) {
						tObject object;
						object.offset = offset;
						object.length = len;
						object.OID = OID;
						object.varName = QString::fromStdString(getStdString(buf, 8, 30));
						object.varType = QString::fromStdString(getStdString(buf, 61, 30));
						object.coords = CEquCoordinates(DEG_TO_RAD(RAdeg), DEG_TO_RAD(DEdeg));
						object.epoch = epoch;
						object.period = period;
						size_t index = m_objects.size();
						m_objects.push_back(object);
						m_objects[index].ptr = new CVSXCatalogObject(this, &m_objects.at(index));
					}
				}
				else {
					//std::cerr << "Invalid line: " << buf << std::endl;
				}
				if ((++i % 10000) == 0) {
					if (cbCancelled()) {
						reset();
						break;
					}
					cbSetProgressValue(offset);
				}
			}
		}
	}

	return !m_objects.empty();
}

void CVSXCatalog::reset()
{
	m_objects.clear();
	m_index = -1;
}

void CVSXCatalog::pickle(QIODevice* os)
{
	constexpr auto item_size = offsetof(tObject, ptr);
	constexpr int hdr_size = 8;

	int hdr[hdr_size];
	memset(hdr, 0, hdr_size * sizeof(int));
	memcpy(hdr, magic_str, sizeof(int));
	hdr[1] = (int)m_objects.size();
	hdr[2] = (int)item_size;
	*(long long*)(hdr + 4) = m_data.size();
	os->write(reinterpret_cast<const char*>(hdr), hdr_size * sizeof(int));

	if (!m_data.isEmpty())
		os->write(m_data);

	auto begin = m_objects.begin(), end = m_objects.end();
	while (begin != end) {
		const tObject& obj = *begin;
		os->write(reinterpret_cast<const char*>(&obj), item_size);
		++begin;
	}
}

void CVSXCatalog::unpickle(QIODevice* is)
{
	constexpr auto item_size = offsetof(tObject, ptr);
	constexpr int hdr_size = 8;

	reset();

	int hdr[hdr_size];
	if (is->read(reinterpret_cast<char*>(hdr), hdr_size * sizeof(int)) != hdr_size * sizeof(int) ||
		memcmp(hdr, magic_str, sizeof(int)) != 0 || hdr[2] != (int)item_size || hdr[1] < 0) {
		throw std::runtime_error("VSX: Error in cache file header");
	}

	size_t dataSize = *(long long*)(hdr + 4);
	m_data = QByteArray(dataSize, Qt::Uninitialized);
	if (is->read(m_data.data(), dataSize) != dataSize) {
		m_data = QByteArray();
		throw std::runtime_error("VSX: Error in cache file header");
	}

	int count = hdr[1];
	for (int i = 0; i < count; i++) {
		tObject object;
		if (is->read(reinterpret_cast<char*>(&object), item_size) != item_size)
			throw std::runtime_error("BSC1991: Error reading cache data");
		size_t index = m_objects.size();
		m_objects.push_back(object);
		m_objects[index].ptr = new CVSXCatalogObject(this, &m_objects[index]);
	}
}

const CCatalogObject* CVSXCatalog::first()
{
	m_index = 0;
	return find();
}

const CCatalogObject* CVSXCatalog::next()
{
	assert(m_index >= 0 && m_index < m_objects.size());
	++m_index;
	return find();
}

const CCatalogObject* CVSXCatalog::find() const
{
	if (m_index != m_objects.size())
		return m_objects[m_index].ptr;
	return nullptr;
}
