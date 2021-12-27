#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include "colotracker.h"
#include "region.h"
#include <string>
#include <limits>

#include "vot.hpp"

using namespace cv;

int main(int, char **) 
{
    ColorTracker tracker;
    cv::Mat image;

    //load region, images and prepare for output
    VOT vot_io("region.txt", "images.txt", "output.txt");
    
    //img = firts frame, initPos = initial position in the first frame
    cv::Rect init_rect = vot_io.getInitRectangle();
    vot_io.outputBoundingBox(init_rect);
    vot_io.getNextImage(image);

    //tracker initialization
    tracker.init(image, init_rect);

    //track   
    double average_speed_ms = 0.0;
    double num_frames = 0.0;
    while (vot_io.getNextImage(image) == 1){
        Rect2d bb;
        double time_profile_counter = cv::getCPUTickCount();

        bool success = tracker.update(image, bb);

        time_profile_counter = cv::getCPUTickCount() - time_profile_counter;
        average_speed_ms += time_profile_counter/((double)cvGetTickFrequency()*1000);
        num_frames += 1.0;

        if (success){
            vot_io.outputBoundingBox(cv::Rect(bb.x, bb.y, bb.width, bb.height));
        } else {
            vot_io.outputBoundingBox(cv::Rect(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN()));
        }
    }

    std::cout << "Average speed " <<  average_speed_ms/num_frames << "ms. (" << 1000.0/(average_speed_ms/num_frames) << "fps)" << std::endl;

    return 0;
}
