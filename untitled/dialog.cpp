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
//! [0]

//! [1]
    bigEditor = new QTextEdit;
    bigEditor->setPlainText(tr("This widget takes up all the remaining space "
                               "in the top-level layout."));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);
    //bind signal and slot
    connect(but_start, SIGNAL(clicked()), this, SLOT(onstart()));
    connect(but_stop, SIGNAL(clicked()), this, SLOT(onstop()));
//! [1]

//! [2]
    QHBoxLayout *mainLayout = new QHBoxLayout;
//! [2] //! [3]
 //   mainLayout->setMenuBar(menuBar);
//! [3] //! [4]
    mainLayout->addWidget(leftView,70,0);
    mainLayout->addWidget(rightView,30,0);
  //  mainLayout->addWidget(formGroupBox);
  //  mainLayout->addWidget(bigEditor);
//    mainLayout->addWidget(buttonBox);
//! [4] //! [5]
//!
//!
    setLayout(mainLayout);

    setWindowTitle(tr("Basic Layouts"));
}
//! [5]
void Dialog::onstart()
{}
void Dialog::onstop()
{

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
    leftView = new QGroupBox(tr("left_layout"));
    QVBoxLayout *layout = new QVBoxLayout;
    createlefttopView();
    createleftbelowView();
    layout->addWidget(lefttopView);
    layout->addWidget(leftbelowView);
    /*
    for (int i = 0; i < NumButtons; ++i) {
        buttons[i] = new QPushButton(tr("Button %1").arg(i + 1));
	layout->addWidget(buttons[i]);
    }
    */
    leftView->setLayout(layout);
}
void Dialog::createlefttopView()
{
    QVBoxLayout
         *layout=new QVBoxLayout;
    layout->addWidget(new QLabel("加油次数："));
    layout->addWidget(new QWidget);
    lefttopView=new QGroupBox(tr("left top"));
    lefttopView->setLayout(layout);//w=new QGroupBox(tr("left top view"));

}
void Dialog::createleftbelowView()
{
    leftbelowView=new QGroupBox(tr("left right view"));
}
//! [7]

//! [8]
void Dialog::createrightView()
{
    rightView = new QGroupBox(tr("right layout"));
//! [8]
//!
    QVBoxLayout *layout = new QVBoxLayout;
//d2_1
    QVBoxLayout *renew_area =new QVBoxLayout();

    QHBoxLayout *first_line =new QHBoxLayout();
    first_line->addWidget(new QLabel("油满时候可行驶"));
    first_line->addWidget(new QLineEdit("**"));
    first_line->addWidget(new QLabel("公里"));

    QHBoxLayout *second_line=new QHBoxLayout();
    second_line->addWidget(new QLabel("沿途有"));
    second_line->addWidget(new QLineEdit("**"));
    second_line->addWidget(new QLabel("加油站"));

    int col=2 ,row=7;
  /*  QGridLayout * grid=new QGridLayout;
    grid->setHorizontalSpacing(col);
    grid->setVerticalSpacing(row);
*/
    renew_area->addLayout(first_line);
    renew_area->addLayout(second_line);
    renew_area->addWidget(new QTableWidget(row,col,0));
//end d2_1

//d2_2
    QHBoxLayout *but_area=new QHBoxLayout;

    but_area->addWidget(but_start);
    but_area->addWidget(but_stop);
  //end d2_2
    layout->addLayout(renew_area);
    layout->addLayout(but_area);
//! [9]
/*    for (int i = 0; i < NumGridRows; ++i) {
        labels[i] = new QLabel(tr("Line %1:").arg(i + 1));
        lineEdits[i] = new QLineEdit;
        layout->addWidget(labels[i], i + 1, 0);
        layout->addWidget(lineEdits[i], i + 1, 1);
    }

//! [9] //! [10]
    smallEditor = new QTextEdit;
    smallEditor->setPlainText(tr("This widget takes up about two thirds of the "
                                 "grid layout."));
    layout->addWidget(smallEditor, 0, 2, 4, 1);
//! [10]

//! [11]
    layout->setColumnStretch(1, 10);
    layout->setColumnStretch(2, 20);
    */
    rightView->setLayout(layout);
}

//! [11]

//! [12]
/*
void Dialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Form layout"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Line 1:")), new QLineEdit);
    layout->addRow(new QLabel(tr("Line 2, long text:")), new QComboBox);
    layout->addRow(new QLabel(tr("Line 3:")), new QSpinBox);
    formGroupBox->setLayout(layout);
}
*/
//! [12]
