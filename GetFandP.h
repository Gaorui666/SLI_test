#pragma once
#define CLASS_H_
#include<opencv2/opencv.hpp>
#include <iostream>         // 包含头文件。
#include<fstream>
#define _USE_MATH_DEFINES
#include"math.h"
#include<opencv2/opencv.hpp>
#include"Calibration.h"

using namespace cv;
using namespace std;        // 指定缺省的命名空间
void Raedtxt_FnP(char* path);
extern vector<int> Freq;
extern vector<int> Pattern_num;