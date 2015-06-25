#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //关联信号到槽函数
    //接收端是标签控件
    connect(ui->lineEdit, SIGNAL(textEdited(QString)), ui->label, SLOT(setText(QString)));
    //接收端是文本浏览控件
    connect(ui->lineEdit, SIGNAL(textEdited(QString)), ui->textBrowser, SLOT(setText(QString)));
    //接收端是主窗口的 PrintText 槽
    connect(ui->lineEdit, SIGNAL(textEdited(QString)), this, SLOT(PrintText(QString)));
    //new style
    //connect(ui->lineEdit, &QLineEdit::textEdited, this, &Widget::PrintText);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::PrintText(const QString &text)
{
    qDebug()<<text; //打印到调试输出面板
}
