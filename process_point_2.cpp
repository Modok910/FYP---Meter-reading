#include <opencv2\opencv.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv\cv.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>
#include <cstdlib>
#include <cmath>
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

int main()
{
	//Videocapture process(Open camera)
	/*VideoCapture cap(0);
	if (!cap.isOpened())
	{
	return -1;
	}*/
	Mat frame, edges, gray, blurred, thres, LineImage; //define Mat variables for image storge
	frame = imread("E:\TEST\6.jpg", CV_LOAD_IMAGE_COLOR);// Open image from computer in color

	bool stop = false;// Loop control define
	while (!stop)
	{
		//cap >> frame; //Bring information from camera into variable
  		cvtColor(frame, gray, CV_BGR2GRAY); //Convert image to gray
		//imwrite("Gray.jpg",gray);
		GaussianBlur(gray, blurred, Size(25, 25), 5); //Gaussiban Blur process
		//imwrite("Blur.jpg", blurred);
		threshold(blurred, thres, 110, 255, THRESH_BINARY); //Thresholding process
		//imwrite("thres.jpg", thres);
		Canny(thres, edges, 120, 360, 3); //Canny edge detection
		imwrite("edges1.jpg", edges);

		//Draw pointer edges by Probability Hough line process
		std::vector<Vec4i> lines;  //Define vector variable includes four numbers of every x and y 
		HoughLinesP(edges, lines, 1, CV_PI / 180, 20, 35, 30); //Probability Hough line
		for (size_t i = 0; i < lines.size(); i++) //Draw lines
		{
			Vec4i l = lines[i]; //Define variable for divide different lines
			line(edges, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 255, 255), 2, CV_AA); //Draw lines by start point and end point
			cout <<Point(l[0], l[1]) << " " << Point(l[2], l[3]) << endl;
		}
		imshow("Image Detected", edges);
		imwrite("lines1.jpg",edges);

		//
		vector<int>DistanceShort;
		DistanceShort.push_back(pow(lines[0][0] - lines[1][0], 2) + pow(lines[0][1] - lines[1][1], 2));
		DistanceShort.push_back(pow(lines[0][0] - lines[1][2], 2) + pow(lines[0][1] - lines[1][3], 2));
		DistanceShort.push_back(pow(lines[0][2] - lines[1][0], 2) + pow(lines[0][3] - lines[1][1], 2));
		DistanceShort.push_back(pow(lines[0][2] - lines[1][2], 2) + pow(lines[0][3] - lines[1][3], 2));
		cout << DistanceShort[0] << " " << DistanceShort[1] << " " << DistanceShort[2] << " " << DistanceShort[3] << endl;
		cout << "The smallest distance is " << FindSmall(DistanceShort) << endl;

		//
		vector<Vec4i>OppositePoints = lines;
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
		cout << OppositePoints[1][0] << " " << OppositePoints[1][1] << " " << OppositePoints[1][2] << " " << OppositePoints[1][3] << endl;
		cout << OppositePoints[0][0] << " " << OppositePoints[0][1] << " " << OppositePoints[0][2] << " " << OppositePoints[0][3] << endl;
		//
		double angle[2], value[3],angle4;
		angle[0] = atan2(OppositePoints[0][3] - OppositePoints[0][1],OppositePoints[0][0] - OppositePoints[0][2] ) * 180 / CV_PI;
		angle[1] = atan2(OppositePoints[1][3] - OppositePoints[1][1],OppositePoints[1][0] - OppositePoints[1][2] ) * 180 / CV_PI;
		angle4 = angle[0] - angle[1];

		/*if (angle4<36)
		{
			angle[0] = atan2(OppositePoints[1][3] - OppositePoints[1][1], OppositePoints[1][0] - OppositePoints[1][2]) * 180 / CV_PI;
			angle[1] = atan2(OppositePoints[0][3] - OppositePoints[0][1], OppositePoints[0][0] - OppositePoints[0][2]) * 180 / CV_PI;
			cout << "The angles are" << angle[0] << "and" << angle[1] << "\n" << endl;
		}
		else*/

		//value[0] = (angle[0] > 0) ? (10 - angle[0] / 36) : (-angle[0] / 36);
		//value[1] = (angle[1] > 0) ? (10 - angle[1] / 36) : (-angle[1] / 36);
		cout << "The angles are" << angle[0] << "and" << angle[1] <<"\n"<< endl;
		//cout << value[0] << " " << value[1] <<"\n"<< endl;
		//angle4 = angle[0]-(angle[0] - angle[1])/2;
		//cout << angle4 << endl;
		//value[2] = (angle4 > 0) ? (10 - angle4 / 36) : (-angle4 / 36);
		//cout << angle4 / 36 << endl;
		//cout << value[2] << endl;

		if (waitKey(5) >= 0)
			stop = true;
	}
	waitKey(0);
	return 0;
}