#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QIcon>        //图标
#include <QListWidget>  //列表控件以及条目
#include <QDir>         //目录浏览
#include <QFileInfo>    //文件信息

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    //条目类型枚举
    enum ITypes{ IDriver = 1999, IFolder = 2000, IFile = 2001 };

private slots:
    void on_pushButtonEnter_clicked();

    void on_pushButtonDrivers_clicked();

    void on_pushButtonParent_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    Ui::Widget *ui;

    //图标
    QIcon m_iconDriver; //分区根
    QIcon m_iconFolder; //文件夹
    QIcon m_iconFile;   //文件

    //当前目录
    QDir m_dirCur;

    //根据指定存在的目录，列举条目到列表控件
    void ShowItems(const QDir& dir);
    //根据 fi 获取文件信息，返回字符串
    QString GetFileInfo(const QFileInfo& fi);
    //根据 fi 获取文件夹信息，返回字符串
    QString GetFolderInfo(const QFileInfo& fi);
};

#endif // WIDGET_H
