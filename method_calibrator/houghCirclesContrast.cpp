#include "houghCirclesContrast.h"

houghCirclesContrast::houghCirclesContrast()
{

}

vector<Vec3f> houghCirclesContrast::run(Mat frame){

    this->resize_factor = 0.25;

    this->dp = 1;
    this->minDist = frame.rows/8;
    this->param1 = 80; //thresh canny
    this->param2 = 20; //thresh acumulador
    this->maxRadius = 60 * resize_factor;
    this->minRadius = 10 * resize_factor;

    /*
    dp – Inverse ratio of the accumulator resolution to the image resolution. For example, if dp=1 , the accumulator has the same resolution as the input image. If dp=2 , the accumulator has half as big width and height.
    minDist – Minimum distance between the centers of the detected circles. If the parameter is too small, multiple neighbor circles may be falsely detected in addition to a true one. If it is too large, some circles may be missed.
    param1 – First method-specific parameter. In case of CV_HOUGH_GRADIENT , it is the higher threshold of the two passed to the Canny() edge detector (the lower one is twice smaller).
    param2 – Second method-specific parameter. In case of CV_HOUGH_GRADIENT , it is the accumulator threshold for the circle centers at the detection stage. The smaller it is, the more false circles may be detected. Circles, corresponding to the larger accumulator values, will be returned first.
    minRadius – Minimum circle radius.
    maxRadius – Maximum circle radius.
    */

    vector<Vec3f> circles;

    Mat gray;

    // resize
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    resize(gray, gray, Size(), resize_factor, resize_factor);

    HoughCircles( gray, circles, CV_HOUGH_GRADIENT, dp, minDist, param1, param2, minRadius, maxRadius );

    for( size_t i = 0; i < circles.size(); i++ )
    {
        /*if(bool da livia){
            circle( frame, center, 3, Scalar(0,255, 0), -1, 8, 0 );    
        }else{
            circle( frame, center, 3, Scalar(0,0,255), -1, 8, 0 );
        }

        */

        //Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        //int radius = cvRound(circles[i][2]);
        // circle outline
        //circle( gray, center, radius, Scalar(255,255,255), 3, 8, 0 );
        //print radius

    }

    //imshow("gray", gray);

    for( size_t i = 0; i < circles.size(); i++ )
        {
            cout << circles[i][0] << endl;
            circles[i][0] *= 1/resize_factor;
            circles[i][1] *= 1/resize_factor;
            circles[i][2] *= 1/resize_factor;
            cout << circles[i][0] << endl;
        }

    return circles;

}
