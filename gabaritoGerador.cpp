//Hello World
#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdlib.h>
 
using namespace std;
using namespace cv;
 
int main(int argc, char *argv[]){ //*argv == argv[0], *(argv+1) == argv[1]
  int fps, fps_new, skip, fr_period; 

  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  VideoCapture cap(argv[1]); 

  //Get the video frame rate
  fps = cap.get(CV_CAP_PROP_FPS);
  fps_new = atoi(argv[2]);
  skip = (fps/fps_new) - 1;
  fr_period = 1000/fps_new;

  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }
     
  while(1){
 
    Mat frame;
    // Capture frame-by-frame in the specified frame rate fps_new
  	cap >> frame;

    // If the frame is empty, break immediately
    if (frame.empty())
      break;
 
    // Display the resulting frame
    imshow( "Frame", frame );
 
    // Press  ESC on keyboard to exit
    //Wait 1000/fps_new ms 
    char c=(char)waitKey(fr_period);
    if(c==27)
      break;

	for(int i=0; i < skip; i++)
		cap >> frame;
  }
  
  // When everything done, release the video capture object
  cap.release();
 
  // Closes all the frames
  destroyAllWindows();
     
  return 0;
}