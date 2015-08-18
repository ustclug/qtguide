#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>   //定时器类

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    //接收定时器信号的槽函数
    void RecvTimer();

private slots:
    void on_pushButtonToday_clicked();

private:
    Ui::Widget *ui;
    QTimer *m_timer;
};

#endif // WIDGET_H
