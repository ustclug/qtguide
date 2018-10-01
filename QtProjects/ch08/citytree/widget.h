#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTreeWidgetItem> //条目类的头文件
#include <QTreeWidget> //树形控件头文件

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

    void on_pushButtonDelLeaf_clicked();

    void on_pushButtonDelSubtree_clicked();

private:
    Ui::Widget *ui;
    //递归删除节点子树
    void RemoveSubtree(QTreeWidgetItem *curLevelItem);

};

#endif // WIDGET_H
