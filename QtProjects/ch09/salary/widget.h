#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMultiHash>
#include <QMultiMap> //可以用于键值对的同步排序

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    //初始化填充
    void InitSalary();
    //工资列表变动时，显示到列表控件
    void UpdateSalaryShow();

private slots:
    void on_pushButtonIncrease_clicked();

    void on_pushButtonFindZhang3_clicked();

    void on_pushButtonFindTop3_clicked();

    void on_pushButtonFind8K_clicked();

    void on_pushButtonDel8K_clicked();

private:
    Ui::Widget *ui;
    //使用哈希映射保存工资表
    QMultiHash<QString, double> m_salary;
};

#endif // WIDGET_H
