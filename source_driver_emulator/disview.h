#ifndef DISVIEW_H
#define DISVIEW_H

#include <QVBoxLayout>
#include <QGroupBox>
#include <QtWidgets>
#include <renderarea.h>
#include <calview.h>
#include <QLabel>
class DisView : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit DisView();
   ~DisView();
    void createlefttopView();
    void createleftbelowView();
    void update_ui(int,int gas_add);
    static void error(char *msg);
private:
 //   CalView *calview;
   QLabel *calview;
    QWidget *lefttopView;
public:
    RenderArea *leftbelowView;

signals:

public slots:

};

#endif // DISVIEW_H
