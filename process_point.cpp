
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
using namespace cv;
using namespace std;

int FindSmall(vector<int>Data)
{
	int Check, number, n;
	Check = Data[0];
	n=number = 0;
	for (n = 0; n < Data.size(); n++)
	{
		if (Check>Data[n])
		{
			Check = Data[n];
			number = n;
		}
	}
	return number;
}

int main(int argc, char** argv)
{
	//Videocapture process(Open camera)
	/*VideoCapture cap(0);
	if (!cap.isOpened())
	{
	return -1;
	}*/
	cv::Mat frame, edges, gray, blurred, thres, LineImage; //define Mat variables for image storge
	frame = cv::imread(argv[1],0);// Open image from computer in color
        if (frame.empty())
           {
            std::cout<<"Loading error"<<std::endl;
            return -1;
           }

	bool stop = false;// Loop control define
	while (!stop)
	{
		//cap >> frame; //Bring information from camera into variable
		gray=frame.clone();

                //cv::cvtColor(frame, gray, CV_BGR2GRAY); //Convert image to gray
		//imwrite("Gray.jpg",gray);
		cv::GaussianBlur(gray, blurred, cv::Size(25, 25), 5); //Gaussiban Blur process
		//imwrite("Blur.jpg", blurred);
		cv::threshold(blurred, thres, 110, 255, THRESH_BINARY); //Thresholding process
		//imwrite("thres.jpg", thres);
		cv::Canny(thres, edges, 120, 360, 3); //Canny edge detection
		//cvSaveImage("edges1.jpg", edges);

		//Draw pointer edges by Probability Hough line process
		std::vector<cv::Vec4i> lines;  //Define vector variable includes four numbers of every x and y 
		HoughLinesP(edges, lines, 1, CV_PI / 180, 20, 35, 30); //Probability Hough line
		for (size_t i = 0; i < lines.size(); i++) //Draw lines
		{
			cv::Vec4i l = lines[i]; //Define variable for divide different lines
			cv::line(edges, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(255, 255, 255), 2, CV_AA); //Draw lines by start point and end point
			std::cout <<Point(l[0], l[1]) << " " << Point(l[2], l[3]) << std::endl;
		}
                //cv::Mat* edgepointer=&edges;
		//cvShowImage("Image Detected", static_cast<CvArr*>(edgepointer));
		//cvSaveImage("lines1.jpg",edges);
                  cv:imshow("Image",edges);
		//
		std::vector<int>DistanceShort;
		DistanceShort.push_back(pow(lines[0][0] - lines[1][0], 2) + pow(lines[0][1] - lines[1][1], 2));
		DistanceShort.push_back(pow(lines[0][0] - lines[1][2], 2) + pow(lines[0][1] - lines[1][3], 2));
		DistanceShort.push_back(pow(lines[0][2] - lines[1][0], 2) + pow(lines[0][3] - lines[1][1], 2));
		DistanceShort.push_back(pow(lines[0][2] - lines[1][2], 2) + pow(lines[0][3] - lines[1][3], 2));
		std::cout << DistanceShort[0] << " " << DistanceShort[1] << " " << DistanceShort[2] << " " << DistanceShort[3] << std::endl;
		std::cout << "The smallest distance is " << FindSmall(DistanceShort) << std::endl;

		//
		std::vector<cv::Vec4i>OppositePoints = lines;
		switch (FindSmall(DistanceShort))
		{
		case 0:
			break;
		case 1:
			OppositePoints[1][0] = lines[1][2];
			OppositePoints[1][1] = lines[1][3];
			OppositePoints[1][2] = lines[1][0];
			OppositePoints[1][3] = lines[1][1];
			break;
		case 2:
			OppositePoints[0][0] = lines[0][2];
			OppositePoints[0][1] = lines[0][3];
			OppositePoints[0][2] = lines[0][0];
			OppositePoints[0][3] = lines[0][1];
			break;
		case 3:
			OppositePoints[1][0] = lines[1][2];
			OppositePoints[1][1] = lines[1][3];
			OppositePoints[1][2] = lines[1][0];
			OppositePoints[1][3] = lines[1][1];
			OppositePoints[0][0] = lines[0][2];
			OppositePoints[0][1] = lines[0][3];
			OppositePoints[0][2] = lines[0][0];
			OppositePoints[0][3] = lines[0][1];
			break;
		}
		std::cout << OppositePoints[1][0] << " " << OppositePoints[1][1] << " " << OppositePoints[1][2] << " " << OppositePoints[1][3] << std::endl;
		std::cout << OppositePoints[0][0] << " " << OppositePoints[0][1] << " " << OppositePoints[0][2] << " " << OppositePoints[0][3] << std::endl;
		//
		double angle[2], value[3],angle4;
		angle[0] = atan2(OppositePoints[0][3] - OppositePoints[0][1],OppositePoints[0][0] - OppositePoints[0][2] ) * 180 / CV_PI;
		angle[1] = atan2(OppositePoints[1][3] - OppositePoints[1][1],OppositePoints[1][0] - OppositePoints[1][2] ) * 180 / CV_PI;
		angle4 = angle[0] - angle[1];
		std::cout << angle4 << std::endl;

		
		if (abs(angle4)>45)
		{
			std::cout << "The angles are" << angle[0] << "and" << angle[1] << "\n" << std::endl;
		}
		else if (angle4<36)
		{
		angle[0] = atan2(OppositePoints[1][3] - OppositePoints[1][1], OppositePoints[1][0] - OppositePoints[1][2]) * 180 / CV_PI;
		angle[1] = atan2(OppositePoints[0][3] - OppositePoints[0][1], OppositePoints[0][0] - OppositePoints[0][2]) * 180 / CV_PI;
		std::cout << "The angles are" << angle[0] << "and" << angle[1] << "\n" << std::endl;
		}
		else 
		//value[0] = (angle[0] > 0) ? (10 - angle[0] / 36) : (-angle[0] / 36);
		//value[1] = (angle[1] > 0) ? (10 - angle[1] / 36) : (-angle[1] / 36);
		std::cout << "The angles are" << angle[0] << "and" << angle[1] <<"\n"<< std::endl;
		//cout << value[0] << " " << value[1] <<"\n"<< endl;
		//angle4 = angle[0]-(angle[0] - angle[1])/2;
		//cout << angle4 << endl;
		//value[2] = (angle4 > 0) ? (10 - angle4 / 36) : (-angle4 / 36);
		//cout << angle4 / 36 << endl;
		//cout << value[2] << endl;

		if (cvWaitKey(5) >= 0)
			stop = true;
	}
	cvWaitKey(0);
	return 0;
}

