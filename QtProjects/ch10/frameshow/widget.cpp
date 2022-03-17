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
    //单选框默认选择 Null
    ui->radioButtonNull->setChecked( true );
    // Line Width 旋钮框
    ui->spinBoxLineWidth->setRange( 0, 27 );
    ui->spinBoxLineWidth->setValue( 1 );
    // Mid Line Width旋钮框
    ui->spinBoxMidLineWidth->setRange( 0, 27 );
    ui->spinBoxMidLineWidth->setValue( 0 );
    //Frame Shape 列表
    m_listFrameShape<<QFrame::NoFrame<<QFrame::Box
        <<QFrame::Panel<<QFrame::WinPanel
        <<QFrame::HLine<<QFrame::VLine
        <<QFrame::StyledPanel;
    //Frame Shape组合框条目
    ui->comboBoxFrameShape->addItem( "NoFrame" );
    ui->comboBoxFrameShape->addItem( "Box" );
    ui->comboBoxFrameShape->addItem( "Panel" );
    ui->comboBoxFrameShape->addItem( "WinPanel" );
    ui->comboBoxFrameShape->addItem( "HLine" );
    ui->comboBoxFrameShape->addItem( "VLine" );
    ui->comboBoxFrameShape->addItem( "StyledPanel" );
    //默认是 StyledPanel
    ui->comboBoxFrameShape->setCurrentIndex( 6 );
    //Frame Shadow列表
    m_listFrameShadow<<QFrame::Plain
        <<QFrame::Raised<<QFrame::Sunken;
    //Frame Shadow组合框条目
    ui->comboBoxFrameShadow->addItem( "Plain" );
    ui->comboBoxFrameShadow->addItem( "Raised" );
    ui->comboBoxFrameShadow->addItem( "Sunken" );
    //默认 Raised
    ui->comboBoxFrameShadow->setCurrentIndex( 1 );
}
//无背景色
void Widget::on_radioButtonNull_clicked()
{
    ui->frameTest->setStyleSheet("");
}
//红色背景
void Widget::on_radioButtonRed_clicked()
{
    ui->frameTest->setStyleSheet("background-color: rgb(255, 0, 0);");
}
//蓝色背景
void Widget::on_radioButtonBlue_clicked()
{
    ui->frameTest->setStyleSheet("background-color: rgb(0, 0, 255);");
}
//绿色背景
void Widget::on_radioButtonGreen_clicked()
{
    ui->frameTest->setStyleSheet("background-color: rgb(0, 255, 0);");
}
//设置 LineWidth
void Widget::on_spinBoxLineWidth_valueChanged(int arg1)
{
    ui->frameTest->setLineWidth( arg1 );
}
//设置 MidLineWidth
void Widget::on_spinBoxMidLineWidth_valueChanged(int arg1)
{
    ui->frameTest->setMidLineWidth( arg1 );
}
//设置 FrameShape
void Widget::on_comboBoxFrameShape_currentIndexChanged(int index)
{
    if( index < 0 ) return;
    //设置 Shape
    ui->frameTest->setFrameShape( m_listFrameShape[index] );
}
//设置 FrameShadow
void Widget::on_comboBoxFrameShadow_currentIndexChanged(int index)
{
    if( index < 0 ) return;
    //设置 Shadow
    ui->frameTest->setFrameShadow( m_listFrameShadow[index] );
}
