#-------------------------------------------------
#
# Project created by QtCreator 2016-08-31T12:27:13
#
#-------------------------------------------------

QT       += core gui androidextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TaskBook
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mousefilter.cpp \
    taskmodel.cpp \
    delegate_list_task.cpp \
    dialogedittask.cpp

HEADERS  += mainwindow.h \
    mousefilter.h \
    taskmodel.h \
    delegate_list_task.h \
    dialogedittask.h

FORMS    += mainwindow.ui \
    dialogedittask.ui

CONFIG += mobility
MOBILITY = 

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/res/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

