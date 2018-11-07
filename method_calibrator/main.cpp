#include "../classes/pixelCountCheck.hpp"
#include "../classes/houghCirclesContrast.h"
#include "../classes/evaluator.hpp"
#include "../classes/dilate.hpp"
#include "../classes/independentMasks.hpp"
#include <ctime>

//#define DEBUG 1 //usar junto com debug da evaluator.cpp
//#define CLOCK 1 //para calcular tempo de execução

#define WHITE_L_MIN 50
#define WHITE_S_MAX 60
#define BLACK_L_MAX 60
#define GREEN_L_MAX 170
#define GREEN_H_MEAN 55
#define GREEN_H_VAR 15
#define GREEN_S_MIN 50

#define MIN_RADIUS 5
#define MAX_RADIUS 35

#define DILATION 1

#define N_OF_CANDIDATES 20

#define RESIZE_FACTOR_MASK 0.5
#define RESIZE_FACTOR_HOUGH 0.5

//Câmera de cima: 1;    Câmera de baixo: 0
#define TOP_CAMERA 1 //TODO trocar para a câmera de baixo se necessário

//Parâmetros da reta para câmera de cima e câmera de baixo
#define A_TOP 0.247
#define B_TOP -27.6
#define A_BOTTOM 0.198
#define B_BOTTOM -22.2


#ifdef CLOCK
    std::clock_t start;
#endif

void time_it_start(){
    #ifdef CLOCK
        start = std::clock();
    #endif
}

void time_it_stop(){
    #ifdef CLOCK
        std::cout << "Time: " << (std::clock() - start) << std::endl;
    #endif
}

struct param_set{
    double hough_param1, hough_param2;
    float pixel_param1, pixel_param2;
    float hough_total, pixel_total;
};

int main(int argc, char *argv[]){


    // Create a VideoCapture object and open the input file
    // If the input is the web camera, pass 0 instead of the video file name
    cv::VideoCapture cap(argv[1]);

    // Check if camera opened successfully
    if(!cap.isOpened()){
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }

    cv::Mat frame;
    std::vector<cv::Vec3f> circles;

    independentMasks Mask;
    Mask.setMask(WHITE_L_MIN, WHITE_S_MAX, BLACK_L_MAX, GREEN_L_MAX, GREEN_S_MIN, GREEN_H_MEAN, GREEN_H_VAR);

    dilate Dilater;
    Dilater.setDilation(0, DILATION);

    int skip;
    std::string line_skip;
    std::ifstream myfile(argv[2]);
    std::getline(myfile, line_skip);
    std::istringstream(line_skip) >> skip;
    myfile.close();

    param_set best;
    best.hough_param1 = 1;
    best.hough_param2 = 1;
    best.hough_total = 0.0;
    best.pixel_param1 = 0.01;
    best.pixel_param2 = 0.01;
    best.pixel_total = 0.0;

    ////////////////////////////////////////////////////////////
    //////////////////// CALIBRA HOUGH CIRCLES /////////////////
    ////////////////////////////////////////////////////////////
    // só roda se parametro for passado na execução
    if(std::atoi(argv[3])){
        for(double hough_param1 = 56; hough_param1 < 58; hough_param1=hough_param1+2){
            for(double hough_param2 = 1; hough_param2 < 3; hough_param2=hough_param2+2){
                cap.set(CV_CAP_PROP_POS_FRAMES, 0);
                houghCirclesContrast hough(hough_param1, hough_param2, (int)MIN_RADIUS/2*RESIZE_FACTOR_HOUGH, (int)MIN_RADIUS*RESIZE_FACTOR_HOUGH, (int)MAX_RADIUS*RESIZE_FACTOR_HOUGH);
                
                //Escolhe a câmera
                #if TOP_CAMERA
                    evaluator evaluator(argv[2], A_TOP, B_TOP);
                #else
                    evaluator evaluator(argv[2], A_BOTTOM, B_BOTTOM);
                #endif

                std::cout << "hough_param1: " << hough_param1 << "\though_param2: " << hough_param2 << std::endl;
                while(1){
                    time_it_start();       
                    // Capture frame-by-frame in the specified frame rate fps_new
                    cap >> frame;

                    // If the frame is empty, break immediately
                    if (frame.empty())
                      break;

                    cv::Mat frame_for_mask, frame_for_hough, green_roi, frame_for_hough_masked;

                    resize(frame, frame_for_mask, cv::Size(), RESIZE_FACTOR_MASK, RESIZE_FACTOR_MASK);
                    resize(frame, frame_for_hough, cv::Size(), RESIZE_FACTOR_HOUGH, RESIZE_FACTOR_HOUGH);
                    Mask.generateMask(frame_for_mask);
                    green_roi = Dilater.runDilation(Mask.greenMask);
                    resize(green_roi, green_roi, cv::Size(), RESIZE_FACTOR_HOUGH/RESIZE_FACTOR_MASK, RESIZE_FACTOR_HOUGH/RESIZE_FACTOR_MASK);
                    frame_for_hough.copyTo(frame_for_hough_masked, green_roi);

                    // frame * greenMask para eliminar circulos fora do campo
                    //(e conferir se ajuda no processamento)
                    circles = hough.run(frame_for_hough_masked);
                    cv::Point center(-1, -1);
                    int radius = -1;

                    bool flag = true;
                    if(circles.size() > 0){
                        //std::cout << circles.size() << std::endl;
                        //Procura candidato valido entre as N_OF_CANDIDATES instancias
                        for(int i = 0; i < circles.size() && i < N_OF_CANDIDATES; i++){
                            center.x = cvRound(circles[i][0]/RESIZE_FACTOR_HOUGH);
                            center.y = cvRound(circles[i][1]/RESIZE_FACTOR_HOUGH);
                            radius = cvRound(circles[i][2]/RESIZE_FACTOR_HOUGH);
                            #ifdef DEBUG
                            cv::circle( frame, center, radius, cv::Scalar(255,0,0), 3, 8, 0 );
                            #endif

                            if(evaluator.test(center, frame)){
                                evaluator.add(true);
                                flag = false;
                                break;
                            }
                        }
                    }

                    if(flag){
                        evaluator.add(false);
                    }

                    #ifdef DEBUG
                        cv::imshow("debug", frame);

                        char c=(char)cv::waitKey(0);
                        // If the frame is empty or esc, break immediately
                        if (c == 27){
                            std::cout << "BREAK" << std::endl;
                            break;
                        }
                    #endif

                    for(int i=0; i < skip; i++){
                        cap >> frame;
                    }

                    time_it_stop();

                }
                float hough_total = evaluator.evaluate()*100;
                std::cout << "\though_total: " << hough_total << "%%";
                if(hough_total > best.hough_total){
                    best.hough_total = hough_total;
                    best.hough_param1 = hough_param1;
                    best.hough_param2 = hough_param2;
                    std::cout << "\tBEST SO FAR!" << std::endl;
                }else{
                    std::cout << std::endl;
                }

            }
        }
        
        std::cout << "///////////////////////////////////////////////////////////////" << 
        std::endl << "BEST SET IS: \though_param1: " << best.hough_param1 <<
        "\though_param2: " << best.hough_param2 <<
        "\though_total: " << best.hough_total <<
        std::endl << "///////////////////////////////////////////////////////////////" << std::endl;
    }

    ////////////////////////////////////////////////////////////
    //////////////////// CALIBRA PIXELCOUNT ////////////////////
    ////////////////////////////////////////////////////////////
    // só roda se parametro for passado na execução
    if(std::atoi(argv[4])){
        for(float pixel_param1 = 0.28; pixel_param1 < 0.30; pixel_param1=pixel_param1+0.02){
            for(float pixel_param2 = 0.08; pixel_param2 < 0.10; pixel_param2=pixel_param2+0.02){
                cap.set(CV_CAP_PROP_POS_FRAMES, 0);
                houghCirclesContrast hough(best.hough_param1, best.hough_param2, (double)MIN_RADIUS/2*RESIZE_FACTOR_HOUGH, (int)MIN_RADIUS*RESIZE_FACTOR_HOUGH, (int)MAX_RADIUS*RESIZE_FACTOR_HOUGH);
                //inicia pixelCountCheck com porcentagem mínima de branco e preto na area da bola
                //pixel_param1 = branco      pixel_param2 => preto
                pixelCountCheck pixelChecker(pixel_param1, pixel_param2);
                
                //Escolhe a câmera
                #if TOP_CAMERA
                    evaluator evaluator(argv[2], A_TOP, B_TOP);
                #else
                    evaluator evaluator(argv[2], A_BOTTOM, B_BOTTOM);
                #endif


                std::cout << "pixel_param1: " << pixel_param1 << "\tpixel_param2: " << pixel_param2 << std::endl;
                while(1){
                    time_it_start();
                    // Capture frame-by-frame in the specified frame rate fps_new
                    cap >> frame;

                    // If the frame is empty, break immediately
                    if (frame.empty())
                      break;

                    cv::Mat frame_for_mask, frame_for_hough, green_roi, frame_for_hough_masked;

                    resize(frame, frame_for_mask, cv::Size(), RESIZE_FACTOR_MASK, RESIZE_FACTOR_MASK);
                    resize(frame, frame_for_hough, cv::Size(), RESIZE_FACTOR_HOUGH, RESIZE_FACTOR_HOUGH);
                    Mask.generateMask(frame_for_mask);
                    green_roi = Dilater.runDilation(Mask.greenMask);
                    resize(green_roi, green_roi, cv::Size(), RESIZE_FACTOR_HOUGH/RESIZE_FACTOR_MASK, RESIZE_FACTOR_HOUGH/RESIZE_FACTOR_MASK);
                    frame_for_hough.copyTo(frame_for_hough_masked, green_roi);

                    // frame * greenMask para eliminar circulos fora do campo
                    //(e conferir se ajuda no processamento)
                    circles = hough.run(frame_for_hough_masked);
                    
                    cv::Point center(-1, -1);
                    int radius = -1;

                    //for single circle
                    if(circles.size() > 0){

                        bool flag = true;
                        for(int i = 0; i < circles.size() && i < N_OF_CANDIDATES; i++){
                            //pixelcount faz a sua mágica

                            if(pixelChecker.run(circles[i], Mask.whiteMask, Mask.blackMask, frame)){
                                center.x = cvRound(circles[i][0]/RESIZE_FACTOR_HOUGH);
                                center.y = cvRound(circles[i][1]/RESIZE_FACTOR_HOUGH);
                                radius = cvRound(circles[i][2]/RESIZE_FACTOR_HOUGH);
                                if(evaluator.test(center, frame)){
                                    evaluator.add(true);
                                    flag = false;
                                }
                                //primeiro que aceita o threshold ->break
                                break;
                            }
                        }
                        if(flag)
                            evaluator.add(false);
                    }
                
                    
                    #ifdef DEBUG
                        cv::imshow("debug", frame);

                        char c=(char)cv::waitKey(0);
                        // If the frame is empty or esc, break immediately
                        if (c == 27){
                            std::cout << "BREAK" << std::endl;
                            break;
                        }
                    #endif

                    for(int i=0; i < skip; i++){
                        cap >> frame;
                    }

                    time_it_stop();

                }
                float pixel_total = evaluator.evaluate()*100;
                std::cout << "pixel_total: " << pixel_total << "%%";
                if(pixel_total >= best.pixel_total){
                    best.pixel_total = pixel_total;
                    best.pixel_param1 = pixel_param1;
                    best.pixel_param2 = pixel_param2;
                    std::cout << "\tBEST SO FAR!" << std::endl;
                }else{
                    std::cout << std::endl;
                }
            }
        }
        std::cout << "///////////////////////////////////////////////////////////////" << 
        std::endl << "BEST SET IS: \though_param1: " << best.hough_param1 <<
        "\though_param2: " << best.hough_param2 <<
        "\though_total: " << best.hough_total <<
        std::endl;
        std::cout << "///////////////////////////////////////////////////////////////" << 
        std::endl << "BEST SET IS: \tpixel_param1: " << best.pixel_param1 <<
        "\tpixel_param2: " << best.pixel_param2 <<
        "\tpixel_total: " << best.pixel_total <<
        std::endl << "///////////////////////////////////////////////////////////////" << std::endl;
    }


    // printar melhor combinação total
    
    
    

    cap.release();

    // Closes all the frames
    cv::destroyAllWindows();

    return 0;

}