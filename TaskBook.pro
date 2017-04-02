#-------------------------------------------------
#
# Project created by QtCreator 2016-08-31T12:27:13
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TaskBook
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mousefilter.cpp \
    taskmodel.cpp \
    delegate_list_task.cpp \
    new_edit_form.cpp \
    dbacsecc.cpp

HEADERS  += mainwindow.h \
    mousefilter.h \
    taskmodel.h \
    delegate_list_task.h \
    new_edit_form.h \
    dbacsecc.h

FORMS    += mainwindow.ui \
    new_edit_form.ui

CONFIG += mobility
MOBILITY = 

DISTFILES += db/my_objective.db3

android {
    data.files = db/my_objective.db3
    data.path = /assets/db/
    INSTALLS += data
}
RESOURCES += \
    res.qrc



