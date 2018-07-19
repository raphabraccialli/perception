#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

class quaternaryMask
{
public:
	quaternaryMask(){}

	int blackVMax, whiteVMin, greenHVar;

	void setMask(int blackVMax, int whiteVMin, int greenHVar);
	void generateMask();
	
};