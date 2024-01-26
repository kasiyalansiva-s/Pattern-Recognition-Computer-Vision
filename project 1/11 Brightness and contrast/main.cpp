// main.cpp
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>  // Don't forget to include this header

#include "filter.cpp"

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap(0);

    if (!cap.isOpened()) {
        cout << "Error opening video stream or file" << endl;
        return -1;
    }

    Mat frame, processedFrame;
    cap >> frame;

    if (frame.empty()) {
        cout << "Could not open or find the webcam stream!" << endl;
        return -1;
    }

    namedWindow("Original Frame", WINDOW_AUTOSIZE);

    namedWindow("Processed Frame", WINDOW_AUTOSIZE);

    double alpha = 0;
    int beta = 0;
    int alpha_slider = 50;
    int beta_slider = 50;
    createTrackbar("Contrast (Alpha)", "Processed Frame", &alpha_slider, 100);

    createTrackbar("Brightness (Beta)", "Processed Frame", &beta_slider, 100);


    while (true) {
        cap >> frame;

        if (frame.empty()) {
            cout << "End of video stream" << endl;
            break;
        }
        alpha = static_cast<double>(alpha_slider) / 50.0;

        beta = beta_slider - 50;

        applyFilter(frame, processedFrame, alpha, beta);

        imshow("Original Frame", frame);
        imshow("Processed Frame", processedFrame);

        if (waitKey(30) == 27) {
            cout << "Esc key is pressed by the user. Stopping the video stream." << endl;
            break;
        }
    }

    return 0;
}
