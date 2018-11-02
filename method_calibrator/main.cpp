#include "../classes/pixelCountCheck.hpp"
#include "../classes/quaternaryMask.h"
#include "../classes/houghCirclesContrast.h"
#include "../classes/evaluator.hpp"

//#define DEBUG 1 //usar junto com debug da evaluator.cpp

#define BLACK_L_MAX 50
#define WHITE_L_MIN 200
#define GREEN_H_MEAN 60
#define GREEN_H_VAR 30
#define GREEN_S_MIN 10

#define RESIZE_FACTOR 0.25

struct param_set{
    float hough_param1, hough_param2, hough_total;

    float pixel_param1, pixel_param2, pixel_total;
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

    cv::Mat frame;
    std::vector<cv::Vec3f> circles;

    quaternaryMask Mask;
    Mask.setMask(BLACK_L_MAX, WHITE_L_MIN, GREEN_H_MEAN, GREEN_H_VAR, GREEN_S_MIN, resize_factor);

    std::string linefps;
    std::ifstream myfile(argv[2]);
    std::getline(myfile, linefps);
    //int fps_new = stoi(linefps, 0, 10);
    int fps_new;
    std::istringstream(linefps) >> fps_new;
    int fps = cap.get(CV_CAP_PROP_FPS);
    int skip = (fps/fps_new) - 1;
    myfile.close();

    param_set best = {0};

    ////////////////////////////////////////////////////////////
    //////////////////// CALIBRA HOUGH CIRCLES /////////////////
    ////////////////////////////////////////////////////////////
    // só roda se parametro for passado na execução
    if(std::atoi(argv[3])){
        for(float hough_param1 = 24; hough_param1 < 26; hough_param1=hough_param1+2){
            for(float hough_param2 = 4; hough_param2 < 6; hough_param2=hough_param2+2){
                cap.set(CV_CAP_PROP_POS_FRAMES, 0);
                houghCirclesContrast hough(hough_param1, hough_param2, resize_factor);
                evaluator evaluator(argv[2], 0.04, 10);
                std::cout << "hough_param1: " << hough_param1 << "\though_param2: " << hough_param2;
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

                    cv::Point center(-1, -1);
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
        for(float pixel_param1 = 0.00; pixel_param1 < 0.55; pixel_param1=pixel_param1+0.05){
            for(float pixel_param2 = 0.00; pixel_param2 < 0.35; pixel_param2=pixel_param2+0.05){
                cap.set(CV_CAP_PROP_POS_FRAMES, 0);
                houghCirclesContrast hough(best.hough_param1, best.hough_param2, resize_factor);
                //inicia pixelCountCheck com porcentagem mínima de branco e preto na area da bola
                //pixel_param1 = branco      pixel_param2 => preto
                pixelCountCheck pixelChecker(pixel_param1, pixel_param2, resize_factor);
                evaluator evaluator(argv[2], 0.04, 10);
                std::cout << "pixel_param1: " << pixel_param1 << "\tpixel_param2: " << pixel_param2 << std::endl;
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
                                //primeiro que aceita o threshold ->break
                                break;
                            }
                        }
                    }
                    //metodo da livia retorna int
                    int gotItRight = evaluator.add(center, frame);
                    
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
