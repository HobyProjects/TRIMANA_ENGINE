#pragma once

#include <glm/glm.hpp>
#include "base.hpp"

namespace trimana::core {

	enum class rendering_api {
		opengl		= TRIMANA_BIT(0),
		vulkan		= TRIMANA_BIT(1),
		directx		= TRIMANA_BIT(2)
	};

	class renderer {
	private:
		renderer() = default;
		renderer(const renderer&) = delete;
		renderer& operator=(const renderer&) = delete;
		~renderer() = default;

	public:
		static void init();
		static void quit();
		static rendering_api api();
		static void change_api(rendering_api api);
		static void clear();
		static void clear_color(const glm::vec4& color);
		static void set_viewport(int32_t x, int32_t y, int32_t width, int32_t height);
	};
}