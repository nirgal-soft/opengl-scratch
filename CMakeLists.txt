cmake_minimum_required(VERSION 2.6)

#enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

#place outside of Debug/Release folders
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${PROJECT_bINARY_DIR}/lib")

file(GLOB SOURCES src/*.cpp imgui/*.cpp libs/gl3w/GL/gl3w.c)

set(EXECUTABLE_NAME "modern_opengl")
add_executable(${EXECUTABLE_NAME} ${SOURCES})
target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_range_for)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIR})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

include_directories(libs/gl3w)

target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARIES} ${SDL2_LIBRARY} ${CMAKE_DL_LIBS})
