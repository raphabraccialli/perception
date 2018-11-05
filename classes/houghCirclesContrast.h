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
    houghCirclesContrast(double param1, double param2, double minDist, int minRadius, int maxRadius);

    double dp, minDist, param1, param2;
    int maxRadius, minRadius;

    std::vector<cv::Vec3f> run(cv::Mat frame);
};

#endif // HOUGHCIRCLESCONTRAST_H
