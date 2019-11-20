TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    debug.c \
    for_each_process.c \
    packetcapturewithnetfilter.c \
    sendUDPWithKernelModule.c \
    test.c \
    world.c \
    create_thread.c \
    server.c \
    client.c \
    socket.c \
    sendmsg.c \
    work_queue.c \
    task_let.c \
    alloc_page.c

DISTFILES += \
    Makefile

HEADERS += \
    test.h
