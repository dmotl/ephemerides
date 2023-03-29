/*!
*  \file      CCatalogLoader.h
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

class CCatalogList;
class CCatalogLoaderDialog;
class CCatalogLoaderThread;

/*!
* \brief Catalog loader 
*
* The CCatalogLoader encapsulates a worker thread and a progress
* dialog. The CCatalogLoader::exec() method is called in the main
* GUI thread to load known catalogs. The process is executed
* in a worker thread. While the process is running, a progress
* dialog is presented to the user.
*
*/
class CCatalogLoader :public QObject
{
	Q_OBJECT

public:
	explicit CCatalogLoader(CCatalogList* catalogs, QWidget* parent = nullptr);

	virtual int exec();

signals:
	void setCancelEnabled(bool enable);
	void setLabelText(const QString& text);
	void setRange(int minimum, int maximum);
	void setValue(int value);

protected:
	CCatalogList* m_catalogs;

	virtual int run();

	virtual bool isCancelled(void) { return m_cancelled; }

private:
	friend class CCatalogLoaderDialog;
	friend class CCatalogLoaderThread;

	int m_retval;
	bool m_cancelled;
	CCatalogLoaderDialog* m_dialog;
	CCatalogLoaderThread* m_thread;

private slots:
	void onThreadFinished();
	void onCancelClicked();
};
