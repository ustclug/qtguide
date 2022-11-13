#include "resizeimagedialog.h"
#include "ui_resizeimagedialog.h"

ResizeImageDialog::ResizeImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResizeImageDialog)
{
    ui->setupUi(this);
    //初始化
    Init();
}

ResizeImageDialog::~ResizeImageDialog()
{
    delete ui;
}

//初始化函数
void ResizeImageDialog::Init()
{
    //旧尺寸编辑器设置为只读
    ui->lineEditOldSize->setReadOnly(true);
    ui->lineEditOldSize->setStyleSheet( "background-color: lightgray;" );
    //限定新的宽度高度数值范围
    ui->spinBoxWidthNew->setRange(1, 10000);
    ui->spinBoxHeightNew->setRange(1, 10000);
    //设置标题栏
    setWindowTitle(tr("缩放图片尺寸"));
}

//接收图片旧尺寸并显示
void ResizeImageDialog::RecvOldSize(int nOldWidth, int nOldHeight)
{
    //构造旧尺寸字符串并显示
    QString strOldSize = tr("%1 X %2").arg(nOldWidth).arg(nOldHeight);
    ui->lineEditOldSize->setText( strOldSize );
    //把两个旋钮框默认值改为现在的数值
    ui->spinBoxWidthNew->setValue(nOldWidth);
    ui->spinBoxHeightNew->setValue(nOldHeight);
}

//设置新尺寸，交给主窗口完成缩放
void ResizeImageDialog::on_pushButtonSetNewSize_clicked()
{
    int nNewWidth = ui->spinBoxWidthNew->value();
    int nNewHeight = ui->spinBoxHeightNew->value();
    //触发信号
    emit SendNewSize(nNewWidth, nNewHeight);
    //更新尺寸字符串
    QString strSize = tr("%1 X %2").arg(nNewWidth).arg(nNewHeight);
    ui->lineEditOldSize->setText( strSize );
}
