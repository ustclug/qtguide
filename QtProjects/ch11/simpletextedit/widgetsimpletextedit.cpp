#include "widgetsimpletextedit.h"
#include "ui_widgetsimpletextedit.h"
#include <QDebug>
#include <QMessageBox>


WidgetSimpleTextEdit::WidgetSimpleTextEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetSimpleTextEdit)
{
    ui->setupUi(this);

    //保存文本是否被修改的状态
    m_bTextIsChanged = false;
}

WidgetSimpleTextEdit::~WidgetSimpleTextEdit()
{
    //判断文本修改状态
    if( m_bTextIsChanged )
    {
        //提示用户保存修改后的文本
        int nRet = QMessageBox::question(this, tr("保存文件询问"),
                                         tr("是否保存文件编辑的内容？"),
                                         QMessageBox::Yes|QMessageBox::No,
                                         QMessageBox::Yes);
        if( QMessageBox::Yes == nRet )
        {
            //保存一下文件
            SaveTextFile();
        }
    }
    //关闭文件
    m_file.close();
    //清空编辑框
    ui->plainTextEdit->clear();
    //删除界面
    delete ui;
}
//浏览文件
void WidgetSimpleTextEdit::on_pushButtonBrowser_clicked()
{
    //文件名
    QString strFileName;
    strFileName = QFileDialog::getOpenFileName(this, tr("选择文本文件"), tr(""),
                                               tr("Text files (*.txt);;All files (*)"));
    if(strFileName.isEmpty())
    {
        //没有文件名
        return;
    }
    //正常文件名
    ui->lineEditFileName->setText(strFileName);
}
//打开文件
void WidgetSimpleTextEdit::on_pushButtonOpenFile_clicked()
{
    //获取文件名
    QString strFileName = ui->lineEditFileName->text().trimmed();
    //判断文件名是否为空
    if( strFileName.isEmpty() )
    {
        QMessageBox::warning(this, tr("文件名检查"), tr("文件名为空，请先浏览选择文本文件。"));
        return;
    }
    //判断文本修改状态
    if( m_bTextIsChanged )
    {
        //提示用户保存修改后的文本
        int nRet = QMessageBox::question(this, tr("保存文件询问"),
                                         tr("是否保存上一个文件编辑的内容？"),
                                         QMessageBox::Yes|QMessageBox::No,
                                         QMessageBox::Yes);
        if( QMessageBox::Yes == nRet  )
        {
            //保存一下文件
            SaveTextFile();
        }
    }
    //关闭旧文件
    m_file.close();
    //清空编辑框
    ui->plainTextEdit->clear();

    //尝试打开文件
    m_file.setFileName( strFileName );
    bool bRet = m_file.open( QIODevice::ReadWrite|QIODevice::Text );
    //判断是否打开
    if( ! bRet )
    {
        //没有打开，报错
        QMessageBox::warning(this, tr("文件打开报错"),
                             tr("指定文件无法打开，请检查文件是否存在，是否有读写权限。"));
        //没有文件，没有编辑
        m_bTextIsChanged = false;
        //修改保存按钮文本，不带 *
        ui->pushButtonSaveFile->setText(tr("保存文件"));
        return;
    }
    //文件成功打开
    QByteArray baData = m_file.readAll();
    //转为 QString
    QString strText = QString::fromLocal8Bit(baData);
    //显示到文本编辑器
    ui->plainTextEdit->setPlainText(strText);
    //修改标记位，新文件，还没有编辑
    m_bTextIsChanged = false;
    //修改保存按钮文本，不带 *
    ui->pushButtonSaveFile->setText(tr("保存文件"));
    return;
}

//根据编辑框内容写入文件
void WidgetSimpleTextEdit::SaveTextFile()
{
    //获取文本
    QString strText = ui->plainTextEdit->toPlainText();
    //转为本地字节数组
    QByteArray baData = strText.toLocal8Bit();
    //保存文件
    if( m_file.isOpen() )
    {
        //文件是打开的
        m_file.resize(baData.size());  //设置文件大小
        m_file.reset(); //光标移动到开头位置
        m_file.write(baData);
        //修改标记位
        m_bTextIsChanged = false;
        //修改保存按钮文本，不带 *
        ui->pushButtonSaveFile->setText(tr("保存文件"));
    }
}
//保存文件
void WidgetSimpleTextEdit::on_pushButtonSaveFile_clicked()
{
    //判断标志位
    if( m_bTextIsChanged )
    {
        //保存文件内容
        SaveTextFile();
    }
}
//关闭文件
void WidgetSimpleTextEdit::on_pushButtonCloseFile_clicked()
{
    //判断标志位
    if( m_bTextIsChanged )
    {
        //有修改文件
        QMessageBox msgBox;
        msgBox.setText(tr("文本已修改。"));
        msgBox.setInformativeText(tr("您希望保存到文件吗？"));
        msgBox.setIcon( QMessageBox::Question );
        //三个按钮
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int nRet = msgBox.exec();
        //判断返回值，分别处理
        switch (nRet) {
        case QMessageBox::Save:
            //保存文件
            SaveTextFile();
            break;
        case QMessageBox::Discard:
            //不保存，在后面代码关闭文件
            break;
        case QMessageBox::Cancel:
            return;  //取消关闭文件
            break;
        default:
            return;  //取消关闭文件
            break;
        }
    }
    //关闭文件
    m_file.close();
    //清空编辑器
    ui->plainTextEdit->clear();
    //没有文件，没有编辑
    m_bTextIsChanged = false;
    //修改保存按钮文本，不带 *
    ui->pushButtonSaveFile->setText(tr("保存文件"));
}
//关于本程序
void WidgetSimpleTextEdit::on_pushButtonAboutThis_clicked()
{
    QMessageBox::about(this, tr("关于本程序"),
                       tr("简单文本编辑器 1.0"));
}
//关于Qt
void WidgetSimpleTextEdit::on_pushButtonAboutQt_clicked()
{
    QMessageBox::aboutQt(this, tr("关于Qt"));
}
//文本修改变化
void WidgetSimpleTextEdit::on_plainTextEdit_textChanged()
{
    //文本已修改
    m_bTextIsChanged = true;
    //修改保存按钮文本，带 *
    ui->pushButtonSaveFile->setText(tr("保存文件*"));
}
