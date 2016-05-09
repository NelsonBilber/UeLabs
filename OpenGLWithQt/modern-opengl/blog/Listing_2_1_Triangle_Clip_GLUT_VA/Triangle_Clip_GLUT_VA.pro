QT -= core
QT -= gui
QT += opengl

CONFIG += c++11

TARGET = Triangle_GLUT_VA
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

INCLUDEPATH += $$(FREEGLUT)\include
LIBS += -L$$(FREEGLUT)/lib/x64/ -lfreeglut

CONFIG(release, debug|release): DESTDIR = $$OUT_PWD/release
CONFIG(debug, debug|release): DESTDIR = $$OUT_PWD/debug
dll.files = $$(FREEGLUT)\bin\x64\freeglut.dll
dll.path = $$DESTDIR
INSTALLS += dll
