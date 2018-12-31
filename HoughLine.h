#include"stdafx.h"
#include <iostream>
#include <stdio.h>
#include<deque>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>


#include"edge.h"
#include"GraylineTransform.h"
#include"time.h"


using namespace cv;
using namespace std;

#define PI 3.1415926535

# define THD 1          
# define THL 30         
#define Bina_threshold 150
#define multiple 4

struct Line
{
	double dist;
	double angle;
	int num;
};

void HoughLine(Mat inputimage, int rho, int theato);





void  HoughLine(Mat inputimage, int rho, int theato) {

	if (inputimage.empty())
	{
		fprintf(stderr, "Can not load image %s\n");
		waitKey(6000);
	}


	time_t timeBegin, timeEnd;
	timeBegin = time(NULL);

	Mat Grayimage = Rgb2Gray(inputimage);
	Mat edge = edge_sobel(Grayimage);
	Mat src;
	edge.copyTo(src);
	Mat op(src.rows, src.cols, CV_8UC1, Scalar(0));

	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			int avg = src.at<uchar>(i, j);
			op.at<uchar>(i, j) = (avg <  Bina_threshold) ? 0 : 255;
		}
	}

	src = op.clone();

	int maxd = sqrt(src.rows*src.rows + src.cols*src.cols);


	short int **data = new short int*[maxd];
	for (int i = 0; i < maxd; i += rho) {
		data[i] = new short int[180];
	}


	for (int i = 0; i < maxd; i += rho) {
		for (int j = 0; j < 180; j += theato) {
			data[i][j] = 0;
		}
	}

	int ptdist;
	for (int m = 0; m < src.rows; m++) {
		for (int n = 0; n < src.cols; n++) {
			if (src.at<uchar>(m, n) == 255) {
				for (int i = 0; i < maxd; i += rho) {
					for (int j = 0; j < 180; j += theato) {
						ptdist = abs(n*cos(j*3.14 / 180) + m*sin(j*3.14 / 180) - i);
						if (ptdist < THD)
							data[i][j]++;
					}
				}
			}
		}
	}


	int Line_num = 0;
	for (int i = 0; i < maxd - rho; i += rho) {
		for (int j = 0; j < 180 - theato; j += theato) {
			if (data[i][j] != 0) {
				Line_num++;
			}
		}
	}

	Line *line = new Line[Line_num];

	int k = 0;
	for (int i = rho; i < maxd - rho; i += rho) {
		for (int j = theato; j < 180 - theato; j += theato) {
			if (data[i][j] > data[i - rho][j] && data[i][j] > data[i + rho][j] && data[i][j] > data[i][j - theato] && data[i][j] > data[i][j + theato])
			{
				line[k].dist = i;
				line[k].angle = j;
				line[k].num = data[i][j];
				k++;
			}
		}
	}

	Line_num = k;

	int temp_num, temp_dist, temp_angle;
	for (int i = 0; i<Line_num - 1; i++)
	{
		for (int j = i + 1; j<Line_num; j++)
		{
			if (line[i].num>line[j].num)
			{
				temp_num = line[j].num; temp_dist = line[j].dist; temp_angle = line[j].angle;
				line[j].num = line[i].num;	line[j].dist = line[i].dist; line[j].angle = line[i].angle;
				line[i].num = temp_num; line[i].dist = temp_dist; line[i].angle = temp_angle;
			}
		}
	}


	Mat op2(src.rows, src.cols, CV_8UC1, Scalar(0));
	op = op2.clone();

	int Nk = Line_num - 1;
	while (Nk>Line_num - 20)
	{
		for (int m = 0; m < src.rows; m++) {
			for (int n = 0; n < src.cols; n++) {
				int ptdist2 = abs(n*cos(line[Nk].angle*3.14 / 180) + m*sin(line[Nk].angle*3.14 / 180) - line[Nk].dist);
				if (ptdist2 < 1)
				{
					op.at<uchar>(m, n) = 255;
					inputimage.at<Vec3b>(m, n)[0] = 0;
					inputimage.at<Vec3b>(m, n)[1] = 0;
					inputimage.at<Vec3b>(m, n)[2] = 255;
				}
			}
		}
		Nk--;
	}


	for (int i = 0; i < maxd; i += rho) {
		delete[]data[i];
	}
	delete[]data;

	delete[]line;


	timeEnd = time(NULL);
	cout << (timeEnd - timeBegin);


	imshow("binary", src);

	imshow("houghtest", op);
	imshow("Output", inputimage);
	waitKey(0);

}


