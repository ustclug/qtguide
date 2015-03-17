//main.cpp
#include <QtWidgets/QApplication>
#include "hellowidget.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    HelloWidget hw;
    hw.show();

    return a.exec();
}
