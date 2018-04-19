TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    cpp/test_lock.cpp \
    cpp/shmread.c \
    cpp/shmwrite.c

DISTFILES += \
    .vimrc \
    README.md \
    pythons/client.py

HEADERS += \
    cpp/shmdata.h
