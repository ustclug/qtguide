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
    void on_comboBoxSnacks_currentIndexChanged(int index);

    void on_pushButtonCalc_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
