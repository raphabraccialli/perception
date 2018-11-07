#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
const int max_value_H = 360/2;
const int max_value = 255;
const int max_gray = 100;

////////// White //////////
int whiteLMin = 0, lightGraySMax = 0, lightGrayLMin = 0;
static void on_white_l_min(int, void *)
{
    setTrackbarPos("White L Min", "track_bars_white", whiteLMin);
}
static void on_light_gray_s_max(int, void *)
{
    setTrackbarPos("Light Gray S Max", "track_bars_white", lightGraySMax);
}
static void on_light_gray_l_min(int, void *)
{
    setTrackbarPos("Light Gray L Min", "track_bars_white", lightGrayLMin);
}

////////// Black //////////
int blackLMax = 0, darkGraySMax = 0, darkGrayLMax = 0;
static void on_black_l_max(int, void *)
{
    setTrackbarPos("Black L Max", "track_bars_black", blackLMax);
}
static void on_dark_gray_s_max(int, void *)
{
    setTrackbarPos("Dark Gray S Max", "track_bars_black", darkGraySMax);
}
static void on_dark_gray_l_max(int, void *)
{
    setTrackbarPos("Dark Gray L Max", "track_bars_black", darkGrayLMax);
}

////////// Green //////////
int greenLMin = 0, greenLMax = 0, greenSMin = 0, greenHMean = 0, greenHVar = 0;
static void on_green_l_min(int, void *)
{
    setTrackbarPos("Green L Min", "track_bars_green", greenLMin);
}
static void on_green_l_max(int, void *)
{
    setTrackbarPos("Green L Max", "track_bars_green", greenLMax);
}
static void on_green_s_min(int, void *)
{
    setTrackbarPos("Green S Min", "track_bars_green", greenSMin);
}
static void on_green_h_mean(int, void *)
{
    setTrackbarPos("Green H Mean", "track_bars_green", greenHMean);
}
static void on_green_h_var(int, void *)
{
    setTrackbarPos("Green H Var", "track_bars_green", greenHVar);
}


int main(int argc, char* argv[])
{
    //VideoCapture cap(argc > 1 ? argv[1] : 0);
    VideoCapture cap("../bola_parada_campo.avi");

    namedWindow("track_bars_white");
    namedWindow("track_bars_black");
    namedWindow("track_bars_green");

    // Trackbars to set thresholds for HSV values
    // White
    createTrackbar("White L Min", "track_bars_white", &whiteLMin, max_value, on_white_l_min);
    createTrackbar("Light Gray S Max", "track_bars_white", &lightGraySMax, max_value, on_light_gray_s_max);
    createTrackbar("Light Gray L Min", "track_bars_white", &lightGrayLMin, max_value_H, on_light_gray_l_min);
    // Black
    createTrackbar("Black L Max", "track_bars_black", &blackLMax, max_value_H, on_black_l_max);
    createTrackbar("Dark Gray S Max", "track_bars_black", &darkGraySMax, max_value, on_dark_gray_s_max);
    createTrackbar("Dark Gray L Max", "track_bars_black", &darkGrayLMax, max_gray, on_dark_gray_l_max);
    // Green
    createTrackbar("Green L Min", "track_bars_green", &greenLMin, max_value, on_green_l_min);
    createTrackbar("Green L Max", "track_bars_green", &greenLMax, max_value, on_green_l_max);
    createTrackbar("Green S Min", "track_bars_green", &greenSMin, max_value, on_green_s_min);
    createTrackbar("Green H Mean", "track_bars_green", &greenHMean, max_value_H, on_green_h_mean);
    createTrackbar("Green H Var", "track_bars_green", &greenHVar, max_value_H, on_green_h_var);
   
    Mat frame, frame_HLS, white_mask, black_mask, green_mask, light_gray_mask, dark_gray_mask, pink_mask, black_and_white_mask, not_green_mask;
    while (true) {
        cap >> frame;
        if(frame.empty())
        {
            cap.set(CV_CAP_PROP_POS_FRAMES, 0);
            cap >> frame;
        }

        // Convert from BGR to HLS colorspace
        cvtColor(frame, frame_HLS, COLOR_BGR2HLS);
        // Detect the object based on HSV Range Values

        // White
        inRange(frame_HLS, Scalar(0, whiteLMin, 0), Scalar(180, 255, 255), white_mask);
        inRange(frame_HLS, Scalar(0, lightGrayLMin, 0), Scalar(180, 255, lightGraySMax), light_gray_mask);

        // Black
        inRange(frame_HLS, Scalar(0, 0, 0), Scalar(180, blackLMax, 255), black_mask);
        inRange(frame_HLS, Scalar(0, 0, 0), Scalar(180, darkGrayLMax, darkGraySMax), dark_gray_mask);

        // Green
        inRange(frame_HLS, Scalar(greenHMean-greenHVar, greenLMin, greenSMin), Scalar(greenHMean+greenHVar, greenLMax, 255), green_mask);
        
        

        bitwise_or(white_mask, light_gray_mask, white_mask);
        bitwise_or(black_mask, dark_gray_mask, black_mask);
        bitwise_or(black_mask, white_mask, black_and_white_mask);
        bitwise_not(green_mask, not_green_mask);
        bitwise_and(white_mask, not_green_mask, white_mask);


        // Show the frames
        imshow("track_bars_white", white_mask);
        imshow("track_bars_black", black_mask);
        imshow("track_bars_green", green_mask);
        imshow("black_and_white_mask", black_and_white_mask);
        // imshow("Pink Mask", frame);
        imshow("Original", frame);
        char key = (char) waitKey(0);
        if (key == 'q' || key == 27)
        {
            break;
        }
    }
    return 0;
}
