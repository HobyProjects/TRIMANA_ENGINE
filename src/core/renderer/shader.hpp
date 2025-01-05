#pragma once

#include <filesystem>
#include <string>
#include <glm/glm.hpp>

namespace TE::Core
{
	using ShaderProgramID = uint32_t;
	using UniformLocation = uint32_t;

	class IShader
	{
		public:
			IShader() = default;
			virtual ~IShader() = default;

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			virtual ShaderProgramID GetID() const = 0;
			virtual const std::string& GetName() const = 0;
			virtual UniformLocation GetUniformLocation(const std::string& uniformName) = 0;

			virtual void SetUniform(const std::string& uniformName, float value) = 0;
			virtual void SetUniform(const std::string& uniformName, int32_t value) = 0;
			virtual void SetUniform(const std::string& uniformName, uint32_t value) = 0;
			virtual void SetUniform(const std::string& uniformName, const glm::vec2& value) = 0;
			virtual void SetUniform(const std::string& uniformName, const glm::vec3& value) = 0;
			virtual void SetUniform(const std::string& uniformName, const glm::vec4& value) = 0;
			virtual void SetUniform(const std::string& uniformName, const glm::mat2& value) = 0;
			virtual void SetUniform(const std::string& uniformName, const glm::mat3& value) = 0;
			virtual void SetUniform(const std::string& uniformName, const glm::mat4& value) = 0;
	};

	using ShaderProgram = IShader;
	std::shared_ptr<ShaderProgram> CreateShaderProgram(const std::string& name, const std::filesystem::path& vtxShader, const std::filesystem::path& fragShader);
	std::shared_ptr<ShaderProgram> CreateShaderProgram(const std::string& name, const std::string& vtxShader, const std::string& fragShader);
}