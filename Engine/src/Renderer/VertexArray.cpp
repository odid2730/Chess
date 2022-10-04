#include "pch.h"
#include "VertexArray.h"

#include <glad/glad.h>

static GLenum ShaderDataTypeToGLType(ShaderDataType type)
{
	switch (type)
	{
		case ShaderDataType::Int:		return GL_INT;
		case ShaderDataType::Int2:		return GL_INT;
		case ShaderDataType::Int3:		return GL_INT;
		case ShaderDataType::Int4:		return GL_INT;
		case ShaderDataType::Float:		return GL_FLOAT;
		case ShaderDataType::Float2:	return GL_FLOAT;
		case ShaderDataType::Float3:	return GL_FLOAT;
		case ShaderDataType::Float4:	return GL_FLOAT;
		case ShaderDataType::Mat3:		return GL_FLOAT;
		case ShaderDataType::Mat4:		return GL_FLOAT;
		case ShaderDataType::Bool:		return GL_BOOL;
	}
}

VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vb)
{
	m_VertexBuffer = vb;
	glBindVertexArray(m_RendererID);
	vb->Bind();

	const auto& layout = vb->GetLayout();

	size_t index = 0;
	for (auto& element : layout)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, element.Count, ShaderDataTypeToGLType(element.Type), element.Normalized, layout.GetStride(), (const void*)element.Offset);
		index++;
	}
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ib)
{
	m_IndexBuffer = ib;
	glBindVertexArray(m_RendererID);
	ib->Bind();
}

void VertexArray::Bind()
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

std::shared_ptr<VertexArray> VertexArray::Create()
{
	return std::shared_ptr<VertexArray>(new VertexArray());
}
