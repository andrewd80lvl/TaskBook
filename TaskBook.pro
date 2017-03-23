#-------------------------------------------------
#
# Project created by QtCreator 2016-08-31T12:27:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TaskBook
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mousefilter.cpp \
    taskmodel.cpp \
    delegate_list_task.cpp \
    dialog_edit_task.cpp

HEADERS  += mainwindow.h \
    mousefilter.h \
    taskmodel.h \
    delegate_list_task.h \
    dialog_edit_task.h

FORMS    += mainwindow.ui \
    dialogedittask.ui

CONFIG += mobility
MOBILITY = 

DISTFILES +=

RESOURCES += \
    res.qrc



