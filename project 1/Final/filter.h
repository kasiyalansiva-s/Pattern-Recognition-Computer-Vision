#ifndef FILTER_H
#define FILTER_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

static int Customgreyscale(cv::Mat & src, cv::Mat & dst);
static int applySepiaTone(cv::Mat& src, cv::Mat& dst);
static int blur5x5_2(cv::Mat& src, cv::Mat& dst);
static int blurQuantize(cv::Mat& src, cv::Mat& dst);
static int showFaces(cv::Mat& src, cv::Mat& dst);
static int Brightness_contrast(cv::Mat& frame, cv::Mat& outputFrame);
#endif // FILTER_H