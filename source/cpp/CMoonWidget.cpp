/*!
*  \file      CMoonWidget.cpp
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
#include "CMoonWidget.h"

void CMoonWidget::setPhase(double phase)
{
    if (phase != m_phase) {
        m_phase = phase;
        update();
    }
}

void CMoonWidget::paintEvent(QPaintEvent* event)
{
    int radius = (qMin(width(), height()) - 2) / 2, size = radius * 2;
    if (size > 2) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(Qt::NoPen);
        int x = (cos(m_phase) * radius + 0.5);
        if (x == 0) {
            if (m_phase < M_PI) {
                // First quarter
                painter.setBrush(QBrush(Qt::white));
                painter.drawChord((width() - size) / 2, (height() - size) / 2, size, size, 16 * 270, 16 * 180);
                painter.setBrush(QBrush(Qt::black));
                painter.drawChord((width() - size) / 2, (height() - size) / 2, size, size, 16 * 90, 16 * 180);
            }
            else {
                // Last quarter
                painter.setBrush(QBrush(Qt::white));
                painter.drawChord((width() - size) / 2, (height() - size) / 2, size, size, 16 * 90, 16 * 180);
                painter.setBrush(QBrush(Qt::black));
                painter.drawChord((width() - size) / 2, (height() - size) / 2, size, size, 16 * 270, 16 * 180);
            }
        }
        else if (abs(x) == radius) {
            if (m_phase > M_PI / 2 && m_phase < 3 * M_PI / 2) {
                // Full moon 
                painter.setBrush(QBrush(Qt::white));
                painter.drawEllipse((width() - size) / 2, (height() - size) / 2, size, size);
            }
            else {
                // New moon
                painter.setBrush(QBrush(Qt::black));
                painter.drawEllipse((width() - size) / 2, (height() - size) / 2, size, size);
            }
        }
        else if (x > 0) {
            if (m_phase < M_PI) {
                // Waxing crescent
                painter.setBrush(QBrush(Qt::white));
                painter.drawChord((width() - size) / 2, (height() - size) / 2, size, size, 16 * 270, 16 * 180);
                painter.setBrush(QBrush(Qt::black));
                painter.drawChord((width() - size) / 2, (height() - size) / 2, size, size, 16 * 90, 16 * 180);
                painter.drawChord((width() - size) / 2 + (size / 2 - x), (height() - size) / 2, 2 * x, size, 16 * 270, 16 * 180);
            }
            else {
                // Waning crescent
                painter.setBrush(QBrush(Qt::white));
                painter.drawChord((width() - size) / 2, (height() - size) / 2, size, size, 16 * 90, 16 * 180);
                painter.setBrush(QBrush(Qt::black));
                painter.drawChord((width() - size) / 2, (height() - size) / 2, size, size, 16 * 270, 16 * 180);
                painter.drawChord((width() - size) / 2 + (size / 2 - x), (height() - size) / 2, 2 * x, size, 16 * 90, 16 * 180);
            }
        }
        else {
            if (m_phase < M_PI) {
                // Waxing gibbous
                painter.setBrush(QBrush(Qt::black));
                painter.drawChord((width() - size) / 2, (height() - size) / 2, size, size, 16 * 90, 16 * 180);
                painter.setBrush(QBrush(Qt::white));
                painter.drawChord((width() - size) / 2, (height() - size) / 2, size, size, 16 * 270, 16 * 180);
                painter.drawChord((width() - size) / 2 + (size / 2 - x), (height() - size) / 2, 2 * x, size, 16 * 90, 16 * 180);
            }
            else {
                // Waning gibbous
                painter.setBrush(QBrush(Qt::black));
                painter.drawChord((width() - size) / 2, (height() - size) / 2, size, size, 16 * 270, 16 * 180);
                painter.setBrush(QBrush(Qt::white));
                painter.drawChord((width() - size) / 2, (height() - size) / 2, size, size, 16 * 90, 16 * 180);
                painter.drawChord((width() - size) / 2 + (size / 2 - x), (height() - size) / 2, 2 * x, size, 16 * 270, 16 * 180);
            }
        }
    }
}
