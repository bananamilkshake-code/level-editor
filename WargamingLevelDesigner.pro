#-------------------------------------------------
#
# Project created by QtCreator 2015-03-31T07:48:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WargamingLevelDesigner
TEMPLATE = app


SOURCES += main.cpp\
	mainwindow.cpp \
    level.cpp \
    drawarea.cpp \
    element.cpp \
    config.cpp \
    elementdescriptionwidget.cpp \
    elementdescription.cpp \
    addelementdialog.cpp

HEADERS  += mainwindow.h \
    level.h \
    drawarea.h \
    element.h \
    config.h \
    elementdescriptionwidget.h \
    elementdescription.h \
    addelementdialog.h

FORMS    += mainwindow.ui \
    elementdescriptionwidget.ui \
    addelementdialog.ui

QMAKE_CXXFLAGS += -std=c++11
