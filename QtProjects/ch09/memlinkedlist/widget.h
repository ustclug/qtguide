#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLinkedList>

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
    void on_pushButtonAllocate_clicked();

    void on_pushButtonFind_clicked();

    void on_pushButtonFree_clicked();

private:
    Ui::Widget *ui;
    //空闲内存块链表，以字符串代表内存块
    QLinkedList<QString> m_memFree;
    //已使用的内存块链表
    QLinkedList<QString> m_memUsed;
    //同步更新图形界面的列表控件
    void updateListWidgets();
};

#endif // WIDGET_H
