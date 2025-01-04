#pragma once

#include "shader.hpp"

namespace TE::Core
{
	class GL_Shader : public IShader
	{
		public:
			GL_Shader(const std::string& name, const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
			virtual ~GL_Shader();

			virtual void Bind() const override;
			virtual void Unbind() const override;

			virtual ShaderProgramID GetID() const override;
			virtual const std::string& GetName() const override;
			virtual UniformLocation GetUniformLocation(const std::string& uniformName) override;

			virtual void SetUniform(const std::string& uniformName, float value) override;
			virtual void SetUniform(const std::string& uniformName, int32_t value) override;
			virtual void SetUniform(const std::string& uniformName, uint32_t value) override;
			virtual void SetUniform(const std::string& uniformName, const glm::vec2& value) override;
			virtual void SetUniform(const std::string& uniformName, const glm::vec3& value) override;
			virtual void SetUniform(const std::string& uniformName, const glm::vec4& value) override;
			virtual void SetUniform(const std::string& uniformName, const glm::mat2& value) override;
			virtual void SetUniform(const std::string& uniformName, const glm::mat3& value) override;
			virtual void SetUniform(const std::string& uniformName, const glm::mat4& value) override;

		private:
			void CompileShaders(const std::unordered_map<GLenum, std::string>& shaders);
			std::string ReadShaderFiles(const std::filesystem::path& filePath);

		private:
			ShaderProgramID m_ID;
			std::string m_Name;
			std::unordered_map<std::string, UniformLocation> m_UniformLocations;
	};
}