#-------------------------------------------------
#
# Project created by QtCreator 2019-01-28T23:29:35
#
#-------------------------------------------------

QT       += widgets network
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

INCLUDEPATH += ../../lib
INCLUDEPATH += ../../multiplayer-lib
INCLUDEPATH += ../common

LIBS += -L../../lib -lqbox2d -L../../multiplayer-lib -lqbox2d-multiplayer

SOURCES += \
    ../common/Platform.cpp \
    ../common/Rocket.cpp \
    ../common/RocketLander.cpp \
    ../common/RocketWorld.cpp \
    ConnectDialog.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    ../common/Platform.h \
    ../common/Rocket.h \
    ../common/RocketLander.h \
    ../common/RocketWorld.h \
    ConnectDialog.h \
    MainWindow.h

FORMS += \
    ConnectDialog.ui \
    MainWindow.ui
