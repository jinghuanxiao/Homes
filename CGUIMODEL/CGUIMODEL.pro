#-------------------------------------------------
#
# Project created by QtCreator 2019-08-29T11:20:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CGUIMODEL
TEMPLATE = app

SOURCES += main.cpp

include(./Interface/Interface.pri)
include(./Common/Common.pri)
include(./Network/Network.pri)
include(./Log/Log.pri)
include(./LibCurl/LibCurl.pri)

RESOURCES += \
    resources.qrc
