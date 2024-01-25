#include <cstdio>                    // this is to call all the C++ input output libraries
#include <iostream>
#include <opencv2/opencv.hpp> // This header covers all the opencv functions 

static int Customgreyscale(cv::Mat & src, cv::Mat & dst) {
    CV_Assert(src.type() == CV_8UC3); // Ensure input is a 3-channel image

    dst.create(src.size(), src.type());

    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            cv::Vec3b pixel = src.at<cv::Vec3b>(i, j);
            dst.at<cv::Vec3b>(i, j) = cv::Vec3b(255 - pixel[2], 255 - pixel[2], 255 - pixel[2]);
        }
    }

    return 0; // Return 0 on success
}
// Function to apply Sepia tone filter to a pixel
static void applySepiaTone(cv::Mat& src, cv::Mat& dst) {
    CV_Assert(src.type() == CV_8UC3); // Ensure input is a 3-channel image

    dst.create(src.size(), src.type());
    // Iterate over each pixel and apply the Sepia tone filter
    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            cv::Vec3b pixel = src.at<cv::Vec3b>(i, j);
            // Get the original color values
            int red = pixel[2];
            int green = pixel[1];
            int blue = pixel[0];

            // Calculate new color values using the Sepia matrix
            int newRed = cv::saturate_cast<uchar>(0.393 * red + 0.769 * green + 0.1869 * blue);
            int newGreen = cv::saturate_cast<uchar>(0.349 * red + 0.686 * green + 0.168 * blue);
            int newBlue = cv::saturate_cast<uchar>(0.272 * red + 0.534 * green + 0.131 * blue);

            // Update the pixel with modified color values
            pixel[2] = newRed;    // Red
            pixel[1] = newGreen;  // Green
            pixel[0] = newBlue;   // Blue
            dst.at<cv::Vec3b>(i, j) = pixel;
        }
        
    }
   
    

}
static int sobelX3x3(cv::Mat& src, cv::Mat& dst) {
    dst.create(src.size(), CV_16SC3);

    for (int y = 1; y < src.rows - 1; ++y) {
        for (int x = 1; x < src.cols - 1; ++x) {
            for (int c = 0; c < 3; ++c) {
                int gx = src.at<cv::Vec3b>(y - 1, x + 1)[c] - src.at<cv::Vec3b>(y - 1, x - 1)[c]
                    + 2 * (src.at<cv::Vec3b>(y, x + 1)[c] - src.at<cv::Vec3b>(y, x - 1)[c])
                    + src.at<cv::Vec3b>(y + 1, x + 1)[c] - src.at<cv::Vec3b>(y + 1, x - 1)[c];
                dst.at<cv::Vec3s>(y, x)[c] = static_cast<short>(gx);
            }
        }
    }

    return 0;
}

static int sobelY3x3(cv::Mat& src, cv::Mat& dst) {
    dst.create(src.size(), CV_16SC3);

    for (int y = 1; y < src.rows - 1; ++y) {
        for (int x = 1; x < src.cols - 1; ++x) {
            for (int c = 0; c < 3; ++c) {
                int gy = src.at<cv::Vec3b>(y + 1, x - 1)[c] - src.at<cv::Vec3b>(y - 1, x - 1)[c]
                    + 2 * (src.at<cv::Vec3b>(y + 1, x)[c] - src.at<cv::Vec3b>(y - 1, x)[c])
                    + src.at<cv::Vec3b>(y + 1, x + 1)[c] - src.at<cv::Vec3b>(y - 1, x + 1)[c];
                dst.at<cv::Vec3s>(y, x)[c] = static_cast<short>(gy);
            }
        }
    }

    return 0;
}
