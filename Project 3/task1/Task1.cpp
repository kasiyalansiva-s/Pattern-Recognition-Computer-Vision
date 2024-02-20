/*
  Suriya Kasiyalan Siva
  Spring 2024
  02/18/2024
  CS 5330 Computer Vision
*/
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/// Function for Thresholding ///
static int dynmcThresholding(Mat& image) {
    Mat samples = image.reshape(1, image.rows * image.cols);
    samples.convertTo(samples, CV_32F);
    int K = 2;  // Kmean value as per asked 
    Mat labels, centers, Threshold;
    TermCriteria criteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 100, 0.2);
    kmeans(samples, K, labels, criteria, 10, KMEANS_RANDOM_CENTERS, centers);
    double threshold = (centers.at<float>(0) + centers.at<float>(1)) / 2.0;
    return threshold;
}

/// Function for Binary Inverse Thresholding ///
static void normalThresholding(Mat& image, int thresholdvalue, Mat& result) {
    Mat gray_img;
    if (image.channels() == 3)
        cvtColor(image, gray_img, cv::COLOR_BGR2GRAY);
    else
        gray_img = image.clone();

    result = Mat(gray_img.rows, gray_img.cols, CV_8UC1);

    for (int y = 0; y < gray_img.rows; ++y) {
        for (int x = 0; x < gray_img.cols; ++x) {
            if (gray_img.at<uchar>(y, x) >= thresholdvalue)
                result.at<uchar>(y, x) = 255; 
            else
                result.at<uchar>(y, x) = 0; 
        }
    }
}
static void binaryInverseThresholding(Mat& image, int thresholdvalue, Mat& result) {
    Mat gray_img;
    if (image.channels() == 3)
        cvtColor(image, gray_img, cv::COLOR_BGR2GRAY);
    else
        gray_img = image.clone();

    result = Mat(gray_img.rows, gray_img.cols, CV_8UC1);

    for (int y = 0; y < gray_img.rows; ++y) {
        for (int x = 0; x < gray_img.cols; ++x) {
            if (gray_img.at<uchar>(y, x) >= thresholdvalue)
                result.at<uchar>(y, x) = 0;
            else
                result.at<uchar>(y, x) = 255;
        }
    }
}

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Error: Unable to open camera!" << endl;
        return -1;
    }
    Mat frame;
    Mat thresholded_normal;
    Mat thresholded_binary_inverse;
    while (true) {
        cap >> frame;
        if (frame.empty())
            break;

        Mat gray;
        GaussianBlur(frame, frame, Size(5, 5), 0, 10);
        cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        int threshold_value = dynmcThresholding(frame);
        normalThresholding(gray, threshold_value, thresholded_normal);
        binaryInverseThresholding(gray, threshold_value, thresholded_binary_inverse);
        Mat display;
        hconcat(thresholded_normal, thresholded_binary_inverse, display);
        imshow("Thresholded Images", display);

        if (waitKey(30) >= 0)
            break;
    }

    cap.release();
    return 0;
}