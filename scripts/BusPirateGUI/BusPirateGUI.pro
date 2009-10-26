PROJECT = BusPirateGui
TARGET = BusPirateGui
TEMPLATE = app
#TEMPLATE += subdirs

SUBDIRS += qextserialport
DEPENDS += qextserialport

CONFIG += warn_off qt thread
CONFIG += debug
#CONFIG += release
CONFIG += staticlib
CONFIG += static

CONFIG(debug, debug|release) {
    LIBS += -Lqextserialport/build -lqextserialportd
} else {
   LIBS += -Lqextserialport/build -lqextserialport
}

OBJECTS_DIR = build/obj
MOC_DIR = build/moc
DEPENDDIR = .
INCLUDEDIR = .

DESTDIR = build
unix:VERSION = 1.0.0

HEADERS += 	\
			BinMode.h \
			BPSettings.h \
			Events.h \
			Interface.h \
			OtherIface.h \
			MainWin.h

SOURCES += 	\
			BinMode.cpp \
			BPSettings.cpp \
			Events.cpp \
			Interface.cpp \
			OtherIface.cpp \
			MainWin.cpp \
			main.cpp

