#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QButtonGroup> //按钮分组类头文件

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
    void RecvGenderID(int id); //接收性别单选按钮分组信号
    void RecvStatusID(int id); //接收状态单选按钮分组信号

private slots:
    void on_radioButton0to19_toggled(bool checked);

    void on_radioButton20to39_toggled(bool checked);

    void on_radioButton40to59_toggled(bool checked);

    void on_radioButton60to_toggled(bool checked);

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    //按钮分组
    QButtonGroup *m_pGenderGroup;   //性别单选按钮分组
    QButtonGroup *m_pStatusGroup;   //状态单选按钮分组
};

#endif // WIDGET_H
