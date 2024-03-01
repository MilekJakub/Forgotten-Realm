cmake_minimum_required(VERSION 3.27)
project(Shadow-Realm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(Shadow-Realm main.cpp)

# target_link_libraries(Shadow-Realm opengl glew glfw)
