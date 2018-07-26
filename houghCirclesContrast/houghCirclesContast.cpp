#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

int main(int argc, char *argv[]){

	// Create a VideoCapture object and open the input file
 	// If the input is the web camera, pass 0 instead of the video file name
 	VideoCapture cap(argv[1]); 

	// Check if camera opened successfully
 	if(!cap.isOpened()){
    	cout << "Error opening video stream or file" << endl;
    	return -1;
  	}


  	Mat frame;

  	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	while(1){
	    // Captures a frame
		cap >> frame;
		cap >> frame;
		cap >> frame;
		cap >> frame;
		cap >> frame;

		Mat gray;
		Mat grad_x, grad_y;
  		Mat abs_grad_x, abs_grad_y;

  		Mat grad;GaussianBlur( frame, gray, Size(3,3), 0, 0, BORDER_DEFAULT );
		cvtColor(gray, gray, COLOR_BGR2GRAY);

		/// Gradient X
		Sobel( gray, grad_x, ddepth, 2, 0, 3, scale, delta, BORDER_DEFAULT );
		/// Gradient Y
		Sobel( gray, grad_y, ddepth, 0, 2, 3, scale, delta, BORDER_DEFAULT );

		convertScaleAbs( grad_x, abs_grad_x );
		convertScaleAbs( grad_y, abs_grad_y );

		addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

		vector<Vec3f> circles;

		HoughCircles( grad, circles, CV_HOUGH_GRADIENT, 1, gray.rows/8, 100, 50, 0, 60 );

		for( size_t i = 0; i < circles.size(); i++ )
		{
		   Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		   int radius = cvRound(circles[i][2]);
		   cout << radius << endl;
		   // circle center
		   circle( frame, center, 3, Scalar(0,255,0), -1, 8, 0 );
		   // circle outline
		   circle( frame, center, radius, Scalar(0,0,255), 3, 8, 0 );
		}

		imshow("frame", frame);
		imshow("grad", grad);

		char c=(char)waitKey(0);
	  	// If the frame is empty or esc, break immediately
	    if (frame.empty() || c == 27)
	      break;

	}

	cap.release();
 
	// Closes all the frames
	destroyAllWindows();
	     
	return 0;

}