#include "quaternaryMask.hpp"

#define DEBUG 1

void quaternaryMask::setMask(int blackLMax, int whiteLMin, int greenHMean, int greenHVar, int greenSMin){
	this->blackLMax = blackLMax;
	this->whiteLMin = whiteLMin;
	this->greenHMean = greenHMean;
	this->greenHVar = greenHVar;
	this->greenSMin = greenSMin;
	
}

void quaternaryMask::generateMask(Mat frame){
	Mat maskHLS;

	// Converts to HSV colorspace
	cvtColor(frame, maskHLS, COLOR_BGR2HLS);

// As each pixel is going to be classified in one of four categories
  	// we start by detecting the easiest one so we can move to more difficult ones later
  	// We should go: white, green, black, others (left)

	// White Threshold
	inRange(frame, Scalar(0, whiteLMin, 0), Scalar(255, 255, 255), this->whiteMask);

	// Green Threshold
	inRange(frame, Scalar(greenHMean-greenHVar, blackLMax, greenSMin), Scalar(greenHMean+greenHVar, whiteLMin, 255), this->greenMask);

	// Black Threshold
	inRange(frame, Scalar(0, 0, 0), Scalar(255, blackLMax, 255), this->blackMask);
	 
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

  	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

  	// Creates and sets values to mask
	quaternaryMask mask;
	//setMask(int blackLMax, int whiteLMin, int greenHMean, int greenHVar, int greenSMin)
	mask.setMask(60, 180, 127, 127, 0);
	//para detecção de bola, greenHMean e greenHVar = 127 desativa detecção de verde (vai abranger toadas cores de L médio)


	int size = 4;
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

		Mat gray;
		Mat grad_x, grad_y;
  		Mat abs_grad_x, abs_grad_y;
  		Mat grad;
		
		GaussianBlur( frame, gray, Size(3,3), 0, 0, BORDER_DEFAULT );
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


	  	mask.generateMask(frame);

		#ifdef DEBUGa
			imshow("Result RGB", frame);
			imshow("this->whiteMask", mask.whiteMask);
			imshow("this->greenMask", mask.greenMask);
			imshow("this->blackMask", mask.blackMask);
		#endif

		//imshow("Result RGB", frame);
		//dilate(mask.greenMask, mask.greenMask, element2);
		//bitwise_not(mask.greenMask, mask.greenMask);
		//imshow("Result greenDilatedNOT", mask.greenMask);
		//bitwise_and(mask.blackMask, mask.greenMask, mask.blackMask);
		dilate(mask.blackMask, mask.blackMask, element2);
		bitwise_and(mask.blackMask, mask.whiteMask, frame);
		//bitwise_or(mask.blackMask, frame, frame);
		//imshow("Result test", frame);



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