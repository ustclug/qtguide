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

private slots:
    void on_pushButtonFixed_clicked();

private:
    Ui::Widget *ui;
    //第二个示范窗口，全部放置 QLineEdit
    QWidget *m_pWidget;
    //通过代码构造第二个示范窗口
    void CreateWidget();
};

#endif // WIDGET_H
