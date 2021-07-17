#pragma once
#include "Includes.h"

void DrawSelectedLines(Renderer& renderer, Shader& shader, std::vector<std::tuple<float, float, float, float, int>>& selected, bool green) {
	if (!green)
		shader.SetUniform4f("u_Colour", 0.0, 1.0, 1.0, 1.0);
	else 
		shader.SetUniform4f("u_Colour", 0.0, 1.0, 0.3, 1.0);
	for (size_t i = 0; i < selected.size(); i++) {
		float len = std::get<2>(selected[i]);
		float rot = std::get<3>(selected[i]);
		float b = len * sin(rot);
		float a = len * cos(rot);

		float startingX = std::get<0>(selected[i]);
		float startingY = std::get<1>(selected[i]);
		float finishingX = startingX + a;
		float finishingY = startingY + b;
		renderer.Line(renderer, shader, startingX, startingY, finishingX, finishingY);
	}
}