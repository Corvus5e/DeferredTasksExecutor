TEMPLATE = app
CONFIG += console c++11 thread
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -pthread

SOURCES += main.cpp \
    deferredtask.cpp \
    worker.cpp \
    deferredtaskexecutor.cpp \
    abstracttask.cpp

HEADERS += \
    deferredtaskexecutor.h \
    worker.h \
    deferredtask.h \
    abstracttask.h

