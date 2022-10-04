#include "pch.h"
#include "Texture.h"
#include "stb_image.h"

#include <glad/glad.h>

Texture::Texture(const std::string& path)
{
	int width, height, channels;
	stbi_set_flip_vertically_on_load(1);
	stbi_uc* data = nullptr;
	data = stbi_load(path.c_str(), &width, &height, &channels, 0);

	if (data == nullptr)
	{
		std::cout << "Stb image::image load error" << std::endl;
	}

	m_Width = width;
	m_Height = height;
	m_Channels = channels;

	std::cout << path << " has " << width << ", " << height << "px, and " << channels << " channels" << std::endl;

	GLint internalFormat = 0, dataFormat = 0;
	if (channels == 3)
	{
		internalFormat = GL_RGB8;
		dataFormat = GL_RGB;
	}
	else if (channels == 4)
	{
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;
	}
	glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	stbi_image_free(data);
}

Texture::Texture(uint32_t width, uint32_t height)
{
	uint32_t data = 0xFFFFFFFF;
	glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void Texture::Bind(uint32_t slot)
{
	glBindTextureUnit(slot, m_RendererID);
}

void Texture::Unbind(uint32_t slot)
{
	glBindTextureUnit(slot, 0);
}

std::shared_ptr<Texture> Texture::Create(const std::string& path)
{
	return std::shared_ptr<Texture>(new Texture(path));
}

std::shared_ptr<Texture> Texture::Create(uint32_t width, uint32_t height)
{
	return std::shared_ptr<Texture>(new Texture(width, height));
}
