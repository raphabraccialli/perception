

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
	
	int test(cv::Point p, cv::Mat frame);
	float evaluate();
	void add(bool data);

	//Câmera de cima
	// Raio = +0.247*y - 27.6		R^2=0.994
	//float a = 0.247, b = 27.6;

	//Câmera de baixo 
	// Raio = +0.198*y - 22.2		R^2=0.994
	// float a = 0.198, b = 22.2;


	float a, b; 						//coeficientes lineares
	std::vector<cv::Point> ballPos;				//vector of coordinates of the center of the ball in each frame
	std::vector<bool> score;

	int index, fps;

};

int dbg_imshow(cv::Mat frame);

int dbg_circle(cv::Mat frame, cv::Point center, int radius, int color);

#endif