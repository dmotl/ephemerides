/*!
*  \file      CCheckListDialog.h
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

#include "ui_CCheckListDialog.h"

class CMainWindow;

/*!
* \brief Check list dialog
* 
* The dialog presents a list of items. The user can check and uncheck
* the items. The dialog is used to edit item-based filters, such as
* selection of constellations.
*/
class CCheckListDialog : public QDialog, private Ui::CCheckListDialog
{
	Q_OBJECT

public:
	/*!
	* \brief Constructor
	* \param parent parent widget
	*/ 
	CCheckListDialog(QWidget* parent);
};
