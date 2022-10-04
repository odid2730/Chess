#pragma once

#include <string>
#include <memory>

class Texture
{
public:
	Texture(const std::string& path);
	Texture(uint32_t width, uint32_t height);
	~Texture() = default;

	void Bind(uint32_t slot = 0);
	void Unbind(uint32_t slot = 0);

	bool operator==(const Texture& other)
	{
		return m_RendererID == other.m_RendererID;
	}
	bool operator!=(const Texture& other)
	{
		return !(*this == other);
	}

	static std::shared_ptr<Texture> Create(const std::string& path);
	static std::shared_ptr<Texture> Create(uint32_t width, uint32_t height);
private:
	int m_Width = 0, m_Height = 0, m_Channels = 0;
	uint32_t m_RendererID = 0;
};