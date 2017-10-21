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

void controlLeftClickFeature()
{
    POINT dir;
    GetCursorPos(&dir);
    mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP,dir.x,dir.y,0,0);
}

void controlRightClickFeature()
{
    POINT dir;
    GetCursorPos(&dir);
    mouse_event(MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_RIGHTUP,dir.x,dir.y,0,0);
}

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
   if(posX>=90&&posX<150&&posY>=160&&posY<220)
   {
       x1 = p.x-3;
       y1 = p.y-3;
       SetCursorPos(x1,y1);
   }
   else if(posX>=150&&posX<190&&posY>=160&&posY<220)
   {
       x1 = p.x;
       y1 = p.y-3;
       SetCursorPos(x1,y1);
   }
   else if(posX>=220&&posX<270&&posY>=160&&posY<220)
   {
       x1 = p.x+3;
       y1 = p.y-3;
       SetCursorPos(x1,y1);
   }
   else if(posX>=70&&posX<150&&posY>=220&&posY<270)
   {
       x1 = p.x-3;
       y1 = p.y;
       SetCursorPos(x1,y1);
   }
   else if(posX>=210&&posX<280&&posY>=220&&posY<270)
   {
       x1 = p.x+3;
       y1 = p.y;
       SetCursorPos(x1,y1);
   }
   else if(posX>=40&&posX<100&&posY>=270&&posY<302)
   {
       x1 = p.x-3;
       y1 = p.y+3;
       SetCursorPos(x1,y1);
   }
   else if(posX>=100&&posX<170&&posY>=270&&posY<302)
   {
       x1 = p.x;
       y1 = p.y+3;
       SetCursorPos(x1,y1);
   }
   else if(posX>=220&&posX<280&&posY>=270&&posY<302)
   {
       x1 = p.x+3;
       y1 = p.y+3;
       SetCursorPos(x1,y1);
   }
   else
   {
      cout<<"Nothing happen\n";
   }
}
