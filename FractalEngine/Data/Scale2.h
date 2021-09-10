#pragma once
#include "Includes.h" 

inline std::tuple<float, float, float, float> FindEdges(std::tuple<float, float, float, float>& selected) {
	float leftmostpoint = 99.0f;
	float lowermostpoint = 99.0f;
	float uppermostpoint = -99.0f;
	float rightmostpoint = -99.0f;
	float len = std::get<2>(selected);
	float rot = std::get<3>(selected);

	float b = len * sin(rot);
	float a = len * cos(rot);

	float x1 = std::get<0>(selected);
	float y1 = std::get<1>(selected);
	float x2 = x1 + a;
	float y2 = y1 + b;
	bool Ybelowzero = rot < 0;
	bool Xbelowzero = abs(rot) > tau / 4;
	if (Ybelowzero) {
		if (lowermostpoint > y2)
			lowermostpoint = y2;
		if (uppermostpoint < y1)
			uppermostpoint = y1;
	}
	else {
		if (lowermostpoint > y1)
			lowermostpoint = y1;
		if (uppermostpoint < y2)
			uppermostpoint = y2;
	}
	if (Xbelowzero) {
		if (rightmostpoint < x1)
			rightmostpoint = x1;
		if (leftmostpoint > x2)
			leftmostpoint = x2;
	}
	else {
		if (rightmostpoint < x2)
			rightmostpoint = x2;
		if (leftmostpoint > x1)
			leftmostpoint = x1;
	}
	return std::make_tuple(leftmostpoint, rightmostpoint, uppermostpoint, lowermostpoint);
}

void ScaleAllNew(std::tuple<float, float, float, float>& selected, float xchange, float ychange) {
	auto edges = FindEdges(selected);
	//std::cout << std::get<0>(edges) << " " << std::get<1>(edges) << " " << std::get<2>(edges) << " " << std::get<3>(edges) << std::endl;
	auto newEdges = edges;
	std::get<0>(newEdges) += xchange;
	std::get<1>(newEdges) -= xchange;
	std::get<3>(newEdges) += ychange;
	std::get<2>(newEdges) -= ychange;

	/*float lenx = abs(std::get<0>(edges)) + abs(std::get<1>(edges));
	float leny = abs(std::get<2>(edges)) + abs(std::get<3>(edges));
	float newlenx = abs(std::get<0>(newEdges)) + abs(std::get<1>(newEdges));
	float newleny = abs(std::get<2>(newEdges)) + abs(std::get<3>(newEdges));*/
	/*
	if (x)
	x = std::get<0>(edges) - std::get<1>(edges));
	float y = abs(std::get<2>(edges) - std::get<3>(edges));
	float newx = abs(std::get<0>(newEdges) - std::get<1>(newEdges));
	float newy = abs(std::get<2>(newEdges) - std::get<3>(newEdges));*/

	float len = std::get<2>(selected);
	float rot = std::get<3>(selected);
	float x2;
	float y2;
	float x1 = std::get<0>(selected);
	float y1 = std::get<1>(selected);
	{
		float b = len * sin(rot);
		float a = len * cos(rot);
		x2 = x1 + a;
		y2 = y1 + b;
	}


	//lenx / newlenx = (x1-lenx) / newx1

	float newx1 = x1;
	float newx2 = x2;
	float newy1 = y1;
	float newy2 = y2;
	/*if (whichXSide == -1)
		a1 = x - newx;
	else
		a1 = x;*/
	{
		float lenx = abs(std::get<0>(edges) - std::get<1>(edges));
		float newlenx = abs(std::get<0>(newEdges) - std::get<1>(newEdges));

		float b1 = lenx - (x1 - std::get<0>(edges));
		float a1 = lenx - b1;

		float d1 = (newlenx / lenx) * b1;
		float c1 = newlenx - d1;

		float b2 = lenx - (x2 - std::get<0>(edges));
		float a2 = lenx - b2;

		float d2 = (newlenx / lenx) * b2;
		float c2 = newlenx - d2;
		newx1 = c1 + std::get<0>(newEdges);
		newx2 = c2 + std::get<0>(newEdges);
	}
	{
		float leny = abs(std::get<3>(edges) - std::get<2>(edges));
		float newleny = abs(std::get<3>(newEdges) - std::get<2>(newEdges));

		float b1 = leny - (y1 - std::get<3>(edges));
		float a1 = leny - b1;

		float d1 = (newleny / leny) * b1;
		float c1 = newleny - d1;

		float b2 = leny - (y2 - std::get<3>(edges));
		float a2 = leny - b2;

		float d2 = (newleny / leny) * b2;
		float c2 = newleny - d2;
		newy1 = c1 + std::get<3>(newEdges);
		newy2 = c2 + std::get<3>(newEdges);
	}


	//std::cout << "Old: " << x1 << " " << y1 << ", " << x2 << " " << y2 << ", new: " << newx1 << " " << newy1 << ", " << newx2 << " " << newy2 << std::endl;
	bool left = false;
	if (newx1 >= newx2)
		left = true;
	float num1 = abs(newx1 - newx2);
	float num2 = abs(newy1 - newy2);
	len = sqrt(num1 * num1 + num2 * num2);
	//rotation of a line
	rot = acos(num1 / len)/**180/3.14159265358979323846*/; //remove the comment for degrees
	if (newy2 - newy1 <= 0) {
		rot = -rot;
	}
	if (left) {
		rot = (float)(pi - abs(rot)) * (rot / abs(rot));
	}
	if (rot >= -185 && rot <= 185) {
		selected = std::make_tuple(newx1, newy1, len, rot);
	}
}