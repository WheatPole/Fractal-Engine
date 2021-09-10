#pragma once
#include "Includes.h"

void DrawLines(Renderer& renderer, VertexBufferLayout& vbl, Shader& shader, std::vector<std::tuple<float, float, float, float>>& positions) {

	for (size_t i = 0; i < positions.size(); i++) {

		VertexArray currLine;
		float len = std::get<2>(positions[i]);
		float rot = std::get<3>(positions[i]);
		float b = len * sin(rot);
		float a = len * cos(rot);
		
		float startingX = std::get<0>(positions[i]);
		float startingY = std::get<1>(positions[i]);
		float finishingX = startingX + a;
		float finishingY = startingY + b;

		float poses[4] = {
			startingX, startingY,
			finishingX, finishingY
		};
		unsigned int ind[2] = {
			0, 1
		};
		VertexBuffer aa(poses, 4 * sizeof(float));
		IndexBuffer bb(ind, 2, 0);
		currLine.Add(aa, vbl);
		renderer.Draw(currLine, bb, shader, GL_LINES);
		
	}

	
}