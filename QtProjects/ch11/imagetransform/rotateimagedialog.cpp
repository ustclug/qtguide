#include "rotateimagedialog.h"
#include "ui_rotateimagedialog.h"

RotateImageDialog::RotateImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RotateImageDialog)
{
    ui->setupUi(this);
    //初始化函数
    Init();
}

RotateImageDialog::~RotateImageDialog()
{
    delete ui;
}

//初始化函数
void RotateImageDialog::Init()
{
    //一圈的范围
    ui->spinBoxAngle->setRange(0, 360);
    ui->spinBoxAngle->setSuffix( tr("°") ); //单位：度
    //设置标题栏
    setWindowTitle(tr("旋转图片"));
}

//执行旋转
void RotateImageDialog::on_pushButtonRotating_clicked()
{
    int nAngle = ui->spinBoxAngle->value();
    done(nAngle);  //角度由 exec() 返回
}
