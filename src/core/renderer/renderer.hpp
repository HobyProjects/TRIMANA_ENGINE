#pragma once

#include <glm/glm.hpp>

#include "base.hpp"
#include "camera2d.hpp"
#include "camera3d.hpp"
#include "texture.hpp"

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
			static void SetViewport(int32_t x, int32_t y, int32_t width, int32_t Height);
			static void Draw(uint32_t indicesCount);
	};

	class BatchRenderer
	{
		private:
			BatchRenderer() = default;
			~BatchRenderer() = default;
			
			static void Restart();

		public:
			struct RendererStatus
			{
				uint32_t DrawCount{ 0 };
				uint32_t QuadCount{ 0 };
			};

		public:
			static void Init();
			static void Quit();

			static void Begin(const Camera2D& camera);
			static void Begin(const Camera2D& camera, const glm::mat4& transform);
			static void End();
			static void Flush();

			static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);
			static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, float rotation);
			static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const std::shared_ptr<Texture2D> texture);
			static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const std::shared_ptr<Texture2D> texture, float rotation);
			static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, const std::shared_ptr<Texture2D>& texture, float rotation);
			static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, const std::shared_ptr<Texture2D> texture, float rotation, float tillingFactor = 1.0f);

			static const RendererStatus& Status();
			static void StatusReset();
	
	};
}