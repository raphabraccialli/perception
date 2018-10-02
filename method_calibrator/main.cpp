#include "quaternaryMask.h"
#include "houghCirclesContrast.h"

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


    //instanciar metodo da livia // le arquivo no construtor(arquivo, a, b)

    while(1){
        // Captures a frame and skip some
        int i=0;
        bool breaker=false;
        while(i<5){
            cap >> frame;
            if(frame.empty()){
                breaker=true;
                break;
            }
            i++;
        }
        if(breaker)
            break;

        //find best circle
        circles = hough.run(frame);
        Mask.generateMask(frame);

        for( size_t i = 0; i < circles.size(); i++ )
        {
            /*if(bool da livia){
                circle( frame, center, 3, Scalar(0,255, 0), -1, 8, 0 );    
            }else{
                circle( frame, center, 3, Scalar(0,0,255), -1, 8, 0 );
            }

            */
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            // circle outline
            circle( frame, center, radius, Scalar(0,0,255), 3, 8, 0 );
            //print radius
            cout << circles[i][2] << endl;
        }
        cout << "-" << endl;
    
        //passa ponto pro metodo da livia
        //retorna bool 
        imshow("frame", frame);



        char c=(char)waitKey(0);
        // If the frame is empty or esc, break immediately
        if (c == 27){
            cout << "BREAK" << endl;
            break;
        }

    }

    cap.release();

    // Closes all the frames
    destroyAllWindows();

    return 0;

}
