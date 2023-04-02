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
	// ע���ļ�·����������Ӧ��ͼƬ
	Pattern obj;

	//��ȡƵ�� ͼ������ У׼����Mc��Mp������ȫ�ֱ�����
	char M_path[] = "..\\original_data\\calibration.txt";
	char M_path2[] = "..\\original_data\\FnP.txt";
	Readtxt(M_path);
	Raedtxt_FnP(M_path2);
	//Ԥ�ȶ�ȡһ��ͼƬ��ȡ��Ӧ�Ŀ�͸ߣ�����Ac Bc����main�в��ϳ��ֵ�Mat�Ĵ���
	string First_Img = "..\\original_data\\0000.bmp";
	Mat Img_one = imread(First_Img);
	int height = Img_one.rows;
	int width = Img_one.cols;
	Mat Ac(height, width, CV_64F, Scalar::all(0));
	Mat Bc(height, width, CV_64F, Scalar::all(0));
	Mat Phase(height, width, CV_64F, Scalar::all(0));
	Mat TempPhase(height, width, CV_64F, Scalar::all(0));
	Mat k(height, width, CV_64F, Scalar::all(0));

	//for (int i = 0; i < Freqlevel; i++)//��������Ƶ��
	//{

	//	int F = *(fSet + i); //ĳһ��Ƶ��ֵ	
	//	int N = *(NSet + i); //��Ƶ�ʶ�Ӧ��n��ͼ
	//	//! Ϊʲô�������obj.Psin.zeros���޷�������أ�
	//	cout << " Ƶ��������" << *(fSet + i) << "��Ƶ�ʶ�Ӧ��ͼƬ����" << *(NSet + i) << endl;

	//	//����ĳ��F��Ӧ��N��ͼƬ��������Psin��Pcos
	//	for (int j = 0; j < N; j++)
	//	{
	//		int kk = i * N + j;
	//		sprintf_s(filename, ".\\original_data\\%04d.bmp", kk);
	//		cout << "���ڶ�����000" << kk << "ͼ" << endl;
	//		obj.Img = imread(filename);  //��ȡͬһƵ���¶�Ӧ�Ķ�����ĳ��ͼ
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
	//		//��Matת����array
	//		// Array(r_Img * c_Img);
	//		//array Img_1=
	//		//Pcos = Psin + Img * 2;
	//		//vector<uchar> array(r_Img* c_Img);
	//		//��matת����һά����
	//		//uchar* array = new uchar[Img.rows * Img.cols];
	//		*/
	//		//��mat���������ʹ�CV_8UC(n)ת��CV_32FC(n)��
	//		//����8UΪUnsigned 8bits uchar 0~255��32FΪFloat 32bits float 3.4E38��3.4E38
	//		//Mat Img_f;
	//		//Img_one.convertTo(Img_f, CV_32F);//!!!!�����޸ĳɱ���������1
	//		//namedWindow("Img_float", 1);
	//		//imshow("Img_float", Img_f);
	//		//waitKey(0);
	//		//int s = Img_f.channels();
	//		//int flag_Img = Img_f.flags;
	//		//int Img_f_type = Img_f.type();
	//		//cout << "Img_f��channels��" << s << endl;
	//		//cout << "Img_f��flags��" << flag_Img << endl;
	//		//cout << "Img_one��type��" << Img_one.type() << endl;
	//		//cout << "Img_f��type��" << Img_f_type << endl;
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
	//		//����ÿһ��Ԫ�ؼ�����λֵ
	//		for (int ii = 0; ii < obj.height; ii++)  //r_Img=480��
	//		{
	//			for (int jj = 0; jj < obj.width; jj++)
	//			{
	//				Phase.at<double>(ii, jj) = atan2(-obj.Psin.at<double>(ii, jj), -obj.Pcos.at<double>(ii, jj)) + M_PI;	
	//				//cout << "Psin.at<float>ֵ=" << obj.Psin.at<float>(ii, jj) << endl;
	//				//cout << "Pcos.at<float>ֵ=" << obj.Pcos.at<float>(ii, jj) << endl;
	//				//cout << "atan2(-Psin.at<float>(ii, jj), -Pcos.at<float>(ii, jj))=" << atan2(-obj.Psin.at<float>(ii, jj), -obj.Pcos.at<float>(ii, jj)) << endl;
	//				//cout << "atan2(Psin.at<float>(ii, jj), Pcos.at<float>(ii, jj))=" << atan2(obj.Psin.at<float>(ii, jj), obj.Pcos.at<float>(ii, jj)) << endl;
	//				//cout << "atan2(-1*Psin.at<float>(ii, jj), -1*Pcos.at<float>(ii, jj))=" << atan2(-1 * obj.Psin.at<float>(ii, jj), -1 * obj.Pcos.at<float>(ii, jj)) << endl;

	//			}
	//		}
	//		Ac = Ac / N;
	//		// sqrt( A, B)�Ľ���Ϊ������A��ƽ������ŵ�����B�У�����Ҫ���¸�ֵ��
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
	//		//�����ÿһ���TempPhase
	//		for (int ii = 0; ii < obj.height; ii++)
	//		{
	//			for (int jj = 0; jj < obj.width; jj++)
	//			{
	//				//cout << "Psin.at<float>"<<"("<<ii<<","<<jj<<")��Pcos: " << obj.Psin.at<float>(ii, jj)<<"\t" << obj.Pcos.at<float>(ii,jj)<< endl;
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
    //����λ���ı�Ac Bc Phase
	WrapPhase(obj, Ac, Bc, Phase, TempPhase, k);\
	//��ʾ����λ���
	imshow_float(Ac, Bc, Phase);
	//����Bc��ֵ��Ϊ��Ĥ
	filter_Kernel(Bc, Phase, Ac, Bc);
	//string Txt_Ac = "..\\x64\\Debug\\original_data\\VS_Ac.txt";
	//SaveTxt(Ac, Txt_Ac);
	//string Txt_Bc = "..\\x64\\Debug\\original_data\\VS_Bc.txt";
	//SaveTxt(Bc, Txt_Bc);
	//string Txt_phase = "..\\x64\\Debug\\original_data\\VS_phase.txt";
	//SaveTxt(Phase, Txt_phase);
	/*������֤��������Ĥ��Phase�ڸú����⼰������Ӧ������Ĥ�仯���*/
	//double test_MinValue, test_MaxValue;
	//minMaxLoc(Phase, &test_MinValue, &test_MaxValue, 0, 0);
	//cout << "MinValue=" << test_MinValue << "�Լ�" << "MaxValue=" << test_MaxValue << endl;
	//������ƣ����浽��ʵ��obj��XYZ��
	pointcloud(CameraM, ProjectorM, obj, Phase);  //����У׼����
	//string Txt_X = "..\\x64\\Debug\\original_data\\VS_objX.txt";
	//SaveTxt(obj.X, Txt_X);
	//string Txt_Y = "..\\x64\\Debug\\original_data\\VS_objY.txt";
	//SaveTxt(obj.Y, Txt_Y);
	//string Txt_Z = "..\\x64\\Debug\\original_data\\VS_objZ.txt";
	//SaveTxt(obj.Z, Txt_Z);
	//��������
	obj.Func_Save();
	obj.Func_SaveAsBMP(Ac, 1, 1);
	obj.Func_SaveAsBMP(Bc, 1, 0);
	return 3;


}