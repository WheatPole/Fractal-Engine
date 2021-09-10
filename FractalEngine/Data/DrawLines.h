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

	//failed idea

	/*unsigned int* indicies = new unsigned int[positions.size()];

	unsigned int* indiciesForTheTriangle = new unsigned int[(positions.size()*2)-2];
	
	float* pos = new float[positions.size() * 2];

	

	int j = 0;
	int k = 0;
	for (int i = 0; i < positions.size(); i++) {
		if (positions.size() * 2 - 2 > 1) {
			if (i != positions.size()-1) {
				if (i % 2 == 0) {
					indiciesForTheTriangle[k] = i;
					indiciesForTheTriangle[k + 1] = i + 1;
					k += 2;
				}
			}
		}
		pos[j] = std::get<0>(positions[i]);
		pos[j + 1] = std::get<1>(positions[i]);
		j += 2;
		indicies[i] = i;

	}

	IndexBuffer ib(indicies, positions.size(), 0);
	IndexBuffer ib2(indiciesForTheTriangle, positions.size(), 0);
	VertexBuffer vb(pos, positions.size() * 2 * sizeof(float));

	points.Add(vb, vbl);
	renderer.Draw(points, ib, shader, GL_POINTS);
	renderer.Draw(points, ib2, shader, GL_LINES);
	points.Unbind();
	ib.Unbind();
	ib2.Unbind();
	vb.Unbind();*/
}