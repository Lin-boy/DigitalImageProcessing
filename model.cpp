// model.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>   
#include "opencv2/core/core.hpp"   
#include "opencv2/highgui/highgui.hpp"   

#include"formatchange.h"
#include"GraylineTransform.h"
#include"Conv.h"
#include"GeometricTrans.h"
#include"data.h"
#include"Mediumfliter.h"
#include"HoughLine.h"
#include"edge.h"

int main()
{
	//格式转换//
	/*char fileName[] = "E:/数图/BIL_856cols_743rows_6bands_byte";
	BIL2bmp(fileName, 743, 856, 6);*/
	//BSQ2bmp(fileName, 743, 856, 6);
	//BIP2bmp(fileName, 743, 856, 6);

	char imageName[] = "C:/Users/xiaofeng/Pictures/timg.jpg";
	Mat imageIN = imread(imageName, IMREAD_COLOR);   // 读入图片 
	if (imageIN.empty())     // 判断文件是否正常打开  
	{
		fprintf(stderr, "Can not load image %s\n", imageName);
		waitKey(6000);  // 等待6000 ms后窗口自动关闭   
		return -1;
	}
	namedWindow("original", 1);

	imshow("original", imageIN);

	Mat Grayimage = Rgb2Gray(imageIN);
	imshow("Gray", Grayimage);


	//灰度线性变换：RGB图像和灰度图像//

	//Mat GLTimage = GrayLinerTran_RGB(imageIN);imshow("GrayLinerTran", GLTimage);  // 显示图片 
	//Mat GLTimage = GrayLinerTran_Gray(Grayimage); imshow("GrayLinerTran", GLTimage);

	//高通滤波 低通滤波//
	//Mat Himage=conv2D(Grayimage, Highpassfilter, 1);imshow("Highpassfiltter",Himage);
	//Mat Limage=conv2D(Grayimage, Lowpassfilter, 8);imshow("Lowpassfillter",Limage);
	//Mat Himage=conv3D(imageIN, Highpassfilter, 1); imshow("RGBHighpassfiltter", Himage);
	//Mat Limage=conv3D(imageIN, Lowpassfilter, 8); imshow("RGBLowpassfillter", Limage);


	//几何处理(输入彩色图像)//
	//Mat Timage=translation(imageIN, 100, 100);imshow("Translation", Timage);
	//Mat Simage=scale(imageIN, 2);imshow("Scaling", Simage);//建议缩放因子范围为[0.6,4]
	//Mat  Rimage = Rotation(imageIN,45, -1, -1);namedWindow("rotation",1 );imshow("rotation", Rimage);


	//灰度图像边缘检测（输入灰度图像）//
	//Mat sobelimage = edge_sobel(Grayimage); imshow("Sobel",sobelimage);
	//Mat prewittimage = edge_sobel(Grayimage); imshow("Prewitt", prewittimage);



	//中值滤波，默认为3 x 3模板//
	 Mat mediumimage= Rgb2Gray(imageIN);
	 mediumimage=Mediumfliter(mediumimage); imshow("Mediumimage", mediumimage);
	 Mat Rgb_mediumimage= Rgb_mediumfliter(imageIN); imshow("Rgb_Mediumimage", Rgb_mediumimage);


	//HoughLine(imageIN,1,1);//输入彩色图，内置二值化采用简单二值化	//

	//imshow("test", imageIN);
	//imwrite("Edgefortest.jpg",prewittimage);
	waitKey();
	destroyAllWindows;

	return 0;
}

