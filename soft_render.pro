#-------------------------------------------------
#
# Project created by QtCreator 2015-10-19T13:45:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = soft_render
TEMPLATE = app


SOURCES += main.cpp\
        canvas.cpp \
    cube.cpp \
    universal.cpp \
    camera.cpp

HEADERS  += canvas.h \
    cube.h \
    universal.h \
    camera.h

FORMS    += canvas.ui

OUTPUT += Console
