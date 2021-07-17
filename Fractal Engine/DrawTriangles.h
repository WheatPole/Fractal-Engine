#pragma once
#include "Includes.h"
#include <algorithm>
//falied
















bool contains(std::vector<std::tuple<std::tuple<float, float>, std::tuple<float, float>>> a, std::tuple<std::tuple<float, float>, std::tuple<float, float>> b) {
	for (int i = 0; i < a.size(); i++) {
		if (std::get<0>(std::get<0>(a[i])) == std::get<0>(std::get<0>(b)) &&
			std::get<0>(std::get<1>(a[i])) == std::get<0>(std::get<1>(b)) &&
			std::get<1>(std::get<1>(a[i])) == std::get<1>(std::get<1>(b)) &&
			std::get<1>(std::get<0>(a[i])) == std::get<1>(std::get<0>(b))) {
			return true;
		}
	}
	return false;
}

bool HasTwoLines(std::vector<std::tuple<std::tuple<float, float>, std::tuple<float, float>>> a, std::tuple<float, float> b) {
	int comparisons = 0;
	for (int i = 0; i < a.size(); i++) {
		if ((std::get<0>(std::get<0>(a[i])) == std::get<0>(b) && 
			std::get<0>(std::get<1>(a[i])) == std::get<1>(b)) ||
			(std::get<1>(std::get<0>(a[i])) == std::get<0>(b) &&
			std::get<1>(std::get<1>(a[i])) == std::get<1>(b))) { //maybe needs a fix
			comparisons++;
			if (comparisons >= 2)
				return true;
		}
	}
	return false;
}

std::tuple<std::tuple<float, float>, std::tuple<float, float>> Reverse(std::tuple<std::tuple<float, float>, std::tuple<float, float>> a) {
	auto temp = std::get<0>(a);
	std::get<0>(a) = std::get<1>(a);
	std::get<1>(a) = temp;
	return a;
}

void DrawTriangles(Renderer renderer, Shader shader, std::vector<std::tuple<float, float>> positions) {
	std::vector<std::tuple<std::tuple<float, float>, std::tuple<float, float>>> linePositions;
	
	std::vector<unsigned int> indicies;

	float* poses = new float[positions.size() * 2];
	int k = 0;
	int t = 0;
	for (int i = 0; i < positions.size(); i++) {
		//Find the vertex with the lowest distance from the current vertex;
		//O(n*n-n), probably could be optimized;

		poses[t] = std::get<0>(positions[i]);
		t++;
		poses[t] = std::get<1>(positions[i]);
		t++;
		
		float smallestSum = 99999.0;
		int temp = -1;
		std::tuple<std::tuple<float, float>, std::tuple<float, float>> pos;
		for (int j = 0; j < positions.size(); j++) {
			if (j != i) {
				float currSumX = abs(std::get<0>(positions[i]) - std::get<0>(positions[j]));
				float currSumY = abs(std::get<1>(positions[i]) - std::get<1>(positions[j]));
				float currSum = currSumX + currSumY;
				if (currSum < smallestSum) {
					std::tuple<std::tuple<float, float>, std::tuple<float, float>> aaa;
					aaa = std::make_tuple(positions[i], positions[j]);
					if (!contains(linePositions, aaa)/* && !contains(linePositions, Reverse(aaa))/*!HasTwoLines(linePositions, std::get<1>(aaa)) && !HasTwoLines(linePositions, std::get<0>(aaa)*/) {
						temp = j;
						pos = aaa;
						indicies.push_back(i);
						indicies.push_back(temp);
						smallestSum = currSum;
					}
				}
			}
		}
		if (temp != -1) {
			
			linePositions.push_back(pos);
			
		}
	}
	unsigned int* ind = new unsigned int[indicies.size()];
	std::copy(indicies.begin(), indicies.end(), ind);
	VertexBuffer vb(poses, positions.size() * 2 * sizeof(float)); //fix
	IndexBuffer ib(ind, indicies.size(), 0);

	VertexArray va;
	VertexBufferLayout vbl;

	vbl.Push<float>(2);

	va.Add(vb, vbl);

	renderer.Draw(va, ib, shader, GL_LINES);
}