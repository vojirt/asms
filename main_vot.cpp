#include <iostream>
#include "cv.h"
#include "colotracker.h"
#include "region.h"
#include <string>

#include "cpp_vot_io.hpp"

using namespace cv;

int main(int, char **) 
{
    ColorTracker tracker;
    cv::Mat img;

    //load region, images and prepare for output
    CPP_VOT_IO vot_io("region.txt", "images.txt", "output.txt");
    
    //img = firts frame, initPos = initial position in the first frame
    cv::Rect initPos = vot_io.getInitRectangle();
    vot_io.outputBoundingBox(initPos);
    vot_io.getNextImage(img);

    //tracker initialization
    tracker.init(img, initPos.x, initPos.y, initPos.x + initPos.width, initPos.y + initPos.height);

    //track   
    while (vot_io.getNextImage(img) == 1){
        BBox * bb = tracker.track(img);
        if (bb != NULL){
            vot_io.outputBoundingBox(cv::Rect(bb->x, bb->y, bb->width, bb->height));
            delete bb;
        }
    }
    return 0;
}
