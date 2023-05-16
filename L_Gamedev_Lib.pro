TEMPLATE = lib
CONFIG += staticlib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "../L_Utility/include"

INCLUDEPATH += "include"

HEADERS += \
    include/Graph/Graph.h \
    include/Graph/Graph_Node.h \
    include/Graph/Pathfinder.h

SOURCES += \
    source/Graph/Graph.cpp \
    source/Graph/Graph_Node.cpp \
    source/Graph/Pathfinder.cpp

