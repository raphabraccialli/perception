#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
const int max_value_H = 360/2;
const int max_value = 255;
const String window_capture_name = "Video Capture";
const String window_detection_name = "Object Detection";
int low_H = 0, low_L = 0, low_S = 0;
int high_H = max_value_H, high_L = max_value, high_S = max_value;
static void on_low_H_thresh_trackbar(int, void *)
{
    low_H = min(high_H-1, low_H);
    setTrackbarPos("Low H", window_detection_name, low_H);
}
static void on_high_H_thresh_trackbar(int, void *)
{
    high_H = max(high_H, low_H+1);
    setTrackbarPos("High H", window_detection_name, high_H);
}
static void on_low_L_thresh_trackbar(int, void *)
{
    low_L = min(high_L-1, low_L);
    setTrackbarPos("Low L", window_detection_name, low_L);
}
static void on_high_L_thresh_trackbar(int, void *)
{
    high_L = max(high_L, low_L+1);
    setTrackbarPos("High L", window_detection_name, high_L);
}
static void on_low_S_thresh_trackbar(int, void *)
{
    low_S = min(high_S-1, low_S);
    setTrackbarPos("Low S", window_detection_name, low_S);
}
static void on_high_S_thresh_trackbar(int, void *)
{
    high_S = max(high_S, low_S+1);
    setTrackbarPos("High S", window_detection_name, high_S);
}
int main(int argc, char* argv[])
{
    VideoCapture cap(argc > 1 ? argv[1] : 0);
    //VideoCapture cap("../apartamento_iluminado.avi");
    namedWindow(window_capture_name);
    namedWindow(window_detection_name);
    // Trackbars to set thresholds for HSV values
    createTrackbar("Low H", window_detection_name, &low_H, max_value_H, on_low_H_thresh_trackbar);
    createTrackbar("High H", window_detection_name, &high_H, max_value_H, on_high_H_thresh_trackbar);
    createTrackbar("Low L", window_detection_name, &low_L, max_value, on_low_L_thresh_trackbar);
    createTrackbar("High L", window_detection_name, &high_L, max_value, on_high_L_thresh_trackbar);
    createTrackbar("Low S", window_detection_name, &low_S, max_value, on_low_S_thresh_trackbar);
    createTrackbar("High S", window_detection_name, &high_S, max_value, on_high_S_thresh_trackbar);
    Mat frame, frame_HLS, frame_threshold;
    while (true) {
        cap >> frame;
        if(frame.empty())
        {
            break;
        }
        // Convert from BGR to HLS colorspace
        cvtColor(frame, frame_HLS, COLOR_BGR2HLS);
        // Detect the object based on HSV Range Values
        inRange(frame_HLS, Scalar(low_H, low_L, low_S), Scalar(high_H, high_L, high_S), frame_threshold);
        // Show the frames
        imshow(window_capture_name, frame);
        imshow(window_detection_name, frame_threshold);
        char key = (char) waitKey(0);
        if (key == 'q' || key == 27)
        {
            break;
        }
    }
    return 0;
}
