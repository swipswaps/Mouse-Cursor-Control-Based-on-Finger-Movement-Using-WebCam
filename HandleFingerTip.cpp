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

CvPoint mainptr;

void setContourPoint(CvPoint p)
{
    mainptr = p;
}

CvPoint getContourPoint()
{
   return mainptr;
}

int getContour(IplImage *src, IplImage *threshold_image)
{
    CvMemStorage * storage = cvCreateMemStorage();
    CvSeq *contour = NULL;
    CvSeq *maxItem = NULL;
    double area,maxArea=0.0;
    CvSeq *ptr = NULL;
    int counting;
    int contour_Value = cvFindContours(threshold_image,storage,&contour,sizeof(CvContour),CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE,cvPoint(0,0));

    if(contour_Value>0)
    {
        for(ptr=contour;ptr!=NULL;ptr=ptr->h_next)
        {
            area = fabs(cvContourArea(ptr,CV_WHOLE_SEQ,0));
            if(area>maxArea)
            {
                maxArea = area;
                maxItem = ptr;
            }
        }

        if(maxArea>1000)
        {
            CvPoint np;
            CvMemStorage *storage1 = cvCreateMemStorage();
            CvMemStorage *storage2 = cvCreateMemStorage(0);
            CvSeq *ptseq = cvCreateSeq(CV_SEQ_KIND_GENERIC|CV_32SC2,sizeof(CvContour),sizeof(CvPoint),storage1);
            CvSeq *hull = NULL;
            CvSeq *defects = NULL;
            for(int i=0;i<maxItem->total;i++)
            {
                CvPoint *p = CV_GET_SEQ_ELEM(CvPoint,maxItem,i);
                np.x = p->x;
                np.y = p->y;
                cvSeqPush(ptseq,&np);
            }
            hull = cvConvexHull2(ptseq,0,CV_CLOCKWISE,0);
            int hull_count = hull->total;
            defects = cvConvexityDefects(ptseq,hull,storage2);

            CvConvexityDefect *defectArray = NULL;
            for(int i=1;i<=hull_count;i++)
            {
                CvPoint pt = **CV_GET_SEQ_ELEM(CvPoint*,hull,i);
                cvLine(src,np,pt,CV_RGB(255,0,0),1,CV_AA,0);
                np = pt;
            }

            for(;defects;defects = defects->h_next)
            {
                int def_amount = defects->total;

                if(def_amount==0)
                    continue;

                defectArray = (CvConvexityDefect*)malloc(sizeof(CvConvexityDefect)*def_amount);

                cvCvtSeqToArray(defects,defectArray,CV_WHOLE_SEQ);

                counting = 0;
                for(int i=0;i<def_amount;i++)
                {
                    if(defectArray[i].depth>40)
                    {
                        counting = counting+1;
                        cvLine(src,*(defectArray[i].start),*(defectArray[i].depth_point),CV_RGB(255,255,0),1,CV_AA,0);
                        cvCircle(src,*(defectArray[i].depth_point),5,CV_RGB(0,0,255),2,8,0);
                        cvCircle(src,*(defectArray[i].start),5,CV_RGB(0,255,0),2,8,0);
                        setContourPoint(*(defectArray[i].start));
                        cvLine(src,*(defectArray[i].depth_point),*(defectArray[i].end),CV_RGB(0,255,255),1,CV_AA,0);
                        cvDrawContours(src,defects,CV_RGB(0,0,0),CV_RGB(255,0,0),-1,CV_FILLED,8);
                    }
                }
                free(defectArray);

            }

            cvReleaseMemStorage(&storage1);
            cvReleaseMemStorage(&storage2);
        }
    }

    return counting;
}
