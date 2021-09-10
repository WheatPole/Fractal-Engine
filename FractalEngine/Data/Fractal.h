#pragma once

#include "Includes.h"

class Fractal {
	std::vector<std::tuple<float, float, float, float>> startingLines;
	std::vector<std::vector<std::tuple<float, float, float, float>>> endingLines;
	
public:
	Fractal(std::vector<std::tuple<float, float, float, float>> starting, std::vector<std::vector<std::tuple<float, float, float, float>>> ending, int fracMode);
	void Recurse(GLFWwindow* window, Renderer renderer, Shader shader, int iterations, int& fractalMode);
	~Fractal();
};