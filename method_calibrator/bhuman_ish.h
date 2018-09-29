#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

#ifndef BHUMAN_ISH_H
#define BHUMAN_ISH_H


class bhuman_ish
{
public:
    bhuman_ish();

    vector<KeyPoint> run(Mat frame);
    vector<KeyPoint> blob(Mat frame);

};

#endif // BHUMAN_ISH_H
