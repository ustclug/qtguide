//main.cpp
#include <QtWidgets/QApplication>
#include "hellouiwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HelloUIWidget *huiw = new HelloUIWidget();
    huiw->show();

    return a.exec();
}
