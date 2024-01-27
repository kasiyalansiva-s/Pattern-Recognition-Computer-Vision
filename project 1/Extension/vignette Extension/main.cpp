// main.cpp 
// vignette filter

#include <iostream>
#include <opencv2/opencv.hpp>

#include "vignette.cpp"


int main() {
    // Open webcam
    cv::VideoCapture cap(0); // Use the default camera (you can change the index if you have multiple cameras)

    if (!cap.isOpened()) {
        std::cerr << "Error opening webcam." << std::endl;
        return -1;
    }

    while (true) {
        // Read a frame from the webcam
        cv::Mat frame;
        cap >> frame;

        if (frame.empty()) {
            std::cerr << "Error reading frame." << std::endl;
            break;
        }

        // Adjust vignette strength (reduce to half)
        double vignetteStrength = 0.15;

        // Apply the vignette effect
        applyVignette(frame, vignetteStrength);

        // Show the output
        cv::imshow("Webcam with Vignette", frame);

        // Write the frame to a file
        cv::imwrite("Output.jpg", frame);

        // Exit if 'q' is pressed
        if (cv::waitKey(10) == 'q') {
            break;
        }
    }

    // Release the webcam
    cap.release();

    return 0;
}
