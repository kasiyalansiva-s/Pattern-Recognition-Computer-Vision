#pragma once
#include "opencv2/opencv.hpp"



int greyscale(cv::Mat& src, cv::Mat& dst) {
    CV_Assert(src.type() == CV_8UC3); // Ensure input is a 3-channel image

    dst.create(src.size(), src.type());

    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            cv::Vec3b pixel = src.at<cv::Vec3b>(i, j);
            dst.at<cv::Vec3b>(i, j) = cv::Vec3b(255 - pixel[0], 255 - pixel[1], 255 - pixel[2]);
        }
    }

    return 0; // Return 0 on success
}