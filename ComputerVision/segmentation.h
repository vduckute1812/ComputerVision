#ifndef SEGMENTATION_H
#define SEGMENTATION_H


#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/highgui.hpp"
#include <ostream>
#include <iostream>

using namespace cv;

typedef struct{
    float x;
    float y;
} pointValue;

std::string floatToString(float );

void transformBGR2GR(const Mat& img, Mat& dst);
pointValue getWhPointColorTria(const Mat &img);
float calcDistance(pointValue whP, float r, float g);
float getDegree(float, float);
bool inThreshold(float s_min, float s_max, float j_t, float w, float s, float j);
void maskBinary(const Mat& img, Mat& dst, float s_min, float s_max, float j_t, float w);

#endif // SEGMENTATION_H
