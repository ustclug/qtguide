#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>

//假定管理的内存块数为10
#define MEM_MAX  10

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置SpinBox上下限，至少分配1块，最多10块内存
    ui->spinBoxMemCount->setRange(1, MEM_MAX);
    //初始化空闲内存链表
    for(int i=0; i<MEM_MAX; i++)
    {
        m_memFree.append( tr("空闲内存") );
    }
    //更新列表控件的显示
    updateListWidgets();
}

Widget::~Widget()
{
    delete ui;
}

//同步更新图形界面的列表控件
void Widget::updateListWidgets()
{
    //清空列表控件
    ui->listWidgetFree->clear();
    ui->listWidgetUsed->clear();
    //根据空闲内存块链表显示
    QLinkedList<QString>::iterator itFree = m_memFree.begin();
    while( itFree != m_memFree.end() )
    {
        ui->listWidgetFree->addItem( *itFree );
        itFree++; //下一个
    }
    //根据已使用内存块链表显示
    QLinkedList<QString>::iterator itUsed = m_memUsed.begin();
    while( itUsed != m_memUsed.end() )
    {
        ui->listWidgetUsed->addItem( *itUsed );
        itUsed++; //下一个
    }
}

//分配内存块
void Widget::on_pushButtonAllocate_clicked()
{
    //获取进程名
    const QString strName = ui->lineEditProcessName->text().trimmed();
    if(strName.isEmpty())
    {
        QMessageBox::warning(this, tr("分配"), tr("进程名为空，无法分配。"));
        return;
    }
    //进程名不能等同 tr("空闲内存")
    if( tr("空闲内存") == strName )
    {
        QMessageBox::warning(this, tr("分配"), tr("进程名不能等同 空闲内存 。"));
        return;
    }
    //判断需要分配的数量
    int nNeededCount = ui->spinBoxMemCount->value();
    //现有的空闲块数量
    int nCurFree = m_memFree.count();
    //判断是否够用
    if( nNeededCount > nCurFree )//超额了
    {
        QMessageBox::warning(this, tr("分配"), tr("请求数量大于现有空闲数量，请减少请求量或释放其他进程内存。"));
        return;
    }
    //数量充足，可以分配
    for(int i=0; i<nNeededCount; i++)
    {
        QString strCurMem = m_memFree.takeFirst(); //从头部取下内存块，逐一分配
        //分配给进程
        strCurMem = strName;
        //添加到已分配链表
        m_memUsed.append( strCurMem );
    }
    //更新列表控件
    updateListWidgets();
}

//根据进程名查询该进程拥有的内存块数量
void Widget::on_pushButtonFind_clicked()
{
    //获取进程名
    const QString strName = ui->lineEditProcessName->text().trimmed();
    //判断是否为空
    if( strName.isEmpty() )
    {
        QMessageBox::warning(this, tr("查询"), tr("进程名为空，无法查询。"));
        return;
    }
    //判断是否为 空闲内存查询
    if( tr("空闲内存") == strName )
    {
        QMessageBox::information(this, tr("查询"),
                                 tr("空闲内存数量为：%1").arg( m_memFree.count() ) );
        return;
    }
    //查询进程名拥有的内存块数量
    int nMemCount = m_memUsed.count( strName );
    if( nMemCount < 1 )//判断是否存在
    {
        QMessageBox::warning(this, tr("查询"), tr("没有找到该进程名。"));
        return;
    }
    else
    {
        //显示数量
        QMessageBox::information(this, tr("查询"),
                                 tr("该进程拥有的内存块数量为：%1").arg(nMemCount) );
    }
}

//释放指定进程、指定数量的内存块
void Widget::on_pushButtonFree_clicked()
{
    //获取进程名
    const QString strName = ui->lineEditProcessName->text().trimmed();
    //判断是否为空
    if( strName.isEmpty() )
    {
        QMessageBox::warning(this, tr("释放"), tr("进程名为空，无法释放。"));
        return;
    }
    //获取需要释放的数量
    int nNeedFree = ui->spinBoxMemCount->value();
    //获取该进程拥有的数量
    int nCurOwn = m_memUsed.count( strName );
    if( nCurOwn < 1 )//判断是否存在
    {
        QMessageBox::warning(this, tr("释放"),tr("没有找到该进程名。"));
        return;
    }
    //判断释放数量是否超过了拥有数量
    if( nNeedFree > nCurOwn )
    {
        QMessageBox::warning(this, tr("释放"),
                             tr("该进程只拥有 %1 块内存，不能释放 %2 块。").arg(nCurOwn).arg(nNeedFree) );
        return;
    }
    //正常释放内存
    //记录已释放数目
    int nCurFreed = 0;
    //获取迭代器
    QLinkedList<QString>::iterator itUsed = m_memUsed.begin();
    //循环查找该进程内存块并释放
    while( itUsed != m_memUsed.end() )
    {
        //判断当前元素是否为该进程名
        if( strName == (*itUsed) )
        {
            //释放 1 块内存
            QString strMem = (*itUsed); //链表及其迭代器没有 takeAt 函数，只能复制后删除中间元素
            itUsed = m_memUsed.erase( itUsed ); //删除中间元素
            //erase() 返回值就是指向下一个，不需要++，并且不能再用erase()参数里的数值迭代
            //设置空闲内存名字，添加到空闲内存块链表
            strMem = tr("空闲内存");
            m_memFree.append( strMem );
            //释放数量 +1
            nCurFreed += 1;
            //判断数量是否够了
            if( nCurFreed >= nNeedFree ) break; //停止循环
        }
        else
        {
            itUsed++;   //进程名不对，查找下一个
        }
    }
    //释放完毕，更新列表控件
    updateListWidgets();
}
