#pragma once

#include <glm/glm.hpp>

class Shader
{
public:
	Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
	~Shader();

	void Bind() const;
	void Unbind();

	void SetIntArray(const std::string& name, int count, int* values);
	void SetMat4(const std::string& name, const glm::mat4& matrix);

	static std::shared_ptr<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
private:
	uint32_t m_RendererID = 0;
};