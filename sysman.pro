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
    country.cpp \
    frameaddcontract.cpp \
    frameaddorderadmission.cpp \
    frameaddorderdismission.cpp \
    frameaddpayment.cpp \
    frameaddphasepayment.cpp \
    framestudet.cpp \
    department.cpp \
    money.cpp

HEADERS  += mainwindow.hpp \
    dialogconnecttodatabase.hpp \
    tableviewtabform.hpp \
    datecolumndelegate.hpp \
    sexcolumndelegate.hpp \
    countrydelegate.hpp \
    country.hpp \
    frameaddcontract.hpp \
    frameaddorderadmission.hpp \
    frameaddorderdismission.hpp \
    frameaddpayment.hpp \
    frameaddphasepayment.hpp \
    framestudet.hpp \
    department.hpp \
    money.hpp

FORMS    += mainwindow.ui \
    dialogconnecttodatabase.ui \
    tableviewtabform.ui \
    frameaddcontract.ui \
    frameaddorderadmission.ui \
    frameaddorderdismission.ui \
    frameaddpayment.ui \
    frameaddphasepayment.ui \
    framestudet.ui

TRANSLATIONS += sysman_ru.ts

RESOURCES += images/icon.qrc
