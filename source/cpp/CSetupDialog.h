#pragma once

#include <QtWidgets>

#include "ui_CSetupDialog.h"

class CMainWindow;

class CSetupDialog : public QDialog, private Ui::CSetupDialog
{
	Q_OBJECT

public:
	// Constructor
	CSetupDialog(CMainWindow* mainWnd, QWidget* parent);
};
