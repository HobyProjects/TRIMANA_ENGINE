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

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

//SubCore
#include "base.hpp"
#include "asserts.hpp"
#include "exceptions.hpp"
#include "keycodes.hpp"
#include "log.hpp"

//renderer
#include "renderer.hpp"

//renderer - opengl
#include "opengl/glfw_gl_context.hpp"
#include "opengl/sdl_gl_context.hpp"
#include "opengl/gl_debug.hpp"
#include "opengl/gl_renderer.hpp"

// events
#include "events.hpp"
#include "window_events.hpp"
#include "keyboard_events.hpp"
#include "mouse_events.hpp"

// window
#include "base_window.hpp"
#include "glfw_window.hpp"
#include "sdl_window.hpp"