TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    cpp/test_lock.cpp \
    cpp/shmread.c \
    cpp/shmwrite.c \
    TcpDos.c \
    cpp/icmpraw.cpp \
    cpp/testsemp.cpp

DISTFILES += \
    .vimrc \
    README.md \
    pythons/client.py

HEADERS += \
    cpp/shmdata.h
