#ifndef CALVIEW_H
#define CALVIEW_H

#include <QLabel>
#include <QFont>
#include <QLabel>
#include <stdio.h>
class CalView : public QLabel
{
    Q_OBJECT
public:
    explicit CalView(QLabel *parent = 0);
    void operator ++();
    void operator =(int);
protected:
   // void paintEvent(QPaintEvent *event);
    void write(int n);
private:
    int num;
signals:

public slots:

};

#endif // CALVIEW_H
