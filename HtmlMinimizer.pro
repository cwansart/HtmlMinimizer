TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS_DEBUG += -Wall -Wextra -pedantic

SOURCES += main.c

DISTFILES += \
    test.html

