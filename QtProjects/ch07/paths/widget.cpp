#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QDir>         //目录浏览类
#include <QFileInfo>    //文件信息类
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置结果文本框为只读
    ui->plainTextEditResult->setReadOnly(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonGetWorkPath_clicked()
{
    //获取程序当前工作路径
    QString strWorkPath = QDir::currentPath();
    //显示到单行编辑控件
    ui->lineEditWorkPath->setText( strWorkPath );
}

void Widget::on_pushButtonSetWorkPath_clicked()
{
    //获取单行编辑器里的路径
    QString strNewPath = ui->lineEditWorkPath->text();
    //判断字符串是否为空
    if(strNewPath.length() < 1)
    {
        return;
    }
    //判断路径是否存在
    QDir dirNew(strNewPath);
    QString strResult;  //操作结果显示
    if( dirNew.exists() )
    {
        //存在该路径，设置为工作路径
        bool bRes = QDir::setCurrent( dirNew.path() );
        if( !bRes )
        {
            //设置工作路径失败
            strResult = tr("设置工作路径为 %1 失败。").arg(strNewPath);
            QMessageBox::warning(this, tr("设置错误"), strResult);
        }
        else
        {
            //设置成功
            strResult = tr("设置工作路径成功，新的路径为：\r\n%1").arg( QDir::currentPath() );
        }
    }
    else    //新路径不存在
    {
        strResult = tr("设置工作路径为 %1 失败，该路径不存在！").arg(strNewPath);
        QMessageBox::warning(this, tr("路径不存在"), strResult);
    }
    //显示结果信息
    ui->plainTextEditResult->setPlainText(strResult);
}

void Widget::on_pushButtonEnvPaths_clicked()
{
    QString strWorkPath = QDir::currentPath();  //应用程序的工作目录
    QString strAppPath = QCoreApplication::applicationDirPath();//可执行程序目录
    QString strHomePath = QDir::homePath();     //用户的主文件夹
    QString strRootPath = QDir::rootPath();     //应用程序所在文件系统的根分区
    QString strTempPath = QDir::tempPath();     //操作系统里默认的临时文件目录

    //构造结果串
    QString strResult;
    strResult += tr("工作路径：%1\r\n").arg(strWorkPath);
    strResult += tr("可执行程序目录：%1\r\n\r\n").arg(strAppPath);
    strResult += tr("用户主文件夹：%1\r\n").arg(strHomePath);
    strResult += tr("系统根目录：%1\r\n").arg(strRootPath);
    strResult += tr("临时目录：%1\r\n").arg(strTempPath);
    //显示
    ui->plainTextEditResult->setPlainText(strResult);
}
//    qDebug()<<QCoreApplication::applicationFilePath();

void Widget::on_pushButtonExist_clicked()
{
    //获取测试路径
    QString strTestPath = ui->lineEditTestPath->text();
    //判断字符串是否为空
    if(strTestPath.length() < 1)
    {
        return;
    }
    //不带参数的 dirWork 默认就是程序工作路径！
    QDir dirWork;
    //结果字符串
    QString strResult;
    //判断存在性，不带参数的 dirWork.exists() 只能判断文件夹
    //这里既需要判断文件夹，也要判断文件，因此把 strTestPath 作为参数传入来判断
    if( dirWork.exists( strTestPath ) )
    {
        strResult = tr("路径 %1 是存在的。").arg(strTestPath);
    }
    else
    {
        strResult = tr("路径 %1 不存在。").arg(strTestPath);
    }
    //显示
    ui->plainTextEditResult->setPlainText(strResult);
}

void Widget::on_pushButtonIsRelative_clicked()
{
    //获取测试路径
    QString strTestPath = ui->lineEditTestPath->text();
    //判断字符串是否为空
    if(strTestPath.length() < 1)
    {
        return;
    }
    //构造目录浏览对象
    QDir dirTest(strTestPath);
    //结果字符串
    QString strResult;
    //判断相对性
    if( dirTest.isRelative() )
    {
        //是相对路径
        strResult = tr("路径 %1 是相对路径").arg(strTestPath);
    }
    else
    {
        //是绝对路径
        strResult = tr("路径 %1 是绝对路径").arg(strTestPath);
    }
    //显示
    ui->plainTextEditResult->setPlainText(strResult);
}

void Widget::on_pushButtonShowAbsolute_clicked()
{
    //获取测试路径
    QString strTestPath = ui->lineEditTestPath->text();
    //判断字符串是否为空
    if(strTestPath.length() < 1)
    {
        return;
    }
    //构建目录浏览对象
    QDir dirTest(strTestPath);
    //结果字符串
    QString strResult;
    //获取绝对路径
    strResult = tr("测试路径 %1 的绝对路径为：%2")
            .arg(strTestPath).arg( dirTest.absolutePath() );
    //显示
    ui->plainTextEditResult->setPlainText(strResult);


}
    //qDebug()<<QFileInfo(strTestPath).absolutePath();



