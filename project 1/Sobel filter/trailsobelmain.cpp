#include <iostream>
#include <opencv2/opencv.hpp>
#include "sobelx_yfilter.cpp"

int main(int argc, char* argv[]) {
    cv::VideoCapture* capdev;

    // open the video device
    capdev = new cv::VideoCapture(0);
    if (!capdev->isOpened()) {
        printf("Unable to open video device\n");
        return(-1);
    }

    // get some properties of the image
    cv::Size refS((int)capdev->get(cv::CAP_PROP_FRAME_WIDTH),
        (int)capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
    printf("Expected size: %d %d\n", refS.width, refS.height);

    cv::namedWindow("Video", 1); // identifies a window
    /*cv::Mat frame;*/

    while (true) {
        cv::Mat frame;
        *capdev >> frame;        // this gets a new frame from the webcam and treats it as a stream 
        if (frame.empty()) {     // we are creatinhg a loop just to make sure the frame is noyt empty
            std::cout << " The Frame is empty\n";
            break;
        }
        //cv::imshow("video", frame);
        //char userInput = cv::waitKey(10);

        
        //if (userInput == 'x') {
        //    // Create an image to store the Sobel X output
        //    Mat sobelXOutput = Mat::zeros(frame.size(), CV_16SC3);
        //    // Apply Sobel X filter
        //    sobelX3x3(frame, sobelXOutput);
        //    // Display Sobel X outputs
        //    namedWindow("Sobel X Output", WINDOW_AUTOSIZE);
        //    imshow("Sobel X Output", sobelXOutput);
        //    //imwrite("Sobel X Output.avi", sobelXOutput);
        //    //waitKey(0);
        //    /*while (true) {
        //        

        //    }return 0;*/
        //  }
       
        // Create an image to store the Sobel X output
        Mat sobelXOutput = Mat::zeros(frame.size(), CV_16SC3);
        // Apply Sobel X filter
        sobelX3x3(frame, sobelXOutput);
        // Display Sobel X outputs
        namedWindow("Sobel X Output", WINDOW_AUTOSIZE);
        imshow("Sobel X Output", sobelXOutput);


        //if (userInput == 'y') {
        //    // Create an image to store the Sobel Y output
        //    Mat sobelYOutput = Mat::zeros(frame.size(), CV_16SC3);


        //    // Apply Sobel Y filter
        //    sobelY3x3(frame, sobelYOutput);

        //    namedWindow("Sobel Y Output", WINDOW_AUTOSIZE);

        //    imshow("Sobel Y Output", sobelYOutput);
        //    //imwrite("Sobel Y Output.avi", sobelYOutput);
        //    //waitKey(0);
        //    /*while (true) {
        //            

        //    }return 0;*/
        //  }
        if (userInput == 'q') {
            break;
        }
            

           

            
        

    }
    return 0;
}
