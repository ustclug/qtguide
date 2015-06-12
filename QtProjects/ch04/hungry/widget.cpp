#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //添加关联代码，必须放在 setupUi 函数之后
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(FoodIsComing()));
    //connect(ui->pushButton, &QPushButton::clicked, this, &Widget::FoodIsComing);
}

Widget::~Widget()
{
    delete ui;
}

//槽函数定义代码，与普通成员函数类似
void Widget::FoodIsComing()
{
    QMessageBox::information(this, tr("送餐"), tr("叮咚！外卖已送达"));
}
