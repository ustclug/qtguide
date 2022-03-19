#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //初始化控件
    InitControls();
}

Widget::~Widget()
{
    delete ui;
}
//初始化控件
void Widget::InitControls()
{
    //默认使用 IP 192.168.1.1
    m_strIP = tr("192.168.1.1");
    ui->radioButtonIP1->setChecked(true);
    //默认使用端口 80
    m_nPort = 80;
    ui->radioButtonPort1->setChecked(true);

    //显示分组框标题的复选框，默认启用IP分组框、Port分组框
    ui->groupBoxIP->setCheckable( true );
    ui->groupBoxPort->setCheckable( true );
    //显示连接操作分组框的复选框
    ui->groupBoxConnection->setCheckable( true );
    //禁用连接操作分组框
    ui->groupBoxConnection->setChecked( false );
}

//三个IP单选框，设置IP地址，分组框内部的单选按钮自动成为一个分组，分组内的单选按钮互斥
void Widget::on_radioButtonIP1_clicked()
{
    m_strIP = tr("192.168.1.1");
}

void Widget::on_radioButtonIP2_clicked()
{
    m_strIP = tr("192.168.1.2");
}

void Widget::on_radioButtonIP3_clicked()
{
    m_strIP = tr("192.168.1.3");
}
//三个Port单选框，设置端口，分组框内部的单选按钮自动成为一个分组，分组内的单选按钮互斥
void Widget::on_radioButtonPort1_clicked()
{
    m_nPort = 80;
}

void Widget::on_radioButtonPort2_clicked()
{
    m_nPort = 443;
}

void Widget::on_radioButtonPort3_clicked()
{
    m_nPort = 8080;
}

//模拟新建一个连接
void Widget::on_pushButtonConnect_clicked()
{
    QString strInfo = tr("新建连接成功：\r\nIP：%1\r\nPort：%2").arg(m_strIP).arg(m_nPort);
    QMessageBox::information(this, tr("新建连接"), strInfo);

    //禁用IP和端口分组框
    ui->groupBoxIP->setChecked( false );
    ui->groupBoxPort->setChecked( false );
    //禁用新建连接按钮
    ui->pushButtonConnect->setEnabled( false );

    //启用连接操作分组框
    ui->groupBoxConnection->setChecked( true );
}
//模拟发送数据，弹出信息框显示
void Widget::on_pushButtonSend_clicked()
{
    QMessageBox::information(this, tr("发送数据"), tr("已发送数据。"));
}
//模拟接收数据，弹出信息框提示
void Widget::on_pushButtonRecv_clicked()
{
    QMessageBox::information(this, tr("接收数据"), tr("已接收数据。"));
}
//关闭连接的操作模拟
void Widget::on_pushButtonClose_clicked()
{
    //显示
    QMessageBox::information(this, tr("关闭连接"), tr("已关闭连接。"));
    //启用IP和Port分组框
    ui->groupBoxIP->setChecked( true );
    ui->groupBoxPort->setChecked( true );
    //启用新建连接按钮
    ui->pushButtonConnect->setEnabled( true );

    //禁用连接操作分组框
    ui->groupBoxConnection->setChecked( false );
}
/*
//设置新建连接按钮启用，或禁用
void Widget::setConButtonEnabled(bool bEnable)
{
    //以 bEnable 为 true 启用时为例，如果是禁用那么参数设置为 false 即可
    //启用IP和Port分组框
    ui->groupBoxIP->setChecked( bEnable );
    ui->groupBoxPort->setChecked( bEnable );
    //启用新建连接按钮
    ui->pushButtonConnect->setEnabled( bEnable );

    //禁用连接操作分组框
    ui->groupBoxConnection->setChecked( ! bEnable );
}
*/
