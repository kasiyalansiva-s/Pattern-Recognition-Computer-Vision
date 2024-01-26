// filter.cpp 
// Brightness and Contrast Filter
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

static void applyFilter(const Mat& inputFrame, Mat& outputFrame, double alpha, int beta) {
    outputFrame = Mat::zeros(inputFrame.size(), inputFrame.type());

    for (int y = 0; y < inputFrame.rows; y++) {
        for (int x = 0; x < inputFrame.cols; x++) {
            for (int c = 0; c < inputFrame.channels(); c++) {
                outputFrame.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha * inputFrame.at<Vec3b>(y, x)[c] + beta);
            }
        }
    }
}
