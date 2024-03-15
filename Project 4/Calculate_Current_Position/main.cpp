/*
  Suriya Kasiyalan Siva
  Spring 2024
  03/15/2024
  CS 5330 Computer Vision
*/

#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::FileStorage fs("camera_calibration.yml", cv::FileStorage::READ);
    cv::Mat cameraMatrix, distCoeffs;
    fs["cameraMatrix"] >> cameraMatrix;
    fs["distortionCoefficients"] >> distCoeffs;
    fs.release();

    cv::VideoCapture cap(0); // Open the video stream
    if (!cap.isOpened()) {
        std::cerr << "Error: Cannot open video stream" << std::endl;
        return -1;
    }

    cv::Size boardSize(9, 6); // Adjust according to your checkerboard size
    std::vector<cv::Point3f> objectPoints;
    float squareSize = 1.0; // Size of each square in the checkerboard

    for (int i = 0; i < boardSize.height; ++i) {
        for (int j = 0; j < boardSize.width; ++j) {
            objectPoints.push_back(cv::Point3f(j * squareSize, i * squareSize, 0));
        }
    }

    while (true) {
        cv::Mat frame;
        cap >> frame; // Capture frame-by-frame
        if (frame.empty()) {
            std::cerr << "Error: Frame is empty" << std::endl;
            break;
        }

        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        std::vector<cv::Point2f> corners;
        bool found = cv::findChessboardCorners(gray, boardSize, corners);

        if (found) {
            cv::Mat rvec, tvec;
            cv::solvePnP(objectPoints, corners, cameraMatrix, distCoeffs, rvec, tvec);

            std::cout << "Rotation vector (rvec):" << std::endl << rvec << std::endl;
            std::cout << "Translation vector (tvec):" << std::endl << tvec << std::endl;
        }

        cv::imshow("Frame", frame);
        char key = cv::waitKey(1);
        if (key == 'q') { // Break the loop if the 'q' key is pressed
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
