#include<opencv2/opencv.hpp>
#include<iostream>
#include <fstream> 
#include <string>
#include"GetPhase.h"
#include"WrapPhase.h"
#include"show_float.h"
#include"pointcloud.h"
#include"show_randc.h"
#include"Filter_Kernel.h"
#include"SaveTxt.h"
#define _USE_MATH_DEFINES
#include"math.h"
#include"Readtxt.h"
#include"GetFandP.h"

using namespace cv;
using namespace std;


int main() {
	// 注意文件路径和你所对应的图片
	Pattern obj;

	//获取频率 图案数量 校准矩阵Mc和Mp（均是全局变量）
	char M_path[] = "..\\original_data\\calibration.txt";
	char M_path2[] = "..\\original_data\\FnP.txt";
	Readtxt(M_path);
	Raedtxt_FnP(M_path2);
	//预先读取一张图片获取对应的宽和高，用于Ac Bc等在main中不断出现的Mat的创建
	string First_Img = "..\\original_data\\0000.bmp";
	Mat Img_one = imread(First_Img);
	int height = Img_one.rows;
	int width = Img_one.cols;
	Mat Ac(height, width, CV_64F, Scalar::all(0));
	Mat Bc(height, width, CV_64F, Scalar::all(0));
	Mat Phase(height, width, CV_64F, Scalar::all(0));
	Mat TempPhase(height, width, CV_64F, Scalar::all(0));
	Mat k(height, width, CV_64F, Scalar::all(0));

	//for (int i = 0; i < Freqlevel; i++)//遍历各个频率
	//{

	//	int F = *(fSet + i); //某一个频率值	
	//	int N = *(NSet + i); //该频率对应的n幅图
	//	//! 为什么在这里把obj.Psin.zeros是无法置零的呢？
	//	cout << " 频率现在是" << *(fSet + i) << "该频率对应的图片数是" << *(NSet + i) << endl;

	//	//读入某个F对应的N幅图片，并计算Psin和Pcos
	//	for (int j = 0; j < N; j++)
	//	{
	//		int kk = i * N + j;
	//		sprintf_s(filename, ".\\original_data\\%04d.bmp", kk);
	//		cout << "现在读的是000" << kk << "图" << endl;
	//		obj.Img = imread(filename);  //获取同一频率下对应的多幅里的某张图
	//		obj.Get_W_H();
	//		obj.Mat8UC3To8U();
	//		obj.Mat8UTo32F();
	//		/*
	//		//namedWindow("Img_one", 1);
	//		//namedWindow("Img_split[1]", 1);
	//		//namedWindow("Img_split[2]", 1);
	//		//imshow("Img_one", Img_one);
	//		//imshow("Img_split[1]", Img_split[1]);
	//		//imshow("Img_split[2]", Img_split[2]);
	//		//waitKey(0);
	//		//
	//		//
	//		//
	//		//把Mat转换成array
	//		// Array(r_Img * c_Img);
	//		//array Img_1=
	//		//Pcos = Psin + Img * 2;
	//		//vector<uchar> array(r_Img* c_Img);
	//		//把mat转换成一维数组
	//		//uchar* array = new uchar[Img.rows * Img.cols];
	//		*/
	//		//把mat的数据类型从CV_8UC(n)转到CV_32FC(n)，
	//		//其中8U为Unsigned 8bits uchar 0~255，32F为Float 32bits float 3.4E38～3.4E38
	//		//Mat Img_f;
	//		//Img_one.convertTo(Img_f, CV_32F);//!!!!这里修改成比例因子是1
	//		//namedWindow("Img_float", 1);
	//		//imshow("Img_float", Img_f);
	//		//waitKey(0);
	//		//int s = Img_f.channels();
	//		//int flag_Img = Img_f.flags;
	//		//int Img_f_type = Img_f.type();
	//		//cout << "Img_f的channels是" << s << endl;
	//		//cout << "Img_f的flags是" << flag_Img << endl;
	//		//cout << "Img_one的type是" << Img_one.type() << endl;
	//		//cout << "Img_f的type是" << Img_f_type << endl;
	//		//cout << "===========Psin==================" << endl;
	//		obj.Psin_Pcos(F,j,N);
	//		/*==========================================================================
	//		for (int mm = 0; mm < Img_f.cols; mm++)
	//		{
	//			cout << Psin.at<float>(0, mm) << "\t";
	//		}
	//		cout << "=============Pcos================" << endl;
	//		===========================================================================*/
	//		/*================================================================================
	//		for (int mm = 0; mm < Img_f.cols; mm++)
	//		{
	//			cout << Pcos.at<float>(0, mm) << "\t";
	//		}
	//		===============================================================================*/

	//		if (F == 1)
	//		{
	//			Ac = Ac + obj.Img_32F;
	//			/*================================================================================
	//			cout << "================Ac=============" << endl;
	//			for (int mm = 0; mm < Img_f.cols; mm++)
	//			{
	//				cout << Ac.at<float>(0, mm) << "\t";
	//			}
	//			===============================================================================*/
	//		}

	//	}

	//	if (F == 1)
	//	{
	//		//遍历每一个元素计算相位值
	//		for (int ii = 0; ii < obj.height; ii++)  //r_Img=480行
	//		{
	//			for (int jj = 0; jj < obj.width; jj++)
	//			{
	//				Phase.at<double>(ii, jj) = atan2(-obj.Psin.at<double>(ii, jj), -obj.Pcos.at<double>(ii, jj)) + M_PI;	
	//				//cout << "Psin.at<float>值=" << obj.Psin.at<float>(ii, jj) << endl;
	//				//cout << "Pcos.at<float>值=" << obj.Pcos.at<float>(ii, jj) << endl;
	//				//cout << "atan2(-Psin.at<float>(ii, jj), -Pcos.at<float>(ii, jj))=" << atan2(-obj.Psin.at<float>(ii, jj), -obj.Pcos.at<float>(ii, jj)) << endl;
	//				//cout << "atan2(Psin.at<float>(ii, jj), Pcos.at<float>(ii, jj))=" << atan2(obj.Psin.at<float>(ii, jj), obj.Pcos.at<float>(ii, jj)) << endl;
	//				//cout << "atan2(-1*Psin.at<float>(ii, jj), -1*Pcos.at<float>(ii, jj))=" << atan2(-1 * obj.Psin.at<float>(ii, jj), -1 * obj.Pcos.at<float>(ii, jj)) << endl;

	//			}
	//		}
	//		Ac = Ac / N;
	//		// sqrt( A, B)的解释为将矩阵A开平方结果放到矩阵B中，不需要重新赋值。
	//		sqrt(obj.Psin.mul(obj.Psin) + obj.Pcos.mul(obj.Pcos), Bc);
	//		Bc = 2.0 / N * Bc;

	//		/*=============================================================================
	//		cout << "================Phase(F=1)=============" << endl;
	//		for (int mm = 0; mm < Img_f.cols; mm++)
	//		{
	//			cout << Phase.at<float>(0, mm) << "\t";
	//		}
	//		=============================================================================*/
	//	}
	//	else
	//	{
	//		//计算出每一点的TempPhase
	//		for (int ii = 0; ii < obj.height; ii++)
	//		{
	//			for (int jj = 0; jj < obj.width; jj++)
	//			{
	//				//cout << "Psin.at<float>"<<"("<<ii<<","<<jj<<")与Pcos: " << obj.Psin.at<float>(ii, jj)<<"\t" << obj.Pcos.at<float>(ii,jj)<< endl;
	//				TempPhase.at<double>(ii, jj) = atan2(-obj.Psin.at<double>(ii, jj), -obj.Pcos.at<double>(ii, jj)) + M_PI;
	//				k.at<double>(ii, jj) = round((F * Phase.at<double>(ii, jj) - TempPhase.at<double>(ii, jj)) / (2 * M_PI));
	//				//cout << "TempPhase.at<float>(ii,jj)=" << TempPhase.at<float>(ii, jj) << endl;
	//				//cout << "k(ii,jj)=" << k.at<float>(ii, jj) << endl;

	//			}
	//		}
	//		Phase = TempPhase / F + 2 * k * M_PI / F;
	//		//Mat P_TEST;
	//		//normalize(Phase, P_TEST, 1.0, 0, NORM_MINMAX);
	//		//namedWindow("P_TEST");
	//		//imshow("P_TEST", P_TEST);
	//		//waitKey(0);
	//		/*================================================================================
	//		cout << "================Phase(F=else)=============" << endl;
	//		for (int mm = 0; mm < Img_f.cols; mm++)
	//		{
	//			cout << Phase.at<float>(0, mm) << "\t";
	//		}
	//		================================================================================*/
	//	}

	//}
    //解相位，改变Ac Bc Phase
	WrapPhase(obj, Ac, Bc, Phase, TempPhase, k);\
	//显示解相位结果
	imshow_float(Ac, Bc, Phase);
	//根据Bc的值作为掩膜
	filter_Kernel(Bc, Phase, Ac, Bc);
	//string Txt_Ac = "..\\x64\\Debug\\original_data\\VS_Ac.txt";
	//SaveTxt(Ac, Txt_Ac);
	//string Txt_Bc = "..\\x64\\Debug\\original_data\\VS_Bc.txt";
	//SaveTxt(Bc, Txt_Bc);
	//string Txt_phase = "..\\x64\\Debug\\original_data\\VS_phase.txt";
	//SaveTxt(Phase, Txt_phase);
	/*下面验证了上述掩膜对Phase在该函数外及后续的应用是掩膜变化后的*/
	//double test_MinValue, test_MaxValue;
	//minMaxLoc(Phase, &test_MinValue, &test_MaxValue, 0, 0);
	//cout << "MinValue=" << test_MinValue << "以及" << "MaxValue=" << test_MaxValue << endl;
	//计算点云，保存到类实例obj的XYZ中
	pointcloud(CameraM, ProjectorM, obj, Phase);  //传入校准矩阵
	//string Txt_X = "..\\x64\\Debug\\original_data\\VS_objX.txt";
	//SaveTxt(obj.X, Txt_X);
	//string Txt_Y = "..\\x64\\Debug\\original_data\\VS_objY.txt";
	//SaveTxt(obj.Y, Txt_Y);
	//string Txt_Z = "..\\x64\\Debug\\original_data\\VS_objZ.txt";
	//SaveTxt(obj.Z, Txt_Z);
	//保存数据
	obj.Func_Save();
	obj.Func_SaveAsBMP(Ac, 1, 1);
	obj.Func_SaveAsBMP(Bc, 1, 0);
	return 3;


}