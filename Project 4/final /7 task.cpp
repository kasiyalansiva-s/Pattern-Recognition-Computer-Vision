/*
  Suriya Kasiyalan Siva
  Spring 2024
  03/11/2024
  CS 5330 Computer Vision
*/

#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::VideoCapture cap(0); // Open the video stream
    if (!cap.isOpened()) {
        std::cerr << "Error: Cannot open video stream" << std::endl;
        return -1;
    }

    while (true) {
        cv::Mat frame;
        cap >> frame; // Capture frame-by-frame
        if (frame.empty()) {
            std::cerr << "Error: Frame is empty" << std::endl;
            break;
        }

        // Convert frame to grayscale
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Detect Harris corners
        cv::Mat corners;
        cv::cornerHarris(gray, corners, 2, 3, 0.04); // Adjust parameters as needed

        // Normalize corner response for visualization
        cv::Mat normalized_corners;
        cv::normalize(corners, normalized_corners, 0, 255, cv::NORM_MINMAX, CV_8UC1, cv::Mat());

        cv::Mat corners_visualization = cv::Mat::zeros(frame.size(), CV_8UC3);

        // Draw corners on the frame
        for (int i = 0; i < normalized_corners.rows; ++i) {
            for (int j = 0; j < normalized_corners.cols; ++j) {
                if (static_cast<int>(normalized_corners.at<uchar>(i, j)) > 100) { // Threshold for corner response
                    cv::circle(frame, cv::Point(j, i), 3, cv::Scalar(0, 0, 255), cv::FILLED);
                }
            }
        }
        // Overlay the visualization image on top of the original frame
        cv::addWeighted(frame, 1, corners_visualization, 0.5, 0, frame);

        // Display the frame with corners
        cv::imshow("Frame with Harris Corners", frame);

        char key = cv::waitKey(1);
        if (key == 'q') { // Break the loop if the 'q' key is pressed
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
