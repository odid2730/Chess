#pragma once

#include "Buffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vb);
	void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ib);

	void Bind();
	void Unbind();

	static std::shared_ptr<VertexArray> Create();

private:
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;

	uint32_t m_RendererID = 0;
};