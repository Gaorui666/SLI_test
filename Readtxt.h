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

void Readtxt(char* path);
extern Mat CameraM;
extern Mat ProjectorM;
extern string testsss;
