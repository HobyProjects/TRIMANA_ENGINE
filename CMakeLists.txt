cmake_minimum_required(VERSION 3.20)
project(TrimanaEngine VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

####################################################################################################

find_package(glfw3 REQUIRED)

####################################################################################################

if(CMAKE_BUILD_TYPE_INIT STREQUAL "Debug")
    add_compile_definitions(TRIMANA_DEBUG)
else()
    add_compile_definitions(TRIMANA_RELEASE)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_compile_definitions(TRIMANA_PLATFORM_WINDOWS)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_compile_definitions(TRIMANA_PLATFORM_LINUX)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    add_compile_definitions(TRIMANA_PLATFORM_MACOS)
endif()

if(BUILD_SHARED_LIBS)
    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        add_compile_definitions(TRIMANA_EXPORT)
    endif()
    add_compile_definitions(TRIMANA_BUILD_SHARED)
else()
    add_compile_definitions(TRIMANA_BUILD_STATIC)
endif()


####################################################################################################

set(TRIMANA_WINDOW "trimana_window")
set(
    TRIMANA_WINDOW_INCLUDE_DIR 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/window
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core
)

set(
    TRIMANA_WINDOW_HEADERS 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/base.hpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/window/window.hpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/window/glfw_window.hpp
)

set(
    TRIMANA_WINDOW_SOURCES 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/window/window.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/window/glfw_window.cpp
)

if(BUILD_SHARED_LIBS)
    add_library(${TRIMANA_WINDOW} SHARED ${TRIMANA_WINDOW_HEADERS} ${TRIMANA_WINDOW_SOURCES})
else()
    add_library(${TRIMANA_WINDOW} STATIC ${TRIMANA_WINDOW_HEADERS} ${TRIMANA_WINDOW_SOURCES})
endif()

target_include_directories(${TRIMANA_WINDOW} PUBLIC ${TRIMANA_WINDOW_INCLUDE_DIR})
target_link_libraries(${TRIMANA_WINDOW} PUBLIC glfw)

####################################################################################################