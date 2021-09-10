#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#define pi 3.14159265358979323846264
#define tau pi*2 //:(
extern void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
extern int fm;
extern std::vector<float> currRotChange;