#pragma once

//std
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <type_traits>
#include <algorithm>
#include <utility>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <bitset>

//external
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <soil2/SOIL2.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>


//SubCore
#include "base.hpp"
#include "asserts.hpp"
#include "keycodes.hpp"
#include "log.hpp"
#include "delta_time.hpp"

//renderer
#include "renderer.hpp"
#include "buffers.hpp"
#include "vertex_array.hpp"
#include "shader.hpp"
#include "frame_buffer.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "camera2d.hpp"
#include "camera3d.hpp"
#include "mesh.hpp"
#include "model.hpp"

//renderer - opengl
#include "opengl/glfw_gl_context.hpp"
#include "opengl/sdl_gl_context.hpp"
#include "opengl/gl_debug.hpp"
#include "opengl/gl_renderer.hpp"
#include "opengl/gl_buffers.hpp"
#include "opengl/gl_vertex_array.hpp"
#include "opengl/gl_shader.hpp"
#include "opengl/gl_frame_buffer.hpp"
#include "opengl/gl_texture.hpp"

// events
#include "events.hpp"
#include "window_events.hpp"
#include "keyboard_events.hpp"
#include "mouse_events.hpp"
#include "inputs_handler.hpp"
#include "glfw_inputs_poll.hpp"
#include "sdl_inputs_poll.hpp"

// window
#include "base_window.hpp"
#include "glfw_window.hpp"
#include "sdl_window.hpp"
#include "core.hpp"