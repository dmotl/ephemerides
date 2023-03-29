/*!
*  \file      CCatalogLoaderDialog.h
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
#pragma once

#include <QtWidgets>

class CCatalogLoader;

/*!
* \brief Catalog loader (progress dialog)
*
* The CCatalogLoaderDialog implements a dialog window 
* that is presented to the user while the catalogs are
* loaded. 
* 
* The dialog comprises of a label and a progress bar.
* The "Cancel" buttons stops the process.
*
*/
class CCatalogLoaderDialog :public QDialog
{
	Q_OBJECT

public:
	CCatalogLoaderDialog(CCatalogLoader* process, QWidget* parent);

public slots:
	void setCancelEnabled(bool enable) { btnCancel->setVisible(enable); }
	void onSetLabelText(const QString& text) { label->setText(text); }
	void onSetRange(int minimum, int maximum) { pbar->setRange(minimum, maximum); }
	void onSetValue(int value) { pbar->setValue(value); }

protected:
	CCatalogLoader* m_process;
	QLabel* label;
	QProgressBar* pbar;
	QPushButton* btnCancel;

	// Start the thread when the window is shown
	virtual void showEvent(QShowEvent* event);

	// Do not allow to close the window when the thread is running
	virtual void closeEvent(QCloseEvent* event);

	// Escape key calls reject instead of close, which bypasses closeEvent call
	virtual void keyPressEvent(QKeyEvent* event);
};
