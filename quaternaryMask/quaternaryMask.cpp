#include "quaternaryMask.hpp"

using namespace std;
using namespace cv;

void quaternaryMask::setMask(int blackVMax, int whiteVMin, int greenHVar){

}

void quaternaryMask::generateMask(){
	 
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

  	// Creates and sets values to mask
	quaternaryMask mask;
	mask.setMask(10, 10, 10);

	// Creates the matrix
	Mat frame, blackMask, blackDilatedMask, whiteMask, greenMask, ballMask;

	int size = 4;
	int size2 = 8;
	Mat element = getStructuringElement( MORPH_RECT,
                                     Size( 2*size + 1, 2*size+1 ),
                                     Point( size, size ) );
	Mat element2 = getStructuringElement( MORPH_RECT,
                                     Size( 2*size2 + 1, 2*size2+1 ),
                                     Point( size2, size2 ) );

	

	while(1){
	    // Captures a frame
		cap >> frame;
		cap >> frame;
		cap >> frame;
		cap >> frame;
		cap >> frame;

		imshow("Result RGB", frame);

	  	cvtColor(frame, frame, cv::COLOR_BGR2HSV);

	  	// As each pixel is going to be classified in one of four categories
	  	// we start by detecting the easiest one so we can move to more difficult ones later
	  	// We should go: white, green, black, others (left)

	  	

		// White Threshold
		inRange(frame, Scalar(0, 0, 200), Scalar(255, 40, 255), whiteMask);
		erode(whiteMask, whiteMask, element);
		dilate(whiteMask, whiteMask, element);
		imshow("whiteMask", whiteMask);

		// Green Threshold
		inRange(frame, Scalar(40, 10, 0), Scalar(120, 255, 255), greenMask);
		erode(greenMask, greenMask, element);
		dilate(greenMask, greenMask, element);
		imshow("greenMask", greenMask);
	

		// Black Threshold
		inRange(frame, Scalar(0, 0, 0), Scalar(255, 150, 50), blackMask);
		erode(blackMask, blackMask, element);
		dilate(blackMask, blackMask, element2);
		imshow("blackMask", blackMask);

	  	waitKey(0);

	  	// If the frame is empty, break immediately
	    if (frame.empty())
	      break;
	}

}