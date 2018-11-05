#include "houghCirclesContrast.h"

houghCirclesContrast::houghCirclesContrast(int param1, int param2, float resize_factor)
{
    this->param1 = param1; //thresh canny
    this->param2 = param2; //thresh acumulador
    this->resize_factor = resize_factor; //resize factor
}

std::vector<cv::Vec3f> houghCirclesContrast::run(cv::Mat frame){

    this->dp = 1;
    this->maxRadius = 60 * resize_factor;
    this->minRadius = 10 * resize_factor;
    this->minDist = this->minRadius/2;

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
    resize(gray, gray, cv::Size(), resize_factor, resize_factor);
    cv::imshow("gray", gray);

    cv::HoughCircles( gray, circles, CV_HOUGH_GRADIENT, dp, minDist, param1, param2, minRadius, maxRadius );

    /*
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // circle outline
        circle( gray, center, radius, Scalar(255,255,255), 3, 8, 0 );

    }*/

    for( size_t i = 0; i < circles.size(); i++ )
        {
            circles[i][0] *= 1/resize_factor;
            circles[i][1] *= 1/resize_factor;
            circles[i][2] *= 1/resize_factor;
        }

    return circles;

}
