#-------------------------------------------------
#
# Project created by QtCreator 2016-05-10T15:22:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TableView
TEMPLATE = app


SOURCES += main.cpp\
        tableview.cpp

HEADERS  += tableview.h \
    comeinhashmap.h \
    goouthashmap.h \
    hashmap.h \
    port.h

FORMS    += tableview.ui

OTHER_FILES +=
INCLUDEPATH += C:\Users\Administrator\Desktop\QTproject\Include
LIBS += "-LC:\Users\Administrator\Desktop\QTproject\Lib" -lwpcap -lPacket
DEFINES += HAVE_REMOTE
