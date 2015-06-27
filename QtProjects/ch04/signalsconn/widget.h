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

signals:    //只添加一个信号，不需要按钮对应的槽函数
    void SendVoid();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
