#-------------------------------------------------
#
# Project created by QtCreator 2013-10-17T14:58:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    lista.cpp \
    microsd_explorer.cpp \
    pc_rs232_handler.cpp \
    dialog_conectar.cpp

HEADERS  += mainwindow.h \
    lista.h \
    microsd_explorer.h \
    pc_rs232_handler.h \
    dialog_conectar.h

FORMS    += mainwindow.ui \
    lista.ui \
    microsd_explorer.ui \
    dialog_conectar.ui

RESOURCES += \
    iconos.qrc

include (qextserialport-1.2rc/src/qextserialport.pri)

OTHER_FILES +=



