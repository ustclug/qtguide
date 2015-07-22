#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QCryptographicHash>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置密码框的显示模式
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
}

Widget::~Widget()
{
    delete ui;
}
//登录按钮
void Widget::on_pushButtonLogin_clicked()
{
    //判断用户名密码是否为空
    if( ui->lineEditUser->text().isEmpty()
            || ui->lineEditPassword->text().isEmpty() )
    {
        QMessageBox::warning(this, tr("警告信息"), tr("用户名或密码为空，不能登录。"));
        return;
    }
    //用户名
    m_strUser = ui->lineEditUser->text();
    //计算密码 Hash
    m_passwordHash = QCryptographicHash::hash( ui->lineEditPassword->text().toUtf8(),
                                               QCryptographicHash::Sha3_256 );
    //构造消息
    //添加用户名
    QString strMsg = tr("用户名：") + m_strUser + tr("\r\n") + tr("密码 Hash：");
    //把每个 Hash 字节转成一对十六进制字符显示
    // 256 bit 对应 32 字节，变成 64 个十六进制字符打印
    strMsg += m_passwordHash.toHex();

    //打印消息
    qDebug()<<strMsg;
    //弹窗显示，注意：实际应用中会将用户名和密码 Hash 与数据库或配置文件里的做比较，而不是弹窗
    QMessageBox::information(this, tr("用户信息"), strMsg);

}

//退出按钮
void Widget::on_pushButtonExit_clicked()
{
    this->close();
}
