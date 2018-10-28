#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>//树形条目
#include <QTreeWidget>  //树形控件
#include <QStack>//栈
#include <QQueue>//队列

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
    void on_pushButtonPreorder_clicked();

    void on_pushButtonPostorder_clicked();

    void on_pushButtonMidorder_clicked();

    void on_pushButtonLevels_clicked();


private:
    Ui::Widget *ui;
    //先序遍历函数
    void PreorderByStack(QTreeWidgetItem *curItem);
    //后序遍历
    void PostorderByStack(QTreeWidgetItem *curItem);
    //中序遍历
    void MidorderByStack(QTreeWidgetItem *curItem);
    //按层遍历，队列实现
    void LevelsByQueue(QTreeWidgetItem *curItem, int curLevel);
};

#endif // WIDGET_H
