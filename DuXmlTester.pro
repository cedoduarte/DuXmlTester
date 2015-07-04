#-------------------------------------------------
#
# Project created by QtCreator 2015-07-03T16:40:05
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DuXmlTester

TEMPLATE = app

SOURCES += main.cpp \
           Widget.cpp

HEADERS  += Widget.h

FORMS    += Widget.ui

QMAKE_CXXFLAGS += -std=gnu++14
