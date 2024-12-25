cmake_minimum_required(VERSION 3.20)
project(TrimanaEngine VERSION 1.0.0 LANGUAGES C CXX)

##############################################################################
# Compiler Configuration
##############################################################################
set(CMAKE_CXX_STANDARD 23)
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
find_package(SDL3 REQUIRED)
find_package(glad REQUIRED)
find_package(glm REQUIRED)







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











###############################################################################
# TrimanaEngine - Core Library
###############################################################################

#Include Directories
set(
    TRIMANA_CORE_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/subcore
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer
)

#Header Files
set(
    TRIMANA_CORE_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/subcore/asserts.hpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/subcore/exceptions.hpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/subcore/log.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/subcore/base.hpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window/window.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window/glfw_window.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window/sdl_window.hpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/renderer.hpp


        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/glfw_gl_context.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/sdl_gl_context.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/gl_renderer.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/gl_debug.hpp
)

#Source Files
set(
    TRIMANA_CORE_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/subcore/log.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window/window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window/glfw_window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window/sdl_window.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/renderer.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/glfw_gl_context.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/sdl_gl_context.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/gl_renderer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/gl_debug.cpp
)


add_library(TrimanaEngineCore STATIC ${TRIMANA_CORE_HEADERS} ${TRIMANA_CORE_SOURCES})
target_include_directories(TrimanaEngineCore PUBLIC ${TRIMANA_CORE_INCLUDE_DIRS})
target_link_libraries(TrimanaEngineCore PUBLIC glfw spdlog::spdlog SDL3::SDL3 glad::glad glm::glm)