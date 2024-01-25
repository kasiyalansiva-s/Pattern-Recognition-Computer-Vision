#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/core.hpp>
#include "sobel_x_filter.cpp"
#include "sobel_y_filter.cpp"

int main(int argc, char* argv[]) {

	
	// Open a video capture object for camera
	cv::VideoCapture* capdev;
	capdev = new cv::VideoCapture(0);
	// Checking if the camera is opened successfully
	if (!capdev->isOpened()) {
		std::cerr << "Error : Could not open the camera. retry fixing the code" << std::endl;  // This prints out this error message if the camera is not opened
		return -1;
	}

	// getting some properties of the image
	// Creating a window to display the webcam live video in it
	cv::Size ref_frame((int)capdev->set(cv::CAP_PROP_FRAME_WIDTH, 640),    // setting the width for the frame
		capdev->set(cv::CAP_PROP_FRAME_HEIGHT, 480));                 // setting the height for the frame

	std::cout << "Expected size : " << ref_frame.width << " x " << ref_frame.height << std::endl;

	//cv::Mat RGB = cv::Mat(cv::Size())
	cv::namedWindow("video", cv::WINDOW_NORMAL); //  cv::namedWindow("Video", cv::WINDOW_NORMAL); // this is used to create a WINDOW_NORMAL flag that we can use to resize the window if needed in the future
	//// Define the codec and create a VideoWriter object for Sobel X output
	//int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');
	//VideoWriter sobelXwriter("SobelXOutput.avi", codec, 25, cv::Size(capdev->get(cv::CAP_PROP_FRAME_WIDTH), capdev->get(cv::CAP_PROP_FRAME_HEIGHT)), true);
	//VideoWriter sobelYwriter("SobelYOutput.avi", codec, 25, cv::Size(capdev->get(cv::CAP_PROP_FRAME_WIDTH), capdev->get(cv::CAP_PROP_FRAME_HEIGHT)), true);

	for (;;) {
		cv::Mat frame;
		*capdev >> frame;        // this gets a new frame from the webcam and treats it as a stream

		/*cv::Mat grayframe;
		grayframe = capdev->read();*/


		if (frame.empty()) {     // we are creatinhg a loop just to make sure the frame is noyt empty
			std::cout << " The Frame is empty\n";
			break;
		}
		cv::imshow("video", frame);
		char userInput = cv::waitKey(10);
		
		if (userInput == 'q') {
			break;
		}
		
		if (userInput == 'x') {
			cv::Mat dst;
			sobelX3x3(frame, dst);
			frame = dst;

			//for (;;) {
			//	sobelXoutput = cv::Mat::zeros(frame.size(), CV_16SC3);
			//	sobelX3x3(frame, sobelXoutput);
			//	cv::imshow("Sobel X Output", sobelXoutput);
			//	cv::imwrite("sobelx.jpeg", sobelXoutput);
			//	//cv::waitKey(0);
			//	//sobelXwriter.write(sx);
			//	char quit = cv::waitKey(10);
			//	if (quit == 'q') {
			//		cv::destroyAllWindows();
			//		break;
			//	}
			//}
			
			
			
			

		}
		if (userInput == 'y') {
			cv::Mat sobelYoutput;
			for (;;) {
				sobelYoutput = cv::Mat::zeros(frame.size(), CV_16SC3);
				sobelY3x3(frame, sobelYoutput);

				cv::imshow("Sobel Y Output", sobelYoutput);
				//cv::waitKey(0);
				//sobelYwriter.write(sy);
				cv::imwrite("sobely.jpeg", sobelYoutput);

				char quit = cv::waitKey(10);
				if (quit == 'q') {
					cv::destroyAllWindows();
					break;
				}
			}
			
			
			

		}

		//if (userInput == 's') {
		//	//save the current frame to a file
		//	cv::imwrite("Sobel X Output.jpg", sobelXOutput);  // using imread function to capture the frame and save it as "captured_frame.jpg" in the files

		//	std::cout << "Frame saved as Sobel X Output.mp4" << std::endl;           // Displays the image is captured and saved successfully to the files

		//	cv::imwrite("Sobel Y Output.jpg", sobelYOutput);
		//	
		//	std::cout << "Frame saved as Sobel Y Output.mp4" << std::endl;

		//}
	}
	//delete capdev;
	return 0;
	/*string path = "sobelx.jpeg";
	Mat sx = imread(path);
	imshow("Image", sx);

	string path = "sobely.jpeg";
	Mat sy = imread(path);
	imshow("Image", sy);*/

	/*while (true) {

	}*/



}