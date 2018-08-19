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
	//definir atributos com parametros e fazer atribuição no construtor
	Point run(Mat frame);

};