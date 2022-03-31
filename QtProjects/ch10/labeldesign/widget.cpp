#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDebug>
#include <QFont>
#include <QColor>

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
    //字号旋钮框的范围
    ui->spinBoxSize->setRange(4, 100);
    ui->spinBoxSize->setValue( 9 );
    //颜色组合框的设置
    //获取常见颜色
    QStringList colorNames = QColor::colorNames();
    //设置前景色组合框
    ui->comboBoxFGColor->addItems( colorNames );
    //默认前景色 黑色
    ui->comboBoxFGColor->setCurrentText( "black" );
    //设置背景色组合框
    ui->comboBoxBGColor->addItems( colorNames );
    //默认背景色，浅灰
    ui->comboBoxBGColor->setCurrentText( "lightgray" );

    //修改工具箱本身的样式表
    QString strCSS = "::tab{ background-color: magenta; }"
            "QWidget#pageText{ background-color: green; }"
            "QWidget#pageFont{ background-color: cyan; }"
            "QWidget#pageColor{ background-color: yellow; }";
    ui->toolBox->setStyleSheet( strCSS );
}

//修改左边标签控件的文本
void Widget::on_pushButtonEditText_clicked()
{
    QString strText = ui->lineEditText->text();
    ui->labelShow->setText( strText );
}

//字体设置
void Widget::on_fontComboBox_currentIndexChanged(const QString &arg1)
{
    QFont txtFont( arg1, ui->spinBoxSize->value() );
    ui->labelShow->setFont( txtFont );
}

//字号设置
void Widget::on_spinBoxSize_valueChanged(int arg1)
{
    QFont txtFont( ui->fontComboBox->currentText(), arg1 );
    ui->labelShow->setFont( txtFont );
}

//前景色修改
void Widget::on_comboBoxFGColor_currentIndexChanged(const QString &arg1)
{
    QString strFGColor = arg1; //前景色
    QString strBGColor = ui->comboBoxBGColor->currentText(); //背景色
    //样式表
    QString strCSS = QString("color: %1; background-color: %2;").arg( strFGColor ).arg( strBGColor );
    ui->labelShow->setStyleSheet( strCSS );
}
//背景色修改
void Widget::on_comboBoxBGColor_currentIndexChanged(const QString &arg1)
{
    QString strFGColor = ui->comboBoxFGColor->currentText(); //前景色
    QString strBGColor = arg1; //背景色
    //样式表
    QString strCSS = QString("color: %1; background-color: %2;").arg( strFGColor ).arg( strBGColor );
    ui->labelShow->setStyleSheet( strCSS );
}
