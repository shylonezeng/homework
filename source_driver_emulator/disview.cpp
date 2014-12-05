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
void DisView::update_ui(int num,int gas_add)
{
    char buff[1024];
    if(gas_add==-1)
      sprintf(buff,"failed");
    else
        sprintf(buff,"%d",gas_add);
    QString str(buff);
    calview->setText(str);
    //
    leftbelowView->update_ui(num);
}
void DisView::createlefttopView()
{
    QVBoxLayout
         *layout=new QVBoxLayout;

    //CalView *calview=new CalView;
    calview=new QLabel;
    calview->setStyleSheet("QTextEdit { color : blue; }");
    calview->setFont(QFont("Courier",150, QFont::Bold, false));
    calview->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter	);
    calview->setText("0");

    layout->addWidget(new QLabel("加油次数："));
    layout->addWidget(calview);
    lefttopView=new QWidget();
    lefttopView->setLayout(layout);//w=new QGroupBox(tr("left top view"));

}
void DisView::createleftbelowView()
{
   leftbelowView=new RenderArea();//new QGroupBox(tr("left right view"));
    leftbelowView->reset_members(0,0,NULL);

}

