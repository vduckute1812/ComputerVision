#ifndef HUMOMENT_H
#define HUMOMENT_H
#include <opencv2/core/core.hpp>

struct{

    // spatial moments
    double m[4][4];
    // central moments
    double mu[4][4];
    // central normalized moments
    double nu[4][4];
    // centroid of the image
    double x_cen;
    double y_cen;
    // seven moment invariants Hu
    double Hu[7];
} typedef HuMomentStruct;




double mo_ment(const cv::Mat& img,int p, int q);
double momentAtPoint(const cv::Mat& img,int p, int q);
void centralMoment(const cv::Mat& img, double x_cen, double y_cen, double mu[][4]);
double normalizedCentralMoments(double mu, double mu00, int p, int q);
void calculateMoment(const cv::Mat& img, double m[][4]);
void centroidImage(double& cent_x, double& cent_y, double m[][4]);
void HuMoment(double Hu[], double nu[][4]);
void calculateHuMoment(const cv::Mat img, HuMomentStruct& Hu_Value);
void normalizedCentralMoments(double nu[][4], double mu[][4], double m[][4]);
void normalizedLogarit(double Hu[]);

#endif // HUMOMENT_H
