cmake_minimum_required(VERSION 2.8.4)
project(GLHeart)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(SOURCE_DIR src)

add_subdirectory(external/glfw)

include_directories(external/glfw/include)
include_directories(external/glm/include)
include_directories(external/glew/include)

add_definitions(-DGLEW_STATIC)

file(GLOB SOURCE_FILES "${SOURCE_DIR}/*.h" "${SOURCE_DIR}/*.cpp")
file(COPY resources DESTINATION ${PROJECT_BINARY_DIR})

add_executable(GLHeart external/glew/src/glew.c ${SOURCE_FILES} src/ePostprocessEffect.cpp src/ePostprocessEffect.h src/sceneBase.cpp src/sceneBase.h src/sceneBasePreincludes.h)
target_link_libraries(GLHeart glfw ${GLFW_LIBRARIES})