#ifndef DISVIEW_H
#define DISVIEW_H

#include <QVBoxLayout>
#include <QGroupBox>
#include <QtWidgets>
#include <renderarea.h>
#include <calview.h>
class DisView : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit DisView();
   ~DisView();
    void createlefttopView();
    void createleftbelowView();
    void update_view();
private:
    CalView *calview;
    QWidget *lefttopView;
    RenderArea *leftbelowView;

signals:

public slots:

};

#endif // DISVIEW_H
