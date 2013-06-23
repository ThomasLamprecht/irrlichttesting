TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    csamplescenenode.cpp


unix: LIBS += -L$$PWD/ -lIrrlicht

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

unix: PRE_TARGETDEPS += $$PWD/libIrrlicht.a

unix: LIBS += -lGL

unix: LIBS += -lXxf86vm

unix: LIBS += -lXxf86vm

unix: LIBS += -xf86vm
unix: LIBS += -lXext
unix: LIBS += -lX11
unix: LIBS += -lXcursor

HEADERS += \
    csamplescenenode.h
