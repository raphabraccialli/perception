#include "pixelCountCheck.hpp"

//#define DEBUG 1 //printa valores na linha de comando

pixelCountCheck::pixelCountCheck(float whiteMin, float blackMin, float resize_factor){
	this->whiteMin = whiteMin;
	this->blackMin = blackMin;
	this->resize_factor = resize_factor;
}

float pixelCountCheck::run(Vec3f candidate, Mat whiteMask, Mat blackMask, Mat frame){

	Mat canvas = Mat::zeros(whiteMask.rows*this->resize_factor, whiteMask.cols*this->resize_factor, CV_8UC1);
	Mat maskedWhite, maskedBlack;
	int whiteCount, blackCount;

	Point center;
	center.x = cvRound(candidate[0]/this->resize_factor);
    center.y = cvRound(candidate[1]/this->resize_factor);
    
    int radius = cvRound(candidate[2]/this->resize_factor);

	circle(canvas, center, radius, Scalar(255,255,255), -1, 8, 0 );

	bitwise_and(canvas, whiteMask, maskedWhite);
	bitwise_and(canvas, blackMask, maskedBlack);

	whiteCount = countNonZero(maskedWhite);
	blackCount = countNonZero(maskedBlack);

	float area =  CV_PI * radius * radius;

	#ifdef DEBUG
	cout << "y: " << candidate[1] << endl;
	cout << "whiteCount: " << whiteCount << endl;
	cout << "blackCount: " << blackCount << endl;
	cout << "proportion: " << whiteCount/(blackCount+1) << endl;
	cout << endl;
	#endif

	if(whiteCount/area > this->whiteMin && blackCount/area > this->blackMin)
		return true;
	else
		return false;
}