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

private slots:
    void on_pushButtonEditText_clicked();

    void on_fontComboBox_currentIndexChanged(const QString &arg1);

    void on_spinBoxSize_valueChanged(int arg1);

    void on_comboBoxFGColor_currentIndexChanged(const QString &arg1);

    void on_comboBoxBGColor_currentIndexChanged(const QString &arg1);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
