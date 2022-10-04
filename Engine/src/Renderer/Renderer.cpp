#include "pch.h"
#include "Renderer.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

struct QuadVertexData
{
	glm::vec3 Position;
	glm::vec4 Color;
	glm::vec2 TexCoord;
	float TexIndex;
};

struct RendererData
{
	std::shared_ptr<VertexArray> VertexArray;
	std::shared_ptr<VertexBuffer> VertexBuffer;
	std::shared_ptr<IndexBuffer> IndexBuffer;
	std::shared_ptr<Shader> TextureShader;
	std::shared_ptr<Shader> FixedTextureShader;
	std::shared_ptr<Texture> WhiteTexture;

	uint32_t TextureSlot = 1;
	std::array<std::shared_ptr<Texture>, 32> Texture;

	uint32_t MaxQuadCount = 1000;
	uint32_t MaxVerticesCount = MaxQuadCount * 4;
	uint32_t MaxIndicesCount = MaxQuadCount * 6;

	QuadVertexData* QuadVertexDataBase = new QuadVertexData[MaxQuadCount];
	QuadVertexData* QuadVertexDataPtr = QuadVertexDataBase;

	uint32_t QuadIndicesCount = 0;

	glm::vec4 QuadVertexPosition[4] = {
		{-0.5f, -0.5f, 0.0f, 1.0f},
		{ 0.5f, -0.5f, 0.0f, 1.0f},
		{ 0.5f,  0.5f, 0.0f, 1.0f},
		{-0.5f,  0.5f, 0.0f, 1.0f}
	};
};

static RendererData s_Data;

void Renderer::Init()
{
	s_Data.VertexArray = VertexArray::Create();

	s_Data.VertexBuffer = VertexBuffer::Create(sizeof(QuadVertexData) * s_Data.MaxVerticesCount);
	s_Data.VertexBuffer->SetLayout({
		{"a_Position", ShaderDataType::Float3},
		{"a_Color", ShaderDataType::Float4},
		{"a_TexCoord", ShaderDataType::Float2},
		{"a_TexIndex", ShaderDataType::Float}
	});
	s_Data.VertexArray->SetVertexBuffer(s_Data.VertexBuffer);
	
	uint32_t* indices = new uint32_t[s_Data.MaxIndicesCount];

	uint32_t offset = 0;
	for (uint32_t i = 0; i < s_Data.MaxIndicesCount; i += 6)
	{
		indices[i + 0] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;
						 
		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}
	s_Data.IndexBuffer = IndexBuffer::Create(indices, s_Data.MaxIndicesCount);
	s_Data.VertexArray->SetIndexBuffer(s_Data.IndexBuffer);

	delete[] indices;

	std::string vertexSource = R"(
		#version 450 core
		layout(location=0) in vec3 a_Position;
		layout(location=1) in vec4 a_Color;
		layout(location=2) in vec2 a_TexCoord;
		layout(location=3) in float a_TexIndex;	

		uniform mat4 u_ViewProjection;

		out vec4 v_Color;
		out vec2 v_TexCoord;
		out flat float v_TexIndex;

		void main()
		{
			v_Color = a_Color;
			v_TexCoord = a_TexCoord;
			v_TexIndex = a_TexIndex;
			gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
		}
	)";

	std::string fragmentSource = R"(
		#version 450 core
		layout(location=0) out vec4 a_Color;

		in vec4 v_Color;
		in vec2 v_TexCoord;
		in flat float v_TexIndex;

		uniform sampler2D u_Textures[32];

		void main()
		{
			switch(int(v_TexIndex))
			{
				case  0: a_Color = texture(u_Textures[ 0], v_TexCoord); break;
				case  1: a_Color = texture(u_Textures[ 1], v_TexCoord); break;
				case  2: a_Color = texture(u_Textures[ 2], v_TexCoord); break;
				case  3: a_Color = texture(u_Textures[ 3], v_TexCoord); break;
				case  4: a_Color = texture(u_Textures[ 4], v_TexCoord); break;
				case  5: a_Color = texture(u_Textures[ 5], v_TexCoord); break;
				case  6: a_Color = texture(u_Textures[ 6], v_TexCoord); break;
				case  7: a_Color = texture(u_Textures[ 7], v_TexCoord); break;
				case  8: a_Color = texture(u_Textures[ 8], v_TexCoord); break;
				case  9: a_Color = texture(u_Textures[ 9], v_TexCoord); break;
				case 10: a_Color = texture(u_Textures[10], v_TexCoord); break;
				case 11: a_Color = texture(u_Textures[11], v_TexCoord); break;
				case 12: a_Color = texture(u_Textures[12], v_TexCoord); break;
				case 13: a_Color = texture(u_Textures[13], v_TexCoord); break;
				case 14: a_Color = texture(u_Textures[14], v_TexCoord); break;
				case 15: a_Color = texture(u_Textures[15], v_TexCoord); break;
				case 16: a_Color = texture(u_Textures[16], v_TexCoord); break;
				case 17: a_Color = texture(u_Textures[17], v_TexCoord); break;
				case 18: a_Color = texture(u_Textures[18], v_TexCoord); break;
				case 19: a_Color = texture(u_Textures[19], v_TexCoord); break;
				case 20: a_Color = texture(u_Textures[20], v_TexCoord); break;
				case 21: a_Color = texture(u_Textures[21], v_TexCoord); break;
				case 22: a_Color = texture(u_Textures[22], v_TexCoord); break;
				case 23: a_Color = texture(u_Textures[23], v_TexCoord); break;
				case 24: a_Color = texture(u_Textures[24], v_TexCoord); break;
				case 25: a_Color = texture(u_Textures[25], v_TexCoord); break;
				case 26: a_Color = texture(u_Textures[26], v_TexCoord); break;
				case 27: a_Color = texture(u_Textures[27], v_TexCoord); break;
				case 28: a_Color = texture(u_Textures[28], v_TexCoord); break;
				case 29: a_Color = texture(u_Textures[29], v_TexCoord); break;
				case 30: a_Color = texture(u_Textures[30], v_TexCoord); break;
				case 31: a_Color = texture(u_Textures[31], v_TexCoord); break;
			}
			a_Color *= v_Color;
			//a_Color = texture(u_Textures[int(v_TexIndex)], v_TexCoord) * v_Color;
		}
	)";
	s_Data.TextureShader = Shader::Create(vertexSource, fragmentSource);

	std::string fixedVertexSource = R"(
		#version 450 core
		layout(location=0) in vec3 a_Position;
		layout(location=1) in vec4 a_Color;
		layout(location=2) in vec2 a_TexCoord;
		layout(location=3) in float a_TexIndex;
		
		uniform mat4 u_Projection;

		out vec4 v_Color;
		out vec2 v_TexCoord;
		out flat float v_TexIndex;

		void main()
		{
			v_Color = a_Color;
			v_TexCoord = a_TexCoord;
			v_TexIndex = a_TexIndex;
			gl_Position = u_Projection * vec4(a_Position, 1.0);
		}
	)";

	s_Data.FixedTextureShader = Shader::Create(fixedVertexSource, fragmentSource);

	int samplers[32];
	for (int i = 0; i < 32; i++)
		samplers[i] = i;
	s_Data.TextureShader->Bind();
	s_Data.TextureShader->SetIntArray("u_Textures", 32, samplers);

	s_Data.FixedTextureShader->Bind();
	s_Data.FixedTextureShader->SetIntArray("u_Textures", 32, samplers);

	//s_Data.WhiteTexture = Texture::Create(1, 1);
	s_Data.Texture[0] = Texture::Create(1, 1); // white texture
}

void Renderer::BeginScene(const Camera& camera)
{
	s_Data.TextureShader->Bind();
	s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjection());
	s_Data.FixedTextureShader->Bind();
	s_Data.FixedTextureShader->SetMat4("u_Projection", camera.GetProjection());

	s_Data.QuadVertexDataPtr = s_Data.QuadVertexDataBase;
	s_Data.QuadIndicesCount = 0;
	
	s_Data.TextureSlot = 1;
}

void Renderer::EndScene()
{
	uint32_t size = (uint8_t*)s_Data.QuadVertexDataPtr - (uint8_t*)s_Data.QuadVertexDataBase;
	s_Data.VertexBuffer->SetData(s_Data.QuadVertexDataBase, size);

	//s_Data.FixedTextureShader->Bind();
	s_Data.VertexArray->Bind();
	for (int i = 0; i < s_Data.TextureSlot; i++)
	{
		s_Data.Texture[i]->Bind(i);
	}
	glDrawElements(GL_TRIANGLES, s_Data.QuadIndicesCount, GL_UNSIGNED_INT, nullptr);

	// Temp: TODO: remove.
	s_Data.QuadVertexDataPtr = s_Data.QuadVertexDataBase;
	s_Data.QuadIndicesCount = 0;

	s_Data.TextureSlot = 1;
}

void Renderer::DrawQuad(const glm::vec3& position, const glm::vec4& color, const glm::vec2& size, int index, float rotation)
{
	glStencilFunc(GL_ALWAYS, index, -1);
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1))
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	DrawQuad(transform, color);
}

void Renderer::DrawQuad(const glm::vec3& position, const std::shared_ptr<Texture>& texture, const glm::vec2& size, int index, float rotation, const glm::vec4& tintColor)
{
	glStencilFunc(GL_ALWAYS, index, -1);
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1))
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	DrawQuad(transform, texture, tintColor);
}

void Renderer::DrawFixedQuad(const glm::vec3& position, const glm::vec4& color, const glm::vec2& size, int index, float rotation)
{
	glStencilFunc(GL_ALWAYS, index, -1);
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1))
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	DrawFixedQuad(transform, color);
}

void Renderer::DrawFixedQuad(const glm::vec3& position, const std::shared_ptr<Texture>& texture, const glm::vec2& size, int index, float rotation, const glm::vec4& tintColor)
{
	glStencilFunc(GL_ALWAYS, index, -1);
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1))
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	DrawFixedQuad(transform, texture, tintColor);
}

void Renderer::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
{
	// Temp, TODO: remove
	s_Data.TextureShader->Bind();

	glm::vec2 texCoord[4] = {
		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f}
	};

	float texIndex = 0.0f;

	for (int i = 0; i < 4; i++)
	{
		s_Data.QuadVertexDataPtr->Position = transform * s_Data.QuadVertexPosition[i];
		s_Data.QuadVertexDataPtr->Color = color;
		s_Data.QuadVertexDataPtr->TexCoord = texCoord[i];
		s_Data.QuadVertexDataPtr->TexIndex = texIndex;
		s_Data.QuadVertexDataPtr++;
	}

	s_Data.QuadIndicesCount += 6;

	EndScene();
}

void Renderer::DrawQuad(const glm::mat4& transform, const std::shared_ptr<Texture>& texture, const glm::vec4& tintColor)
{
	// Temp, TODO: remove.
	s_Data.TextureShader->Bind();

	glm::vec4 color = tintColor;//{ 1.0f, 1.0f, 1.0f, 1.0f };

	glm::vec2 texCoord[4] = {
		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f}
	};

	float texIndex = 0.0f;

	for (int i = 1; i < s_Data.TextureSlot; i++)
	{
		if (*texture.get() == *s_Data.Texture[i].get())
		{
			texIndex = (float)i;
			break;
		}
	}

	if (texIndex == 0.0f)
	{
		texIndex = (float)s_Data.TextureSlot;
		s_Data.Texture[s_Data.TextureSlot] = texture;
		s_Data.TextureSlot++;
	}

	for (int i = 0; i < 4; i++)
	{
		s_Data.QuadVertexDataPtr->Position = transform * s_Data.QuadVertexPosition[i];
		s_Data.QuadVertexDataPtr->Color = color;
		s_Data.QuadVertexDataPtr->TexCoord = texCoord[i];
		s_Data.QuadVertexDataPtr->TexIndex = texIndex;
		s_Data.QuadVertexDataPtr++;
	}

	s_Data.QuadIndicesCount += 6;

	EndScene();
}

void Renderer::DrawFixedQuad(const glm::mat4& transform, const glm::vec4& color)
{
	// Temp, TODO: remove.
	s_Data.FixedTextureShader->Bind();

	glm::vec2 texCoord[4] = {
		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f}
	};

	float texIndex = 0.0f;

	for (int i = 0; i < 4; i++)
	{
		s_Data.QuadVertexDataPtr->Position = transform * s_Data.QuadVertexPosition[i];
		s_Data.QuadVertexDataPtr->Color = color;
		s_Data.QuadVertexDataPtr->TexCoord = texCoord[i];
		s_Data.QuadVertexDataPtr->TexIndex = texIndex;
		s_Data.QuadVertexDataPtr++;
	}

	s_Data.QuadIndicesCount += 6;
	EndScene();
}

void Renderer::DrawFixedQuad(const glm::mat4& transform, const std::shared_ptr<Texture>& texture, const glm::vec4& tintColor)
{
	// Temp, TODO: remove.
	s_Data.FixedTextureShader->Bind();

	glm::vec4 color = tintColor;//{ 1.0f, 1.0f, 1.0f, 1.0f };

	glm::vec2 texCoord[4] = {
		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f}
	};

	float texIndex = 0.0f;

	for (int i = 1; i < s_Data.TextureSlot; i++)
	{
		if (*texture.get() == *s_Data.Texture[i].get())
		{
			texIndex = (float)i;
			break;
		}
	}

	if (texIndex == 0.0f)
	{
		texIndex = (float)s_Data.TextureSlot;
		s_Data.Texture[s_Data.TextureSlot] = texture;
		s_Data.TextureSlot++;
	}

	for (int i = 0; i < 4; i++)
	{
		s_Data.QuadVertexDataPtr->Position = transform * s_Data.QuadVertexPosition[i];
		s_Data.QuadVertexDataPtr->Color = color;
		s_Data.QuadVertexDataPtr->TexCoord = texCoord[i];
		s_Data.QuadVertexDataPtr->TexIndex = texIndex;
		s_Data.QuadVertexDataPtr++;
	}

	s_Data.QuadIndicesCount += 6;

	EndScene();
}