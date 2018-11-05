#include "pixelCountCheck.hpp"

// #define DEBUG 1 //printa valores na linha de comando

pixelCountCheck::pixelCountCheck(float whiteMin, float blackMin){
	this->whiteMin = whiteMin;
	this->blackMin = blackMin;
}

bool pixelCountCheck::run(cv::Vec3f candidate, cv::Mat whiteMask, cv::Mat blackMask, cv::Mat frame){

	cv::Mat canvas = cv::Mat::zeros(whiteMask.rows, whiteMask.cols, CV_8UC1);
	cv::Mat maskedWhite, maskedBlack;
	int whiteCount, blackCount;

	cv::Point center;
	center.x = cvRound(candidate[0]);
    center.y = cvRound(candidate[1]);
    
    int radius = cvRound(candidate[2]);

	cv::circle(canvas, center, radius, cv::Scalar(255,255,255), -1, 8, 0 );

	cv::bitwise_and(canvas, whiteMask, maskedWhite);
	cv::bitwise_and(canvas, blackMask, maskedBlack);

	whiteCount = cv::countNonZero(maskedWhite);
	blackCount = cv::countNonZero(maskedBlack);

	

	float area =  CV_PI * radius * radius;

	#ifdef DEBUG
	cv::imshow("white", whiteMask);
	cv::imshow("black", blackMask);
	std::cout << "x: " << candidate[0] << "\ty: " << candidate[1] << std::endl;
	std::cout << "whiteCount: " << whiteCount << std::endl;
	std::cout << "blackCount: " << blackCount << std::endl;
	std::cout << "area: " << area << std::endl;
	std::cout << std::endl;
	#endif

	if(whiteCount/area > this->whiteMin && blackCount/area > this->blackMin)
		return true;
	else
		return false;
}