#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>  //文件对话框
#include <QFile>        //文件类
#include <QDataStream>  //串行化数据流，用于读写 .ds 文件
#include <QTextStream>  //用于列表控件显示的文本和数据转换
#include <QListWidgetItem>//用于从列表控件的行提取文本

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置列表控件只能选中一行，简化删除行的操作
    ui->listWidget->setSelectionMode( QAbstractItemView::SingleSelection );
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonAdd_clicked()
{
    QString strName = ui->lineEditName->text().trimmed();
    QString strAge = ui->lineEditAge->text().trimmed();
    QString strWeight = ui->lineEditWeight->text().trimmed();
    //判断三个数据项是否为空
    if( strName.isEmpty() || strAge.isEmpty() || strWeight.isEmpty() )
    {
        QMessageBox::warning(this, tr("添加行"), tr("请填好姓名、年龄、体重三个数据项再添加。"));
        return;
    }
    //计算出年龄和体重
    qint32 nAge = strAge.toInt();
    double dblWeight = strWeight.toDouble();
    //判断范围
    if( (nAge<0) || (nAge>600) )
    {
        QMessageBox::warning(this, tr("添加行"), tr("年龄数值不对，应该 0~600 "));
        return;
    }
    if( dblWeight < 0.1 )
    {
        QMessageBox::warning(this, tr("添加行"), tr("体重数值不对，至少 0.1kg "));
        return;
    }
    //对于正常数据，添加新行到列表控件
    QString strAll;
    QTextStream tsLine(&strAll);
    tsLine<<strName<<"\t"<<nAge<<"\t"
         <<fixed<<qSetRealNumberPrecision(2)<<dblWeight;
    ui->listWidget->addItem( strAll );
}

void Widget::on_pushButtonDel_clicked()
{
    //获取列表控件选中的行
    int nCurRow = ui->listWidget->currentRow();
    //判断序号是否合法
    if( nCurRow < 0)
    {
        return; //没有选中行
    }
    //对于正常选中的行，删除掉
    ui->listWidget->takeItem( nCurRow );
}

void Widget::on_pushButtonSaveDS_clicked()
{
    //总行数
    int nCount = ui->listWidget->count();
    //判断是否有数据
    if(nCount < 1)
    {
        return; //没数据，不用写
    }
    //获取要保存的文件名
    QString strFileName = QFileDialog::getSaveFileName(
                this,
                tr("保存为 DS 文件"),
                tr("."),
                tr("DS files(*.ds);;All files(*)")
                );
    if( strFileName.isEmpty() )
    {
        return; //没有保存文件名
    }

    //有保存文件名，打开该文件供写入
    QFile fileOut(strFileName);
    if( ! fileOut.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, tr("无法打开文件"),
                            tr("无法打开要写入的文件：") + fileOut.errorString() );
        return;
    }
    //现在有输出文件对象，构造输出流
    QDataStream dsOut(&fileOut);
    //设置流的版本
    dsOut.setVersion(QDataStream::Qt_4_8);

    //先写文件头，都用 qt 定义的整型变量输出
    dsOut<<qint16(0x4453);  //'D' 'S'
    dsOut<<qint16(0x0100);  //1.0版本文件格式
    dsOut<<qint32(nCount);  //行计数
    //每行的三个数据项
    QString strCurName;
    qint32 nCurAge;
    double dblCurWeight;
    //从列表控件按行读取数据，然后写入到文件
    for(int i=0; i<nCount; i++)
    {
        QString strLine = ui->listWidget->item(i)->text();
        QTextStream tsLine(&strLine);
        //从该行文本提取三个数据项
        tsLine>>strCurName>>nCurAge>>dblCurWeight;
        //写入到文件
        dsOut<<strCurName<<nCurAge<<dblCurWeight;
    }
    //提示写入完毕
    QMessageBox::information(this, tr("保存DS文件"), tr("保存为 .ds 文件成功！"));
}

void Widget::on_pushButtonLoadDS_clicked()
{
    //获取要打开的文件名
    QString strFileName = QFileDialog::getOpenFileName(
                this,
                tr("打开DS文件"),
                tr("."),
                tr("DS files(*.ds);;All files(*)")
                );
    //判断文件名
    if( strFileName.isEmpty() )
    {
        return;
    }
    //文件对象
    QFile fileIn( strFileName );
    //打开
    if( ! fileIn.open( QIODevice::ReadOnly ) )
    {
        //打开失败
        QMessageBox::warning(this, tr("打开DS文件"),
                             tr("打开DS文件失败: ") + fileIn.errorString());
        return;
    }
    //构造输入数据流
    QDataStream dsIn(&fileIn);
    //读取文件头
    qint16 nDS;
    qint16 nVersion;
    qint32 nCount;
    dsIn>>nDS>>nVersion>>nCount;
    //判断 nDS 数值
    if( 0x4453 != nDS )
    {
        QMessageBox::warning(this, tr("打开文件"),
                             tr("指定的文件不是 .ds 文件类型，无法加载。"));
        return;
    }
    //判断版本号目前只有 1.0
    if( 0x0100 != nVersion )
    {
        QMessageBox::warning(this, tr("打开文件"),
                             tr("指定的 .ds 文件格式版本不是 1.0，暂时不支持。"));
        return;
    }
    else
    {
        //设置流的版本
        dsIn.setVersion( QDataStream::Qt_4_8 );
    }
    //判断行计数
    if( nCount < 1 )
    {
        QMessageBox::warning(this, tr("打开文件"),
                             tr("指定的 .ds 文件内数据行计数小于 1，无数据加载。"));
        return;
    }
    //现在行计数也正常
    //三个数据项
    QString strCurName;
    qint32 nCurAge;
    double dblCurWeight;
    //先清空列表控件的内容
    ui->listWidget->clear();
    //逐行加载数据到列表控件
    for(int i=0; i<nCount; i++)
    {
        //每行开头判断输入数据流状态
        if( dsIn.status() != QDataStream::Ok )
        {
            qDebug()<<tr("第 %1 行读取前的状态出错：%2").arg(i).arg(dsIn.status());
            break;  //跳出循环
        }
        //如果现在的状态正常，就加载当前行的数据项
        dsIn>>strCurName>>nCurAge>>dblCurWeight;

        //构造字符串
        QString strLine = tr("%1\t%2\t%3")
                .arg(strCurName)
                .arg(nCurAge)
                .arg(dblCurWeight, 0, 'f', 2);
        //添加到列表控件
        ui->listWidget->addItem(strLine);
    }
    //提示加载完毕
    QMessageBox::information(this, tr("加载DS文件"),tr("加载DS文件完成！"));
}

void Widget::on_listWidget_currentRowChanged(int currentRow)
{
    //判断行号是否合法
    if( currentRow < 0 )
    {
        return;
    }
    //对于正常的行号
    //读取该行文本
    QString strLine = ui->listWidget->item(currentRow)->text();
    //构造内存字符串文本流
    QTextStream tsLine(&strLine);
    //三个数据项
    QString strName;
    int nAge;
    double dblWeight;
    tsLine>>strName>>nAge>>dblWeight;

    //显示到三个单行编辑器
    ui->lineEditName->setText(strName);
    ui->lineEditAge->setText( tr("%1").arg(nAge) );
    ui->lineEditWeight->setText( tr("%1").arg(dblWeight) );
}
