#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

class houghCirclesContrast
{
public:
	houghCirclesContrast(){}

	Point run(Mat frame);

};