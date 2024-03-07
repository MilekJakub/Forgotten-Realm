cmake_minimum_required(VERSION 3.27)
project(Forgotten-Realm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER "/Library/Developer/CommandLineTools/usr/bin/g++")

# Include both the src and include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/*.c
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/src/*.h
        ${CMAKE_SOURCE_DIR}/src/*.hpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIRS})

# Find the Cocoa framework
find_library(COCOA_LIBRARY Cocoa)
if(NOT COCOA_LIBRARY)
    message(FATAL_ERROR "Cocoa framework not found")
endif()

# Find the IOKit framework
find_library(IOKIT_LIBRARY IOKit)
if(NOT IOKIT_LIBRARY)
    message(FATAL_ERROR "IOKit framework not found")
endif()

# Link the Cocoa and IOKit frameworks along with OpenGL and other libraries
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${COCOA_LIBRARY} ${IOKIT_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/libglfw3.a)
target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/libGLEW.a)

link_directories(${CMAKE_SOURCE_DIR}/libs)
