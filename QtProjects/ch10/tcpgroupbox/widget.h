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
    //初始化控件
    void InitControls();

    //设置连接分组框启用，或禁用
    //void setConButtonEnabled(bool bEnable);

private slots:
    void on_radioButtonIP1_clicked();

    void on_radioButtonIP2_clicked();

    void on_radioButtonIP3_clicked();

    void on_radioButtonPort1_clicked();

    void on_radioButtonPort2_clicked();

    void on_radioButtonPort3_clicked();

    void on_pushButtonConnect_clicked();

    void on_pushButtonSend_clicked();

    void on_pushButtonRecv_clicked();

    void on_pushButtonClose_clicked();

private:
    Ui::Widget *ui;
    //保存IP和端口
    QString m_strIP;
    int m_nPort;
};

#endif // WIDGET_H
