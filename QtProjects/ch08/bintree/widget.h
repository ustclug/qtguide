#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTreeWidgetItem> //树形条目
#include <QTreeWidget>  //树形控件
#include <QTreeWidgetItemIterator> //树形迭代器

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

    void on_pushButtonIterator_clicked();

    void on_pushButtonLevels_clicked();

private:
    Ui::Widget *ui;
    //先序遍历递归函数，只打印字符，不需要返回值
    void PreorderTraversal(QTreeWidgetItem *curItem);
    //后序遍历递归函数
    void PostorderTraversal(QTreeWidgetItem *curItem);
    //中序遍历递归函数
    void MidorderTraversal(QTreeWidgetItem *curItem);
    //迭代器遍历
    void IteratorTraversal(QTreeWidgetItem *curItem);
    //按层遍历
    void LevelsTraversal(QTreeWidgetItem *curItem);
};

#endif // WIDGET_H
