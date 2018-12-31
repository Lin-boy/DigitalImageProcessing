#pragma once

#include "stdafx.h"
#include <iostream>   
#include "opencv2/core/core.hpp"   
#include "opencv2/highgui/highgui.hpp"   

using namespace std;
using namespace cv;

Mat Lowpassfilter = (Mat_<double>(3, 3) << 1, 1, 1, 1, 0, 1, 1, 1, 1);
Mat Highpassfilter = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

