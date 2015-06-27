#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //关联按钮信号到自定义的信号
    connect(ui->pushButton, SIGNAL(clicked()), this, SIGNAL(SendVoid()));
}

Widget::~Widget()
{
    delete ui;
}
