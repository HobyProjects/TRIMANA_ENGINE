#include "core_pch.hpp"

namespace TE::Core
{
	std::string GL_Shader::ReadShaderFiles(const std::filesystem::path& filePath)
	{
		std::string result{};
		std::ifstream in_file(filePath, std::ios::in | std::ios::binary);
		if( in_file )
		{
			in_file.seekg(0, std::ios::end);
			result.resize(in_file.tellg());
			in_file.seekg(0, std::ios::beg);
			in_file.read(&result [0], result.size());
			return result;
		}

		TE_ASSERT(false, "Failed to read shader file: {0}", filePath.string());
		return std::string("");
	}

	void GL_Shader::CompileShaders(const std::unordered_map<GLenum, std::string>& shaders)
	{
		ShaderProgramID programID = glCreateProgram();
		TE_ASSERT(programID, "Failed to create program for the shader");

		for( auto& source : shaders )
		{
			GLenum type = source.first;
			const std::string& src = source.second;
			uint32_t shader = glCreateShader(type);
			const char* src_cstr = src.c_str();
			glShaderSource(shader, 1, &src_cstr, nullptr);
			glCompileShader(shader);
			glAttachShader(programID, shader);
		}

		glLinkProgram(programID);
		glValidateProgram(programID);
		m_ID = programID;
	}

	GL_Shader::GL_Shader(const std::string& name, const std::string& vtxShader, const std::string& fragShader)
	{
		m_Name = name;
		std::unordered_map<GLenum, std::string> shaders;
		shaders [GL_VERTEX_SHADER] = vtxShader;
		shaders [GL_FRAGMENT_SHADER] = fragShader;
		CompileShaders(shaders);
	}

	GL_Shader::GL_Shader(const std::string& name, const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
	{
		m_Name = name;
		std::unordered_map<GLenum, std::string> shaders;
		shaders [GL_VERTEX_SHADER] = ReadShaderFiles(vertexPath);
		shaders [GL_FRAGMENT_SHADER] = ReadShaderFiles(fragmentPath);
		CompileShaders(shaders);
	}

	GL_Shader::~GL_Shader()
	{
		glDeleteProgram(m_ID);
	}

	void GL_Shader::Bind() const
	{
		glUseProgram(m_ID);
	}

	void GL_Shader::Unbind() const
	{
		glUseProgram(0);
	}

	ShaderProgramID GL_Shader::GetID() const
	{
		return m_ID;
	}

	const std::string& GL_Shader::GetName() const
	{
		return m_Name;
	}

	UniformLocation GL_Shader::GetUniformLocation(const std::string& uniformName)
	{
		if( m_UniformLocations.find(uniformName) == m_UniformLocations.end() )
		{
			UniformLocation location = glGetUniformLocation(m_ID, uniformName.c_str());
			if( location == -1 )
			{
				TE_ASSERT(location, "Failed to get uniform location: {0}", uniformName);
				return -1;
			}
			m_UniformLocations [uniformName] = location;
		}
		return m_UniformLocations [uniformName];
	}

	void GL_Shader::SetUniform(const std::string& uniformName, float value)
	{
		glUniform1f(GetUniformLocation(uniformName), value);
	}

	void GL_Shader::SetUniform(const std::string& uniformName, int32_t value)
	{
		glUniform1i(GetUniformLocation(uniformName), value);
	}

	void GL_Shader::SetUniform(const std::string& uniformName, uint32_t value)
	{
		glUniform1ui(GetUniformLocation(uniformName), value);
	}

	void GL_Shader::SetUniform(const std::string& uniformName, const glm::vec2& value)
	{
		glUniform2f(GetUniformLocation(uniformName), value.x, value.y);
	}

	void GL_Shader::SetUniform(const std::string& uniformName, const glm::vec3& value)
	{
		glUniform3f(GetUniformLocation(uniformName), value.x, value.y, value.z);
	}

	void GL_Shader::SetUniform(const std::string& uniformName, const glm::vec4& value)
	{
		glUniform4f(GetUniformLocation(uniformName), value.x, value.y, value.z, value.w);
	}

	void GL_Shader::SetUniform(const std::string& uniformName, const glm::mat2& value)
	{
		glUniformMatrix2fv(GetUniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(value));
	}

	void GL_Shader::SetUniform(const std::string& uniformName, const glm::mat3& value)
	{
		glUniformMatrix3fv(GetUniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(value));
	}

	void GL_Shader::SetUniform(const std::string& uniformName, const glm::mat4& value)
	{
		glUniformMatrix4fv(GetUniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(value));
	}
}