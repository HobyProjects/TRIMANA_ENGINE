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
find_package(stb REQUIRED)


###############################################################################
# Platform Specific Configuration
###############################################################################
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_compile_definitions(TE_PLATFORM_WINDOWS)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_compile_definitions(TE_PLATFORM_LINUX)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(TE_DEBUG)
else()
    add_compile_definitions(TE_RELEASE)
endif()



###############################################################################
# TrimanaEngine - Core Library
###############################################################################

#Include Directories
set(
    TRIMANA_CORE_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/subcore
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/events
)

#Header Files
set(
    TRIMANA_CORE_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/subcore/asserts.hpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/subcore/log.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/subcore/base.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/subcore/keycodes.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/subcore/delta_time.hpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window/base_window.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window/glfw_window.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window/sdl_window.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window/core.hpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/renderer.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/buffers.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/vertex_array.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/shader.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/frame_buffer.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/texture.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/camera.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/camera2d.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/camera3d.hpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/glfw_gl_context.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/sdl_gl_context.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/gl_renderer.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/gl_debug.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/gl_buffers.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/gl_vertex_array.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/gl_shader.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/gl_frame_buffer.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/gl_texture.hpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/events/events.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/events/window_events.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/events/keyboard_events.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/events/mouse_events.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/events/inputs_handler.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/events/glfw_inputs_poll.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/events/sdl_inputs_poll.hpp

)


#Source Files
set(
    TRIMANA_CORE_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/subcore/log.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window/glfw_window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window/sdl_window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/window/core.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/renderer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/buffers.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/vertex_array.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/shader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/frame_buffer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/texture.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/camera2d.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/camera3d.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/glfw_gl_context.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/sdl_gl_context.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/gl_renderer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/gl_debug.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/gl_buffers.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/gl_vertex_array.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/gl_shader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/gl_frame_buffer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer/opengl/gl_texture.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/events/inputs_handler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/events/glfw_inputs_poll.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/events/sdl_inputs_poll.cpp

)


add_library(TrimanaEngineCore STATIC ${TRIMANA_CORE_HEADERS} ${TRIMANA_CORE_SOURCES})
target_precompile_headers(TrimanaEngineCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/core/subcore/core_pch.hpp)
target_include_directories(TrimanaEngineCore PUBLIC ${TRIMANA_CORE_INCLUDE_DIRS})
target_link_libraries(
    TrimanaEngineCore 
        PUBLIC 
            glfw 
            spdlog::spdlog 
            SDL3::SDL3-static 
            glad::glad 
            glm::glm-header-only
            stb::stb
)


###############################################################################
# TrimanaEngine - Application
###############################################################################

set(
    TRIMANA_APP_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/entrypoint
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/camera
)

set(
    TRIMANA_APP_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/entrypoint/application.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/entrypoint/application_layer.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/entrypoint/application_layers_stack.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/entrypoint/sandbox.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/camera/primary_camera.hpp
)

set(
    TRIMANA_APP_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/entrypoint/application.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/entrypoint/application_layers_stack.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/entrypoint/sandbox.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/entrypoint/main.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/camera/primary_camera.cpp
)

add_executable(TrimanaEngine ${TRIMANA_CORE_HEADERS} ${TRIMANA_APP_HEADERS} ${TRIMANA_APP_SOURCES})
target_precompile_headers(TrimanaEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/app/entrypoint/app_pch.hpp)
target_include_directories(TrimanaEngine PUBLIC ${TRIMANA_CORE_INCLUDE_DIRS} ${TRIMANA_APP_INCLUDE_DIRS})
target_link_libraries(TrimanaEngine PUBLIC TrimanaEngineCore)

add_custom_target(
    TrimanaEngineResources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/res 
    ${PROJECT_BINARY_DIR}/res 
    COMMENT "Copying resources into the binary dir"
)
add_dependencies(TrimanaEngine TrimanaEngineResources)

