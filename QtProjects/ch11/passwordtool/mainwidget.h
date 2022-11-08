#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QCryptographicHash> //计算密码哈希值
#include <QMap>  //保存用户名-密码映射
#include "formchangepassword.h"  //子窗口类
#include <QListWidget>
#include <QListWidgetItem>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();    

    //更新列表控件的显示
    void UpdateListShow();

signals:
    //发送旧的用户名密码哈希给子窗口，用于修改密码
    void SendOldUserPassword(QString strUser, QByteArray baOldHash);

private slots:
    void on_pushButtonAddUser_clicked();

    void on_pushButtonChangePassword_clicked();

    void on_pushButtonDelUser_clicked();

    //手动添加的槽函数，从子窗口接收新的密码哈希值
    void RecvNewUserPassword(QString strUser, QByteArray baNewHash);

private:
    Ui::MainWidget *ui;
    //保存用户名和密码哈希值
    QMap<QString, QByteArray> m_mapUserAndHash;
    //子窗口对象指针
    FormChangePassword *m_pFormChild;
    //初始化设置
    void Init();

};

#endif // MAINWIDGET_H
