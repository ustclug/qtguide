#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QTableWidgetItem>//表格控件条目
#include <QTableWidget>//表格控件

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置标题栏
    setWindowTitle( tr("顺序容器操作耗时测试，时间单位：纳秒") );
    //设置表格列计数
    ui->tableWidget->setColumnCount( 4 );
    //设置表头
    QStringList header;
    header<<tr("操作名称")<<tr("QLinkedList")<<tr("QList")<<tr("QVector");
    ui->tableWidget->setHorizontalHeaderLabels( header );
    //各列均匀拉伸
    ui->tableWidget->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
    //设置旋钮编辑框
    ui->spinBoxTimes->setSuffix( tr(" 万") );//次数的单位是万
    ui->spinBoxTimes->setRange( 1, 21*10000 );//测试次数范围从1万到21亿，int上限是 21 亿多
    //设置英语本地化，每3个数字使用逗号分隔
    m_locale = QLocale(QLocale::English, QLocale::UnitedStates);
    qDebug()<<m_locale.toString( 1234567 );
}

Widget::~Widget()
{
    delete ui;
}

//测试头部添加的耗时
void Widget::on_pushButtonPrepend_clicked()
{
    //获取测试次数
    int nTimes = ui->spinBoxTimes->value() * 10000;
    //表格控件添加新行
    int nNewRow = ui->tableWidget->rowCount(); //新增行的序号
    ui->tableWidget->setRowCount( nNewRow + 1 );
    //设置第 0 列文本
    QString strText = tr("头部添加 %1 万次").arg( ui->spinBoxTimes->value() );
    QTableWidgetItem *itemNew = new QTableWidgetItem( strText );
    ui->tableWidget->setItem(nNewRow, 0, itemNew);

    //链表测试，先清空旧的内容
    m_linkdList.clear();
    qint64 nsUsed = 0;  //统计纳秒数
    //开始计时
    m_calcTimer.start();
    for(int i=0; i<nTimes; i++)
    {
        m_linkdList.prepend( i ); //头部添加
    }
    nsUsed = m_calcTimer.nsecsElapsed();//耗时
    //设置文本并新建表格条目
    strText = m_locale.toString( nsUsed );
    itemNew = new QTableWidgetItem(strText);
    ui->tableWidget->setItem( nNewRow, 1, itemNew );

    //列表测试，先清空旧的内容
    m_list.clear();
    //开始计时
    m_calcTimer.start();
    //提前保留元素空间，避免频繁分配空间和复制元素
    m_list.reserve( nTimes );
    for(int i=0; i<nTimes; i++)
    {
        m_list.prepend( i );    //头部添加
    }
    nsUsed = m_calcTimer.nsecsElapsed();//耗时
    //设置文本并新建表格条目
    strText = m_locale.toString( nsUsed );
    itemNew = new QTableWidgetItem(strText);
    ui->tableWidget->setItem( nNewRow, 2, itemNew );

    //向量测试，先清空旧的
    m_vector.clear();
    //开始计时
    m_calcTimer.start();
    //提前保留元素空间
    m_vector.reserve( nTimes );
    for(int i=0; i<nTimes; i++)
    {
        m_vector.prepend( i );  //头部添加
    }
    nsUsed = m_calcTimer.nsecsElapsed();//耗时
    //设置文本并新建表格条目
    strText = m_locale.toString( nsUsed );
    itemNew = new QTableWidgetItem(strText);
    ui->tableWidget->setItem( nNewRow, 3, itemNew );

    //滚动到最下面新建行
    ui->tableWidget->scrollToBottom();
}

//测试中部添加的耗时
void Widget::on_pushButtonMidInsert_clicked()
{
    int nTimes = ui->spinBoxTimes->value() * 10000;
    //表格控件添加新行
    int nNewRow = ui->tableWidget->rowCount(); //新增行的序号
    ui->tableWidget->setRowCount( nNewRow + 1 );
    //设置第 0 列文本
    QString strText = tr("中部添加 %1 万次").arg( ui->spinBoxTimes->value() );
    QTableWidgetItem *itemNew = new QTableWidgetItem( strText );
    ui->tableWidget->setItem(nNewRow, 0, itemNew);

    //链表测试，先清空旧的内容
    m_linkdList.clear();
    qint64 nsUsed = 0;  //统计纳秒数
    QLinkedList<int>::iterator it; //迭代器
    //开始计时
    m_calcTimer.start();
    for(int i=0; i<nTimes; i++)
    {
        int nMid = m_linkdList.count() / 2;
        //用迭代器访问，链表如果知道指向元素的迭代器，那么增删效率高
        //如果不知道中间元素迭代器，那么迭代器遍历的时间比较长
        it = m_linkdList.begin();
        for(int j=0; j<nMid; j++)
        {
            it++;
        }
        //中部添加
        m_linkdList.insert(it, i);
    }
    nsUsed = m_calcTimer.nsecsElapsed();//耗时
    //设置文本并新建表格条目
    strText = m_locale.toString( nsUsed );
    itemNew = new QTableWidgetItem(strText);
    ui->tableWidget->setItem( nNewRow, 1, itemNew );

    //列表测试，先清空旧的
    m_list.clear();
    //开始计时
    m_calcTimer.start();
    //提前保留元素空间，避免频繁分配空间和复制元素
    m_list.reserve( nTimes );
    for(int i=0; i<nTimes; i++)
    {
        m_list.insert( m_list.count()/2, i );
    }
    nsUsed = m_calcTimer.nsecsElapsed();//耗时
    //设置文本并新建表格条目
    strText = m_locale.toString( nsUsed );
    itemNew = new QTableWidgetItem(strText);
    ui->tableWidget->setItem( nNewRow, 2, itemNew );

    //向量测试，先清空旧的
    m_vector.clear();
    //开始计时
    m_calcTimer.start();
    //提前保留元素空间
    m_vector.reserve( nTimes );
    for(int i=0; i<nTimes; i++)
    {
        m_vector.insert( m_vector.count()/2, i );
    }
    nsUsed = m_calcTimer.nsecsElapsed();//耗时
    //设置文本并新建表格条目
    strText = m_locale.toString( nsUsed );
    itemNew = new QTableWidgetItem(strText);
    ui->tableWidget->setItem( nNewRow, 3, itemNew );

    //滚动到最下面新建行
    ui->tableWidget->scrollToBottom();
}

//测试尾部添加的耗时
void Widget::on_pushButtonAppend_clicked()
{
    //获取测试次数
    int nTimes = ui->spinBoxTimes->value() * 10000;
    //表格控件添加新行
    int nNewRow = ui->tableWidget->rowCount(); //新增行的序号
    ui->tableWidget->setRowCount( nNewRow + 1 );
    //设置第 0 列文本
    QString strText = tr("尾部添加 %1 万次").arg( ui->spinBoxTimes->value() );
    QTableWidgetItem *itemNew = new QTableWidgetItem( strText );
    ui->tableWidget->setItem(nNewRow, 0, itemNew);

    //链表测试，先清空旧的
    m_linkdList.clear();
    qint64 nsUsed = 0;  //统计纳秒数
    //开始计时
    m_calcTimer.start();
    for(int i=0; i<nTimes; i++)
    {
        m_linkdList.append( i );//尾部添加
    }
    nsUsed = m_calcTimer.nsecsElapsed();//耗时
    //设置文本并新建表格条目
    strText = m_locale.toString( nsUsed );
    itemNew = new QTableWidgetItem(strText);
    ui->tableWidget->setItem( nNewRow, 1, itemNew );

    //列表测试，先清空旧的
    m_list.clear();
    //开始计时
    m_calcTimer.start();
    //提前保留元素空间
    m_list.reserve( nTimes );
    for(int i=0; i<nTimes; i++)
    {
        m_list.append( i );//尾部添加
    }
    nsUsed = m_calcTimer.nsecsElapsed();//耗时
    //设置文本并新建表格条目
    strText = m_locale.toString( nsUsed );
    itemNew = new QTableWidgetItem(strText);
    ui->tableWidget->setItem( nNewRow, 2, itemNew );

    //向量测试，先清空旧的
    m_vector.clear();
    //开始计时
    m_calcTimer.start();
    //提前保留元素空间
    m_vector.reserve( nTimes );
    for(int i=0; i<nTimes; i++)
    {
        m_vector.append( i );//尾部添加
    }
    nsUsed = m_calcTimer.nsecsElapsed();//耗时
    //设置文本并新建表格条目
    strText = m_locale.toString( nsUsed );
    itemNew = new QTableWidgetItem(strText);
    ui->tableWidget->setItem( nNewRow, 3, itemNew );

    //滚动到最下面新建行
    ui->tableWidget->scrollToBottom();
}

void Widget::on_pushButtonRandAccess_clicked()
{
    //获取测试次数
    int nTimes = ui->spinBoxTimes->value() * 10000;
    //查看元素数量是否有 nTimes 个
    if( m_list.count() < nTimes )
    {
        QMessageBox::warning(this, tr("随机访问"), tr("请先进行任意其他项测试为顺序容器添加元素。"));
        return;
    }
    //每个容器已经有了 nTimes 个元素
    //表格控件添加新行
    int nNewRow = ui->tableWidget->rowCount(); //新增行的序号
    ui->tableWidget->setRowCount( nNewRow + 1 );
    //设置第 0 列文本
    QString strText = tr("随机访问 %1 万次").arg( ui->spinBoxTimes->value() );
    QTableWidgetItem *itemNew = new QTableWidgetItem( strText );
    ui->tableWidget->setItem(nNewRow, 0, itemNew);
    //计时变量和随机序号变量
    qint64 nsUsed = 0; //纳秒计时
    int nIndex = 0; //随机序号

    //链表测试，随机访问
    int nAllCount = m_linkdList.count(); //元素数量
    //开始计时
    m_calcTimer.start();
    for(int i=0; i<nTimes; i++)
    {
        //生成新的随机序号
        nIndex = ( nIndex + qrand() ) % nAllCount;
        //迭代器
        QLinkedList<int>::iterator it = m_linkdList.begin();
        for(int j=0; j<nIndex; j++) //只能用迭代器查找元素
        {
            it++;
        }
        (*it) += i; //获取元素值并加上 i
    }
    nsUsed = m_calcTimer.nsecsElapsed();//耗时
    //设置文本并新建表格条目
    strText = m_locale.toString( nsUsed );
    itemNew = new QTableWidgetItem(strText);
    ui->tableWidget->setItem( nNewRow, 1, itemNew );

    //列表随机访问测试
    nAllCount = m_list.count(); //元素的数量
    //开始计时
    m_calcTimer.start();
    for(int i=0; i<nTimes; i++)
    {
        //生成新的随机序号
        nIndex = ( nIndex + qrand() ) % nAllCount;
        m_list[ nIndex ] += i; //将元素值加 i
    }
    nsUsed = m_calcTimer.nsecsElapsed();//耗时
    //设置文本并新建表格条目
    strText = m_locale.toString( nsUsed );
    itemNew = new QTableWidgetItem(strText);
    ui->tableWidget->setItem( nNewRow, 2, itemNew );

    //向量随机访问测试
    nAllCount = m_vector.count();
    //开始计时
    m_calcTimer.start();
    for(int i=0; i<nTimes; i++)
    {
        //生成新的随机序号
        nIndex = ( nIndex + qrand() ) % nAllCount;
        m_vector[ nIndex ] += i; //将元素值加 i
    }
    nsUsed = m_calcTimer.nsecsElapsed();//耗时
    //设置文本并新建表格条目
    strText = m_locale.toString( nsUsed );
    itemNew = new QTableWidgetItem(strText);
    ui->tableWidget->setItem( nNewRow, 3, itemNew );

    //滚动到最下面新建行
    ui->tableWidget->scrollToBottom();
}
