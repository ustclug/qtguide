#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLinkedList>//链表
#include <QList> //列表
#include <QVector>//向量
#include <QElapsedTimer> //耗费计时
#include <QLocale> //本地化类，用于打印逗号分隔的数字

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
    void on_pushButtonPrepend_clicked();

    void on_pushButtonMidInsert_clicked();

    void on_pushButtonAppend_clicked();

    void on_pushButtonRandAccess_clicked();

private:
    Ui::Widget *ui;
    //链表
    QLinkedList<int> m_linkdList;
    //列表
    QList<int> m_list;
    //向量
    QVector<int> m_vector;
    //耗费计时器
    QElapsedTimer m_calcTimer;
    //本地化对象，用于打印逗号分隔的数字
    QLocale m_locale;
};

#endif // WIDGET_H
