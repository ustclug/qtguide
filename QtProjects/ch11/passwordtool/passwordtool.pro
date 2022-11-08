#-------------------------------------------------
#
# Project created by QtCreator 2022-11-07T18:24:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = passwordtool
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    formchangepassword.cpp

HEADERS  += mainwidget.h \
    formchangepassword.h

FORMS    += mainwidget.ui \
    formchangepassword.ui
