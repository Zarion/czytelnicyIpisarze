#-------------------------------------------------
#
# Project created by QtCreator 2015-05-28T18:29:58
#
#-------------------------------------------------

QT       += core gui
QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = czytelnicyIpisarze
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    czytelnik.cpp \
    pisarz.cpp \
    biblioteka.cpp

HEADERS  += mainwindow.h \
    czytelnik.h \
    pisarz.h \
    biblioteka.h

FORMS    += mainwindow.ui
