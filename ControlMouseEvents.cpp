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
   int posX = momentpositiontwo/area;
   int posY = momentpositionone/area;
   int x1,y1;
   cout<<posX<<" "<<posY<<endl;
   GetCursorPos(&p);

   //change position according to matrix
   if(posX>=60&&posX<120&&posY>=170&&posY<230)
   {
       x1 = p.x-3;
       y1 = p.y-3;
       SetCursorPos(x1,y1);
       cout<<"top left\n";
   }
   else if(posX>=120&&posX<190&&posY>=170&&posY<230)
   {
       x1 = p.x;
       y1 = p.y-3;
       SetCursorPos(x1,y1);
       cout<<"top middle\n";
   }
   else if(posX>=190&&posX<270&&posY>=170&&posY<230)
   {
       x1 = p.x+3;
       y1 = p.y-3;
       SetCursorPos(x1,y1);
       cout<<"top right\n";
   }
   else if(posX>=20&&posX<100&&posY>=220&&posY<260)
   {
       x1 = p.x-3;
       y1 = p.y;
       SetCursorPos(x1,y1);
       cout<<"middle left\n";
   }
   else if(posX>=180&&posX<270&&posY>=220&&posY<270)
   {
       x1 = p.x+3;
       y1 = p.y;
       SetCursorPos(x1,y1);
       cout<<"middle right\n";
   }
   else if(posX>=20&&posX<90&&posY>=266&&posY<310)
   {
       x1 = p.x-3;
       y1 = p.y+3;
       SetCursorPos(x1,y1);
       cout<<"bottom left\n";
   }
   else if(posX>=90&&posX<170&posY>=266&&posY<310)
   {
       x1 = p.x;
       y1 = p.y+3;
       SetCursorPos(x1,y1);
       cout<<"bottom middle\n";
   }
   else if(posX>=170&&posX<240&&posY>=266&&posY<310)
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
