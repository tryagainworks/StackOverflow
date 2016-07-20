#-------------------------------------------------
#
# Project created by QtCreator 2016-07-20T10:03:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTVideoFrame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    videowidgetsurface.cpp

HEADERS  += mainwindow.h \
    videowidgetsurface.h

FORMS    += mainwindow.ui
config += C++11
QT += multimedia
QT += multimediawidgets
