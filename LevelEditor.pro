#-------------------------------------------------
#
# Project created by QtCreator 2015-03-31T07:48:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LevelEditor
TEMPLATE = app


SOURCES += main.cpp\
	mainwindow.cpp \
    level.cpp \
    drawarea.cpp \
    element.cpp \
    config.cpp \
    elementdescriptionwidget.cpp \
    elementdescription.cpp \
    elementdialog.cpp \
    parameter.cpp \
    enumparameter.cpp \
    valueframe.cpp \
    enumvalueframe.cpp \
    floatvalueframe.cpp \
    floatparameter.cpp

HEADERS  += mainwindow.h \
    level.h \
    drawarea.h \
    element.h \
    config.h \
    elementdescriptionwidget.h \
    elementdescription.h \
    elementdialog.h \
    parameter.h \
    enumparameter.h \
    valueframe.h \
    enumvalueframe.h \
    floatvalueframe.h \
    floatparameter.h

FORMS    += mainwindow.ui \
    elementdescriptionwidget.ui \
    elementdialog.ui \
    enumvalueframe.ui \
    floatvalueframe.ui

QMAKE_CXXFLAGS += -std=c++11
