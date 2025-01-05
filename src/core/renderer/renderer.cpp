#include "core_pch.hpp"

namespace TE::Core
{
	static RENDERING_API s_API = RENDERER_API_OPENGL;

	void Renderer::Init()
	{
		switch( s_API )
		{
			case RENDERER_API_OPENGL:
			{
				OpenGL_Renderer::Init();
				break;
			}
			case RENDERER_API_VULKAN:
			{
				throw UnimplementedFeatureException("Vulkan renderer is not implemented yet");
				break;
			}
			case RENDERER_API_DIRECTX:
			{
				throw UnimplementedFeatureException("DirectX renderer is not implemented yet");
				break;
			}
			default:
			{
				break;
			}
		};
	}

	void Renderer::Quit()
	{
		switch( s_API )
		{
			case RENDERER_API_OPENGL:
			{
				OpenGL_Renderer::Quit();
				break;
			}
			case RENDERER_API_VULKAN:
			{
				throw UnimplementedFeatureException("Vulkan renderer is not implemented yet");
				break;
			}
			case RENDERER_API_DIRECTX:
			{
				throw UnimplementedFeatureException("DirectX renderer is not implemented yet");
				break;
			}
			default:
			{
				break;
			}
		};
	}

	RENDERING_API Renderer::API()
	{
		return s_API;
	}

	void Renderer::ChangeAPI(RENDERING_API api)
	{
		//[TODO]: Need to think about how to handle this
	}

	void Renderer::Clear()
	{
		switch( s_API )
		{
			case RENDERER_API_OPENGL:
			{
				OpenGL_Renderer::Clear();
				break;
			}
			case RENDERER_API_VULKAN:
			{
				throw UnimplementedFeatureException("Vulkan renderer is not implemented yet");
				break;
			}
			case RENDERER_API_DIRECTX:
			{
				throw UnimplementedFeatureException("DirectX renderer is not implemented yet");
				break;
			}
			default:
			{
				break;
			}
		};
	}

	void Renderer::ClearColor(const glm::vec4& color)
	{
		switch( s_API )
		{
			case RENDERER_API_OPENGL:
			{
				OpenGL_Renderer::ClearColor(color);
				break;
			}
			case RENDERER_API_VULKAN:
			{
				throw UnimplementedFeatureException("Vulkan renderer is not implemented yet");
				break;
			}
			case RENDERER_API_DIRECTX:
			{
				throw UnimplementedFeatureException("DirectX renderer is not implemented yet");
				break;
			}
			default:
			{
				break;
			}
		};
	}

	void Renderer::SetViewport(int32_t x, int32_t y, int32_t width, int32_t height)
	{
		switch( s_API )
		{
			case RENDERER_API_OPENGL:
			{
				OpenGL_Renderer::SetViewport(x, y, width, height);
				break;
			}
			case RENDERER_API_VULKAN:
			{
				throw UnimplementedFeatureException("Vulkan renderer is not implemented yet");
				break;
			}
			case RENDERER_API_DIRECTX:
			{
				throw UnimplementedFeatureException("DirectX renderer is not implemented yet");
				break;
			}
			default:
			{
				break;
			}
		};
	}

	void Renderer::Draw(uint32_t indicesCount)
	{
		switch( s_API )
		{
			case RENDERER_API_OPENGL:
			{
				OpenGL_Renderer::Draw(indicesCount);
				break;
			}
			case RENDERER_API_VULKAN:
			{
				throw UnimplementedFeatureException("Vulkan renderer is not implemented yet");
				break;
			}
			case RENDERER_API_DIRECTX:
			{
				throw UnimplementedFeatureException("DirectX renderer is not implemented yet");
				break;
			}
			default:
			{
				break;
			}
		};
	}
}