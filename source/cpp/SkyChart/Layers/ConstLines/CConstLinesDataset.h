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
#include "CLines.h"
#include "CBSC1991.h"

class CConstLinesDataset : public CSkyChartDataset
{
public:
	CConstLinesDataset(const CLines* const_lines, QObject* parent = nullptr);

	void paint(QPainter& painter, const CMatrix3d& q, const CProjection& p, const CTransformd& m, const QRectF& paint_rect) override;

private:
	class CPolyline
	{
	public:
		CPolyline() {}
		CPolyline(const std::vector<CVector3d>& pts) : m_pts(pts) {}
		std::optional<QPainterPath> toPath(const CMatrix3d& q, const CProjection& p, const CTransformd& m,
			const QRectF& paint_rect) const;

	private:
		std::vector<CVector3d> m_pts;
	};

	std::vector<CPolyline> m_data;
};
