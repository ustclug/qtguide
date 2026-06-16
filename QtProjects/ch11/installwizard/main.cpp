#include "installwizarddialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InstallWizardDialog w;
    w.show();

    return a.exec();
}
