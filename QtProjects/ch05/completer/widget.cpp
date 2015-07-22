#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QCompleter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //星期单词列表
    QStringList listDayOfWeek;
    listDayOfWeek<<"Monday"<<"Tuesday"<<"Wednesday"
                <<"Thursday"<<"Friday"<<"Saturday"<<"Sunday";
    //构建补全器
    QCompleter *cpDayOfWeek = new QCompleter(listDayOfWeek);
    //大小写不敏感
    cpDayOfWeek->setCaseSensitivity(Qt::CaseInsensitive);
    //设置给 lineEditDayOfWeek
    ui->lineEditDayOfWeek->setCompleter(cpDayOfWeek);

    //年份列表
    QStringList listYear;
    listYear<<"2016"<<"2015"
            <<"2008"<<"2006"
            <<"1999"<<"1991";
    //重新排序，默认是大小写敏感排序，对数字字符没影响
    listYear.sort();
    //构建补全器
    QCompleter *cpYear = new QCompleter(listYear);
    //设置给 lineEditYear
    ui->lineEditYear->setCompleter(cpYear);

    //何夕名字列表
    QStringList listHeXi;
    listHeXi<<"何百夕"<<"何千夕"<<"何万夕"<<"何亿夕";
    //中文没有大小写敏感，也不要排序
    //构建补全器
    QCompleter *cpHexi = new QCompleter(listHeXi);
    //设置给 lineEditHeXi
    ui->lineEditHeXi->setCompleter(cpHexi);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_lineEditDayOfWeek_textChanged(const QString &arg1)
{
    qDebug()<<"DayOfWeek: "<<arg1;
}

void Widget::on_lineEditYear_textChanged(const QString &arg1)
{
    qDebug()<<"Year: "<<arg1;
}

void Widget::on_lineEditHeXi_textChanged(const QString &arg1)
{
    qDebug()<<"何夕："<<arg1;
}
