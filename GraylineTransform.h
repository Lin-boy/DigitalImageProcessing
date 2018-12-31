#pragma once
#include "stdafx.h"
#include <iostream>   
#include "opencv2/core/core.hpp"   
#include "opencv2/highgui/highgui.hpp"   

using namespace std;
using namespace cv;


struct Weights_biases
{
	double weights;
	double biases;
};


Mat Rgb2Gray(Mat inputimage);
Mat GrayLinerTran_RGB(Mat  inputimage);
Mat GrayLinerTran_Gray(Mat  inputimage);
Weights_biases GetWeights_biases(Mat inputimage);



Mat Rgb2Gray(Mat inputimage) {
	Mat outimage = Mat(inputimage.rows, inputimage.cols, CV_8UC1, Scalar(0));

	for (int i = 0; i < inputimage.rows; i++)
	{
		for (int j = 0; j <inputimage.cols; j++)
		{
			outimage.at<uchar>(i, j) = 0.114*inputimage.at<Vec3b>(i, j)[0] + 0.587*inputimage.at<Vec3b>(i, j)[1] + 0.299*inputimage.at<Vec3b>(i, j)[2];
		}

	}
	return outimage;
}


Mat GrayLinerTran_RGB(Mat inputimage) {
	Mat grayimage = Rgb2Gray(inputimage);
	Weights_biases wb = GetWeights_biases(grayimage);
	double Weights = wb.weights, biases = wb.biases;
	for (int i = 0; i < inputimage.rows; i++) {
		for (int j = 0; j < inputimage.cols; j++) {
			inputimage.at<Vec3b>(i, j)[0] = int(Weights*inputimage.at<Vec3b>(i, j)[0] + biases);
			inputimage.at<Vec3b>(i, j)[1] = int(Weights*inputimage.at<Vec3b>(i, j)[1] + biases);
			inputimage.at<Vec3b>(i, j)[2] = int(Weights*inputimage.at<Vec3b>(i, j)[2] + biases);
		}
	}
	return inputimage;
}


Mat GrayLinerTran_Gray(Mat inputimage) {
	Weights_biases wb = GetWeights_biases(inputimage);
	double Weights = wb.weights, biases = wb.biases;
	for (int i = 0; i < inputimage.rows; i++) {
		for (int j = 0; j < inputimage.cols; j++) {
			inputimage.at<uchar>(i, j) = int(Weights*inputimage.at<uchar>(i, j) + biases);
		}
	}
	return inputimage;
}


Weights_biases GetWeights_biases(Mat inputimage) {
	Weights_biases weight_biases;
	int Graymax = inputimage.at<uchar>(0, 0), Graymin = inputimage.at<uchar>(0, 0);
	for (int i = 0; i < inputimage.rows; i++)
	{
		for (int j = 0; j <inputimage.cols; j++)
		{
			if (inputimage.at<uchar>(i, j) > Graymax) {
				Graymax = inputimage.at<uchar>(i, j);
			}
			if (inputimage.at<uchar>(i, j) < Graymin) {
				Graymin = inputimage.at<uchar>(i, j);
			}
		}
	}

	weight_biases.weights = 255 / (Graymax - Graymin);
	weight_biases.biases = (0 - Graymin) * 255 / (Graymax - Graymin);

	//cout<< weight_biases.weights<< weight_biases.biases;
	return weight_biases;
}