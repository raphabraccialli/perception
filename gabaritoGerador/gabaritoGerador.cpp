//Hello World
#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
 
using namespace std;
using namespace cv;

vector<int> posX, posY;
bool flag = false;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    if  ( event == EVENT_LBUTTONDOWN )
    {
        cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
        flag = true;
        posX.push_back(x);
        posY.push_back(y);
    }
    else if  ( event == EVENT_RBUTTONDOWN )
    {
        cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
        flag = true;
        posX.push_back(-1);
        posY.push_back(-1);
    }
    /*else if  ( event == EVENT_MBUTTONDOWN )
    {
        cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    }
    else if ( event == EVENT_MOUSEMOVE )
    {
        cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
    }*/    
}
 
int main(int argc, char *argv[]){ //*argv == argv[0], *(argv+1) == argv[1]
  int fps, fps_new, skip, fr_period;
  bool stop = false;

  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  VideoCapture cap(argv[1]); 

  //Get the video frame rate
  fps = cap.get(CV_CAP_PROP_FPS);
  fps_new = atoi(argv[2]);
  skip = (fps/fps_new) - 1;
  fr_period = 1000/fps_new;

  cout << "FPS: " << fps << endl;
  cout << "FPS_NEW: " << fps_new << endl;
  cout << "SKIP: " << skip << endl;

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

  	//Create a window
    namedWindow("Frame", 1);

    setMouseCallback("Frame", CallBackFunc, NULL);
 
    // Display the resulting frame
    imshow("Frame", frame );
 
    // Press  ESC on keyboard to exit
    //Wait 1000/fps_new ms 
    //char c=(char)waitKey(fr_period);
    //if(c==27)
    //  break;

  	while(!flag){
  		char c=(char)waitKey(50);
	    if(c==27){
	    	stop = true;
	    	break;
	    }
  	}
  	flag = false;

  	if(stop)
  		break;

	for(int i=0; i < skip; i++)
		cap >> frame;
  }

  	vector<int>::iterator itX, itY;  

	ofstream myfile(argv[3]);

	//Saves FPS
	myfile << fps_new << endl;


	if(myfile.is_open()){

		itX = posX.begin();
		itY = posY.begin();
		while(itX!=posX.end()){
			myfile << (*itX) << endl;
			myfile << (*itY) << endl;
			itX++;
			itY++;
		}

  		myfile.close();
	}
	else
		cout << "Not possible to open the file." << endl;

  // When everything done, release the video capture object
  cap.release();
 
  // Closes all the frames
  destroyAllWindows();
     
  return 0;
}