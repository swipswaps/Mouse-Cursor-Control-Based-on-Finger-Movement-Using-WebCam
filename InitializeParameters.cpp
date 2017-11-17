#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <bits/stdc++.h>
#include<opencv2/core/core.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

VideoCapture getCameraInstance()
{
    VideoCapture capture(0);
    return capture;
}

/*
@ method [createRectangle]
*/
void createRectange(Mat img)
{
    rectangle(img,Point(2,2),Point(302,302),CV_RGB(255,255,255),1,CV_AA,0);
}

/*
@ method [createLine]
*/
void createLine(Mat img)
{
    line(img, Point(102,0), Point(102,302),CV_RGB(0,255,0),1, CV_AA, 0 );
    line(img, Point(202,0), Point(202,302),CV_RGB(0,255,0),1, CV_AA, 0 );
    line(img, Point(0,102), Point(302,102),CV_RGB(255,255,0),1, CV_AA, 0 );
    line(img, Point(0,202), Point(302,202),CV_RGB(255,255,0),1, CV_AA, 0 );
}
