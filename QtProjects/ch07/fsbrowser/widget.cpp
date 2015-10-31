#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>  //消息框
#include <QDesktopServices> //打开本地文件或 URL
#include <QDateTime>    //日期时间

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置结果信息框只读
    ui->plainTextEditInfo->setReadOnly(true);
    //图标
    m_iconDriver = QIcon(":/images/driver.png");
    m_iconFolder = QIcon(":/images/folder.png");
    m_iconFile = QIcon(":/images/file.png");
    //罗列分区根
    on_pushButtonDrivers_clicked();
}

Widget::~Widget()
{
    delete ui;
}

//根据目录列出条目到列表控件
void Widget::ShowItems(const QDir &dir)
{
    if( ! dir.exists())
    {
        //如果不存在就直接返回
        return;
    }
    //获取所有条目，目录排在前面
    QFileInfoList li = dir.entryInfoList(QDir::NoFilter, QDir::DirsFirst);
    //计数
    int nCount = li.count();
    //清空列表控件
    ui->listWidget->clear();
    //逐个添加
    for(int i=0; i<nCount; i++)
    {
        //不含路径的名字
        QString name = li[i].fileName();
        //判断是文件夹还是文件
        if(li[i].isDir())
        {
            //文件夹条目
            QListWidgetItem *itemFolder =
                    new QListWidgetItem(m_iconFolder, name, NULL, IFolder);
            //添加
            ui->listWidget->addItem(itemFolder);
        }
        else
        {
            //文件条目
            QListWidgetItem *itemFile =
                    new QListWidgetItem(m_iconFile, name, NULL, IFile);
            //添加
            ui->listWidget->addItem(itemFile);
        }
    }
}

void Widget::on_pushButtonEnter_clicked()
{
    //新目录
    QString strNewDir = ui->lineEditDir->text();
    QDir dirNew(strNewDir);
    //判断新目录是否存在
    if( dirNew.exists() )
    {
        //存在目录，使用权威路径，避免 Windows 系统进入的 "/" 的 bug
        m_dirCur = QDir( dirNew.canonicalPath() );
        //更新列表控件
        ShowItems(m_dirCur);
        //使用绝对路径显示
        ui->lineEditDir->setText(m_dirCur.absolutePath());
        //结果信息
        ui->plainTextEditInfo->setPlainText(tr("进入成功"));
    }
    else
    {
        //不存在目录
        QMessageBox::warning(this, tr("目录不存在"), tr("目录 %1 不存在").arg(strNewDir));
    }
}

void Widget::on_pushButtonDrivers_clicked()
{
    //获取磁盘根分区
    QFileInfoList fil = QDir::drives();
    //手动添加本程序资源根
    fil.append( QFileInfo(":/") );
    //分区根计数
    int nCount = fil.count();
    //清空列表控件
    ui->listWidget->clear();
    //逐个添加条目
    for(int i=0; i<nCount; i++)
    {
        //分区根路径，全部用绝对路径显示
        QString strPath = fil[i].absolutePath();
        //新建条目
        QListWidgetItem *item =
                new QListWidgetItem(m_iconDriver, strPath, NULL, IDriver);
        //添加到列表控件
        ui->listWidget->addItem(item);
    }
    //当前目录设为系统根
    m_dirCur = QDir::root();
    //单行编辑控件文件
    ui->lineEditDir->setText( m_dirCur.absolutePath() );
    //结果显示
    ui->plainTextEditInfo->setPlainText(tr("已获取分区根"));
}

void Widget::on_pushButtonParent_clicked()
{
    if( m_dirCur.cdUp() )
    {
        //单行编辑控件更新，显示绝对路径
        ui->lineEditDir->setText( m_dirCur.absolutePath() );
        //列表更新
        ShowItems(m_dirCur);
        ui->plainTextEditInfo->setPlainText(tr("进入父目录成功"));
    }
    else
    {
        ui->plainTextEditInfo->setPlainText(tr("已到根目录"));
    }
}

void Widget::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //判断 item 的类型
    int theType = item->type();

    if( IDriver == theType )    //如果是分区根
    {
        //根路径
        QString strFullPath = item->text();
        //设置当前目录
        m_dirCur = QDir( strFullPath );
        //更新单行编辑控件，显示绝对路径
        ui->lineEditDir->setText( m_dirCur.absolutePath() );
        //更新列表控件
        ShowItems(m_dirCur);
    }
    else if( IFolder == theType )   //如果是文件夹
    {
        //先对 . 和 .. 做排除
        QString strName = item->text();
        if( tr(".") == strName)
        {
            //不需要处理，还是当前目录
            return;
        }
        else if ( tr("..") == strName )
        {
            //切换父目录
            on_pushButtonParent_clicked();
            //返回
            return;
        }
        //正常的子文件夹处理
        //完整路径
        QString strFullPath = m_dirCur.absolutePath() + tr("/") + strName;
        strFullPath = QDir::cleanPath(strFullPath); //清理多余的斜杠
        //切换路径
        m_dirCur = QDir(strFullPath);
        //更新单行编辑控件，显示绝对路径
        ui->lineEditDir->setText(m_dirCur.absolutePath());
        //更新列表控件
        ShowItems(m_dirCur);
    }
    else    //普通文件
    {
        //拼接出路径字符串
        QString strFilePath = m_dirCur.absolutePath() + tr("/")  + item->text();
        strFilePath = QDir::cleanPath(strFilePath); //清理多余的斜杠
        //如果不是内嵌资源文件，是本地文件系统的
        if( ! strFilePath.startsWith( tr(":") ))
        {
            //调用系统浏览器打开
            QDesktopServices::openUrl( QUrl::fromLocalFile(strFilePath) );
        }
    }
}

void Widget::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    //如果当前条目为空则返回
    if( NULL == current )
    {
        return;
    }
    //条目信息对象
    QFileInfo fi;
    //记录信息字符串
    QString strResult;
    //条目类型
    int theType = current->type();
    //条目名称
    QString strName = current->text();
    //判断类型
    if( IDriver == theType )    //分区根
    {
        //分区根路径
        fi = QFileInfo( strName );
        if( strName.startsWith( tr(":") ) )
        {
            strResult += tr("资源根 %1").arg(strName); //显示绝对路径
        }
        else
        {
            strResult += tr("分区根 %1").arg(strName); //显示绝对路径
        }
    }
    else if( IFolder == theType )   //文件夹
    {
        //完整路径
        QString strFullPath = m_dirCur.absolutePath() + tr("/") + strName;
        strFullPath = QDir::cleanPath(strFullPath); //清理多余的斜杠
        strResult += tr("文件夹 %1\r\n").arg(strFullPath); //显示绝对路径
        //获取信息，添加到结果串
        fi = QFileInfo(strFullPath);        
        strResult += GetFolderInfo(fi);
    }
    else    //文件
    {
        //完整文件名
        QString strFilePath = m_dirCur.absolutePath() + tr("/") + strName;
        strFilePath = QDir::cleanPath(strFilePath); //清理多余的斜杠
        strResult += tr("文件 %1\r\n").arg(strFilePath); //显示绝对路径
        //获取文件信息，添加到结果串
        fi = QFileInfo(strFilePath);
        strResult += GetFileInfo(fi);
    }
    //显示结果信息
    ui->plainTextEditInfo->setPlainText(strResult);
}

//获取文件夹信息字符串
QString Widget::GetFolderInfo(const QFileInfo &fi)
{
    QString strResult;  //用于返回的串
    //判断文件夹信息
    if(fi.isReadable()) //是否可读
    {
        strResult += tr("可读：是\r\n");
    }
    else
    {
        strResult += tr("可读：否\r\n");
    }
    if(fi.isWritable()) //是否可写
    {
        strResult += tr("可写：是\r\n");
    }
    else
    {
        strResult += tr("可写：否\r\n");
    }
    //时间
    QDateTime dtCreate = fi.created();
    QDateTime dtModify = fi.lastModified();
    strResult += tr("创建时间：%1\r\n").arg(dtCreate.toString("yyyy-MM-dd HH:mm:ss"));
    strResult += tr("修改时间：%1\r\n").arg(dtModify.toString("yyyy-MM-dd HH:mm:ss"));

    //返回
    return strResult;
}

//返回文件信息字符串
QString Widget::GetFileInfo(const QFileInfo &fi)
{
    QString strResult;  //用于返回的串
    //判断文件信息
    if(fi.isReadable())
    {
        strResult += tr("可读：是\r\n");
    }
    else
    {
        strResult += tr("可读：否\r\n");
    }
    if(fi.isWritable())
    {
        strResult += tr("可写：是\r\n");
    }
    else
    {
        strResult += tr("可写：否\r\n");
    }
    if(fi.isExecutable())
    {
        strResult += tr("可执行：是\r\n");
    }
    else
    {
        strResult += tr("可执行：否\r\n");
    }
    //类型
    strResult += tr("类型：%1\r\n").arg(fi.suffix());
    //大小
    strResult += tr("大小：%1 B\r\n").arg(fi.size());
    //时间
    QDateTime dtCreate = fi.created();
    QDateTime dtModify = fi.lastModified();
    strResult += tr("创建时间：%1\r\n").arg(dtCreate.toString("yyyy-MM-dd HH:mm:ss"));
    strResult += tr("修改时间：%1\r\n").arg(dtModify.toString("yyyy-MM-dd HH:mm:ss"));

    //返回
    return strResult;
}
