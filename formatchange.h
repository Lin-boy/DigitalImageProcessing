#pragma once
#include "stdafx.h"
#include <iostream>   
#include "opencv2/core/core.hpp"   
#include "opencv2/highgui/highgui.hpp"   

using namespace std;
using namespace cv;

void raw2bmp(char *fileName, int height, int width);
void BIL2bmp(char *fileName, int height, int width, int bands);
void BIP2bmp(char *fileName, int height, int width, int bands);
void BSQ2bmp(char *fileName, int height, int width, int bands);

void raw2bmp(char *fileName, int height, int width) {
	FILE *fp = fopen(fileName, "rb+");	//读入文件
	if (fp == NULL) {
		printf("cannot open file for read\n");
		waitKey();
		exit(0);
	}

	Mat M(height, width, CV_8UC1, Scalar(0));
	uchar *p = new uchar[height*width];
	fread(p, 1, height*width, fp);

	//使用data指针（unsigned char*）加偏移量
	//	unsigned char* ptr = M.data;
	//for (int i = 0; i < 1024; i++) {
	//	for (int j = 0; j < 1024; j++) {
	//		ptr[(i * 1024 + j) * 1 + 0] = p[i * 1024 + j];
	//	}
	//}
	//delete[] p;


	//用mat.ptr<数据类型>(行数) 获取图像行指针
	//	uchar * p;
	//for (int i = 0; i < height; i++)
	//{
	//	p = m.ptr<uchar>(i);
	//	fread(p, 1, width, fp);
	//}

	//uchar * p;
	//for (int i = 0; i<height; i++)
	//{
	//	for (int j = 0; j<width; j++) {
	//		p = m.ptr<uchar>(i, j);
	//		fread(p, 1, 1, fp);
	//	}
	//}

	//用Mat.at(i,j)访问坐标(i,j)的图像元素 

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			M.at<uchar>(i, j) = p[i*width + j];
		}
	}
	// 显示图片
	namedWindow("image", WINDOW_AUTOSIZE);
	imshow("image", M);

	// 等待按键后窗口自动关闭 
	waitKey();
	imwrite("pic.bmp", M); // 存为bmp格式图片
	fclose(fp);
}


void BIL2bmp(char *fileName, int height, int width, int bands) {
	FILE *fp = fopen(fileName, "rb+");	//读入文件
	if (fp == NULL) {
		printf("cannot open file for read\n");
		waitKey();
		exit(0);
	}

	//BIL （波段按行交叉格式）按 BIL 格式存储的图像先存储第一个波段的第一行，接着是第二个波段的第一行，然后是第三个波段的第一行，交叉存取直到波段总数为止。每个波段随后的行按照类似的方式交叉存取。

	Mat M(height, width, CV_8UC3, Scalar(0, 0, 0));
	uchar *p = new uchar[height * width * bands];
	fread(p, 1, height * width * bands, fp);
	int k = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			M.at<Vec3b>(i, j)[0] = p[(k + 0) * width + j];
			M.at<Vec3b>(i, j)[1] = p[(k + 1) * width + j];
			M.at<Vec3b>(i, j)[2] = p[(k + 2) * width + j];

		}
		k += bands;
	}
	delete[] p;

	// 显示图片
	namedWindow("image", WINDOW_AUTOSIZE);
	imshow("image", M);

	// 等待按键后窗口自动关闭 
	waitKey();
	imwrite("pic.bmp", M); // 存为bmp格式图片
	fclose(fp);
}


void BIP2bmp(char *fileName, int height, int width, int bands) {
	FILE *fp = fopen(fileName, "rb+");	//读入文件
	if (fp == NULL) {
		printf("cannot open file for read\n");
		waitKey();
		exit(0);
	}

	//BIP （波段按像元交叉格式）按 BIP 格式存储的图像按顺序存储第一个像元所有的波段，接着是第二个像元的所有波段，然后是第 3 个像元的所有波段，等等，交叉存取直到像元总数为止。
	Mat M(height, width, CV_8UC3, Scalar(0, 0, 0));
	uchar *p = new uchar[height * width * bands];
	fread(p, 1, height * width * bands, fp);
	int k = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			M.at<Vec3b>(i, j)[0] = p[k];
			M.at<Vec3b>(i, j)[1] = p[k + 1];
			M.at<Vec3b>(i, j)[2] = p[k + 2];
			k += bands;
		}
	}
	delete[] p;


	// 显示图片
	namedWindow("image", WINDOW_AUTOSIZE);
	imshow("image", M);

	// 等待按键后窗口自动关闭 
	waitKey();
	imwrite("pic.bmp", M); // 存为bmp格式图片
	fclose(fp);
}


void BSQ2bmp(char *fileName, int height, int width, int bands) {
	FILE *fp = fopen(fileName, "rb+");	//读入文件
	if (fp == NULL) {
		printf("cannot open file for read\n");
		waitKey();
		exit(0);
	}

	//BSQ （波段顺序格式）每行数据后面紧接着同一波谱波段的下一行数据。
	Mat M(height, width, CV_8UC3, Scalar(0, 0, 0));
	uchar *p = new uchar[height * width * bands];
	fread(p, 1, height * width * bands, fp);

	int k = height*width;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			M.at<Vec3b>(i, j)[0] = p[i * width + j];
			M.at<Vec3b>(i, j)[1] = p[i * width + j + k * 4];
			M.at<Vec3b>(i, j)[2] = p[i * width + j + k * 2];
		}
	}
	delete[] p;

	// 显示图片
	namedWindow("image", WINDOW_AUTOSIZE);
	imshow("image", M);

	// 等待按键后窗口自动关闭 
	waitKey();
	imwrite("pic.bmp", M); // 存为bmp格式图片
	fclose(fp);
}
