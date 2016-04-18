#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include "Comparing.h"
using namespace std;
double Comparing(double x,double y)
{

	int nx=0;//Define variable of reading number
	if (170 <= x &&x<= 180 && 130 <= y &&y<= 145) //Comparing calculated angles to find reading numbers
	{
		nx = 8;
		cout << "The number is "<<nx << endl;
	}
	else if (135 <= x&&x <= 145 && 95 <= y&&y <= 110)
	{
		nx = 9;
		cout << "The number is " << nx << endl;
	}
	else if (90 < x&&x < 110 && 50 < y&&y < 80)
	{
		 nx = 0;
		 cout << "The number is " << nx << endl;
	}	
	else if (65 <= x&&x <= 80 && 30 <= y&&y <= 40)
	{
		nx = 1;
		cout << "The number is " << nx << endl;
	}
	else if (35 <= x&&x <= 50 && -5 <= y&&y <= 10)
	{
		nx = 2;
		cout << "The number is " << nx << endl;
	}
	else if (0 <= x&&x <= 10 && -40 <= y&&y <= -30)
	{
		nx = 3;
		cout << "The number is " << nx << endl;
	}
	else if (-35 <= x&&x <= -20 && -75 <= y&&y <= -60)
	{
		nx = 4;
		cout << "The number is " << nx << endl;
	}
	else if (-75 <= x&&x <= -60 && -115 <= y &&y <= -100)
	{
		nx = 5;
		cout << "The number is " << nx << endl;
	}
	else if (-120 <= x&&x <= -105 && -155 <= y&&y <= -140)
	{
		nx = 6;
		cout << "The number is " << nx << endl;
	}
	else if (-155 <= x&&x <= -145 && 170 <= y&&y <= 180)
	{
		nx = 7;
		cout << "The number is " << nx << endl;
	}
	ofstream file;
	file.open("result.txt");
	file << nx;
	file.close();	
	return 0;
}

