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
	FILE *fp = fopen(fileName, "rb+");	//�����ļ�
	if (fp == NULL) {
		printf("cannot open file for read\n");
		waitKey();
		exit(0);
	}

	Mat M(height, width, CV_8UC1, Scalar(0));
	uchar *p = new uchar[height*width];
	fread(p, 1, height*width, fp);

	//ʹ��dataָ�루unsigned char*����ƫ����
	//	unsigned char* ptr = M.data;
	//for (int i = 0; i < 1024; i++) {
	//	for (int j = 0; j < 1024; j++) {
	//		ptr[(i * 1024 + j) * 1 + 0] = p[i * 1024 + j];
	//	}
	//}
	//delete[] p;


	//��mat.ptr<��������>(����) ��ȡͼ����ָ��
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

	//��Mat.at(i,j)��������(i,j)��ͼ��Ԫ�� 

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			M.at<uchar>(i, j) = p[i*width + j];
		}
	}
	// ��ʾͼƬ
	namedWindow("image", WINDOW_AUTOSIZE);
	imshow("image", M);

	// �ȴ������󴰿��Զ��ر� 
	waitKey();
	imwrite("pic.bmp", M); // ��Ϊbmp��ʽͼƬ
	fclose(fp);
}


void BIL2bmp(char *fileName, int height, int width, int bands) {
	FILE *fp = fopen(fileName, "rb+");	//�����ļ�
	if (fp == NULL) {
		printf("cannot open file for read\n");
		waitKey();
		exit(0);
	}

	//BIL �����ΰ��н����ʽ���� BIL ��ʽ�洢��ͼ���ȴ洢��һ�����εĵ�һ�У������ǵڶ������εĵ�һ�У�Ȼ���ǵ��������εĵ�һ�У������ȡֱ����������Ϊֹ��ÿ�����������а������Ƶķ�ʽ�����ȡ��

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

	// ��ʾͼƬ
	namedWindow("image", WINDOW_AUTOSIZE);
	imshow("image", M);

	// �ȴ������󴰿��Զ��ر� 
	waitKey();
	imwrite("pic.bmp", M); // ��Ϊbmp��ʽͼƬ
	fclose(fp);
}


void BIP2bmp(char *fileName, int height, int width, int bands) {
	FILE *fp = fopen(fileName, "rb+");	//�����ļ�
	if (fp == NULL) {
		printf("cannot open file for read\n");
		waitKey();
		exit(0);
	}

	//BIP �����ΰ���Ԫ�����ʽ���� BIP ��ʽ�洢��ͼ��˳��洢��һ����Ԫ���еĲ��Σ������ǵڶ�����Ԫ�����в��Σ�Ȼ���ǵ� 3 ����Ԫ�����в��Σ��ȵȣ������ȡֱ����Ԫ����Ϊֹ��
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


	// ��ʾͼƬ
	namedWindow("image", WINDOW_AUTOSIZE);
	imshow("image", M);

	// �ȴ������󴰿��Զ��ر� 
	waitKey();
	imwrite("pic.bmp", M); // ��Ϊbmp��ʽͼƬ
	fclose(fp);
}


void BSQ2bmp(char *fileName, int height, int width, int bands) {
	FILE *fp = fopen(fileName, "rb+");	//�����ļ�
	if (fp == NULL) {
		printf("cannot open file for read\n");
		waitKey();
		exit(0);
	}

	//BSQ ������˳���ʽ��ÿ�����ݺ��������ͬһ���ײ��ε���һ�����ݡ�
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

	// ��ʾͼƬ
	namedWindow("image", WINDOW_AUTOSIZE);
	imshow("image", M);

	// �ȴ������󴰿��Զ��ر� 
	waitKey();
	imwrite("pic.bmp", M); // ��Ϊbmp��ʽͼƬ
	fclose(fp);
}
