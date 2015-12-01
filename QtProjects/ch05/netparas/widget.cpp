#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QIntValidator>
#include <QRegExp>
#include <QRegExpValidator>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置 MAC 输入模板
    ui->lineEditMAC->setInputMask("HH:HH:HH:HH:HH:HH");

    //定义 IPv4 正则表达式，注意 "\\" 就是一个反斜杠字符
    QRegExp re("^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}"
               "(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    //新建正则表达式验证器
    QRegExpValidator *reVali = new QRegExpValidator(re);
    //设置给 lineEditIP
    ui->lineEditIP->setValidator(reVali);

    //新建整数验证器
    QIntValidator *intVali = new QIntValidator(0, 65535);
    //设置给 lineEditPort
    ui->lineEditPort->setValidator(intVali);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_lineEditMAC_textChanged(const QString &arg1)
{
    qDebug()<<"MAC: "<<arg1;
}

void Widget::on_lineEditIP_textChanged(const QString &arg1)
{
    qDebug()<<"IP: "<<arg1;
}

void Widget::on_lineEditPort_textChanged(const QString &arg1)
{
    qDebug()<<"Port: "<<arg1;
}
