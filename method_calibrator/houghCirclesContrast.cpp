#include "houghCirclesContrast.h"

houghCirclesContrast::houghCirclesContrast()
{

}

Point houghCirclesContrast::run(Mat frame){


    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;


    Mat gray;
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    Mat grad;GaussianBlur( frame, gray, Size(3,3), 0, 0, BORDER_DEFAULT );
    cvtColor(gray, gray, COLOR_BGR2GRAY);

    /// Gradient X
    Sobel( gray, grad_x, ddepth, 2, 0, 3, scale, delta, BORDER_DEFAULT );
    /// Gradient Y
    Sobel( gray, grad_y, ddepth, 0, 2, 3, scale, delta, BORDER_DEFAULT );

    convertScaleAbs( grad_x, abs_grad_x );
    convertScaleAbs( grad_y, abs_grad_y );

    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

    vector<Vec3f> circles;

    HoughCircles( grad, circles, CV_HOUGH_GRADIENT, 1, gray.rows/8, 100, 50, 0, 60 );

    Point p;

    if(circles.size()>0){
        p.x = circles[0][0];
        p.y = circles[0][1];
    }else{
        p.x = -1;
        p.y = -1;
    }

    return p;

}
