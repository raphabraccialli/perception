#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

#ifndef QUATERNARYMASK_H
#define QUATERNARYMASK_H


class quaternaryMask
{
public:
    quaternaryMask(){}

    float resize_factor;

    int blackLMax, whiteLMin, greenHMean, greenHVar, greenSMin;

    Mat blackMask, whiteMask, greenMask;

    void setMask(int blackLMax, int whiteLMin, int greenHMean, int greenHVar, int greenSMin, float resize_factor);
    void generateMask(cv::Mat image);

};

#endif // QUATERNARYMASK_H
