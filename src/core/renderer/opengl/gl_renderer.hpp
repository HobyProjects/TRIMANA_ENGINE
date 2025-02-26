#pragma once

#include "renderer.hpp"

namespace TE::Core
{
	class OpenGL_Renderer
	{
		private:
			OpenGL_Renderer() = default;
			OpenGL_Renderer(const OpenGL_Renderer&) = delete;
			OpenGL_Renderer& operator=(const OpenGL_Renderer&) = delete;
			~OpenGL_Renderer() = default;

		public:
			static void Init();
			static void Quit();
			static RENDERING_API API() { return RENDERER_API_OPENGL; }
			static void Clear();
			static void ClearColor(const glm::vec4& color);
			static void SetViewport(int32_t x, int32_t y, int32_t width, int32_t Height);
			static void Draw(uint32_t indicesCount);
	};
}