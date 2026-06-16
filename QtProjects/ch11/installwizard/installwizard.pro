#-------------------------------------------------
#
# Project created by QtCreator 2026-06-08T16:09:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = installwizard
TEMPLATE = app


SOURCES += main.cpp\
        installwizarddialog.cpp \
    intropage.cpp \
    licencepage.cpp \
    installpage.cpp \
    finalpage.cpp

HEADERS  += installwizarddialog.h \
    intropage.h \
    licencepage.h \
    installpage.h \
    finalpage.h

FORMS    += installwizarddialog.ui \
    intropage.ui \
    licencepage.ui \
    installpage.ui \
    finalpage.ui

RESOURCES += \
    pixmaps.qrc
