#include "../classes/pixelCountCheck.hpp"
#include "../classes/quaternaryMask.h"
#include "../classes/houghCirclesContrast.h"

#define DEBUG 1

#define H_PARAM_1 76
#define H_PARAM_2 16
#define P_PARAM_1 0.5
#define P_PARAM_2 0

#define BLACK_L_MAX 50
#define WHITE_L_MIN 200
#define GREEN_H_MEAN 60
#define GREEN_H_VAR 30
#define GREEN_S_MIN 10

#define RESIZE_FACTOR 0.5

int main(int argc, char *argv[]){

    // Create a VideoCapture object and open the input file
    // If the input is the web camera, pass 0 instead of the video file name
    cv::VideoCapture cap(argv[1]);

    // Check if camera opened successfully
    if(!cap.isOpened()){
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }

    float resize_factor = RESIZE_FACTOR;

    cv::Mat frame;
    std::vector<cv::Vec3f> circles;

    quaternaryMask Mask;
    Mask.setMask(BLACK_L_MAX, WHITE_L_MIN, GREEN_H_MEAN, GREEN_H_VAR, GREEN_S_MIN, resize_factor);

    cap.set(CV_CAP_PROP_POS_FRAMES, 0);
    houghCirclesContrast hough(H_PARAM_1, H_PARAM_2, resize_factor);
    pixelCountCheck pixelChecker(P_PARAM_1, P_PARAM_2, resize_factor);

    while(1){
        // Capture frame-by-frame in the specified frame rate fps_new
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty())
          break;

        //find best circle
        Mask.generateMask(frame);
        // frame * greenMask para eliminar circulos fora do campo
        //(e conferir se ajuda no processamento)
        circles = hough.run(frame);
        cv::Point center(-1, -1);
        int radius = -1;

        //for single circle
        if(circles.size() > 0){
            for(int i = 0; i < circles.size() && i < 10; i++){
                //pixelcount faz a sua mágica
                if(pixelChecker.run(circles[i], Mask.whiteMask, Mask.blackMask, frame)){
                    center.x = cvRound(circles[i][0]);
                    center.y = cvRound(circles[i][1]);
                    radius = cvRound(circles[i][2]);

                    circle( frame, center, radius, cv::Scalar(0,0,255), 3, 8, 0 );
                    //primeiro que aceita o threshold -> break
                    break;
                }
            }
        }

        #ifdef DEBUG
            cv::imshow("debug", frame);

            char c =(char)cv::waitKey(0);
            // If the frame is empty or esc, break immediately
            if (c == 27){
                std::cout << "BREAK" << std::endl;
                break;
            }
        #endif
    }

    cap.release();

    // Closes all the frames
    cv::destroyAllWindows();

    return 0;

}
