#ifndef HANDLEFINGERTIP_H_INCLUDED
#define HANDLEFINGERTIP_H_INCLUDED

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

int getContour(IplImage *, IplImage *);

void setContourPoint(CvPoint);

CvPoint getContourPoint();

#endif // HANDLEFINGERTIP_H_INCLUDED
