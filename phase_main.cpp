//
////#include<iostream>
////#include "GetPhase.h"
////using namespace std;
////int main()
////{
////	const char* folder = R"(D:\GAORUI\code\original_data)";
////	int NSet[]={ 4,4,4,4,4,4,4,4 };
////	int fSet[]={ 1,2,4,8,12,16,24,32 };
////	cout << sizeof(fSet) << endl;
////	cout << sizeof(int) << endl;
////
////	int f_L;
////	f_L = GetPhase(folder, NSet, 8, fSet, 8);
////	cout << f_L << endl;
////	return 0;
////
////}
//#include<opencv2/opencv.hpp>
//#include<iostream>
//#include <string>
//#include"GetPhase.h"
//#define _USE_MATH_DEFINES
//#include"math.h"
//using namespace cv;
//using namespace std;
//
//Mat vector2mat(vector<uchar>output, Size2d size = { 480,640 })
//{
//	Mat out_result(size.height, size.width, CV_8UC1, Scalar(0));
//	out_result.data = output.data();
//	return out_result;
//}
//int main() {
//	char filename[50];
//	 // 注意文件路径和你所对应的图片
//
//	int NSet[]={ 4,4,4,4,4,4,4,4 };
//	int fSet[]={ 1,2,4,8,12,16,24,32 };
//	int r_Img=480;
//	int c_Img=640;
//	Mat Img,Img_1,Img_f;   //Mat(int rows, int cols, int type);
//	Mat Ac(480, 640, CV_32F, Scalar::all(0));
//	Mat Bc(480, 640, CV_32F, Scalar::all(0));
//
//	Mat Phase(480, 640, CV_32F, Scalar::all(0));
//	Mat TempPhase(480, 640, CV_32F, Scalar::all(0));
//	Mat k(480, 640, CV_32F, Scalar::all(0));
//	int Freqlevel = sizeof(fSet) / sizeof(fSet[0]);
//	//getphase(NSet, 8, fSet, 8, Img, Ac, Bc, Psin, Pcos, Phase);
//		for (int i = 0; i < Freqlevel; i++)//遍历各个频率
//		{
//
//			int F = *(fSet + i); //某一个频率值	
//			int N = *(NSet + i); //该频率对应的n幅图
//			Mat Psin(480, 640, CV_32F, Scalar::all(0));
//			Mat Pcos(480, 640, CV_32F, Scalar::all(0));
//			cout << " 频率现在是" << *(fSet + i)<<"该频率对应的图片数是" << *(NSet + i) << endl;
//
//
//	        //读入某个F对应的N幅图片，并计算Psin和Pcos
//			for (int j = 0; j < N; j++)
//			{
//				//char folder[50];
//				int kk = i * N + j;
//				sprintf_s(filename, "D:\\GAORUI\\code\\original_data\\%04d.bmp", kk);
//				//string filename = R"D:\GAORUI\code\original_data\0001.bmp";
//				cout << "现在读的是000" << kk << "图" << endl;
//				//cout << sin(2 * M_PI) << endl;
//
//				Img = imread(filename);  //获取同一频率下对应的多幅里的某张图
//				//灰度化处理
//				Mat Img_split[3];
//				split(Img, Img_split);
//				//cvtColor(Img_1, Img, CV_BGR2GRAY);
//				r_Img = Img.rows;//返回矩阵的行数
//				c_Img = Img.cols;  //返回矩阵的列数
//				//把vector转换成单通道mat
//				Mat Img_one = Img_split[0].clone();
//				/*
//				//namedWindow("Img_one", 1);
//				//namedWindow("Img_split[1]", 1);
//				//namedWindow("Img_split[2]", 1);
//				//imshow("Img_one", Img_one);
//				//imshow("Img_split[1]", Img_split[1]);
//				//imshow("Img_split[2]", Img_split[2]);
//				//waitKey(0);
//				// 
//				// 
//				// 
//				//把Mat转换成array
//				// Array(r_Img * c_Img);
//				//array Img_1= 
//				//Pcos = Psin + Img * 2;
//				//vector<uchar> array(r_Img* c_Img);
//				//把mat转换成一维数组
//				//uchar* array = new uchar[Img.rows * Img.cols];
//				*/
//				//把mat的数据类型从CV_8UC(n)转到CV_32FC(n)，
//				//其中8U为Unsigned 8bits uchar 0~255，32F为Float 32bits float 3.4E38～3.4E38
//				//Mat Img_f;
//				Img_one.convertTo(Img_f, CV_32F);//!!!!这里修改成比例因子是1
//				//namedWindow("Img_float", 1);
//				//imshow("Img_float", Img_f);
//				//waitKey(0);
//
//
//				
//
//				//int s = Img_f.channels();
//				//int flag_Img = Img_f.flags;
//				//int Img_f_type = Img_f.type();
//				//cout << "Img_f的channels是" << s << endl;
//				//cout << "Img_f的flags是" << flag_Img << endl;
//				//cout << "Img_one的type是" << Img_one.type() << endl;
//				//cout << "Img_f的type是" << Img_f_type << endl;
//				//cout << "===========Psin==================" << endl;
//				Psin = Psin + Img_f * sin(2 * M_PI * j / N);
//				/*==========================================================================
//				for (int mm = 0; mm < Img_f.cols; mm++)
//				{
//					cout << Psin.at<float>(0, mm) << "\t";
//				}
//				cout << "=============Pcos================" << endl;
//				===========================================================================*/
//				Pcos = Pcos + Img_f * cos(2 * M_PI * j / N);
//				/*================================================================================
//				for (int mm = 0; mm < Img_f.cols; mm++)
//				{
//					cout << Pcos.at<float>(0, mm) << "\t";
//				}
//				===============================================================================*/
//
//
//				if (F == 1)
//				{
//					Ac = Ac + Img_f;
//					/*================================================================================
//					cout << "================Ac=============" << endl;
//					for (int mm = 0; mm < Img_f.cols; mm++)
//					{
//						cout << Ac.at<float>(0, mm) << "\t";
//					}
//					===============================================================================*/
//				}
//			}
//
//			if (F == 1)
//			{
//				//遍历每一个元素计算相位值
//				for (int ii = 0; ii < 480; ii++)  //r_Img=480行
//				{
//					for (int jj = 0; jj < 640; jj++)
//					{
//						
//						Phase.at<float>(ii, jj) = atan2(-Psin.at<float>(ii, jj), -Pcos.at<float>(ii, jj))+M_PI;
//						/*验证性代码
//						cout << "Psin.at<float>值=" << Psin.at<float>(ii, jj) << endl;
//						cout << "Pcos.at<float>值=" << Pcos.at<float>(ii, jj) << endl;
//						cout << "atan2(-Psin.at<float>(ii, jj), -Pcos.at<float>(ii, jj))=" << atan2(-Psin.at<float>(ii, jj), -Pcos.at<float>(ii, jj)) << endl;
//						cout << "atan2(Psin.at<float>(ii, jj), Pcos.at<float>(ii, jj))=" << atan2(Psin.at<float>(ii, jj), Pcos.at<float>(ii, jj)) << endl;
//						cout << "atan2(-1*Psin.at<float>(ii, jj), -1*Pcos.at<float>(ii, jj))=" << atan2(-1 * Psin.at<float>(ii, jj), -1 * Pcos.at<float>(ii, jj)) << endl;
//
//						cout << Phase.at<float>(ii,jj) << "\t";
//						*/
//
//					}
//				}
//				Ac = Ac / N;
//				// sqrt( A, B)的解释为将矩阵A开平方结果放到矩阵B中，不需要重新赋值。
//				sqrt(Psin.mul(Psin) + Pcos.mul(Pcos), Bc);
//				Bc = 2.0 / N * Bc;
//				/*=============================================================================
//				cout << "================Phase(F=1)=============" << endl;
//				for (int mm = 0; mm < Img_f.cols; mm++)
//				{
//					cout << Phase.at<float>(0, mm) << "\t";
//				}
//				=============================================================================*/
//			}
//			else
//			{
//				//计算出每一点的TempPhase
//				for (int ii = 0; ii < 480; ii++)
//				{
//					for (int jj = 0; jj < 640; jj++)
//					{
//						    //cout << "Psin.at<float>(ii,jj)与Pcos:" << Psin.at<float>(ii, jj)<<"\t" <<Pcos.at<float>(ii,jj)<< endl;
//							TempPhase.at<float>(ii, jj) = atan2(-Psin.at<float>(ii, jj), -Pcos.at<float>(ii, jj)) + M_PI;
//							k.at<float>(ii, jj) = round((F * Phase.at<float>(ii, jj) - TempPhase.at<float>(ii, jj)) / (2 * M_PI));
//							//cout << "TempPhase.at<float>(ii,jj)=" << TempPhase.at<float>(ii, jj) << endl;
//							//cout << "k(ii,jj)=" << k.at<float>(ii, jj) << endl;
//
//					}
//				}
//				Phase = TempPhase / F + 2 * k * M_PI / F;
//				/*================================================================================
//				cout << "================Phase(F=else)=============" << endl;
//				for (int mm = 0; mm < Img_f.cols; mm++)
//				{
//					cout << Phase.at<float>(0, mm) << "\t";
//				}
//				================================================================================*/
//			}
//	
//		}
//		//cout << "phase的某一个值是" << Phase.at<float>(1, 1) << endl;
//		cout <<"\n" << "===================phase======================" << endl;
//		for (int mm = 0; mm < Img_f.cols; mm++)
//		{
//			cout << Phase.at<float>(0, mm) << "\t";
//		}
//		cout << "\n" << "===================Ac======================" << endl;
//		for (int mm = 0; mm < Img_f.cols; mm++)
//		{
//			cout << Ac.at<float>(0, mm) << "\t";
//		}
//		Mat norm_Ac,norm_Bc,norm_Phase;
//		normalize(Ac, norm_Ac, 1.0, 0, NORM_MINMAX);
//		normalize(Bc, norm_Bc, 1.0, 0, NORM_MINMAX);
//		normalize(Phase, norm_Phase, 1.0, 0, NORM_MINMAX);
//		namedWindow("norm_Ac");
//		imshow("norm_Ac", norm_Ac);
//		waitKey(0);
//		namedWindow("norm_Bc");
//		imshow("norm_Bc", norm_Bc);
//		waitKey(0);
//		namedWindow("norm_Phase");
//		imshow("norm_Phase", norm_Phase);
//		waitKey(0);
//	//
//	//namedWindow("image");
//	//imshow("image", Img);
//	//waitKey(0);
//	return 3;
//}
