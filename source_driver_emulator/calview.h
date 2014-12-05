#ifndef CALVIEW_H
#define CALVIEW_H

#include <QFont>
#include <QTextEdit>
#include <stdio.h>
#include <QDebug>
class CalView : public QTextEdit
{
    Q_OBJECT
public:
    explicit CalView(QTextEdit *parent = 0);
    void addone();
    void operator =(int);
    void error(char *msg);
   // void paintEvent(QPaintEvent *event);
private:
    int num;
signals:
    void signal_write(int n);
public slots:
    void write(int n);
};

#endif // CALVIEW_H
