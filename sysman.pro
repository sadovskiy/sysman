#-------------------------------------------------
#
# Project created by QtCreator 2014-07-16T18:02:41
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sysman
TEMPLATE = app

VERSION = 0.1

QMAKE_TARGET_PRODUCT = Didgital System Manadgment Document
QMAKE_TARGET_COPYRIGHT = Sadovskiy B.S., GPL

SOURCES += main.cpp\
        mainwindow.cpp \
    dialogconnecttodatabase.cpp \
    tableviewtabform.cpp \
    datecolumndelegate.cpp \
    sexcolumndelegate.cpp \
    countrydelegate.cpp \
    country.cpp

HEADERS  += mainwindow.hpp \
    dialogconnecttodatabase.hpp \
    tableviewtabform.hpp \
    datecolumndelegate.hpp \
    sexcolumndelegate.hpp \
    countrydelegate.hpp \
    country.hpp

FORMS    += mainwindow.ui \
    dialogconnecttodatabase.ui \
    tableviewtabform.ui

TRANSLATIONS += sysman_translation_ru_RU.ts

RESOURCES += images/icon.qrc
