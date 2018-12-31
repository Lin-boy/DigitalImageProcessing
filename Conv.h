#pragma once
#include "stdafx.h"
#include <iostream>   
#include "opencv2/core/core.hpp"   
#include "opencv2/highgui/highgui.hpp"   

using namespace std;
using namespace cv;

//conv 中的num为滤波器前的系数

Mat GrayExpadzero(Mat image, int ExpadLength);
Mat conv2D(Mat inputimage, Mat Convkernel, int num);
Mat ImageExpadzero(Mat image, int ExpadLength);
Mat conv3D(Mat ImageIN, Mat Convkernel, int num);


Mat GrayExpadzero(Mat image, int  ExpadLength) {

	int num = ExpadLength;
	Mat temp = Mat(image.rows + num * 2, image.cols + num * 2, CV_8UC1, Scalar(0));
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			temp.at<uchar>(i + num, j + num) = image.at<uchar>(i, j);
		}
	}
	temp.copyTo(image);
	return image;
}

Mat conv2D(Mat inputimage, Mat Convkernel, int num) {

	int Kernel_halfWidth = (Convkernel.rows - 1) / 2;
	Mat imagetemp,ImageIN;
	inputimage.copyTo(ImageIN); inputimage.copyTo(imagetemp);

	int nRows = ImageIN.rows;
	int nCols = ImageIN.cols;
	//扩张这个Mat 避免对边缘进行操作
	//在src_clone外部套上几行几列
	imagetemp = GrayExpadzero(ImageIN, Kernel_halfWidth);

	//对imagetemp进行计算，把计算结果写入ImageIN
	for (int i1 = Kernel_halfWidth; i1 < nRows + Kernel_halfWidth; ++i1)
	{
		for (int j1 = Kernel_halfWidth; j1 < nCols + Kernel_halfWidth; ++j1)
		{
			//计算内部小矩阵
			double sum = 0;
			for (int ini1 = i1 - Kernel_halfWidth; ini1 <= i1 + Kernel_halfWidth; ++ini1)
			{
				for (int inj1 = j1 - Kernel_halfWidth; inj1 <= j1 + Kernel_halfWidth; ++inj1)
				{
					int p = (double)imagetemp.at<uchar>(ini1, inj1);
					int q = Convkernel.at<double>(ini1 - i1 + Kernel_halfWidth, inj1 - j1 + Kernel_halfWidth);
					sum += p*q;
				}
			}
			ImageIN.at<uchar>(i1 - Kernel_halfWidth, j1 - Kernel_halfWidth) = (int)(sum / num);
		}
	}
	
	return ImageIN;

}

Mat ImageExpadzero(Mat image, int ExpadLength) {
	int num = ExpadLength;
	Mat temp = Mat(image.rows + num * 2, image.cols + num * 2, CV_8UC3, Scalar(0, 0, 0));
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			temp.at<Vec3b>(i + num, j + num)[0] = image.at<Vec3b>(i, j)[0];
			temp.at<Vec3b>(i + num, j + num)[1] = image.at<Vec3b>(i, j)[1];
			temp.at<Vec3b>(i + num, j + num)[2] = image.at<Vec3b>(i, j)[2];
		}
	}
	temp.copyTo(image);
	return image;
}

Mat conv3D(Mat inputimage, Mat Convkernel, int num) {

	int Kernel_halfWidth = (Convkernel.rows - 1) / 2;
	Mat imagetemp, ImageIN;
	inputimage.copyTo(ImageIN); inputimage.copyTo(imagetemp);


	int nRows = ImageIN.rows;
	int nCols = ImageIN.cols;
	//扩张这个Mat 避免对边缘进行操作
	//在src_clone外部套上几行几列
	imagetemp = ImageExpadzero(ImageIN, Kernel_halfWidth);

	//对imagetemp进行计算，把计算结果写入ImageIN

	for (int k = 0; k < 3; k++) {
		int i1, j1 = 0;
		int ini1, inj1 = 0;
		for (i1 = Kernel_halfWidth; i1 < nRows + Kernel_halfWidth; ++i1)
		{
			for (j1 = Kernel_halfWidth; j1 < nCols + Kernel_halfWidth; ++j1)
			{
				//计算内部小矩阵
				double sum = 0;
				for (ini1 = i1 - Kernel_halfWidth; ini1 <= i1 + Kernel_halfWidth; ++ini1)
				{
					for (inj1 = j1 - Kernel_halfWidth; inj1 <= j1 + Kernel_halfWidth; ++inj1)
					{
						int p = (double)imagetemp.at<Vec3b>(ini1, inj1)[k];
						int q = Convkernel.at<double>(ini1 - i1 + Kernel_halfWidth, inj1 - j1 + Kernel_halfWidth);
						sum += p*q;
					}
				}
				ImageIN.at<Vec3b>(i1 - Kernel_halfWidth, j1 - Kernel_halfWidth)[k] = (int)(sum / num);
			}
		}
	}
	return ImageIN;
}