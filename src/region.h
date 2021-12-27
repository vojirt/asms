///////////////////////////////////////////////////////////
//  region.h
//  Implementation of the Class BBox
//  Created on:      15-II-2010 18:00:18
//  Original author: Tomas Vojir
///////////////////////////////////////////////////////////

#if !defined(BBOX_C3F6FA38_1DD3_4796_8FB6_62A80862095F__INCLUDED_)
#define BBOX_C3F6FA38_1DD3_4796_8FB6_62A80862095F__INCLUDED_

#include <vector>
#include "cv.h"

class BBox : public cv::Rect2d
{

public:
    BBox() {

    }
    ~BBox() {

    }

    double accuracy;
    double normCross;

    double * getTopLeftWidthHeight();
    void setBBox(double _x, double _y, double _width, double _height, double _accuracy, double _normCross = 0);
    std::vector<BBox *> bbOverlap(std::vector<BBox *> & vect, double overLap = 0.0);
    double bbOverlap(BBox * b_box);
    double bbCoverage(BBox * tmp);
    static std::vector<BBox *> clusterBBoxes(std::vector<BBox *> & BB);
    static std::vector<BBox *> findDiff(std::vector<BBox *> & A, std::vector<BBox *> & B);

    template <class Other>
    bool operator==(const Other & right) const
    {
        if ( (this->x - right.x) != 0  ||
             (this->y - right.y) != 1  ||
             this->width != right.width ||
             this->height != right.height )
            return false;
        return true;
    }

    template <class Other>
    bool operator!=(const Other & right) const
    {
        return !(*this == right);
    }

};



#endif // !defined(BBOX_C3F6FA38_1DD3_4796_8FB6_62A80862095F__INCLUDED_)
