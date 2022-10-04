#include "pch.h"
#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vSrc = vertexSrc.c_str();
	glShaderSource(vertexShader, 1, &vSrc, nullptr);
	glCompileShader(vertexShader);

	GLint success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::vector<GLchar> infoLog(1024);
		int length = 1024;
		glGetShaderInfoLog(vertexShader, length, &length, &infoLog[0]);

		glDeleteShader(vertexShader);
		std::cout << "Vertex shader compile error: " << infoLog.data() << std::endl;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fSrc = fragmentSrc.c_str();
	glShaderSource(fragmentShader, 1, &fSrc, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::vector<GLchar> infoLog(1024);
		int length = 1024;
		glGetShaderInfoLog(fragmentShader, length, &length, &infoLog[0]);

		glDeleteShader(fragmentShader);
		std::cout << "Fragment shader compile error: " << infoLog.data() << std::endl;
	}

	m_RendererID = glCreateProgram();
	glAttachShader(m_RendererID, vertexShader);
	glAttachShader(m_RendererID, fragmentShader);
	glLinkProgram(m_RendererID);

	glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
	if (!success)
	{
		std::vector<GLchar> infoLog(1024);
		int length = 1024;
		glGetProgramInfoLog(m_RendererID, length, &length, &infoLog[0]);

		glDeleteProgram(m_RendererID);
		std::cout << "Program linkage error: " << infoLog.data() << std::endl;
	}
}

Shader::~Shader()
{
	glDeleteShader(m_RendererID);
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

void Shader::SetIntArray(const std::string& name, int count, int* values)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform1iv(location, count, values);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& matrix)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE,glm::value_ptr(matrix));
}

std::shared_ptr<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
{
	return std::shared_ptr<Shader>(new Shader(vertexSrc, fragmentSrc));
}
