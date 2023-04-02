#pragma once
#include <iostream>         // 包含头文件。
#define _USE_MATH_DEFINES
#include"math.h"
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
class Calibration
{
public:
	Mat Mc;
	Mat Mp;
	
};