#-------------------------------------------------
#
# Project created by QtCreator 2015-04-19T19:31:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xyhistogram.cpp \
    xyotsumethod.cpp \
    xyentropy.cpp \
    dialog.cpp \
    circle.cpp \
    xydilation.cpp \
    xygrayscale.cpp

HEADERS  += mainwindow.h \
    xyhistogram.h \
    xyotsumethod.h \
    xyentropy.h \
    dialog.h \
    circle.h \
    xydilation.h \
    xygrayscale.h

FORMS    += mainwindow.ui \
    dialog.ui \
    circle.ui
