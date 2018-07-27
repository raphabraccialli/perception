#include "houghCirclesContrast/houghCirclesContrast.hpp"

int main(int argc, char *argv[]){
	cout << "rodou" << endl;

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
		cap >> frame;
		cap >> frame;
		cap >> frame;
		cap >> frame;
		cap >> frame;

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
	    if (frame.empty() || c == 27)
	      break;

	}

	cap.release();
 
	// Closes all the frames
	destroyAllWindows();
	     
	return 0;

}