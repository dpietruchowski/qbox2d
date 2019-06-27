#-------------------------------------------------
#
# Project created by QtCreator 2019-01-28T23:29:35
#
#-------------------------------------------------

QT       += widgets
QT       -= gui

TARGET = qbox2d
TEMPLATE = app

DEFINES += QBOX2D_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -std=c++17

INCLUDEPATH += ../lib

LIBS += -L../lib -lqbox2d

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    MyWorld.cpp \
    Platform.cpp \
    Rocket.cpp \
    RocketLanderWorld.cpp \
    RocketLander.cpp

HEADERS += \
    MainWindow.h \
    MyWorld.h \
    Platform.h \
    Rocket.h \
    RocketLanderWorld.h \
    RocketLander.h


unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    MainWindow.ui
