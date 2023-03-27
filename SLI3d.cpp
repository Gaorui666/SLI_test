#include<opencv2/opencv.hpp>
#include<iostream>
#include <string>
#include"GetPhase.h"
#include"show_float.h"
#include"pointcloud.h"
#include"show_randc.h"
#include"Filter_Kernel.h"
#define _USE_MATH_DEFINES
#include"math.h"
using namespace cv;
using namespace std;

int main() {
	char filename[50];
	// 注意文件路径和你所对应的图片
	Pattern obj;
	int NSet[] = { 4,4,4,4,4,4,4,4 };
	int fSet[] = { 1,2,4,8,12,16,24,32 };
	Mat CameraM = (Mat_<double>(3, 4) <<14.482179029727, -0.0756069225994708, 3.90009297641972, 349.8528298221, 
		0.0329090032063584, -14.2355151081274, 3.43483510271307, 365.592830043863, 
		0.000406751331336066, 0.000141240585119761, 0.0129506560912335, 1);
	Mat ProjectorM = (Mat_<double>(3, 4) << 0.119031855442746, -0.00148766326981583, 0.0342189923344704, 2.6554776313302,
		0.00124299057297682, -0.159561909244587, 0.0622804102444807, 5.21798183908058, 
		0.000160084540869339, -0.000439436532245431, 0.0113912158012247, 1 );

	Mat Ac(480, 640, CV_64F, Scalar::all(0));
	Mat Bc(480, 640, CV_64F, Scalar::all(0));
	Mat Phase(480, 640, CV_64F, Scalar::all(0));
	Mat TempPhase(480, 640, CV_64F, Scalar::all(0));
	Mat k(480, 640, CV_64F, Scalar::all(0));

	int Freqlevel = sizeof(fSet) / sizeof(fSet[0]);   //频率数

	for (int i = 0; i < Freqlevel; i++)//遍历各个频率
	{

		int F = *(fSet + i); //某一个频率值	
		int N = *(NSet + i); //该频率对应的n幅图
		//! 为什么在这里把obj.Psin.zeros是无法置零的呢？
		cout << " 频率现在是" << *(fSet + i) << "该频率对应的图片数是" << *(NSet + i) << endl;

		//读入某个F对应的N幅图片，并计算Psin和Pcos
		for (int j = 0; j < N; j++)
		{
			int kk = i * N + j;
			sprintf_s(filename, "D:\\GAORUI\\code\\original_data\\%04d.bmp", kk);
			cout << "现在读的是000" << kk << "图" << endl;
			obj.Img = imread(filename);  //获取同一频率下对应的多幅里的某张图
			obj.Get_W_H();
			obj.Mat8UC3To8U();
			obj.Mat8UTo32F();
			obj.Psin_Pcos(F,j,N);

			if (F == 1)
			{
				Ac = Ac + obj.Img_32F;

			}

		}

		if (F == 1)
		{
			//遍历每一个元素计算相位值
			for (int ii = 0; ii < obj.height; ii++)  //r_Img=480行
			{
				for (int jj = 0; jj < obj.width; jj++)
				{
					Phase.at<double>(ii, jj) = atan2(-obj.Psin.at<double>(ii, jj), -obj.Pcos.at<double>(ii, jj)) + M_PI;	
					
				}
			}
			Ac = Ac / N;
			// sqrt( A, B)的解释为将矩阵A开平方结果放到矩阵B中，不需要重新赋值。
			sqrt(obj.Psin.mul(obj.Psin) + obj.Pcos.mul(obj.Pcos), Bc);
			Bc = 2.0 / N * Bc;

		}
		else
		{
			//计算出每一点的TempPhase
			for (int ii = 0; ii < obj.height; ii++)
			{
				for (int jj = 0; jj < obj.width; jj++)
				{
					//cout << "Psin.at<float>"<<"("<<ii<<","<<jj<<")与Pcos: " << obj.Psin.at<float>(ii, jj)<<"\t" << obj.Pcos.at<float>(ii,jj)<< endl;
					TempPhase.at<double>(ii, jj) = atan2(-obj.Psin.at<double>(ii, jj), -obj.Pcos.at<double>(ii, jj)) + M_PI;
					k.at<double>(ii, jj) = round((F * Phase.at<double>(ii, jj) - TempPhase.at<double>(ii, jj)) / (2 * M_PI));


				}
			}
			Phase = TempPhase / F + 2 * k * M_PI / F;
			//Mat P_TEST;
			//normalize(Phase, P_TEST, 1.0, 0, NORM_MINMAX);
			//namedWindow("P_TEST");
			//imshow("P_TEST", P_TEST);
			//waitKey(0);

		}

	}

	imshow_float(Ac, Bc, Phase);
	filter_Kernel(Bc, Phase, Ac, Bc);
	/*下面验证了上述掩膜对Phase在该函数外及后续的应用是掩膜变化后的*/
	//double test_MinValue, test_MaxValue;
	//minMaxLoc(Phase, &test_MinValue, &test_MaxValue, 0, 0);
	//cout << "MinValue=" << test_MinValue << "以及" << "MaxValue=" << test_MaxValue << endl;
	pointcloud(CameraM, ProjectorM, obj, Phase);  //传入校准矩阵

	obj.Func_Save();
	obj.Func_SaveAsBMP(Ac, 1, 1);
	obj.Func_SaveAsBMP(Bc, 1, 0);
	return 3;


}
