#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>  //消息框
#include <QIcon>        //图标类
#include <QPixmap>      //像素图的类

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //选中一个默认的单选按钮（如果不设置，那么初始时都处于不选中状态）
    ui->radioButtonMan->setChecked(true);

    //添加组合框条目
    ui->comboBox->addItem( QIcon(":/images/triangle.png"),
                           tr("锐意进取"));
    ui->comboBox->addItem( QIcon(":/images/rectangle.png"),
                           tr("大方得体"));
    ui->comboBox->addItem( QIcon(":/images/polygon.png"),
                           tr("灵活善变"));
    ui->comboBox->addItem( QIcon(":/images/ellipse.png"),
                           tr("精明圆滑"));
    //组合框默认选中第 0 号条目，不用设置
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonCommit_clicked()
{
    QString strResult;
    //添加姓名
    strResult += tr("姓名：%1\r\n").arg( ui->lineEditName->text() );
    //添加性别
    if( ui->radioButtonMan->isChecked() )
    {
        strResult += tr("性别：男\r\n");
    }
    else
    {
        strResult += tr("性别：女\r\n");
    }
    //添加性格特质
    strResult += tr("性格特质：%1\r\n").arg( ui->comboBox->currentText() );

    //取出性格特质条目的像素图
    int nIndex = ui->comboBox->currentIndex();      //当前条目序号
    QIcon icon = ui->comboBox->itemIcon( nIndex );  //当前条目图标对象
    QPixmap pixmap = icon.pixmap(QSize(32, 32));    //从图标对象取出一个 32*32 的像素图

    //自定义消息框
    QMessageBox theMessageBox;
    //设置标题
    theMessageBox.setWindowTitle( tr("人员信息") );
    //设置消息
    theMessageBox.setText(strResult);
    //设置显示的按钮
    theMessageBox.setStandardButtons(QMessageBox::Ok);
    //设置图标像素图
    theMessageBox.setIconPixmap(pixmap);
    //弹窗显示
    theMessageBox.exec();   //模态显示
}

void Widget::on_pushButtonCancel_clicked()
{
   int ret =  QMessageBox::information(this,
                             tr("退出"),
                             tr("您确定要退出程序吗？"),
                             QMessageBox::Yes|QMessageBox::No);
   if(QMessageBox::Yes == ret)
   {
       //确认退出
       this->close();
   }
   else
   {
       //不退出，不需要操作
   }
}
