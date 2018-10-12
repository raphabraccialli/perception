#include "pixelCountCheck.hpp"
#include "quaternaryMask.h"
#include "houghCirclesContrast.h"
#include "evaluator.hpp"

//#define DEBUG 1 //usar junto com debug da evaluator.cpp

struct param_set{
    int hough_param1 = 0;
    int hough_param2 = 0;
    float hough_total = 0;

    int pixel_param1 = 0;
    int pixel_param2 = 0;
    float pixel_total = 0;
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

    ////////////////////////////////////////////////////////////
    //////////////////// CALIBRA HOUGH CIRCLES /////////////////
    ////////////////////////////////////////////////////////////
    if(argv[3]){
        for(int hough_param1 = 66; hough_param1 < 74; hough_param1=hough_param1+2){
            for(int hough_param2 = 22; hough_param2 < 30; hough_param2=hough_param2+2){
                cap.set(CV_CAP_PROP_POS_FRAMES, 0);
                houghCirclesContrast hough(hough_param1, hough_param2);
                evaluator evaluator(argv[2], 0.04, 10);
                cout << "hough_param1: " << hough_param1 << "\though_param2: " << hough_param2;
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
                    //metodo da livia retorna int
                    int gotItRight = evaluator.add(center, frame);
                    
                    #ifdef DEBUG
                        imshow("debug", frame);

                        char c=(char)waitKey(0);
                        // If the frame is empty or esc, break immediately
                        if (c == 27){
                            cout << "BREAK" << endl;
                            break;
                        }
                    #endif

                    for(int i=0; i < skip; i++){
                        cap >> frame;
                    }

                }
                float hough_total = evaluator.evaluate()*100;
                cout << "\though_total: " << hough_total << "%";
                if(hough_total > best.hough_total){
                    best.hough_total = hough_total;
                    best.hough_param1 = hough_param1;
                    best.hough_param2 = hough_param2;
                    cout << "\tBEST SO FAR!" << endl;
                }else{
                    cout << endl;
                }

            }
        }
        
        cout << "///////////////////////////////////////////////////////////////" << 
        endl << "BEST SET IS: \though_param1: " << best.hough_param1 <<
        "\though_param2: " << best.hough_param2 <<
        "\though_total: " << best.hough_total <<
        endl << "///////////////////////////////////////////////////////////////" << endl;
    }

    ////////////////////////////////////////////////////////////
    //////////////////// CALIBRA PIXELCOUNT ////////////////////
    ////////////////////////////////////////////////////////////
    if(argv[4]){
        for(int pixel_param1 = 66; pixel_param1 < 74; pixel_param1=pixel_param1+2){
            for(int pixel_param2 = 22; pixel_param2 < 30; pixel_param2=pixel_param2+2){
                cap.set(CV_CAP_PROP_POS_FRAMES, 0);
                houghCirclesContrast hough(best.hough_param1, best.hough_param2);
                //iniciar pixelcount com pixelbranco vs y e pixelbranco vs preto
                evaluator evaluator(argv[2], 0.04, 10);
                cout << "hough_param1: " << hough_param1 << "\though_param2: " << hough_param2;
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
                    while(int i < circle.size() && i < 5){
                        //pixelcount faz a sua mágica
                        //primeiro que aceita o threshold ->break
                    }
                    
                    //metodo da livia retorna int
                    int gotItRight = evaluator.add(center, frame);
                    
                    #ifdef DEBUG
                        imshow("debug", frame);

                        char c=(char)waitKey(0);
                        // If the frame is empty or esc, break immediately
                        if (c == 27){
                            cout << "BREAK" << endl;
                            break;
                        }
                    #endif

                    for(int i=0; i < skip; i++){
                        cap >> frame;
                    }

                }
                float hough_total = evaluator.evaluate()*100;
                cout << "\though_total: " << hough_total << "%";
                if(hough_total > best.hough_total){
                    best.hough_total = hough_total;
                    best.hough_param1 = hough_param1;
                    best.hough_param2 = hough_param2;
                    cout << "\tBEST SO FAR!" << endl;
                }else{
                    cout << endl;
                }
            }
        }
        cout << "///////////////////////////////////////////////////////////////" << 
        endl << "BEST SET IS: \though_param1: " << best.hough_param1 <<
        "\though_param2: " << best.hough_param2 <<
        "\though_total: " << best.hough_total <<
        endl << "///////////////////////////////////////////////////////////////" << endl;
    }



    
    

    cap.release();

    // Closes all the frames
    destroyAllWindows();

    return 0;

}
