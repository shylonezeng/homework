/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "dialog.h"

//! [0]
Dialog::Dialog()
{

    //init window size
    QRect rec = QApplication::desktop()->screenGeometry();
    int height = rec.height()*0.8;
    int width = rec.width()*0.8;
    this->setFixedSize(width,height);
    //ui init
    but_start=new QPushButton("start");
    but_stop=new QPushButton("stop");

    createrightView();
    createMenu();
    createleftView();
    //    createFormGroupBox();
    //bind signal and slot
    connect(but_start, SIGNAL(clicked()), this, SLOT(onstart()));
    connect(but_stop, SIGNAL(clicked()), this, SLOT(onstop()));
   connect(this,&Dialog::signal_update,this,&Dialog::update_view);
    //! [2]
    QHBoxLayout *mainLayout = new QHBoxLayout;
    //   mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(leftView,70,0);
    mainLayout->addWidget(rightView,30,0);

    setLayout(mainLayout);
    setWindowTitle(tr("Greedy"));
    //
    initValue();
}

//algorithm core value initialize
void Dialog::initValue()
{
    if_renew=true;
    stime=2;
  //  gas_num=0;

}
void Dialog::update_view(int value,int gas_add)
{
    //  review top part and buttom part
    left_disview->update_ui(value,gas_add);
}
void* Dialog::call_travel(void *arg)
{
    return reinterpret_cast<Dialog*>(arg)->travel();
}
bool Dialog::readValue()
{
    return  input_area->get_input(st_dis,&st_num,&max_dis_full);
}
void* Dialog::travel()
{
    //    int travel(int d[],int max_dis_full,int num_sta) {
    bool ret=readValue();
    if (!ret)
    {
        //or popup dialog box
       // left_disview-> error("data erro");
        qDebug()<<"data read error";
        return (void*)-1;
    }
 /*   if (st_dis[0]>max_dis_full)
    {
        qDebug()<<"st_dis[0]>max_dis_full";
    }
   */ left_disview->leftbelowView->reset_members(max_dis_full,st_num,st_dis);
    //get to first station
    int num=0;
    int dis_remain=max_dis_full;
   // dis_remain-=st_dis[0];
    emit signal_update(0,0);
    qDebug()<<"travel line 115";
    int i;
    for(i = 0;if_renew && i <= st_num;i++) {
        //s += st_dis[i];
    qDebug()<<"step into for loop (line 117):";
        if(st_dis[i]>max_dis_full )
        {
             emit signal_update(i,-1);
            return (void*)-1;
        }
        else if((dis_remain-=st_dis[i])<0) {
            num++;
            qDebug()<<"station number:"<<num;
            dis_remain=max_dis_full-st_dis[i];
            RenderArea::if_add[i-1]=true;
        }
        emit signal_update(i,num);
        sleep(stime);
    }
     emit signal_update(i,num);
    return (void*)num;
    //     }/*end travel function*/

}


//! [5]
void Dialog::onstart()
{
    if(pthread>0)
    {
        pthread_cancel(pthread);
    }
    initValue();
    if_renew=true;
    pthread_create(&pthread,0,&Dialog::call_travel,this);
}

void Dialog::onstop()
{
    if_renew=false;
}
//! [6]
void Dialog::createMenu()
{
    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);

    connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
}
//! [6]

//! [7]
void Dialog::createleftView()
{
    leftView = new QGroupBox(tr("left_left_layout"));
    //  QVBoxLayout *left_layout = new QVBoxLayout;
    left_disview=new DisView();
    leftView->setLayout(left_disview);
}
//! [7]

//! [8]
void Dialog::createrightView()
{
   rightView = new QGroupBox(tr("right layout"));
    //! [8]
    //!
    QVBoxLayout *layout = new QVBoxLayout;

     input_area=new source_area;
    //d2_2
    QHBoxLayout *but_area=new QHBoxLayout;

    but_area->addWidget(but_start);
    but_area->addWidget(but_stop);
    //end d2_2
    layout->addLayout(input_area);
    layout->addLayout(but_area);
    rightView->setLayout(layout);
}
