#include "widget.h"
#include "ui_widget.h"
#include <QTemporaryFile>//临时文件
#include <QTemporaryDir> //临时文件夹
#include <QElapsedTimer> //耗时计时器
#include <QDebug>
#include <QMessageBox>
#include <QDir>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->radioButton1k->setChecked(true);    //默认计算一千位
    //打印应用程序名
    qDebug()<<tr("应用程序名称：")<<qApp->applicationName();
    //打印操作系统临时文件路径
    qDebug()<<tr("系统临时文件路径：")<<QDir::tempPath();
}

Widget::~Widget()
{
    delete ui;
}
//获取单选按钮指定的PI长度
int Widget::GetPILength()
{
    if( ui->radioButton1k->isChecked() )
    {
        return 1000;
    }
    else if( ui->radioButton2k->isChecked() )
    {
        return 2000;
    }
    else if( ui->radioButton4k->isChecked() )
    {
        return 4000;
    }
    else
    {
        return 8000;
    }
}

void Widget::on_pushButtonCalcPI_clicked()
{
    //要计算的长度
    int nPILength = GetPILength();
    //定义耗时计时器
    QElapsedTimer eTimer;
    eTimer.start();
    //计算PI
    m_calcPI.Calc( nPILength );
    //耗时，毫秒
    qint64 nms = eTimer.elapsed();

    //定义临时文件
    QTemporaryFile tf;  //默认的即可
    if( ! tf.open() )   //打开并判断是否正常
    {
        QMessageBox::information(this, tr("打开临时文件"), tr("打开临时文件失败！"));
        return;
    }
    //设置为不自动删除，通常应该用默认自动删除的临时文件，这里仅用于观察临时文件路径
    tf.setAutoRemove(false);
    //把PI输出到临时文件
    m_calcPI.WriteToFile(tf);

    //构造信息串
    QString strInfo;
    QString strTemp;
    //耗时
    strTemp = tr("计算 %1 位 PI 耗时 %2 毫秒\r\n").arg(nPILength).arg(nms);
    strInfo += strTemp;
    //保存位置
    strTemp = tr("保存到临时文件：\r\n%1\r\n").arg( tf.fileName() );
    strInfo += strTemp;
    //显示到编辑器
    ui->textEdit->setText( strInfo );
}
//计算四次，把计算结果放到临时文件夹
void Widget::on_pushButtonCalcAll_clicked()
{
    //建一个临时文件夹，把四个长度的PI都存到该文件夹
    QTemporaryDir td("PI-");    // "PI-" 是模板
    QString strTempDir; //临时文件夹的路径字符串
    //判断临时文件夹是否可用
    if( td.isValid() )
    {
        strTempDir = td.path();
    }
    else
    {
        //没有正确建立临时文件夹
        QMessageBox::warning(this, tr("新建临时文件夹"), tr("新建临时文件夹失败！"));
        return;
    }
    //设置为不自动删除
    td.setAutoRemove(false);
    //字符串
    QString strInfo;
    QString strTemp;

    //临时文件夹建立正常，下面计算四种长度的PI
    for(int i=1; i<=8; i*=2)
    {
        int nPILength = i*1000;
        QElapsedTimer eTimer;
        //计算PI，并计算耗时
        eTimer.start();
        m_calcPI.Calc(nPILength);
        qint64 nms = eTimer.elapsed();
        //构造文件名，保存到文件
        QString strCurName = strTempDir + tr("/%1.txt").arg(nPILength);
        QFile fileCur(strCurName);
        if( ! fileCur.open( QIODevice::WriteOnly ) )
        {
            QMessageBox::warning(this, tr("新建文件"), tr("新建存储PI的文件失败！"));
        }
        //写入到文件
        m_calcPI.WriteToFile(fileCur);

        //构造结果信息
        strTemp = tr("计算 %1 位 PI，耗时 %2 毫秒\r\n存到 %3 \r\n")
                .arg( nPILength )
                .arg( nms )
                .arg( fileCur.fileName() );
        strInfo += strTemp;
        strInfo += tr("\r\n");
    }
    //显示结果信息
    ui->textEdit->setText( strInfo );
}
