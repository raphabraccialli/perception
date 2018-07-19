#include "quaternaryMask.hpp"

#define DEBUG 1

void quaternaryMask::setMask(int blackVMax, int whiteVMin, int greenHVar){
	this->blackVMax = blackVMax;
	this->whiteVMin = whiteVMin;
	this->greenHVar = greenHVar;
}

void quaternaryMask::generateMask(Mat frame){
	// Converts to HSV colorspace
	cvtColor(frame, frame, COLOR_BGR2HSV);

// As each pixel is going to be classified in one of four categories
  	// we start by detecting the easiest one so we can move to more difficult ones later
  	// We should go: white, green, black, others (left)

	// White Threshold
	inRange(frame, Scalar(0, 0, whiteVMin), Scalar(255, 20, 255), this->whiteMask);

	// Green Threshold
	inRange(frame, Scalar(80-greenHVar, 20, 60), Scalar(80+greenHVar, 255, 255), this->greenMask);

	// Black Threshold
	inRange(frame, Scalar(0, 0, 0), Scalar(255, 255, blackVMax), this->blackMask);
	 
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


  	Mat frame, blackMaskDilated;

  	// Creates and sets values to mask
	quaternaryMask mask;
	mask.setMask(80, 180, 10);


	int size = 8;
	int size2 = 15;
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

	  	mask.generateMask(frame);

		#ifdef DEBUGa
			imshow("Result RGB", frame);
			imshow("this->whiteMask", mask.whiteMask);
			imshow("this->greenMask", mask.greenMask);
			imshow("this->blackMask", mask.blackMask);
		#endif

		imshow("Result RGB", frame);
		dilate(mask.greenMask, mask.greenMask, element2);
		bitwise_not(mask.greenMask, mask.greenMask);
		imshow("Result greenDilatedNOT", mask.greenMask);
		bitwise_and(mask.blackMask, mask.greenMask, mask.blackMask);
		dilate(mask.blackMask, blackMaskDilated, element);
		bitwise_and(blackMaskDilated, mask.whiteMask, frame);
		//bitwise_or(mask.blackMask, frame, frame);
		imshow("Result test", frame);

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