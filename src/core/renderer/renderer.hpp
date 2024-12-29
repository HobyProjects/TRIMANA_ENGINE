#pragma once

#include <glm/glm.hpp>
#include "base.hpp"

namespace TE::Core
{
	enum RENDERING_API
	{
		RENDERER_API_OPENGL 	= TE_BIT(0),
		RENDERER_API_VULKAN 	= TE_BIT(1),
		RENDERER_API_DIRECTX 	= TE_BIT(2)
	};

	class Renderer
	{
		private:
			Renderer() = default;
			Renderer(const Renderer&) = delete;
			Renderer& operator=(const Renderer&) = delete;
			~Renderer() = default;

		public:
			static void Init();
			static void Quit();
			static RENDERING_API API();
			static void ChangeAPI(RENDERING_API api);
			static void Clear();
			static void ClearColor(const glm::vec4& color);
			static void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height);
	};
}