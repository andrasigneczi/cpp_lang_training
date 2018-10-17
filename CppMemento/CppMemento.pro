TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    CppMemento.cpp \
    stringutil.cpp

DISTFILES += \
    Makefile \
    questionlist.txt

HEADERS += \
    CppMemento.h \
    stringutil.h
