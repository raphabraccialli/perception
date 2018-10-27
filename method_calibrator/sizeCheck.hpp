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

	float a, b;
	int run(std::vector<cv::Vec3f> circles);
};

#endif