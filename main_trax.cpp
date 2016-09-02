#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include "colotracker.h"
#include "region.h"
#include <string>
#include <limits>
#include <trax/opencv.hpp>
#include <memory>

using namespace cv;

int main(int, char **) 
{
    trax::Image img;
    trax::Region reg;

    std::unique_ptr<ColorTracker> tracker;
    cv::Mat image;
	cv::Rect rectangle;

    trax::Server handle(trax::Configuration(TRAX_IMAGE_PATH | TRAX_IMAGE_MEMORY | TRAX_IMAGE_BUFFER, TRAX_REGION_RECTANGLE), trax_no_log);

    while(true) {

        trax::Properties prop;
        trax::Region status;

        int tr = handle.wait(img, reg, prop);

        if (tr == TRAX_INITIALIZE) {
            rectangle = trax::region_to_rect(reg);
            image = trax::image_to_mat(img);

            tracker.reset(new ColorTracker());

			tracker->init(image, rectangle.x, rectangle.y, rectangle.x + rectangle.width, rectangle.y + rectangle.height);

            status = trax::rect_to_region(rectangle);

        } else if (tr == TRAX_FRAME) {

            image = trax::image_to_mat(img);
			BBox* bb = tracker->track(image);

            if (bb != NULL) {
			    rectangle = cv::Rect(bb->x, bb->y, bb->width, bb->height);
                status = trax::rect_to_region(rectangle);
                delete bb;
            } else {
                status = trax::Region::create_special(0);
            }

        } else {
            break;
        }

        handle.reply(status, trax::Properties());

    }

    return EXIT_SUCCESS;

}
