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

void quaternaryMask::generateMask(cv::Mat frame){
    cv::Mat maskHLS;

    // Resizes the shit out of this fucking matrix, mate
    cv::resize(frame, frame, cv::Size(), this->resize_factor, this->resize_factor);

    // Converts to HSV colorspace
    cv::cvtColor(frame, maskHLS, cv::COLOR_BGR2HLS);

    // As each pixel is going to be classified in one of four categories
    // we start by detecting the easiest one so we can move to more difficult ones later
    // We should go: white, green, black, others (left)

    // White Threshold
    cv::inRange(maskHLS, cv::Scalar(0, whiteLMin, 0), cv::Scalar(255, 255, 255), this->whiteMask);

    // Green Threshold
    cv::inRange(maskHLS, cv::Scalar(greenHMean-greenHVar, blackLMax, greenSMin), cv::Scalar(greenHMean+greenHVar, whiteLMin, 255), this->greenMask);

    // Black Threshold
    cv::inRange(maskHLS, cv::Scalar(0, 0, 0), cv::Scalar(255, blackLMax, 255), this->blackMask);

}
