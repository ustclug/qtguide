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
    void on_pushButtonBrowseSrc_clicked();

    void on_pushButtonLoad_clicked();

    void on_pushButtonBrowseDst_clicked();

    void on_pushButtonSave_clicked();

private:
    Ui::Widget *ui;
    //分析一行配置文本，设置到对应的控件里
    void AnalyzeOneLine(const QByteArray &baLine);
};

#endif // WIDGET_H
