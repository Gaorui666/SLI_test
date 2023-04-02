/*
����һ����Pattern ��������Psin Pcos�Լ�float��ʽ��Mat
����Func_SaveAsBMP���������Mat(64λ)����Ϊbmp�ļ�
����Func_Save+Func_file������Ϊbyt�ļ�
*/
#pragma once
#ifndef CLASS_H_
#define CLASS_H_
#include<opencv2/opencv.hpp>
#include <iostream>         // ����ͷ�ļ���
#define _USE_MATH_DEFINES
#include"math.h"
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;        // ָ��ȱʡ�������ռ�
class Pattern
{
public:
	int width, height;
	Mat Img, Img_one, Img_split[3], Img_32F,X,Y,Z;

	Mat Psin = Mat::zeros(height, width, CV_32F);
	Mat Pcos = Mat::zeros(height, width, CV_32F);
	Mat Mat8UC3To8U();
	Mat Mat8UTo32F();
	void Psin_Pcos(int& f, int& num, int& N);
	void Get_W_H();
	void Func_file(char* s, Mat& Input_64F);
	void Func_Save();
	void Func_SaveAsBMP(Mat& InputMat, int Scale0No1, int n);

private:

};

#endif // !CLASS_H_


int getphase(int* nset, int len_n, int* fset, int len_f, Mat& Img, Mat& Ac, Mat& Bc, Mat& Psin, Mat& Pcos, Mat_<double>& Phase);
//void test(int* nset, int len_n, int* fset, int len_f, Mat_<int>& Img);