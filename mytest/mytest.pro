TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    cstring.cpp \
    consdbg.cpp \
    HtmlParser.cpp \
    test-html-parser.cpp

HEADERS += \
    cstring.h \
    consdbg.h \
    HtmlParser.h

DISTFILES += \
    test/testfiles/163.com.html \
    test/testfiles/baidu.com.html \
    test/testfiles/cnbeta.com.html \
    test/testfiles/google.com.html \
    test/testfiles/plus.google.com.explore.html \
    test/testfiles/qq.com.html \
    test/testfiles/sina.com.cn.html \
    test/testfiles/sohu.com.html \
    test/testfiles/taobao.com.html
