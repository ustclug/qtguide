#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QFile>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //加载地图和文本数据，包含省份和像素点位置
    LoadData();
    //初始化控件
    InitControls();
}

Widget::~Widget()
{
    delete ui;
}

//加载地图和文本数据，包含省份和像素点位置
void Widget::LoadData()
{
    //加载地图
    m_map.load( ":/china.png" );
    //读取文本文件
    QFile fileIn( ":/china.txt" );
    m_listProvinces.clear();
    m_listPoints.clear();
    //打开文件
    fileIn.open( QIODevice::ReadOnly|QIODevice::Text );
    while( ! fileIn.atEnd() )
    {
        QByteArray baLine = fileIn.readLine();
        QString strLine = QString::fromUtf8( baLine );
        QStringList liParts = strLine.split( '\t' );
        QPoint pt;
        m_listProvinces << liParts[0];
        pt.setX( liParts[1].toInt() );
        pt.setY( liParts[2].toInt() );
        m_listPoints<<pt;
    }
    //加载完毕
    qDebug()<<m_listProvinces.size()<<m_listProvinces;
    qDebug()<<m_listPoints.size()<<m_listPoints;
}

//初始化控件
void Widget::InitControls()
{
    //使用QLabel绘图
    m_labelMap = new QLabel();
    m_labelMap->setPixmap( m_map );
    //构建滚动区域包裹标签
    m_saLeftMap = new QScrollArea();
    m_saLeftMap->setWidget( m_labelMap );

    //右边容器和布局器
    QWidget *pWidRight = new QWidget();
    QVBoxLayout *pLayoutRight = new QVBoxLayout();
    //用于循环新建单选按钮
    QRadioButton *curButton = NULL;
    m_pSigMapper = new QSignalMapper(this);
    //个数
    int nCount = m_listProvinces.size();
    for(int i=0; i<nCount; i++)
    {
        curButton = new QRadioButton( m_listProvinces[i] );
        //关联信号到信号映射对象
        connect(curButton, SIGNAL(clicked()),
                m_pSigMapper, SLOT(map()) );
        //设置映射参数，将当前按钮的编号设置为 i
        m_pSigMapper->setMapping(curButton, i);
        //添加到布局器
        pLayoutRight->addWidget( curButton );
    }
    //将信号映射对象的 mapped() 信号关联到统一的槽函数
    connect(m_pSigMapper, SIGNAL(mapped(int)),
            this, SLOT(ShowProvince(int)) );

    //布局器设置给右边容器
    pWidRight->setLayout( pLayoutRight );
    //新建右边滚动区域，将容器设置给右边滚动区域
    m_saRightButtons = new QScrollArea();
    m_saRightButtons->setWidget( pWidRight );

    //主界面布局器
    QHBoxLayout *pMainLayout = new QHBoxLayout();
    pMainLayout->addWidget( m_saLeftMap );
    pMainLayout->addWidget( m_saRightButtons );
    pMainLayout->setStretch( 0, 4); //左边拉伸因子 4
    pMainLayout->setStretch( 1, 1); //右边拉伸因子 1
    //主窗口布局器
    setLayout( pMainLayout );
    //窗口大小
    resize(800, 600);
    //最后一个单选按钮选中
    curButton->setChecked( true );
    //显示最后一个单选按钮
    m_saRightButtons->ensureWidgetVisible( curButton );
    //视口保证最后一个点会显示
    m_saLeftMap->ensureVisible( m_listPoints[nCount-1].x(), m_listPoints[nCount-1].y(), 200, 200 );
}

//信号映射将所有按钮的信号都发给该槽函数
void Widget::ShowProvince(int index)
{
    m_saLeftMap->ensureVisible( m_listPoints[index].x(), m_listPoints[index].y(), 200, 200 );
}

