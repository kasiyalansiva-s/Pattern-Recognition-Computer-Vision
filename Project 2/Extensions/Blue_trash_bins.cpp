#include <iostream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include <dirent.h> // Include for dirent

using namespace std;
using namespace cv;

Mat detectBlueRegions(const Mat& image) {
    Mat hsvImage;
    cvtColor(image, hsvImage, COLOR_BGR2HSV);

    Scalar lowerBound = Scalar(100, 50, 50); // Adjust as needed
    Scalar upperBound = Scalar(140, 255, 255); // Adjust as needed

    Mat mask;
    inRange(hsvImage, lowerBound, upperBound, mask);

    return mask;
}

int main() {
     // Load the target image
    string targetImagePath = "/media/sakiran/Internal/2nd Semester/PRCV/Project/shape/olympus/pic.0287.jpg";

    double minArea = 10000; // Adjust as needed
    double maxArea = 50000; // Adjust as needed

    vector<string> blueBinImages;

    Mat targetImage = imread(targetImagePath);
    if (targetImage.empty()) {
        cerr << "Error: Could not read target image." << endl;
        return 1;
    }

    Mat targetBlueMask = detectBlueRegions(targetImage);
    vector<vector<Point>> targetContours;
    findContours(targetBlueMask, targetContours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

    string directoryPath = "/media/sakiran/Internal/2nd Semester/PRCV/Project/shape/olympus";

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(directoryPath.c_str())) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            string filename = ent->d_name;
            if (filename == "." || filename == "..") {
                continue;
            }
            string imagePath = directoryPath + "/" + filename;
            Mat image = imread(imagePath);
            if (image.empty()) {
                cerr << "Error: Could not read image " << filename << endl;
                continue;
            }
            Mat blueMaskImage = detectBlueRegions(image);
            vector<vector<Point>> contours;
            findContours(blueMaskImage, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

            for (const auto& contour : contours) {
                double area = contourArea(contour);
                if (area >= minArea && area <= maxArea) {
                    // Compare the contours of the current image with the target image
                    for (const auto& targetContour : targetContours) {
                        double similarity = matchShapes(contour, targetContour, CONTOURS_MATCH_I1, 0);
                        
                            blueBinImages.push_back(imagePath);
                            break;
                        
                    }
                    break;
                }
            }
        }
        closedir(dir);
    } else {
        cerr << "Error: Could not open directory." << endl;
        return 1;
    }

    cout << "Images with blue trash can bins similar to the target image:" << endl;
    for (const auto& imagePath : blueBinImages) {
        cout << imagePath << endl;
        Mat outputImage = imread(imagePath);
        imshow("Blue Trash Can Bins", outputImage);
        waitKey(0);
    }

    return 0;
}
