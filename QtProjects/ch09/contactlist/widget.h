#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QList>   //列表类
#include "contact.h"  //联系人

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
    void on_pushButtonAdd_clicked();

    void on_pushButtonDel_clicked();

    void on_pushButtonFind_clicked();

    void on_pushButtonSort_clicked();

    void on_pushButtonSave_clicked();

    void on_pushButtonOpen_clicked();

private:
    Ui::Widget *ui;
    //联系人列表
    QList<Contact> m_listContacts;
};

#endif // WIDGET_H
