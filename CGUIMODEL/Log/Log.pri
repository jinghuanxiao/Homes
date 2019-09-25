INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
DEFINES += HAVE_CONFIG_H

DISTFILES +=

HEADERS += \
    $$PWD/base/commandlineflags.h \
    $$PWD/base/googleinit.h \
    $$PWD/base/mutex.h \
    $$PWD/glog/log_severity.h \
    $$PWD/glog/logging.h \
    $$PWD/glog/raw_logging.h \
    $$PWD/glog/stl_logging.h \
    $$PWD/glog/vlog_is_on.h \
    $$PWD/config.h \
    $$PWD/demangle.h \
    $$PWD/mock-log.h \
    $$PWD/port.h \
    $$PWD/stacktrace.h \
    $$PWD/stacktrace_generic-inl.h \
    $$PWD/stacktrace_libunwind-inl.h \
    $$PWD/stacktrace_powerpc-inl.h \
    $$PWD/stacktrace_windows-inl.h \
    $$PWD/stacktrace_x86-inl.h \
    $$PWD/stacktrace_x86_64-inl.h \
    $$PWD/symbolize.h \
    $$PWD/utilities.h

SOURCES += \
    $$PWD/demangle.cc \
    $$PWD/logging.cc \
    $$PWD/port.cc \
    $$PWD/raw_logging.cc \
    $$PWD/signalhandler.cc \
    $$PWD/symbolize.cc \
    $$PWD/utilities.cc \
    $$PWD/vlog_is_on.cc

