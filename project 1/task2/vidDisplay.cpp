#include <cstdio>                    // this is to call all the C++ input output libraries
#include <iostream>
#include <opencv2/opencv.hpp> // This header covers all the opencv functions 
#include "filter.cpp"

int main(int argc, char *argv[]) {

	// Task 4 prompt //
	//cv::VideoWriter grayscaleWriter("grayscale_output.avi", cv::VideoWriter::fourcc('X', 'V', 'I', 'D'), 30, cv::Size(640, 480), false);

	                 // * Here I used VideoWrite function to grayscale the live webcam stream and saving it in a variable named "grayscaleWriter".
	                 // * Naming the Output video file as "grayscale_output.avi".
	                 // * cv::VideoWriter::fourcc('X', 'V', 'I', 'D') : FourCC code representing the video codec
	                 // * the file is color (true) or grayscale (false). 
    
	// Task 4 prompt end here //




	// Open a video capture object for camera
	cv::VideoCapture *capdev;
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




    
	for (;;) {
		cv::Mat frame;
		*capdev >> frame;    
		// this gets a new frame from the webcam and treats it as a stream
        
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
		
		if (userInput == 'h') {
			cv::Mat greyscaleFrame;
			

			for (;;) {
				*capdev >> frame;
				greyscale(frame, greyscaleFrame);

				//cv::Mat greyscaleFrame;
				//greyscale(frame, greyscaleFrame);      // Display or use greyscaleFrame as needed
				cv::imshow("Greyscaled Frame", greyscaleFrame);
				char quit = cv::waitKey(10);
				if(quit == 'q') {
					cv::destroyAllWindows();
					break;
				}
			}
			
		}

	 //   if (key == 's') {
		//		//save the current frame to a file
		//	cv::imwrite("captured_frame.jpg", frame);       // using imread function to capture the frame and save it as "captured_frame.jpg" in the files
		//	std::cout << "Frame saved as captured_frame.jpg" << std::endl;           // Displays the image is captured and saved successfully to the files
		//}
		if (userInput == 'g') {
			cv::Mat newgrayscale;
			for (;;) {
				*capdev >> frame;
				cv::cvtColor(frame, newgrayscale, cv::COLOR_BGR2GRAY);


				// DISPLAY GRAYSCALE FRAME
				cv::imshow("Grayscale Webcam", newgrayscale);
				char quit = cv::waitKey(10);
				if (quit == 'q') {
					cv::destroyAllWindows();
					break;
				}
			}
			

			// Write the grayscale frame to video file
			//grayscaleWriter.write(grayscaleFrame);
			//cv::waitKey(1) == 27;


		}
		if (userInput == 's') {
			//save the current frame to a file
			cv::imwrite("captured_frame.jpg", frame);       // using imread function to capture the frame and save it as "captured_frame.jpg" in the files

			std::cout << "Frame saved as captured_frame.jpg" << std::endl;           // Displays the image is captured and saved successfully to the files

			cv::cvtColor(frame, frame, cv::COLOR_RGB2GRAY);

			cv::imwrite("grayscale_image.jpeg", frame);

			std::cout << "Frame saved as grayscale_image.jpeg" << std::endl;

		}
		
		
		

	}return 0;


}
