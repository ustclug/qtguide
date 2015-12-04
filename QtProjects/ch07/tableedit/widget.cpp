#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>      //打开或保存文件对话框
#include <QFile>            //文件类
#include <QTextStream>      //文本流输入输出
#include <QListWidgetItem>  //列表控件条目

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置列表控件的选中模式，一次只能选一行
    ui->listWidget->setSelectionMode( QAbstractItemView::SingleSelection );
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonLoad_clicked()
{
    //获取打开文件名
    QString strFile = QFileDialog::getOpenFileName(
                this,
                tr("打开文件"),
                tr("."),
                tr("Text Files(*.txt);;All files(*)")
                );
    //判断文件名
    if( strFile.isEmpty() )
    {
        return;
    }
    //有文件名，定义文件对象并打开
    QFile fileIn(strFile);
    if( ! fileIn.open(QIODevice::ReadOnly) )
    {
        QMessageBox::warning(this, tr("打开文件"),
                             tr("打开文件失败：") + fileIn.errorString());
        return;
    }
    //文件已经正确打开，定义文本流
    QTextStream tsIn(&fileIn);
    //表格的列数据类型
    QString strCurName;
    int nCurAge;
    double dblCurWeight;
    //先清空旧的列表
    ui->listWidget->clear();

    //加载自定义的表格数据
    while( ! tsIn.atEnd() )
    {
        //提取打头的字符串
        tsIn>>strCurName;
        //判断空行
        if( strCurName.isEmpty() )
        {
            tsIn.skipWhiteSpace();  //跳过空白
            continue;
        }
        //判断注释行
        if( strCurName.startsWith( '#' ) )
        {
            //是注释行，跳过这一行
            tsIn.readLine();
            continue;
        }
        //现在 strCurName 是正常的人名
        //提取后续的年龄、体重
        tsIn>>nCurAge>>dblCurWeight;

        //原本可以用 arg 函数进行内存字符串格式化
        //这里用文本流格式化输出到内存字符串里面
        QString strOut;
        QTextStream tsOut( & strOut );
        tsOut<<strCurName<<"\t"<<nCurAge<<"\t";
        //定点数形式，精度为2，输出到内存字符串
        tsOut<<fixed<<qSetRealNumberPrecision(2)<<dblCurWeight;
        //内存中输出字符串填充好了，添加到列表控件
        ui->listWidget->addItem( strOut );
    }
    //提示加载完毕
    QMessageBox::information(this, tr("加载表格"), tr("加载自定义表格完毕。"));
}

void Widget::on_pushButtonSave_clicked()
{
    //条目计数
    int nCount = ui->listWidget->count();
    if(nCount < 1)
    {
        //没有数据
        return;
    }
    //获取保存的文件名
    QString strFileSave = QFileDialog::getSaveFileName(
                this,
                tr("保存文件"),
                tr("."),
                tr("XLS files(*.xls);;Text Files(*.txt)")
                );
    if(strFileSave.isEmpty())
    {
        //文件名是空的
        return;
    }
    //打开输出文件
    QFile fileOut(strFileSave);
    if( ! fileOut.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, tr("保存文件"),
                             tr("打开保存文件失败：") + fileOut.errorString());
        return;
    }
    //定义输出文本流
    QTextStream tsOut( & fileOut);
    //先打印一行表头
    tsOut<<tr("#姓名\t岁数\t体重")<<endl;
    //从列表提取信息
    for(int i=0; i<nCount; i++)
    {
        QString strCurAll = ui->listWidget->item(i)->text();
        tsOut<<strCurAll<<endl;
    }
    //提示保存完毕
    QMessageBox::information(this, tr("保存文件"), tr("保存表格文件成功。"));
}

void Widget::on_pushButtonDelRow_clicked()
{
    //选取当前选中的行
    int nCurIndex = ui->listWidget->currentRow();
    if(nCurIndex < 0)
    {
        //没有选中合法行
        return;
    }
    else
    {
        //删除行
        ui->listWidget->takeItem( nCurIndex );
    }
}

void Widget::on_pushButtonAddRow_clicked()
{
    QString strName = ui->lineEditName->text().trimmed();
    QString strAge = ui->lineEditAge->text().trimmed();
    QString strWeight = ui->lineEditWeight->text().trimmed();
    //判断是否为空
    if( strName.isEmpty() || strAge.isEmpty() || strWeight.isEmpty() )
    {
        QMessageBox::warning(this, tr("添加行"), tr("请先填好三项数据再添加！"));
        return;
    }
    int nAge = strAge.toInt();  //年龄
    double dblWeight = strWeight.toDouble();    //体重
    //判断年龄体重是否正确
    if( (nAge < 0)  || (nAge > 600) )
    {
        QMessageBox::warning(this, tr("添加行"), tr("年龄不能是负数或超过600！"));
        return;
    }
    if( dblWeight < 0.1 )
    {
        QMessageBox::warning(this, tr("添加行"), tr("重量不能低于 0.1 kg ！"));
        return;
    }
    //添加正确的数据，这里使用 arg 函数实现格式化字符串
    //无论用 arg 函数还是 QTextStream 都可以实现一样的效果
    QString strCurAll = tr("%1\t%2\t%3").arg(strName)
            .arg(nAge)
            .arg( dblWeight, 0, 'f', 2 );
    ui->listWidget->addItem( strCurAll );
}

//选中的行变化时，把当前选中行的数据显示到下方编辑器里面
void Widget::on_listWidget_currentRowChanged(int currentRow)
{
    if( currentRow < 0 )
    {
        //非法的行号不处理
        return;
    }
    //正常行号，读取行文本
    QString strCurAll = ui->listWidget->item( currentRow )->text();
    //根据字符串构造输入流
    QTextStream tsLine( &strCurAll );
    //三项数据
    QString strName;
    int nAge;
    double dblWeight;
    //从当前行文本提取三项数据
    tsLine>>strName>>nAge>>dblWeight;

    //显示到三个编辑器
    ui->lineEditName->setText( strName );
    ui->lineEditAge->setText( tr("%1").arg( nAge ) );
    ui->lineEditWeight->setText( tr("%1").arg(dblWeight) );
}
