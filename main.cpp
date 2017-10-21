#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <bits/stdc++.h>
#include<opencv2/core/core.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include "InitializeParameters.h"
#include "HandleFingerTip.h"
#include "ControlMouseEvents.h"

using namespace std;
using namespace cv;

int main()
{
    // Get Instance of Camera
    VideoCapture capture = getCameraInstance();
    //Image frame
    Mat frame;
    //capture.open(0);
    capture>>frame;
    capture.read(frame);

    CvSize cv_size(capture.get(CV_CAP_PROP_FRAME_WIDTH),capture.get(CV_CAP_PROP_FRAME_HEIGHT));

    /*
    @ Assign Channels 24 pixel
    */
    Mat img = Mat::zeros(cv_size,CV_8UC3);
    Mat img_roi = Mat::zeros(cv_size,CV_8UC3);
    Mat channel = Mat::zeros(cv_size,CV_8UC3);
    Mat imgHSV = Mat::zeros(cvSize(300,310),CV_8UC3);
    IplImage* gray_image  = cvCreateImage(cvSize(305,305),8,1);
    IplImage *ref_img = cvCreateImage(cv_size,8,3);
    string finger = "";
    int counting = 0;
    while(true)
    {
        capture.read(frame);
        img = frame;
        ref_img->imageData = (char*)img.data;
        /*
        @ [crop the image]
        @ description [Detect the contour within the window]
        */
        //img = img(Rect(330,90,305,305));
	    //cvtColor(img,imgHSV,CV_BGR2HSV);
	    cvSetImageROI(ref_img, cvRect(330,90,305,305));
	    img = cvarrToMat(ref_img,false);
	    cvCvtColor(ref_img,gray_image,CV_BGR2GRAY);
        cvSmooth(gray_image,gray_image,CV_BLUR,(12,12),0);
        cvThreshold(gray_image,gray_image,0,255,CV_THRESH_BINARY_INV+CV_THRESH_OTSU);

        /*
        Take a storage vectors
        */
        {
            counting = getContour(ref_img,gray_image);
        }

        if(counting==1)
        {
            //Moving the Mouse
            controlMousePosition(gray_image);
            finger = "detecting One";
        }
        else if(counting==2)
        {
            //Left Click
            controlLeftClickFeature();
            finger = "detecting Two";
        }
        else if(counting==4)
        {
            //Right Click
            controlRightClickFeature();;
            finger = "detecting Four";
        }
        else
        {
            finger = "No Operation happen";
        }

        /*create a matrix channel*/
        createRectange(img);
        createLine(img);
        imshow("Crop Frame",img);
        cvResetImageROI(ref_img);
        img = cvarrToMat(ref_img,false);
        CvFont font;
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.5,1.5,0,5,CV_AA);
        cvPutText(ref_img,finger.c_str(),cvPoint(50, 50),&font,cvScalar(0,0,255,0));
        namedWindow("Original Frame",CV_WINDOW_AUTOSIZE);
        imshow("Original Frame",img);

        if(char(waitKey(1))=='q'&&capture.isOpened())
        {
           break;
        }
    }
    return 0;
}
