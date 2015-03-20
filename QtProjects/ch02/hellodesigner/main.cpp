//main.cpp
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include "ui_hello.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget *hw = new QWidget();    //main GUI window
    Ui::Form createUi;      //createUi is not a real window
    createUi.setupUi(hw);   //createUi is a tool for creating the GUI
    hw->show();             //hw is the real window

    return a.exec();
}
