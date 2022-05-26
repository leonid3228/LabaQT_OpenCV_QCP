#-------------------------------------------------
#
# Project created by QtCreator 2022-04-08T13:54:23
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
        mainwindow.h \
    qcustomplot.h

FORMS +=
INCLUDEPATH+/="usr/local/include"
LIBS+=`pkg-config --libs opencv`

DISTFILES += \
    resources/for1/1_0.jpg \
    resources/for1/1_1.jpg \
    resources/for1/1_2.jpg \
    resources/for1/1_3.jpg \
    resources/for1/1_4.jpg \
    resources/for1/1_5.jpg \
    resources/for1/1_6.jpg \
    resources/for1/1_7.jpg \
    resources/for1/1_8.jpg \
    resources/for1/1_9.jpg \
    resources/for2/2_0.jpg \
    resources/for2/2_1.jpg \
    resources/for2/2_2.jpg \
    resources/for2/2_3.jpg \
    resources/for2/2_4.jpg \
    resources/for2/2_5.jpg \
    resources/for2/2_6.jpg \
    resources/for2/2_7.jpg \
    resources/for2/2_8.jpg \
    resources/for2/2_9.jpg \
    resources/for1/1_10.jpg
