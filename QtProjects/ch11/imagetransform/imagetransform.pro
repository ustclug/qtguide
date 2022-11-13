#-------------------------------------------------
#
# Project created by QtCreator 2022-11-13T08:47:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = imagetransform
TEMPLATE = app


SOURCES += main.cpp\
        imagetransformwidget.cpp \
    resizeimagedialog.cpp \
    rotateimagedialog.cpp

HEADERS  += imagetransformwidget.h \
    resizeimagedialog.h \
    rotateimagedialog.h

FORMS    += imagetransformwidget.ui \
    resizeimagedialog.ui \
    rotateimagedialog.ui
