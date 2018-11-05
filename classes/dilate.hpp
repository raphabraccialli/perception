#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>

#ifndef DILATE_H
#define DILATE_H

class dilate
{
public:
	dilate(){}
	void setDilation(int erosion_elem, int erosion_size);
	cv::Mat runDilation(cv::Mat frame);
	cv::Mat element;

};

#endif