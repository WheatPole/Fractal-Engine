#include "Shader.h"

#include "Renderer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(const std::string& filepath)
	: filepathh(filepath), renderer(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	renderer = CreateShader(source.VertexSource, source.FragmentSource);
}
Shader::~Shader() {
	GLCall(glDeleteProgram(renderer));
}
void Shader::Bind() const {
	GLCall(glUseProgram(renderer));
}
void Shader::Unbind() const {
	GLCall(glUseProgram(0))
}
ShaderProgramSource Shader::ParseShader(const std::string& filepath) {
	std::ifstream stream(filepath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}
unsigned int Shader::CompileShader(const std::string& source, unsigned int type) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (!result) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
unsigned int Shader::GetUniformLocation(const std::string& name) {
	if (unicachetable.find(name) != unicachetable.end()) {
		return unicachetable[name];
	}
	GLCall(int location = glGetUniformLocation(renderer, name.c_str()));
	if (location == -1) {
		std::cout << "Warning: uniform '" << name << "' doesn't exist" << std::endl;
	}
	unicachetable[name] = location;

	return location;
}
void Shader::SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4) {
	GLCall(glUniform4f(GetUniformLocation(name), v1, v2, v3, v4));
}