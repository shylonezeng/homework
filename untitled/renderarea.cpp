#include "renderarea.h"
#include <QPainter>

#ifndef MAX_SIZE
#define MAX_SIZE 32
#endif
//! [0]
RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    pixmap.load(":/images/qt-logo.png");

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    st_dis=NULL;
    reset_members(0,0,NULL);
}
RenderArea::~RenderArea()
{
    if(st_dis)
        delete st_dis;
}

void RenderArea::update_ui(int st)
{
    this->current_st=st;
    update();
}
//! [8]
bool RenderArea::reset_members(int maxsize,int st_num,int *st_dis)
{
    global_scale=0.8;
    rads=10*global_scale;
    scale=30*global_scale;

    current_st=0;
    flag_drawtext=0;
    if(st_dis!=NULL)
    {
        this->st_dis=st_dis;
        this->st_num=(++st_num);
        this->maxsize=maxsize;
        return true;
    }

    //otherwise
    this->maxsize=7;
    this->st_num=6;   this->st_num+=1;
    int temp[MAX_SIZE]={2,2,3,4,5,1,6,6,
                        2,1,3,4,2,3,1,2,
                        4,3,2,3,2,4,1,4,
                        12,2,23,2,23,21,23,2
                       };
    if(this->st_dis==NULL)
        this->st_dis=new int[MAXSIZE+1];
    std::copy(temp,temp+sizeof(temp)/sizeof(int),this->st_dis);
    return false;
}
void RenderArea::drawline_and_move(QPainter &painter,int *x,int *y,int station)
{
    //painter.
    painter.save();

    int len=st_dis[station]*scale;
    painter.drawLine(QPoint(*x,*y+rads),QPoint(*x+len,*y+rads));
    *x+=len;
    painter.translate(*x,*y);

    painter.restore();
}
void RenderArea::drawround_and_move (QPainter &painter,int *x,int *y)
{
    painter.save();

    int width=2*rads,height=width;
    painter.drawEllipse(QRect(*x,*y,width,height));
    //output message
    char msg[1024];

//    painter.restore();

    if(flag_drawtext<=st_num)
    {
  //      painter.save();

        if(flag_drawtext==0)
            sprintf(msg,"Start");
        else if(flag_drawtext==st_num)
            sprintf(msg,"Destination");
        else
            sprintf(msg,"station %d",flag_drawtext);
        painter.drawText(QRect(*x-20,*y+2*rads,150,height), Qt::AlignLeft, tr(msg));
        flag_drawtext++;

    //    painter.restore();
    }
    else
        flag_drawtext=0;

    *x+=width;
    painter.translate(*x,*y);

    painter.restore();
}
void setDrawStype(QPainter& painter)
{
    //pen initiaize before using
    Qt::PenStyle style=Qt::PenStyle(Qt::DashLine);
    QPen pen;
    pen.setStyle(style);

    painter.setPen(pen);
}
void set_brushstyle(QPainter &painter)
{

    QPen pen;
    Qt::PenStyle style=Qt::PenStyle(Qt::SolidLine);
    pen.setStyle(style);
    pen.setWidth(3);

    Qt::BrushStyle bstyle=Qt::BrushStyle(Qt::Dense1Pattern);
    QBrush brush(Qt::red,bstyle);

    painter.setPen(pen);
    painter.setBrush(brush);
}

void RenderArea::once_draw(QPainter& painter,int draw_to)
{
    QRect rect(0, 0, 20,20);
    //   painter.translate(x,y);
    //  painter.drawRect(rect);
    int x=width()*0.05,y=this->height()/2;
    this->drawround_and_move(painter,&x,&y);
    for (int i=0;i<draw_to;++i)
    {
        this->drawline_and_move(painter,&x,&y,i);
        this->drawround_and_move(painter,&x,&y);
        //	painter.drawRoundedRect(rect, 25, 25, Qt::RelativeSize);

    }


}
void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    static const QPoint points[4] = {
        QPoint(10, 80),
        QPoint(20, 10),
        QPoint(80, 30),
        QPoint(90, 70)
    };

    QPainter painter(this);

    setDrawStype(painter);
    once_draw(painter,st_num);

    //change pen and brush , draw second time
    set_brushstyle(painter);
    once_draw(painter,current_st);

    //  painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
    // unknown doing;
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    //restore painter
}
/***********************************************************************/

//void RenderArea::paintEvent(QPaintEvent * /* event */)
/*{
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
}*/
