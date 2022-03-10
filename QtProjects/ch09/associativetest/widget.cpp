#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDebug>
#include <random>
using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //窗口标题栏
    setWindowTitle( tr("关联容器测试，时间单位：纳秒") );

    //设置表格列数
    ui->tableWidget->setColumnCount( 4 );
    //设置表头
    QStringList header;
    header<<tr("操作名称")<<tr("QMap")<<tr("QHash")<<tr("QSet");
    ui->tableWidget->setHorizontalHeaderLabels( header );
    //各列均匀拉伸
    ui->tableWidget->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );

    //设置旋钮编辑框
    ui->spinBoxTimes->setSuffix( tr(" 万") ); // 单位万
    ui->spinBoxTimes->setRange( 1, 21*10000 ); //21亿上限
    //设置英语本地化，每三个数字打逗号
    m_locale = QLocale(QLocale::English, QLocale::UnitedStates);
    qDebug()<<m_locale.toString( 1234567 );

}

Widget::~Widget()
{
    delete ui;
}

//添加元素功能测试
void Widget::on_pushButtonInsert_clicked()
{
    //获取测试次数
    int nTimes = ui->spinBoxTimes->value() * 10000;
    //表格控件添加新行
    int nNewRow = ui->tableWidget->rowCount(); //作为新行序号
    ui->tableWidget->setRowCount( nNewRow+1 ); //增加一行
    //设置第 0 列文本
    QString strText = tr("添加元素 %1 万次").arg( ui->spinBoxTimes->value() );
    QTableWidgetItem *itemNew = new QTableWidgetItem( strText );
    ui->tableWidget->setItem(nNewRow, 0, itemNew);

    //C++11特性，定义随机数均匀分布、随机数引擎
    uniform_int_distribution<unsigned> ud(0, nTimes);
    default_random_engine eg;
    //QMap测试
    m_map.clear();
    qint64 nsUsed = 0; //纳秒计数，耗时包含了随机数产生时间
    //开始计时
    m_calcTimer.start();
    for(int i=0; i<nTimes; i++)
    {
        int nVal = ud(eg);
        m_map.insert(nVal, nVal);
    }
    nsUsed = m_calcTimer.nsecsElapsed();
    //设置文本并新建表格条目
    strText = m_locale.toString( nsUsed );
    itemNew = new QTableWidgetItem( strText );
    ui->tableWidget->setItem( nNewRow, 1, itemNew );

    //QHash测试
    m_hash.clear(); //清空旧的
    nsUsed = 0;
    //开始计时
    m_calcTimer.start();
    for(int i=0; i<nTimes; i++)
    {
        int nVal = ud(eg);
        m_hash.insert(nVal, nVal);
    }
    nsUsed = m_calcTimer.nsecsElapsed();
    //设置文本并新建表格条目
    strText = m_locale.toString( nsUsed );
    itemNew = new QTableWidgetItem( strText );
    ui->tableWidget->setItem( nNewRow, 2, itemNew );

    //QSet测试
    m_set.clear(); //清空旧的
    nsUsed = 0;
    //开始计时
    m_calcTimer.start();
    for(int i=0; i<nTimes; i++)
    {
        int nVal = ud(eg);
        m_set.insert( nVal );
    }
    nsUsed = m_calcTimer.nsecsElapsed();
    //设置文本并新建条目
    strText = m_locale.toString( nsUsed );
    itemNew = new QTableWidgetItem( strText );
    ui->tableWidget->setItem( nNewRow, 3, itemNew );
}
//随机访问功能测试
void Widget::on_pushButtonFind_clicked()
{
    //检查是否为空
    if( m_map.isEmpty() || m_hash.isEmpty() || m_set.isEmpty() )
    {
        QMessageBox::warning(this, tr("随机访问"), tr("容器对象为空，请执行添加元素后执行访问！"));
        return;
    }
    //获取测试次数
    int nTimes = ui->spinBoxTimes->value() * 10000;
    //表格控件增加一行
    int nNewRow = ui->tableWidget->rowCount(); //新行的序号
    ui->tableWidget->setRowCount( nNewRow+1 ); //加一行
    //设置第 0 列文本
    QString strText = tr("随机访问 %1 万次").arg( ui->spinBoxTimes->value() );
    QTableWidgetItem *itemNew = new QTableWidgetItem( strText );
    ui->tableWidget->setItem( nNewRow, 0, itemNew );

    //C++11特性，定义随机数均匀分布、随机数引擎
    uniform_int_distribution<unsigned> ud(0, nTimes);
    default_random_engine eg;

    //QMap测试
    qint64 nsUsed = 0; //纳秒计数，耗时包含了随机数产生时间
    //开始计时
    m_calcTimer.start();
    for(int i=0; i<nTimes; i++)
    {
        int nVal = ud(eg);
        m_map.find( nVal );
    }
    nsUsed = m_calcTimer.nsecsElapsed();
    //设置文本并新建表格条目
    strText = m_locale.toString( nsUsed );
    itemNew = new QTableWidgetItem( strText );
    ui->tableWidget->setItem( nNewRow, 1, itemNew );

    //QHash测试
    nsUsed = 0;
    //开始计时
    m_calcTimer.start();
    for(int i=0; i<nTimes; i++)
    {
        int nVal = ud(eg);
        m_hash.find(nVal);
    }
    nsUsed = m_calcTimer.nsecsElapsed();
    //设置文本并新建表格条目
    strText = m_locale.toString( nsUsed );
    itemNew = new QTableWidgetItem( strText );
    ui->tableWidget->setItem( nNewRow, 2, itemNew );

    //QSet测试
    nsUsed = 0;
    //开始计时
    m_calcTimer.start();
    for(int i=0; i<nTimes; i++)
    {
        int nVal = ud(eg);
        m_set.find( nVal );
    }
    nsUsed = m_calcTimer.nsecsElapsed();
    //设置文本并新建条目
    strText = m_locale.toString( nsUsed );
    itemNew = new QTableWidgetItem( strText );
    ui->tableWidget->setItem( nNewRow, 3, itemNew );
}
