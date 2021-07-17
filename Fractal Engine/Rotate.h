#pragma once
#include "Includes.h"


void Rotate(std::vector<std::tuple<float, float, float, float, int>>& selected, std::tuple<float, float> middle,  float angle) {

	for (size_t i = 0; i < selected.size(); i++) {
		float len = std::get<2>(selected[i]);
		float& rot = std::get<3>(selected[i]);

		float& x = std::get<0>(selected[i]);
		float& y = std::get<1>(selected[i]);
		
		float tempx = x;
		float tempy = y;
		tempx -= std::get<0>(middle);
		tempy -= std::get<1>(middle);
		x = tempx * cos(angle) - tempy * sin(angle);
		y = tempx * sin(angle) + tempy * cos(angle);
		x += std::get<0>(middle);
		y += std::get<1>(middle);
		//std::cout << tempx << " " << tempy << " " << x << " " << y << std::endl;
		rot += angle;
		if (rot <= -tau / 2) {
			rot = (float)tau - rot;
		}
		else if (rot >= tau / 2) {
			rot = -(float)tau + rot;
		}
		std::cout << rot << " ";
	}
	std::cout << std::endl;
}
void Rotate(std::vector<std::tuple<float, float, float, float, int>>& selected, std::tuple<float, float> middle, float angle, float& rotchange) {

	for (size_t i = 0; i < selected.size(); i++) {
		float len = std::get<2>(selected[i]);
		float& rot = std::get<3>(selected[i]);

		float& x = std::get<0>(selected[i]);
		float& y = std::get<1>(selected[i]);

		float tempx = x;
		float tempy = y;
		tempx -= std::get<0>(middle);
		tempy -= std::get<1>(middle);
		x = tempx * cos(angle) - tempy * sin(angle);
		y = tempx * sin(angle) + tempy * cos(angle);
		x += std::get<0>(middle);
		y += std::get<1>(middle);
		//std::cout << tempx << " " << tempy << " " << x << " " << y << std::endl;
		rot += angle;
		if (rot <= -tau / 2) {
			rot = (float)tau - rot;
		}
		else if (rot >= tau / 2) {
			rot = -(float)tau + rot;
		}
		
		std::cout << rot << " ";
	}
	rotchange += angle;
	std::cout << std::endl;
}