#include "independentMasks.hpp"

//#define DEBUG 1

void independentMasks::setMask
(int whiteLMin, int whiteSMax,
 int blackLMax,
  int greenLMax, int greenSMin, int greenHMean, int greenHVar){
    this->whiteLMin = whiteLMin;
    this->whiteSMax = whiteSMax;
    this->blackLMax = blackLMax;
    this->greenLMax = greenLMax;
    this->greenSMin = greenSMin;
    this->greenHMean = greenHMean;
    this->greenHVar = greenHVar;

}

void independentMasks::generateMask(cv::Mat frame){
    cv::Mat frame_HLS;
    cv::Mat notGreenMask;

    // Converts to HSV colorspace
    cv::cvtColor(frame, frame_HLS, cv::COLOR_BGR2HLS);

    // As each pixel is going to be classified in one of four categories
    // we start by detecting the easiest one so we can move to more difficult ones later
    // We should go: white, green, black, others (left)

      // White
    cv::inRange(frame_HLS, cv::Scalar(0, this->whiteLMin, 0), cv::Scalar(180, 255, whiteSMax), this->whiteMask);

    // Black
    cv::inRange(frame_HLS, cv::Scalar(0, 0, 0), cv::Scalar(180, this->blackLMax, 255), this->blackMask);

    // Green
    cv::inRange(frame_HLS, cv::Scalar(greenHMean-greenHVar, 0, greenSMin), cv::Scalar(greenHMean+greenHVar, greenLMax, 255), this->greenMask);
        

    cv::bitwise_not(this->greenMask, notGreenMask);
    cv::bitwise_and(this->whiteMask, notGreenMask, this->whiteMask);

}
