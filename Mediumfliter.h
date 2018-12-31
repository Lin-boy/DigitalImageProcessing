#pragma once
#include "stdafx.h"
#include <iostream>   
#include "opencv2/core/core.hpp"   
#include "opencv2/highgui/highgui.hpp"   
#include "GraylineTransform.h"
#include "Conv.h"


using namespace std;
using namespace cv;


Mat mediumkernel = (Mat_<double>(3, 3) << 1, 1, 1, 1, 1, 1, 1, 1, 1);


Mat  Mediumfliter(Mat ImageIN);
int Getmedium(int *k, int n);
Mat Rgb_mediumfliter(Mat ImageIN);


Mat  Mediumfliter(Mat ImageIN) {

	int Kernel_halfWidth = (mediumkernel.rows - 1) / 2;
	Mat imagetemp;
	ImageIN.copyTo(imagetemp);

	int nRows = ImageIN.rows;
	int nCols = ImageIN.cols;
	//扩张这个Mat 避免对边缘进行操作
	//在src_clone外部套上几行几列
	imagetemp = GrayExpadzero(imagetemp, Kernel_halfWidth);

	//对imagetemp进行计算，把计算结果写入ImageIN
	for (int i1 = Kernel_halfWidth; i1 < nRows + Kernel_halfWidth; ++i1)
	{
		for (int j1 = Kernel_halfWidth; j1 < nCols + Kernel_halfWidth; ++j1)
		{
			//计算内部小矩阵
			int temp[9] = { 0 };
			for (int ini1 = i1 - Kernel_halfWidth; ini1 <= i1 + Kernel_halfWidth; ++ini1)
			{
				for (int inj1 = j1 - Kernel_halfWidth; inj1 <= j1 + Kernel_halfWidth; ++inj1)
				{
					temp[(ini1 - i1 + Kernel_halfWidth)*mediumkernel.rows + (inj1 - j1 + Kernel_halfWidth)] = (double)imagetemp.at<uchar>(ini1, inj1);
				}
			}
			ImageIN.at<uchar>(i1 - Kernel_halfWidth, j1 - Kernel_halfWidth) = (int)Getmedium(temp, mediumkernel.rows*mediumkernel.cols);

		}

	}
	return ImageIN;
}



int Getmedium(int *k, int n)
{
	int i, j, temp;
	int medium = (n - 1) / 2;
	for (i = 0; i<n - 1; i++)
	{
		for (j = i + 1; j<n; j++)
		{
			if (k[i]>k[j])
			{
				temp = k[j];
				k[j] = k[i];
				k[i] = temp;
			}
		}
	}
	int final = k[medium + 1];
	return final;
}



Mat Rgb_mediumfliter(Mat ImageIN) {
	int Kernel_halfWidth = (mediumkernel.rows - 1) / 2;
	Mat imagetemp;
	ImageIN.copyTo(ImageIN);
	int nRows = ImageIN.rows;
	int nCols = ImageIN.cols;
	//扩张这个Mat 避免对边缘进行操作
	//在src_clone外部套上几行几列
	imagetemp = ImageExpadzero(ImageIN, Kernel_halfWidth);

	//对imagetemp进行计算，把计算结果写入ImageIN
	for (int k = 0; k < 3; k++) {
		for (int i1 = Kernel_halfWidth; i1 < nRows + Kernel_halfWidth; ++i1)
		{
			for (int j1 = Kernel_halfWidth; j1 < nCols + Kernel_halfWidth; ++j1)
			{
				//计算内部小矩阵
				int temp[9] = { 0 };
				for (int ini1 = i1 - Kernel_halfWidth; ini1 <= i1 + Kernel_halfWidth; ++ini1)
				{
					for (int inj1 = j1 - Kernel_halfWidth; inj1 <= j1 + Kernel_halfWidth; ++inj1)
					{
						temp[(ini1 - i1 + Kernel_halfWidth)*mediumkernel.rows + (inj1 - j1 + Kernel_halfWidth)] = (double)imagetemp.at<Vec3b>(ini1, inj1)[k];
					}
				}
				ImageIN.at<Vec3b>(i1 - Kernel_halfWidth, j1 - Kernel_halfWidth)[k] = (int)Getmedium(temp, mediumkernel.rows*mediumkernel.cols);

			}

		}
	}
	return ImageIN;

}