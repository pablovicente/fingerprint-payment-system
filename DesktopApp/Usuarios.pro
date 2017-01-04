#-------------------------------------------------
#
# Project created by QtCreator 2015-02-18T16:10:35
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = Usuarios
TEMPLATE = app
CONFIG  += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    toolbar.cpp \
    communication.cpp \
    myuser.cpp \
    mypurchases.cpp \
    mycard.cpp \
    utils.cpp \
    Fingerprint/angle.cpp \
    Fingerprint/minutiaextractor.cpp \
    Fingerprint/mathoperation.cpp \
    Fingerprint/normalize.cpp \
    Fingerprint/binarization.cpp \
    Fingerprint/minutia.cpp \
    Fingerprint/orientation.cpp \
    Fingerprint/segmentation.cpp \
    Fingerprint/thinning.cpp \
    Fingerprint/myfingerprint.cpp \
    Fingerprint/filter.cpp \
    Fingerprint/fingerprintloader.cpp \
    Fingerprint/frequency.cpp \
    Fingerprint/matching.cpp \
    Fingerprint/processfingerprint.cpp \
    stylesheetprovider.cpp

HEADERS  += mainwindow.h \
    toolbar.h \
    communication.h \
    myuser.h \
    mypurchases.h \
    mycard.h \
    utils.h \
    Fingerprint/angle.h \
    Fingerprint/minutiaextractor.h \
    Fingerprint/mathoperation.h \
    Fingerprint/normalize.h \
    Fingerprint/binarization.h \
    Fingerprint/minutia.h \
    Fingerprint/orientation.h \
    Fingerprint/segmentation.h \
    Fingerprint/thinning.h \
    Fingerprint/myfingerprint.h \
    Constants.h \
    Fingerprint/filter.h \
    Fingerprint/fingerprintloader.h \
    Fingerprint/frequency.h \
    Fingerprint/ConstantsFingerprint.h \
    Fingerprint/matching.h \
    Fingerprint/processfingerprint.h \
    stylesheetprovider.h

FORMS    += mainwindow.ui

RESOURCES += \
    MyResources.qrc


LDFLAGS = -I/usr/local/include/opencv -lm -lopencv_core -lopencv_highgui -lopencv_video -lopencv_imgproc -lboost_thread-mt

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib \
     -lopencv_core \
     -lopencv_imgproc \
     -lopencv_features2d \
     -lopencv_highgui \
     -lfprint \     
     -lboost_system \
     -lboost_thread-mt

