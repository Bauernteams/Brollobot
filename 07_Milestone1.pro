#-------------------------------------------------
#
# Project created by QtCreator 2017-05-10T14:15:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 07_Milestone1
TEMPLATE = app


SOURCES +=\
        mainwindow.cpp \
    controlsystem.cpp \
    DcMotor.cpp \
    LineSensor.cpp \
    mobileplatform.cpp \
    tools.cpp \
    main.cpp

HEADERS  += mainwindow.h \
    controlsystem.h \
    DcMotor.h \
    LineSensor.h \
    mobileplatform.h \
    tools.h \
    main.cppasd \
    SensorData.h

FORMS    += mainwindow.ui

LIBS += -lwiringPi \
        -lpthread
