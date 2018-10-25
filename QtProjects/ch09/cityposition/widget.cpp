#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QFile>    //文件
#include <QTextStream>//文本流

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置编辑框为只读
    ui->lineEditLongitude->setReadOnly(true);
    ui->lineEditLatitude->setReadOnly(true);
    //从资源文件 position.txt 读取省市经纬度
    loadPositions();
    //关联信号，省份组合框序号变化
    connect(ui->comboBoxProvince, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onProvinceIndexChange(int)) );
    //市县组合框序号变化
    connect(ui->comboBoxCity, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onCityIndexChange(int)) );
}

Widget::~Widget()
{
    delete ui;
}

//从资源文件 position.txt 读取省市经纬度
void Widget::loadPositions()
{
    //打开资源里的文件
    QFile fileIn( ":/position.txt" );
    //资源文件打开一般不需要判断，只要文件名对就可以打开
    fileIn.open( QIODevice::ReadOnly );
    //定义文本流
    QTextStream tsIn(&fileIn);
    tsIn.setCodec( "UTF-8" ); //该文件使用 UTF-8 文本编码

    //为二维向量的第一维省份添加元素空间，这样后面才能使用中括号访问
    m_vCities.resize( 40 );//全国省份目前只有34个，分配 40 保证够用
    m_vLongitudes.resize( 40 );
    m_vLatitudes.resize( 40 );

    //定义变量
    QString strProvBefore;//保存前一行记录的省份，用于判断是否应该添加新省份了
    QString strProvCur;   //当前行加载的省份
    QString strCity;    //当前行加载的市县
    int nLonD;  //经度的度
    int nLonM;  //经度的分
    int nLatD;  //纬度的度
    int nLatM;  //纬度的分
    //记录当前省份的序号
    int nProvIndex = -1;
    //开始读取，文本流不结束就一直读
    while( !tsIn.atEnd() )
    {
        //依次读取省份、市县、纬度的度和分、经度的度和分
        tsIn>>strProvCur>>strCity
            >>nLatD>>nLatM
            >>nLonD>>nLonM ;
        //如果当前省份不等于前一个省份，需要新增省份
        if( strProvBefore != strProvCur )
        {
            nProvIndex++; //省份序号增加
            strProvBefore = strProvCur; //保存省份，用于下一行记录判断
            //添加新的省份
            m_vProvinces<<strProvCur; //一维向量不需要提前分配，自动分配空间并追加元素
        }
        //无论省份新旧，都要添加市县、经度、纬度
        //添加市县
        m_vCities[nProvIndex] << strCity;
        //添加纬度，转为浮点数的度
        m_vLatitudes[nProvIndex] << nLatD + (double)nLatM/60.0;
        //添加经度
        m_vLongitudes[nProvIndex] << nLonD + (double)nLonM/60.0;
    }
    //从文件加载完毕
    //省份组合框的内容是固定的，直接添加
    for(int i=0; i<m_vProvinces.count(); i++)
    {
        ui->comboBoxProvince->addItem( m_vProvinces[i] );
    }
    //设置省份序号
    ui->comboBoxProvince->setCurrentIndex( 0 );
    //手动调用省份变化槽函数，显示第一个省份的所有市县到组合框
    onProvinceIndexChange( 0 );
    //手动调用市县变化槽函数，显示经纬度
    onCityIndexChange( 0 );
    //打印省份计数
    qDebug()<<tr("加载完毕，省份计数： %1").arg( m_vProvinces.count() );
}

//根据省份序号变化，自动加载该省的市县
void Widget::onProvinceIndexChange(int index)
{
    if(index < 0)   return; //序号不合法，不处理
    //清空市县组合框
    ui->comboBoxCity->clear();
    //根据省份序号，加载该省的市县到市县组合框
    //该省的市县计数
    int nCount = m_vCities[index].count();
    for(int i=0; i<nCount; i++)
    {
        //第一维是省序号，第二维是市县序号
        ui->comboBoxCity->addItem( m_vCities[index][i] );
    }
    //设置默认市县的序号
    ui->comboBoxCity->setCurrentIndex( 0 );
}

//根据市县序号变化，自动显示市县的经纬度到编辑框
void Widget::onCityIndexChange(int index)
{
    if(index < 0)   return; //序号不合法，不处理
    //获取省份序号，为第一个纬度
    int nProvIndex = ui->comboBoxProvince->currentIndex();
    //设置经度编辑框
    ui->lineEditLongitude->setText(
                tr("%1").arg( m_vLongitudes[nProvIndex][index] ) );
    //设置纬度编辑框
    ui->lineEditLatitude->setText(
                tr("%1").arg( m_vLatitudes[nProvIndex][index] ) );
}
