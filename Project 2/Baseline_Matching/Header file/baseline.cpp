/*
  Suriya Kasiyalan Siva & Saikiran Juttu
  Spring 2024
  02/06/2024
  CS 5330 Computer Vision
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace cv;
using namespace std;

// Function to compute the sum-of-squared-difference between two matrices
static double computeSSD(const Mat& mat1, const Mat& mat2) {
    Mat diff;
    absdiff(mat1, mat2, diff);
    return sum(diff.mul(diff))[0];
}

// Function to find the most similar images based on SSD
static vector<pair<double, String>> findSimilarImages(const Mat& targetFeature, const vector<String>& imagePaths) {
    vector<pair<double, String>> distances;

    for (const auto& imagePath : imagePaths) {
        // Read the current image
        Mat currentImage = imread(imagePath, IMREAD_GRAYSCALE);

        if (currentImage.empty()) {
            cout << "Error reading image: " << imagePath << endl;
            continue;
        }

        // Extract the central 7x7 square as the feature vector from the current image
        Mat currentFeature = currentImage(Rect(currentImage.cols / 2 - 3, currentImage.rows / 2 - 3, 7, 7)).clone();

        // Compute the sum-of-squared-difference between targetFeature and currentFeature
        double distance = computeSSD(targetFeature, currentFeature);

        // Store the distance and image path in the distances vector
        distances.push_back({ distance, imagePath });
    }

    // Sort the distances vector based on the first element of the pairs (distance)
    sort(distances.begin(), distances.end());

    return distances;
}
