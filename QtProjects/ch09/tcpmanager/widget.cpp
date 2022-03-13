#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDebug>
#include <QMapIterator>
#include <QMutableMapIterator>
#include <QTreeWidgetItem>
#include <QRegExp>
#include <QRegExpValidator>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置树形控件只有 1 列
    ui->treeWidget->setColumnCount( 1 );
    ui->treeWidget->header()->setHidden( true ); //隐藏头部，未使用
    //设置 IP编辑框
    //定义 IPv4 正则表达式，注意 "\\" 就是一个反斜杠字符
    QRegExp re("^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}"
               "(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    //新建正则表达式验证器
    QRegExpValidator *reVali = new QRegExpValidator(re);
    //设置给 lineEditIP
    ui->lineEditIP->setValidator(reVali);
    ui->lineEditIP->setText( tr("192.168.1.1") ); //默认值
    //设置端口范围
    ui->spinBoxPort->setRange( 0, 65535 );
    ui->spinBoxPort->setValue( 1500 ); //默认值

    //初始化填充连接信息
    InitTCPLinks();
    //更新树形控件的显示
    UpdateTreeShow();
}

Widget::~Widget()
{
    delete ui;
}

//初始化填充
void Widget::InitTCPLinks()
{
    m_tcplinks.clear(); //清空旧的
    m_tcplinks.insert( tr("192.168.1.1"), 80 );
    m_tcplinks.insert( tr("192.168.1.1"), 443 );
    m_tcplinks.insert( tr("192.168.1.2"), 20 );
    m_tcplinks.insert( tr("192.168.1.2"), 21 );
    m_tcplinks.insert( tr("192.168.1.3"), 80 );
    m_tcplinks.insert( tr("192.168.1.3"), 443 );
    m_tcplinks.insert( tr("192.168.1.3"), 3306 );
}

//更新树形控件的显示
void Widget::UpdateTreeShow()
{
    ui->treeWidget->clear(); //清空旧的
    //定义迭代器
    QMapIterator<QString, int> it( m_tcplinks );
    //保存迭代中旧的IP
    QString strOldIP;
    //保存旧的顶级IP节点
    QTreeWidgetItem *pOldTopItem = NULL;
    //端口号节点
    QTreeWidgetItem *pPortItem = NULL;
    //迭代遍历
    while( it.hasNext() )
    {
        it.next();  //滑过一个元素
        //获取滑过元素的 IP 和端口
        QString strIP = it.key();
        int nPort = it.value();
        //判断
        if( strIP != strOldIP )
        {
            //新的主机IP，建立顶级IP节点
            pOldTopItem = new QTreeWidgetItem();
            pOldTopItem->setText(0, strIP);
            ui->treeWidget->addTopLevelItem( pOldTopItem );
            //添加端口号为子节点
            pPortItem = new QTreeWidgetItem();
            pPortItem->setText( 0, tr("%1").arg(nPort) );
            pOldTopItem->addChild( pPortItem );
            //更新旧的IP
            strOldIP = strIP;
        }
        else
        {
            //现在元素IP 与 上一个元素IP一样
            //添加 pOldTopItem 子节点
            pPortItem = new QTreeWidgetItem();
            pPortItem->setText( 0, tr("%1").arg(nPort) );
            pOldTopItem->addChild( pPortItem );
        }
    }// end while
    //遍历结束，树形控件条目添加完成
    ui->treeWidget->expandAll(); //全部展开
}
//添加一个连接
void Widget::on_pushButtonAddTCP_clicked()
{
    //获取 IP 和端口
    QString strIP = ui->lineEditIP->text().trimmed();
    if( strIP.isEmpty() )
    {
        ui->textBrowser->setText( tr("IP为空。") );
        return; //IP为空
    }
    //端口
    int nPort = ui->spinBoxPort->value();
    //检查是否已存在相同的 IP和端口
    if( m_tcplinks.contains( strIP, nPort ) )
    {
        ui->textBrowser->setText( tr("该IP端口的连接已存在，IP和端口不能同时重复。") );
        return;
    }
    //不重复的连接，添加
    m_tcplinks.insert( strIP, nPort );
    ui->textBrowser->setText( tr("添加TCP连接完成。") );
    //更新树形控件
    UpdateTreeShow();
}
//删除匹配IP的连接
void Widget::on_pushButtonDelIP_clicked()
{
    //获取 IP
    QString strIP = ui->lineEditIP->text().trimmed();
    if( strIP.isEmpty() )
    {
        ui->textBrowser->setText( tr("IP为空。") );
        return; //IP为空
    }
    //删除计数
    int nDelCount = 0;
    //使用迭代器查找
    QMutableMapIterator<QString, int> it( m_tcplinks );
    //循环查找
    while ( it.hasNext() )
    {
        it.next(); //滑过一个元素
        if( it.key() == strIP ) //检查滑过元素的 key
        {
            //删除刚找到的滑过元素
            it.remove();
            nDelCount += 1; //更新删除计数
        }
    }
    //判断
    if( nDelCount < 1 )
    {
        ui->textBrowser->setText( tr("没有匹配的IP。") );
    }
    else
    {
        ui->textBrowser->setText( tr("已删除匹配IP的连接个数：%1 。").arg( nDelCount ) );
        //更新树形控件
        UpdateTreeShow();
    }
}
//删除匹配端口的连接
void Widget::on_pushButtonDelPort_clicked()
{
    //获取端口号
    const int nFindPort = ui->spinBoxPort->value();
    int nDelCount = 0; //删除计数
    //读写迭代器
    QMutableMapIterator<QString, int> it( m_tcplinks );
    //循环迭代
    it.toFront(); //从头开始
    //注意 Q*MapIterator 迭代器的 findNext() 和 findPrevious() 比较的是 value ;
    // 而 QMap/QMultiMap 容器类的 find() 比较的是 key 或者 key-value 对。
    while( it.findNext( nFindPort ) ) //端口号是 value，可以用迭代器的查找函数
    {
        it.remove();
        nDelCount += 1;
    }
    //遍历结束
    if( nDelCount < 1 )
    {
        ui->textBrowser->setText( tr("没有匹配的端口。") );
    }
    else
    {
        ui->textBrowser->setText( tr("已删除匹配端口的连接个数：%1 。").arg( nDelCount ) );
        //更新树形控件
        UpdateTreeShow();
    }
}
//找寻 <= 1024 的端口连接
void Widget::on_pushButtonFindBelow1024_clicked()
{
    QMapIterator<QString, int> it( m_tcplinks );
    QString strInfo = tr("1024以下端口号的连接：\r\n");
    //迭代查找
    while( it.hasNext() )
    {
        it.next();  //滑过一个元素
        if( it.value() <= 1024 )
        {
            strInfo += it.key() + tr(" 端口：%1 \r\n").arg(it.value() );
        }
    }
    //显示
    ui->textBrowser->setText( strInfo );
}
//为所有的小端口号增加 1024
void Widget::on_pushButtonPlus1024_clicked()
{
    QMutableMapIterator<QString, int> it( m_tcplinks );
    QString strInfo = tr("修改旧的1024以下端口号的连接：\r\n");
    //迭代查找
    while( it.hasNext() )
    {
        it.next();  //滑过一个元素
        if( it.value() <= 1024 )
        {
            strInfo += it.key() + tr(" 端口：%1 \r\n").arg(it.value() );
            //修改端口号，增加1024
            it.setValue( it.value() + 1024 );
            //等同于  it.value() += 1024;
        }
    }
    //显示
    ui->textBrowser->setText( strInfo );
    //更新树形控件
    UpdateTreeShow();
}
