#-------------------------------------------------
#
# Project created by QtCreator 2019-03-11T10:27:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NF-Prober
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

CONFIG += c++11

SOURCES += \
    bitset.cpp \
    intersectiontable.cpp \
        main.cpp \
        mainwindow.cpp \
    dialogfilein.cpp \
    dialogfileview.cpp \
    dialogfileconfirm.cpp \
    data2int.cpp \
    dependencies.cpp \
    candidate.cpp \
    hashtable.cpp \
    partition.cpp

HEADERS += \
    bitset.h \
    intersectiontable.h \
        mainwindow.h \
    dialogfilein.h \
    dialogfileview.h \
    dialogfileconfirm.h \
    data2int.h \
    dependencies.h \
    candidate.h \
    hashtable.h \
    partition.h

FORMS += \
        mainwindow.ui \
    dialogfilein.ui \
    dialogfileview.ui \
    dialogfileconfirm.ui \
    dependencies.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
