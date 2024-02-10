




#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace cv;
using namespace std;

// Function to calculate a 2D normalized color histogram from an image for specified regions
static vector<Mat> calculateHistograms(const Mat& image, const vector<Rect>& regions, int bins) {
    vector<Mat> histograms;

    for (const Rect& region : regions) {
        Mat roi = image(region);

        // Split the region into its three channels (BGR)
        vector<Mat> bgrChannels;
        split(roi, bgrChannels);

        // Calculate histograms for each channel
        Mat histB, histG, histR;
        float range[] = { 0, 256 };
        const float* histRange = { range };
        calcHist(&bgrChannels[0], 1, 0, Mat(), histB, 1, &bins, &histRange, true, false);
        calcHist(&bgrChannels[1], 1, 0, Mat(), histG, 1, &bins, &histRange, true, false);
        calcHist(&bgrChannels[2], 1, 0, Mat(), histR, 1, &bins, &histRange, true, false);

        // Normalize the histograms
        normalize(histB, histB, 0, 1, NORM_MINMAX);
        normalize(histG, histG, 0, 1, NORM_MINMAX);
        normalize(histR, histR, 0, 1, NORM_MINMAX);

        // Merge the histograms into a single feature vector
        Mat hist;
        hconcat(histB, histG, hist);
        hconcat(hist, histR, hist);

        histograms.push_back(hist);
    }

    return histograms;
}

// Function to compute histogram intersection distance between corresponding histograms
static double calculateHistogramIntersection(const vector<Mat>& hist1s, const vector<Mat>& hist2s) {
    double intersection = 0.0;

    for (size_t i = 0; i < hist1s.size(); ++i) {
        Mat hist1 = hist1s[i];
        Mat hist2 = hist2s[i];

        for (int j = 0; j < hist1.rows; ++j) {
            intersection += min(hist1.at<float>(j), hist2.at<float>(j));
        }
    }

    return intersection;
}

// Function to find the most similar images based on weighted average of histogram intersection distance
static vector<pair<double, string>> findSimilarImages(const vector<Mat>& targetHistograms, const vector<vector<Mat>>& imageHistograms, const vector<string>& imagePaths) {
    vector<pair<double, string>> distances;

    for (size_t i = 0; i < imageHistograms.size(); ++i) {
        double distance = 0.0;

        // Compute histogram intersection distance for each histogram
        for (size_t j = 0; j < targetHistograms.size(); ++j) {
            distance += calculateHistogramIntersection({ targetHistograms[j] }, { imageHistograms[i][j] });
        }

        // Weighted averaging of distances
        distance /= targetHistograms.size();

        distances.push_back({ distance, imagePaths[i] });
    }

    // Sort distances in ascending order
    sort(distances.begin(), distances.end());

    return distances;
}

int main() {
    // Example usage
    Mat targetImage = imread("olympus/pic.0214.jpg");
    if (targetImage.empty()) {
        cerr << "Error: Unable to load the target image." << endl;
        return -1;
    }
    // This line is to display that the image has read successfully
    cout << "Target image read successfully." << endl;

    // Define regions of interest for the target image (top and bottom halves)
    vector<Rect> targetRegions = { Rect(0, 0, targetImage.cols, targetImage.rows / 2),
                                   Rect(0, targetImage.rows / 2, targetImage.cols, targetImage.rows / 2) };

    // Number of bins for the histogram
    int bins = 8;

    // Calculate histograms for the target image
    vector<Mat> targetHistograms = calculateHistograms(targetImage, targetRegions, bins);

    // Load database images and calculate histograms for specified regions
    vector<string> imagePaths;
    glob("olympus/*.jpg", imagePaths);
    if (imagePaths.empty()) {
        cerr << "Error: No images found in the database." << endl;
        return -1;
    }

    vector<vector<Mat>> imageHistograms;

    // Process each image in the database
    for (const string& imagePath : imagePaths) {
        Mat image = imread(imagePath);
        if (image.empty()) {
            cerr << "Error: Unable to load image " << imagePath << endl;
            continue;
        }

        // Define regions of interest for the database image (top and bottom halves)
        vector<Rect> imageRegions = { Rect(0, 0, image.cols, image.rows / 2),
                                      Rect(0, image.rows / 2, image.cols, image.rows / 2) };

        // Calculate histograms for specified regions of the database image
        vector<Mat> histograms = calculateHistograms(image, imageRegions, bins);
        imageHistograms.push_back(histograms);
    }

    // Find similar images based on histogram intersection distance
    vector<pair<double, string>> similarImages = findSimilarImages(targetHistograms, imageHistograms, imagePaths);

    // Display top 3 matches
    int topN = min(static_cast<int>(similarImages.size()), 3);
    for (int i = 0; i < topN; ++i) {
        // Display image
        Mat similarImage = imread(similarImages[i].second);
        if (similarImage.empty()) {
            cerr << "Error: Unable to load image " << similarImages[i].second << endl;
            continue;
        }
        imshow("Target Image", targetImage);
        imshow("Match " + to_string(i + 1) + " - Distance: " + to_string(similarImages[i].first), similarImage);

    }

    waitKey(0); // Wait for a keystroke

    return 0;
}
