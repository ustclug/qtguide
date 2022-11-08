#ifndef FORMCHANGEPASSWORD_H
#define FORMCHANGEPASSWORD_H

#include <QWidget>
#include <QCryptographicHash> //计算密码哈希值

namespace Ui {
class FormChangePassword;
}

class FormChangePassword : public QWidget
{
    Q_OBJECT

public:
    explicit FormChangePassword(QWidget *parent = 0);
    ~FormChangePassword();

signals:
    //发送新的密码哈希给主窗口
    void SendNewUserPassword(QString strUser, QByteArray baNewHash);

private slots:
    void on_pushButtonChange_clicked();

    //手动添加的槽函数，从主窗口接收旧的用户名和密码哈希
    void RecvOldUserPassword(QString strUser, QByteArray baOldHash);

private:
    Ui::FormChangePassword *ui;
    //初始化设置
    void Init();
    //保存用户名和密码哈希值
    QString m_strUser;
    QByteArray m_baOldHash;
};

#endif // FORMCHANGEPASSWORD_H
