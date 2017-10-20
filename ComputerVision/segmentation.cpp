#include "segmentation.h"
#define PI_ 3.141592654

string floatToString(float x){
    std::ostringstream ss;
    ss << x;
    return ss.str();
}


void transformBGR2GR(const Mat& img, Mat& dst){
    Mat tmp = Mat::zeros(img.size(),CV_32FC2);

    for(int i=0; i<img.rows;++i)
        for(int j=0;j<img.cols;++j)
            {
            if(img.at<Vec3b>(i,j)[0]+img.at<Vec3b>(i,j)[1]+img.at<Vec3b>(i,j)[2]==0){
                tmp.at<Vec2f>(i,j)[0]=1.0/3;
                tmp.at<Vec2f>(i,j)[1]=1.0/3;
                continue;
            }
                tmp.at<Vec2f>(i,j)[0] = (float)img.at<Vec3b>(i,j)[1]/(img.at<Vec3b>(i,j)[0]+img.at<Vec3b>(i,j)[1]+img.at<Vec3b>(i,j)[2]);
                tmp.at<Vec2f>(i,j)[1] = (float)img.at<Vec3b>(i,j)[2]/(img.at<Vec3b>(i,j)[0]+img.at<Vec3b>(i,j)[1]+img.at<Vec3b>(i,j)[2]);
            }
    tmp.copyTo(dst);
}

pointValue getWhPointColorTria(const Mat &img){
    float b=0;
    float r=0;
    float g=0;
    pointValue whPoint;
    int sizeImg = img.rows*img.cols;
    for(int i=0; i<img.rows;++i){
        for(int j=0;j<img.cols;++j){
            b+=(float)img.at<Vec3b>(i,j)[0]/sizeImg;
            g+=(float)img.at<Vec3b>(i,j)[1]/sizeImg;
            r+=(float)img.at<Vec3b>(i,j)[2]/sizeImg;
        }
    }
    r = r/(r+g+b);
    g = g/(r+g+b);

    whPoint.x = g;
    whPoint.y = r;
//    whPoint.x = 1./3;
//    whPoint.y = 1./3;

    return(whPoint);
}

float calcDistance(pointValue whP, float r, float g){
    return sqrt(pow((whP.x-r),2)+pow((whP.y-g),2));
}

float getDegree(float r_, float g_){
    float arg= atan2(r_, g_);
    arg=arg/PI_*180;
    if(arg<0)
        arg+=360;
    return arg;
}

bool inThreshold(float s_min, float s_max, float j_t, float w, float s, float j){
    return ((s>s_min) && (s<s_max) && (j>j_t-w/2) && (j<j_t+w/2));
}

void maskBinary(const Mat& img, Mat& dst, float s_min, float s_max, float j_t, float w){
    Mat rgColorSpace;
    pointValue whPoint;
    transformBGR2GR(img,rgColorSpace);
    whPoint = getWhPointColorTria(rgColorSpace);
    float arg = 0;
    float s=0;
    bool check = false;

    for(int i=0;i<img.rows;++i){
        for(int j=0;j<img.cols;++j){
            s= calcDistance(whPoint, rgColorSpace.at<Vec2f>(i,j)[1], rgColorSpace.at<Vec2f>(i,j)[0]);
            arg=getDegree(rgColorSpace.at<Vec2f>(i,j)[1]-whPoint.x,rgColorSpace.at<Vec2f>(i,j)[0]-whPoint.y);
            check = inThreshold(s_min, s_max, j_t, w, s, arg);
            if(check)
                dst.at<uchar>(i,j) = 255;
            else
                dst.at<uchar>(i,j) = 0;
        }
    }
}
