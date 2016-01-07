#include "widget.h"
#include "ui_widget.h"
#include <QStorageInfo> //获取存储器信息
#include <QTextDocumentWriter> //将信息写入文件
#include <QMessageBox>
#include <QFileDialog>

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

void Widget::on_pushButtonGetDiskInfo_clicked()
{
    //获取所有分区信息
    QList<QStorageInfo> listDisks = QStorageInfo::mountedVolumes();
    //信息字符串和临时串，使用 HTML 字符串
    QString strInfo;
    QString strTemp;
    //枚举各个分区信息
    int nCount = listDisks.count();
    for(int i=0; i<nCount; i++)
    {
        // <br> 是换行
        strTemp = tr("分区 %1 信息：<br>").arg(i);
        strInfo += strTemp;
        //设备字符串，这个是固定有的信息
        strTemp = listDisks[i].device();
        strInfo += tr("设备：") + strTemp + tr("<br>");
        //挂载点
        strTemp = listDisks[i].rootPath();
        strInfo += tr("挂载点：") + strTemp + tr("<br>");
        //判断是否可用
        if( (listDisks[i].isValid()) && (listDisks[i].isReady()) )
        {
            //可用的，读取更多信息
            //分区显示名
            strTemp = tr("卷名：%1<br>").arg( listDisks[i].displayName() );
            strInfo += strTemp;
            //文件系统类型
            strTemp = tr("文件系统类型：%1<br>").arg( QString( listDisks[i].fileSystemType() ) );
            strInfo += strTemp;
            //是否为操作系统根
            if( listDisks[i].isRoot() )
            {
                //红色粗体
                strTemp = tr("<font color=red><b>系统根：是</b></font><br>");
            }
            else
            {
                strTemp = tr("系统根：否<br>");
            }
            strInfo += strTemp;
            //是否只读
            if( listDisks[i].isReadOnly() )
            {
                strTemp = tr("只读：是<br>");
            }
            else
            {
                strTemp = tr("只读：否<br>");
            }
            strInfo += strTemp;
            //分区的空间信息
            double dblAllGB = 1.0 * listDisks[i].bytesTotal() /(1024*1024*1024);
            double dblFreeGB = 1.0 * listDisks[i].bytesFree() / (1024*1024*1024);
            strTemp = tr("总空间(GB)：%1 已用：%2 剩余：%3<br>")
                    .arg(dblAllGB, 0, 'f', 3)
                    .arg(dblAllGB - dblFreeGB, 0, 'f', 3)
                    .arg(dblFreeGB, 0, 'f', 3);
            strInfo += strTemp;
        }
        else
        {
            //不可用，<b>...</b>字符串是粗体
            strTemp = tr("<b>设备不可用或未加载。</b><br>");
            strInfo += strTemp;
        }
        //下一个分区，换行
        strInfo += tr("<br>");
    }
    //信息收集完毕，显示
    ui->textEdit->setText(strInfo);
}

void Widget::on_pushButtonSaveDiskInfo_clicked()
{
    //获取保存文件名
    QString strFileName = QFileDialog::getSaveFileName(
                this,
                tr("保存信息"),
                tr("."),
                tr("Html files(*.htm);;Text files(*.txt);;ODF files(*.odf)")
                );
    //判断文件名长度
    if( strFileName.length() < 1 )
    {
        return;
    }
    //定义文档保存对象，写入文件
    QTextDocumentWriter tw(strFileName);
    bool bRes = tw.write( ui->textEdit->document() );
    //提示保存是否成功
    if( bRes )
    {
        QMessageBox::information(this, tr("保存成功"), tr("信息已成功保存到文件。"));
    }
    else
    {
        QMessageBox::warning(this, tr("保存出错"), tr("保存到文件出错！"));
    }
}
