cmake_minimum_required(VERSION 3.7)
project(geGL_4_VAO)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)

find_package(GPUEngine COMPONENTS REQUIRED geGL geUtil)
find_package(Qt5 COMPONENTS REQUIRED Gui)

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

add_executable(geGL_4_VAO ${sources})
target_link_libraries(geGL_4_VAO Qt5::Gui geGL geUtil)
target_include_directories(geGL_4_VAO PUBLIC ${CMAKE_CURRENT_LIST_DIR} )
target_compile_definitions(geGL_4_VAO PUBLIC "VERTEX_SHADER=\"${vertexShader}\"" "FRAGMENT_SHADER=\"${fragmentShader}\"")

# setting up the MSVC helper var
get_target_property(Qt5dllPath Qt5::Gui IMPORTED_LOCATION_RELEASE)
get_filename_component(Qt5dllDir ${Qt5dllPath} DIRECTORY)
get_target_property(GPUEdllPath geGL IMPORTED_LOCATION_RELEASE)
get_filename_component(GPUEdllDir ${GPUEdllPath} DIRECTORY)
set_target_properties(${PROJECT_NAME} PROPERTIES VS_GLOBAL_DllPath "${GPUEdllDir};${Qt5dllDir}")
SET_PROPERTY(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})