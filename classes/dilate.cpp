#include "dilate.hpp"

//#define DEBUG 1

void dilate::setDilation(int erosion_elem, float erosion_size){
    int erosion_type;
    if( erosion_elem == 0 ){ erosion_type = cv::MORPH_RECT; }
    else if( erosion_elem == 1 ){ erosion_type = cv::MORPH_CROSS; }
    else if( erosion_elem == 2) { erosion_type = cv::MORPH_ELLIPSE; }

    this->element = cv::getStructuringElement( erosion_type,
    cv::Size( 2*erosion_size + 1, 2*erosion_size+1 ),
    cv::Point( erosion_size, erosion_size ) );

}

cv::Mat dilate::runDilation(cv::Mat frame){

    cv::Mat dilated;
    cv::dilate( frame, dilated, this->element);

    return dilated;

}
