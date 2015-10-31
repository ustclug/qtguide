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
    void on_pushButtonGetWorkPath_clicked();

    void on_pushButtonSetWorkPath_clicked();

    void on_pushButtonEnvPaths_clicked();

    void on_pushButtonExist_clicked();

    void on_pushButtonIsRelative_clicked();

    void on_pushButtonShowAbsolute_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
