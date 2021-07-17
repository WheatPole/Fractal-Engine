#pragma once

#include <GL/glew.h>
#include <iostream>
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLPrintError(#x, __LINE__))


void GLClearError();

bool GLPrintError(const char* function, int line);

class Renderer {

public:
	void Rect(Renderer rend, Shader shader, float x1, float y1, float x2, float y2, bool fill) const;
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, GLuint mode) const;
	void Line(Renderer rend, Shader shader, float x1, float y1, float x2, float y2) const;
};