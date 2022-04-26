#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //初始化控件函数
    InitControls();
}

Widget::~Widget()
{
    delete ui;
}

//初始化控件函数
void Widget::InitControls()
{
    //第 0 号预览标签页
    //新建预览标签
    m_pLabelPreview = new QLabel();
    ui->scrollArea->setWidget( m_pLabelPreview );
    m_pLabelPreview->setStyleSheet( "background-color: lightgray;" );

    //第 1 号标签页，简单显示文本
    ui->textBrowserInfo->setText( tr("用于显示图片文件信息。") );

    //第 2 号标签页，需要填充扩展名类型的组合框
    //获取支持保存的图片格式
    QList<QByteArray> listTypes = QImageWriter::supportedImageFormats();
    int nCount = listTypes.count();
    for(int i=0; i<nCount; i++)
    {
        ui->comboBoxExtFormat->addItem( listTypes[i] );
    }

    //关联列表控件的序号信号变化到堆栈控件的切换序号槽函数
    connect(ui->listWidgetIndex, SIGNAL(currentRowChanged(int)),
            ui->stackedWidget, SLOT(setCurrentIndex(int)) );
    //默认显示头一个标签页
    ui->stackedWidget->setCurrentIndex( 0 );
}


//打开图片文件
void Widget::on_pushButtonOpen_clicked()
{
    //获取文件名
    QString strFileName = QFileDialog::getOpenFileName(this, tr("打开图片文件"), "",
                           "Images (*.png *.bmp *.jpg);;All files(*)" );
    if( strFileName.isEmpty() ) //判断是否为空
    {
        return;
    }
    //文件名存在，尝试加载
    QImage imgTemp;
    if( ! imgTemp.load( strFileName ) ) //判断加载是否失败
    {
        QMessageBox::warning(this, tr("打开文件失败"), tr("加载图片数据失败，不支持该格式。"));
        return;
    }
    //成功加载，保存文件名和图片对象
    m_strImageName = strFileName;
    m_image = imgTemp;
    // 0 号标签预览
    m_pLabelPreview->setPixmap( QPixmap::fromImage( m_image ) );
    // 1 号标签页显示文件信息
    QString strInfo = m_strImageName + tr("\r\n");
    strInfo += tr("图片尺寸： %1 x %2\r\n").arg( m_image.width() ).arg( m_image.height() );
    strInfo += tr("颜色深度： %1\r\n").arg( m_image.depth() );
    //设置到文本浏览框
    ui->textBrowserInfo->setText( strInfo );
}

//转换新格式图片
void Widget::on_pushButtonConvert_clicked()
{
    //要转换的新格式
    QString strNewExt = ui->comboBoxExtFormat->currentText();
    //判断与旧的文件格式是否一样
    if( m_strImageName.endsWith( strNewExt, Qt::CaseInsensitive ) )
    {
        QMessageBox::warning(this, tr("转换图片格式"), tr("新旧图片扩展名一样，不需要转换。"));
        return;
    }
    //需要转换新格式
    QFileInfo fi( m_strImageName );
    //新名字
    QString strNewName = fi.absolutePath() + tr("/")
            +  fi.completeBaseName()  + tr(".") + strNewExt ;
    qDebug()<<strNewName;
    //转换格式保存为新文件
    if( m_image.save( strNewName ) )
    {
        QMessageBox::information(this, tr("转换图片格式"),
             tr("转换成功，新文件为：\r\n") + strNewName );
    }
    else
    {
        QMessageBox::warning(this, tr("转换图片格式"), tr("转换失败！"));
    }
}
