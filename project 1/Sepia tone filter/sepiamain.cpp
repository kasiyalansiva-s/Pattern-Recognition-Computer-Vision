#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // Read image
    cv::Mat img = cv::imread("Image.jpg");

    if (img.empty()) {
        std::cerr << "Error reading image file." << std::endl;
        return -1;
    }

    cv::Size newsize(750, 497);

    cv::resize(img, img, newsize);


    // Get image dimensions
    int width = img.cols;
    int height = img.rows;
    
    // Convert to sepia with vignetting
    double vignetteStrength = 0.3;   //Adjust this value for the strength of vignetting //

    // Convert to sepia
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            cv::Vec3b& pixel = img.at<cv::Vec3b>(y, x);

            // Extract color channels
            int r = pixel[2];
            int g = pixel[1];
            int b = pixel[0];

            // Calculate new color values
            int tb = static_cast<int>(0.272 * r + 0.534 * g + 0.131 * b);
            int tg = static_cast<int>(0.349 * r + 0.686 * g + 0.168 * b);
            int tr = static_cast<int>(0.393 * r + 0.769 * g + 0.189 * b);

            // Calculate vignetting effect
            double vignette = pow((1.0 - sqrt(pow((x - width / 2.0) / (width / 2.0), 2) + pow((y - height / 2.0) / (height / 2.0), 2))), vignetteStrength);

            // Apply vignetting
            tr *= vignette;
            tg *= vignette;
            tb *= vignette;

            // Check conditions and set new values
            pixel[2] = (tr > 255) ? 255 : tr;
            pixel[1] = (tg > 255) ? 255 : tg;
            pixel[0] = (tb > 255) ? 255 : tb;
        }
    }

    


    while (true) {
        
        cv::imshow("Output", img);

        cv::waitKey(10);


        // Write image
        cv::imwrite("Output.jpg", img);
        if (cv::waitKey(10) == 'q') {
            break;
        }

    }
    //cv::imshow("Output", img);
    //cv::waitKey(10);

    //// Write image
    //cv::imwrite("Output.jpg", img);

    return 0;
}
