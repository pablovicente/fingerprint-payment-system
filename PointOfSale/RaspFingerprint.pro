#-------------------------------------------------
#
# Project created by QtCreator 2015-06-05T12:15:40
#
#-------------------------------------------------

QT       += core network
QT       -= gui

TARGET = RaspFingerprint
CONFIG   += console c++11 -pthread
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mathoperation.cpp \
    orientation.cpp \
    angle.cpp \
    normalize.cpp \
    segmentation.cpp \
    binarization.cpp \
    thinning.cpp \
    minutiaextractor.cpp \
    minutia.cpp \
    processfingerprint.cpp \
    screen.cpp \
    keypad.cpp \
    scanfingerprint.cpp \
    myfingerprint.cpp \
    communication.cpp \
    filter.cpp \
    frequency.cpp \
    matching.cpp \
    paymentprocess.cpp \
    settings.cpp

HEADERS += mathoperation.h \
    orientation.h \
    angle.h \
    normalize.h \
    segmentation.h \
    binarization.h \
    thinning.h \
    minutiaextractor.h \
    minutia.h \
    processfingerprint.h \
    screen.h \
    keypad.h \
    scanfingerprint.h \
    myfingerprint.h \
    communication.h \
    mathoperation.h \
    filter.h \
    frequency.h \
    ConstantsFingerprint.h \
    matching.h \
    paymentprocess.h \
    settings.h \
    Constants.h


LDFLAGS = -I/usr/local/include/opencv -lm -lopencv_core -lopencv_video -lopencv_imgproc -lboost_system

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib \
     -lopencv_core \
     -lopencv_imgproc \
     -lopencv_features2d \     
     -lwiringPi \
     -lwiringPiDev \
     -lfprint \
     -lboost_system \
     -lboost_thread


