#-------------------------------------------------
#
# Project created by QtCreator 2018-05-25T20:08:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JSTestG29
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

QT += network

INCLUDEPATH +=/usr/local/include \
    /usr/local/include/opencv2

LIBS += -ludev
        -lpthread


LIBS += \
    -L/usr/local/lib \
    -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_ml -lopencv_calib3d -lopencv_video -lopencv_objdetect \
    -lopencv_features2d -lopencv_flann -lopencv_nonfree \
#LIBS += /usr/lib/x86_64-linux-gnu/libprotobuf.so \
#/usr/lib/x86_64-linux-gnu/libprotobuf.a

SOURCES += \
        main.cpp \
        jstestwindow.cpp \
    logitechg29.cpp \
    hid.c \



HEADERS += \
        jstestwindow.h \
    logitechg29_global.h \
    logitechg29.h \
    hidapi.h \


FORMS += \
        jstestwindow.ui










