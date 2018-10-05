#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidget>//列表控件
#include <QMenu>//菜单
#include <QAction>//菜单项

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    //添加槽函数
public slots:
    //弹出右键菜单的槽函数
    void onCustomContextMenuRequested(const QPoint & pos);
    //添加条目菜单项的槽函数
    void onAddItemTriggered();
    //编辑条目菜单项的槽函数
    void onEditItemTriggered();
    //删除条目菜单项的槽函数
    void onDelItemTriggered();
    //清空所有条目的菜单项槽函数
    void onClearAllTriggered();

private:
    Ui::Widget *ui;
    //保存右键菜单的指针
    QMenu *m_menuContext;
    //创建菜单并关联信号和槽函数
    void CreateMenu();
};

#endif // WIDGET_H
