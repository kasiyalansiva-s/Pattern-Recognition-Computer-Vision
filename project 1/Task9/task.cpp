#include <iostream>
#include <opencv2/opencv.hpp>

int blurQuantize(cv::Mat& src, cv::Mat& dst, int levels) {
    // Clone the source image to the destination
    dst = src.clone();

    // Blur the image
    cv::GaussianBlur(src, dst, cv::Size(5, 5), 0);

    // Quantize the image
    int b = 255 / levels;
    for (int y = 0; y < dst.rows; y++) {
        for (int x = 0; x < dst.cols; x++) {
            for (int c = 0; c < 3; c++) {  // 3 channels (BGR)
                int xt = dst.at<cv::Vec3b>(y, x)[c] / b;
                int xf = xt * b;
                dst.at<cv::Vec3b>(y, x)[c] = xf;
            }
        }
    }

    return 0;  // Success
}

int main() {
    // Load the image
    cv::Mat image = cv::imread("cathedral.jpeg");

    // Check if the image is loaded successfully
    if (image.empty()) {
        std::cerr << "Error: Could not read the image." << std::endl;
        return -1;
    }

    // Display the original image
    cv::imshow("Original Image", image);

    // Blur and quantize the image
    cv::Mat blurredQuantizedImage;
    int levels = 10;  // You can change this value as needed
    blurQuantize(image, blurredQuantizedImage, levels);

    // Display the blurred and quantized image
    cv::imshow("Blurred and Quantized Image", blurredQuantizedImage);

    // Wait for a key press
    cv::waitKey(0);

    return 0;
}
