#pragma once
#define CLASS_H_
#include<opencv2/opencv.hpp>
#include <iostream>         // ����ͷ�ļ���
#include<fstream>
#define _USE_MATH_DEFINES
#include"math.h"
#include<opencv2/opencv.hpp>
#include"Calibration.h"

using namespace cv;
using namespace std;        // ָ��ȱʡ�������ռ�
void Raedtxt_FnP(char* path);
extern vector<int> Freq;
extern vector<int> Pattern_num;