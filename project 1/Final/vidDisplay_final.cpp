/*
  Saikiran Juttu & Suriya Kasiyalan Siva
  Spring 2024
  01/27/2024
  CS 5330 Computer Vision
*/
#include <opencv2/opencv.hpp>
#include "filter.h"
#include "filter.cpp"
#include "faceDetect.h"

int main(int argc, char* argv[]) {
    // Initialize Video Capture
    cv::VideoCapture* capdev;

    // Open the video device (camera)
    capdev = new cv::VideoCapture(0);
    if (!capdev->isOpened()) {
        printf("Unable to open video device\n");
        return (-1);
    }

    // Get video frame properties
    cv::Size refS((int)capdev->get(cv::CAP_PROP_FRAME_WIDTH),
                  (int)capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
    printf("Expected size: %d %d\n", refS.width, refS.height);

    // Create a named window for video display
    cv::namedWindow("Video", 1);

    // Mat object to store each video frame
    cv::Mat frame;
    char lastKey = 'c'; // Default to color display

    // Main processing loop
    for (;;) {
        *capdev >> frame; // Capture a new frame from the camera

        // Check if the frame is empty
        if (frame.empty()) {
            printf("frame is empty\n");
            break;
        }

        // Apply different filters based on user input
        if (lastKey == 'g') {
            // Convert the frame to grayscale
            cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
        }
        if (lastKey == 's') {
            // Save the current frame as an image
            cv::imwrite("image_saved.jpg", frame);
        }
        if (lastKey == 'h') {
            // Apply custom grayscale filter
            Customgreyscale(frame, frame);
        }
        if (lastKey == 't') {
            // Apply sepia tone filter
            applySepiaTone(frame, frame);
        }
        if (lastKey == 'i') {
            // Apply blur and quantize filter
            blurQuantize(frame, frame);
        }
        if (lastKey == 'b') {
            // Apply a 5x5 blur filter
            blur5x5_2(frame, frame);
        }
        if (lastKey == 'a') {
            // Apply brightness and contrast adjustment
            brightness_contrast(frame, frame);
        }
        if (lastKey == 'f') {
            // Apply brightness and contrast adjustment
            showFaces(frame, frame);
        }
        if (lastKey == 'x') {
            cv::Mat sobelXImage, displayXImage;

            sobelX3x3(frame, sobelXImage);

            cv::convertScaleAbs(sobelXImage, displayXImage);
            cv::imshow("Video1", displayXImage);

            cv::imwrite("Video1.jpg", displayXImage);


        }
        if (lastKey == 'y') {
            cv::Mat sobelYImage, displayYImage;
            sobelY3x3(frame, sobelYImage);
            cv::convertScaleAbs(sobelYImage, displayYImage);
            cv::imshow("Video2", displayYImage);

            cv::imwrite("Video2.jpg", displayYImage);
        }
        if (lastKey == 'm') {
            cv::Mat sobelXImage, sobelYImage, magnitudeImage;
            sobelX3x3(frame, sobelXImage);
            sobelY3x3(frame, sobelYImage);
            magnitude(sobelXImage, sobelYImage, magnitudeImage);
            cv::imwrite("Video3.jpg", magnitudeImage);
        }
        // Display the processed frame
        cv::imshow("Video", frame);

        // Check for a waiting keystroke
        char key = cv::waitKey(10);

        // User input handling
        if (key == 'q') {
            // Exit the program if 'q' is pressed
            break;
        } else if (key == 'g' || key == 'c' || key == 'h' || key == 't' || key == 'b' || key == 'i' || key == 's' || key == 'a'|| key == 'x' || key == 'y' || key == 'm') {
            // Update lastKey based on user input
            lastKey = key;
        }
    }

    // Release resources
    delete capdev;
    return (0);
}
