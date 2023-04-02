#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>
#include"GetPhase.h"
#include"GetFandP.h"
using namespace cv;
using namespace std;
Pattern WrapPhase(Pattern& Object, Mat& Ac, Mat& Bc, Mat& Phase, Mat& TempPhase, Mat& k);