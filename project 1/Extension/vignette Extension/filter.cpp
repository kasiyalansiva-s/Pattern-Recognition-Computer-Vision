// vignette filter 

#include <iostream>
#include <opencv2/opencv.hpp>

//using namespace std;
//using namespace cv;
//


static void applyVignette(cv::Mat& src, double vignetteStrength) {   //cv::Mat& dst
    int width = src.cols;
    int height = src.rows;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            cv::Vec3b& pixel = src.at<cv::Vec3b>(y, x);
            //cv::Vec3b& resultPixel = dst.at<cv::Vec3b>(y, x);

            // Calculate vignetting effect with faded curves
            double vignette = pow((1.0 - sqrt(pow((x - width / 2.0) / (width / 2.0), 4) + pow((y - height / 2.0) / (height / 2.0), 4))), vignetteStrength);

            ////// Apply vignetting
            ////resultPixel[2] = static_cast<uchar>(pixel[2] * vignette);
            ////resultPixel[1] = static_cast<uchar>(pixel[1] * vignette);
            ////resultPixel[0] = static_cast<uchar>(pixel[0] * vignette);


            // Apply vignetting only
            pixel[2] *= vignette;
            pixel[1] *= vignette;
            pixel[0] *= vignette;
        }
    }
}
