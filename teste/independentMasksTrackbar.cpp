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
    VideoCapture cap("../../videos_e_gabaritos/bola_parada_favor_da_luz_bottom.avi");
    VideoCapture cap2("../../videos_e_gabaritos/bola_parada_campo_bottom.avi");

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
    Mat frame2, frame_HLS2, white_mask2, black_mask2, green_mask2, light_gray_mask2, dark_gray_mask2, pink_mask2, black_and_white_mask2, not_green_mask2;
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


        // // Show the frames
        // imshow("track_bars_white", white_mask);
        // imshow("track_bars_black", black_mask);
        // imshow("track_bars_green", green_mask);
        // imshow("black_and_white_mask", black_and_white_mask);
        // imshow("Pink Mask", frame);
        


        cap2 >> frame2;
        if(frame2.empty())
        {
            cap2.set(CV_CAP_PROP_POS_FRAMES, 0);
            cap2 >> frame2;
        }

        // Convert from BGR to HLS colorspace
        cvtColor(frame2, frame_HLS2, COLOR_BGR2HLS);
        // Detect the object based on HSV Range Values

        // White
        inRange(frame_HLS2, Scalar(0, whiteLMin, 0), Scalar(180, 255, 255), white_mask2);
        inRange(frame_HLS2, Scalar(0, lightGrayLMin, 0), Scalar(180, 255, lightGraySMax), light_gray_mask2);

        // Black
        inRange(frame_HLS2, Scalar(0, 0, 0), Scalar(180, blackLMax, 255), black_mask2);
        inRange(frame_HLS2, Scalar(0, 0, 0), Scalar(180, darkGrayLMax, darkGraySMax), dark_gray_mask2);

        // Green
        inRange(frame_HLS2, Scalar(greenHMean-greenHVar, greenLMin, greenSMin), Scalar(greenHMean+greenHVar, greenLMax, 255), green_mask2);

        bitwise_or(white_mask2, light_gray_mask2, white_mask2);
        bitwise_or(black_mask2, dark_gray_mask2, black_mask2);
        bitwise_or(black_mask2, white_mask2, black_and_white_mask2);
        bitwise_not(green_mask2, not_green_mask2);
        bitwise_and(white_mask2, not_green_mask2, white_mask2);


        // Show the frames
        // imshow("track_bars_white2", white_mask2);
        // imshow("track_bars_black2", black_mask2);
        // imshow("track_bars_green2", green_mask2);
        //imshow("black_and_white_mask2", black_and_white_mask2);
        // imshow("Pink Mask", frame);

        Mat canvas_white = Mat::zeros(white_mask.rows, white_mask.cols*2+10, white_mask.type());
        Mat canvas_black = Mat::zeros(black_mask.rows, black_mask.cols*2+10, black_mask.type());
        Mat canvas_green = Mat::zeros(green_mask.rows, green_mask.cols*2+10, green_mask.type());
        Mat canvas_original = Mat::zeros(frame2.rows, frame.cols*2+10, frame2.type());

        float resize_factor = 1.5;

        white_mask.copyTo(canvas_white(Range::all(), Range(0, white_mask.cols)));
        white_mask2.copyTo(canvas_white(Range::all(), Range(white_mask.cols+10, white_mask.cols*2 + 10)));

        resize(canvas_white, canvas_white, Size(canvas_white.cols/resize_factor, canvas_white.rows/resize_factor));
        imshow("track_bars_white", canvas_white);

        black_mask.copyTo(canvas_black(Range::all(), Range(0, black_mask.cols)));
        black_mask2.copyTo(canvas_black(Range::all(), Range(black_mask.cols+10, black_mask.cols*2 + 10)));

        resize(canvas_black, canvas_black, Size(canvas_black.cols/resize_factor, canvas_black.rows/resize_factor));
        imshow("track_bars_black", canvas_black);

        green_mask.copyTo(canvas_green(Range::all(), Range(0, green_mask.cols)));
        green_mask2.copyTo(canvas_green(Range::all(), Range(green_mask.cols+10, green_mask.cols*2 + 10)));

        resize(canvas_green, canvas_green, Size(canvas_green.cols/resize_factor, canvas_green.rows/resize_factor));
        imshow("track_bars_green", canvas_green);

        frame.copyTo(canvas_original(Range::all(), Range(0, frame.cols)));
        frame2.copyTo(canvas_original(Range::all(), Range(frame.cols+10, frame.cols*2 + 10)));

        resize(canvas_original, canvas_original, Size(canvas_original.cols/resize_factor, canvas_original.rows/resize_factor));
        imshow("Original", canvas_original);


        char key = (char) waitKey(10);
        if (key == 'q' || key == 27)
        {
            break;
        }
    }
    return 0;
}
