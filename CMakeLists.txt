cmake_minimum_required(VERSION 3.20)
project(TrimanaEngine VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

###############################################################################
# Dependencies
###############################################################################
find_package(glfw3 REQUIRED)
find_package(spdlog REQUIRED)



###############################################################################
# Platform Specific Configuration
###############################################################################
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_compile_definitions(TRIMANA_PLATFORM_WINDOWS)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_compile_definitions(TRIMANA_PLATFORM_LINUX)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(TRIMANA_DEBUG)
else()
    add_compile_definitions(TRIMANA_RELEASE)
endif()

if(BUILD_SHARED_LIBS)
    add_compile_definitions(TRIMANA_BUILD_SHARED)
else()
    add_compile_definitions(TRIMANA_BUILD_STATIC)
endif()


###############################################################################
# TrimanaEngine - Core Library
###############################################################################

#Include Directories
set(
    TRIMANA_CORE_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/subcore
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window
)

#Header Files
set(
    TRIMANA_CORE_HEADERS 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/subcore/log.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/subcore/base.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window/window.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window/glfw_window.hpp
)

#Source Files
set(
    TRIMANA_CORE_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/subcore/log.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window/window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window/glfw_window.cpp
)

if(BUILD_SHARED_LIBS)
    add_library(TrimanaEngineCore SHARED ${TRIMANA_CORE_HEADERS} ${TRIMANA_CORE_SOURCES})
else()
    add_library(TrimanaEngineCore STATIC ${TRIMANA_CORE_HEADERS} ${TRIMANA_CORE_SOURCES})
endif()

target_include_directories(TrimanaEngineCore PUBLIC ${TRIMANA_CORE_INCLUDE_DIRS})
target_link_libraries(TrimanaEngineCore PUBLIC glfw spdlog::spdlog)

###############################################################################