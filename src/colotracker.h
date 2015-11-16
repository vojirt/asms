#ifndef COLOTRACKER_H
#define COLOTRACKER_H

#include "cv.h"
#include "highgui.h"
#include "region.h"
#include "histogram.h"
#include <iostream>


//#define SHOWDEBUGWIN

#define BIN_1 16
#define BIN_2 16
#define BIN_3 16

class ColorTracker
{
private:
    BBox lastPosition;
    cv::Mat im1;
    cv::Mat im2;
    cv::Mat im3;

    cv::Mat im1_old;
    cv::Mat im2_old;
    cv::Mat im3_old;

    Histogram q_hist;
    Histogram q_orig_hist;
    Histogram b_hist;

    double defaultWidth;
    double defaultHeight;

    cv::Point histMeanShift(double x1, double y1, double x2, double y2);
    cv::Point histMeanShiftIsotropicScale(double x1, double y1, double x2, double y2, double * scale, int * msIter = NULL);

    void preprocessImage(cv::Mat & img);
    void extractBackgroundHistogram(int x1, int y1, int x2, int y2, Histogram &hist);
    void extractForegroundHistogram(int x1, int y1, int x2, int y2, Histogram &hist);

    inline double kernelProfile_Epanechnikov(double x)
        { return (x <= 1) ? (2.0/3.14)*(1-x) : 0; }
        //{ return (x <= 1) ? (1-x) : 0; }
    inline double kernelProfile_EpanechnikovDeriv(double x)
        { return (x <= 1) ? (-2.0/3.14) : 0; }
        //{ return (x <= 1) ? -1 : 0; }
public:
    int frame;
    int sumIter;

	// Init methods
    void init(cv::Mat & img, int x1, int y1, int x2, int y2);

    // Set last object position - starting position for next tracking step
    inline void setLastBBox(int x1, int y1, int x2, int y2)
	{
        lastPosition.setBBox(x1, y1, x2-x1, y2-y1, 1, 1);
    }

    inline BBox * getBBox()
    {
        BBox * bbox = new BBox();
        *bbox = lastPosition;
        return bbox;
    }

	// frame-to-frame object tracking
    BBox * track(cv::Mat & img, double x1, double y1, double x2, double y2);
    inline BBox * track(cv::Mat & img)
    {
        return track(img, lastPosition.x, lastPosition.y, lastPosition.x + lastPosition.width, lastPosition.y + lastPosition.height);
    }
};

#endif // COLOTRACKER_H
