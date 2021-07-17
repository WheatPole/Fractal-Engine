#pragma once
#include "Includes.h"

class Fractal {
	std::vector<std::tuple<float, float, float, float>> startingLines;
	std::vector<std::vector<std::tuple<float, float, float, float, float>>> endingLines;
public:
	Fractal(std::vector<std::tuple<float, float, float, float>> starting, std::vector<std::vector<std::tuple<float, float, float, float, float>>> ending);
	//store how much does the rotation change, how much shorter (larger) are the new positions in comparison with the old ones (, and the new positionsl
	//maybe use this?
	//for the new positions use: how much does it go up/down/left/right DIVIDED by how much does the scale change (correct)? also don't forget to rotate the object
	//or this:
	// px1    px2
	//-----=------
	// px2    px3
	//not sure if this second idea would work though (it won't)
	void Recurse(Renderer renderer, Shader shader, int iterations);
	~Fractal();
};