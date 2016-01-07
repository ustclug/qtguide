#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "calcpi.h"

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
    void on_pushButtonCalcPI_clicked();

    void on_pushButtonCalcAll_clicked();

private:
    Ui::Widget *ui;
    //用于计算pi的类对象
    CalcPI m_calcPI;
    //获取单选按钮对应的PI长度
    int GetPILength();
};

#endif // WIDGET_H
