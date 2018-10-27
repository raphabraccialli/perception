#include "quaternaryMask.h"

//#define DEBUG 1

void quaternaryMask::setMask(int blackLMax, int whiteLMin, int greenHMean, int greenHVar, int greenSMin, float resize_factor){
    this->blackLMax = blackLMax;
    this->whiteLMin = whiteLMin;
    this->greenHMean = greenHMean;
    this->greenHVar = greenHVar;
    this->greenSMin = greenSMin;
    this->resize_factor = resize_factor;

}

void quaternaryMask::generateMask(Mat frame){
    Mat maskHLS;

    // Resizes the shit out of this fucking matrix, mate
    resize(frame, frame, Size(), this->resize_factor, this->resize_factor);

    // Converts to HSV colorspace
    cvtColor(frame, maskHLS, COLOR_BGR2HLS);

    // As each pixel is going to be classified in one of four categories
    // we start by detecting the easiest one so we can move to more difficult ones later
    // We should go: white, green, black, others (left)

    // White Threshold
    inRange(maskHLS, Scalar(0, whiteLMin, 0), Scalar(255, 255, 255), this->whiteMask);

    // Green Threshold
    inRange(maskHLS, Scalar(greenHMean-greenHVar, blackLMax, greenSMin), Scalar(greenHMean+greenHVar, whiteLMin, 255), this->greenMask);

    // Black Threshold
    inRange(maskHLS, Scalar(0, 0, 0), Scalar(255, blackLMax, 255), this->blackMask);

}
