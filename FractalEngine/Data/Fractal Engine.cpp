//Copyright © 2021 WheatPole

#include "CheckForMouseState.h"
#include "DrawLines.h"
#include "DrawSelectedLines.h"
#include "CheckIfTheMouseIsOverALine.h"
#include "Rotate.h"
#include "Scale.h"
#include "Fractal.h"

//0 - drawing
//1 - editing
//2 - recursion

int fractalMode = 0;

float leftmostpoint = 99.0;
float rightmostpoint = -99.0;
float uppermostpoint = -99.0;
float lowermostpoint = 99.0;
/*float templen = (float)sqrt(0.3 * 0.3 + 0.01);
float temprot = (float)acos(0.3 / templen);*/
std::vector<std::tuple<float, float, float, float>> positions;
std::vector<std::tuple<float, float, float, float, int>> selected;

std::vector<std::tuple<float, float, float, float>> starting;
//last float - rot change
std::vector<std::vector<std::tuple<float, float, float, float>>> endings;
std::vector<float> currRotChange = {0};

bool green = false;

int endingiterator = 0;
bool ctrlpressed = false;
//int currentIndex = 0;

int recursionCounter = 8;

//std::vector<std::tuple< std::vector<std::tuple<float, float, float, float>>, std::vector<std::tuple<float, float, float, float, int>>>> moves;
std::tuple<float, float> middle;

void UpdatePos() {
	for (size_t i = 0; i < selected.size(); i++) {
		std::tuple<float, float, float, float> temp = std::make_tuple(std::get<0>(selected[i]), std::get<1>(selected[i]), std::get<2>(selected[i]), std::get<3>(selected[i]));
		positions[std::get<4>(selected[i])] = temp;
		if (fractalMode == 2) {
			endings[endingiterator][std::get<4>(selected[i])] = temp;
		}
	}
	/*moves.erase(moves.begin() + currentIndex, moves.end());
	currentIndex++;
	moves.push_back(std::make_tuple(positions, selected));*/

}
void UpdateMid() {
	middle = FindMiddle(selected);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		//std::cout << "Key: " << std::to_string(key) << std::endl;
		if (fractalMode == 4) {
			if (key == GLFW_KEY_ESCAPE) {
				fractalMode = 0;
				endings.clear();
				positions = starting;
				starting.clear();
				fm = 0;
			}
		}
		else {
			switch (key) {
			case GLFW_KEY_LEFT_CONTROL:
				ctrlpressed = true;
				break;
			case GLFW_KEY_1:
				
				fractalMode = 0;
				currRotChange.clear();
				currRotChange.push_back(0);
				starting.clear();
				endings.clear();
				selected.clear();
				break;
			case GLFW_KEY_2:
				selected.clear();
				currRotChange.clear();
				currRotChange.push_back(0);
				if (fractalMode == 2) {
					positions = starting;
				}
				endings.clear();
				starting.clear();
				fractalMode = 1;
				green = false;
				break;
			case GLFW_KEY_3:
				currRotChange.clear();
				currRotChange.push_back(0);
				selected.clear();
				for (size_t i = 0; i < positions.size(); i++) {
					std::tuple<float, float, float, float, int> temp = std::make_tuple(std::get<0>(positions[i]), std::get<1>(positions[i]), std::get<2>(positions[i]), std::get<3>(positions[i]), i);
					selected.push_back(temp);
					//std::cout << std::get<3>(positions[i]) << std::endl;
					

				}
				middle = FindMiddle(positions);
				green = true;
				starting = positions;
				fractalMode = 2;
				break;
			case GLFW_KEY_C:
				if (fractalMode == 0) {
					positions.clear();
				}
				else if (fractalMode == 1) {
					selected.clear();
				}
				break;
			case GLFW_KEY_F:
				if (fractalMode == 1 || fractalMode == 2) {
					auto temp = FindLRUL(selected); float len = abs(std::get<0>(temp) - std::get<1>(temp));
					Scale(selected, -1, 0, -len / 32, 0.0f, middle);
				}
				break;
			case GLFW_KEY_H:
				if (fractalMode == 1 || fractalMode == 2) {
					auto temp = FindLRUL(selected); float len = abs(std::get<0>(temp) - std::get<1>(temp));
					Scale(selected, 1, 0, -len / 32, 0.0f, middle);
				}
				break;
			case GLFW_KEY_J:
				if (fractalMode == 1 || fractalMode == 2) {
					auto temp = FindLRUL(selected); float len = abs(std::get<0>(temp) - std::get<1>(temp));
					Scale(selected, -1, 0, len / 32, 0.0f, middle);
				}
				break;
			case GLFW_KEY_L:
				if (fractalMode == 1 || fractalMode == 2) {
					auto temp = FindLRUL(selected); float len = abs(std::get<0>(temp) - std::get<1>(temp));
					Scale(selected, 1, 0, len / 32, 0.0f, middle);
				}
				break;
			case GLFW_KEY_T:
				if (fractalMode == 1 || fractalMode == 2) {
					auto temp = FindLRUL(selected); float len = abs(std::get<3>(temp) - std::get<2>(temp));
					Scale(selected, 0, -1, 0.0f, -len / 32, middle);
				}
				break;
			case GLFW_KEY_G:
				if (fractalMode == 1 || fractalMode == 2) {
					auto temp = FindLRUL(selected); float len = abs(std::get<3>(temp) - std::get<2>(temp));
					Scale(selected, 0, 1, 0.0f, -len / 32, middle);
				}
				break;
			case GLFW_KEY_I:
				if (fractalMode == 1 || fractalMode == 2) {
					auto temp = FindLRUL(selected); float len = abs(std::get<3>(temp) - std::get<2>(temp));
					Scale(selected, 0, -1, 0.0f, len / 32, middle);
				}
				break;
			case GLFW_KEY_K:
				if (fractalMode == 1 || fractalMode == 2) {
					auto temp = FindLRUL(selected); float len = abs(std::get<3>(temp) - std::get<2>(temp));
					Scale(selected, 0, 1, 0.0f, len / 32, middle);
				}
				break;


			case GLFW_KEY_B:
				if (fractalMode == 1 || fractalMode == 2) {
					auto temp = FindLRUL(selected); float len = abs(std::get<3>(temp) - std::get<2>(temp));
					ScaleAll(selected, len / 32, len / 32, middle);
				}
				break;

			case GLFW_KEY_COMMA:
				if (fractalMode == 1 || fractalMode == 2) {
					auto temp = FindLRUL(selected); float len = abs(std::get<3>(temp) - std::get<2>(temp));
					ScaleAll(selected, -len / 32, -len / 32, middle);
				}
				break;

			case GLFW_KEY_E:
				if (fractalMode == 1) {
					Rotate(selected, middle, (float)(-tau / 228));
				}
				else if (fractalMode == 2) {
					Rotate(selected, middle, (float)(-tau / 228), currRotChange[currRotChange.size() - 1]);
				}
				break;
			case GLFW_KEY_Q:
				if (fractalMode == 1) {
					Rotate(selected, middle, (float)(tau / 228));
				}
				else if (fractalMode == 2) {
					Rotate(selected, middle, (float)(tau / 228), currRotChange[currRotChange.size() - 1]);
				}
				break;
			case GLFW_KEY_R:
				if (fractalMode == 1 || fractalMode == 2) {
					std::vector<std::tuple<float, float, float, float>> temp;
					for (size_t i = 0; i < selected.size(); i++) {
						auto temp2 = std::make_tuple(std::get<0>(selected[i]), std::get<1>(selected[i]), std::get<2>(selected[i]), std::get<3>(selected[i]));
						positions.push_back(temp2);
						auto temp3 = std::make_tuple(std::get<0>(selected[i]), std::get<1>(selected[i]), std::get<2>(selected[i]), std::get<3>(selected[i]));
						temp.push_back(temp3);
					}
					if (fractalMode == 2) {
						currRotChange.push_back(currRotChange[currRotChange.size()-1]);
						endings.push_back(temp);
					}

				}
				break;
			case GLFW_KEY_Y:
				if (fractalMode == 0) {
					std::tuple<float, float, float, float> line1 = std::make_tuple(0.5, 0.5, 1.0, -tau/4+0.004f);
					std::tuple<float, float, float, float> line2 = std::make_tuple(0.5, -0.5, 1.0, -tau/2 + 0.004f);
					std::tuple<float, float, float, float> line3 = std::make_tuple(-0.5, -0.5, 1.0, -3*tau/4 + 0.004f);
					std::tuple<float, float, float, float> line4 = std::make_tuple(-0.5, 0.5, 1.0, 0.004f);
					
					positions.push_back(line1);
					positions.push_back(line2);
					positions.push_back(line3);
					positions.push_back(line4);

				}
				else if (fractalMode == 1) {
					selected.clear();
					for (int i = 0; i < positions.size(); i++) {
						selected.push_back(std::make_tuple(std::get<0>(positions[i]), std::get<1>(positions[i]), std::get<2>(positions[i]), std::get<3>(positions[i]), i));
					}
					UpdateMid();
				}
				break;
			case GLFW_KEY_W:
				if (fractalMode == 1 || fractalMode == 2) {
					for (size_t i = 0; i < selected.size(); i++) {
						if (!ctrlpressed)
							std::get<1>(selected[i]) += 0.02f;
						else 
							std::get<1>(selected[i]) += 0.004f;
					}
					UpdateMid();
				}
				break;
			case GLFW_KEY_S:
				if (fractalMode == 1 || fractalMode == 2) {
					for (size_t i = 0; i < selected.size(); i++) {
						if (!ctrlpressed)
							std::get<1>(selected[i]) -= 0.02f;
						else
							std::get<1>(selected[i]) -= 0.004f;
					}
					UpdateMid();
				}
				break;
			case GLFW_KEY_D:
				if (fractalMode == 1 || fractalMode == 2) {
					for (size_t i = 0; i < selected.size(); i++) {
						if (!ctrlpressed)
							std::get<0>(selected[i]) += 0.02f;
						else
							std::get<0>(selected[i]) += 0.004f;
					}
					UpdateMid();
				}
				break;
			case GLFW_KEY_A:
				if (fractalMode == 1 || fractalMode == 2) {
					for (size_t i = 0; i < selected.size(); i++) {
						if (!ctrlpressed)
							std::get<0>(selected[i]) -= 0.02f;
						else
							std::get<0>(selected[i]) -= 0.004f;
					}
					UpdateMid();
				}
				break;

			case GLFW_KEY_DELETE:
				if (fractalMode == 1) {
					for (size_t i = 0; i < selected.size(); i++) {
						auto temp = std::make_tuple(std::get<0>(selected[i]), std::get<1>(selected[i]), std::get<2>(selected[i]), std::get<3>(selected[i]));
						positions.erase(std::find(positions.begin(), positions.end(), temp));///
						
					}
					selected.clear();
				}
				break;



			case GLFW_KEY_8:

				recursionCounter = 8;
				break;
			case GLFW_KEY_9:

				recursionCounter = 15;
				break;
			case GLFW_KEY_7:

				recursionCounter = 100;
				break;

			case GLFW_KEY_ENTER:
				if (fractalMode == 2) {
					std::vector<std::tuple<float, float, float, float>> temp;
					for (size_t i = 0; i < selected.size(); i++) {
						auto temp2 = std::make_tuple(std::get<0>(selected[i]), std::get<1>(selected[i]), std::get<2>(selected[i]), std::get<3>(selected[i]));
						temp.push_back(temp2);
					}
					endings.push_back(temp);
					//begin
					for (size_t i = 0; i < selected.size(); i++) {
						auto temp2 = std::make_tuple(std::get<0>(selected[i]), std::get<1>(selected[i]), std::get<2>(selected[i]), std::get<3>(selected[i]));
						positions.push_back(temp2);
					}
					//update the endings vector
					std::cout << endings.size() * endings[0].size() << " " << positions.size() - selected.size() << std::endl;
					
					selected.clear();
					
					//set recursion counter to 6
					fractalMode = 4;
				}
				break;
			}
			if (fractalMode == 1 && GLFW_KEY_Y != key && GLFW_KEY_Z != key)
				UpdatePos();
		}
	}
	else if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_LEFT_CONTROL:
			ctrlpressed = false;
			break;
		}
	}
}

int main(void)
{
	
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	int width = 800;
	int height = 800;
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 800, "Fractal Engine", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}



	std::cout << glGetString(GL_VERSION) << std::endl;
	{
		float r = 0.0f;
		float k = 0.001f;

		//x, y, rotation, length, (false - right corner, true - left corner)
		
		//moves.push_back(std::make_tuple(positions, selected));
		
		int cleks = 0;

		Renderer renderer;
		Shader shader("Basic.shader");

		

		VertexBufferLayout vbl;

		vbl.Push<float>(2);

		bool swipe = false;
		
		float currentFirstPositionX = 0.0f;
		float currentFirstPositionY = 0.0f;

		float finalX = 0.0f;
		float finalY = 0.0f;

		/*va.Unbind();
		vb.Unbind();*/
		shader.Unbind();
		bool clicked = false;
		bool editclick = false;
		/* Loop until the user closes the window */

		//positions.push_back(std::make_tuple(0.2, 0.2, temprot, templen));

		while (!glfwWindowShouldClose(window))
		{
			//std::cout << clicked << " [" << currentFirstPositionX << ", " << currentFirstPositionY << "] [" << finalX << ", " << finalY << "]" << std::endl;
			//if (fractalMode == 0)
				renderer.Clear();
			shader.Bind();
			//renderer.Draw(va, i, shader);

			shader.SetUniform4f("u_Colour", 30.0f/255, 2.0f/255, 2.0f/255, 1.0f);
			renderer.Rect(renderer, shader, -1.0, -1.0, 1.0, 1.0, true);

			shader.SetUniform4f("u_Colour", 1.0f, 1.0f, 1.0f, 1.0f);
			//std::cout << selected.size() << std::endl;
			
			if (fractalMode == 4) {
				Fractal fractal(starting, endings, fractalMode);
				fractal.Recurse(window, renderer, shader, recursionCounter, fractalMode);
			}
			
			if (cleks >= 1) {
				
				shader.SetUniform4f("u_Colour", 1.0f, 1.0f, 1.0f, 1.0f);
				DrawLines(renderer, vbl, shader, positions);
				
				if (fractalMode == 1 || fractalMode == 2) {
					DrawSelectedLines(renderer, shader, selected, green);
					
				}
				
			}

			shader.SetUniform4f("u_Colour", 1.0f, 1.0f, 1.0f, 1.0f);
			

			if (clicked) {
				renderer.Line(renderer, shader, currentFirstPositionX, currentFirstPositionY, finalX, finalY);
			}
			glfwSwapBuffers(window);

			glfwPollEvents();
			if (fractalMode == 0) {
				CheckForMouseState(window, width, height, clicked, swipe, cleks, positions, currentFirstPositionX, currentFirstPositionY, finalX, finalY);
			}
			else if (fractalMode == 1 || fractalMode == 2) {
				CheckIfTheMouseIsOverALine(window, renderer, width, height, positions, selected, editclick, middle);
			}
			
			glfwSetKeyCallback(window, key_callback);
		}
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}