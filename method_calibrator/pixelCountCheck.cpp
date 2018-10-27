#include "pixelCountCheck.hpp"

//#define DEBUG 1 //printa valores na linha de comando

pixelCountCheck::pixelCountCheck(float whiteMin, float blackMin, float resize_factor){
	this->whiteMin = whiteMin;
	this->blackMin = blackMin;
	this->resize_factor = resize_factor;
}

float pixelCountCheck::run(cv::Vec3f candidate, cv::Mat whiteMask, cv::Mat blackMask, cv::Mat frame){

	cv::Mat canvas = cv::Mat::zeros(whiteMask.rows, whiteMask.cols, CV_8UC1);
	cv::Mat maskedWhite, maskedBlack;
	int whiteCount, blackCount;

	cv::Point center;
	center.x = cvRound(candidate[0]/this->resize_factor);
    center.y = cvRound(candidate[1]/this->resize_factor);
    
    int radius = cvRound(candidate[2]/this->resize_factor);

	circle(canvas, center, radius, cv::Scalar(255,255,255), -1, 8, 0 );

	std::cout << "whiteMask: " << whiteMask.rows << "\tcanvas: " << canvas.rows << std::endl;
	cv::bitwise_and(canvas, whiteMask, maskedWhite);
	cv::bitwise_and(canvas, blackMask, maskedBlack);

	whiteCount = cv::countNonZero(maskedWhite);
	blackCount = cv::countNonZero(maskedBlack);

	float area =  CV_PI * radius * radius;

	#ifdef DEBUG
	std::cout << "y: " << candidate[1] << std::endl;
	std::cout << "whiteCount: " << whiteCount << std::endl;
	std::cout << "blackCount: " << blackCount << std::endl;
	std::cout << "proportion: " << whiteCount/(blackCount+1) << std::endl;
	std::cout << std::endl;
	#endif

	if(whiteCount/area > this->whiteMin && blackCount/area > this->blackMin)
		return true;
	else
		return false;
}