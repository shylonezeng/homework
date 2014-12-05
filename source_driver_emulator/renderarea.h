/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef RENDERAREA_H
#define RENDERAREA_H
#include <algorithm>
#include <cstring>
#include "stdio.h"
#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
QT_BEGIN_NAMESPACE
    #define MAXSIZE 1024
QT_END_NAMESPACE

//! [0]
class RenderArea : public QWidget
{
    Q_OBJECT

public:
    enum Shape { Line, Points, Polyline, Polygon, Rect, RoundedRect, Ellipse, Arc,
                 Chord, Pie, Path, Text, Pixmap };

    RenderArea(QWidget *parent = 0);
    ~RenderArea();

    static bool if_add[1024];
public slots:
/*    void setShape(Shape shape);
    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);
    void setAntialiased(bool antialiased);
    void setTransformed(bool transformed);
*/
protected:
    void drawround_and_move (QPainter &painter,int *x,int *y);
    void drawline_and_move (QPainter &painter,int *x,int *y,int station);
    void  once_draw( QPainter &painter,int draw_to);
public:
    bool reset_members(int ,int ,int*);
    void update_ui(int );
protected:
    void paintEvent(QPaintEvent *event);

private:
   Shape shape;
    QPen pen;
  //  QBrush brush;
    bool antialiased;
    bool transformed;
    QPixmap pixmap;
private:
    float global_scale;
    int scale;
    int rads;
    int maxsize;
    int st_num;
    int *st_dis;
    int current_st;
    int flag_drawtext;
};
//! [0]

#endif // RENDERAREA_H
