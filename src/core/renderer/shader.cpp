#include "core_pch.hpp"

namespace TE::Core
{
	std::shared_ptr<IShader> CreateShaderProgram(const std::string& name, const std::filesystem::path& vtxShader, const std::filesystem::path& fragShader)
	{
		switch( Renderer::API() )
		{
			case RENDERER_API_OPENGL:			return std::make_shared<GL_Shader>(name, vtxShader, fragShader);
			case RENDERER_API_VULKAN:			TE_ASSERT(false, "Vulkan is not yet supported."); return nullptr;
			case RENDERER_API_DIRECTX:			TE_ASSERT(false, "DirectX 11 is not yet supported."); return nullptr;
			default:							return nullptr;
		};
	}

	std::shared_ptr<IShader> CreateShaderProgram(const std::string& name, const std::string& vtxShader, const std::string& fragShader)
	{
		switch( Renderer::API() )
		{
			case RENDERER_API_OPENGL:			return std::make_shared<GL_Shader>(name, vtxShader, fragShader);
			case RENDERER_API_VULKAN:			TE_ASSERT(false, "Vulkan is not yet supported."); return nullptr;
			case RENDERER_API_DIRECTX:			TE_ASSERT(false, "DirectX 11 is not yet supported."); return nullptr;
			default:							return nullptr;
		};
	}
}