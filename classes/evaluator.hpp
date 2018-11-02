#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>

#ifndef EVALUATOR_H
#define EVALUATOR_H

class evaluator
{
public:
	evaluator(cv::String name_file, float a, float b);
	
	int add(cv::Point p, cv::Mat frame);
	float evaluate();

	float a, b; 						//coeficientes lineares
	std::vector<cv::Point> ballPos;				//vector of coordinates of the center of the ball in each frame
	std::vector<bool> score;

	int index, fps;

};

int dbg_imshow(cv::Mat frame);

int dbg_circle(cv::Mat frame, cv::Point center, int radius, int color);

#endif