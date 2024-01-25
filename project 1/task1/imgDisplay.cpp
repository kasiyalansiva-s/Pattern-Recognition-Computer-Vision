//<opencv2/imgcodecs.hpp>
//nclude <opencv2/highgui.hpp>
//nclude <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  Images  //////////////////////

void main() {
    
    string path = "Resource/test.jpeg";
    Mat img = imread(path);
    imshow("Image", img);
    while (true) {
        char key = waitKey(0);
        if (key == 'q') {
            return;
        }else {

        }

    }
    

}
