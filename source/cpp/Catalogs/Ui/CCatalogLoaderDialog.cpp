/*!
*  \file      CCatalogLoaderDialog.cpp
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
#include "CCatalogLoaderDialog.h"

#include "CCatalogLoaderThread.h"

CCatalogLoaderDialog::CCatalogLoaderDialog(CCatalogLoader* process, QWidget* parent) :QDialog(parent), m_process(process)
{
	setWindowModality(Qt::WindowModal);
	setWindowTitle(tr("Please, wait..."));

	QVBoxLayout* mainLayout = new QVBoxLayout(this);

	label = new QLabel(this);
	label->setTextFormat(Qt::PlainText);
	label->setAlignment(Qt::AlignCenter);
	label->setMargin(6);
	mainLayout->addWidget(label);

	pbar = new QProgressBar(this);
	pbar->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	pbar->setRange(0, 1000);
	pbar->setMinimumWidth(250);
	pbar->setValue(0);
	mainLayout->addWidget(pbar);

	QBoxLayout* btnBox = new QHBoxLayout();
	mainLayout->addLayout(btnBox);
	btnBox->addStretch(20);

	btnCancel = new QPushButton(tr("Cancel"), this);
	btnCancel->setAutoDefault(false);
	btnCancel->setVisible(false);
	btnBox->addWidget(btnCancel);
	connect(btnCancel, SIGNAL(clicked()), m_process, SLOT(onCancelClicked()));
}

void CCatalogLoaderDialog::showEvent(QShowEvent* event)
{
	if (!m_process->m_thread) {
		m_process->m_thread = new CCatalogLoaderThread(m_process, this);
		connect(m_process->m_thread, SIGNAL(finished()), m_process, SLOT(onThreadFinished()));
		m_process->m_thread->start();
	}
	QDialog::showEvent(event);
}

void CCatalogLoaderDialog::closeEvent(QCloseEvent* event)
{
	if (m_process->m_thread) {
		event->ignore();
		return;
	}
	QDialog::closeEvent(event);
}

//
// Escape key calls reject instead of close, which bypasses closeEvent call
// Ignore the Escape key when a process is running
//
void CCatalogLoaderDialog::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Escape && m_process->m_thread) {
		event->ignore();
		return;
	}
	QDialog::keyPressEvent(event);
}
