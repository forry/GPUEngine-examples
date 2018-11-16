cmake_minimum_required(VERSION 3.7)
project(geGL_5_Uniforms)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(GPUEngine COMPONENTS REQUIRED geGL geCore)
find_package(Qt5 COMPONENTS REQUIRED Gui)
find_package(glm REQUIRED)

# This is one way to find it the other more precise way would employ get the library location propery
# and extracting the dir path from that, might require special handling when the target gives you more
# than one library path in the property which should not happen but it will for some libraries with improper
# CMake support. This brings a question of how to handle the transitive dependencies for this usecase.
get_filename_component(geDLLs ${GPUEngine_DIR}/../../../bin ABSOLUTE)
get_filename_component(Qt5DLLs ${Qt5_DIR}/../../../bin ABSOLUTE)

set(sources
    main.cpp
    OpenGLWindow.cpp OpenGLWindow.h
)

find_file(vertexShader vertexShader.glsl
        HINTS ${CMAKE_CURRENT_LIST_DIR}/..
        )

find_file(fragmentShader fragmentShader.glsl
        HINTS ${CMAKE_CURRENT_LIST_DIR}/..
        )

add_custom_target(resources SOURCES ${vertexShader} ${fragmentShader})
SOURCE_GROUP(shaders FILES ${vertexShader} ${fragmentShader})

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} Qt5::Gui geGL geCore glm)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR} )
target_compile_definitions(${PROJECT_NAME} PUBLIC "VERTEX_SHADER=\"${vertexShader}\"" "FRAGMENT_SHADER=\"${fragmentShader}\"")

#MSVC special
set_target_properties(${PROJECT_NAME} PROPERTIES VS_GLOBAL_DLLDir "${geDLLs};${Qt5DLLs}")
SET_PROPERTY(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})