#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp> 
#include <opencv2/imgcodecs/imgcodecs.hpp> 
#include <opencv2/video/video.hpp> 
#include <opencv2/videoio/videoio.hpp> 

#include "Cabecera.hpp"

using namespace std;
using namespace cv; 
Mat BaseClass::nShape(Mat img, int weight, int height){
    resize(img, img, Size(weight, height), 1, 1);
    return img;
}

Mat BaseClass::edgelp_fil(Mat img, int kernel){
    Mat img_lp;
    Mat img_sca;
    if(kernel%2!=0 && kernel>0){
        Laplacian(img, img_lp, CV_16S, kernel);
        convertScaleAbs(img_lp, img_sca);
    }else{
        Laplacian(img, img_lp, CV_16S, 5);
        convertScaleAbs(img_lp, img_sca);
    }
    
    return img_sca;
}
Mat BaseClass::edgc_fil(Mat img, int thres, int kernel){
    Mat canny;
    if(kernel%2!=0 && kernel>0){
        Canny(img, canny, thres, thres*3, kernel);
    }else{
        Canny(img, canny, thres, thres*3, 5);
    }
    
    return canny;
}

Mat BaseClass::md_fil(Mat image, int vl_mk){
    Mat desImage;
    if(vl_mk%2!=0 && vl_mk>0){
        medianBlur(image, desImage, vl_mk);
    }
    return desImage;
}

Mat BaseClass::b_fil(Mat image, int vl_mk){
    Mat desImage;
    if(vl_mk%2!=0 && vl_mk>0){
        blur(image, desImage, Size(vl_mk, vl_mk), Point(-1,-1));
    }
    return desImage;
}

Mat BaseClass::gb_fil(Mat image, int vl_mk, double sig){
    Mat desImage;
    if(vl_mk%2!=0 && vl_mk>0){
        GaussianBlur(image,desImage,Size(vl_mk, vl_mk), sig, sig);
    }
    return desImage;
}

Mat BaseClass::ero(Mat imagen, Mat obj){
    Mat img_res;
    morphologyEx(imagen, img_res, MORPH_ERODE, obj);
    return img_res;
}

Mat BaseClass::dil(Mat imagen, Mat obj){
    Mat img_res;
    morphologyEx(imagen, img_res, MORPH_DILATE, obj);
    return img_res;
}

Mat BaseClass::ch_gray(Mat img){
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    return gray;
}

Mat BaseClass::ch_hsv(Mat img){
    Mat hsv;
    cvtColor(img, hsv, COLOR_BGR2HSV);
    return hsv;
}

Mat BaseClass::ch_cie(Mat img){
    Mat cielab;
    cvtColor(img, cielab, COLOR_BGR2Lab);
    return cielab;
}

Mat BaseClass::ch_ycr(Mat img){ 
    Mat YCrCb;
    cvtColor(img, YCrCb, COLOR_BGR2YCrCb);
    return YCrCb;
}

Mat BaseClass::spa_mm(Mat img, int minCanal0, int minCanal1, int minCanal2, 
                                int maxCanal0, int maxCanal1, int maxCanal2)
{
    Mat umb;
    cv::inRange(img, Scalar(minCanal0, minCanal1, minCanal2), Scalar(maxCanal0, maxCanal1, maxCanal2), umb);
    return umb;
}

Mat BaseClass::img_neg(Mat img){
    Mat img_neg;
    bitwise_not(img, img_neg);
    return img_neg;
}

Mat BaseClass::ove_scr(Mat img_neg, Mat backgr, Mat img){
    Mat img_back = backgr;
    for(int i=0;i<img_neg.rows;i++){
        for(int j=0;j<img_neg.cols;j++){
            if((int)img_neg.at<uchar>(i,j) == 255) {
                img_back.at<Vec3b>(i,j) = backgr.at<Vec3b>(i,j);
            }else{
                img_back.at<Vec3b>(i,j) = img.at<Vec3b>(i,j);
            }
        }
    }
    return img_back;
}

Mat BaseClass::ove_cam(Mat umb, Mat img_neg, Mat img, Mat backgr){
    Vec3b vc3;
    Vec3b vc31;

    for(int i=0;i<img.rows;i++){
        for(int j=0;j<img.cols;j++){
            vc3 = backgr.at<Vec3b>(i,j);
            vc31 = img.at<Vec3b>(i,j);
            vc3[0] *= (int)(umb.at<uchar>(i,j))/255;
            vc3[1] *= (int)(umb.at<uchar>(i,j))/255;
            vc3[2] *= (int)(umb.at<uchar>(i,j))/255;


            vc31[0] *= ((int)img_neg.at<uchar>(i,j))/255;
            vc31[1] *= ((int)img_neg.at<uchar>(i,j))/255;
            vc31[2] *= ((int)img_neg.at<uchar>(i,j))/255;
            if(vc3[0]==0 && vc3[1]==0 && vc3[2]==0) {
                vc3[0] = vc31[0];
                vc3[1] = vc31[1];
                vc3[2] = vc31[2];
            }        			
            backgr.at<Vec3b>(i,j)=vc3;
        }        	
    }
    return backgr;
}