#include <opencv2\opencv.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv\cv.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace cv;
using namespace std;


int main()
{
	//Videocapture process(Open camera)
	/*VideoCapture cap(0);
	if (!cap.isOpened())
	{
		return -1;
	}*/
	Mat frame, edges, gray, blurred, thres,LineImage; //define Mat variables for image storge
	frame = imread("E:/c1.jpg", CV_LOAD_IMAGE_COLOR);// Open image from computer in color

	bool stop = false;// Loop control define
	while (!stop)
	{
		//cap >> frame; //Bring information from camera into variable
		cvtColor(frame, gray, CV_BGR2GRAY); //Convert image to gray
		GaussianBlur(gray, blurred, Size(25, 25), 5); //Gaussiban Blur process
		threshold(blurred, thres, 110, 255, THRESH_BINARY); //Thresholding process
		Canny(thres, edges, 120, 360, 3); //Canny edge detection
		
		// Draw pointer edges by standard Hough line process
		/*vector<Vec2f>lines; //Define vector variable, which include distance rho and angle theta.
		HoughLines(edges, lines, 1, CV_PI / 180, 32.5, 0, 0); //Standard Hough line process
		for (size_t i = 0; i < lines.size(); i++) //Draw lines
		{
			float rho = lines[i][0], theta = lines[i][1]; //Load rho and theta
			Point pt1, pt2; //Define start and end point of one line
			double a = cos(theta), b = sin(theta); //Calculate parameters of x and y
			double x0 = a*rho, y0 = b*rho; //Calculate the nearest point with zero point in the line
			pt1.x = cvRound(x0 + 1000 * (-b)); //Calculate x1 and y1
			pt1.y = cvRound(y0 + 1000 * (a));
			pt2.x = cvRound(x0 - 1000 * (-b)); //Calculate x2 and y2
			pt2.y = cvRound(y0 - 1000 * (a));
			line(edges, pt1, pt2, Scalar(255, 0, 0), 2, CV_AA); //Draw calculated line
			cout << pt1 <<" "<< pt2 << endl;
		}*/
		
		//Draw pointer edges by Probability Hough line process
		std::vector<Vec4i> lines;  //Define vector variable includes four numbers of every x and y 
		HoughLinesP(edges, lines, 1, CV_PI/180, 30, 40, 30 ); //Probability Hough line
		for( size_t i = 0; i < lines.size(); i++ ) //Draw lines
		{
		Vec4i l = lines[i]; //Define variable for divide different lines
		line(edges, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,255,255), 2, CV_AA); //Draw lines by start point and end point
		cout << Point(l[0], l[1]) << " " << Point(l[2], l[3]) << endl;
		}


		//imwrite("E:/r.jpg", edges);
		//namedWindow("Image Detected", CV_WINDOW_AUTOSIZE);
		

//		if (lines.size() == 3){
//			cout << "Found three angels:" << endl;
//			cout << lines[0][1] * 180 / CV_PI << endl << lines[1][1] * 180 / CV_PI << endl << lines[2][1] * 180 / CV_PI << endl << endl;
//		}
			
		//Find the proper angel from the three found angels
		






		float angel1=0, angle2=0;
		float piThresh = (float)CV_PI / 90;
		float pi2 = CV_PI / 2;
		
		
		float t1 = lines[0][0],t2=lines[0][1],t3=lines[0][2],t4=lines[0][3];
		float x01 = (t1 + t3) / 2, y01 = (t2 + t4) / 2;
		float TanTheta1 = y01 / x01;
			cout << t1 << " " << t2 << " " << t3 << " " << t4 << " " <<TanTheta1<< endl;
			float theta1 = atan(TanTheta1);
			cout << theta1 << endl;
			if (abs(theta1) < piThresh || abs(theta1 - pi2) < piThresh)
				;
			else{
				angel1 = theta1;	
			}
			angel1 = angel1<pi2 ? angel1 : angel1 - CV_PI;
			cout << angel1 << endl;
			if (angel1 != pi2){
				float angelT = edges.rows*tan(angel1) /  edges.cols;
				cout << edges.rows / edges.cols << endl;
				angel1 = atan(angelT);
				cout << angel1 << endl;
			}
			float angleD = angel1 * 180 / (float)CV_PI;
			cout << "the angel 0 of the pointer to be applied:" << endl << angleD << endl << endl;

			float g1 = lines[1][0], g2 = lines[1][1], g3 = lines[1][2], g4 = lines[1][3];
			float x02 = (g1 + g3) / 2, y02 = (g2 + g4) / 2;
			float TanTheta2 = y02 / x02;
			float theta2 = atan(TanTheta2);
			cout << theta2 << endl;
			if (abs(theta2) < piThresh || abs(theta2 - pi2) < piThresh) //Compare with 90 degrees, check whether the line has angle change
				;
			else{
				angle2 = theta2; 
			}
			angle2 = angle2<pi2 ? angle2 : angle2 - CV_PI; //Check the angle is smaller than 90 or larger than 90
			cout << angle2 << endl;
			if (angle2 != pi2){
				float angelT = edges.rows*tan(angle2) / edges.cols; //Ensure calculation based on the size of row and column
				angle2 = atan(angelT); //arctan function to receive angle
				cout << angle2 << endl;
			}
			float angleD2 = angle2 * 180 / (float)CV_PI; //Convert angle from radians to degrees
			cout << "the angel 1 of the pointer to be applied:" << endl << angleD2 << endl << endl;


			float HalfPointer = (angleD2 - angleD) / 2;
			float Fxx = 180 - (angleD2 / 2) - (angleD / 2);
			cout << HalfPointer << " " << Fxx << endl;
			imshow("Image Detected", edges);
			//imwrite("E:/angle.jpg", edges);
		if (waitKey(5) >= 0)
			stop = true;
	}
	waitKey(0);
	return 0;
}