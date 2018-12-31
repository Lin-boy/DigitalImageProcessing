// model.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//��ʽת��//
	/*char fileName[] = "E:/��ͼ/BIL_856cols_743rows_6bands_byte";
	BIL2bmp(fileName, 743, 856, 6);*/
	//BSQ2bmp(fileName, 743, 856, 6);
	//BIP2bmp(fileName, 743, 856, 6);

	char imageName[] = "C:/Users/xiaofeng/Pictures/timg.jpg";
	Mat imageIN = imread(imageName, IMREAD_COLOR);   // ����ͼƬ 
	if (imageIN.empty())     // �ж��ļ��Ƿ�������  
	{
		fprintf(stderr, "Can not load image %s\n", imageName);
		waitKey(6000);  // �ȴ�6000 ms�󴰿��Զ��ر�   
		return -1;
	}
	namedWindow("original", 1);

	imshow("original", imageIN);

	Mat Grayimage = Rgb2Gray(imageIN);
	imshow("Gray", Grayimage);


	//�Ҷ����Ա任��RGBͼ��ͻҶ�ͼ��//

	//Mat GLTimage = GrayLinerTran_RGB(imageIN);imshow("GrayLinerTran", GLTimage);  // ��ʾͼƬ 
	//Mat GLTimage = GrayLinerTran_Gray(Grayimage); imshow("GrayLinerTran", GLTimage);

	//��ͨ�˲� ��ͨ�˲�//
	//Mat Himage=conv2D(Grayimage, Highpassfilter, 1);imshow("Highpassfiltter",Himage);
	//Mat Limage=conv2D(Grayimage, Lowpassfilter, 8);imshow("Lowpassfillter",Limage);
	//Mat Himage=conv3D(imageIN, Highpassfilter, 1); imshow("RGBHighpassfiltter", Himage);
	//Mat Limage=conv3D(imageIN, Lowpassfilter, 8); imshow("RGBLowpassfillter", Limage);


	//���δ���(�����ɫͼ��)//
	//Mat Timage=translation(imageIN, 100, 100);imshow("Translation", Timage);
	//Mat Simage=scale(imageIN, 2);imshow("Scaling", Simage);//�����������ӷ�ΧΪ[0.6,4]
	//Mat  Rimage = Rotation(imageIN,45, -1, -1);namedWindow("rotation",1 );imshow("rotation", Rimage);


	//�Ҷ�ͼ���Ե��⣨����Ҷ�ͼ��//
	//Mat sobelimage = edge_sobel(Grayimage); imshow("Sobel",sobelimage);
	//Mat prewittimage = edge_sobel(Grayimage); imshow("Prewitt", prewittimage);



	//��ֵ�˲���Ĭ��Ϊ3 x 3ģ��//
	 Mat mediumimage= Rgb2Gray(imageIN);
	 mediumimage=Mediumfliter(mediumimage); imshow("Mediumimage", mediumimage);
	 Mat Rgb_mediumimage= Rgb_mediumfliter(imageIN); imshow("Rgb_Mediumimage", Rgb_mediumimage);


	//HoughLine(imageIN,1,1);//�����ɫͼ�����ö�ֵ�����ü򵥶�ֵ��	//

	//imshow("test", imageIN);
	//imwrite("Edgefortest.jpg",prewittimage);
	waitKey();
	destroyAllWindows;

	return 0;
}

