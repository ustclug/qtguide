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
    void on_pushButtonOpen_clicked();

    void on_textBrowser_backwardAvailable(bool arg1);

    void on_textBrowser_forwardAvailable(bool arg1);

    void on_textBrowser_textChanged();

private:
    Ui::Widget *ui;
    //保存配置
    void SaveSettings();
    //加载配置
    void LoadSettings();

    // QWidget interface
protected:
    virtual void closeEvent(QCloseEvent *);
};

#endif // WIDGET_H
