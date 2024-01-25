#include <iostream>
#include <opencv2/opencv.hpp>
#include "blur5x5_1.cpp"
#include "blur5x5_2.cpp"
#include <chrono>

double getTime() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto duration = currentTime.time_since_epoch();

    // Extract seconds and microseconds
    long seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration).count() % 1000000;

    return seconds + microseconds / 1000000.0;
}


int main() {
    // Replace "your_image.jpg" with the path to your input image
    cv::Mat src = cv::imread("cathedral.jpeg");
    std::cout << "Width : " << src.cols << std::endl;
    std::cout << "Height: " << src.rows << std::endl;
    cv::Mat dst;
    if (src.empty()) {
        std::cerr << "Error loading image." << std::endl;
        return -1;
    }
    const int Ntimes = 25;
    double startTime1 = getTime();
    for (int i = 0; i < Ntimes; i++) {
        blur5x5_1(src, dst);
    }
    // end the timing
    double endTime1 = getTime();

    // compute the time per image
    double difference1 = (endTime1 - startTime1) / Ntimes;

    // print the results
    printf("Time per image (1): %.4lf seconds\n", difference1);
    // Save the result
    std::cout << "Width : " << dst.cols << std::endl;
    std::cout << "Height: " << dst.rows << std::endl;
    cv::imwrite("2D_blur_result.jpg", dst);
    cv::imshow("2D_blur_result.jpg", dst);
    
    double startTime2 = getTime();
    for (int i = 0; i < Ntimes; i++) {
      
        blur5x5_2(src, dst);
        
    }
    //end the timing
    double endTime2 = getTime();

    //compute the time per image
    double difference2 = (endTime2 - startTime2) / Ntimes;

    //print the results
    printf("Time per image (1): %.4lf seconds\n", difference2);
    //Save the result
    std::cout << "Width : " << dst.cols << std::endl;
    std::cout << "Height: " << dst.rows << std::endl;
    cv::imwrite("separable_blur_result.jpg", dst);
    cv::imshow("separable_blur_result.jpg", dst);
    cv::waitKey(0);
    return 0;
    
}