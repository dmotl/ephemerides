/*!
*  \file      CConstBoundDataset.cpp
*  \author    David Motl
*  \date      2022-06-10
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
#include "CConstBoundsDataset.h"

#include "CBound.h"

CConstBoundsDataset::CConstBoundsDataset(QObject* parent) : CSkyChartDataset(parent)
{
	CBound file;
	tConstellation cons_last = tConstellation::EndOfConstellations;
	Utils::CVector3d previous_pos;
	QList<QPair<Utils::CVector3d, Utils::CVector3d>> pairs;
	auto begin = file.data().begin(), end = file.data().end();
	while (begin != end) {
		CEquCoordinates equ = begin->equatorialJ2000();
		Utils::CVector3d current_pos = Utils::sphericalToRectangular(equ.rightAscension().radians(), equ.declination().radians());
		if (cons_last == begin->constellation()) 
			pairs.append(qMakePair(previous_pos, current_pos));
		else 
			cons_last = begin->constellation();
		previous_pos = current_pos;
		++begin;
	}
	//!!!!!!!!!!!!!!!!!!!precession(1875.0, 2000.0, current_pos);

	if (!pairs.empty()) {
		QVector<bool> processed(pairs.length());
		QList<Utils::CVector3d> pt_list;
		int first_i = processed.indexOf(false);
		while (first_i >= 0) {
			auto current_pair = pairs[first_i];
			pt_list << current_pair.first << current_pair.second;
			processed[first_i] = true;
			int next_i;
			do {
				next_i = -1;
				for (int j = 0; j < pairs.length(); j++) {
					if (!processed[j] && (pairs[j].first != current_pair.second || pairs[j].second != current_pair.first) && (pairs[j].first == current_pair.second || pairs[j].second == current_pair.second)) {
						next_i = j;
						break;
					}
				}
				if (next_i >= 0) {
					if (pairs[next_i].first == current_pair.second) {
						current_pair.second = pairs[next_i].second;
						current_pair.first = pairs[next_i].first;
					}
					else {
						current_pair.second = pairs[next_i].first;
						current_pair.first = pairs[next_i].second;
					}
					pt_list << current_pair.second;
					processed[next_i] = true;
				}
			} while (next_i >= 0);
			if (pt_list.size() >= 2) {
				CCurve curve;
				Utils::CVector3d previous_pos = pt_list.first();
				for (int i = 1; i < pt_list.length(); i++) {
					Utils::CVector3d pts[4], current_pos = pt_list[i];
					assert(previous_pos != current_pos);
					cubic(pts, previous_pos, current_pos);
					if (i == 1)
						curve.append(pts[0]);
					curve.append(pts[1]);
					curve.append(pts[2]);
					curve.append(pts[3]);
					previous_pos = pt_list[i];
				}
				m_data.append(curve);
			}
			pt_list.clear();
			first_i = processed.indexOf(false);
		}
	}
}

void CConstBoundsDataset::paint(QPainter& painter, const QQuaternion& q, const CProjection& p, const QTransform& m)
{
	Qt::GlobalColor color = Qt::transparent;

	painter.setBrush(QBrush());

	// Equatorial grid
	auto begin = m_data.begin(), end = m_data.end();
	while (begin != end) {
		auto path = begin->toPath(q, p, m);
		if (path) {
			if (color != Qt::green) {
				painter.setPen(Qt::green);
				color = Qt::green;
			}
			painter.drawPath(*path);

		}
		++begin;
	}
}

void CConstBoundsDataset::cubic(Utils::CVector3d point[], const Utils::CVector3d& p_start, const Utils::CVector3d& p_end)
{
	Utils::CVector3d start = p_start, end = p_end;

	double z = DBL_MAX;
	if (start[2] == end[2]) {
		// Horizontal line
		z = start[2];
		start[2] = end[2] = 0;
	}

	double AplusBlength = (start + end).length();
	double AminusBlength = (start - end).length();
	double radius = start.length();
	assert(radius > 0 && AplusBlength > 0 && AminusBlength > 0);

	double beta = 0.5 * AminusBlength, alphaSq = radius * radius - beta * beta;
	assert(beta > 0 && alphaSq >= 0);

	double alpha = sqrt(alphaSq);

	Utils::CVector3d P1 = (4 * radius - alpha) / (3.0 * AplusBlength) * (start + end) + (radius - alpha) * (3.0 * radius - alpha) / (3.0 * beta * AminusBlength) * (start - end);
	Utils::CVector3d P2 = (4 * radius - alpha) / (3.0 * AplusBlength) * (start + end) - (radius - alpha) * (3.0 * radius - alpha) / (3.0 * beta * AminusBlength) * (start - end);

	if (z != DBL_MAX)
		start[2] = end[2] = P1[2] = P2[2] = z;

	point[0] = start;
	point[1] = P1;
	point[2] = P2;
	point[3] = end;
}

std::optional<QPainterPath> CConstBoundsDataset::CCurve::toPath(const QQuaternion& q, const CProjection& p, const QTransform& m) const
{
	int size = length();

	QVector<QPointF> xy(size);
	QVector<double> z(size);

	for (int i = 0; i < size; i++) {
		QVector3D r3d;
		for (int j = 0; j < 3; j++)
			r3d[j] = at(i)[j];
		r3d = q.rotatedVector(r3d).normalized();
		p.project(r3d);
		xy[i] = m.map(r3d.toPointF());
		z[i] = r3d.z();
	}

	std::optional<QPainterPath> retval;
	for (int i = 1; i < size - 2; i += 3) {
		if (z[i - 1] >= 0 && z[i] >= 0 && z[i + 1] >= 0 && z[i + 2] >= 0) {
			if (!retval) {
				retval = QPainterPath(xy[i - 1]);
				retval->cubicTo(xy[i], xy[i + 1], xy[i + 2]);
			}
			else {
				retval->moveTo(xy[i - 1]);
				retval->cubicTo(xy[i], xy[i + 1], xy[i + 2]);
			}
		}
	}
	return retval;
}
