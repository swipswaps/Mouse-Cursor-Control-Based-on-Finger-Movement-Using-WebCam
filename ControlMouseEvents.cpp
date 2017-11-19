#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <bits/stdc++.h>
#include<opencv2/core/core.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include "windows.h"
#include "HandleFingerTip.h"

using namespace std;
using namespace cv;

/*
@ method controlLeftClickFeature
@ description [handle the left click]
@ return void
*/
void controlLeftClickFeature()
{
    POINT dir;
    GetCursorPos(&dir);
    mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP,dir.x,dir.y,0,0);
}
/*
@ method controlRightClickFeature
@ description [handle the right click]
@ return void
*/
void controlRightClickFeature()
{
    POINT dir;
    GetCursorPos(&dir);
    mouse_event(MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_RIGHTUP,dir.x,dir.y,0,0);
}

/*
@ method controlMousePosition
@ description [handle the cursor moments]
@ return void
*/
void controlMousePosition(IplImage *img)
{
   POINT p;
   CvMoments *moments = (CvMoments *)malloc(sizeof(CvMoments));
   cvMoments(img,moments,1);
   double momentpositiontwo = cvGetSpatialMoment(moments,1,0);
   double momentpositionone = cvGetSpatialMoment(moments,0,1);
   double area = cvGetCentralMoment(moments,0,0);
   int  X = momentpositiontwo/area;
   int  Y = momentpositionone/area;
   int x1,y1;
   cout<<X<<" "<<Y<<endl;
   GetCursorPos(&p);

   //change position according to matrix
   if(X>=60&&X<120&&Y>=170&&Y<230)
   {
       x1 = p.x-3;
       y1 = p.y-3;
       SetCursorPos(x1,y1);
       cout<<"top left\n";
   }
   else if(X>=120&&X<190&&Y>=170&&Y<230)
   {
       x1 = p.x;
       y1 = p.y-3;
       SetCursorPos(x1,y1);
       cout<<"top middle\n";
   }
   else if(X>=190&&X<270&&Y>=170&&Y<230)
   {
       x1 = p.x+3;
       y1 = p.y-3;
       SetCursorPos(x1,y1);
       cout<<"top right\n";
   }
   else if(X>=20&&X<100&&Y>=220&&Y<260)
   {
       x1 = p.x-3;
       y1 = p.y;
       SetCursorPos(x1,y1);
       cout<<"middle left\n";
   }
   else if(X>=180&&X<270&&Y>=220&&Y<270)
   {
       x1 = p.x+3;
       y1 = p.y;
       SetCursorPos(x1,y1);
       cout<<"middle right\n";
   }
   else if(X>=20&&X<90&&Y>=266&&Y<310)
   {
       x1 = p.x-3;
       y1 = p.y+3;
       SetCursorPos(x1,y1);
       cout<<"bottom left\n";
   }
   else if(X>=90&&X<170&&Y>=266&&Y<310)
   {
       x1 = p.x;
       y1 = p.y+3;
       SetCursorPos(x1,y1);
       cout<<"bottom middle\n";
   }
   else if(X>=170&&X<240&&Y>=266&&Y<310)
   {
       x1 = p.x+3;
       y1 = p.y+3;
       SetCursorPos(x1,y1);
       cout<<"bottom right\n";
   }
   else
   {
      cout<<"Nothing happen\n";
   }
}
