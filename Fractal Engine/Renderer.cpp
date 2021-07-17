#include "Renderer.h"
#include <GL/glew.h>
#include <iostream>
#include "VertexBufferLayout.h"

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLPrintError(const char* function, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[Open GL Error] (" << error << "): Function:" << function << " Line: " << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, GLuint mode) const {
	va.Bind();
	ib.Bind();
	shader.Bind();
	GLCall(glDrawElements(mode, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
	va.Unbind();
	ib.Unbind();
	shader.Bind();
}

void Renderer::Clear() const {
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
void Renderer::Rect(Renderer rend, Shader shader, float x1, float y1, float x2, float y2) const {
	float debug[] = {
		x1, y1,
		x2, y1,
		x2, y2,
		x1, y2
	};

	unsigned int indices[] = {
		0, 1, 1, 2, 2, 3, 3, 0
	};

	VertexArray va;
	VertexBufferLayout vbl;
	vbl.Push<float>(2);
	VertexBuffer vb(debug, 4 * 2 * sizeof(float));
	IndexBuffer ib(indices, 8, 0);
	va.Add(vb, vbl);
	rend.Draw(va, ib, shader, GL_LINES);
}
void Renderer::Line(Renderer rend, Shader shader, float x1, float y1, float x2, float y2) const {
	float debug[] = {
		x1, y1,
		x2, y2
	};

	unsigned int indices[] = {
		0, 1
	};

	VertexArray va;
	VertexBufferLayout vbl;
	vbl.Push<float>(2);
	VertexBuffer vb(debug, 2 * 2 * sizeof(float));
	IndexBuffer ib(indices, 2, 0);
	va.Add(vb, vbl);
	rend.Draw(va, ib, shader, GL_LINES);
}