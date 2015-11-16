///////////////////////////////////////////////////////////
//  region.cpp
//  Implementation of the Class BBox
//  Created on:      15-II-2010 18:00:19
//  Original author: Tomas Vojir
///////////////////////////////////////////////////////////

#include "region.h"
#include <algorithm>

void BBox::setBBox(double _x, double _y, double _width, double _height, double _accuracy, double _normCross){
	accuracy = _accuracy;
	height = _height;
	width = _width;
	x = _x;
	y = _y;
    normCross = _normCross;
}


double * BBox::getTopLeftWidthHeight()
{
    double * ret = new double[4];
    ret[0] = x;
    ret[1] = y;
    ret[2] = width;
    ret[3] = height;

    return ret;
}

std::vector<BBox *> BBox::bbOverlap(std::vector<BBox *> & vect, double overLap)
{
    std::vector<BBox *> ret;
    std::vector<BBox *> retP;
    double x1, y1;
    BBox * tmp;
    double intersection;
    double over = overLap;

    if (over == 0)
        over = 0.7;

    for(std::vector<BBox *>::iterator it = vect.begin(); it != vect.end(); ++it){
        tmp = *it;
        x1 =  std::min(x + width, tmp->x + tmp->width) - std::max(x, tmp->x) + 1;
        if (x1 <= 0)
        {
            ret.push_back(*it);
            continue;
        }

        y1 =  std::min(y + height, tmp->y + tmp->height) - std::max(y, tmp->y) + 1;

        if (y1 <= 0)
        {
            ret.push_back(*it);
            continue;
        }

        intersection = x1 * y1;

        if ( (intersection / (width * height + tmp->width * tmp->height - intersection)) >= over)
            retP.push_back(*it);
        else
            ret.push_back(*it);
    }
    vect = retP;

    return (ret);
}

double BBox::bbOverlap(BBox * tmp)
{
    double x1, y1;
    double intersection;

    x1 =  std::min(x + width, tmp->x + tmp->width) - std::max(x, tmp->x) + 1;
    if (x1 <= 0)
        return 0;
    y1 =  std::min(y + height, tmp->y + tmp->height) - std::max(y, tmp->y) + 1;

    if (y1 <= 0)
        return 0;

    intersection = x1 * y1;
	double area1 = (width+1)*(height+1);
	double area2 = (tmp->width+1)*(tmp->height+1);
    return (intersection / (area1 + area2 - intersection));
}

double BBox::bbCoverage(BBox * tmp)
{
    double x1, y1;
    double intersection;

    x1 =  std::min(x + width, tmp->x + tmp->width) - std::max(x, tmp->x) + 1;
    if (x1 <= 0)
        return 0;
    y1 =  std::min(y + height, tmp->y + tmp->height) - std::max(y, tmp->y) + 1;

    if (y1 <= 0)
        return 0;

    intersection = x1 * y1;

    return (intersection);

}

std::vector<BBox *> BBox::clusterBBoxes(std::vector<BBox *> & BB)
{
    std::vector<BBox *> ret;
    std::vector<BBox *> tmpV1;
    std::vector<BBox *> tmpV2;
    std::vector<BBox *> tmpV3;

    BBox * tmp;

    if (BB.size() == 0)
        return ret;

    while(1){
        tmp = BB[0];
        tmpV1 = tmp->bbOverlap(BB);
        tmpV3 = BB;

        for (std::vector<BBox *>::iterator it = BB.begin(); it != BB.end(); ++it){
            tmpV2 = (*it)->bbOverlap(tmpV1);
            for (unsigned int i=0; i<tmpV1.size(); ++i)
                tmpV3.push_back(tmpV1[i]);
            tmpV1.swap(tmpV2);
        }

        if (tmpV3.size() != 0){
            BBox * bbox = new BBox();
            bbox->setBBox(0,0,0,0,0);
            bbox->normCross = 0;
            for (std::vector<BBox *>::iterator it = tmpV3.begin(); it != tmpV3.end(); ++it){
                bbox->x += (*it)->x;
                bbox->y += (*it)->y;
                bbox->width += (*it)->width;
                bbox->height += (*it)->height;
                if ((*it)->normCross > bbox->normCross)
                    bbox->normCross = (*it)->normCross;
                if ((*it)->accuracy > bbox->accuracy)
                    bbox->accuracy = (*it)->accuracy;
                delete *it;
            }
            bbox->x /= tmpV3.size();
            bbox->y /= tmpV3.size();
            bbox->width /= tmpV3.size();
            bbox->height /= tmpV3.size();

            ret.push_back(bbox);
            tmpV3.clear();
            tmpV2.clear();
        }
        BB.swap(tmpV1);

        if (BB.size() == 0)
            break;
    }

    return ret;
}

std::vector<BBox *> BBox::findDiff(std::vector<BBox *> & A, std::vector<BBox *> & B)
{
    bool equal;
    std::vector<BBox *> ret;
    if (B.size()==0){
        ret = A;
        return (ret);
    }

    for(std::vector<BBox *>::iterator it = A.begin(); it != A.end(); ++it){
        equal = false;
        for (std::vector<BBox *>::iterator it2 = B.begin(); it2 != B.end(); ++it2)
            if (*it == *it2) {
                equal = true;
                break;
            }

        if (!equal)
            ret.push_back(*it);
    }

    return (ret);
}


