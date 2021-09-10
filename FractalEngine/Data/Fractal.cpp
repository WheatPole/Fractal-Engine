#include "Fractal.h"
#include "Scale2.h"

int fm;
bool scalingOnly = true;

std::vector<float> startingRotations;
Fractal::Fractal(std::vector<std::tuple<float, float, float, float>> starting, std::vector<std::vector<std::tuple<float, float, float, float>>> ending, int fracMode) {
	startingLines = starting;
	endingLines = ending;
	fm = fracMode;
}





void Recur(GLFWwindow* window, Renderer renderer, Shader shader, int start, int& iterations, int& fractalMode, std::vector<std::tuple<float, float, float, float>>& begin, std::vector<std::vector<std::tuple<float, float, float, float>>>& end) {

	if (start >= iterations)
		return;

	std::vector<float> nextRots;

	if (fm == 0) {

		renderer.Clear();
		fractalMode = 0;
		return;
	}
	else {
		glfwPollEvents();

		glfwSetKeyCallback(window, key_callback);
	}

	std::vector<std::vector<std::vector<std::tuple<float, float, float, float>>>> newend;
	std::cout << "Rendering iteration " << start << std::endl;



	for (size_t j = 0; j < end.size(); j++) {
		std::vector<std::vector<std::tuple<float, float, float, float>>> newend2;
		float coefficient = std::get<2>(begin[0]) / std::get<2>(end[j][0]);;
		for (size_t i = 1; i < begin.size(); i++) {
			float currCoefficient = std::get<2>(begin[i]) / std::get<2>(end[j][i]);
			if (currCoefficient > coefficient) {
				coefficient = currCoefficient;
			}
		}
		

		for (size_t k = 0; k < end.size(); k++) {

			std::vector<std::tuple<float, float, float, float>> temp;

			for (size_t i = 0; i < begin.size(); i++) {

				

				float beginlen = std::get<2>(begin[i]);
				float beginrot = std::get<3>(begin[i]);
				float beginb = beginlen * sin(beginrot);
				float begina = beginlen * cos(beginrot);

				float beginx1 = std::get<0>(begin[i]);
				float beginy1 = std::get<1>(begin[i]);
				float beginx2 = beginx1 + begina;
				float beginy2 = beginy1 + beginb;

				float endlen = std::get<2>(end[k][i]);
				float endrot = std::get<3>(end[k][i]);

				float endb = endlen * sin(endrot);
				float enda = endlen * cos(endrot);

				float endx1 = std::get<0>(end[k][i]);
				float endy1 = std::get<1>(end[k][i]);
				float endx2 = endx1 + enda;
				float endy2 = endy1 + endb;


				float endlen1 = std::get<2>(end[j][i]);
				float endrot1 = std::get<3>(end[j][i]);

				float endb1 = endlen1 * sin(endrot1);
				float enda1 = endlen1 * cos(endrot1);

				float endx11 = std::get<0>(end[j][i]);
				float endy11 = std::get<1>(end[j][i]);
				float endx12 = endx11 + enda1;
				float endy12 = endy11 + endb1;

				

				float rotChange = currRotChange[j]/begin.size(); 

				if (scalingOnly) {
					float lenendx2 = (endx12 - endx11);
					float lenendy2 = (endy12 - endy11);



					float lenendx = (endx2 - endx1);
					float lenbeginx = (beginx2 - beginx1);

					float lenendy = (endy2 - endy1);
					float lenbeginy = (beginy2 - beginy1);

					const float coefficientX = lenbeginx / lenendx2;
					float changex3 = (endx1 - beginx1) / coefficientX;
					float changex4 = lenendx / coefficientX;

					const float coefficientY = lenbeginy / lenendy2;
					float changey3 = (endy1 - beginy1) / coefficientY;
					float changey4 = lenendy / coefficientY;

					float y3 = endy11 + changey3;
					float x3 = endx11 + changex3;
					float y4 = y3 + changey4;
					float x4 = x3 + changex4;
					float num2 = y4 - y3;
					float num1 = x4 - x3;

					float len3 = sqrt((num1 * num1) + (num2 * num2));
					float rot3 = acos(num1 / len3);

					if (y4 - y3 <= 0) {
						rot3 = -rot3;
					}

					renderer.Line(renderer, shader, x3, y3, x4, y4);

					
					temp.push_back(std::make_tuple(x3, y3, len3, rot3));



				}
				else {



					float mid1x1 = beginx1;
					float mid1x2 = endx1;
					float mid1y1 = beginy1;
					float mid1y2 = endy1;
					float mid1len = sqrt(pow(abs(mid1x2 - mid1x1), 2) + pow(abs(mid1y2 - mid1y1), 2));
					float mid1rot = asin(abs(mid1y2 - mid1y1) / mid1len);
					if (mid1y2 - mid1y1 <= 0) {
						mid1rot = -mid1rot;
					}
					if (beginx1 >= endx1) {
						mid1rot = (float)(pi - abs(mid1rot)) * (mid1rot / abs(mid1rot));
					}
					mid1rot += rotChange;



					float newmid1len = mid1len / (coefficient);;
					float x3 = newmid1len;
					float y3 = 0.0;
					float tempx3 = x3;
					float tempy3 = y3;
					x3 = tempx3 * cos(mid1rot) - tempy3 * sin(mid1rot);
					y3 = tempx3 * sin(mid1rot) + tempy3 * cos(mid1rot);

					x3 += endx11;
					y3 += endy11;


					float mid2x1 = beginx2;
					float mid2x2 = endx2;
					float mid2y1 = beginy2;
					float mid2y2 = endy2;
					float mid2len = sqrt(pow(abs(mid2x2 - mid2x1), 2) + pow(abs(mid2y2 - mid2y1), 2));
					float mid2rot = asin(abs(mid2y2 - mid2y1) / mid2len);
					if (mid2y2 - mid2y1 <= 0) {
						mid2rot = -mid2rot;
					}
					if (beginx2 >= endx2) {
						mid2rot = (float)(pi - abs(mid2rot)) * (mid2rot / abs(mid2rot));
					}
					mid2rot += rotChange;

					float newmid2len = mid2len/ (coefficient);
					float x4 = newmid2len;
					float y4 = 0.0;
					float tempx4 = x4;
					float tempy4 = y4;
					x4 = tempx4 * cos(mid2rot) - tempy4 * sin(mid2rot);
					y4 = tempx4 * sin(mid2rot) + tempy4 * cos(mid2rot);

					x4 += endx12;
					y4 += endy12;

					float num2 = abs(y4 - y3);
					float num1 = abs(x4 - x3);

					float len3 = sqrt((num1 * num1) + (num2 * num2));
					float rot3 = acos(num1 / len3);


					
					if (y4 - y3 <= 0) {
						rot3 = -rot3;
					}

					if (x3 >= x4) {
						rot3 = (float)(pi - abs(rot3)) * (rot3 / abs(rot3));
					}

					if (coefficient < 1 && len3 < endlen1 - endlen1 / 10) {
						return;
					}
					if (coefficient > 1 && len3 > endlen1 + endlen1 / 10) {
						return;
					}
					renderer.Line(renderer, shader, x3, y3, x4, y4);

					temp.push_back(std::make_tuple(x3, y3, len3, rot3));

				}
			}
			newend2.push_back(temp);
		}
		
		newend.push_back(newend2);
	}
	

	for (size_t i = 0; i < end.size(); i++) {

		


		Recur(window, renderer, shader, start + 1, iterations, fractalMode, end[i], newend[i]);
	}
}

void Fractal::Recurse(GLFWwindow* window, Renderer renderer, Shader shader, int iterations, int& fractalMode) {
	scalingOnly = true;


	for (int i = 0; i < startingLines.size(); i++) {
		startingRotations.push_back(std::get<3>(startingLines[i])+tau);
		if (scalingOnly) {
			if (currRotChange[i] > 0.001f) {
				scalingOnly = false;
			}
		}
	}

	Recur(window, renderer, shader, 0, iterations, fractalMode, startingLines, endingLines);
}

Fractal::~Fractal() {

}
