#include <opencv2/opencv.hpp>

int main() {
    // Read an image
    cv::Mat inputImage = cv::imread("images1.jpg");

    if (inputImage.empty()) {
        std::cerr << "Error: Could not read the image." << std::endl;
        return -1;
    }

    // Create a greyscale version of the original image
    cv::Mat greyscaleCopy;
    cv::cvtColor(inputImage, greyscaleCopy, cv::COLOR_BGR2GRAY);

    // Iterate through each pixel
    for (int y = 0; y < inputImage.rows; ++y) {
        for (int x = 0; x < inputImage.cols; ++x) {
            // Check if the pixel is red (adjust the threshold as needed)
            if (inputImage.at<cv::Vec3b>(y, x)[0] < 50 && inputImage.at<cv::Vec3b>(y, x)[1] < 50 && inputImage.at<cv::Vec3b>(y, x)[2] > 100) {
                // Retain the red color
                greyscaleCopy.at<uchar>(y, x) = 255;  // Set to 0 to keep it black in greyscale
                inputImage.at<uchar>(y, x) = 255;

            }
        }
    }

    // Display the result
    cv::imshow("Result", greyscaleCopy);
    cv::waitKey(0);

    return 0;
}
