/*
  Saikiran Juttu & Suriya Kasiyalan Siva
  Spring 2024
  01/27/2024
  CS 5330 Computer Vision
*/
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
static int magnitude(cv::Mat& sx, cv::Mat& sy, cv::Mat& dst);
static int sobelX3x3(cv::Mat& src, cv::Mat& dst);
static int sobelY3x3(cv::Mat& src, cv::Mat& dst);
#endif // FILTER_H
