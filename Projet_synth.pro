#-------------------------------------------------
#
# Project created by QtCreator 2017-04-02T16:33:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projet_synth
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS \
            __WINDOWS_MM__

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    RtMidi.cpp \
    ADSR.cpp \
    filter.cpp \
    oscillators.cpp \
    LUTs.cpp \
    synth_engine.cpp \
    reverb.cpp \
    echo.cpp \
    effect.cpp

HEADERS  += mainwindow.h \
    portaudio.h \
    RtMidi.h \
    ADSR.hpp \
    filter.hpp \
    global.hpp \
    LUTs.hpp \
    oscillators.hpp \
    synth_engine.hpp \
    reverb.hpp \
    echo.hpp \
    effect.hpp

FORMS    += mainwindow.ui

LIBS += -lwinmm \
 -L$$PWD/./portaudio/lib/.libs/ -lportaudio

DISTFILES +=


