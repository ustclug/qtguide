#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator> //正则表达式验证器，检验IP
#include <QIntValidator>    //整数验证器，检验端口
#include <QFileDialog>      //打开和保存文件对话框
#include <QFile>            //读写文件

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //定义 IPv4 正则表达式，注意 "\\" 就是一个反斜杠
    QRegExp re("^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}"
               "(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    //新建正则表达式验证器
    QRegExpValidator *reVali = new QRegExpValidator(re);
    //设置给 lineEditIP
    ui->lineEditIP->setValidator(reVali);

    //新建整数验证器
    QIntValidator *intVali = new QIntValidator(0, 65535);
    //设置给 lineEditPort
    ui->lineEditPort->setValidator(intVali);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonBrowseSrc_clicked()
{
    //获取将要打开的文件名
    QString strSrcName = QFileDialog::getOpenFileName(
                this,
                tr("打开配置文件"),
                tr("."),
                tr("Text files(*.txt);;All files(*)")
                );
    if( strSrcName.isEmpty() )
    {
        //空字符串不处理，返回
        return;
    }
    else
    {
        //设置源文件名
        ui->lineEditSrcFile->setText(strSrcName);
    }
}

void Widget::on_pushButtonLoad_clicked()
{
    //获取源文件名
    QString strSrc = ui->lineEditSrcFile->text();
    if(strSrc.isEmpty())
    {
        //没设置文件名
        return;
    }
    //定义文件对象
    QFile fileIn(strSrc);
    //判断是否正确打开
    if( ! fileIn.open( QIODevice::ReadOnly ) )
    {
        //打开错误
        QMessageBox::warning(this, tr("打开错误")
                             , tr("打开文件错误：") + fileIn.errorString());
        return; //不处理文件
    }
    //读取并解析文件
    while( ! fileIn.atEnd() )
    {
        //读取一行
        QByteArray baLine = fileIn.readLine();
        baLine = baLine.trimmed();  //剔除字符串两端空白
        //判断是否为注释行
        if( baLine.startsWith('#') )
        {
            continue;   //不处理注释行
        }
        //正常的设置行，分析这一行的配置项
        AnalyzeOneLine(baLine);
    }
    //提示加载完毕
    QMessageBox::information(this, tr("加载配置"), tr("加载配置项完毕！"));
}

//分析一行配置文本，设置到对应的控件里
void Widget::AnalyzeOneLine(const QByteArray &baLine)
{
    //按等号分隔
    QList<QByteArray> list = baLine.split('=');
    if(list.count() < 2)
    {
        //分隔之后没有配置值，无法设置
        return;
    }
    //配置项名，剔除空格，变为统一的小写名称
    QByteArray optionName = list[0].trimmed().toLower();
    //配置项的值，只需要剔除空格
    QByteArray optionValue = list[1].trimmed();
    QString strValue = QString::fromLocal8Bit( optionValue );
    //判断哪个配置项
    if( "ip" == optionName )
    {
        ui->lineEditIP->setText( strValue );
        return;
    }
    if( "port" == optionName)
    {
        ui->lineEditPort->setText( strValue );
        return;
    }
    if( "hostname" == optionName )
    {
        ui->lineEditHostName->setText( strValue );
        return;
    }
    if( "workgroup" == optionName)
    {
        ui->lineEditWorkGroup->setText( strValue );
        return;
    }
    //如果有其他不相关的配置项名不处理
}

void Widget::on_pushButtonBrowseDst_clicked()
{
    //获取要保存的文件名
    QString strDstName = QFileDialog::getSaveFileName(
                this,
                tr("保存配置文件"),
                tr("."),
                tr("Text files(*.txt);;All files(*)")
                );
    if(strDstName.isEmpty())
    {
        //空字符串不处理
        return;
    }
    else
    {
        //设置要保存的文件名
        ui->lineEditDstFile->setText(strDstName);
    }
}

void Widget::on_pushButtonSave_clicked()
{
    //获取保存文件名
    QString strSaveName = ui->lineEditDstFile->text();
    //获取设置值
    QString strIP = ui->lineEditIP->text();
    QString strPort = ui->lineEditPort->text();
    QString strHostName = ui->lineEditHostName->text();
    QString strWorkGroup = ui->lineEditWorkGroup->text();
    //如果字符串有空串就不写入
    if( strSaveName.isEmpty() || strIP.isEmpty() || strPort.isEmpty()
            || strHostName.isEmpty() || strWorkGroup.isEmpty() )
    {
        QMessageBox::warning(this, tr("保存配置"),
                                 tr("需要设置好保存文件名和所有配置项数值。"));
        return;
    }
    //定义文件对象
    QFile fileOut(strSaveName);
    //打开
    if( ! fileOut.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("打开文件"),
                             tr("打开目的文件失败：") + fileOut.errorString() );
        return;
    }
    //构造字节数组写入
    //ip 行
    QByteArray baTemp = "ip = ";
    baTemp += strIP.toLocal8Bit() + "\n";
    fileOut.write( baTemp );
    //port 行
    baTemp = "port = ";
    baTemp += strPort.toLocal8Bit() + "\n";
    fileOut.write( baTemp );
    //hostname 行
    baTemp = "hostname = ";
    baTemp += strHostName.toLocal8Bit() + "\n";
    fileOut.write( baTemp );
    //workgroup 行
    baTemp = "workgroup = ";
    baTemp += strWorkGroup.toLocal8Bit() + "\n";
    fileOut.write( baTemp );
    //提示保存成功
    QMessageBox::information(this, tr("保存配置"), tr("保存配置项成功！"));
}
