/*!
*  \file      CSkyChartTab.cpp
*  \author    David Motl
*  \date      2022-05-11
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
#include "CSkyChartTab.h"

#include "CEquGridDataset.h"
#include "CBrightStarCatalogDataset.h"
#include "CConstBoundsDataset.h"
#include "CConstLinesDataset.h"
#include "CStereographicProjection.h"
#include "CSharedData.h"
#include "UtilsQt.h"
#include "CMainDockWidget.h"

//
// Constructor
//
CSkyChartTab::CSkyChartTab(CSharedData* sharedData, CMainWindow* mainWnd, QWidget* parent) : CMainTabWidget(sharedData, mainWnd, parent)
{
	registerTabWidget(type_id);

	setupUi(this);

	layout()->setContentsMargins(0, 0, 0, 0);
	toolBox->layout()->setContentsMargins(9, 9, 9, 9);

	view->addDataset(new CEquGridDataset(this));
	view->addDataset(new CBrightStarCatalogDataset(m_sharedData->bsc(), this));
	view->addDataset(new CConstBoundsDataset(m_sharedData->constBound(), this));
	view->addDataset(new CConstLinesDataset(m_sharedData->constLines(), this));

	view->setProjector(new CStereographicProjection(this));

	createToolBar(mainFrame);

	on_view_viewChanged();
}

void CSkyChartTab::on_view_viewChanged(void)
{
	CEquCoordinates equ = view->centerCoords();

	raSpinBox->blockSignals(true);
	raSpinBox->setValue(equ.rightAscension().hours());
	raSpinBox->blockSignals(false);

	decSpinBox->blockSignals(true);
	decSpinBox->setValue(equ.declination().degrees());
	decSpinBox->blockSignals(false);
}

void CSkyChartTab::on_raSpinBox_valueChanged(double value)
{
	CEquCoordinates e = view->centerCoords();
	e.setRightAscension(CRightAscension::fromHours(value));
	view->setCoords(e);
	on_view_viewChanged();
}

void CSkyChartTab::on_decSpinBox_valueChanged(double value)
{
	CEquCoordinates e = view->centerCoords();
	e.setDeclination(CDeclination::fromDegrees(value));
	view->setCoords(e);
	on_view_viewChanged();
}

void CSkyChartTab::on_btnCopyE_clicked(void)
{
	CEquCoordinates equ = view->centerCoords();
	
	QStringList str;
	str << QString::number(equ.rightAscension().radians(), 'f', 12);
	str << QString::number(equ.declination().radians(), 'f', 12);
	str << QString::number(view->scale(), 'f', 12);
	qApp->clipboard()->setText(str.join(QStringLiteral(" ")));
}

void CSkyChartTab::on_btnPasteE_clicked(void)
{
	QStringList str = qApp->clipboard()->text().split(QStringLiteral(" "));
	if (str.size() >= 2) {
		CEquCoordinates q(str[0].toDouble(), str[1].toDouble());
		if (q.isValid())
			view->setCoords(q);
	}
	if (str.size() >= 3) {
		double scale = str[2].toDouble();
		if (scale > 0)
			view->setScale(scale);
	}
}
