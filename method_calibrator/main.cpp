#include "quaternaryMask.h"
#include "houghCirclesContrast.h"
#include "evaluator.hpp"

int main(int argc, char *argv[]){


    // Create a VideoCapture object and open the input file
    // If the input is the web camera, pass 0 instead of the video file name
    VideoCapture cap(argv[1]);

    // Check if camera opened successfully
    if(!cap.isOpened()){
        cout << "Error opening video stream or file" << endl;
        return -1;
    }


    Mat frame;
    vector<Vec3f> circles;
    houghCirclesContrast hough;

    quaternaryMask Mask;
    Mask.setMask(50, 200, 60, 30, 10);

    evaluator evaluator(argv[3], 0.04, 10);

    int fps = cap.get(CV_CAP_PROP_FPS);
    int fps_new = atoi(argv[2]);
    int skip = (fps/fps_new) - 1;

    while(1){

        // Capture frame-by-frame in the specified frame rate fps_new
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty())
          break;

        // Captures a frame and skip some
        /*int i=0;
        bool breaker=false;
        while(i<skip){
            cap >> frame;
            if(frame.empty()){
                breaker=true;
                break;
            }
            i++;
        }
        if(breaker)
            break;*/

        //find best circle
        Mask.generateMask(frame);
        // frame * greenMask para eliminar circulos fora do campo
        //(e conferir se ajuda no processamento)
        circles = hough.run(frame);

        Point center(-1, -1);
        int radius = -1;

        //for single circle
        if(circles.size() > 0){
            center.x = cvRound(circles[0][0]);
            center.y = cvRound(circles[0][1]);
            radius = cvRound(circles[0][2]);
        }
        cout << "center: " << center << endl;
        //metodo da livia retorna int
        int gotItRight = evaluator.add(center);

        ////////////////////// implementar falsos positivos e falso negativo

        // circle outline
        if(gotItRight == 1){
            cout << "GOT IT RIGHT" << endl;
            if(center.x != -1){
                circle( frame, center, radius, Scalar(0,255, 0), 3, 8, 0 );
            }
        }else{
            cout << "SHAME ON YOU" << endl;
            if(center.x != -1){
                circle( frame, center, radius, Scalar(0,0,255), 3, 8, 0 );
            }else{
            }
        }

        imshow("frame", frame);


        char c=(char)waitKey(0);
        // If the frame is empty or esc, break immediately
        if (c == 27){
            cout << "BREAK" << endl;
            break;
        }

        for(int i=0; i < skip; i++){
            cap >> frame;
        }

    }

    cout << "TOTAL: " << evaluator.evaluate()*100 << "%" << endl;

    cap.release();

    // Closes all the frames
    destroyAllWindows();

    return 0;

}
