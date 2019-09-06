cmake_minimum_required(VERSION 3.7)
project(geGL_2_Shaders)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)

find_package(GPUEngine COMPONENTS REQUIRED geGL geUtil)
find_package(Qt5 COMPONENTS REQUIRED Gui)

set(sources
    main.cpp
    OpenGLWindow.cpp OpenGLWindow.h
)

find_file(vertexShader triag_vs.glsl
        HINTS ${CMAKE_CURRENT_LIST_DIR}/..
        )

add_executable(geGL_2_Shaders ${sources})
target_link_libraries(geGL_2_Shaders Qt5::Gui geGL geUtil)
target_include_directories(geGL_2_Shaders PUBLIC ${CMAKE_CURRENT_LIST_DIR} )
target_compile_definitions(geGL_2_Shaders PUBLIC "VERTEX_SHADER=\"${vertexShader}\"")

# setting up the MSVC helper var
get_target_property(Qt5dllPath Qt5::Gui IMPORTED_LOCATION_RELEASE)
get_filename_component(Qt5dllDir ${Qt5dllPath} DIRECTORY)
get_target_property(GPUEdllPath geGL IMPORTED_LOCATION_RELEASE)
get_filename_component(GPUEdllDir ${GPUEdllPath} DIRECTORY)
set_target_properties(${PROJECT_NAME} PROPERTIES VS_GLOBAL_DllPath "${GPUEdllDir};${Qt5dllDir}")
SET_PROPERTY(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})