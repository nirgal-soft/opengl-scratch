cmake_minimum_required(VERSION 2.6)

#enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

#place outside of Debug/Release folders
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${PROJECT_bINARY_DIR}/lib")

file(GLOB SOURCES src/*.cpp)

set(EXECUTABLE_NAME "modern_opengl")
add_executable(${EXECUTABLE_NAME} ${SOURCES})
target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_range_for)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIR})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

find_package(SFML 2 REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})

target_link_libraries(${EXECUTABLE_NAME} ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SFML_LIBRARIES})
