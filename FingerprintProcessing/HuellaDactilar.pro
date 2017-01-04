#-------------------------------------------------
#
# Project created by QtCreator 2015-01-28T16:52:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HuellaDactilar
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    thinning.cpp \
    mathoperation.cpp \
    minutiaextractor.cpp \
    minutia.cpp \
    angle.cpp \
    matching.cpp \
    processfingerprint.cpp \
    fingerprintloader.cpp \
    segmentation.cpp \
    orientation.cpp \
    frequency.cpp \
    filter.cpp \
    binarization.cpp \
    normalize.cpp

HEADERS  += mainwindow.h \
    thinning.h \
    mathoperation.h \
    minutiaextractor.h \
    minutia.h \
    angle.h \
    matching.h \
    processfingerprint.h \
    fingerprintloader.h \
    segmentation.h \
    orientation.h \
    frequency.h \
    filter.h \
    binarization.h \
    ConstantsFingerprint.h \
    normalize.h

FORMS    += mainwindow.ui

LDFLAGS = -I/usr/local/include/opencv -lm -lopencv_core -lopencv_highgui -lopencv_video -lopencv_imgproc -lboost_thread-mt

INCLUDEPATH += /usr/local/include
INCLUDEPATH += /opt/local/include

LIBS += -L/usr/local/lib \
     -L/opt/local/lib \
     -lopencv_core \
     -lopencv_imgproc \
     -lopencv_features2d \
     -lopencv_highgui \
     -lfprint \
     -lboost_system \
     -lboost_thread-mt \
     -lboost_filesystem-mt

RESOURCES += \
    Resources.qrc
