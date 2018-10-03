#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>//树形条目
#include <QTreeWidget> //树形控件
#include <QFile> //文件类
#include <QDataStream> //用数据流保存树

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButtonAddTop_clicked();

    void on_pushButtonAddChild_clicked();

    void on_pushButtonEditHeader_clicked();

    void on_pushButtonSaveFile_clicked();

    void on_pushButtonClearTree_clicked();

    void on_pushButtonLoadFile_clicked();

private:
    Ui::Widget *ui;
    //文件对象，用于保存或打开
    QFile m_file;
    //数据流对象
    QDataStream m_ds;
    //保存树的先序递归函数，自顶向下保存
    void SaveTree( QTreeWidgetItem *curItem );
    //加载树的先序递归函数，自顶向下创建树形结构
    void LoadTree( QTreeWidgetItem *curItem );
    //加载时的列数限制
    static const int MAX_COLS = 1000;
};

#endif // WIDGET_H
