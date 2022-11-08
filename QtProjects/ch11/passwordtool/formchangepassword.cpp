#include "formchangepassword.h"
#include "ui_formchangepassword.h"
#include <QMessageBox>
#include <QDebug>

FormChangePassword::FormChangePassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormChangePassword)
{
    ui->setupUi(this);
    //初始化
    Init();
}

FormChangePassword::~FormChangePassword()
{
    delete ui;
}

//初始化设置
void FormChangePassword::Init()
{
    //修改窗口标题栏
    setWindowTitle( tr("修改用户密码") );
    //设置密码隐藏
    ui->lineEditOldPassword->setEchoMode( QLineEdit::Password );
    ui->lineEditNewPassword->setEchoMode( QLineEdit::Password );
    ui->lineEditNewPassword2->setEchoMode( QLineEdit::Password );

    //用户名为只读
    ui->lineEditUser->setReadOnly(true);
    ui->lineEditUser->setStyleSheet( "background-color: rgb(200,200,255);" );

    //工具提示
    ui->lineEditOldPassword->setToolTip( tr("旧密码验证成功才能修改为新密码。") );
}

//手动添加的槽函数，从主窗口接收旧的用户名和密码哈希
void FormChangePassword::RecvOldUserPassword(QString strUser, QByteArray baOldHash)
{
    //存到成员变量
    m_strUser = strUser;
    m_baOldHash = baOldHash;
    //设置用户名
    ui->lineEditUser->setText(m_strUser);
    //清空密码编辑框
    ui->lineEditOldPassword->clear();
    ui->lineEditNewPassword->clear();
    ui->lineEditNewPassword2->clear();
}

//修改密码操作
void FormChangePassword::on_pushButtonChange_clicked()
{
    //先获取三个密码字符串
    QString strOldPassword = ui->lineEditOldPassword->text().trimmed();
    QString strNewPassword = ui->lineEditNewPassword->text().trimmed();
    QString strNewPassword2 = ui->lineEditNewPassword2->text().trimmed();
    //判断密码字符串是否为空
    if( strOldPassword.isEmpty() || strNewPassword.isEmpty()
            || strNewPassword2.isEmpty() )
    {
        QMessageBox::information(this, tr("密码框检查"), tr("三个密码都不能为空。"));
        return;
    }
    if( strNewPassword != strNewPassword2 )
    {
        QMessageBox::information(this, tr("新密码检查"), tr("两个新密码不一致。"));
        return;
    }
    //根据旧密码计算旧的哈希值
    QByteArray baOldHashCheck = QCryptographicHash::hash(strOldPassword.toUtf8(),
                                                    QCryptographicHash::Sha256 );
    //转为 Hex 字符串
    baOldHashCheck = baOldHashCheck.toHex();
    if( baOldHashCheck != m_baOldHash )
    {
        QMessageBox::information(this, tr("旧密码检查"), tr("输入的旧密码不正确，不能修改密码。"));
        return;
    }
    //旧密码正确了
    QByteArray baNewHash = QCryptographicHash::hash(strNewPassword.toUtf8(),
                                         QCryptographicHash::Sha256 );
    //转为Hex字符串
    baNewHash = baNewHash.toHex();
    //发送信号，后面交给主窗口处理
    emit SendNewUserPassword(m_strUser, baNewHash);
}

