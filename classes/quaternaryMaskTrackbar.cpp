#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
const int max_value_H = 360/2;
const int max_value = 255;
const int max_gray = 100;

int whiteLMin = 0, greenHMean = 0, greenHVar = 0, greenSMin = 0, gray_thresh = 0;
int blackLMax = max_value;

static void on_white_l_min(int, void *)
{
    // low_H = min(high_H-1, low_H);
    setTrackbarPos("White L Min", "track_bars_window", whiteLMin);
}
static void on_black_l_max(int, void *)
{
    setTrackbarPos("Black L Max", "track_bars_window", blackLMax);
}
static void on_green_h_var(int, void *)
{
    setTrackbarPos("Green H Var", "track_bars_window", greenHVar);
}
static void on_green_h_mean(int, void *)
{
    setTrackbarPos("Green H Mean", "track_bars_window", greenHMean);
}
static void on_green_s_min(int, void *)
{
    setTrackbarPos("Green S Min", "track_bars_window", greenSMin);
}
static void on_gray_thresh(int, void *)
{
    setTrackbarPos("Gray Thresh", "track_bars_window", gray_thresh);
    float gray_thresh_float = float(gray_thresh);
    gray_thresh = gray_thresh_float/100*(whiteLMin - blackLMax) + blackLMax;
}



int main(int argc, char* argv[])
{
    VideoCapture cap(argc > 1 ? argv[1] : 0);
    //VideoCapture cap("../apartamento_iluminado_bottom.avi");

    namedWindow("track_bars_window");
    // Trackbars to set thresholds for HSV values
    createTrackbar("White L Min", "track_bars_window", &whiteLMin, max_value, on_white_l_min);
    createTrackbar("Black L Max", "track_bars_window", &blackLMax, max_value, on_black_l_max);
    createTrackbar("Green H Var", "track_bars_window", &greenHVar, max_value_H, on_green_h_var);
    createTrackbar("Green H Mean", "track_bars_window", &greenHMean, max_value_H, on_green_h_mean);
    createTrackbar("Green S Min", "track_bars_window", &greenSMin, max_value, on_green_s_min);
    createTrackbar("Gray Thresh", "track_bars_window", &gray_thresh, max_gray, on_gray_thresh);
   
    Mat frame, frame_HLS, white_mask, black_mask, green_mask, light_gray_mask, dark_gray_mask, pink_mask, black_and_white_mask;
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
        inRange(frame_HLS, Scalar(0, whiteLMin, 0), Scalar(255, 255, 255), white_mask);
        inRange(frame_HLS, Scalar(0, 0, 0), Scalar(255, blackLMax, 255), black_mask);
        inRange(frame_HLS, Scalar(greenHMean-greenHVar, blackLMax, greenSMin), Scalar(greenHMean+greenHVar, whiteLMin, 255), green_mask);
        inRange(frame_HLS, Scalar(0, gray_thresh, 0), Scalar(255, 255, greenSMin), light_gray_mask);
        inRange(frame_HLS, Scalar(0, 0, 0), Scalar(255, gray_thresh, greenSMin), dark_gray_mask);

        bitwise_or(white_mask, light_gray_mask, white_mask);
        bitwise_or(black_mask, dark_gray_mask, black_mask);
        bitwise_or(black_mask, white_mask, black_and_white_mask);


        // Show the frames
        imshow("White Mask", white_mask);
        imshow("Black Mask", black_mask);
        imshow("Green Mask", green_mask);
        imshow("Black and White Mask", black_and_white_mask);
        // imshow("Pink Mask", frame);
        imshow("track_bars_window", frame);
        char key = (char) waitKey(0);
        if (key == 'q' || key == 27)
        {
            break;
        }
    }
    return 0;
}