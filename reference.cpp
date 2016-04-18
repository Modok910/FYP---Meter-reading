#include <opencv2\opencv.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv\cv.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>
using namespace cv;


int main()
{
/*	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		return -1;
	}*/
	Mat frame, edges, gray, blurred, thres;
	frame = imread("E:/c2.jpg", CV_LOAD_IMAGE_COLOR);
	bool stop = false;
	while (!stop)
	{
		//cap >> frame;
		cvtColor(frame, gray, CV_BGR2GRAY);
		GaussianBlur(gray, blurred, Size(17, 17), 5);
		threshold(blurred, thres, 105, 255, THRESH_BINARY);
		//Canny(thres, edges, 120, 360, 3);
		imwrite("E:/reference.jpg", thres);
		namedWindow("Image Detected", CV_WINDOW_AUTOSIZE);
		imshow("Image Detected", thres);
		if (waitKey(30) >= 0)
			stop = true;
	}
	waitKey(0);
	return 0;
}