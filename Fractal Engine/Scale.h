#pragma once
#include "Includes.h"

std::tuple<float, float, float, float> FindEdges(std::vector<std::tuple<float, float, float, float,int>>& selected) {
	float leftmostpoint = 99.0f;
	float lowermostpoint = 99.0f;
	float uppermostpoint = -99.0f;
	float rightmostpoint = -99.0f;
	for (size_t i = 0; i < selected.size(); i++) {
		float len = std::get<2>(selected[i]);
		float rot = std::get<3>(selected[i]);

		float b = len * sin(rot);
		float a = len * cos(rot);

		float x1 = std::get<0>(selected[i]);
		float y1 = std::get<1>(selected[i]);
		float x2 = x1 + a;
		float y2 = y1 + b;
		bool Ybelowzero = rot < 0;
		bool Xbelowzero = abs(rot) > /*NOT 90 YOU IDIOT*/tau / 4;
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
	}
	return std::make_tuple(leftmostpoint, rightmostpoint, uppermostpoint, lowermostpoint);
}
																											      //-1-left,1-right//1-upper,-1-lower
void Scale(std::vector<std::tuple<float, float, float, float, int>>& selected, unsigned int whichXSide, unsigned int whichYSide, float xchange, float ychange, std::tuple<float, float>& middle) {
	auto edges = FindEdges(selected);
	std::cout << std::get<0>(edges) << " " << std::get<1>(edges) << " " << std::get<2>(edges) << " " << std::get<3>(edges) << std::endl;
	auto newEdges = edges;
	float y = 1, newy = 1;
	if (whichXSide == -1) {
		std::get<0>(newEdges) += xchange;
	}
	else if (whichXSide == 1) {
		std::get<1>(newEdges) -= xchange;
	}
	if (whichYSide == 1) {
		std::get<3>(newEdges) += ychange;
	}
	else if (whichYSide == -1) {
		std::get<2>(newEdges) -= ychange;
	}

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

	for (size_t i = 0; i < selected.size(); i++) {
		float len = std::get<2>(selected[i]);
		float rot = std::get<3>(selected[i]);
		float x2;
		float y2;
		float x1 = std::get<0>(selected[i]);
		float y1 = std::get<1>(selected[i]);
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
		if (whichXSide == -1 || whichXSide == 1) {
			float lenx = abs(std::get<0>(edges) - std::get<1>(edges));
			float newlenx = abs(std::get<0>(newEdges) - std::get<1>(newEdges));

			float b1 = lenx - (x1- std::get<0>(edges));
			float a1 = lenx - b1;

			float d1 = (newlenx / lenx) * b1;
			float c1 = newlenx - d1;

			float b2 = lenx - (x2- std::get<0>(edges));
			float a2 = lenx - b2;

			float d2 = (newlenx / lenx) * b2;
			float c2 = newlenx - d2;
			newx1 = c1 + std::get<0>(newEdges);
			newx2 = c2 + std::get<0>(newEdges);
		}
		/*else if (whichXSide == 1) {
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
			newx1 = c1 + std::get<0>(edges);
			newx2 = c2 + std::get<0>(edges);
		}*/
		if (whichYSide == -1 || whichYSide == 1) {
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
		/*else if (whichYSide == -1) {
			float leny = abs(std::get<3>(edges) - std::get<2>(edges));
			float newleny = abs(std::get<3>(newEdges) - std::get<2>(newEdges));

			float b1 = leny - (x1 - std::get<3>(edges));
			float a1 = leny - b1;

			float d1 = (newleny / leny) * b1;
			float c1 = newleny - d1;

			float b2 = leny - (x2 - std::get<3>(edges));
			float a2 = leny - b2;

			float d2 = (newleny / leny) * b2;
			float c2 = newleny - d2;
			newy1 = c1 + std::get<3>(newEdges);
			newy2 = c2 + std::get<3>(newEdges);
		}*/


		//float ratio1 = std::get<0>(edges) / std::get<0>(newEdges);
		/*if (whichXSide == -1) {
		float ratio2 = std::get<1>(edges) / std::get<1>(newEdges);
		newx1 = abs(x1 / ratio1)*(abs(std::get<0>(newEdges))/ std::get<0>(newEdges));
		newx2 = abs(x2 / ratio2) * (abs(std::get<0>(newEdges)) / std::get<0>(newEdges));
		}
		else if (whichXSide == 1) {

		}*/
		//if (whichYSide == -1)
		/*newx1 = x1 * (newx / x);
		float newx2 = x2 * (newx / x);
		float newy1 = y1 * (newy / y);
		float newy2 = y2 * (newy / y);*/


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
			selected[i] = std::make_tuple(newx1, newy1, len, rot, std::get<4>(selected[i]));
		}
	}
	middle = FindMiddle(selected);
}