#include "Fractal.h"
#include "Scale2.h"

int fm;

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

			
			/*float coefficientLEN = std::get<2>(begin[i]) / std::get<2>(end[j][i]);
			
			float rotChange = std::get<3>(begin[i]) / std::get<3>(end[j][i]); */
			//create an array containing how much the rot has changed, and after each iteration change the rot by that much (don't forget to subtract the rot before calculating the next point)

			//A ----------------------------- B
			//  |                           |
			//  |                           |
			//  |                           |
			//  |                           |
			//  |                           |
			//  |                         C |-------------- D
			//  |                           |             |
			//  |                           |             |
			//  |                           |           E |------- F
			//  |                           |             |      |
			//  |                           |             |      |
			//  --------------------------------------------------
			//

			//calculate the next point on the line (if you have A calculate B), and compare AB and CD to get EF
			//do AB + (C - B) to find the next point

			//for rot maybe rotate it back to find the proportions, and then add 2 * rot to the rotation (because the rotation was -rot)
			//that's actually a good idea

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

				

				float rotChange = currRotChange[j]/begin.size(); //????????????????????????????????????????????????????????????????????????????????????????

				//float rotChange = (endrot1 - beginrot)/begin.size();

				//std::cout << endrot-beginrot << " " << currRotChange << std::endl;

				if (/*currRotChange[i] == 0.0f */ false) {
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

					//endx1, endy1, changex3, changex4, changey3, changey4

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

					/*float begink = (beginy1 - beginy2) / (beginx1 - beginx2);
					float beginn = beginy1 - beginx1 * begink;
					float endk = (endy1 - endy2) / (endx1 - endx2);
					float endn = endy1 - (endx1 * endk);
					float intersectionx = (beginn - endn) / (endk - begink);
					float intersectiony = (begink * intersectionx) + beginn;


					float beginlength = sqrt(pow((beginx1 - beginx2), 2) + pow((beginy1 - beginy2), 2));
					float endlength = sqrt(pow((endx1 - endx2), 2) + pow((endy1 - endy2), 2));
					const float coefficient = beginlength / endlength; //end[i][j]

					float lengthbegin = sqrt(pow((beginx1 - intersectionx), 2) + pow((beginy1 - intersectiony), 2));
					float lengthend = sqrt(pow((endx1 - intersectionx), 2) + pow((endy1 - intersectiony), 2));

					float newlenbegin = lengthbegin / coefficient;
					float newlenend = lengthend / coefficient;

					//breaks when the intersection vector is in the line

					float newrot = endrot;
					if (abs(intersectionx-endx1) > abs(intersectionx-endx2)) {

						newrot = -(float)(pi - abs(newrot)) * (newrot / abs(newrot));
						//newrot = (float)(pi - abs(newrot)) * (newrot / abs(newrot));

						std::cout << "Broken" << std::endl;
						lengthend = sqrt(pow((endx2 - intersectionx), 2) + pow((endy2 - intersectiony), 2));
						newlenbegin = sqrt(pow((beginx2 - intersectionx), 2) + pow((beginy2 - intersectiony), 2));
					}

					float rotation = newrot;
					float lenx;
					lenx = lengthend - newlenbegin;

					float leny =  0.0f;

					float templenx = lenx;
					float templeny = leny;
					lenx = templenx * cos(newrot) - templeny * sin(newrot);
					leny = templenx * sin(newrot) + templeny * cos(newrot);

					//rotation matrix to the newinterx & newintery
					//extend the line by newlenend




					float newintersectionx = lenx + intersectionx;
					float newintersectiony = leny + intersectiony;




					std::cout << lengthend << " " << coefficient << std::endl;
					std::cout << newintersectionx << " " << newintersectiony << " " << rotChange << std::endl;
					std::cout << newlenbegin << " " << lenx << " " << leny << std::endl;

					rotation += rotChange;
					if (rotation == 0) {
						rotation += 0.002f;
					}
					else if (rotation == pi / 2) {
						rotation += 0.002f;
					}
					else if (rotation == -pi || rotation == pi) {
						rotation -= 0.002f;
					}
					else if (rotation == -pi / 2) {
						rotation -= 0.002f;
					}

					//std::cout << "Length after: " << rotation << std::endl;


					if (rotation < -pi) {
						rotation += tau;
					}
					else if (rotation >= pi) {
						rotation -= tau;
					}

					float x3 = newlenend;
					float y3 = 0.0f;
					float x4 = newlenend + (endlen/coefficient) ;
					float y4 = 0.0f;
					//std::cout << "Length change: " << rotChange << std::endl;
					//rotate by rotation
					float tempx = x3;
					float tempy = y3;
					x3 = tempx * cos(rotation) - tempy * sin(rotation);
					y3 = tempx * sin(rotation) + tempy * cos(rotation);
					tempx = x4;
					tempy = y4;
					x4 = tempx * cos(rotation) - tempy * sin(rotation);
					y4 = tempx * sin(rotation) + tempy * cos(rotation);

					x3 += newintersectionx;
					y3 += newintersectiony;
					x4 += newintersectionx;
					y4 += newintersectiony;


					shader.SetUniform4f("u_Colour", 0.1, 1.0, 0.6, 1.0);


					float num2 = y4 - y3;
					float num1 = x4 - x3;

					float len3 = sqrt((num1 * num1) + (num2 * num2));
					float rot3 = acos(num1 / len3);

					if (y4 - y3 <= 0) {
						rot3 = -rot3;
					}

					renderer.Line(renderer, shader, x3, y3, x4, y4);*/

					/*
					float coefbx1 = beginx1 * sin(-rotationChange);
					float coefex1 = endx1;
					float coefby1 = beginy1 * cos(-rotationChange);
					float coefey1 = endy1;
					float coefbx2 = beginx2 * sin(-rotationChange);
					float coefex2 = endx2 * sin(-rotationChange - currRotChange);
					float coefby2 = beginy2 * cos(-rotationChange);
					float coefey2 = endy2;



					const float trueCoefficientX = abs(((coefbx2 * cos(-rotationChange) - coefby2 * sin(-rotationChange)) - (coefbx1 * cos(-rotationChange) - coefby1 * sin(-rotationChange))) / ((coefex2 * cos(-rotationChange - currRotChange) - coefey2 * sin(-rotationChange - currRotChange)) - (coefex1 * cos(-rotationChange - currRotChange) - coefey1 * sin(-rotationChange - currRotChange))));
					const float trueCoefficientY = abs(((coefbx2 + coefby2) - (coefbx1 + coefby1)) / ((coefex2 + coefey2) - (coefex1 + coefey1)));*/
					//y3 = tempx3 * sin(rotationChange) + tempy3 * cos(rotationChange);




/*
					float coefbx1X = beginx1 * cos(startingRotations[i] - beginrot);
					float coefex1X = endx1 * cos(startingRotations[i] - endrot);
					float coefby1X = beginy1 * sin(startingRotations[i] - beginrot);
					float coefey1X = endy1 * sin(startingRotations[i] - endrot);
					float coefbx2X = beginx2 * cos(startingRotations[i] - beginrot);
					float coefex2X = endx2 * cos(startingRotations[i] - endrot);
					float coefby2X = beginy2 * sin(startingRotations[i] - beginrot);
					float coefey2X = endy2 * sin(startingRotations[i] - endrot);

					float coefb1X = coefbx1X - coefby1X;
					float coefb2X = coefbx2X - coefby2X;
					float coefe1X = coefex1X - coefey1X;
					float coefe2X = coefex2X - coefey2X;

					float coefbx1Y = beginx1 * sin(startingRotations[i] - beginrot);
					float coefex1Y = endx1 * sin(startingRotations[i] - endrot);
					float coefby1Y = beginy1 * cos(startingRotations[i] - beginrot);
					float coefey1Y = endy1 * cos(startingRotations[i] - endrot);
					float coefbx2Y = beginx2 * sin(startingRotations[i] - beginrot);
					float coefex2Y = endx2 * sin(startingRotations[i] - endrot);
					float coefby2Y = beginy2 * cos(startingRotations[i] - beginrot);
					float coefey2Y = endy2 * cos(startingRotations[i] - endrot);

					float coefb1Y = coefbx1Y + coefby1Y;
					float coefb2Y = coefbx2Y + coefby2Y;
					float coefe1Y = coefex1Y + coefey1Y;
					float coefe2Y = coefex2Y + coefey2Y;


					const float trueCoefficientX = abs((coefb2X - coefb1X) / (coefe2X - coefe1X));

					const float trueCoefficientY = abs(((coefbx2Y + coefby2Y) - (coefbx1Y + coefby1Y)) / ((coefex2Y + coefey2Y) - (coefex1Y + coefey1Y)));

					*/
					//const float coefficient = beginlen / endlen1;

					//const float trueCoefficient = sqrt(trueCoefficientX * trueCoefficientY);

					//std::cout << trueCoefficientX << " " << trueCoefficientY << " " << coefficient << std::endl;

					float mid1x1 = beginx1;
					float mid1x2 = endx1;
					float mid1y1 = beginy1;
					float mid1y2 = endy1;
					float mid1len = sqrt(pow(abs(mid1x2 - mid1x1), 2) + pow(abs(mid1y2 - mid1y1), 2));
					float mid1rot = asin(abs(mid1y2 - mid1y1) / mid1len)/**180/3.14159265358979323846*/; //remove the comment for degrees
					if (mid1y2 - mid1y1 <= 0) {
						mid1rot = -mid1rot;
					}
					if (beginx1 >= endx1) {
						mid1rot = (float)(pi - abs(mid1rot)) * (mid1rot / abs(mid1rot));
					}
					mid1rot += rotChange;



					float newmid1len = mid1len / (coefficient);// / trueCoefficientX;
					float x3 = newmid1len;
					float y3 = 0.0;
					float tempx3 = x3;
					float tempy3 = y3;
					x3 = tempx3 * cos(mid1rot) - tempy3 * sin(mid1rot);
					y3 = tempx3 * sin(mid1rot) + tempy3 * cos(mid1rot);

					x3 += endx11;
					y3 += endy11;
					/*
					auto temptuple = std::make_tuple(x3, y3, newmid1len, mid1rot);

					auto edges = FindEdges(temptuple);

					float scalex = (abs((std::get<0>(edges) - std::get<1>(edges))) - abs((std::get<0>(edges) - std::get<1>(edges))) / trueCoefficientX) / 2;
					float scaley = (abs((std::get<2>(edges) - std::get<3>(edges))) - abs((std::get<2>(edges) - std::get<3>(edges))) / trueCoefficientY) / 2;

					ScaleAllNew(temptuple, -scalex, -scaley);

					x3 = std::get<0>(temptuple);
					y3 = std::get<1>(temptuple);
					*/
					

					/*
					float truex3 = mid1x2 - (mid1x2 - x3) / trueCoefficient;
					float truey3 = mid1y2 - (mid1y2 - y3) / trueCoefficient;
					*/

					float mid2x1 = beginx2;
					float mid2x2 = endx2;
					float mid2y1 = beginy2;
					float mid2y2 = endy2;
					float mid2len = sqrt(pow(abs(mid2x2 - mid2x1), 2) + pow(abs(mid2y2 - mid2y1), 2));
					float mid2rot = asin(abs(mid2y2 - mid2y1) / mid2len)/**180/3.14159265358979323846*/; //remove the comment for degrees
					if (mid2y2 - mid2y1 <= 0) {
						mid2rot = -mid2rot;
					}
					if (beginx2 >= endx2) {
						mid2rot = (float)(pi - abs(mid2rot)) * (mid2rot / abs(mid2rot));
					}
					mid2rot += rotChange;



					float newmid2len = mid2len/ (coefficient);// / trueCoefficientX;
					float x4 = newmid2len;
					float y4 = 0.0;
					float tempx4 = x4;
					float tempy4 = y4;
					x4 = tempx4 * cos(mid2rot) - tempy4 * sin(mid2rot);
					y4 = tempx4 * sin(mid2rot) + tempy4 * cos(mid2rot);

					x4 += endx12;
					y4 += endy12;

					/*shader.SetUniform4f("u_Colour", 0.5f, 0.2f, 0.4f, 1.0f);
					renderer.Line(renderer, shader, mid1x1, mid1y1, mid1x2, mid1y2);
					renderer.Line(renderer, shader, mid2x1, mid2y1, mid2x2, mid2y2);
					shader.SetUniform4f("u_Colour", 1.0f, 1.0f, 1.0f, 1.0f);*/

					/*
					auto temptuple1 = std::make_tuple(x4, y4, newmid2len, mid2rot);

					auto edges1 = FindEdges(temptuple1);

					float scalex1 = (abs((std::get<0>(edges1) - std::get<1>(edges1))) - abs((std::get<0>(edges1) - std::get<1>(edges1))) / trueCoefficientX) / 2;
					float scaley1 = (abs((std::get<2>(edges1) - std::get<3>(edges1))) - abs((std::get<2>(edges1) - std::get<3>(edges1))) / trueCoefficientY) / 2;

					ScaleAllNew(temptuple1, -scalex1, -scaley1);

					x4 = std::get<0>(temptuple1);
					y4 = std::get<1>(temptuple1);

					*/

					/*x3 = truex3;
					x4 = truex4;
					y3 = truey3;
					y4 = truey4;*/

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

					//shader.SetUniform4f("u_Colour", 1.0f, 1.0f, 1.0f, 1.0f);
					/*if (coefficient < 1 && len3 < endlen1 - endlen1 / 10) {
						return;
					}
					if (coefficient > 1 && len3 > endlen1 + endlen1 / 10) {
						return;
					}*/
					renderer.Line(renderer, shader, x3, y3, x4, y4);
					//glfwSwapBuffers(window);
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
	for (int i = 0; i < startingLines.size(); i++) {
		startingRotations.push_back(std::get<3>(startingLines[i])+tau);
	}
	
	Recur(window, renderer, shader, 0, iterations, fractalMode, startingLines, endingLines);
}

Fractal::~Fractal() {

}