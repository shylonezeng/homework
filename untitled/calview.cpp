#include "calview.h"

CalView::CalView(QLabel *parent) :
    QLabel(parent)
{
    num=0;
    this->setStyleSheet("QLabel { color : blue; }");
    this->setFont(QFont("Courier",150, QFont::Bold, false));
    this->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter	);
    write(0);
}
void CalView::write(int n)
{
    char buff[1024];
    sprintf(buff,"%d",n);
    this->setText(buff);
}
void CalView::operator ++()
{
    num++;
    write(num);
}
void CalView::operator =(int n)
{
    num=n;
    write(num);
}

