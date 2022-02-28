/*!
*  \file      CMoonWidget.h
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

class CMoonWidget : public QWidget
{
public:
	CMoonWidget(QWidget* parent) : QWidget(parent), m_phase(0) {}

	// Phase in radians
	void setPhase(double phase);

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	double m_phase;
};