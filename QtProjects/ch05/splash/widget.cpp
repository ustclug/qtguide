#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>  //消息框


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonAbout_clicked()
{
    QMessageBox::about(this, tr("关于本程序"),
                       tr("闪屏程序，版本 1.0，\r\n使用外挂资源 splash.rcc。"));
}

void Widget::on_pushButtonAboutQt_clicked()
{
    QMessageBox::aboutQt(this, tr("关于 Qt"));
}
