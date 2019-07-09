#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMultiMap>//多重映射模板类

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
    void on_pushButtonAdd_clicked();

    void on_pushButtonReplace_clicked();

    void on_pushButtonDelName_clicked();

    void on_pushButtonDelNamePhone_clicked();

    void on_pushButtonFindName_clicked();

    void on_pushButtonFindPhone_clicked();

private:
    Ui::Widget *ui;
    //多重映射对象，保存姓名电话映射
    QMultiMap<QString, QString> m_mmapNamePhone;
    //枚举映射对象内容，显示到列表控件
    void showNamePhoneMap();
};

#endif // WIDGET_H
