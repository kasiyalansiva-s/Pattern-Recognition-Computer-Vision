#include <iostream>
#include <opencv2/opencv.hpp>

static int blur5x5_2(cv::Mat& src, cv::Mat& dst) {
    if (src.empty()) {
        return -1;  // Return error code if source image is empty
    }

    // Copy the source image to the destination image
    dst = src.clone();

    // Get image dimensions
    int rows = src.rows;
    int cols = src.cols;

    // Separable 1x5 filters for vertical and horizontal blur
    int kernel[5] = { 1, 2, 4, 2, 1 };

    // Apply the horizontal blur filter
    for (int i = 0; i < rows; ++i) {
        for (int j = 2; j < cols - 2; ++j) {
            for (int c = 0; c < src.channels(); ++c) {
                int sum = 0;
                // Convolution with the 1x5 kernel horizontally
                for (int n = -2; n <= 2; ++n) {
                    sum += src.ptr<cv::Vec3b>(i)[j + n][c] * kernel[n + 2];
                }
                // Update the destination pixel
                dst.ptr<cv::Vec3b>(i)[j][c] = sum / 10;  // Integer approximation of Gaussian
            }
        }
    }

    // Apply the vertical blur filter
    for (int i = 2; i < rows - 2; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int c = 0; c < src.channels(); ++c) {
                int sum = 0;
                // Convolution with the 1x5 kernel vertically
                for (int m = -2; m <= 2; ++m) {
                    sum += dst.ptr<cv::Vec3b>(i + m)[j][c] * kernel[m + 2];
                }
                // Update the destination pixel
                dst.ptr<cv::Vec3b>(i)[j][c] = sum / 10;  // Integer approximation of Gaussian
            }
        }
    }

    return 0;  // Return success code
}

