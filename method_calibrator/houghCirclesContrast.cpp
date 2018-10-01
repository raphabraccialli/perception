#include "houghCirclesContrast.h"

houghCirclesContrast::houghCirclesContrast()
{

}

vector<Vec3f> houghCirclesContrast::run(Mat frame){

    this->dp = 1;
    this->minDist = frame.rows/8;
    this->param1 = 100;
    this->param2 = 50;
    this->maxRadius = 60;
    this->minRadius = 10;

    /*
    dp – Inverse ratio of the accumulator resolution to the image resolution. For example, if dp=1 , the accumulator has the same resolution as the input image. If dp=2 , the accumulator has half as big width and height.
    minDist – Minimum distance between the centers of the detected circles. If the parameter is too small, multiple neighbor circles may be falsely detected in addition to a true one. If it is too large, some circles may be missed.
    param1 – First method-specific parameter. In case of CV_HOUGH_GRADIENT , it is the higher threshold of the two passed to the Canny() edge detector (the lower one is twice smaller).
    param2 – Second method-specific parameter. In case of CV_HOUGH_GRADIENT , it is the accumulator threshold for the circle centers at the detection stage. The smaller it is, the more false circles may be detected. Circles, corresponding to the larger accumulator values, will be returned first.
    minRadius – Minimum circle radius.
    maxRadius – Maximum circle radius.
    */

    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    Mat gray;
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    Mat grad;
    GaussianBlur( frame, gray, Size(3,3), 0, 0, BORDER_DEFAULT );
    cvtColor(gray, gray, COLOR_BGR2GRAY);

    /// Gradient X
    Sobel( gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    /// Gradient Y
    Sobel( gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );

    convertScaleAbs( grad_x, abs_grad_x );
    convertScaleAbs( grad_y, abs_grad_y );

    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

    vector<Vec3f> circles;

    HoughCircles( grad, circles, CV_HOUGH_GRADIENT, dp, minDist, param1, param2, minRadius, maxRadius );

    return circles;

}
