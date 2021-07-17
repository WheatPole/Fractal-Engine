
#include "Fractal.h"

Fractal::Fractal(std::vector<std::tuple<float, float, float, float>> starting, std::vector<std::vector<std::tuple<float, float, float, float, float>>> ending) {
	startingLines = starting;
	endingLines = ending;
}

void Recur(Renderer renderer, Shader shader, int start, int& iterations, std::vector<std::tuple<float, float, float, float, float>>& begin, std::vector<std::vector<std::tuple<float, float, float, float, float>>>& end) {

	if (start >= iterations)
		return;

	std::vector<std::vector<std::vector<std::tuple<float, float, float, float, float>>>> newend;
	std::cout << "START " << start << std::endl;
	//find out what the rules are
		
	

	//std::cout << end.size() << " " << end[0].size() << " " << begin.size() << std::endl;

	for (int j = 0; j < end.size(); j++) {
		std::vector<std::vector<std::tuple<float, float, float, float, float>>> newend2;

		for (int k = 0; k < end.size(); k++) {
		
		
			//find how much larger/smaller a line is from the line at the vector
			
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

			std::vector<std::tuple<float, float, float, float, float>> temp;

			for (int i = 0; i < begin.size(); i++) {

				float rotChange = std::get<4>(end[k][i]) - std::get<4>(begin[i]);

				//return to original positions with (-std::get<4>(begin[i])

				float beginlen = std::get<2>(begin[i]);
				float beginrot = std::get<3>(begin[i]);
				float beginb = beginlen * sin(beginrot);
				float begina = beginlen * cos(beginrot);

				float beginx1 = std::get<0>(begin[i]);
				float beginy1 = std::get<1>(begin[i]);
				float beginx2 = beginx1 + begina;
				float beginy2 = beginy1 + beginb;

				//return to original positions with (-std::get<4>(end[k][i])

				float endlen = std::get<2>(end[k][i]);
				float endrot = std::get<3>(end[k][i]);

				float endb = endlen * sin(endrot);
				float enda = endlen * cos(endrot);

				float endx1 = std::get<0>(end[k][i]);
				float endy1 = std::get<1>(end[k][i]);
				float endx2 = endx1 + enda;
				float endy2 = endy1 + endb;

				std::cout << std::get<4>(begin[i]) << " " << std::get<4>(end[k][i]) << std::endl;

				//alright here's the plan:
				//for each object in the end vector find the set of rules (changex3 & changey3), scale it down by coefficientX
				//and coefficientY (USE THE J VARIABLE, NOT THE K) depending on the current variable, do the same for changex4 &
				//changey4 and apply those rules to the end[j] object - note that you don't have to calculate the positions 
				// of end[k], but instead of that, calculate it for end[j], aka a new variable for the end1 and end2 positions
				//of end[k]

				//return to original positions with (-std::get<4>(end[j][i])? maybe
				if (rotChange == 0.0) {
					float endlen1 = std::get<2>(end[j][i]);
					float endrot1 = std::get<3>(end[j][i]);

					float endb1 = endlen1 * sin(endrot1);
					float enda1 = endlen1 * cos(endrot1);

					float endx11 = std::get<0>(end[j][i]);
					float endy11 = std::get<1>(end[j][i]);
					float endx12 = endx11 + enda1;
					float endy12 = endy11 + endb1;

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

					//enx1, endy1, changex3, changex4, changey3, changey4

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

					//add rotChange to begin[i] - create a new variable
					//add rotChange to end[k][i] - create a new variable
					//maybe add rotChange to end[j][i] not sure why though
					//check if those rots are bigger than pi or lower than -pi

					//maybe do the duplication process and then add the currRotChange -------------------------------------------
					temp.push_back(std::make_tuple(x3, y3, len3, rot3, std::get<4>(end[k][i])));


					/*std::cout << "oldx: " << beginx1 << " " << begina << " " << beginb << " " << beginx2 << " " << endx1 << " " << enda << " " << endb << " " << endx2 << std::endl;
					/*std::cout << "oldx: " << beginx1 << " " << begina << " " << beginb << " " << beginx2 << " " << endx1 << " " << enda << " " << endb << " " << endx2 << std::endl;
					std::cout << "oldy: " << beginy1 << " " << begina << " " << beginb << " " << beginy2 << " " << endy1 << " " << enda << " " << endb << " " << endy2 << std::endl;
					std::cout << "rot: " << beginrot << " " << endrot << " len: " << beginlen << " " << endlen << std::endl;
					std::cout << "newx3: " << x3 << " " << coefficientX << " " << changex3 << " newy3: " << y3 << " " << coefficientY << " " << changey3 << std::endl;
					std::cout << "newx4: " << x4 << " " << changex4 << " newy4: " << y4 << " " << changey4 << std::endl;
					std::cout << lenendx << " " << lenbeginx << " " << lenendy << " " << lenbeginy << std::endl;*/

				}
				else {
					
					float begink = (beginy1 - beginy2) / (beginx1 - beginx2);
					float beginn = beginy1 - beginx1 * begink;
					float endk = (endy1 - endy2) / (endx1 - endx2);
					float endn = endy1 - (endx1 * endk);
					float intersectionx = (beginn - endn) / (endk - begink);
					float intersectiony = (begink * intersectionx) + beginn;


					float beginlength = sqrt(pow((beginx1 - beginx2), 2) + pow((beginy1 - beginy2), 2));
					float endlength = sqrt(pow((endx1 - endx2), 2) + pow((endy1 - endy2), 2));
					const float coefficient = beginlength / endlength /*end[j][i]*/;

					float lengthbegin = sqrt(pow((beginx1 - intersectionx), 2) + pow((beginy1 - intersectiony), 2));
					float lengthend = sqrt(pow((endx1 - intersectionx), 2) + pow((endy1 - intersectiony), 2));

					float newlenbegin = lengthbegin / coefficient;
					float newlenend = lengthend / coefficient;

					float rotation = endrot;

					float newrot = endrot;
					/*if (endy1 < endy2) {
						newrot = -newrot;
					}*/
					float lenx = newlenbegin;
					float leny =  0.0f;

					float templenx = lenx;
					float templeny = leny;
					lenx = templenx * cos(newrot) - templeny * sin(newrot);
					leny = templenx * sin(newrot) + templeny * cos(newrot);

					//rotation matrix to the newinterx & newintery
					//extend the line by newlenend


					

					float newintersectionx = lenx + endx1;
					float newintersectiony = leny + endy1;

					/*if (endx2 > endx1)
						newintersectionx = endx1 + abs(lenx);
					else
						newintersectionx = endx1 - abs(lenx);

					if (endy2 > endy1)
						newintersectiony = endy1 + abs(leny);
					else
						newintersectiony = endy1 - abs(leny);*/

					/*newintersectionx = endx1 - lenx;

					newintersectiony = endy1 - leny;*/

					std::cout << newintersectionx << " " << newintersectiony << std::endl;
					std::cout << newlenbegin << " " << lenx << " " << leny << std::endl;

					//std::cout << lengthend << " " << lengthbegin << " " << newintersectionx << " " << newintersectiony << std::endl;
					//std::cout << "Length before: " << rotation << std::endl;
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
					
					/*if (intersectionx >= endx1) {

						rotation = (float)(tau - abs(rotation)) * (rotation / abs(rotation));
					}*/
					//std::cout << "Length after: " << rotation << std::endl;
					/*if (endy1 - intersectiony <= 0) {
						//rotation = -rotation;
						rotation = (float)(pi - abs(rotation)) * (rotation / abs(rotation));
					}*/
					
					
					if (rotation < -pi) {
						rotation += tau;
					}
					else if (rotation >= pi) {
						rotation -= tau;
					}
					float x3 = newlenend /*newlenbegin*/;
					float y3 = 0.0f;
					float x4 = newlenend /*newlenbegin*/ + (endlen/coefficient) /*beginlen*/;
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
					/*renderer.Line(renderer, shader, endx1, endy1, intersectionx, intersectiony);
					renderer.Line(renderer, shader, beginx1, beginy1, intersectionx, intersectiony);*/
					/*renderer.Line(renderer, shader, intersectionx, -1.0, intersectionx, 1.0);
					renderer.Line(renderer, shader, -1.0, intersectiony, 1.0, intersectiony);*/
					renderer.Line(renderer, shader, newintersectionx, -1.0, newintersectionx, 1.0);
					renderer.Line(renderer, shader, -1.0, newintersectiony, 1.0, newintersectiony);


					//std::cout << "[" << x3 << ", " << y3 << "]" << " " << rotation << " " << newlenbegin << " " << newlenend << " " << coefficient << std::endl;

					float num2 = y4 - y3;
					float num1 = x4 - x3;

					float len3 = sqrt((num1 * num1) + (num2 * num2));
					float rot3 = acos(num1 / len3);

					if (y4 - y3 <= 0) {
						rot3 = -rot3;
					}

					renderer.Line(renderer, shader, x3, y3, x4, y4);

					//add rotChange to begin[i] - create a new variable
					//add rotChange to end[k][i] - create a new variable
					//maybe add rotChange to end[j][i] not sure why though
					//check if those rots are bigger than pi or lower than -pi

					//maybe do the duplication process and then add the currRotChange -------------------------------------------
					temp.push_back(std::make_tuple(x3, y3, len3, rot3, std::get<4>(end[k][i])));
					
				}

			}
			newend2.push_back(temp);
		}
		
		//Recur(renderer, shader, start + 1, iterations, end[j], newend2);
		newend.push_back(newend2);
	}
	
	//draw the temp elements
	//apply those rules
	/*shader.SetUniform4f("u_Colour", 0.4, 0.2, 0.7, 0.5);
	for (int j = 0; j < newend.size(); j++) {
		for (int i = 0; i < newend[j].size(); i++) {
			float len = std::get<2>(newend[j][i]);
			float rot = std::get<3>(newend[j][i]);

			float b = len * sin(rot);
			float a = len * cos(rot);

			float x1 = std::get<0>(newend[j][i]);
			float y1 = std::get<1>(newend[j][i]);
			float x2 = x1 + a;
			float y2 = y1 + b;
			renderer.Line(renderer, shader, x1, y1, x2, y2);
		}
	}*/
	


	for (int i = 0; i < end.size(); i++) {
		//std::cout << i << " has a size of " << newend[i].size() << " of the size " << newend.size() << " while end has the size of " << end.size() << " and the size of " << end[i].size() << std::endl;
		for (int j = 0; j < end[i].size(); j++) {
			std::get<4>(end[i][j]) = 0.0f;
		}
		Recur(renderer, shader, start + 1, iterations, end[i], newend[i]);
	}
}

void Fractal::Recurse(Renderer renderer, Shader shader, int iterations) {
	std::vector<std::tuple<float, float, float, float, float>> temp;
	for (int i = 0; i < startingLines.size(); i++) {
		temp.push_back(std::make_tuple(std::get<0>(startingLines[i]), std::get<1>(startingLines[i]), std::get<2>(startingLines[i]), std::get<3>(startingLines[i]), 0.0f));
	}
	Recur(renderer, shader, 0, iterations, temp, endingLines);
}

Fractal::~Fractal() {

}