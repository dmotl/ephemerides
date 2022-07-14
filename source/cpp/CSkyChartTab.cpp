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

//
// Constructor
//
CSkyChartTab::CSkyChartTab(CMainWindow* mainWnd, QWidget* parent) : CMainTabWidget(mainWnd, parent),
m_toolBar(NULL), m_toolsBtn(NULL), m_toolsMenu(NULL), m_toolsActionMapper(NULL)
{
	setupUi(this);
	setText(tr("Sky chart"));
	layout()->setContentsMargins(0, 0, 0, 0);
	toolBox->layout()->setContentsMargins(9, 9, 9, 9);

	m_toolsActionMapper = new QSignalMapper(this);
	connect(m_toolsActionMapper, &QSignalMapper::mappedInt, this, &CSkyChartTab::onToolsAction);

	view->addDataset(new CEquGridDataset());
	view->addDataset(new CBrightStarCatalogDataset());
	view->addDataset(new CConstBoundsDataset());

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

	qSSpinBox->blockSignals(true);
	qSSpinBox->setValue(q.scalar());
	qSSpinBox->blockSignals(false);

	qXSpinBox->blockSignals(true);
	qXSpinBox->setValue(q.x());
	qXSpinBox->blockSignals(false);

	qYSpinBox->blockSignals(true);
	qYSpinBox->setValue(q.y());
	qYSpinBox->blockSignals(false);

	qZSpinBox->blockSignals(true);
	qZSpinBox->setValue(q.z());
	qZSpinBox->blockSignals(false);

	CEquCoordinates equ = view->centerCoords();

	raSpinBox->blockSignals(true);
	raSpinBox->setValue(equ.rightAscension().hours());
	raSpinBox->blockSignals(false);

	decSpinBox->blockSignals(true);
	decSpinBox->setValue(equ.declination().degrees());
	decSpinBox->blockSignals(false);
}

void CSkyChartTab::on_qSSpinBox_valueChanged(double value)
{
	CQuaterniond q = view->viewQuat();
	q.setScalar(value);
	view->setViewQuat(q);
	on_view_viewChanged();
}

void CSkyChartTab::on_qXSpinBox_valueChanged(double value)
{
	CQuaterniond q = view->viewQuat();
	q.setX(value);
	view->setViewQuat(q);
	on_view_viewChanged();
}

void CSkyChartTab::on_qYSpinBox_valueChanged(double value)
{
	CQuaterniond q = view->viewQuat();
	q.setY(value);
	view->setViewQuat(q);
	on_view_viewChanged();
}

void CSkyChartTab::on_qZSpinBox_valueChanged(double value)
{
	CQuaterniond q = view->viewQuat();
	q.setZ(value);
	view->setViewQuat(q);
	on_view_viewChanged();
}

void CSkyChartTab::on_btnCopyQ_clicked(void)
{
	CQuaterniond q = view->viewQuat();
	QStringList str;
	str << QString::number(q.x(), 'f', 12);
	str << QString::number(q.y(), 'f', 12);
	str << QString::number(q.z(), 'f', 12);
	str << QString::number(q.scalar(), 'f', 12);
	str << QString::number(view->scale(), 'f', 12);
	qApp->clipboard()->setText(str.join(QStringLiteral(" ")));
}

void CSkyChartTab::on_btnPasteQ_clicked(void)
{
	QStringList str = qApp->clipboard()->text().split(QStringLiteral(" "));
	if (str.size() >= 4) {
		CQuaterniond q(str[0].toDouble(), str[1].toDouble(), str[2].toDouble(), str[3].toDouble());
		if (!q.isNull())
			view->setViewQuat(q);
	}
	if (str.size() >= 5) {
		double scale = str[4].toDouble();
		if (scale > 0)
			view->setScale(scale);
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
