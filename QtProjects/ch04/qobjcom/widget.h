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

signals:    //添加自定义的信号
    void SendMsg(QString str);  //信号只需要声明，不要给信号写实体代码

public slots:   //接收按钮信号的槽函数
    void ButtonClicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
