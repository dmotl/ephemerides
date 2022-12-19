/*!
*  \file      CSetupDialog.h
*  \author    David Motl
*  \date      2022-01-31
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

#include "ui_CSetupDialog.h"

class CSharedData;

/*
* \brief Configuration dialog
* 
* The CSetupDialog implements the dialog for setting the configuration parameters,
* such as position of the observer.
* 
*/
class CSetupDialog : public QDialog, private Ui::CSetupDialog
{
	Q_OBJECT

public:
	/*! 
	* \brief Constructor
	* 
	* \param parent parent widget
	*/
	CSetupDialog(QWidget* parent);
};
