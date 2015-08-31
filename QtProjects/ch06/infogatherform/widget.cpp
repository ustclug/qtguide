#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>  //消息框
#include <QDateTime>    //日期时间类，可以获取当前时间

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置职业组合框可编辑
    ui->comboBoxJob->setEditable(true);

    //设置日期编辑器在编辑时自动弹出日历
    ui->dateEdit->setCalendarPopup(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_comboBoxGender_currentIndexChanged(int index)
{
    if(index < 0)   //index 可能 -1，表示用户没有选，或者条目全被删除了
    {
        return; //直接返回
    }
    //打印信息
    qDebug()<<"性别："<<ui->comboBoxGender->itemText(index);
}

void Widget::on_comboBoxJob_currentTextChanged(const QString &arg1)
{
    //不是基于序号的，直接得到了新的文本
    qDebug()<<"职业"<<arg1;
}

void Widget::on_dateEdit_dateChanged(const QDate &date)
{
    qDebug()<<date.toString("yyyy-MM-dd");  //参数是日期字符串格式
    //yyyy 是四位数年份，MM 是两位数月份，dd 是两位数日子，比如 "2000-01-01"
}

void Widget::on_pushButtonCommit_clicked()
{
    QString strResult;  //结果字符串
    //获取姓名
    strResult += tr("姓名：%1\r\n").arg( ui->lineEditName->text() );
    //性别
    strResult += tr("性别：%1\r\n").arg( ui->comboBoxGender->currentText() );
    //职业
    strResult += tr("职业：%1\r\n").arg( ui->comboBoxJob->currentText() );
    //生日
    strResult += tr("生日：%1\r\n").arg( ui->dateEdit->date().toString() );
    //QDate::toString() 如果不带参数格式，自动按照本地化语言的日期格式返回字符串

    //额外功能，根据当前时间和用户生日，计算用户当前岁数
    QDateTime dtCur = QDateTime::currentDateTime();
    //计算岁数
    int nYears = dtCur.date().year() - ui->dateEdit->date().year();
    strResult += tr("岁数：%1").arg(nYears);

    //显示消息框
    QMessageBox::information(this, tr("信息"), strResult);
}
