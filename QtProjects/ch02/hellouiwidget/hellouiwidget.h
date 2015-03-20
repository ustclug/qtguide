//hellouiwidget.h
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include "ui_hello.h"

class HelloUIWidget : public QWidget, public Ui::Form
{
    Q_OBJECT
public:
    explicit HelloUIWidget(QWidget *parent = 0);
    ~HelloUIWidget();

protected:
    void AdjustLabel();
};

