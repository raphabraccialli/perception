#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>

#ifndef PIXELCOUNTCHECK_H
#define PIXELCOUNTCHECK_H

class pixelCountCheck
{
public:
	pixelCountCheck(float whiteMin, float blackMin, float resize_factor);
	
	// minimal percentage of pixels in area
	// area = r² * pi
	float whiteMin, blackMin, resize_factor;

	float run(cv::Vec3f candidate, cv::Mat whiteMask, cv::Mat blackMask, cv::Mat frame);
};

#endif