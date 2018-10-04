#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#ifndef EVALUATOR_H
#define EVALUATOR_H

class evaluator
{
public:
	evaluator(String name_file, float a, float b);

	int testa(string nome_gabarito);

	int add(Point p);
	float evaluate();

	float a, b; 						//coeficientes lineares
	vector<Point> ballPos;				//vector of coordinates of the center of the ball in each frame
	vector<bool> score;

	int index, fps;

};

#endif