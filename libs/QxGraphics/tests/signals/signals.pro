QT = core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = signals
TEMPLATE = app

SOURCES += main.cpp

include(../../QxGraphics.pri)
