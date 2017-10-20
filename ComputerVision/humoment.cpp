#include "humoment.h"


///*=======================Hu's moment=========================*/


double mo_ment(const cv::Mat& img,int p, int q){
    double m = 0;
    for (int x = 0; x < img.rows; x++)
        for (int y = 0; y < img.cols; y++){
            if (img.at<uchar>(x, y) == 255){
                 m += pow(x, p)*pow(y, q);
            }
        }
    return m;
}

double cent(const cv::Mat& img, double cenx, double ceny,int p, int q)
{
    double mu = 0;
    for (int x = 0; x < img.rows; x++)
        for (int y = 0; y < img.cols; y++){
            if (img.at<uchar>(x, y) == 255){
                mu += pow(x - cenx, p)*pow(y - ceny, q);
            }
        }
    return mu;
}

//normalized central moments
double norm_cent(double mu, double mu00, int p, int q)
{
    return mu / (pow(mu00, static_cast<float>(p + q)  / 2.0 + 1));
}

void centralMoment(const cv::Mat& img, double x_cen, double y_cen, double mu[][4]){
    for (int p = 0; p <= 3; ++p){
        for (int q = 0; q <= 3 && p + q < 4; ++q){
            if (p + q > 1)
                mu[p][q] = cent(img, x_cen, y_cen, p, q);
        }
    }
}

//Calculate moment
void calculateMoment(const cv::Mat &img, double m[][4]){
    for (int p = 0; p <= 3; ++p){
        for (int q = 0; q <= 3 && p + q < 4; ++q){
            m[p][q] = mo_ment(img, p, q);
        }
    }
}


void centroidImage(double& cent_x, double& cent_y, double m[][4]){
    cent_x = m[1][0] / m[0][0];
    cent_y = m[0][1] / m[0][0];
}


void HuMoment(double Hu[], double nu[][4]){
    //Based on normalized central moments
    Hu[0] = nu[2][0] + nu[0][2];
    Hu[1] = (nu[2][0] - nu[0][2])*(nu[2][0] - nu[0][2]) + 4 * nu[1][1] * nu[1][1];
    Hu[2] = (nu[3][0] - 3 * nu[1][2])*(nu[3][0] - 3 * nu[1][2]) + (nu[3][0] - 3 * nu[2][1])*(nu[3][0] - 3 * nu[2][1]);
    Hu[3] = (nu[3][0] + nu[1][2])*(nu[3][0] + nu[1][2]) + (nu[2][1] + nu[0][3])*(nu[2][1] + nu[0][3]);
    Hu[4] = (nu[3][0] - 3 * nu[1][2])*(nu[3][0] + nu[1][2])*((nu[3][0] + nu[1][2])*(nu[3][0] + nu[1][2]) - 3 * (nu[2][1] + nu[0][3])*(nu[2][1] + nu[0][3]))
        + (3 * nu[2][1] - nu[0][3])*(nu[2][1] + nu[0][3])*(3 * (nu[3][0] + nu[1][2])*(nu[3][0] + nu[1][2]) - (nu[2][1] + nu[0][3])*(nu[2][1] + nu[0][3]));
    Hu[5] = (nu[2][0] - nu[0][2])*((nu[3][0] + nu[1][2])*(nu[3][0] + nu[1][2]) - (nu[2][1] + nu[0][3])*(nu[2][1] + nu[0][3])
        + 4 * nu[1][1] * (nu[3][0] + nu[1][2])*(nu[2][1] + nu[0][3]));
    Hu[6] = (3 * nu[2][1] - nu[0][3])*(nu[3][0] + nu[1][2])*((nu[3][0] + nu[1][2])*(nu[3][0] + nu[1][2]) - 3 * (nu[2][1] + nu[0][3])* (nu[2][1] + nu[0][3]))
        - (nu[3][0] - 3 * nu[1][2])*(nu[2][1] + nu[0][2])*(3 * (nu[3][0] + nu[1][2])* (nu[3][0] + nu[1][2]) - (nu[2][1] + nu[0][3])*(nu[2][1] + nu[0][3]));

}

void normalizedCentralMoments(double nu[][4], double mu[][4], double m[][4]){
    //The normalized central moments
    for (int p = 0; p <= 3; ++p){
        for (int q = 0; q <= 3 && p + q < 4; ++q){
            if (p + q > 1)
                nu[p][q] = norm_cent(mu[p][q], m[0][0], p, q);
        }
    }
}

void calculateHuMoment(const cv::Mat img, HuMomentStruct& Hu_Value){
    calculateMoment(img, Hu_Value.m);
    centroidImage(Hu_Value.x_cen, Hu_Value.y_cen, Hu_Value.m);
    centralMoment(img, Hu_Value.x_cen, Hu_Value.y_cen, Hu_Value.mu);
    normalizedCentralMoments(Hu_Value.nu, Hu_Value.mu, Hu_Value.m);
    HuMoment(Hu_Value.Hu, Hu_Value.nu);
}

void normalizedLogarit(double Hu[]){
    for(int i=0; i<7; ++i){
        Hu[i] = log(fabs(Hu[i]));
    }
}
