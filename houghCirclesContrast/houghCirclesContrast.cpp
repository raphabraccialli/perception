#include "houghCirclesContrast.hpp"

Point houghCirclesContrast::run(Mat frame){


  	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	
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
	
	Point p;

	if(circles.size()>0){
  		p.x = circles[0][0];
  		p.y = circles[0][1];
	}else{
  		p.x = -1;
  		p.y = -1;
	}
	     
	return p;

}

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
  	Point p;

	while(1){
	    // Captures a frame
	    int i=0;
	    bool breaker=false;
	    while(i<5){
	    	cap >> frame;
	    	if(frame.empty()){
	    		breaker=true;
	    		break;
	    	}
	    	i++;
	    }

	    if(breaker)
	    	break;


		houghCirclesContrast hough;

		p = hough.run(frame);

		if(p.x != -1){
		    Point center(p.x, p.y);
		    // circle center
        	circle( frame, center, 3, Scalar(0,0,255), -1, 8, 0 );
        }
		imshow("frame", frame);


		char c=(char)waitKey(0);
	  	// If the frame is empty or esc, break immediately
	    if (c == 27)
	      break;

	}
 
	cap.release();
 
	// Closes all the frames
	destroyAllWindows();
	     
	return 0;

}