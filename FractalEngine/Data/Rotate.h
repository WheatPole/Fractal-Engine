#pragma once
#include "Includes.h"


void Rotate(std::vector<std::tuple<float, float, float, float, int>>& selected, std::tuple<float, float> middle,  float angle) {

	for (size_t i = 0; i < selected.size(); i++) {
		float& len = std::get<2>(selected[i]);
		float& rot = std::get<3>(selected[i]);

		float& x1 = std::get<0>(selected[i]);
		float& y1 = std::get<1>(selected[i]);
		float x2;
		float y2;
		{
			float b = len * sin(rot);
			float a = len * cos(rot);
			x2 = x1 + a;
			y2 = y1 + b;
		}


		float tempx1 = x1;
		float tempy1 = y1;
		tempx1 -= std::get<0>(middle);
		tempy1 -= std::get<1>(middle);
		x1 = tempx1 * cos(angle) - tempy1 * sin(angle);
		y1 = tempx1 * sin(angle) + tempy1 * cos(angle);
		x1 += std::get<0>(middle);
		y1 += std::get<1>(middle);

		

		float tempx2 = x2;
		float tempy2 = y2;
		tempx2 -= std::get<0>(middle);
		tempy2 -= std::get<1>(middle);
		x2 = tempx2 * cos(angle) - tempy2 * sin(angle);
		y2 = tempx2 * sin(angle) + tempy2 * cos(angle);
		x2 += std::get<0>(middle);
		y2 += std::get<1>(middle);
		
		float tempnum1 = abs(x2 - x1);
		float tempnum2 = abs(y2 - y1);

		len = sqrt(tempnum1 * tempnum1 + tempnum2 * tempnum2);

		rot = acos(tempnum1/len);
		if (y2 - y1 <= 0) {
			rot = -rot;
		}
		if (x1 >= x2) {
			rot = (float)(pi - abs(rot)) * (rot / abs(rot));
		}
	}
}
void Rotate(std::vector<std::tuple<float, float, float, float, int>>& selected, std::tuple<float, float> middle, float angle, float& rotchange) {

	for (size_t i = 0; i < selected.size(); i++) {
		float& len = std::get<2>(selected[i]);
		float& rot = std::get<3>(selected[i]);

		float& x1 = std::get<0>(selected[i]);
		float& y1 = std::get<1>(selected[i]);
		float x2;
		float y2;
		{
			float b = len * sin(rot);
			float a = len * cos(rot);
			x2 = x1 + a;
			y2 = y1 + b;
		}


		float tempx1 = x1;
		float tempy1 = y1;
		tempx1 -= std::get<0>(middle);
		tempy1 -= std::get<1>(middle);
		x1 = tempx1 * cos(angle) - tempy1 * sin(angle);
		y1 = tempx1 * sin(angle) + tempy1 * cos(angle);
		x1 += std::get<0>(middle);
		y1 += std::get<1>(middle);

		

		float tempx2 = x2;
		float tempy2 = y2;
		tempx2 -= std::get<0>(middle);
		tempy2 -= std::get<1>(middle);
		x2 = tempx2 * cos(angle) - tempy2 * sin(angle);
		y2 = tempx2 * sin(angle) + tempy2 * cos(angle);
		x2 += std::get<0>(middle);
		y2 += std::get<1>(middle);
		
		float tempnum1 = abs(x2 - x1);
		float tempnum2 = abs(y2 - y1);

		len = sqrt(tempnum1 * tempnum1 + tempnum2 * tempnum2);

		rot = acos(tempnum1/len);
		if (y2 - y1 <= 0) {
			rot = -rot;
		}
		if (x1 >= x2) {
			rot = (float)(pi - abs(rot)) * (rot / abs(rot));
		}
	
		rotchange += angle;
	}
}