#include "disview.h"

DisView::DisView()
{
    createlefttopView();
    createleftbelowView();
    this->addWidget(lefttopView);
     this->addWidget(leftbelowView);
}

void DisView::createlefttopView()
{
    QVBoxLayout
         *layout=new QVBoxLayout;
    layout->addWidget(new QLabel("加油次数："));
    layout->addWidget(new QWidget);
    lefttopView=new QGroupBox(tr("left top"));
    lefttopView->setLayout(layout);//w=new QGroupBox(tr("left top view"));

}
void DisView::createleftbelowView()
{
    leftbelowView=new QGroupBox(tr("left right view"));
}
