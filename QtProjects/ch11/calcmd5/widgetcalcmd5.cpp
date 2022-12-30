#include "widgetcalcmd5.h"
#include "ui_widgetcalcmd5.h"

WidgetCalcMD5::WidgetCalcMD5(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetCalcMD5)
{
    ui->setupUi(this);
}

WidgetCalcMD5::~WidgetCalcMD5()
{
    delete ui;
}

//浏览要打开的文件
void WidgetCalcMD5::on_pushButtonBrowser_clicked()
{
    QString strFileName = QFileDialog::getOpenFileName(
                this, tr("选择文件"), "", "All files (*)");
    if( strFileName.isEmpty() )
    {
        m_dlgErrorMsg.showMessage( tr("文件名为空，未选择文件！") );
        return;
    }
    //文件名非空
    m_strFileName = strFileName;
    ui->lineEditFileName->setText( m_strFileName );
    //清空旧的文本框
    ui->textBrowserInfo->clear();
}

//槽函数，计算文件 MD5
void WidgetCalcMD5::on_pushButtonCalcMD5_clicked()
{
    //先从编辑框获取文件名
    QString strFileName = ui->lineEditFileName->text().trimmed();
    if( strFileName.isEmpty() )
    {
        m_dlgErrorMsg.showMessage( tr("文件名编辑框内容为空！") );
        return;
    }
    //文件名非空
    m_strFileName = strFileName;
    //文件对象
    QFile fileIn(m_strFileName);
    //尝试打开
    if( ! fileIn.open(QIODevice::ReadOnly) )
    {
        m_dlgErrorMsg.showMessage( tr("打开指定文件失败！") );
        return;
    }
    //正常打开文件，检查文件大小
    qint64 nFileSize = fileIn.size();
    if( nFileSize < 1 )
    {
        m_dlgErrorMsg.showMessage( tr("文件大小为 0，没有数据！") );
        fileIn.close();
        return;
    }
    //计算MD5值
    QByteArray baMD5 = CalcFileMD5( fileIn, nFileSize );
    //构造信息字符串
    QString strInfo = tr("文件名：") + m_strFileName;
    strInfo += tr("\n文件大小：%1 字节").arg(nFileSize);
    strInfo += tr("\nMD5校验值：\n");
    strInfo += baMD5.toHex().toUpper();
    //设置给文本框
    ui->textBrowserInfo->setText(strInfo);
    //关闭文件
    fileIn.close();
}

//计算文件对象 MD5 值
QByteArray WidgetCalcMD5::CalcFileMD5( QFile &fileIn, qint64 nFileSize )
{
    //返回的MD5字节数组
    QByteArray baRet;
    //定义算法对象
    QCryptographicHash algMD5(QCryptographicHash::Md5);
    //数据块
    QByteArray baCurData;
    //判断
    if( nFileSize < 100*1000 ) //小于 100K
    {
        //一次读取全部数据计算MD5
        baCurData = fileIn.readAll();
        algMD5.addData(baCurData);
        baRet = algMD5.result();
        return baRet;
    }
    //如果是大于 100K，分块读取数据
    qint64 oneBlockSize = nFileSize / 100; //可能有余数
    int nBlocksCount = 100;
    if( nFileSize % oneBlockSize != 0 )
    {
        //存在余数除不尽
        nBlocksCount += 1;
    }

    //先设置进度对话框，然后开始循环读取文件内容
    QProgressDialog dlgProgress(tr("正在计算MD5 ..."), tr("取消计算"),
                    0, nBlocksCount, this);
    dlgProgress.setWindowModality( Qt::WindowModal );
    dlgProgress.setMinimumDuration( 0 ); //总是显示对话框
    //循环处理
    for(int i=0; i<nBlocksCount; i++)
    {
        //设置进度，自动显示对话框
        dlgProgress.setValue(i);
        //判断是否取消
        if( dlgProgress.wasCanceled() )
        {
            break;
        }
        //正常读取数据块，计算MD5
        baCurData = fileIn.read(oneBlockSize);
        algMD5.addData(baCurData);
    }
    //进度没有取消，获取正常MD5结果
    if( ! dlgProgress.wasCanceled() )
    {
        baRet = algMD5.result();
    }
    //结束进度
    dlgProgress.setValue( nBlocksCount );
    //返回MD5字节数组
    return baRet;
}

