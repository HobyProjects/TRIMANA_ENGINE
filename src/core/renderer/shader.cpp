#include "core_pch.hpp"

namespace TE::Core
{
	std::shared_ptr<ShaderProgram> CreateShaderProgram(const std::string& name, const std::filesystem::path& vtxShader, const std::filesystem::path& fragShader)
	{
		switch( Renderer::API() )
		{
			case RENDERER_API_OPENGL:			return std::make_shared<GL_Shader>(name, vtxShader, fragShader);
			case RENDERER_API_VULKAN:			throw UnimplementedFeatureException("Vulkan is not yet supported."); return nullptr;
			case RENDERER_API_DIRECTX:			throw UnimplementedFeatureException("DirectX 11 is not yet supported."); return nullptr;
			default:							return nullptr;
		};
	}

	std::shared_ptr<ShaderProgram> CreateShaderProgram(const std::string& name, const std::string& vtxShader, const std::string& fragShader)
	{
		switch( Renderer::API() )
		{
			case RENDERER_API_OPENGL:			return std::make_shared<GL_Shader>(name, vtxShader, fragShader);
			case RENDERER_API_VULKAN:			throw UnimplementedFeatureException("Vulkan is not yet supported."); return nullptr;
			case RENDERER_API_DIRECTX:			throw UnimplementedFeatureException("DirectX 11 is not yet supported."); return nullptr;
			default:							return nullptr;
		};
	}
}