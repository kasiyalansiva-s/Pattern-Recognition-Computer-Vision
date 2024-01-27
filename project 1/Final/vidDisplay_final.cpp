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
    cv::VideoCapture* capdev;

    // open the video device
    capdev = new cv::VideoCapture(0);
    if (!capdev->isOpened()) {
        printf("Unable to open video device\n");
        return (-1);
    }

    // get some properties of the image
    cv::Size refS((int)capdev->get(cv::CAP_PROP_FRAME_WIDTH),
        (int)capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
    printf("Expected size: %d %d\n", refS.width, refS.height);

    cv::namedWindow("Video", 1); // identifies a window
    cv::Mat frame;
    char lastKey = 'c'; // Default to color display

    for (;;) {
        *capdev >> frame; // get a new frame from the camera, treat as a stream
        if (frame.empty()) {
            printf("frame is empty\n");
            break;
        }

        if (lastKey == 'g') {
            // Convert the frame to grayscale
            cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
        }
        if (lastKey == 's') {
            cv::imwrite("image saved2.jpg", frame);
        }
        if (lastKey == 'h') {
            Customgreyscale(frame, frame);
        }
        if (lastKey == 't') {
            applySepiaTone(frame, frame);
        }
        if (lastKey == 'i') {
            blurQuantize(frame, frame);
        }
        if (lastKey == 'b') {
            blur5x5_2(frame, frame);
        }
        if (lastKey == 'a') {
            brightness_contrast(frame, frame);
        }
        
        cv::imshow("Video", frame);

        // see if there is a waiting keystroke
        char key = cv::waitKey(10);

        if (key == 'q') {
            break;
        }
        else if (key == 'g' || key == 'c') {
            // Update lastKey based on user input
            lastKey = key;
        }
        else if (key == 'h' || key == 'c') {
            // Update lastKey based on user input
            lastKey = key;
        }
        else if (key == 't' || key == 'c') {
            // Update lastKey based on user input
            lastKey = key;
        }
        else if (key == 'b' || key == 'c') {
            // Update lastKey based on user input
            lastKey = key;
        }
        else if (key == 'i' || key == 'c') {
            // Update lastKey based on user input
            lastKey = key;
        }
        else if (key == 's' || key == 'c') {
            // Update lastKey based on user input
            lastKey = key;
        }

        //else if (key == 'a' || key == 'c') {
        //    // Update lastKey based on user input
        //    lastKey = key;
        //}
    }

    delete capdev;
    return (0);
}
