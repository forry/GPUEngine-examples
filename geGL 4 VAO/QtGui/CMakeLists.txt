cmake_minimum_required(VERSION 3.7)
project(geGL_4_VAO)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)

find_package(GPUEngine COMPONENTS REQUIRED geGL)
find_package(Qt5 COMPONENTS REQUIRED Gui)

set(sources
    main.cpp
    OpenGLWindow.cpp OpenGLWindow.h
)

add_executable(geGL_4_VAO ${sources})
target_link_libraries(geGL_4_VAO Qt5::Gui geGL)
target_include_directories(geGL_4_VAO PUBLIC ${CMAKE_CURRENT_LIST_DIR} )