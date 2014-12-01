#include "disview.h"

DisView::DisView()
{
    createlefttopView();
    createleftbelowView();
    this->addWidget(lefttopView,30,0);
     this->addWidget(leftbelowView,70,0);
}
DisView::~DisView()
{
    //delete resources
}
void DisView::createlefttopView()
{
    QVBoxLayout
         *layout=new QVBoxLayout;
    CalView *calview=new CalView;
    layout->addWidget(new QLabel("加油次数："));
    layout->addWidget(calview);
    lefttopView=new QWidget();
    lefttopView->setLayout(layout);//w=new QGroupBox(tr("left top view"));

}
void DisView::createleftbelowView()
{
   leftbelowView=new RenderArea();//new QGroupBox(tr("left right view"));
}
