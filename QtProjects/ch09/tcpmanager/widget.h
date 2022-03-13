#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMultiMap> //保存IP和端口映射

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    //初始化填充
    void InitTCPLinks();
    //更新树形控件的显示
    void UpdateTreeShow();

private slots:
    void on_pushButtonAddTCP_clicked();

    void on_pushButtonDelIP_clicked();

    void on_pushButtonDelPort_clicked();

    void on_pushButtonFindBelow1024_clicked();

    void on_pushButtonPlus1024_clicked();

private:
    Ui::Widget *ui;
    //保存IP和端口信息
    QMultiMap<QString, int> m_tcplinks;

};

#endif // WIDGET_H
