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
    void on_lineEdit_textEdited(const QString &arg1);

private:
    Ui::Widget *ui;

    // QWidget interface
protected:
    virtual void resizeEvent(QResizeEvent *);
};

#endif // WIDGET_H
