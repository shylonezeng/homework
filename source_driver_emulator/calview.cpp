#include "calview.h"

CalView::CalView(QTextEdit *parent) :
    QTextEdit(parent)
{
    connect(this,&CalView::signal_write,this,&CalView::write);
    num=0;
    this->setStyleSheet("QTextEdit { color : blue; }");
    this->setFont(QFont("Courier",150, QFont::Bold, false));
    this->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter	);
    setText("0");
}
void CalView::write(int n)
{
    char buff[1024];
    sprintf(buff,"%d",n);
    QString str(buff);
    setText(str);
}
void CalView::error(char *msg)
{
    if(!msg)
   {
        qDebug()<<"calview message is NULL";
        return;
    }
    QString str(msg);
    setText(str);
}
void CalView::addone()
{
    num=num+1;
    write(num);
}
void CalView::operator =(int n)
{
    num=n;
    write(num);
}

