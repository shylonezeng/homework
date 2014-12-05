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

#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
#include "source_area.h"
#include "disview.h"
#include <pthread.h>
#include <unistd.h>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
QT_END_NAMESPACE

//extern int if_add;
//! [0]
class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog();

private:
    void createMenu();
    void createleftView();
    void createrightView();
    void createFormGroupBox();

    void createlefttopView();
    void createleftbelowView();
    enum { NumGridRows = 3, NumButtons = 4 };




    QTextEdit *smallEditor;
    QTextEdit *bigEditor;
    QLabel *labels[NumGridRows];
    QLineEdit *lineEdits[NumGridRows];
    QPushButton *buttons[NumButtons];
    QDialogButtonBox *buttonBox;

    QMenu *fileMenu;
    QAction *exitAction;
//my  property
private:
    //ui compoment
    QMenuBar *menuBar;
    QGroupBox *leftView;
    QGroupBox *rightView;
   source_area *input_area;
    DisView *left_disview;
 QPushButton *but_stop;
 QPushButton *but_start;
    //
    bool end_thread;
    pthread_t pthread;
    //algorithm core
    bool if_renew;
    int stime;
    int   st_dis[MAX_SIZE];
    int max_dis_full;
    int st_num;
public:
   // int gas_num; //time of fixing full of gas
signals:
    void signal_update(int value,int gas_add);
public slots:
    void update_view(int value,int gas_add);
    void onstart();
    void onstop();
public:
    void initValue();
    void *travel();
    bool readValue();
    static void* call_travel(void *arg);
};
//! [0]

#endif // DIALOG_H
