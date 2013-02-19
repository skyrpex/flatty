QT = core gui
TARGET = QxGraphics
TEMPLATE = lib
DESTDIR = $$PWD/../bin
DEFINES += QXGRAPHICS_LIBRARY

SOURCES += \
    qxgraphicsview.cpp \
    qxgraphicslineitem.cpp \
    qxgraphicsedgeitem.cpp \
    qxgraphicspolygonitem.cpp \
    qxgraphicsvertexitem.cpp \
    qxgraphicsviewcontroller.cpp

HEADERS  += \
    ../include/qxgraphics_global.h \
    ../include/QxGraphicsView \
    ../include/QxGraphicsLineItem \
    ../include/QxGraphicsPolygonItem \
    ../include/QxGraphicsVertexItem \
    ../include/QxGraphicsEdgeItem \
    ../include/QxGraphicsViewController \
    ../include/qxgraphicsview.h \
    ../include/qxgraphicslineitem.h \
    ../include/qxgraphicspolygonitem.h \
    ../include/qxgraphicsvertexitem.h \
    ../include/qxgraphicsedgeitem.h \
    ../include/qxgraphicsviewcontroller.h

INCLUDEPATH += ../include
