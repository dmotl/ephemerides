/*!
*  \file      CBSC1991Catalog.cpp
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
#include "CBSC1991Catalog.h"

#include "CCatalogObject.h"

#define _USE_MATH_DEFINES
#define LINE_MAX 200

#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <iostream>

static const char magic_str[4] = "BSC";

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

#if 0

static std::string getStdString(const char* buf, int start, int length)
{
	int j = 0;
	const char* buf_ptr = buf + start;
	while (j < length && *buf_ptr != '\0')
		++buf_ptr, ++j;
	return std::string(buf + start, j);
}

#endif

bool CBSC1991Catalog::open(tCancelledFn cbCancelled, tSetProgressMaxFn cbSetProgressRange, tSetProgressValueFn cbSetProgressValue)
{
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
				if (len >= 108 && (buf[83] == '+' || buf[83] == '-')) {
					bool bs_ok = false, hd_ok = false;
					int bs_num = getInt(buf, 0, 4, &bs_ok);
					int hd_num = getInt(buf, 25, 6, &hd_ok);
					bool ra_h_ok = false, ra_m_ok = false, ra_s_ok = false;
					int ra_h = getInt(buf, 75, 2, &ra_h_ok);
					int ra_m = getInt(buf, 77, 2, &ra_m_ok);
					double ra_s = getDouble(buf, 79, 6, &ra_s_ok);
					int de_sign = (buf[83] == '-' ? -1 : +1);
					bool dec_d_ok = false, dec_m_ok = false, dec_s_ok = false;
					int dec_d = getInt(buf, 84, 2, &dec_d_ok);
					int dec_m = getInt(buf, 86, 2, &dec_m_ok);
					int dec_s = getInt(buf, 88, 2, &dec_s_ok);
					bool vmag_ok = false;
					double v_mag = getDouble(buf, 102, 7, &vmag_ok);
					if (ra_h_ok && ra_m_ok && ra_s_ok && dec_d_ok && dec_m_ok && dec_s_ok && vmag_ok) {
						tObject object;
						object.offset = offset;
						object.length = len;
						object.bs_num = bs_num;
						object.hd_num = hd_num;
						double RAdeg = (double)ra_h + (double)ra_m / 60.0 + (double)ra_s / 3600.0;
						double DEdeg = de_sign * ((double)dec_d + (double)dec_m / 60.0 + (double)dec_s / 3600.0);
						object.coords = CEquCoordinates(DEG_TO_RAD(RAdeg), DEG_TO_RAD(DEdeg));
						object.mag = v_mag;
						size_t index = m_objects.size();
						m_objects.push_back(object);
						m_objects[index].ptr = new CBSCCatalogObject(this, &m_objects[index]);
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


void CBSC1991Catalog::pickle(QIODevice* os)
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

void CBSC1991Catalog::unpickle(QIODevice* is)
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
		m_objects[index].ptr = new CBSCCatalogObject(this, &m_objects[index]);
	}
}

const CCatalogObject* CBSC1991Catalog::first()
{
	m_index = 0;
	return find();
}

const CCatalogObject* CBSC1991Catalog::next()
{
	assert(m_index >= 0 && m_index < m_objects.size());
	++m_index;
	return find();
}

const CCatalogObject* CBSC1991Catalog::find() const
{
	if (m_index != m_objects.size())
		return m_objects[m_index].ptr;
	return nullptr;
}
