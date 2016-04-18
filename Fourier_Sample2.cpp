#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <stdint.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;
/// Global variables
Mat src, src_gray, canny_image, padded, good_f_t, threshold_image, lowerRect, imageROI, dst, detected_edges;
int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
char* window_name = "Edge Map";
void CannyThreshold(int, void*)
{
	GaussianBlur(src_gray, detected_edges, Size(25, 25), 5); //Gaussiban Blur process
	
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);
	dst = Scalar::all(0);
	src_gray.copyTo(dst, detected_edges);
	imshow(window_name, dst);
	Mat padded;
	int m = getOptimalDFTSize(dst.rows);
	int n = getOptimalDFTSize(dst.cols);
	copyMakeBorder(dst, padded, 0, m - dst.rows, 0, n - dst.cols, BORDER_CONSTANT, Scalar::all(0));
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexdst;
	merge(planes, 2, complexdst);
	dft(complexdst, complexdst);

	split(complexdst, planes);
	magnitude(planes[0], planes[1], planes[0]);
	Mat magdst = planes[0];
	magdst += Scalar::all(1);
	log(magdst, magdst);
	magdst = magdst(Rect(0, 0, magdst.cols & -2, magdst.rows & -2));
	int cx = magdst.cols / 2;
	int cy = magdst.rows / 2;
	Mat q0(magdst, Rect(0, 0, cx, cy));
	Mat q1(magdst, Rect(cx, 0, cx, cy));
	Mat q2(magdst, Rect(0, cy, cx, cy));
	Mat q3(magdst, Rect(cx, cy, cx, cy));
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	normalize(magdst, magdst, 0, 1, CV_MINMAX);
	imshow("spectrum magnitude", magdst);
}


int main(int argc, char** argv)
{
	src = imread("E:/c1.jpg");
	resize(src, src, Size(), 1, 1, INTER_LANCZOS4);

	if (!src.data)
	{
		return -1;
	}

	dst.create(src.size(), src.type());

	cvtColor(src, src_gray, CV_BGR2GRAY);

	namedWindow(window_name, CV_WINDOW_AUTOSIZE);

	createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);

	CannyThreshold(0, 0);

	waitKey(0);

	return 0;
}