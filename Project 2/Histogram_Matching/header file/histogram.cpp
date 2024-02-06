/*
  Suriya Kasiyalan Siva & Saikiran Juttu
  Spring 2024
  02/06/2024
  CS 5330 Computer Vision
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace cv;
using namespace std;

// Function to calculate a 2D normalized color histogram from an image
static Mat calculateHistogram(const Mat& image, int bins) {
    Mat hist;

    // Split the image into its three channels (BGR)
    vector<Mat> bgrChannels;
    split(image, bgrChannels);

    // Set the range for each channel (0 to 256)
    float range[] = { 0, 256 };
    const float* histRange = { range };

    // Calculate histograms for each channel
    calcHist(&bgrChannels[0], 1, 0, Mat(), hist, 1, &bins, &histRange, true, false);
    calcHist(&bgrChannels[1], 1, 0, Mat(), hist, 1, &bins, &histRange, true, false);
    calcHist(&bgrChannels[2], 1, 0, Mat(), hist, 1, &bins, &histRange, true, false);

    // Normalize the histogram
    normalize(hist, hist, 0, 1, NORM_MINMAX);

    return hist;
}

// Function to calculate histogram intersection distance between two histograms
static double calculateHistogramIntersection(const Mat& hist1, const Mat& hist2) {
    double intersection = 0.0;

    for (int i = 0; i < hist1.rows; ++i) {
        intersection += min(hist1.at<float>(i), hist2.at<float>(i));
    }

    return intersection;
}

// Function to find the most similar images based on histogram intersection distance
static vector<pair<double, String>> findSimilarImages(const Mat& targetHist, const vector<String>& imagePaths, int bins) {
    vector<pair<double, String>> distances;

    for (const auto& imagePath : imagePaths) {
        Mat currentImage = imread(imagePath);

        if (currentImage.empty()) {
            cout << "Error reading image: " << imagePath << endl;
            continue;
        }

        Mat currentHist = calculateHistogram(currentImage, bins);

        double distance = 1.0 - calculateHistogramIntersection(targetHist, currentHist);

        distances.push_back({ distance, imagePath });
    }

    sort(distances.begin(), distances.end());

    return distances;
}
