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

#ifndef TESTAMETODO_H
#define TESTAMETODO_H

class testaMetodo
{
public:
	testaMetodo(char* name_file, float a, float b);

	int testa(string nome_gabarito);

	bool evaluate(Point p);

	float a;							//linear coeficient of de range
	float b;							//angular coeficient of the range
	vector<Point> ballPos;				//vector of coordinates of the center of the ball in each frame

	int index;
};

#endif