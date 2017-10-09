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
    dbacsecc.cpp \
    buttonabovewindow.cpp

HEADERS  += mainwindow.h \
    mousefilter.h \
    taskmodel.h \
    delegate_list_task.h \
    new_edit_form.h \
    dbacsecc.h \
    buttonabovewindow.h

FORMS    += mainwindow.ui \
    new_edit_form.ui

CONFIG += mobility
MOBILITY =

DISTFILES += db/my_objective.db3 \
    dialog_edit_task.obj \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

android {
    data.files = db/my_objective.db3
    data.path = /assets/db/
    INSTALLS += data
}

DEFINES += QT_DEPRECATED_WARNINGS

RESOURCES += \
    res.qrc

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android



