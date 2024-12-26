#pragma once

#include "renderer.hpp"

namespace trimana::core
{
	class gl_renderer
	{
	private:
		gl_renderer() = default;
		gl_renderer(const gl_renderer&) = delete;
		gl_renderer& operator=(const gl_renderer&) = delete;
		~gl_renderer() = default;

	public:
		static void init();
		static void quit();
		static rendering_api api() { return rendering_api::opengl; }
		static void clear();
		static void clear_color(const glm::vec4& color);
		static void set_viewport(int32_t x, int32_t y, int32_t width, int32_t height);
	};
}