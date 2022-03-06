#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "person.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    //显示更新后的数据
    void UpdateDataShow();

private slots:
    void on_pushButtonAdd_clicked();

    void on_pushButtonDel_clicked();

    void on_pushButtonPersonToID_clicked();

    void on_pushButtonIDToPerson_clicked();

    void on_pushButtonSaveData_clicked();

    void on_pushButtonLoadData_clicked();

private:
    Ui::Widget *ui;

    //定义容器
    QHash<Person, quint64> m_data;
};

#endif // WIDGET_H
