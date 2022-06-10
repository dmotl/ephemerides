/*!
*  \file      CConstBoundDataset.h
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
#pragma once

#include "CSkyChartDataset.h"
#include "SkyChartUtils.h"
#include "CEquCoordinates.h"

class CConstBoundsDataset : public CSkyChartDataset
{
public:
	explicit CConstBoundsDataset(QObject* parent = nullptr);

	void paint(QPainter& painter, const QQuaternion& q, const CProjection& p, const QTransform& m) override;

private:
	class CCurve : public QList<Utils::CVector3d>
	{
	public:
		CCurve() {}
		std::optional<QPainterPath> toPath(const QQuaternion& q, const CProjection& p, const QTransform& m) const;
	};

	static void cubic(Utils::CVector3d out[], const Utils::CVector3d& start, const Utils::CVector3d& end);

	QList<CCurve> m_data;
};