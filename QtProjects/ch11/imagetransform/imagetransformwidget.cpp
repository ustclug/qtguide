#include "imagetransformwidget.h"
#include "ui_imagetransformwidget.h"
#include <QDebug>
#include <QMessageBox>

ImageTransformWidget::ImageTransformWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageTransformWidget)
{
    ui->setupUi(this);
    //初始化
    Init();
}

ImageTransformWidget::~ImageTransformWidget()
{
    delete m_pResizeDlg; m_pResizeDlg = NULL;
    delete m_pRotateDlg; m_pRotateDlg = NULL;
    delete ui;
}

//初始化函数
void ImageTransformWidget::Init()
{
    //新建标签对象
    m_pLabelImage = new QLabel();
    //标签内容对齐方式，左上角对齐
    m_pLabelImage->setAlignment( Qt::AlignLeft | Qt::AlignTop );
    m_pLabelImage->setStyleSheet( "background-color: lightgray;" ) ;
    //把标签设置给滚动区域，该标签隶属于滚动区域，滚动区域销毁时，也销毁该标签
    ui->scrollArea->setWidget(m_pLabelImage);

    //新建缩放尺寸对话框
    m_pResizeDlg = new ResizeImageDialog(this);
    //主窗口发送旧尺寸给子对话框
    connect(this, SIGNAL(SendOldSize(int,int)),
            m_pResizeDlg, SLOT(RecvOldSize(int,int)) );
    //子对话框发送新尺寸给主窗口
    connect(m_pResizeDlg, SIGNAL(SendNewSize(int,int)),
            this, SLOT(RecvNewSizeAndResize(int,int)) );

    //新建旋转图片对话框
    m_pRotateDlg = new RotateImageDialog(this);
    //模态对话框，要求用户输入角度后，由 exec() 函数返回角度，不需要信号和槽传递
    //使用子窗口的公有函数也可以进行数据传递
}

//打开图片
void ImageTransformWidget::on_pushButtonOpen_clicked()
{
    //获取图片文件名
    QString strFile = QFileDialog::getOpenFileName(this, tr("打开图片文件"),
                           tr(""), tr("Image files(*.png *.jpg *.bmp)"));
    if( strFile.isEmpty() )
    {
        return; //没有文件名
    }
    //正常图片
    bool bLoadOK = m_image.load( strFile );
    if( ! bLoadOK )
    {
        QMessageBox::warning(this, tr("加载图片文件"), tr("加载图片文件失败，请检查文件格式。"));
        return;
    }
    //加载正常，保存文件名
    m_strFileName = strFile;
    //将新图片设置给标签显示
    m_pLabelImage->setPixmap( m_image );
    //窗口标题栏设置为文件名
    setWindowTitle( tr("预览文件为 %1").arg(m_strFileName) );
}

//缩放图片
void ImageTransformWidget::on_pushButtonResize_clicked()
{
    if( m_image.isNull() ) //没有图片
    {
        return;
    }
    //有图片时，发送旧尺寸给子对话框
    emit SendOldSize(m_image.width(), m_image.height());
    //显示子对话框
    m_pResizeDlg->show();
    m_pResizeDlg->raise();
}

//收到新尺寸后进行缩放
void ImageTransformWidget::RecvNewSizeAndResize(int nNewWidth, int nNewHeight)
{
    //如果尺寸没变，直接返回
    if( (m_image.width() == nNewWidth) &&
        (m_image.height() == nNewHeight) )
    {
        return;
    }
    //缩放到新尺寸
    QPixmap imgNew = m_image.scaled(nNewWidth, nNewHeight);
    //存到成员变量
    m_image = imgNew;
    //显示新图片
    m_pLabelImage->setPixmap( m_image );
}

//旋转图片
void ImageTransformWidget::on_pushButtonRotate_clicked()
{
    if( m_image.isNull() ) //没有图片
    {
        return;
    }
    int nAngle = m_pRotateDlg->exec();
    if( 0 == nAngle )
    {
        return; // 没旋转
    }
    //旋转变换矩阵
    QMatrix mxRotate;
    mxRotate.rotate( nAngle );
    //执行旋转变换
    QPixmap imgNew = m_image.transformed( mxRotate );
    //保存到成员
    m_image = imgNew;
    //显示
    m_pLabelImage->setPixmap(m_image);
}
