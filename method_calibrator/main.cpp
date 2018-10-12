#include "pixelCountCheck.hpp"
#include "quaternaryMask.h"
#include "houghCirclesContrast.h"
#include "evaluator.hpp"

struct param_set{
    int param1 = 0;
    int param2 = 0;
    float total = 0;
};

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

    quaternaryMask Mask;
    Mask.setMask(50, 200, 60, 30, 10);

    string linefps;
    ifstream myfile(argv[2]);
    getline(myfile, linefps);
    int fps_new = stoi(linefps, 0, 10);
    int fps = cap.get(CV_CAP_PROP_FPS);
    int skip = (fps/fps_new) - 1;
    myfile.close();

    param_set best;

    for(int param1 = 66; param1 < 74; param1=param1+2){
        for(int param2 = 22; param2 < 30; param2=param2+2){
            cap.set(CV_CAP_PROP_POS_FRAMES, 0);
            houghCirclesContrast hough(param1, param2);
            evaluator evaluator(argv[2], 0.04, 10);
            cout << "param1: " << param1 << "\tparam2: " << param2;
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
                //cout << "BOLAS: " << circles.size() << endl;
                //////////////////////////////////////// teste ///////////////////////
                pixelCountCheck checker;
                checker.run(circles, Mask.whiteMask, Mask.blackMask, frame);

                Point center(-1, -1);
                int radius = -1;
                //for single circle
                if(circles.size() > 0){
                    center.x = cvRound(circles[0][0]);
                    center.y = cvRound(circles[0][1]);
                    radius = cvRound(circles[0][2]);
                }
                //metodo da livia retorna int
                int gotItRight = evaluator.add(center, frame);
                /*imshow("debug", frame);

                char c=(char)waitKey(0);
                // If the frame is empty or esc, break immediately
                if (c == 27){
                    cout << "BREAK" << endl;
                    break;
                }*/

                for(int i=0; i < skip; i++){
                    cap >> frame;
                }

            }
            float total = evaluator.evaluate()*100;
            cout << "\tTOTAL: " << total << "%";
            if(total > best.total){
                best.total = total;
                best.param1 = param1;
                best.param2 = param2;
                cout << " BEST SO FAR!" << endl;
            }else{
                cout << endl;
            }

        }
    }
    
    cout << "///////////////////////////////////////////////////////////////" << 
    endl << "BEST SET IS: \tparam1: " << best.param1 <<
    "\tparam2: " << best.param2 <<
    "\tTotal: " << best.total <<
    endl << "///////////////////////////////////////////////////////////////" << endl;
    

    cap.release();

    // Closes all the frames
    destroyAllWindows();

    return 0;

}
