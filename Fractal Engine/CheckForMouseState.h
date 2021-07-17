#pragma once
#include "Includes.h"



void CheckForMouseState(GLFWwindow* window, int width, int height, bool& clicked, bool& swipe, int& cleks, std::vector<std::tuple<float, float, float, float>>& positions, float& currPosX, float& currPosY, float& finalX, float& finalY) {
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1);
	if (state == GLFW_PRESS) {
		float mousePos[] = {
			0.0, 0.0
		};
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		if (mouseX > width || mouseX < 0 || mouseY > height || mouseY < 0) {
			//don't do anything
		}
		else {
			mouseX = 1 - (mouseX / (width / 2));
			mouseY = 1 - (mouseY / (height / 2));
			mousePos[0] = (float)-mouseX;
			mousePos[1] = (float)mouseY;

			cleks++;
		}
		if (!clicked) {		
			currPosX = mousePos[0];
			currPosY = mousePos[1];
			clicked = true;
		}
		finalX = mousePos[0];
		finalY = mousePos[1];
	}
	else if (state == GLFW_RELEASE) {
		if (clicked) {
			bool left = false;
			float len = 0.0f;
			if (currPosX >= finalX)
				left = true;
			float num1 = abs(currPosX - finalX);
			float num2 = abs(currPosY - finalY);
			len = sqrt(num1 * num1 + num2 * num2);
			//rotation of a line
			float rotation = acos(num1/len)/**180/3.14159265358979323846*/; //remove the comment for degrees
			if (finalY - currPosY <= 0) {
				rotation = -rotation;
			}
			if (left) {
				rotation = (float)(pi - abs(rotation)) * (rotation / abs(rotation));
			}
			if (rotation >= -185 && rotation <= 185) {
				std::cout << rotation << std::endl;
				positions.push_back(std::make_tuple(currPosX, currPosY, len, rotation));
				std::vector<std::tuple<float, float, float, float, int>> temp;
			}
			clicked = false;
		}
	}
}