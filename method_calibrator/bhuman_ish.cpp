#include "bhuman_ish.h"

//#define print 1
//#define opencv3 1
//#define opencv2 1

bhuman_ish::bhuman_ish()
{

}

vector<KeyPoint> bhuman_ish::run(Mat frame)
{
    vector<KeyPoint> keypoints = this->blob(frame);
    return keypoints;
}

vector<KeyPoint> bhuman_ish::blob(Mat frame)
{
    vector<KeyPoint> keypoints;
    #ifdef opencv3
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(); 
    detector->detect(frame, keypoints);
    #endif

    #ifdef opencv2

    #endif

    return keypoints;

}

