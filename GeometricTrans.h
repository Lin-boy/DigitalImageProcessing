#pragma once

#include "stdafx.h"
#include <iostream>   
#include "opencv2/core/core.hpp"   
#include "opencv2/highgui/highgui.hpp"   

using namespace std;
using namespace cv;

#define PI 3.14159265

Mat translation(Mat inputimage, int x, int y);

Mat scale(Mat inputImage, double factor);


Mat Rotation(Mat inputImage, double rotationDegree, int x, int y);



Mat translation(Mat inputimage, int x, int y) {
	cout << "Translating...\n";
	cout << "Translation in x-axis:" << x << ",";
	cout << "Translation in y-axis:" << y << "\n";
	int r = inputimage.rows; int c = inputimage.cols;
	Mat final = Mat(inputimage.rows, inputimage.cols, CV_8UC3, Scalar(0, 0, 0));

	for (int i = 0; i < r - y; i++)
	{
		for (int j = 0; j < c - x; j++)
		{
			final.at<Vec3b>(i + y, j + x)[0] = inputimage.at<Vec3b>(i, j)[0];
			final.at<Vec3b>(i + y, j + x)[1] = inputimage.at<Vec3b>(i, j)[1];
			final.at<Vec3b>(i + y, j + x)[2] = inputimage.at<Vec3b>(i, j)[2];
		}
	}
	return final;
}



Mat scale(Mat inputImage, double factor) {
	cout << "Scaling...\n";
	cout << "Scale factor: " << factor << "\n";
	int r_factor, c_factor;
	r_factor = int(factor*inputImage.rows);
	c_factor = int(factor*inputImage.cols);

	Mat final = Mat(r_factor, c_factor, CV_8UC3, Scalar(0, 0, 0));

	cout << "Old Size: " << inputImage.rows << "x" << inputImage.cols << endl;
	cout << "New Size: " << r_factor << "x" << c_factor << endl;

	if (factor > 1.0)
		//If factor > 1.0, the image is enlarged.
	{

		//DST[r*(W*factor) + c] = SRC[(r/factor)*W + c/factor]

		for (int i = 0; i < r_factor; i++)
		{
			for (int j = 0; j < c_factor; j++)
			{
				final.at<Vec3b>(i, j)[0] = inputImage.at<Vec3b>(int(i / factor), int(j / factor))[0];
				final.at<Vec3b>(i, j)[1] = inputImage.at<Vec3b>(int(i / factor), int(j / factor))[1];
				final.at<Vec3b>(i, j)[2] = inputImage.at<Vec3b>(int(i / factor), int(j / factor))[2];
			}
		}
	}

	else if (factor < 1.0)
		//If factor < 1.0, the image is shrinked.
	{

		//DST[(r/factor)*W + c/factor] = SRC[r*W + c]

		for (int i = 0; i < inputImage.rows; i++)
		{
			for (int j = 0; j < inputImage.cols; j++)
			{
				final.at<Vec3b>((int)i*factor, (int)j*factor)[0] = inputImage.at<Vec3b>(i, j)[0];
				final.at<Vec3b>((int)i*factor, (int)j*factor)[1] = inputImage.at<Vec3b>(i, j)[1];
				final.at<Vec3b>((int)i*factor, (int)j*factor)[2] = inputImage.at<Vec3b>(i, j)[2];
			}
		}

	}
	else {
		inputImage.copyTo(final);
	}
	return final;
}



//Mat Rotation(Mat inputImage, double rotationDegree, int x, int y) {
//	cout << "Rotating....\n" << "Rotation degree:" << rotationDegree << "°" << "\n";
//
//	Mat outputImage = Mat(inputImage.rows, inputImage.cols, CV_8UC3, Scalar(0, 0, 0));
//	int newX, newY;
//	int ox, oy;
//	double COS, SIN;
//	if (x == -1 && y == -1)
//	{
//		cout << "Rotating center in the center of the picture\n";
//		ox = (inputImage.rows - 1) / 2;
//		oy = (inputImage.cols - 1) / 2;
//	}
//	else
//	{
//		cout << "Rotating center " << x << "，" << y;
//		ox = x;
//		oy = y;
//	}
//
//	int nx2, ny2;
//
//	SIN = sin(rotationDegree * PI / 180.0), COS = cos(rotationDegree * PI / 180.0);
//
//	for (int i = 0; i < inputImage.rows; i++)
//	{
//		for (int j = 0; j < inputImage.cols; j++)
//		{
//
//			nx2 = i - ox, ny2 = j - oy;
//
//			newX = (int)(nx2 * COS + ny2 * SIN + 0.5 + ox);
//			newY = (int)(-nx2 * SIN + ny2 * COS + 0.5 + oy);
//
//			if (newY >= 0 && newY < inputImage.cols && newX >= 0 && newX < inputImage.rows)
//			{
//				outputImage.at<Vec3b>(i, j)[0] = inputImage.at<Vec3b>(newX, newY)[0];
//				outputImage.at<Vec3b>(i, j)[1] = inputImage.at<Vec3b>(newX, newY)[1];
//				outputImage.at<Vec3b>(i, j)[2] = inputImage.at<Vec3b>(newX, newY)[2];
//			}
//			else
//			{
//				outputImage.at<Vec3b>(i, j)[0] = 0;
//				outputImage.at<Vec3b>(i, j)[1] = 0;
//				outputImage.at<Vec3b>(i, j)[2] = 0;
//			}
//		}
//	}
//	return outputImage;
//}


Mat Rotation(Mat inputImage, double rotationDegree, int x, int y) {
	cout << "Rotating....\n" << "Rotation degree:" << rotationDegree << "°" << "\n";
	int ox, oy;
	double COS, SIN;
	if (x == -1 && y == -1)
	{
		cout << "Rotating center in the center of the picture\n";
		ox = inputImage.cols / 2;
		oy = inputImage.rows / 2;
	}
	else
	{
		cout << "Rotating center " << x << "，" << y;
		ox = x;
		oy = y;
	}

	SIN = sin(rotationDegree * PI / 180.0), COS = cos(rotationDegree * PI / 180.0);

	//顺时针角点坐标左上开始//
	double a[4][2] = { 0 };
	a[0][0] = -ox;                    a[0][1] = oy;
	a[1][0] = (inputImage.cols - ox); a[1][1] = oy;
	a[2][0] = -ox;                    a[2][1] = -inputImage.rows + oy;
	a[3][0] = inputImage.cols - ox;   a[3][1] = -inputImage.rows + oy;

	double ca[4][2] = { 0 };
	for (int i = 0; i < 4; i++) {
		ca[i][0] = (int)(a[i][0] * COS - a[i][1] * SIN);
		ca[i][1] = (int)(a[i][0] * SIN + a[i][1] * COS);
	}




	//int Xmax = 0, Xmin = 0, Ymax = 0, Ymin = 0;
	//for (int i = 0; i < 4; i++) {
	//	Xmax = (ca[i][0] > Xmcax) ? ca[i][0] : Xmcax;
	//	Ymax = (ca[i][1] > Ymcax) ? ca[i][1] : Ymcax;
	//	Xmin = (ca[i][0] < Xmin) ? ca[i][0] : Xmin;
	//	Ymin = (ca[i][1] < Ymin) ? ca[i][1] : Ymin;
	//}

	int Xmax = max({ ca[0][0],ca[1][0],ca[2][0],ca[3][0] });
	int Xmin = min({ ca[0][0],ca[1][0],ca[2][0],ca[3][0] });
	int Ymax = max({ ca[0][1],ca[1][1],ca[2][1],ca[3][1] });
	int Ymin = min({ ca[0][1],ca[1][1],ca[2][1],ca[3][1] });

	int width = static_cast<int>(abs(Xmin - Xmax) + 0.5);
	int height = static_cast<int>(abs(Ymax - Ymin) + 0.5);

	Mat outputImage = Mat(height, width , CV_8UC3, Scalar(0, 0, 0));

	int ox2 = -abs(Xmin)*COS - abs(Ymax)*SIN + ox;
	int oy2 = abs(Xmin)*SIN - abs(Ymax)*COS + oy;
	int newX, newY;

	for (int i = 0; i < outputImage.rows; i++)
	{
		for (int j = 0; j < outputImage.cols; j++)
		{

			newX = (int)(j * COS + i * SIN + 0.5 + ox2);
			newY = (int)(-j * SIN + i * COS + 0.5 + oy2);

			if (newY >= 0 && newY < inputImage.rows && newX >= 0 && newX < inputImage.cols)
			{
				outputImage.at<Vec3b>(i, j)[0] = inputImage.at<Vec3b>(newY, newX)[0];
				outputImage.at<Vec3b>(i, j)[1] = inputImage.at<Vec3b>(newY, newX)[1];
				outputImage.at<Vec3b>(i, j)[2] = inputImage.at<Vec3b>(newY, newX)[2];
			}
		}
	}
	return outputImage;
}
