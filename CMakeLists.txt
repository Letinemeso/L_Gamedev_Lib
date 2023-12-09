cmake_minimum_required(VERSION 3.5)

project(L_Gamedev_Lib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FILE(GLOB_RECURSE LibFiles "include/*.h")
add_custom_target(L_Gamedev_Lib_include SOURCES ${LibFiles})

add_library(L_Gamedev_Lib STATIC    
    source/Behavior_Tree/Action.cpp
    source/Behavior_Tree/Node_Base.cpp
    source/Behavior_Tree/Selector.cpp
    source/Behavior_Tree/Sequence.cpp
    source/Graph/Graph.cpp
    source/Graph/Graph_Node.cpp
    source/Graph/Pathfinder.cpp
)

target_include_directories(L_Gamedev_Lib PUBLIC
                            "${PROJECT_SOURCE_DIR}"
                            "${PROJECT_SOURCE_DIR}/include"
                            "${PROJECT_SOURCE_DIR}/../L_Utility/include"
)

