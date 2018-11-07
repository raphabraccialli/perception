#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#ifndef INDEPENDENTMASKS_H
#define INDEPENDENTMASKS_H


class independentMasks
{
public:
    independentMasks(){}

	int whiteLMin, whiteSMax, blackLMax, greenLMax, greenSMin, greenHMean, greenHVar;

    cv::Mat blackMask, whiteMask, greenMask;

    void setMask(int whiteLMin, int whiteSMax, int blackLMax, int greenLMax, int greenSMin, int greenHMean, int greenHVar);

    void generateMask(cv::Mat image);

};

#endif // INDEPENDENTMASKS_H
