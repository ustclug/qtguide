#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //三个按钮的信号都关联到 FoodIsComing 槽函数
    connect(ui->pushButtonAnderson, SIGNAL(clicked()), this, SLOT(FoodIsComing()));
    connect(ui->pushButtonBruce, SIGNAL(clicked()), this, SLOT(FoodIsComing()));
    connect(ui->pushButtonCastiel, SIGNAL(clicked()), this, SLOT(FoodIsComing()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::FoodIsComing()
{
    //获取信号源头对象的名称
    QString strObjectSrc = this->sender()->objectName();
    qDebug()<<strObjectSrc; //打印源头对象名称

    //将要显示的消息
    QString strMsg;
    //判断是哪个按钮发的信号
    if( "pushButtonAnderson" == strObjectSrc )
    {
        strMsg = tr("Hello Anderson! Your food is coming!");
    }
    else if( "pushButtonBruce" == strObjectSrc )
    {
        strMsg = tr("Hello Bruce! Your food is coming!");
    }
    else if( "pushButtonCastiel" == strObjectSrc )
    {
        strMsg = tr("Hello Castiel! Your food is coming!");
    }
    else
    {
        //do nothing
        return;
    }
    //显示送餐消息
    QMessageBox::information(this, tr("Food"), strMsg);
}
