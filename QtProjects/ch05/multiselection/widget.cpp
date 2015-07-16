#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置三态工作模式
    ui->checkBoxTristate->setTristate(true);

}

Widget::~Widget()
{
    delete ui;
}

//检查 6 个兴趣爱好复选框，根据兴趣复选框状态，更新三态复选框显示
void Widget::CheckHobbies()
{
    int count = 0;  //兴趣计数
    if( ui->checkBoxRead->isChecked() )
    {
        count++;
    }
    if( ui->checkBoxClimb->isChecked() )
    {
        count++;
    }
    if( ui->checkBoxSwim->isChecked() )
    {
        count++;
    }
    if( ui->checkBoxDaze->isChecked() )
    {
        count++;
    }
    if( ui->checkBoxShopping->isChecked() )
    {
        count++;
    }
    if( ui->checkBoxEat->isChecked() )
    {
        count++;
    }
    //根据兴趣计数设置三态按钮的状态
    if( count <= 0)
    {
        ui->checkBoxTristate->setCheckState(Qt::Unchecked);
        return;
    }
    else if( count <= 5 )
    {
        ui->checkBoxTristate->setCheckState(Qt::PartiallyChecked);
        return;
    }
    else
    {
        ui->checkBoxTristate->setCheckState(Qt::Checked);
        return;
    }
}

void Widget::on_checkBoxRead_toggled(bool checked)
{
    if(checked)
    {
        qDebug()<<tr("读书");
    }
    CheckHobbies(); //更新三态复选框
}

void Widget::on_checkBoxClimb_toggled(bool checked)
{
    if(checked)
    {
        qDebug()<<tr("爬山");
    }
    CheckHobbies(); //更新三态复选框
}

void Widget::on_checkBoxSwim_toggled(bool checked)
{
    if(checked)
    {
        qDebug()<<tr("游泳");
    }
    CheckHobbies(); //更新三态复选框
}

void Widget::on_checkBoxDaze_toggled(bool checked)
{
    if(checked)
    {
        qDebug()<<tr("发呆");
    }
    CheckHobbies(); //更新三态复选框
}

void Widget::on_checkBoxShopping_toggled(bool checked)
{
    if(checked)
    {
        qDebug()<<tr("逛街");
    }
    CheckHobbies(); //更新三态复选框
}

void Widget::on_checkBoxEat_toggled(bool checked)
{
    if(checked)
    {
        qDebug()<<tr("吃货");
    }
    CheckHobbies(); //更新三态复选框
}

//弹窗显示选中的兴趣爱好
void Widget::on_pushButton_clicked()
{
    QString strResult = tr("兴趣爱好为：\r\n");
    if( ui->checkBoxRead->isChecked() )
    {
        strResult += tr("读书\r\n");
    }
    if( ui->checkBoxClimb->isChecked() )
    {
        strResult += tr("爬山\r\n");
    }
    if( ui->checkBoxSwim->isChecked() )
    {
        strResult += tr("游泳\r\n");
    }
    if( ui->checkBoxDaze->isChecked() )
    {
        strResult += tr("发呆\r\n");
    }
    if( ui->checkBoxShopping->isChecked() )
    {
        strResult += tr("逛街\r\n");
    }
    if( ui->checkBoxEat->isChecked() )
    {
        strResult += tr("吃货\r\n");
    }
    //弹窗显示
    QMessageBox::information(this, tr("兴趣爱好"), strResult);
}

void Widget::on_commandLinkButtonFolder_clicked()
{
    QDesktopServices::openUrl( QUrl("file:///D:/QtProjects") );
}

void Widget::on_commandLinkButtonWeb_clicked()
{
    QDesktopServices::openUrl( QUrl("https://lug.ustc.edu.cn/sites/qtguide/") );
}
