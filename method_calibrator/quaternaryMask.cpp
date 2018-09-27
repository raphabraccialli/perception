#include "quaternaryMask.h"

//#define DEBUG 1

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
    inRange(maskHLS, Scalar(0, whiteLMin, 0), Scalar(255, 255, 255), this->whiteMask);

    // Green Threshold
    inRange(maskHLS, Scalar(greenHMean-greenHVar, blackLMax, greenSMin), Scalar(greenHMean+greenHVar, whiteLMin, 255), this->greenMask);

    // Black Threshold
    inRange(maskHLS, Scalar(0, 0, 0), Scalar(255, blackLMax, 255), this->blackMask);

}
