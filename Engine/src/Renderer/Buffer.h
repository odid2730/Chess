#pragma once

enum class ShaderDataType
{
	Int, Int2, Int3, Int4,
	Float, Float2, Float3, Float4,
	Mat3, Mat4,
	Bool
};

static uint32_t ShaderDataTypeToCount(ShaderDataType type)
{
	switch (type)
	{
		case ShaderDataType::Int:		return 1;
		case ShaderDataType::Int2:		return 2;
		case ShaderDataType::Int3:		return 3;
		case ShaderDataType::Int4:		return 4;
		case ShaderDataType::Float:		return 1;
		case ShaderDataType::Float2:	return 2;
		case ShaderDataType::Float3:	return 3;
		case ShaderDataType::Float4:	return 4;
		case ShaderDataType::Mat3:		return 3 * 3;
		case ShaderDataType::Mat4:		return 4 * 4;
		case ShaderDataType::Bool:		return 1;
	}
}

static uint32_t ShaderDataTypeToSize(ShaderDataType type)
{
	switch (type)
	{
		case ShaderDataType::Int:		return 1 * 4;
		case ShaderDataType::Int2:		return 2 * 4;
		case ShaderDataType::Int3:		return 3 * 4;
		case ShaderDataType::Int4:		return 4 * 4;
		case ShaderDataType::Float:		return 1 * 4;
		case ShaderDataType::Float2:	return 2 * 4;
		case ShaderDataType::Float3:	return 3 * 4;
		case ShaderDataType::Float4:	return 4 * 4;
		case ShaderDataType::Mat3:		return 3 * 3 * 4;
		case ShaderDataType::Mat4:		return 4 * 4 * 4;
		case ShaderDataType::Bool:		return 1;
	}
}

struct BufferElement
{
	std::string Name;
	uint32_t Count;
	uint32_t Size;
	ShaderDataType Type;
	bool Normalized;
	uint32_t Offset;

	BufferElement(const std::string& name, ShaderDataType type)
		: Name(name), Count(ShaderDataTypeToCount(type)), Size(ShaderDataTypeToSize(type)), Type(type), Normalized(false), Offset(0)
	{
		
	}
};

class BufferLayout
{
public:
	BufferLayout() = default;
	BufferLayout(const std::initializer_list<BufferElement>& elements)
		: m_Elements(elements)
	{
		CalculateStrideAndOffset();
	}

	uint32_t GetStride() const { return m_Stride; }

	std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
	std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
	std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
	std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

private:
	void CalculateStrideAndOffset()
	{
		uint32_t offset = 0;
		for (auto& element : m_Elements)
		{
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;
		}
	}

	uint32_t m_Stride = 0;
	std::vector<BufferElement> m_Elements;
};

class VertexBuffer
{
public:
	VertexBuffer() = default;
	VertexBuffer(float* vertices, uint32_t size);
	VertexBuffer(uint32_t size);
	~VertexBuffer();
	
	void SetData(void* data, uint32_t size);

	void Bind() const;
	void Unbind();
	
	void SetLayout(const BufferLayout& layout) { m_BufferLayout = layout; }
	const BufferLayout& GetLayout() const { return m_BufferLayout; }

	static std::shared_ptr<VertexBuffer> Create(float* vertices, uint32_t size);
	static std::shared_ptr<VertexBuffer> Create(uint32_t size);
private:
	uint32_t m_RendererID = 0;
	BufferLayout m_BufferLayout;
};

class IndexBuffer
{
public:
	IndexBuffer() = default;
	IndexBuffer(uint32_t* indices, int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind();

	static std::shared_ptr<IndexBuffer> Create(uint32_t* indices, int count);
private:
	uint32_t m_RendererID = 0;
};