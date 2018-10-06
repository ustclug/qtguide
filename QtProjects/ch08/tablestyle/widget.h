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
    void on_pushButtonAlternatingRowColors_clicked();

    void on_pushButtonSelectionCustom_clicked();

    void on_pushButtonItemCustom_clicked();

    void on_pushButtonCornerButtonCustom_clicked();

    void on_pushButtonHeaderCustom_clicked();

    void on_pushButtonClearStyle_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
