#include <opencv2\opencv.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv\cv.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Reading.h"
using namespace cv;
using namespace std;

/*int FindSmall(vector<int>Data)
{
	int Check, number, n;
	Check = Data[0];
	n = number = 0;
	for (n = 0; n < Data.size(); n++)
	{
		if (Check>Data[n])
		{
			Check = Data[n];
			number = n;
		}
	}
	return number;
}*/

double *Reading()
{
	double angle4;
	double MeasureAngle[2];
	//Videocapture process(Open camera)
	/*VideoCapture cap(0);
	if (!cap.isOpened())
	{
	return -1;
	}*/
	Mat frame, edges, gray, blurred, thres, LineImage; //define Mat variables for image storge
	frame = imread("E:/TEST/7.jpg", CV_LOAD_IMAGE_COLOR);// Open image from computer in color

		//cap >> frame; //Bring information from camera into variable
		cvtColor(frame, gray, CV_BGR2GRAY); //Convert image to gray
		imwrite("Gray.jpg",gray);
		//imshow("gray", gray);
		GaussianBlur(gray, blurred, Size(25, 25), 5); //Gaussiban Blur process
		imwrite("Blur.jpg", blurred);
		//imshow("blur", blurred);
		threshold(blurred, thres, 110, 255, THRESH_BINARY); //Thresholding process
		imwrite("thres.jpg", thres);
		//imshow("Thresholding", thres);
		Canny(thres, edges, 120, 360, 3); //Canny edge detection
		imwrite("edges1.jpg", edges);
		//imshow("Edge detction", edges);

		//Draw pointer edges by Probability Hough line process
		std::vector<Vec4i> lines;  //Define vector variable includes four numbers of every x and y 
		HoughLinesP(edges, lines, 1, CV_PI / 180, 25, 37, 30); //Probability Hough line
		for (size_t i = 0; i < lines.size(); i++) //Draw lines
		{
			Vec4i l = lines[i]; //Define variable for divide different lines
			line(edges, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 255, 255), 2, CV_AA); //Draw lines by start point and end point
			//cout << Point(l[0], l[1]) << " " << Point(l[2], l[3]) << endl;
		}
		//imshow("Image Detected", edges);
		imwrite("lines1.jpg", edges);
		//
		vector<int>DistanceShort;//Define vector variable to record distance between different points
		DistanceShort.push_back(pow(lines[0][0] - lines[1][0], 2) + pow(lines[0][1] - lines[1][1], 2));//Calculate distances by coordinates
		DistanceShort.push_back(pow(lines[0][0] - lines[1][2], 2) + pow(lines[0][1] - lines[1][3], 2));
		DistanceShort.push_back(pow(lines[0][2] - lines[1][0], 2) + pow(lines[0][3] - lines[1][1], 2));
		DistanceShort.push_back(pow(lines[0][2] - lines[1][2], 2) + pow(lines[0][3] - lines[1][3], 2));
		//
		vector<Vec4i>OppositePoints = lines;
		//Find two points which have smallest distance between each other
			int Check, number, n;
			Check = DistanceShort[0];
			n = number = 0;
			for (n = 0; n < DistanceShort.size(); n++)
			{
				if (Check>DistanceShort[n])
				{
					Check = DistanceShort[n];
					number = n;
				}
			}
			//cout << "The smallest distance is " << number << endl;
		switch (number)//Use smallest distance to find correct cases
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
		//cout << OppositePoints[1][0] << " " << OppositePoints[1][1] << " " << OppositePoints[1][2] << " " << OppositePoints[1][3] << endl;
		//cout << OppositePoints[0][0] << " " << OppositePoints[0][1] << " " << OppositePoints[0][2] << " " << OppositePoints[0][3] << endl;
		//Use atan2 to calculate angles
		MeasureAngle[0] = atan2(OppositePoints[0][3] - OppositePoints[0][1], OppositePoints[0][0] - OppositePoints[0][2]) * 180 / CV_PI;
		MeasureAngle[1] = atan2(OppositePoints[1][3] - OppositePoints[1][1], OppositePoints[1][0] - OppositePoints[1][2]) * 180 / CV_PI;
		angle4 = MeasureAngle[0] - MeasureAngle[1];//Calculate peak angle of meter hand
		//Judging whether the peak angle is in correct region 
		if (abs(angle4)>45)
		{
			cout << "The angles are" << MeasureAngle[0] << "and" << MeasureAngle[1] << "\n" << endl;
		}
		else if (angle4<36)
		{
			MeasureAngle[0] = atan2(OppositePoints[1][3] - OppositePoints[1][1], OppositePoints[1][0] - OppositePoints[1][2])*180 / CV_PI;
			MeasureAngle[1] = atan2(OppositePoints[0][3] - OppositePoints[0][1], OppositePoints[0][0] - OppositePoints[0][2])*180 / CV_PI;
			cout << "The angles are" << MeasureAngle[0] << "and" << MeasureAngle[1] << "\n" << endl;
		}
		else
			cout << "The angles are" << MeasureAngle[0] << "and" << MeasureAngle[1] << "\n" << endl;


	//cout << MeasureAngle << endl;
	return MeasureAngle;
}