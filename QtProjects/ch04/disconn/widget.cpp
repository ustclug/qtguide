#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //进行关联，按钮的槽函数可以当作普通函数来调用，实现关联
    on_pushButtonConn_clicked();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonConn_clicked()
{
    //关联
    connect(ui->lineEdit, SIGNAL(textEdited(QString)), ui->label, SLOT(setText(QString)));

    //调整按钮可用性
    ui->pushButtonConn->setEnabled(false);      //已经关联，禁用关联按钮
    ui->pushButtonDisconn->setEnabled(true);    //已经关联，只有解除关联按钮可用
}

void Widget::on_pushButtonDisconn_clicked()
{
    //解除关联
    disconnect(ui->lineEdit, SIGNAL(textEdited(QString)), ui->label, SLOT(setText(QString)));

    //调整按钮可用性
    ui->pushButtonConn->setEnabled(true);       //没有关联，只有关联按钮可用
    ui->pushButtonDisconn->setEnabled(false);   //没有关联，解除关联按钮禁用
}
