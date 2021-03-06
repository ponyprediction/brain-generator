#-------------------------------------------------
#
# Project created by QtCreator 2015-05-31T17:59:36
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = brain-generator

CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11

TEMPLATE = app


SOURCES += main.cpp \
    util.cpp \
    brain-generator.cpp \
    layer.cpp \
    neuron.cpp

HEADERS += \
    util.hpp \
    brain-generator.hpp \
    layer.hpp \
    neuron.hpp

DISTFILES += \
    brain-generator.conf
