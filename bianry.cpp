#include"stdafx.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;

Mat src, dst;

void main()
{
	src = imread("C:/Users/xiaofeng/Pictures/1_1.bmp", IMREAD_GRAYSCALE);
	if (!src.data) {
		printf("读取图片错误! \n");
	}
	imshow("原始图", src);
	//使用otsu方法
	threshold(src, dst, 100, 255, THRESH_OTSU);
	imshow("效果图", dst);

	Mat dst = Mat::zeros(src.size(), src.type());
	//自适应阈值处理
	adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, 5);
	
	imshow("效果图2", dst);
	waitKey(0);
}
