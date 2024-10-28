cmake_minimum_required(VERSION 3.5)

project(L_Gamedev_Lib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FILE(GLOB_RECURSE Headers "include/*.h")
add_custom_target(_L_Gamedev_Lib_include SOURCES ${Headers})
FILE(GLOB_RECURSE Sources "source/*.cpp")

add_library(L_Gamedev_Lib STATIC ${Sources})

target_include_directories(L_Gamedev_Lib PUBLIC
                            "${PROJECT_SOURCE_DIR}"
                            "${PROJECT_SOURCE_DIR}/include"
                            "${PROJECT_SOURCE_DIR}/../L_Utility/include"
)

