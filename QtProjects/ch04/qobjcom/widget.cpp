#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //关联
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(ButtonClicked()));
}

Widget::~Widget()
{
    delete ui;
}
//槽函数
void Widget::ButtonClicked()
{
    //用 emit 发信号
    emit SendMsg( tr("This is the message!") );
}
