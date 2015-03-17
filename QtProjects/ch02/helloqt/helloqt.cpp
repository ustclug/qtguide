//helloqt.cpp
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLabel label( QLabel::tr("Hello Qt!") );
    label.show();

    return a.exec();
}
