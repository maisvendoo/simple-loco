TEMPLATE = lib

QT -= gui
QT += xml

TARGET = simple-loco

DESTDIR = $$(RRS_ROOT)/modules/$$join(TARGET,,,)

LIBS += -L$$(RRS_ROOT)/bin -lCfgReader
LIBS += -L$$(RRS_ROOT)/bin -lphysics
LIBS += -L$$(RRS_ROOT)/bin -lvehicle
LIBS += -L$$(RRS_ROOT)/bin -ldevice
LIBS += -L$$(RRS_ROOT)/bin -lfilesystem

INCLUDEPATH += ./include
INCLUDEPATH += $$(RRS_ROOT)/sdk/include

HEADERS += $$files(./include/*.h)
SOURCES += $$files(./src/*.cpp)
