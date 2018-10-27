#include "pixelCountCheck.hpp"
#include "quaternaryMask.h"
#include "houghCirclesContrast.h"
#include "evaluator.hpp"

//#define DEBUG 1 //usar junto com debug da evaluator.cpp

struct param_set{
    float hough_param1, hough_param2, hough_total;

    float pixel_param1, pixel_param2, pixel_total;
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


    float resize_factor = 0.25;

    Mat frame;
    vector<Vec3f> circles;

    quaternaryMask Mask;
    Mask.setMask(50, 200, 60, 30, 10, resize_factor);

    string linefps;
    ifstream myfile(argv[2]);
    getline(myfile, linefps);
    //int fps_new = stoi(linefps, 0, 10);
    int fps_new;
    istringstream(linefps) >> fps_new;
    int fps = cap.get(CV_CAP_PROP_FPS);
    int skip = (fps/fps_new) - 1;
    myfile.close();

    param_set best = {0}; //conferir isso aqui

    ////////////////////////////////////////////////////////////
    //////////////////// CALIBRA HOUGH CIRCLES /////////////////
    ////////////////////////////////////////////////////////////
    // só roda se parametro for passado na execução
    if(atoi(argv[3])){
        for(float hough_param1 = 60; hough_param1 < 80; hough_param1=hough_param1+2){
            for(float hough_param2 = 10; hough_param2 < 30; hough_param2=hough_param2+2){
                cap.set(CV_CAP_PROP_POS_FRAMES, 0);
                houghCirclesContrast hough(hough_param1, hough_param2, resize_factor);
                evaluator evaluator(argv[2], 0.04, 10);
                cout << "hough_param1: " << hough_param1 << "\though_param2: " << hough_param2;
                while(1){
                    // Capture frame-by-frame in the specified frame rate fps_new
                    cap >> frame;

                    // If the frame is empty, break immediately
                    if (frame.empty())
                      break;

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
    // só roda se parametro for passado na execução
    if(atoi(argv[4])){
        for(float pixel_param1 = 0.01; pixel_param1 < 0.30; pixel_param1=pixel_param1+0.02){
            for(float pixel_param2 = 0.00; pixel_param2 < 0.10; pixel_param2=pixel_param2+0.02){
                cap.set(CV_CAP_PROP_POS_FRAMES, 0);
                houghCirclesContrast hough(best.hough_param1, best.hough_param2, resize_factor);
                //inicia pixelCountCheck com porcentagem mínima de branco e preto na area da bola
                //pixel_param1 = branco      pixel_param2 => preto
                pixelCountCheck pixelChecker(pixel_param1, pixel_param2, resize_factor);
                evaluator evaluator(argv[2], 0.04, 10);
                cout << "pixel_param1: " << pixel_param1 << "\tpixel_param2: " << pixel_param2 << endl;
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

                    Point center(-1, -1);
                    int radius = -1;

                    //for single circle
                    if(circles.size() > 0){
                        for(int i = 0; i < circles.size() && i < 10; i++){
                            //pixelcount faz a sua mágica
                            if(pixelChecker.run(circles[i], Mask.whiteMask, Mask.blackMask, frame)){
                                center.x = cvRound(circles[i][0]);
                                center.y = cvRound(circles[i][1]);
                                //primeiro que aceita o threshold ->break
                                break;
                            }
                        }
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
                float pixel_total = evaluator.evaluate()*100;
                cout << "pixel_total: " << pixel_total << "%";
                if(pixel_total > best.pixel_total){
                    best.pixel_total = pixel_total;
                    best.pixel_param1 = pixel_param1;
                    best.pixel_param2 = pixel_param2;
                    cout << "\tBEST SO FAR!" << endl;
                }else{
                    cout << endl;
                }
            }
        }
        cout << "///////////////////////////////////////////////////////////////" << 
        endl << "BEST SET IS: \tpixel_param1: " << best.pixel_param1 <<
        "\tpixel_param2: " << best.pixel_param2 <<
        "\tpixel_total: " << best.pixel_total <<
        endl << "///////////////////////////////////////////////////////////////" << endl;
    }


    // printar melhor combinação total
    
    
    

    cap.release();

    // Closes all the frames
    destroyAllWindows();

    return 0;

}
