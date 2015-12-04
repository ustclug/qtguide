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
    void on_pushButtonLoad_clicked();

    void on_pushButtonSave_clicked();

    void on_pushButtonDelRow_clicked();

    void on_pushButtonAddRow_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
