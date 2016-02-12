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
    double average_speed_ms = 0.0;
    double num_frames = 0.0;
    while (vot_io.getNextImage(img) == 1){
        double time_profile_counter = cv::getCPUTickCount();
        BBox * bb = tracker.track(img);
        time_profile_counter = cv::getCPUTickCount() - time_profile_counter;
        average_speed_ms += time_profile_counter/((double)cvGetTickFrequency()*1000);
        num_frames += 1.0;

        if (bb != NULL){
            vot_io.outputBoundingBox(cv::Rect(bb->x, bb->y, bb->width, bb->height));
            delete bb;
        }
    }
    std::cout << "Average speed " <<  average_speed_ms/num_frames << "ms. (" << 1000.0/(average_speed_ms/num_frames) << "fps)" << std::endl;

    return 0;
}
