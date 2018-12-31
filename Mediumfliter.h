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
	//�������Mat ����Ա�Ե���в���
	//��src_clone�ⲿ���ϼ��м���
	imagetemp = GrayExpadzero(imagetemp, Kernel_halfWidth);

	//��imagetemp���м��㣬�Ѽ�����д��ImageIN
	for (int i1 = Kernel_halfWidth; i1 < nRows + Kernel_halfWidth; ++i1)
	{
		for (int j1 = Kernel_halfWidth; j1 < nCols + Kernel_halfWidth; ++j1)
		{
			//�����ڲ�С����
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
	//�������Mat ����Ա�Ե���в���
	//��src_clone�ⲿ���ϼ��м���
	imagetemp = ImageExpadzero(ImageIN, Kernel_halfWidth);

	//��imagetemp���м��㣬�Ѽ�����д��ImageIN
	for (int k = 0; k < 3; k++) {
		for (int i1 = Kernel_halfWidth; i1 < nRows + Kernel_halfWidth; ++i1)
		{
			for (int j1 = Kernel_halfWidth; j1 < nCols + Kernel_halfWidth; ++j1)
			{
				//�����ڲ�С����
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