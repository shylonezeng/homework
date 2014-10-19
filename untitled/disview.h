#ifndef DISVIEW_H
#define DISVIEW_H

#include <QVBoxLayout>
#include <QGroupBox>
#include <QtWidgets>
class DisView : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit DisView();
    void createlefttopView();
    void createleftbelowView();
    void update_view();
private:
    QGroupBox *lefttopView;
    QGroupBox *leftbelowView;
signals:

public slots:

};

#endif // DISVIEW_H
