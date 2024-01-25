#include <opencv2/opencv.hpp>
#include "filter.cpp"

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
    cv::Mat frame, sobelXOutput, sobelYOutput;
    for (;;) {
        *capdev >> frame; // get a new frame from the camera, treat as a stream

        /*sobelX3x3(frame, sobelXOutput);
        sobelY3x3(frame, sobelYOutput);

        cv::convertScaleAbs(sobelXOutput, sobelXOutput);
        cv::convertScaleAbs(sobelYOutput, sobelYOutput);*/

        if (frame.empty()) {
            printf("frame is empty\n");
            break;
        }

        if (lastKey == 'g') {
            // Convert the frame to grayscale
            cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
        }
        else if (lastKey == 'h') {
            Customgreyscale (frame, frame);
        }
        else if (lastKey == 'i') {
          
            applySepiaTone(frame, frame);
            
        }
        else if (lastKey == 'x') {
            
            sobelX3x3(frame, sobelXOutput);
            cv::convertScaleAbs(sobelXOutput, sobelXOutput);
            cv::imshow("Sobel X", sobelXOutput);
            
        }
        else if (lastKey == 'y') {
            sobelY3x3(frame, sobelYOutput);
            cv::convertScaleAbs(sobelYOutput, sobelYOutput);
            cv::imshow("Sobel Y", sobelYOutput);
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
        else if (key == 'i' || key == 'c') {
            // Update lastKey based on user input
            lastKey = key;
        }
        else if (key == 'x' || key == 'c') {
            // Update lastKey based on user input
            lastKey = key;
        }
        else if (key == 'y' || key == 'c') {
            // Update lastKey based on user input
            lastKey = key;
        }
    }

    delete capdev;
    return (0);
}

