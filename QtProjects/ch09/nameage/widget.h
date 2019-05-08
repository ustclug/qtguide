#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMap> //映射类

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

    void on_pushButtonDel_clicked();

    void on_pushButtonFindName_clicked();

    void on_pushButtonFindAge_clicked();

private:
    Ui::Widget *ui;
    //映射类对象，保存姓名-年龄映射
    QMap<QString, int> m_mapNameAge;
    //枚举映射对象的内容，显示到列表控件
    void showNameAgeMap();
};

#endif // WIDGET_H
