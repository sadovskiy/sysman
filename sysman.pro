#-------------------------------------------------
#
# Project created by QtCreator 2014-07-16T18:02:41
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sysman
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialogconnecttodatabase.cpp

HEADERS  += mainwindow.hpp \
    dialogconnecttodatabase.hpp

FORMS    += mainwindow.ui \
    dialogconnecttodatabase.ui

RESOURCES += ico.qrc

TRANSLATIONS += sysman_ru_RU.ts
