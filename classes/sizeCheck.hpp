
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>

#ifndef SIZECHECK_H
#define SIZECHECK_H

class sizeCheck
{
public:
	sizeCheck(float a, float b);

	//Câmera de cima
	// Raio = +0.247*y - 27.6		R^2=0.994
	//float a = 0.247, b = 27.6;

	//Câmera de baixo 
	// Raio = +0.198*y - 22.2		R^2=0.994
	// float a = 0.198, b = 22.2;

	float a, b;

	bool run(cv::Point center, int radius);
};

#endif