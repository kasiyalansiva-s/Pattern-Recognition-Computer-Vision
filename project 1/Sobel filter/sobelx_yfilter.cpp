#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// Function to apply 3x3 Sobel X filter
void sobelX3x3(cv::Mat& src, cv::Mat& dst) {
    // Define the Sobel X filter
    int sobelX[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    // Iterate over the image
    for (int j = 0; j < src.rows - 2; j++) {
        for (int i = 0; i < src.cols - 2; i++) {
            for (int c = 0; c < src.channels(); c++) {
                // Calculate the convolution
                int pixval_x =
                    (sobelX[0][0] * (int)src.at<Vec3b>(j, i)[c]) + (sobelX[0][1] * (int)src.at<Vec3b>(j + 1, i)[c]) + (sobelX[0][2] * (int)src.at<Vec3b>(j + 2, i)[c]) +
                    (sobelX[1][0] * (int)src.at<Vec3b>(j, i + 1)[c]) + (sobelX[1][1] * (int)src.at<Vec3b>(j + 1, i + 1)[c]) + (sobelX[1][2] * (int)src.at<Vec3b>(j + 2, i + 1)[c]) +
                    (sobelX[2][0] * (int)src.at<Vec3b>(j, i + 2)[c]) + (sobelX[2][1] * (int)src.at<Vec3b>(j + 1, i + 2)[c]) + (sobelX[2][2] * (int)src.at<Vec3b>(j + 2, i + 2)[c]);

                // Set the result pixel value
                dst.at<Vec3s>(j, i)[c] = static_cast<short>(pixval_x);
            }
        }
    }
}

// Function to apply 3x3 Sobel Y filter
void sobelY3x3(cv::Mat& src, cv::Mat& dst) {
    // Define the Sobel Y filter
    int sobelY[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    // Iterate over the image
    for (int j = 0; j < src.rows - 2; j++) {
        for (int i = 0; i < src.cols - 2; i++) {
            for (int c = 0; c < src.channels(); c++) {
                // Calculate the convolution
                int pixval_y =
                    (sobelY[0][0] * (int)src.at<Vec3b>(j, i)[c]) + (sobelY[0][1] * (int)src.at<Vec3b>(j + 1, i)[c]) + (sobelY[0][2] * (int)src.at<Vec3b>(j + 2, i)[c]) +
                    (sobelY[1][0] * (int)src.at<Vec3b>(j, i + 1)[c]) + (sobelY[1][1] * (int)src.at<Vec3b>(j + 1, i + 1)[c]) + (sobelY[1][2] * (int)src.at<Vec3b>(j + 2, i + 1)[c]) +
                    (sobelY[2][0] * (int)src.at<Vec3b>(j, i + 2)[c]) + (sobelY[2][1] * (int)src.at<Vec3b>(j + 1, i + 2)[c]) + (sobelY[2][2] * (int)src.at<Vec3b>(j + 2, i + 2)[c]);

                // Set the result pixel value
                dst.at<Vec3s>(j, i)[c] = static_cast<short>(pixval_y);
            }
        }
    }
}
