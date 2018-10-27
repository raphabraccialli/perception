#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#ifndef HOUGHCIRCLESCONTRAST_H
#define HOUGHCIRCLESCONTRAST_H


class houghCirclesContrast
{
public:
    houghCirclesContrast(int param, int param2, float resize_factor);

    double dp, minDist, param1, param2;
    int maxRadius, minRadius;
    float resize_factor;

    std::vector<cv::Vec3f> run(cv::Mat frame);
};

#endif // HOUGHCIRCLESCONTRAST_H
