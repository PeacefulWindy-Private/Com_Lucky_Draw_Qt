#-------------------------------------------------
#
# Project created by QtCreator 2016-11-17T12:21:34
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD/Bass/inc

LIBS += -L$$PWD/Bass/lib -lbass

TARGET = Com_Lucky_Draw
TEMPLATE = app

SOURCES += main.cpp\
        lucky.cpp \
    music.cpp

HEADERS  += lucky.h \
    music.h

FORMS    += lucky.ui

RESOURCES +=
