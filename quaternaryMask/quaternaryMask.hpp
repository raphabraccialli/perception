#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

class quaternaryMask
{
public:
	quaternaryMask(){}

	int blackVMax, whiteVMin, greenHMean, greenHVar, greenSMin;

	Mat blackMask, whiteMask, greenMask;

	void setMask(int blackVMax, int whiteVMin, int greenHMean, int greenHVar, int greenSMin);
	void generateMask(cv::Mat image);
	
};