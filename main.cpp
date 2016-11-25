#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include<fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <string>
#include <strstream>

using namespace std;
using namespace cv;

std::string fpsString("FPS:");
char strings[10];
int fps_num = 0;

Mat frame_gray;

std::vector<Rect> faces;

 struct timeval tv;
void save_picture( Mat& face_farme, int x, int y, int width, int height );

/** FPS show */
static struct itimerval oldtv;
void set_timer()
{
    struct itimerval itv;
    itv.it_interval.tv_sec = 1;  //start time 1S
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 1;  //    each interrupt time  is 1S
    itv.it_value.tv_usec = 0;
    setitimer (ITIMER_REAL, &itv, &oldtv);
}

void mysignal_handler(int)
{
    fpsString = "FPS:";
    sprintf(strings, "%d", fps_num);
    fpsString += strings;
    fps_num = 0;  //  complete the statistics of frames per second, fps_num reset to 0

}
/** Function Headers */
void detectAndDisplay( Mat& frame );

/** Global variables */
String face_cascade_name = "lbpcascade_frontalface.xml";
CascadeClassifier face_cascade;
String window_name = "fram_Down";
String window_name1 = "fram";

/** @function main */
int main( void )
{
    VideoCapture capture;
    Mat frame;

    signal(SIGALRM, mysignal_handler);
    set_timer ();
    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return -1; };

    //-- 2. Read the video stream
    capture.open( -1 );
    if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n"); return -1; }
    capture.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    capture.set (CV_CAP_PROP_FRAME_HEIGHT, 240);
    while ( capture.read(frame) )
    {
        if( frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }

        //-- 3. Apply the classifier to the frame
        double time0 = static_cast<double>(getTickCount ());
        detectAndDisplay( frame );
        time0 = ((double)getTickCount () - time0) /getTickFrequency ();
        cout << "time=" <<time0 <<endl;
        int c = waitKey(5);
        if( (char)c == 27 ) { break; } // escape
    }


    return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay( Mat& frame )
{
    pthread_t thread1;

         //   pyrDown (frame, frame_gray);
        //    cvtColor( frame_gray, frame_gray, COLOR_BGR2GRAY );
        //    equalizeHist( frame_gray, frame_gray );

            //-- Detect faces
            face_cascade.detectMultiScale( frame, faces, 1.2, 2, 0|CASCADE_SCALE_IMAGE, Size(20,20) );

    std::cout << "faces num=" << faces.size ()<< "        ";

    for ( size_t i = 0; i < faces.size(); i++ )
    {

        save_picture(frame, faces[i].x, faces[i].y, faces[i].width, faces[i].height);

        Point center( faces[i].x  + (faces[i].width/2) , faces[i].y + (faces[i].height/2)  );
        ellipse( frame, center, Size( (faces[i].width/2), (faces[i].height/2)  ), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
    }

    //-- Show what you got

    putText (frame, fpsString, cv::Point(5, 20), cv::FONT_HERSHEY_DUPLEX, 0.8, cv::Scalar(231, 28, 55));  // write fps in frame
    imshow( window_name, frame );
    fps_num++; //  processed a frame, fps_num plus one
   //
}


void save_picture( Mat& face_farme, int x, int y, int width, int height )
{
    Mat test_frame ;



    gettimeofday (&tv, NULL);
    face_farme.copyTo(test_frame);
    std::strstream ss;
    string s;
    ss <<  (tv.tv_sec * 1000 + tv.tv_usec / 1000);
    ss >> s;
    s = "./testImages/" + s + ".jpg";
    imwrite(s, test_frame(Rect(x, y, width, height)));
}
