/*!
*  \file      CSunWidget.cpp
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
#include "CSunWidget.h"

void CSunWidget::paintEvent(QPaintEvent* event)
{
    int size = qMin(width(), height()) - 2;
    if (size > 2) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(QColor(qRgb(255, 96, 0)), 1));
        painter.setBrush(QBrush(QColor(qRgb(255, 192, 0))));
        painter.drawEllipse((width() - size) / 2, (height() - size) / 2, size, size);
    }
}
