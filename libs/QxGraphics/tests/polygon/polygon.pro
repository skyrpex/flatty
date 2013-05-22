QT = core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = polygon
TEMPLATE = app

SOURCES += main.cpp

include(../../QxGraphics.pri)
