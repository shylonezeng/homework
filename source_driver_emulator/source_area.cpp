#include "source_area.h"
#include <iostream>
#include <fstream>
using namespace std;

source_area::source_area()
{
    //read failed
    read_from_file();
    //init property members
    ledit_maxdis=new QLineEdit("4");
    ledit_stnum=new QLineEdit("6") ;
    int col=2 ,row=7;
    table=new QTableWidget(row,col,0);
    table->setItem(1,1,new QTableWidgetItem("debuging"));
    table->setHorizontalHeaderItem(0,new QTableWidgetItem("区间"));
    table->setHorizontalHeaderItem(1,new QTableWidgetItem("距离"));
    this->on_stnm_input("6");
    //d2_1
    // QVBoxLayout *renew_area =new QVBoxLayout();

    QHBoxLayout *first_line =new QHBoxLayout();
    first_line->addWidget(new QLabel("油满时候可行驶"));
    first_line->addWidget(ledit_maxdis);
    first_line->addWidget(new QLabel("公里"));

    QHBoxLayout *second_line=new QHBoxLayout();
    second_line->addWidget(new QLabel("沿途有"));
    second_line->addWidget(ledit_stnum);
    second_line->addWidget(new QLabel("加油站"));


    /*  QGridLayout * grid=new QGridLayout;
    grid->setHorizontalSpacing(col);
    grid->setVerticalSpacing(row);
    */
    this->addLayout(first_line);
    this->addLayout(second_line);
    this->addWidget(table);
    //end d2_1

    //bind signal and slots
    connect(ledit_stnum,SIGNAL(textChanged(const QString)),this,SLOT(on_stnm_input(const QString)));
    connect(ledit_maxdis,SIGNAL(textChanged(const QString)),this,SLOT(digit_ensure(const QString)));
}

source_area::~source_area()
{
    //delete allocated resouces
}

bool getItem(QTableWidgetItem **pp_item,char* buff)
{
    *pp_item=new QTableWidgetItem(QString(buff));
    (*pp_item)->setTextAlignment(Qt::AlignCenter);
}
//get digit number from qlineEdit
int source_area::text_from_edit(QLineEdit &ledit)
{
    bool ok=true;
    int ret=ledit.text().toInt(&ok);
    if(!ok)
    {
        ledit.setFocus();
        return -1;
    }
    return ret;
}
bool source_area::digit_ensure(const QString &str)
{
    if( text_from_edit(*ledit_maxdis)<0)
        return false;
    return true;

}
//return algorithm input data
void source_area::on_stnm_input(const QString & stnum) //do not use stunum argument
{
    //qDebug()<<stnum<<endl;
    /* bool ok=true;
    int row=stnum.toInt(&ok)+1;
    if(!ok)
    return;
    */
    int row=text_from_edit(*ledit_stnum)+1;
    if(row<0)
        return;

    table->setRowCount(row);
    if(row>31)
    {
        ledit_stnum->setText("num should be less than 32");
        return;
    }
    QTableWidgetItem *item;
    getItem(&item,"start point -> destination");
    //set first col content
    if(row==1)
    {
        table->setItem(0,0,item);
    }


    getItem(&item, "start_point->station 1");
    table->setItem(0,0,item);

    int i;

    char buff[BUFF_LEN];
    for( i=1;i<row-1;++i)
    {
        sprintf(buff,"station %d -> station %d",i,i+1);
        getItem(&item,buff);
        table->setItem(i,0,item);

    }
    sprintf(buff,"station %d -> destination",i);
     //the last row
    getItem(&item,buff);
    table->setItem(i,0,item);


    for(int i=0;i<row;++i)
    {
        sprintf(buff,"%d",st_dis[i]);
        getItem(&item,buff);
        table->setItem(i,1,item);

    }

}
bool source_area::get_input(int *st_dis,int *st_num,int *maxdis)
{
    *maxdis=ledit_maxdis->text().toInt();
    *st_num=ledit_stnum->text().toInt();
    for(int i=0;i<=*st_num;++i)
    {
        bool ok;
        QString str=(table->item(i,1))->text();
        qDebug()<<"getdata:"<<str;
        int ret=str.toInt(&ok);
        if(!ok)
           return false;
        st_dis[i]=ret;
    }
    return true;
}


bool    source_area::read_from_file()
{
    int temp[MAX_SIZE]={2,2,3,4,3,1,3,3,
2,1,3,4,2,3,1,2,
4,3,2,3,2,4,1,4,
12,2,23,2,23,21,23,2
};
    copy(temp,temp+sizeof(temp)/sizeof(int),st_dis);
#ifndef _data_in
#define _data_in
    ifstream cin(":/data_in");
#endif
    int item=0;
    while(cin>>st_dis[item++]);
#include <algorithm>
    qDebug()<<"item:"<<item;
    copy(st_dis,st_dis+item,std::ostream_iterator<int>(cout,","));
    if(item==1)
        return false;
    return true;

}
