#include "../classes/pixelCountCheck.hpp"
#include "../classes/quaternaryMask.h"
#include "../classes/houghCirclesContrast.h"
#include "../classes/evaluator.hpp"
#include "../classes/dilate.hpp"

#define DEBUG 1 //usar junto com debug da evaluator.cpp

#define BLACK_L_MAX 40
#define WHITE_L_MIN 200
#define GREEN_H_MEAN 50
#define GREEN_H_VAR 20
#define GREEN_S_MIN 40

#define MIN_RADIUS 10
#define MAX_RADIUS 30

#define DILATION 1

#define N_OF_CANDIDATES 10

#define RESIZE_FACTOR 0.5


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


    float resize_factor = RESIZE_FACTOR;

    cv::Mat frame, frame_resized;
    std::vector<cv::Vec3f> circles;

    quaternaryMask Mask;
    Mask.setMask(BLACK_L_MAX, WHITE_L_MIN, GREEN_H_MEAN, GREEN_H_VAR, GREEN_S_MIN);

    dilate Dilater;
    Dilater.setDilation(0, DILATION * resize_factor);


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
        for(double hough_param1 = 60; hough_param1 < 62; hough_param1=hough_param1+2){
            for(double hough_param2 = 1; hough_param2 < 3; hough_param2=hough_param2+2){
                cap.set(CV_CAP_PROP_POS_FRAMES, 0);
                houghCirclesContrast hough(hough_param1, hough_param2, 30, (int)MIN_RADIUS, (int)MAX_RADIUS);
                evaluator evaluator(argv[2], 0.04, 10);
                std::cout << "hough_param1: " << hough_param1 << "\though_param2: " << hough_param2 << std::endl;
                while(1){
                    // Capture frame-by-frame in the specified frame rate fps_new
                    cap >> frame;

                    // If the frame is empty, break immediately
                    if (frame.empty())
                      break;

                    resize(frame, frame_resized, cv::Size(), resize_factor, resize_factor);

                    cv::Mat frame_resized_masked;
                    Mask.generateMask(frame_resized);
                    cv::Mat greenROI = Dilater.runDilation(Mask.greenMask);
                    frame_resized.copyTo(frame_resized_masked, greenROI);

                    // frame * greenMask para eliminar circulos fora do campo
                    //(e conferir se ajuda no processamento)
                    circles = hough.run(frame_resized_masked);

                    cv::Point center(-1, -1);
                    int radius = -1;

                    bool flag = true;
                    if(circles.size() > 0){
                        //Procura candidato valido entre as N_OF_CANDIDATES instancias
                        for(int i = 0; i < circles.size() && i < N_OF_CANDIDATES; i++){
                            center.x = cvRound(circles[i][0]/resize_factor);
                            center.y = cvRound(circles[i][1]/resize_factor);
                            radius = cvRound(circles[i][2]/resize_factor);
                            #ifdef DEBUG
                            cv::Point center_plot(cvRound(circles[i][0]/resize_factor), cvRound(circles[i][1]/resize_factor));
                            cv::circle( frame, center_plot, cvRound(circles[i][2]/resize_factor), cv::Scalar(255,0,0), 3, 8, 0 );
                            #endif

                            if(evaluator.test(center, frame_resized)){
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

                }
                float hough_total = evaluator.evaluate()*100;
                std::cout << "\though_total: " << hough_total << "%";
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
        for(float pixel_param1 = 0.02; pixel_param1 < 0.30; pixel_param1=pixel_param1+0.02){
            for(float pixel_param2 = 0.02; pixel_param2 < 0.10; pixel_param2=pixel_param2+0.02){
                cap.set(CV_CAP_PROP_POS_FRAMES, 0);
                houghCirclesContrast hough(best.hough_param1, best.hough_param2, (double)MIN_RADIUS/2, (int)MIN_RADIUS, (int)MAX_RADIUS);
                //inicia pixelCountCheck com porcentagem mínima de branco e preto na area da bola
                //pixel_param1 = branco      pixel_param2 => preto
                pixelCountCheck pixelChecker(pixel_param1, pixel_param2);
                evaluator evaluator(argv[2], 0.04, 10);
                std::cout << "pixel_param1: " << pixel_param1 << "\tpixel_param2: " << pixel_param2 << std::endl;
                while(1){
                    // Capture frame-by-frame in the specified frame rate fps_new
                    cap >> frame;

                    // If the frame is empty, break immediately
                    if (frame.empty())
                      break;

                    resize(frame, frame_resized, cv::Size(), resize_factor, resize_factor);

                    cv::Mat frame_resized_masked;
                    Mask.generateMask(frame_resized);
                    cv::Mat greenROI = Dilater.runDilation(Mask.greenMask);
                    frame_resized.copyTo(frame_resized_masked, greenROI);

                    // frame * greenMask para eliminar circulos fora do campo
                    //(e conferir se ajuda no processamento)
                    circles = hough.run(frame_resized_masked);
                    cv::Point center(-1, -1);
                    int radius = -1;

                    //for single circle
                    if(circles.size() > 0){

                        bool flag = true;
                        for(int i = 0; i < circles.size() && i < N_OF_CANDIDATES; i++){
                            //pixelcount faz a sua mágica

                            if(pixelChecker.run(circles[i], Mask.whiteMask, Mask.blackMask, frame_resized)){
                                center.x = cvRound(circles[i][0]/resize_factor);
                                center.y = cvRound(circles[i][1]/resize_factor);
                                radius = cvRound(circles[i][2]/resize_factor);
                                if(evaluator.test(center, frame_resized)){
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

                }
                float pixel_total = evaluator.evaluate()*100;
                std::cout << "pixel_total: " << pixel_total << "%";
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
