QT += core gui opengl

CONFIG += c++11

TARGET = BaseExample
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    myopenglwindow.cpp

HEADERS += \
    myopenglwindow.h
