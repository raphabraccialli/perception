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

	int erosion_size = 4;
	int erosion_size2 = 4;
	Mat element = getStructuringElement( MORPH_RECT,
                                     Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                     Point( erosion_size, erosion_size ) );

	

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
	  	// We should go: black, white, green, others (left)

	  	// Black Threshold
		inRange(frame, Scalar(0, 0, 0), Scalar(255, 150, 50), blackMask);
		//imshow("blackMask", blackMask);
		dilate(blackMask, blackDilatedMask, element);
		imshow("blackMaskEroded", blackDilatedMask);

		// White Threshold
		inRange(frame, Scalar(0, 0, 200), Scalar(255, 40, 255), whiteMask);
		//imshow("whiteMask", whiteMask);
		// whiteMask = whiteMask and ~blackMask
		bitwise_and(whiteMask, blackDilatedMask, ballMask);

		// Green Threshold
		inRange(frame, Scalar(40, 10, 0), Scalar(120, 255, 255), greenMask);
		//imshow("greenMask", greenMask);
		dilate(ballMask, ballMask, erosion_size2);
		imshow("contraste preto/branco", ballMask);
	

	  	waitKey(0);

	  	// If the frame is empty, break immediately
	    if (frame.empty())
	      break;
	}

}