#pragma once
#include "stdafx.h"
#include <iostream>   
#include "opencv2/core/core.hpp"   
#include "opencv2/highgui/highgui.hpp"   

using namespace std;
using namespace cv;


Mat edge_sobel(Mat inputImage);
Mat edge_prewitt(Mat inputImage);

Mat edge_sobel(Mat inputImage)
{
	int gx, gy, sum;
	Mat outputImage;
	outputImage = inputImage.clone();

	for (int y = 0; y < inputImage.rows; y++)
		for (int x = 0; x < inputImage.cols; x++)
			outputImage.at<uchar>(y, x) = 0.0;

	for (int y = 1; y < inputImage.rows - 1; y++)
	{
		for (int x = 1; x < inputImage.cols - 1; x++)
		{
			gx = inputImage.at<uchar>(y - 1, x - 1) + 2 * inputImage.at<uchar>(y, x - 1) + inputImage.at<uchar>(y + 1, x - 1) - inputImage.at<uchar>(y - 1, x + 1) - 2 * inputImage.at<uchar>(y, x + 1) - inputImage.at<uchar>(y + 1, x + 1);
			gy = inputImage.at<uchar>(y - 1, x - 1) + 2 * inputImage.at<uchar>(y - 1, x) + inputImage.at<uchar>(y - 1, x + 1) - inputImage.at<uchar>(y + 1, x - 1) - 2 * inputImage.at<uchar>(y + 1, x) - inputImage.at<uchar>(y + 1, x + 1);

			sum = abs(gx) + abs(gy);
			if (sum > 255) sum = 255;
			if (sum < 0) sum = 0;
			outputImage.at<uchar>(y, x) = sum;
		}
	}
	return outputImage;
}



Mat edge_prewitt(Mat inputImage)
{
	int gx, gy, sum;
	Mat outputImage;
	outputImage = inputImage.clone();

	for (int y = 0; y < inputImage.rows; y++)
		for (int x = 0; x < inputImage.cols; x++)
			outputImage.at<uchar>(y, x) = 0.0;

	for (int y = 1; y < inputImage.rows - 1; y++)
	{
		for (int x = 1; x < inputImage.cols - 1; x++)
		{
			gx = inputImage.at<uchar>(y - 1, x + 1) + inputImage.at<uchar>(y, x + 1) + inputImage.at<uchar>(y + 1, x + 1)- inputImage.at<uchar>(y - 1, x - 1) - inputImage.at<uchar>(y, x - 1) - inputImage.at<uchar>(y + 1, x - 1) ;
			gy =inputImage.at<uchar>(y + 1, x - 1) + inputImage.at<uchar>(y + 1, x) + inputImage.at<uchar>(y + 1, x + 1)- inputImage.at<uchar>(y - 1, x - 1) - inputImage.at<uchar>(y - 1, x) - inputImage.at<uchar>(y - 1, x + 1);

			sum = abs(gx) + abs(gy);
			if (sum > 255) sum = 255;
			if (sum < 0) sum = 0;
			outputImage.at<uchar>(y, x) = sum;
		}
	}
	return outputImage;
}