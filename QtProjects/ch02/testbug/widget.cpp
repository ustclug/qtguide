#include "widget.h"
#include "ui_widget.h"
#include <QtTest/QTest> //added new line
#include <QDebug>       //added

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    //qDebug()<<(void *)(ui->label);      //show the "wild" pointer
    //ui->label->setText(tr("Test Bug")); //change text

    ui->setupUi(this);
    qsleep(1000);       //added new line

    //qDebug()<<(void *)(ui->label);    //show normal pointer
    //qDebug()<<ui->label;              //show label object
}

Widget::~Widget()
{
    delete ui;
}
