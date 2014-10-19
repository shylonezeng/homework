#include "renderarea.h"

#include <QPainter>

//! [0]
RenderArea::RenderArea(QWidget *parent)
        : QWidget(parent)
{
    shape = Polygon;
    antialiased = false;
    transformed = false;
    pixmap.load(":/images/qt-logo.png");

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    rads=10;
    scale=1;
}
//! [0]

//! [1]
QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}
//! [1]

//! [2]
QSize RenderArea::sizeHint() const
{
    return QSize(400, 200);
}
//! [2]

//! [3]
void RenderArea::setShape(Shape shape)
{
    this->shape = shape;
}
//! [3]

//! [4]
void RenderArea::setPen(const QPen &pen)
{
    this->pen = pen;
}
//! [4]

//! [5]
void RenderArea::setBrush(const QBrush &brush)
{
    this->brush = brush;
}
//! [5]

//! [6]
void RenderArea::setAntialiased(bool antialiased)
{
    this->antialiased = antialiased;
}
//! [6]

//! [7]
void RenderArea::setTransformed(bool transformed)
{
    this->transformed = transformed;
}
//! [7]

//! [8]
void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    static const QPoint points[4] = {
            QPoint(10, 80),
            QPoint(20, 10),
            QPoint(80, 30),
            QPoint(90, 70)
    };

    QRect rect(10, 20, 80, 60);

    QPainterPath path;
    path.moveTo(20, 80);
    path.lineTo(20, 30);
    path.cubicTo(80, 0, 50, 50, 80, 80);

    int startAngle = 20 * 16;
    int arcLength = 120 * 16;
    //! [8]

    //! [9]
    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);
    if (antialiased)
        painter.setRenderHint(QPainter::Antialiasing, true);
    //! [9]

    //! [10]
    for (int x = 0; x < width(); x += 100) {
        for (int y = 0; y < height(); y += 100) {
            painter.save();
            painter.translate(x, y);
            //! [10] //! [11]
            if (transformed) {
                painter.translate(50, 50);
                painter.rotate(60.0); painter.scale(0.6, 0.9); painter.translate(-50, -50); } //! [11]
            //! [12]
            switch (shape) {
            case Line:
                painter.drawLine(rect.bottomLeft(), rect.topRight());
                break;
            case Points:
                painter.drawPoints(points, 4);
                break;
            case Polyline:
                painter.drawPolyline(points, 4);
                break;
            case Polygon:
                painter.drawPolygon(points, 4);
                break;
            case Rect:
                painter.drawRect(rect);
                break;
            case RoundedRect:
                painter.drawRoundedRect(rect, 25, 25, Qt::RelativeSize);
                break;
            case Ellipse:
                painter.drawEllipse(rect);
                break;
            case Arc:
                painter.drawArc(rect, startAngle, arcLength);
                break;
            case Chord:
                painter.drawChord(rect, startAngle, arcLength);
                break;
            case Pie:
                painter.drawPie(rect, startAngle, arcLength);
                break;
            case Path:
                painter.drawPath(path);
                break;
            case Text:
                painter.drawText(rect, Qt::AlignCenter, tr("Qt by\nDigia"));
                break;
            case Pixmap:
                painter.drawPixmap(10, 10, pixmap);
            }
            //! [12] //! [13]
            painter.restore();
        }
    }

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
void RenderArea::drawline_and_move(QPainter &painter,int *x,int *y,int station)
{
    //painter.
    int len=st_dis[station]*scale;
    painter.drawline(QPoint(x,y+rads),QPoint(x+len,y+rads));
    x+=len;
    painter.translate(x,y);

}
void RenderArea::drawround_and_move (QPainter &painter,int *x,int *y,int station)
{
    int width=2*rads,height=width;
    painter.drawEllipse(QRect(x,y,width,height));
    x+=width;
    painter.translate(x,y);
}
void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    static const QPoint points[4] = {
            QPoint(10, 80),
            QPoint(20, 10),
            QPoint(80, 30),
            QPoint(90, 70)
    };

/*
    QPainterPath path;
    path.moveTo(20, 80);
    path.lineTo(20, 30);
    path.cubicTo(80, 0, 50, 50, 80, 80);

    int startAngle = 20 * 16;
    int arcLength = 120 * 16;
    *///! [8]

    //! [9]
    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);
    if (antialiased)
        painter.setRenderHint(QPainter::Antialiasing, true);
    //! [9]

    //! [10]

    QRect rect(10, 20, 20,20);

    int unit=1;
      int x=100,y=this->height()/2;
      painter.save();
      painter.translate(x,y);
      painter.drawRect(rect);
     painter.restore();

    bool if_round=false;
    for (int i=0;i<st_num;++i)
    {
        painter.save();
        painter.translate(x, y);
        //! [10] //! [1u1
        if (transformed) {

            painter.translate(50, 50);
            painter.rotate(60.0); painter.scale(0.6, 0.9); painter.translate(-50, -50); } //! [11]
        if(if_round)
            painter.drawEllipse(rect);
        else
            painter.drawLine(rect.bottomLeft(), rect.topRight());
        if_round~=if_round;
    //	painter.drawRoundedRect(rect, 25, 25, Qt::RelativeSize);
    //	painter.drawText(rect, Qt::AlignCenter, tr("Qt by\nDigia"));


        painter.restore();
    }


    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRefct(0, 0, width() - 1, height() - 1));
}
