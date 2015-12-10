#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDataStream>  //串行化数据流
#include <QListWidgetItem>  //从列表控件的行提取文本
#include <QIntValidator>    //验证端口号范围

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置列表控件一次只能选一行
    ui->listWidget->setSelectionMode( QAbstractItemView::SingleSelection );
    //新建验证器，限制源端口和目的端口范围
    QIntValidator *valSrc = new QIntValidator(0, 65535);
    ui->lineEditSrcPort->setValidator( valSrc );
    QIntValidator *valDst = new QIntValidator(0, 65535);
    ui->lineEditDstPort->setValidator( valDst );
}

Widget::~Widget()
{
    delete ui;
}
//将 UDPPacker 对象串行化的全局函数
QDataStream & operator<<(QDataStream & stream, const UDPPacker & udp)
{
    //将数据按照规定顺序都写入流中，整型数值会自动转为网络字节序
    stream<<udp.m_srcPort;
    stream<<udp.m_dstPort;
    stream<<udp.m_length;
    stream<<udp.m_checksum;
    //写入裸的数据报文
    stream.writeRawData( udp.m_data.data(), udp.m_data.size() );

    //返回数据流对象
    return stream;
}

QDataStream & operator>>(QDataStream & stream, UDPPacker & udp)
{
    //按照原来的顺序和类型读取，网络字节序自动转为主机字节序
    stream>>udp.m_srcPort;
    stream>>udp.m_dstPort;
    stream>>udp.m_length;
    stream>>udp.m_checksum;
    //读取裸的数据报文
    //readRawData参数的缓冲区必须由程序员提前分配空间
    //计算报文消息的长度
    int nMsgLen = udp.m_length - 8; //减去包头 8 字节
    char *buff = new char[nMsgLen]; //分配空间
    stream.readRawData( buff, nMsgLen );    //把数据读到缓冲区
    //把缓冲区设置给 QByteArray 对象，缓冲区自动划归 QByteArray 对象管理，不要手动删除 buff 指针
    udp.m_data.setRawData( buff, nMsgLen );

    //返回数据流对象
    return stream;
}

void Widget::on_pushButtonAddUDP_clicked()
{
    //获取字符串
    QString strSrcPort = ui->lineEditSrcPort->text().trimmed();
    QString strDstPort = ui->lineEditDstPort->text().trimmed();
    QString strMsg = ui->lineEditMsg->text().trimmed();
    //判断字符串是否为空
    if( strSrcPort.isEmpty() || strDstPort.isEmpty() || strMsg.isEmpty() )
    {
        QMessageBox::warning(this, tr("添加包"), tr("请先填写两个端口和消息字符串。"));
        return;
    }
    //定义UDP包的结构体
    UDPPacker udp;
    //把消息转为 UTF-8 编码的字节数组
    QByteArray baMsg = strMsg.toUtf8();
    //填充结构体
    udp.m_srcPort = strSrcPort.toUShort();
    udp.m_dstPort = strDstPort.toUShort();
    udp.m_length = 8 + baMsg.size();    //8是包头长度
    udp.m_checksum = 0 ;    //这里填充0，UDP校验和不是强制要求
    udp.m_data = baMsg;

    //把结构体输出到一个字节数组，打成一个包
    QByteArray baAll;
    QDataStream dsOut(&baAll, QIODevice::ReadWrite);
    dsOut<<udp; //只需要一句，就可以把复杂的结构体填充到流里面

    //baAll 是原始字节数组，人为不可读，转为十六进制字符串显示
    QString strAll = baAll.toHex();
    //添加到列表控件显示
    ui->listWidget->addItem( strAll );
}

void Widget::on_pushButtonDelUDP_clicked()
{
    //获取行号
    int nCurRow = ui->listWidget->currentRow();
    //判断行号是否合法
    if( nCurRow < 0 )
    {
        return;
    }
    //删除该行的 UDP 包
    ui->listWidget->takeItem(nCurRow);
}

//把UDP包存到文件
void Widget::on_pushButtonSave_clicked()
{
    //获取行计数，并判断是否有数据行
    int nCount = ui->listWidget->count();
    if(nCount < 1)
    {
        return;
    }
    //获取保存文件名
    QString strFileName = QFileDialog::getSaveFileName(
                this,
                tr("保存UDP文件"),
                tr("."),
                tr("UDP files(*.udp);;All files(*)") );
    //判断文件名
    if( strFileName.isEmpty() )
    {
        return; //没文件名不保存
    }
    //根据文件名定义文件对象
    QFile fileOut(strFileName);
    //打开
    if( ! fileOut.open( QIODevice::WriteOnly ) )
    {
        QMessageBox::warning(this, tr("保存UDP文件"),
                             tr("打开要保存的文件失败：") + fileOut.errorString());
        return;
    }
    //构建串行化输出流
    QDataStream dsOut( &fileOut );
    //不设置流的版本号，用默认的版本号
    //先写入一个整型变量，表示包个数
    dsOut<<qint32(nCount);

    //用 for 循环从列表控件提取包
    UDPPacker udpCur;
    for(int i=0; i<nCount; i++)
    {
        //十六进制字符串
        QString strHex = ui->listWidget->item(i)->text();
        //转为原始数据包
        QByteArray baCur = QByteArray::fromHex( strHex.toUtf8() );
        //根据字节数组定义输入流
        QDataStream dsIn(baCur);
        //提取UDP包
        dsIn>>udpCur;

        //把原始 udp 包写入到文件中
        dsOut<<udpCur;
    }
    //保存完毕
    QMessageBox::information(this, tr("保存UDP包"), tr("保存UDP包到文件完毕！"));
}

void Widget::on_pushButtonLoad_clicked()
{
    //获取打开文件名
    QString strFileName = QFileDialog::getOpenFileName(
                this,
                tr("打开UDP文件"),
                tr("."),
                tr("UDP files(*.udp);;All files(*)") );
    //判断文件名
    if( strFileName.isEmpty() )
    {
        return;
    }
    //定义文件对象
    QFile fileIn( strFileName );
    //打开
    if( ! fileIn.open(QIODevice::ReadOnly) )
    {
        QMessageBox::warning(this, tr("打开UDP文件"),
                             tr("打开指定UDP文件失败：") + fileIn.errorString());
        return;
    }
    //定义串行化输入流
    QDataStream dsIn(&fileIn);
    //获取数据包个数
    qint32 nCount;
    dsIn>>nCount;
    //判断个数
    if( nCount < 1 )
    {
        QMessageBox::warning(this, tr("加载UDP包"), tr("指定UDP文件内数据包计数小于1，无法加载。"));
        return;
    }
    //先清空列表控件内容
    ui->listWidget->clear();
    //使用 for 循环提取UDP数据包
    UDPPacker udpCur;
    for( int i=0; i<nCount; i++ )
    {
        //先判断流的状态，状态不对就结束循环
        if( dsIn.status() != QDataStream::Ok )
        {
            qDebug()<<tr("读取第 %1 个数据包前的状态错误：%2").arg(i).arg(dsIn.status());
            break;
        }
        //提取UDP数据包
        dsIn>>udpCur;

        //把UDP数据包的内容打包成一个 QByteArray
        QByteArray baCur;
        QDataStream dsOut(&baCur, QIODevice::ReadWrite);
        dsOut<<udpCur;
        //把原始字节数组转成十六进制字符串
        QString strHex = baCur.toHex();
        //添加到列表控件显示
        ui->listWidget->addItem( strHex );
    }
    //提示加载完毕
    QMessageBox::information(this, tr("加载UDP包"), tr("加载文件中的UDP包完成！"));
}

void Widget::on_listWidget_currentRowChanged(int currentRow)
{
    //判断行号是否合法
    if( currentRow < 0 )
    {
        return;
    }
    //提取十六进制字符串
    QString strHex = ui->listWidget->item(currentRow)->text();
    //转为原始数据包
    QByteArray baAll = QByteArray::fromHex( strHex.toUtf8() );
    //构造输入流
    QDataStream dsIn(baAll);
    //定义UDP结构体对象
    UDPPacker udp;
    dsIn>>udp;      //只需要一句，就可以从字节数组提取 UDP 结构体对象

    //显示到三个编辑器里面
    ui->lineEditSrcPort->setText( tr("%1").arg( udp.m_srcPort ) );
    ui->lineEditDstPort->setText( tr("%1").arg( udp.m_dstPort ) );
    ui->lineEditMsg->setText( QString::fromUtf8( udp.m_data ) );
}
