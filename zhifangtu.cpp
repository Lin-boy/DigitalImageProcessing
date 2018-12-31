
#include"stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "stdio.h"
using namespace cv;

int main()
{
	// 加载源图像
	Mat srcImage, dstImage;
	srcImage = imread("C:/Users/xiaofeng/Pictures/1_1.bmp", 1);
	if (!srcImage.data) { printf("读取图片错误！ \n"); return false; }

	// 转为灰度图
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);

	// 直方图均衡化
	equalizeHist(srcImage, dstImage);

	// 显示结果
	namedWindow("原始图", WINDOW_NORMAL);
	namedWindow("直方图处理后", WINDOW_NORMAL);
	imshow("原始图", srcImage);
	imshow("直方图处理后", dstImage);

	// 等待用户按键退出程序
	waitKey(0);
	return 0;

}