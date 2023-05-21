TEMPLATE = lib
CONFIG += staticlib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "../L_Utility/include"

INCLUDEPATH += "include"

HEADERS += \
    include/Behavior_Tree/Action.h \
    include/Behavior_Tree/Node_Base.h \
    include/Behavior_Tree/Selector.h \
    include/Behavior_Tree/Sequence.h \
    include/Graph/Graph.h \
    include/Graph/Graph_Node.h \
    include/Graph/Pathfinder.h

SOURCES += \
    source/Behavior_Tree/Action.cpp \
    source/Behavior_Tree/Node_Base.cpp \
    source/Behavior_Tree/Selector.cpp \
    source/Behavior_Tree/Sequence.cpp \
    source/Graph/Graph.cpp \
    source/Graph/Graph_Node.cpp \
    source/Graph/Pathfinder.cpp

