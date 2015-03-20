//hellouiwidget.cpp
#include "hellouiwidget.h"

HelloUIWidget::HelloUIWidget(QWidget *parent) : QWidget(parent)
{
    setupUi(this);  //Must call setupUi first!
    //Then do other things.
    AdjustLabel();
}

HelloUIWidget::~HelloUIWidget()
{
    //Do not need to delete labels/widgets manually.
    //They will be deleted by Qt automatically.
}

void HelloUIWidget::AdjustLabel()
{
    label->setText(tr("<h1>Hello UIWidget!</h1>"));
    label->setStyleSheet(tr("color: red; background-color: rgb(0, 255, 255)"));
}
