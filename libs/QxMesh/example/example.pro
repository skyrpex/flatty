QT += core gui

TARGET = example
TEMPLATE = app
DESTDIR = $$PWD

SOURCES += main.cpp

OTHER_FILES += \
    example.png

include(../QxMesh.pri)
