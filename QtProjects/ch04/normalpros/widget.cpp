#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

//读函数定义
//读nickName数值
const QString& Widget::nickName()
{
    return m_nickName;
}
//读count数值
int Widget::count()
{
    return m_count;
}

//写函数，在数值发生变化是才发信号
void Widget::setNickName(const QString &strNewName)
{
    if(strNewName == m_nickName)
    {
        //数值没变化，直接返回
        return;
    }
    //修改数值并触发信号
    m_nickName = strNewName;
    emit nickNameChanged(strNewName);
}

void Widget::setCount(int nNewCount)
{
    if(nNewCount == m_count)
    {
        //数值没变化，直接返回
        return;
    }
    //修改数值并触发信号
    m_count = nNewCount;
    emit countChanged(nNewCount);
}
