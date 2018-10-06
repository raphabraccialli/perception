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

#ifndef PIXELCOUNTCHECK_H
#define PIXELCOUNTCHECK_H

class pixelCountCheck
{
public:
	pixelCountCheck();

	int run(vector<Vec3f> circles, Mat whiteMask, Mat blackMask, Mat frame);
};

#endif