#include "houghCirclesContrast.h"

houghCirclesContrast::houghCirclesContrast(double param1, double param2, double minDist, int minRadius, int maxRadius)
{
    this->param1 = param1; //thresh canny
    this->param2 = param2; //thresh acumulador
    this->minDist = minDist; //min distance between balls
    this->minRadius = minRadius; // min ball radius
    this->maxRadius = maxRadius; // max ball radius

}

std::vector<cv::Vec3f> houghCirclesContrast::run(cv::Mat frame){

    this->dp = 1;

    /*
    dp – Inverse ratio of the accumulator resolution to the image resolution. For example, if dp=1 , the accumulator has the same resolution as the input image. If dp=2 , the accumulator has half as big width and height.
    minDist – Minimum distance between the centers of the detected circles. If the parameter is too small, multiple neighbor circles may be falsely detected in addition to a true one. If it is too large, some circles may be missed.
    param1 – First method-specific parameter. In case of CV_HOUGH_GRADIENT , it is the higher threshold of the two passed to the Canny() edge detector (the lower one is twice smaller).
    param2 – Second method-specific parameter. In case of CV_HOUGH_GRADIENT , it is the accumulator threshold for the circle centers at the detection stage. The smaller it is, the more false circles may be detected. Circles, corresponding to the larger accumulator values, will be returned first.
    minRadius – Minimum circle radius.
    maxRadius – Maximum circle radius.
    */

    std::vector<cv::Vec3f> circles;

    cv::Mat gray;

    // resize
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::imshow("gray", gray);

    cv::HoughCircles( gray, circles, CV_HOUGH_GRADIENT, dp, minDist, param1, param2, minRadius, maxRadius );

    return circles;

}
