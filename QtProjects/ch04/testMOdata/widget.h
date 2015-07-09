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

signals:
    void callSth(int a, double b);

public slots:
    void recvSth(int a, double b);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
