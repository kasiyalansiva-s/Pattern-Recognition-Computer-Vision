#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include "baseline.cpp"


using namespace cv;
using namespace std;

//// Function to compute the sum-of-squared-difference between two matrices
//double computeSSD(const Mat& mat1, const Mat& mat2) {
//    Mat diff;
//    absdiff(mat1, mat2, diff);
//    return sum(diff.mul(diff))[0];
//}
//
//// Function to find the most similar images based on SSD
//vector<pair<double, String>> findSimilarImages(const Mat& targetFeature, const vector<String>& imagePaths) {
//    vector<pair<double, String>> distances;
//
//    for (const auto& imagePath : imagePaths) {
//        // Read the current image
//        Mat currentImage = imread(imagePath, IMREAD_GRAYSCALE);
//
//        if (currentImage.empty()) {
//            cout << "Error reading image: " << imagePath << endl;
//            continue;
//        }
//
//        // Extract the central 7x7 square as the feature vector from the current image
//        Mat currentFeature = currentImage(Rect(currentImage.cols / 2 - 3, currentImage.rows / 2 - 3, 7, 7)).clone();
//
//        // Compute the sum-of-squared-difference between targetFeature and currentFeature
//        double distance = computeSSD(targetFeature, currentFeature);
//
//        // Store the distance and image path in the distances vector
//        distances.push_back({ distance, imagePath });
//    }
//
//    // Sort the distances vector based on the first element of the pairs (distance)
//    sort(distances.begin(), distances.end());
//
//    return distances;
//}

int main() {
    // Hardcoded paths to the target image and directory containing images
    String targetImagePath = "olympus/pic.0715.jpg";
    String directoryPath = "olympus";

    cout << "Reading target image..." << endl;
    // Read the target image
    Mat targetImage = imread(targetImagePath, IMREAD_GRAYSCALE);

    if (targetImage.empty()) {
        cout << "Error reading target image." << endl;
        return -1;
    }

    cout << "Target image read successfully." << endl;

    // Extract the central 7x7 square as the feature vector from the target image
    Mat targetFeature = targetImage(Rect(targetImage.cols / 2 - 3, targetImage.rows / 2 - 3, 7, 7)).clone();

    // Read all images from the directory
    vector<String> imagePaths;
    glob(directoryPath + "/*.jpg", imagePaths);

    // Find similar images based on SSD
    vector<pair<double, String>> similarImages = findSimilarImages(targetFeature, imagePaths);

    // Display the target image
    namedWindow("Target Image", WINDOW_NORMAL);
    imshow("Target Image", targetImage);
    waitKey(0);

    // Display the top 5 similar images
    int topN = 5;
    for (int i = 0; i < min(topN, static_cast<int>(similarImages.size())); ++i) {
        //cout << "Distance: " << similarImages[i].first << ", Image Path: " << similarImages[i].second << endl;
        Mat similarImage = imread(similarImages[i].second, IMREAD_GRAYSCALE);
        
        if (similarImage.empty()) {
            cout << "Error reading similar image: " << similarImages[i].second << endl;
            continue;
        }

        namedWindow("Similar Image " + to_string(i + 1), WINDOW_NORMAL);
        imshow("Similar Image " + to_string(i + 1), similarImage);
        

    }waitKey(0);


    // Display the top 5 similar images distances                   ** can be add in the above for loop but just to display the distance in the separately i have done this **

    // Distance: 0, Image Path: olympus\pic.0217.jpg
    //Distance: 7664, Image Path : olympus\pic.1007.jpg
    //Distance : 7994, Image Path : olympus\pic.0776.jpg
    //Distance : 8015, Image Path : olympus\pic.0617.jpg
    //Distance : 8106, Image Path : olympus\pic.0063.jpg
    // this will display the distance of the images separately like this in the terminal
    // that is the reason that i have added it 


    for (int i = 0; i < min(topN, static_cast<int>(similarImages.size())); ++i) {
        cout << "Distance: " << similarImages[i].first << ", Image Path: " << similarImages[i].second << endl;
    }waitKey(0);

    

    return 0;
}
