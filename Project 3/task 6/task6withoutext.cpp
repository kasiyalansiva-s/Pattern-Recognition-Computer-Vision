
/*
  Suriya Kasiyalan Siva
  Spring 2024
  02/18/2024
  CS 5330 Computer Vision
*/


#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <map>
#include <fstream>
#include <sys/stat.h>

using namespace cv;
using namespace std;


class Object;
class FeatureStdDeviations;
static map<string, double> compute_features(const Mat& regionMask, Mat& frame);
class Object {
public:
    double centroid_x;
    double centroid_y;
    double theta;
    double percent_filled;
    double bounding_box_ratio;
    string label;

    Object(double x, double y, double t, double pf, double bbr, const string& l) : centroid_x(x), centroid_y(y), theta(t), percent_filled(pf), bounding_box_ratio(bbr), label(l) {}
};

class FeatureStdDeviations {
public:
    double centroid_x_stddev;
    double centroid_y_stddev;
    double theta_stddev;
    double percent_filled_stddev;
    double bounding_box_ratio_stddev;
};

// Function to check if a file exists
bool fileExists(const string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

static double computeStdDev(const vector<double>& values);
static FeatureStdDeviations computeFeatureStdDeviations(const vector<Object>& known_objects) {
    FeatureStdDeviations stddev;
    int num_objects = known_objects.size();
    if (num_objects == 0) {
        throw std::invalid_argument("No known objects provided.");
    }

    vector<double> centroid_x_values, centroid_y_values, theta_values, percent_filled_values, bounding_box_ratio_values;

    for (const auto& obj : known_objects) {
        centroid_x_values.push_back(obj.centroid_x);
        centroid_y_values.push_back(obj.centroid_y);
        theta_values.push_back(obj.theta);
        percent_filled_values.push_back(obj.percent_filled);
        bounding_box_ratio_values.push_back(obj.bounding_box_ratio);
    }

    stddev.centroid_x_stddev = computeStdDev(centroid_x_values);
    stddev.centroid_y_stddev = computeStdDev(centroid_y_values);
    stddev.theta_stddev = computeStdDev(theta_values);
    stddev.percent_filled_stddev = computeStdDev(percent_filled_values);
    stddev.bounding_box_ratio_stddev = computeStdDev(bounding_box_ratio_values);

    return stddev;
}

static double computeStdDev(const vector<double>& values) {
    double mean = 0.0;
    for (double value : values) {
        mean += value;
    }
    mean /= values.size();

    double variance = 0.0;
    for (double value : values) {
        variance += pow(value - mean, 2);
    }
    variance /= values.size();

    return sqrt(variance);
}

static double scaledEuclideanDistance(const Object& f1, const Object& f2, const FeatureStdDeviations& stddev) {
    double scaled_percent_filled_diff = (f1.percent_filled - f2.percent_filled) / stddev.percent_filled_stddev;
    double scaled_bounding_box_ratio_diff = (f1.bounding_box_ratio - f2.bounding_box_ratio) / stddev.bounding_box_ratio_stddev;

    double scaled_distance = sqrt(pow(scaled_percent_filled_diff, 2) + pow(scaled_bounding_box_ratio_diff, 2));
    return scaled_distance;
}

static string classifyObject(const Object& unknown_object, const vector<Object>& known_objects, const FeatureStdDeviations& stddev) {
    double min_distance = numeric_limits<double>::infinity();
    string closest_object_label;

    for (const auto& known_object : known_objects) {
        double distance = scaledEuclideanDistance(unknown_object, known_object, stddev);
        if (distance < min_distance) {
            min_distance = distance;
            closest_object_label = known_object.label;
        }
    }

    return closest_object_label;
}



static int dynmcThresholding(const Mat& image) {
    Mat samples = image.reshape(1, image.rows * image.cols);
    samples.convertTo(samples, CV_32F);
    int K = 2;
    Mat labels, centers;
    TermCriteria criteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 100, 0.2);
    kmeans(samples, K, labels, criteria, 10, KMEANS_RANDOM_CENTERS, centers);
    double threshold = (centers.at<float>(0) + centers.at<float>(1)) / 2.0;
    return static_cast<int>(threshold);
}

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
                result.at<uchar>(y, x) = 0;
            else
                result.at<uchar>(y, x) = 255;
        }
    }
}

map<string, double> compute_features(const Mat& regionMask, Mat& frame) {
    map<string, double> features;

    // Check if the region mask contains any nonzero pixels
    if (countNonZero(regionMask) == 0) {
        return features; // No object present, return empty features
    }
    // Compute moments
    Moments moments = cv::moments(regionMask, false); // Use binary moments

    // Calculate area
    double area = moments.m00;

    // Calculate centroid
    double xc = moments.m10 / area;
    double yc = moments.m01 / area;

    // Calculate central moments
    double mu20 = moments.mu20 / area;
    double mu02 = moments.mu02 / area;
    double mu11 = moments.mu11 / area;

    // Calculate angle of least central moment
    double alpha = 0.5 * atan2(2 * mu11, (mu20 - mu02));

    // Calculate axis of the least central moment from centroid
    double cos_alpha = cos(alpha);
    double sin_alpha = sin(alpha);
    Point2f start(xc, yc);
    Point2f end(xc + 50 * cos_alpha, yc + 50 * sin_alpha); // Adjust length of axis pointer as needed
    line(frame, start, end, Scalar(0, 0, 255), 2);

    // Calculate rotated bounding box points
    vector<Point> nonzeroPoints;
    findNonZero(regionMask, nonzeroPoints);
    RotatedRect rotatedRect = minAreaRect(nonzeroPoints);

    // Extract width and height from the rotated rectangle
    double width = rotatedRect.size.width;
    double height = rotatedRect.size.height;

    // Draw oriented bounding box
    Point2f rectPoints[4];
    rotatedRect.points(rectPoints);
    for (int i = 0; i < 4; ++i) {
        line(frame, rectPoints[i], rectPoints[(i + 1) % 4], Scalar(255, 0, 255), 2);
    }

    // Calculate percent filled
    double bounding_box_area = width * height;
    double percent_filled = (area / bounding_box_area) * 100;

    // Store computed features in the map
    features["centroid_x"] = xc;
    features["centroid_y"] = yc;
    features["theta"] = alpha;
    features["percent_filled"] = percent_filled;
    features["bounding_box_ratio"] = height / width;

    return features;
}

void saveObjectData(const string& label, const map<string, double>& features, ofstream& outputFile) {
    if (outputFile.is_open()) {
        outputFile << label << ",";
        outputFile << features.at("centroid_x") << ",";
        outputFile << features.at("centroid_y") << ",";
        outputFile << features.at("theta") << ",";
        outputFile << features.at("percent_filled") << ",";
        outputFile << features.at("bounding_box_ratio") << endl;

        cout << "Object data saved with label: " << label << endl;
    }
    else {
        cerr << "Error: Unable to write to the output file. File is not open." << endl;
    }
}

int main() {

    // Set threshold distance for classification
    double threshold_distance = 100.0; // Adjust threshold distance as needed

    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Error: Unable to open the webcam.\n";
        return -1;
    }

    ofstream outputFile("object_data.csv", ios::app);
    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open object_data.csv for writing.\n";
        return -1;
    }

    // Check if the file exists, if not, write the header
    if (!fileExists("object_data.csv")) {
        outputFile << "Label,Centroid_X,Centroid_Y,Theta,Percent_Filled,BoundingBox_Ratio\n";
    }

    char mode = 'n'; // Mode: 'n' for normal operation, 't' for training mode
    string label; // Label for the object

    vector<Object> known_objects;
    known_objects.clear();
    ifstream objectFile("object_data.csv");
    if (objectFile.is_open()) {
        string line;
        getline(objectFile, line); // Skip header line
        while (getline(objectFile, line)) {
            stringstream ss(line);
            string label;
            double centroid_x, centroid_y, theta, percent_filled, bounding_box_ratio;
            char delimiter;
            if (getline(ss, label, ',') && (ss >> centroid_x >> delimiter >> centroid_y >> delimiter >> theta >> delimiter >> percent_filled >> delimiter >> bounding_box_ratio)) {
                known_objects.push_back(Object(centroid_x, centroid_y, theta, percent_filled, bounding_box_ratio, label));
            }
        }
        objectFile.close();
    }
    else {
        cerr << "Error: Unable to open object_data.csv for reading.\n";
        return -1;
    }

    FeatureStdDeviations stddev = computeFeatureStdDeviations(known_objects);

    while (true) {
        Mat frame;
        cap >> frame;
        if (frame.empty()) {
            cerr << "Error: Unable to capture frame.\n";
            break;
        }

        Mat grayFrame;
        cvtColor(frame, grayFrame, COLOR_BGR2GRAY);

        int thresholdValue = dynmcThresholding(grayFrame);
        Mat thresholded;
        normalThresholding(grayFrame, thresholdValue, thresholded);

        Mat erodedImage;
        Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
        erode(thresholded, erodedImage, element);

        Mat labels, stats, centroids;
        int numComponents = connectedComponentsWithStats(erodedImage, labels, stats, centroids, 8, CV_32S);

        int minRegionSize = 100;
        int maxRegionsToShow = 1;
        vector<int> regionIndices;
        for (int i = 1; i < numComponents; ++i) {
            if (stats.at<int>(i, CC_STAT_AREA) > minRegionSize) {
                regionIndices.push_back(i);
            }
        }
        sort(regionIndices.begin(), regionIndices.end(),
            [&](int a, int b) { return stats.at<int>(a, CC_STAT_AREA) > stats.at<int>(b, CC_STAT_AREA); });

        Mat regionMap = Mat::zeros(labels.size(), CV_8UC3);
        for (int i : regionIndices) {
            Mat regionMask = (labels == i);
            map<string, double> features = compute_features(regionMask, frame);
            Object unknown_object(features["centroid_x"], features["centroid_y"], features["theta"],
                features["percent_filled"], features["bounding_box_ratio"], "");
            string object_label = classifyObject(unknown_object, known_objects, stddev);

            // Display the label on the frame
            if (!object_label.empty()) {
                cout << "Object label: " << object_label << endl; // Debug statement
                cout << "Centroid position: (" << features["centroid_x"] << ", " << features["centroid_y"] << ")" << endl; // Debug statement
                putText(frame, object_label, Point(features["centroid_x"], features["centroid_y"]),
                    FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);
            }
            else {
                cout << "Object label is empty!" << endl; // Debug statement
            }

            regionMap.setTo(Scalar(rand() & 255, rand() & 255, rand() & 255), regionMask);

            if (mode == 't' && label.empty()) { // Training mode and label is not set
                cout << "Enter label for the object: ";
                cin >> label;
            }

            // If label is provided, save object data and store in known_objects vector
            if (!label.empty()) {
                saveObjectData(label, features, outputFile);
                known_objects.emplace_back(features["centroid_x"], features["centroid_y"], features["theta"],
                    features["percent_filled"], features["bounding_box_ratio"], label);
            }
            label.clear();

            cout << "Region " << i << " Features:\n";
            for (const auto& pair : features) {
                cout << pair.first << ": " << pair.second << endl;
            }
            regionMap.setTo(Scalar(rand() & 255, rand() & 255, rand() & 255), regionMask);
        }

        imshow("Frame", frame);
        imshow("Region Map", regionMap);

        char key = waitKey(30);
        if (key == 't' || key == 'T') { // Toggle training mode on 'T' key press
            mode = (mode == 't') ? 'n' : 't'; // Switch mode
            if (mode == 't') {
                cout << "Training mode enabled. Press 'T' again to disable.\n";
            }
            else {
                cout << "Training mode disabled.\n";
                label.clear(); // Clear label when training mode is disabled
            }
        }
        else if (key == 27) { // Exit if 'Esc' key is pressed
            cout << "Esc key is pressed. Exiting...\n";
            break;
        }
    }

    cap.release();
    outputFile.close(); // Close the output file when done

    return 0;
}
