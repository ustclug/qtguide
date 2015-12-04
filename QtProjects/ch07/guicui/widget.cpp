#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QTextStream>

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

void Widget::on_pushButtonIn_clicked()
{
    //输入和输出流
    QTextStream tsIn(stdin);
    QTextStream tsOut(stdout);
    //在命令行提示用户输入一行字符串
    QString strOut = tr("请输入一行字符串：");
    tsOut<<strOut<<endl;
    //接收输入
    QString strMsg = tsIn.readLine();
    //显示到单行编辑器
    ui->lineEditMsg->setText( strMsg );
}

void Widget::on_pushButtonOut_clicked()
{
    //只需要输出流
    QTextStream tsOut(stdout);
    //打印一行字符串
    QString strMsg = ui->lineEditMsg->text();
    tsOut<<endl<<tr("输出信息：")<<strMsg<<endl;

    //打印调试信息，也会自动显示到命令行
    qDebug()<<endl<<tr("这行是调试信息。")<<endl;
}



