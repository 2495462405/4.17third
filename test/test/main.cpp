//
//  main.cpp
//  test
//
//  Created by 徐亦燊 on 2020/2/28.
//  Copyright © 2020 徐亦燊. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;
int main(int argc, const char * argv[]) {
    
    
  Mat img1 = imread("/Users/xuyishen/Desktop/sa jiganyouhaximeiyouga/2020.4.24/1/img1.jpg");
    Mat img2 = imread("/Users/xuyishen/Desktop/sa jiganyouhaximeiyouga/2020.4.24/1/img2.jpg");
    Mat hog = imread("/Users/xuyishen/Desktop/sa jiganyouhaximeiyouga/2020.4.24/1/hogTemplate.jpg");
    Mat gx,gy;
       Mat mag,angle;
       Sobel(hog, gx, CV_32F, 1, 0, 1);
       Sobel(hog, gy, CV_32F, 0, 1, 1);
       cartToPolar(gx, gy, mag, angle, true);
    
    int cellSize=16;
    int nX = hog.cols/cellSize;
    int nY = hog.rows/cellSize;
    int cellnum=nX*nY;
    int bins=cellnum*8;
    float* ref_hist = new float[bins];
    memset(ref_hist, 0, sizeof(float) * bins);
    int cell = 0;
    for (int j = 0;j < nY;j++)
       {
           for (int i = 0;i < nX;i++)
           {
               for (int y = j * cellSize;y < (j + 1) * cellSize;y++)
               {
                   for (int x = i * cellSize;x < (i + 1) * cellSize;x++)
                   {
                       int intangle = 0;
                       float fangle = angle.at<float>(y, x);
                       intangle = fangle/45;
                       float magnitude = mag.at<float>(y, x);
                       ref_hist[intangle + cell * 8] += magnitude;
                   }
               }
               cell++;
           }
       }
   
     Mat gx1,gy1;
        Mat mag1,angle1;
        Sobel(img1, gx1, CV_32F, 1, 0, 1);
        Sobel(img1, gy1, CV_32F, 0, 1, 1);
        cartToPolar(gx1, gy1, mag1, angle1, true);
     
 
     nX = img1.cols/cellSize;
     nY = img1.rows/cellSize;
     cellnum=nX*nY;
     bins=cellnum*8;
     float* ref_hist1 = new float[bins];
     memset(ref_hist1, 0, sizeof(float) * bins);
     cell = 0;
     for (int j = 0;j < nY;j++)
        {
            for (int i = 0;i < nX;i++)
            {
                for (int y = j * cellSize;y < (j + 1) * cellSize;y++)
                {
                    for (int x = i * cellSize;x < (i + 1) * cellSize;x++)
                    {
                        int intangle = 0;
                        float fangle = angle1.at<float>(y, x);
                        intangle = fangle/45;
                        float magnitude = mag1.at<float>(y, x);
                        ref_hist1[intangle + cell * 8] += magnitude;
                    }
                }
                cell++;
            }
        }
    
     Mat gx2,gy2;
        Mat mag2,angle2;
        Sobel(img2, gx2, CV_32F, 1, 0, 1);
        Sobel(img2, gy2, CV_32F, 0, 1, 1);
        cartToPolar(gx2, gy2, mag2, angle2, true);
     
     nX = img2.cols/cellSize;
     nY = img2.rows/cellSize;
     cellnum=nX*nY;
     bins=cellnum*8;
     float* ref_hist2 = new float[bins];
     memset(ref_hist2, 0, sizeof(float) * bins);
      cell = 0;
     for (int j = 0;j < nY;j++)
        {
            for (int i = 0;i < nX;i++)
            {
                for (int y = j * cellSize;y < (j + 1) * cellSize;y++)
                {
                    for (int x = i * cellSize;x < (i + 1) * cellSize;x++)
                    {
                        int intangle = 0;
                        float fangle = angle2.at<float>(y, x);
                        intangle = fangle/45;
                        float magnitude = mag2.at<float>(y, x);
                        ref_hist2[intangle + cell * 8] += magnitude;
                    }
                }
                cell++;
            }
        }
    
    
    int r1 = 0;
    int r2 = 0;
    int result1=0;
    int result2=0;
    for (int i = 0;i < bins;i++)
    {
        r1 += (ref_hist[i]- ref_hist1[i])*(ref_hist[i]- ref_hist1[i]);
        r2 += (ref_hist[i] - ref_hist2[i])*(ref_hist[i]- ref_hist2[i]);

    }
    result1=sqrt(r1);
    result2=sqrt(r2);
    cout << result1 << endl;
    cout << result2 << endl;
    if (result1 < result2)
    {
        cout << "img1与原图更像" << endl;
    }
    else
    {
        cout << "img2与原图更像" << endl;
    }
    waitKey(0);
    delete[] ref_hist;
    delete[] ref_hist1;
    delete[] ref_hist2;

        return 0;
    }
