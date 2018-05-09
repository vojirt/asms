#ifndef COLOTRACKER_H
#define COLOTRACKER_H

#include "cv.h"
#include "opencv2/core/persistence.hpp"
#include "opencv2/tracking/tracker.hpp"
#include "highgui.h"
#include "region.h"
#include "histogram.h"
#include <iostream>


//#define SHOWDEBUGWIN

#define BIN_1 16
#define BIN_2 16
#define BIN_3 16

class ColorTrackerModel: public cv::TrackerModel {
  void modelEstimationImpl(const std::vector<cv::Mat>&) { }
  void modelUpdateImpl() { }
};



class ColorTracker : public cv::Tracker
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

    double wAvgBg;
    double bound1;
    double bound2;

    cv::Point histMeanShift(double x1, double y1, double x2, double y2);
    cv::Point histMeanShiftIsotropicScale(double x1, double y1, double x2, double y2, double * scale, int * msIter = NULL);
    cv::Point histMeanShiftAnisotropicScale(double x1, double y1, double x2, double y2, double * width, double * height);

    void preprocessImage(const cv::Mat & img);
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

  // Abstract methods for param IO in cv::Tracker
    void read(const cv::FileNode&) {}
    void write(cv::FileStorage&) const {}


	// Init methods
    bool initImpl(const cv::Mat & img, const cv::Rect2d & output);

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
    bool updateImpl(const cv::Mat & img, cv::Rect2d & output);
};

#endif // COLOTRACKER_H
