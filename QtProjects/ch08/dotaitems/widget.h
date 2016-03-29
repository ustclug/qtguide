#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidget>  //列表控件
#include <QListWidgetItem> //列表控件条目

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
    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_pushButtonAdd_clicked();

    void on_pushButtonDel_clicked();

    void on_pushButtonViewMode_clicked();

    void on_pushButtonLoad_clicked();

    void on_pushButtonSave_clicked();

    void on_pushButtonEditToolTip_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
