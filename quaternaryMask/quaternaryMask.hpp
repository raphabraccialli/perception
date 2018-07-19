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

	int blackVMax, whiteVMin, greenHVar;

	Mat blackMask, whiteMask, greenMask;

	void setMask(int blackVMax, int whiteVMin, int greenHVar);
	void generateMask(cv::Mat image);
	
};