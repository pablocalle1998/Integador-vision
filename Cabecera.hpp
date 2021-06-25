
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
using namespace std;
using namespace cv; 

class BaseClass
{
private:
    int m_ch1 = 44;
    int m_ch2 = 50;
    int m_ch3 = 57;
    int mx_ch1 = 98;
    int mx_ch2 = 255;
    int mx_ch3 = 255;
    int typeSpa = 1;


public:

    Mat nShape(Mat img, int weight, int height);
    Mat edgc_fil(Mat img, int thres, int kernel);
    Mat edgelp_fil(Mat img, int kernel);
    Mat md_fil(Mat img2, int mask);
    Mat b_fil(Mat img2, int mask);
    Mat gb_fil(Mat img2, int mask, double sig);
    Mat ero(Mat img3, Mat obj);
    Mat dil(Mat img3, Mat obj);
    Mat ch_gray(Mat img);
    Mat ch_hsv(Mat img);
    Mat ch_cie(Mat img);
    Mat ch_ycr(Mat img);

    Mat spa_mm(Mat img, int m_ch1, int m_ch2, int m_ch3, int mx_ch1, int mx_ch2, int mx_ch3);

    Mat img_neg(Mat img);

    Mat ove_cam(Mat umb, Mat neg, Mat img, Mat backgr);
    Mat ove_scr(Mat neg, Mat backgr, Mat img);
};


