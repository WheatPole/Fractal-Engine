#pragma once
#include "Includes.h"

class Fractal {
public:
	Fractal();
	//store how much does the rotation change, how much shorter (larger) are the new positions in comparison with the old ones (, and the new positionsl
	//maybe use this?
	//for the new positions use: how much does it go up/down/left/right DIVIDED by how much does the scale change (correct)? also don't forget to rotate the object
	//or this:
	// px1    px2
	//-----=------
	// px2    px3
	//not sure if this second idea would work though (it won't)
	void Recurse(int start, int finish);
	~Fractal();
};