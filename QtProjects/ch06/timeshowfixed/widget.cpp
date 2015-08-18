#include "widget.h"
#include "ui_widget.h"
#include <QDateTime>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);    
    //窗体标题改为电子钟
    this->setWindowTitle(tr("电子钟"));

    //新建定时器对象
    m_timer = new QTimer(this);
    //设置定时器循环触发
    m_timer->setSingleShot(false);  //非单次触发
    //设置定时器触发时间间隔，单位毫秒
    m_timer->setInterval( 1*1000 );

    //关联定时器信号到槽函数
    connect(m_timer, SIGNAL(timeout()), this, SLOT(RecvTimer()));

    //启动定时器
    m_timer->start();

    //调用一次 "回到今天" 槽函数，初始化日历
    on_pushButtonToday_clicked();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::RecvTimer()
{
    //获取当前时间
    QDateTime dt = QDateTime::currentDateTime();

    //构造时间字符串
    QString strTime = dt.time().toString("HH:mm:ss");
    //设置 LCD 时钟
    ui->lcdNumber->display(strTime);

    //设置进度条的显示： 秒数%10
    ui->progressBar->setValue( dt.time().second() % 10 );
}

void Widget::on_pushButtonToday_clicked()
{
    //获取当前时间
    QDateTime dt = QDateTime::currentDateTime();
    //设置日历为今天
    ui->calendarWidget->setSelectedDate( dt.date() );
    //点击按钮时，输入焦点在按钮上，这时候日历选中的日子是灰色，容易看不清
    //将输入焦点回到日历控件，这样日历选中日子会重新变成高亮蓝色
    ui->calendarWidget->setFocus();
}

/*
#include <QDebug>

    qDebug()<<dt.time().toString("hh:mm:ss ap");
    qDebug()<<dt.date().toString("yyyy-MM-dd dddd");

*/
