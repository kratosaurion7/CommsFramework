#-------------------------------------------------
#
# Project created by QtCreator 2015-08-01T17:56:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestWindow
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

INCLUDEPATH += $$PWD/../../CommsFramework $$PWD/../../../libs/rapidxml

HEADERS  += mainwindow.h $$PWD/../../CommsFramework/*.h

#$$PWD/../../CommsFramework/*.h

FORMS    += mainwindow.ui

win32: LIBS += -L$$PWD/../../Debug/ -lCommsFramework

INCLUDEPATH += $$PWD/../../Debug
DEPENDPATH += $$PWD/../../Debug

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../Debug/CommsFramework.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../Debug/libCommsFramework.a
