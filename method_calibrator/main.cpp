#include "quaternaryMask.h"
#include "houghCirclesContrast.h"
#include "bhuman_ish.h"

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
    Point p;
    houghCirclesContrast hough;

    quaternaryMask Mask;
    Mask.setMask(50, 200, 60, 30, 10);

    bhuman_ish Blob;
    vector<KeyPoint> keypoints;
    Mat blobMask;


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
        //p = hough.run(frame);
        Mask.generateMask(frame);
        keypoints = Blob.run(Mask.whiteMask);
        drawKeypoints( frame, keypoints, blobMask, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );
        
        //passa ponto pro metodo da livia
        //retorna bool 

        if(p.x != -1){
            Point center(p.x, p.y);
            // circle center
            /*if(bool da livia){
                circle( frame, center, 3, Scalar(0,255, 0), -1, 8, 0 );    
            }else{
                circle( frame, center, 3, Scalar(0,0,255), -1, 8, 0 );
            }

            */
            circle( frame, center, 3, Scalar(0,0,255), -1, 8, 0 );
        }
        imshow("frame", frame);
        imshow("keypoints", blobMask );


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
