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

/*
@ method [getContour]
@ description [design the contour on Frame and return no of contour defect]
*/
int getContour(IplImage *src, IplImage *threshold_image)
{
    CvMemStorage * memstorage = cvCreateMemStorage();
    CvSeq *contour = NULL;
    CvSeq *maxItem = NULL;
    double area,maxArea=0.0;
    CvSeq *ptr = NULL;
    int counting;
    int contour_Value = cvFindContours(threshold_image,memstorage,&contour,sizeof(CvContour),CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE,cvPoint(0,0));

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
            CvMemStorage *bufferstorage = cvCreateMemStorage();
            CvMemStorage *defectstorage = cvCreateMemStorage(0);
            CvSeq *pt_seq = cvCreateSeq(CV_SEQ_KIND_GENERIC|CV_32SC2,sizeof(CvContour),sizeof(CvPoint),bufferstorage);
            CvSeq *hull_seq = NULL;
            CvSeq *defects_seq = NULL;
            for(int i=0;i<maxItem->total;i++)
            {
                CvPoint *p = CV_GET_SEQ_ELEM(CvPoint,maxItem,i);
                np.x = p->x;
                np.y = p->y;
                cvSeqPush(pt_seq,&np);
            }
            hull_seq = cvConvexHull2(pt_seq,0,CV_CLOCKWISE,0);
            int hull_count = hull_seq->total;
            defects_seq = cvConvexityDefects(pt_seq,hull_seq,defectstorage);

            CvConvexityDefect *defect_Array = NULL;
            for(int i=1;i<=hull_count;i++)
            {
                CvPoint pt = **CV_GET_SEQ_ELEM(CvPoint*,hull_seq,i);
                cvLine(src,np,pt,CV_RGB(255,0,0),1,CV_AA,0);
                np = pt;
            }

            for(;defects_seq;defects_seq = defects_seq->h_next)
            {
                int def_amount = defects_seq->total;

                if(def_amount==0)
                    continue;

                defect_Array = (CvConvexityDefect*)malloc(sizeof(CvConvexityDefect)*def_amount);

                cvCvtSeqToArray(defects_seq,defect_Array,CV_WHOLE_SEQ);

                counting = 0;
                for(int i=0;i<def_amount;i++)
                {
                    if(defect_Array[i].depth>40)
                    {
                        counting = counting+1;
                        cvLine(src,*(defect_Array[i].start),*(defect_Array[i].depth_point),CV_RGB(255,255,0),1,CV_AA,0);
                        cvCircle(src,*(defect_Array[i].depth_point),5,CV_RGB(0,0,255),2,8,0);
                        cvCircle(src,*(defect_Array[i].start),5,CV_RGB(0,255,0),2,8,0);
                        setContourPoint(*(defect_Array[i].start));
                        cvLine(src,*(defect_Array[i].depth_point),*(defect_Array[i].end),CV_RGB(0,255,255),1,CV_AA,0);
                        cvDrawContours(src,defects_seq,CV_RGB(0,0,0),CV_RGB(255,0,0),-1,CV_FILLED,8);
                    }
                }
                free(defect_Array);

            }

            cvReleaseMemStorage(&bufferstorage);
            cvReleaseMemStorage(&defectstorage);
        }
    }

    return counting;
}
