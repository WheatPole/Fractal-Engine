#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray {
	unsigned int renderer;
public:
	VertexArray();
	~VertexArray();

	void Add(const VertexBuffer& buffer, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};