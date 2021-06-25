#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "Cabecera.hpp"

using namespace std;

using namespace cv;

int fil_op = 2;
int edge_fil = 1;
int mof_fil = 7;
int mf_op = 0;
int vf_op = 0;

/*color space took by variables*/
int c_hsv = 1;
int valorMascara = 11;
int mof_val = 37;
int mask_edge_val = 3;
double sig = 0.1;

//define threshold for filter
int thres = 150;

/*
default values minimum and maximum
*/
int val_0 = 85;
int m1 = 0;
int m2 = 0;
int mx0 = 180;
int mx1 = 255;
int mx2 = 255;

int main(int argc, char *argv[]){

    BaseClass col_space;
   
    Mat backgr;
    Mat fr;
    Mat gray;
    Mat hsv;
    Mat cielab;
    Mat YCrCb;

    /*
    Set of Filters aplying to diferents images
    */
    Mat best_img;
    Mat res_img;
    Mat umb_img;
    Mat neg;
    Mat img_med;
    Mat img_gau;
    Mat img_sof;
    

    Mat img_lp;
    Mat img_can;
    Mat img_edg;
    Mat ero;
    Mat img_opmo;
    VideoCapture video("/dev/video0");
    if (video.isOpened()){
        namedWindow("just vidio", WINDOW_AUTOSIZE);
        namedWindow("background", WINDOW_AUTOSIZE);
        namedWindow("umb_img", WINDOW_AUTOSIZE);
        namedWindow("Edge Dectection", WINDOW_AUTOSIZE);
        createTrackbar("HSV","background",&c_hsv, 1, NULL);
        createTrackbar("Edge Detection","background",&mf_op, 1, NULL);
        createTrackbar("Value minimum 0","background", &val_0, 180, NULL);
        createTrackbar("Value minimum 1","background",&m1, 255, NULL);
        createTrackbar("Value minimum 2","background",&m2, 255, NULL);
        createTrackbar("Value maximum 0","background", &mx0, 180, NULL);
        createTrackbar("Value maximum 1","background", &mx1, 255, NULL);
        createTrackbar("Value maximum 2","background", &mx2, 255, NULL);

        int ct = 0;
        while(3==3){

            if(ct > 2){
                ct = 0;
            }

            if(vf_op == 1){
                break;
            }
            VideoCapture ba_vid("ric.mp4");
            ct++;

            while(3==3){
                video >> fr;
                ba_vid >> backgr;
                if(vf_op == 1){
                    break;
                }
                if(fr.empty()){
                    break;
                }
                if(backgr.empty()||fr.rows==0 || fr.cols==0){
                    break;
                    
                }else{
                    flip(fr, fr, 1);
                    fr = col_space.nShape(fr, 400, 400);
                    backgr = col_space.nShape(backgr, 400, 400);
                    if(mf_op == 1){
                        gray = col_space.ch_gray(fr);
                        if(fil_op == 1){

                            if(valorMascara%2!=0 && valorMascara>0){
                                img_gau = col_space.gb_fil(gray, valorMascara, sig);
                                img_sof = img_gau;
                            }else{
                                img_gau = col_space.gb_fil(gray, 11, sig);
                                img_sof = img_gau;
                            }

                        }else if(fil_op == 0){
                            
                            if(valorMascara%2!=0 && valorMascara>0){
                                img_med = col_space.md_fil(gray, valorMascara);
                                img_sof = img_med;
                            }else{
                                img_med = col_space.md_fil(gray, 11);
                                img_sof = img_med;
                            }

                        }else{
                            img_sof = gray;
                        }

                        if(edge_fil == 0){
                            
                            img_lp = col_space.edgelp_fil(img_sof, mask_edge_val);
                            absdiff( img_lp, gray, img_edg );
                        
                        }else if(edge_fil == 1){ 

                            img_can = col_space.edgc_fil(img_sof, thres, mask_edge_val);
                            absdiff( img_can, gray, img_edg );
                        
                        }else{
                            absdiff( gray, gray, img_edg );
                            
                        }

                        cvtColor(img_edg, img_edg, COLOR_GRAY2BGR);
                        absdiff( fr, img_edg, best_img);
                        ero = getStructuringElement(MORPH_CROSS, Size(mof_val, mof_val));

                        if(mof_fil == 0){
                            img_opmo = col_space.ero(best_img, ero);
                        }else if(mof_fil ==1){
                            img_opmo = col_space.dil(best_img, ero);
                        }else if(mof_fil ==2){
                        }else{
                            img_opmo = best_img;
                        }
                        res_img = img_opmo;
                        imshow("Edge Dectection", res_img);
                    }else{
                        res_img = fr;
                    }

                    if (c_hsv == 0){
                        umb_img = col_space.spa_mm(res_img, val_0, m1, m2, mx0, mx1, mx2);

                    }else if (c_hsv == 1){
                        hsv = col_space.ch_hsv(res_img);
                        umb_img = col_space.spa_mm(hsv, val_0, m1, m2, mx0, mx1, mx2);
                    
                    }

                    neg = col_space.img_neg(umb_img);
                    backgr = col_space.ove_scr(neg, backgr, fr);
                    
                    imshow("just vidio", fr);
                    imshow("umb_img", umb_img);
                    imshow("Negative IMG", neg);
                    imshow("background", backgr);

                    if (waitKey(23)==27){
                        break;
                    }
                }
            }

        }
        video.release();
        destroyAllWindows();
    }
    return 0;
}





