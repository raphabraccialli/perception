#include "quaternaryMask.h"

//#define DEBUG 1

void quaternaryMask::setMask(int blackLMax, int whiteLMin, int greenHMean, int greenHVar, int greenSMin, int gray_thresh){
    this->blackLMax = blackLMax;
    this->whiteLMin = whiteLMin;
    this->greenHMean = greenHMean;
    this->greenHVar = greenHVar;
    this->greenSMin = greenSMin;
    this->gray_thresh = gray_thresh;

}

void quaternaryMask::generateMask(cv::Mat frame){
    cv::Mat maskHLS;
    cv::Mat light_gray_mask, dark_gray_mask;

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

    // Gray Threshold
    cv::inRange(maskHLS, cv::Scalar(0, gray_thresh, 0), cv::Scalar(255, 255, greenSMin), light_gray_mask);
    cv::inRange(maskHLS, cv::Scalar(0, 0, 0), cv::Scalar(255, gray_thresh, greenSMin), dark_gray_mask);

    bitwise_or(this->whiteMask, light_gray_mask, this->whiteMask);
    bitwise_or(this->blackMask, dark_gray_mask, this->blackMask);

}
