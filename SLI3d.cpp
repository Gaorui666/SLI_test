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
	// ע���ļ�·����������Ӧ��ͼƬ
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

	int Freqlevel = sizeof(fSet) / sizeof(fSet[0]);   //Ƶ����

	for (int i = 0; i < Freqlevel; i++)//��������Ƶ��
	{

		int F = *(fSet + i); //ĳһ��Ƶ��ֵ	
		int N = *(NSet + i); //��Ƶ�ʶ�Ӧ��n��ͼ
		//! Ϊʲô�������obj.Psin.zeros���޷�������أ�
		cout << " Ƶ��������" << *(fSet + i) << "��Ƶ�ʶ�Ӧ��ͼƬ����" << *(NSet + i) << endl;

		//����ĳ��F��Ӧ��N��ͼƬ��������Psin��Pcos
		for (int j = 0; j < N; j++)
		{
			int kk = i * N + j;
			sprintf_s(filename, "D:\\GAORUI\\code\\original_data\\%04d.bmp", kk);
			cout << "���ڶ�����000" << kk << "ͼ" << endl;
			obj.Img = imread(filename);  //��ȡͬһƵ���¶�Ӧ�Ķ�����ĳ��ͼ
			obj.Get_W_H();
			obj.Mat8UC3To8U();
			obj.Mat8UTo32F();
			/*
			//namedWindow("Img_one", 1);
			//namedWindow("Img_split[1]", 1);
			//namedWindow("Img_split[2]", 1);
			//imshow("Img_one", Img_one);
			//imshow("Img_split[1]", Img_split[1]);
			//imshow("Img_split[2]", Img_split[2]);
			//waitKey(0);
			//
			//
			//
			//��Matת����array
			// Array(r_Img * c_Img);
			//array Img_1=
			//Pcos = Psin + Img * 2;
			//vector<uchar> array(r_Img* c_Img);
			//��matת����һά����
			//uchar* array = new uchar[Img.rows * Img.cols];
			*/
			//��mat���������ʹ�CV_8UC(n)ת��CV_32FC(n)��
			//����8UΪUnsigned 8bits uchar 0~255��32FΪFloat 32bits float 3.4E38��3.4E38
			//Mat Img_f;
			//Img_one.convertTo(Img_f, CV_32F);//!!!!�����޸ĳɱ���������1
			//namedWindow("Img_float", 1);
			//imshow("Img_float", Img_f);
			//waitKey(0);
			//int s = Img_f.channels();
			//int flag_Img = Img_f.flags;
			//int Img_f_type = Img_f.type();
			//cout << "Img_f��channels��" << s << endl;
			//cout << "Img_f��flags��" << flag_Img << endl;
			//cout << "Img_one��type��" << Img_one.type() << endl;
			//cout << "Img_f��type��" << Img_f_type << endl;
			//cout << "===========Psin==================" << endl;
			obj.Psin_Pcos(F,j,N);
			/*==========================================================================
			for (int mm = 0; mm < Img_f.cols; mm++)
			{
				cout << Psin.at<float>(0, mm) << "\t";
			}
			cout << "=============Pcos================" << endl;
			===========================================================================*/
			/*================================================================================
			for (int mm = 0; mm < Img_f.cols; mm++)
			{
				cout << Pcos.at<float>(0, mm) << "\t";
			}
			===============================================================================*/

			if (F == 1)
			{
				Ac = Ac + obj.Img_32F;
				/*================================================================================
				cout << "================Ac=============" << endl;
				for (int mm = 0; mm < Img_f.cols; mm++)
				{
					cout << Ac.at<float>(0, mm) << "\t";
				}
				===============================================================================*/
			}

		}

		if (F == 1)
		{
			//����ÿһ��Ԫ�ؼ�����λֵ
			for (int ii = 0; ii < obj.height; ii++)  //r_Img=480��
			{
				for (int jj = 0; jj < obj.width; jj++)
				{
					Phase.at<double>(ii, jj) = atan2(-obj.Psin.at<double>(ii, jj), -obj.Pcos.at<double>(ii, jj)) + M_PI;	
					//cout << "Psin.at<float>ֵ=" << obj.Psin.at<float>(ii, jj) << endl;
					//cout << "Pcos.at<float>ֵ=" << obj.Pcos.at<float>(ii, jj) << endl;
					//cout << "atan2(-Psin.at<float>(ii, jj), -Pcos.at<float>(ii, jj))=" << atan2(-obj.Psin.at<float>(ii, jj), -obj.Pcos.at<float>(ii, jj)) << endl;
					//cout << "atan2(Psin.at<float>(ii, jj), Pcos.at<float>(ii, jj))=" << atan2(obj.Psin.at<float>(ii, jj), obj.Pcos.at<float>(ii, jj)) << endl;
					//cout << "atan2(-1*Psin.at<float>(ii, jj), -1*Pcos.at<float>(ii, jj))=" << atan2(-1 * obj.Psin.at<float>(ii, jj), -1 * obj.Pcos.at<float>(ii, jj)) << endl;

				}
			}
			Ac = Ac / N;
			// sqrt( A, B)�Ľ���Ϊ������A��ƽ������ŵ�����B�У�����Ҫ���¸�ֵ��
			sqrt(obj.Psin.mul(obj.Psin) + obj.Pcos.mul(obj.Pcos), Bc);
			Bc = 2.0 / N * Bc;

			/*=============================================================================
			cout << "================Phase(F=1)=============" << endl;
			for (int mm = 0; mm < Img_f.cols; mm++)
			{
				cout << Phase.at<float>(0, mm) << "\t";
			}
			=============================================================================*/
		}
		else
		{
			//�����ÿһ���TempPhase
			for (int ii = 0; ii < obj.height; ii++)
			{
				for (int jj = 0; jj < obj.width; jj++)
				{
					//cout << "Psin.at<float>"<<"("<<ii<<","<<jj<<")��Pcos: " << obj.Psin.at<float>(ii, jj)<<"\t" << obj.Pcos.at<float>(ii,jj)<< endl;
					TempPhase.at<double>(ii, jj) = atan2(-obj.Psin.at<double>(ii, jj), -obj.Pcos.at<double>(ii, jj)) + M_PI;
					k.at<double>(ii, jj) = round((F * Phase.at<double>(ii, jj) - TempPhase.at<double>(ii, jj)) / (2 * M_PI));
					//cout << "TempPhase.at<float>(ii,jj)=" << TempPhase.at<float>(ii, jj) << endl;
					//cout << "k(ii,jj)=" << k.at<float>(ii, jj) << endl;

				}
			}
			Phase = TempPhase / F + 2 * k * M_PI / F;
			//Mat P_TEST;
			//normalize(Phase, P_TEST, 1.0, 0, NORM_MINMAX);
			//namedWindow("P_TEST");
			//imshow("P_TEST", P_TEST);
			//waitKey(0);
			/*================================================================================
			cout << "================Phase(F=else)=============" << endl;
			for (int mm = 0; mm < Img_f.cols; mm++)
			{
				cout << Phase.at<float>(0, mm) << "\t";
			}
			================================================================================*/
		}

	}

	imshow_float(Ac, Bc, Phase);
	filter_Kernel(Bc, Phase, Ac, Bc);
	/*������֤��������Ĥ��Phase�ڸú����⼰������Ӧ������Ĥ�仯���*/
	//double test_MinValue, test_MaxValue;
	//minMaxLoc(Phase, &test_MinValue, &test_MaxValue, 0, 0);
	//cout << "MinValue=" << test_MinValue << "�Լ�" << "MaxValue=" << test_MaxValue << endl;
	pointcloud(CameraM, ProjectorM, obj, Phase);  //����У׼����

	obj.Func_Save();
	obj.Func_SaveAsBMP(Ac, 1, 1);
	obj.Func_SaveAsBMP(Bc, 1, 0);
	return 3;


}