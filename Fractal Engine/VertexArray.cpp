#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray() {
	GLCall(glGenVertexArrays(1, &renderer));
}
VertexArray::~VertexArray() {
	GLCall(glDeleteVertexArrays(1, &renderer));
}
void VertexArray::Add(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	Bind();
	vb.Bind();
	GLCall(const std::vector<VertexBufferElement> & el = layout.GetElements());
	unsigned int offset = 0;
	for (unsigned int i = 0; i < el.size(); i++) {
		const VertexBufferElement& element = el[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	}
}
void VertexArray::Bind() const {
	GLCall(glBindVertexArray(renderer));
}
void VertexArray::Unbind() const {
	GLCall(glBindVertexArray(0));
}