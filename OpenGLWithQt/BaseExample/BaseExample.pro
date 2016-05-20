QT += core gui opengl widgets

CONFIG += c++11

TARGET = BaseExample

CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    myopenglwindow.cpp \
    trianglewindow.cpp

HEADERS += \
    myopenglwindow.h \
    trianglewindow.h

RESOURCES += \
    shader.qrc

DISTFILES += \
    fshader.glsl \
    vshader.glsl

