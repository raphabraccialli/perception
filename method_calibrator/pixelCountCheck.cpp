#include "pixelCountCheck.hpp"

#define DEBUG 1

pixelCountCheck::pixelCountCheck(int propMin, int propMax){
	this->propMin = propMin;
	this->propMax = propMax;
}

int pixelCountCheck::run(vector<Vec3f> circles, Mat whiteMask, Mat blackMask, Mat frame){
	vector<bool> looksLikeABall;
	for(int i = 0; i < circles.size(); i++){
		Mat canvas = Mat::zeros(whiteMask.rows, whiteMask.cols, CV_8UC1);
		Mat maskedWhite, maskedBlack;
		int whiteCount, blackCount;

		Point center;
		center.x = cvRound(circles[i][0]);
        center.y = cvRound(circles[i][1]);
        
        int radius = cvRound(circles[i][2]);

		circle(canvas, center, radius, Scalar(255,255,255), -1, 8, 0 );

		bitwise_and(canvas, whiteMask, maskedWhite);
		bitwise_and(canvas, blackMask, maskedBlack);

		whiteCount = countNonZero(maskedWhite);
		blackCount = countNonZero(maskedBlack);

		#ifdef DEBUG
		cout << "bola: " << i <<  "\ty: " << circles[0][1] << endl;
		cout << "whiteCount: " << whiteCount << endl;
		cout << "blackCount: " << blackCount << endl;
		cout << "proportion: " << whiteCount/(blackCount+1) << endl;
		cout << endl;
		#endif

	}
	return 0;
}