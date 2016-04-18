#include <opencv2\opencv.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv\cv.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Reading.h"
#include "Comparing.h"
using namespace cv;
using namespace std;

void main()
{
	double *ReceiveAngle1; //Define variable to transfer reading results
	double ReceiveAngle2[2]; //Define variable to store results respectively for comparing
	//double OutNumber;
	//int ReadNumber;
	ReceiveAngle1=Reading();//Reading results
	ReceiveAngle2[0] = ReceiveAngle1[0];
	ReceiveAngle2[1] = ReceiveAngle1[1];
	//ReceiveAngle1->ReceiveAngle2[2];
	//cout << ReceiveAngle1 << endl;
	//cout << ReceiveAngle2[0] << endl;
	//cout << ReceiveAngle2[1]<< endl;
	Comparing(ReceiveAngle2[0],ReceiveAngle2[1]); //Comparing process
}