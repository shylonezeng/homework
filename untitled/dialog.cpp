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

#include <QtWidgets>
#include <pthread.h>
#include <unistd.h>
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

    createMenu();
    createleftView();
    createrightView();
//    createFormGroupBox();
    //bind signal and slot
    connect(but_start, SIGNAL(clicked()), this, SLOT(onstart()));
    connect(but_stop, SIGNAL(clicked()), this, SLOT(onstop()));
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
    stime=1000;
    gas_num=0;

}
void Dialog::update_view()
{
 //  review top part and buttom part
}
void* Dialog::call_travel(void *arg)
{
    return reinterpret_cast<Dialog*>(arg)->travel();
}
void* Dialog::travel()
{
   while(!if_renew)
   {
       //some cal
       gas_num++;
       update_view();
       sleep(stime);
   }
}

//! [5]
void Dialog::onstart()
{
    initValue();
    pthread_t pthread;
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
    DisView* left_layout=new DisView();
   leftView->setLayout(left_layout);
}
//! [7]

//! [8]
void Dialog::createrightView()
{
    rightView = new QGroupBox(tr("right layout"));
//! [8]
//!
    QVBoxLayout *layout = new QVBoxLayout;

    source_area *renew_area=new source_area;
//d2_2
    QHBoxLayout *but_area=new QHBoxLayout;

    but_area->addWidget(but_start);
    but_area->addWidget(but_stop);
  //end d2_2
    layout->addLayout(renew_area);
    layout->addLayout(but_area);
    rightView->setLayout(layout);
}
