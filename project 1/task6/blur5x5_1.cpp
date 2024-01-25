#include <iostream>
#include <opencv2/opencv.hpp>

static int blur5x5_1(cv::Mat& src, cv::Mat& dst) {
    if (src.empty()) {
        return -1;  // Return error code if source image is empty
    }

    // Copy the source image to the destination image
    dst = src.clone();

    // Get image dimensions
    int rows = src.rows;
    int cols = src.cols;

    // Gaussian kernel
    int kernel[5][5] = { {1, 2, 4, 2, 1},
                        {2, 4, 8, 4, 2},
                        {4, 8, 16, 8, 4},
                        {2, 4, 8, 4, 2},
                        {1, 2, 4, 2, 1} };

    // Apply the blur filter to each color channel separately
    for (int i = 2; i < rows - 2; ++i) {
        for (int j = 2; j < cols - 2; ++j) {
            for (int c = 0; c < src.channels(); ++c) {
                int sum = 0;
                // Convolution with the 5x5 kernel
                for (int m = -2; m <= 2; ++m) {
                    for (int n = -2; n <= 2; ++n) {
                        sum += src.at<cv::Vec3b>(i + m, j + n)[c] * kernel[m + 2][n + 2];
                    }
                }
                // Update the destination pixel
                dst.at<cv::Vec3b>(i, j)[c] = sum / 100;  // Integer approximation of Gaussian
            }
        }
    }

    return 0;  // Return success code
}
