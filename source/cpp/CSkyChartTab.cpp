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

//
// Constructor
//
CSkyChartTab::CSkyChartTab(CSharedData* sharedData, CMainWindow* mainWnd, QWidget* parent) : CMainTabWidget(sharedData, mainWnd, parent),
m_toolBar(NULL), m_toolsBtn(NULL), m_toolsMenu(NULL), m_toolsActionMapper(NULL)
{
	setupUi(this);
	setText(tr("Sky chart"));
	layout()->setContentsMargins(0, 0, 0, 0);
	toolBox->layout()->setContentsMargins(9, 9, 9, 9);

	m_toolsActionMapper = new QSignalMapper(this);
	connect(m_toolsActionMapper, &QSignalMapper::mappedInt, this, &CSkyChartTab::onToolsAction);

	view->addDataset(new CEquGridDataset(this));
	view->addDataset(new CBrightStarCatalogDataset(m_sharedData->bsc(), this));
	view->addDataset(new CConstBoundsDataset(m_sharedData->constBound(), this));
	view->addDataset(new CConstLinesDataset(m_sharedData->constLines(), this));

	view->setProjector(new CStereographicProjection(this));

	createToolBar();

	on_view_viewChanged();
}


//
// Create toolbar and actions
//
void CSkyChartTab::createToolBar()
{
	m_toolBar = new QToolBar(this);
	static_cast<QVBoxLayout*>(mainFrame->layout())->insertWidget(0, m_toolBar);
	m_toolBar->setFloatable(false);
	m_toolBar->setMovable(false);

	m_toolsMenu = new QMenu(this);

	m_toolsBtn = new QToolButton(this);
	m_toolsBtn->setText(tr("Tools"));
	m_toolsBtn->setPopupMode(QToolButton::InstantPopup);
	m_toolsBtn->setMenu(m_toolsMenu);
	m_toolsAction = m_toolBar->addWidget(m_toolsBtn);

	m_helpAction = m_toolsMenu->addAction(tr("Help"));
}


//
// Handle toolbar actions
//
void CSkyChartTab::onToolsAction(int dockWidgetId)
{

}


void CSkyChartTab::on_view_viewChanged(void)
{
	CQuaterniond q = view->viewQuat();

	pitchSpinBox->blockSignals(true);
	pitchSpinBox->setValue(RAD_TO_DEG(q.pitch()));
	pitchSpinBox->blockSignals(false);

	yawSpinBox->blockSignals(true);
	yawSpinBox->setValue(RAD_TO_DEG(q.yaw()));
	yawSpinBox->blockSignals(false);

	rollSpinBox->blockSignals(true);
	rollSpinBox->setValue(RAD_TO_DEG(q.roll()));
	rollSpinBox->blockSignals(false);

	CEquCoordinates equ = view->centerCoords();

	raSpinBox->blockSignals(true);
	raSpinBox->setValue(equ.rightAscension().hours());
	raSpinBox->blockSignals(false);

	decSpinBox->blockSignals(true);
	decSpinBox->setValue(equ.declination().degrees());
	decSpinBox->blockSignals(false);
}

void CSkyChartTab::on_pitchSpinBox_valueChanged(double value)
{
	CQuaterniond q = view->viewQuat();
	q = CQuaterniond::fromEulerAngles(DEG_TO_RAD(value), q.yaw(), q.roll());
	view->setViewQuat(q);
	on_view_viewChanged();
}

void CSkyChartTab::on_yawSpinBox_valueChanged(double value)
{
	CQuaterniond q = view->viewQuat();
	q = CQuaterniond::fromEulerAngles(q.pitch(), DEG_TO_RAD(value), q.roll());
	view->setViewQuat(q);
	on_view_viewChanged();
}

void CSkyChartTab::on_rollSpinBox_valueChanged(double value)
{
	CQuaterniond q = view->viewQuat();
	q = CQuaterniond::fromEulerAngles(q.pitch(), q.yaw(), DEG_TO_RAD(value));
	view->setViewQuat(q);
	on_view_viewChanged();
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

void CSkyChartTab::on_btnCopyQ_clicked(void)
{
	CQuaterniond q = view->viewQuat();
	QStringList str;
	str << QString::number(q.pitch(), 'f', 12);
	str << QString::number(q.yaw(), 'f', 12);
	str << QString::number(q.roll(), 'f', 12);
	qApp->clipboard()->setText(str.join(QStringLiteral(" ")));
}

void CSkyChartTab::on_btnPasteQ_clicked(void)
{
	QStringList str = qApp->clipboard()->text().split(QStringLiteral(" "));
	if (str.size() == 3) {
		CQuaterniond q = CQuaterniond::fromEulerAngles(str[0].toDouble(), str[1].toDouble(), str[2].toDouble());
		if (!q.isNull())
			view->setViewQuat(q);
	}
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
