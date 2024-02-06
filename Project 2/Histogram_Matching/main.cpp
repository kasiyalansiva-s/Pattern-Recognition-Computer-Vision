/*
  Suriya Kasiyalan Siva & Saikiran Juttu
  Spring 2024
  02/06/2024
  CS 5330 Computer Vision
*/
//3//

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "histogram.cpp"

using namespace cv;
using namespace std;
int main() {
    String targetImagePath = "olympus/pic.0747.jpg";
    String directoryPath = "olympus";

    int bins = 256;  // Number of bins for the histogram

    cout << "Reading target image..." << endl;
    Mat targetImage = imread(targetImagePath);

    if (targetImage.empty()) {
        cout << "Error reading target image." << endl;
        return -1;
    }

    cout << "Target image read successfully." << endl;

    Mat targetHist = calculateHistogram(targetImage, bins);

    vector<String> imagePaths;
    glob(directoryPath + "/*.jpg", imagePaths);

    vector<pair<double, String>> similarImages = findSimilarImages(targetHist, imagePaths, bins);

    namedWindow("Target Image", WINDOW_NORMAL);
    imshow("Target Image", targetImage);
    waitKey(0);

    int topN = 4;
    for (int i = 0; i < min(topN, static_cast<int>(similarImages.size())); ++i) {
        Mat similarImage = imread(similarImages[i].second);

        if (similarImage.empty()) {
            cout << "Error reading similar image: " << similarImages[i].second << endl;
            continue;
        }

        namedWindow("Similar Image " + to_string(i + 1), WINDOW_NORMAL);
        imshow("Similar Image " + to_string(i + 1), similarImage);
    }

    waitKey(0);

    return 0;
}
