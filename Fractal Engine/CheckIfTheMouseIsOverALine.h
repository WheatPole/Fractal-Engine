#include "Includes.h"

bool contains(std::vector<std::tuple<float, float, float, float, int>>& selected, std::tuple<float, float, float> xy) {
	for (size_t i = 0; i < selected.size(); i++) {
		if (std::get<0>(selected[i]) == std::get<0>(xy) && std::get<1>(selected[i]) == std::get<1>(xy) && std::get<3>(selected[i]) == std::get<2>(xy))
			return true;
	}
	return false;
}

std::tuple<float, float> FindMiddle(std::vector<std::tuple<float, float, float, float, int>>& selected) {
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
		bool Xbelowzero = abs(rot) > /*NOT 90 YOU IDIOT*/pi / 2;
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
	float x = (leftmostpoint + rightmostpoint) / 2;
	float y = (uppermostpoint + lowermostpoint) / 2;
	return std::make_tuple(x, y);
}

std::tuple<float, float, float, float> FindLRUL(std::vector<std::tuple<float, float, float, float, int>>& selected) {
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
		bool Xbelowzero = abs(rot) > /*NOT 90 YOU IDIOT*/pi / 2;
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

//maybe add a slide mode?
void CheckIfTheMouseIsOverALine(GLFWwindow* window, Renderer& renderer, int& width, int& height, std::vector<std::tuple<float, float, float, float>>& positions, std::vector<std::tuple<float, float, float, float, int>>& selected, bool& editclick, std::tuple<float, float>& middle) {
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1);
	if (state == GLFW_PRESS) { //add the clicked bool
		if (!editclick) {
			editclick = true;
			for (size_t i = 0; i < positions.size(); i++) {
				float len = std::get<2>(positions[i]);
				float rot = std::get<3>(positions[i]);

				float b = len * sin(rot);
				float a = len * cos(rot);

				float x1 = std::get<0>(positions[i]);
				float y1 = std::get<1>(positions[i]);
				float x2 = x1 + a;
				float y2 = y1 + b;
				//function
				double k = (y1 - y2) / (x1 - x2);


				double closesty = 9999.0f;
				double closestx = 9999.0f;

				//			|
				//			|
				//			|
				//-------mouseptr------
				//			|
				//			|
				//			|

				float helper = 0.03f;

				double mouseX, mouseY;
				glfwGetCursorPos(window, &mouseX, &mouseY);
				mouseX = 1 - (mouseX / (width / 2));
				mouseY = 1 - (mouseY / (height / 2));
				mouseX = -mouseX;
				//if (rot == 0)?
				bool Ybelowzero = rot < 0;
				bool validY = (Ybelowzero) ? (mouseY-helper <= y1) && (mouseY+helper >= y2) : (mouseY-helper <= y2) && (mouseY+helper >= y1);
				bool Xbelowzero = abs(rot) > /*NOT 90 YOU IDIOT*/tau / 4;
				bool validX = (Xbelowzero) ? (mouseX-helper <= x1) && (mouseX+helper >= x2) : (mouseX-helper <= x2) && (mouseX+helper >= x1);
				
				double n = y1 - x1 * k;
				double newn = mouseY - mouseX*k;
				std::cout << n << " " << newn << " " << k << " " << y1 - y2 << " " << x1 - x2 << std::endl;

				if (validY && validX) {
					bool validClick = (y1 - mouseY) / (x1 - mouseX);
					if (validClick) {
						float minimum = 0.03f;
						if (abs(x1 - x2) >= 0.01f) {
							closesty = abs(mouseY - (mouseX * k + n));

						}
						if (abs(y1 - y2) >= 0.01f) {
							closestx = abs(mouseX-((mouseY-n)/k));
						}
						if (closestx <= minimum || closesty <= minimum || x1-x2 == 0) {
							if (!contains(selected, std::make_tuple(x1, y1, rot))) {
								std::cout << "?" << std::endl;
								std::tuple<float, float, float, float, int> toBeInserted = std::make_tuple(x1, y1, len, rot, i);
								selected.push_back(toBeInserted);
								middle = FindMiddle(selected);
								break;
							}
						}
					}
				}

			}
		}
	}
	else {
		editclick = false;
	}
}