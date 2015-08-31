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
    void on_comboBoxGender_currentIndexChanged(int index);

    void on_comboBoxJob_currentTextChanged(const QString &arg1);

    void on_dateEdit_dateChanged(const QDate &date);

    void on_pushButtonCommit_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
