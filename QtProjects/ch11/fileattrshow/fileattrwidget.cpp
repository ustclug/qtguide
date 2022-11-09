#include "fileattrwidget.h"
#include "ui_fileattrwidget.h"
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>

FileAttrWidget::FileAttrWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileAttrWidget)
{
    ui->setupUi(this);
    //初始化函数
    Init();
}

FileAttrWidget::~FileAttrWidget()
{
    //删除子窗口
    delete m_pPreviewWnd;   m_pPreviewWnd = NULL;
    delete ui;
}
//初始化函数
void FileAttrWidget::Init()
{
    //单行编辑器都设置为只读
    ui->lineEditFullName->setReadOnly(true);
    ui->lineEditShortName->setReadOnly(true);
    ui->lineEditFileSize->setReadOnly(true);
    ui->lineEditTimeCreated->setReadOnly(true);
    ui->lineEditTimeRead->setReadOnly(true);
    ui->lineEditTimeModified->setReadOnly(true);

    //指针初始化为 NULL
    m_pPreviewWnd = NULL;
    //新建子窗口
    m_pPreviewWnd = new TabPreview(NULL);
    //设置子窗口标题栏
    m_pPreviewWnd->setWindowTitle(tr("预览文件"));

    //关联信号和槽函数，传递文件名给子窗口
    connect(this, SIGNAL(fileNameChanged(QString)),
            m_pPreviewWnd, SLOT(onFileNameChanged(QString)) );
}

//选择文件
void FileAttrWidget::on_pushButtonSelectFile_clicked()
{
    QString strName = QFileDialog::getOpenFileName(this, tr("选择文件"),
                      tr(""), tr("All files(*)") );
    strName = strName.trimmed();    //剔除空格
    if( strName.isEmpty() )
    {
        return; //名字为空
    }
    //获取了正常文件名
    m_strFileName = strName;
    m_fileInfo.setFile( m_strFileName );
    //文件大小
    qint64 nFileSize = m_fileInfo.size();

    //设置全名、短名、大小三个编辑框
    ui->lineEditFullName->setText( m_strFileName );
    ui->lineEditShortName->setText( m_fileInfo.fileName() );
    ui->lineEditFileSize->setText( tr("%1 字节").arg(nFileSize) );

    //三个时间字符串
    QString strTimeCreated = m_fileInfo.created().toString("yyyy-MM-dd  HH:mm:ss");
    QString strTimeRead = m_fileInfo.lastRead().toString("yyyy-MM-dd  HH:mm:ss");
    QString strTimeModified = m_fileInfo.lastModified().toString("yyyy-MM-dd  HH:mm:ss");
    //设置时间编辑框
    ui->lineEditTimeCreated->setText( strTimeCreated );
    ui->lineEditTimeRead->setText( strTimeRead );
    ui->lineEditTimeModified->setText( strTimeModified );

    //触发文件名称修改的信号
    emit fileNameChanged(m_strFileName);
}

//预览文件
void FileAttrWidget::on_pushButtonPreview_clicked()
{
    if( m_strFileName.isEmpty() )
    {
        //没有文件名，没有预览
        return;
    }
    //模态窗口弹出示范
    if( m_pPreviewWnd->isVisible() )
    {
        //窗口处于已经显示，需要先隐藏，设置模态属性后重新显示
        m_pPreviewWnd->hide();
    }
    //应用程序级别的模态显示
    m_pPreviewWnd->setWindowModality( Qt::ApplicationModal );
    m_pPreviewWnd->show();
    //模态显示会强制占据前台焦点，只有用户关闭模态窗口才会回到主窗口
}
