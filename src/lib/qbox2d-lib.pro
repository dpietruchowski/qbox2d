#-------------------------------------------------
#
# Project created by QtCreator 2019-01-28T23:29:35
#
#-------------------------------------------------

QT       += widgets
QT       -= gui

TARGET = qbox2d
TEMPLATE = lib

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

LIBS += -lBox2D

SOURCES += \
        QB2World.cpp \
    QB2Body.cpp \
    QB2Fixture.cpp \
    QB2CircleFixture.cpp \
    QB2PolygonFixture.cpp \
    QB2Scene.cpp \
    QB2WorldScene.cpp

HEADERS += \
        QB2World.h \
        qbox2d_global.h \ 
    utils/ListRef.h \
    QB2Body.h \
    QB2Fixture.h \
    QB2CircleFixture.h \
    QB2PolygonFixture.h \
    QB2Scene.h \
    QB2WorldScene.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
