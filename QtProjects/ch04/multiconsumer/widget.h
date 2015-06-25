#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:   //添加槽函数进行弹窗
    void FoodIsComing();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
