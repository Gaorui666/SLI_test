#include"WrapPhase.h"
#include"show_float.h"
#include"SaveTxt.h"

Pattern WrapPhase(Pattern& Object, Mat& Ac, Mat& Bc, Mat& Phase,Mat& TempPhase,Mat& k)
{
	//把图案数量和频率vector全局变量重新命名
	vector<int>& NSet = Pattern_num;
	vector<int>& fSet = Freq;
	//获取频率数量，以及定义原始数据相对存储路径
	int Freqlevel = sizeof(fSet) / sizeof(fSet[0]);   //频率数
	char filename[100];
	const char filepath[100] = "..\\original_data\\%04d.bmp";

	for (int i = 0; i < Freqlevel; i++)//遍历各个频率
	{

		int F = *(fSet.data() + i); //某一个频率值	
		int N = *(NSet.data() + i); //该频率对应的n幅图
		//! 为什么在这里把obj.Psin.zeros是无法置零的呢？
		cout << " 频率现在是" << *(fSet.data() + i) << "该频率对应的图片数是" << *(NSet.data() + i) << endl;

		//读入某个F对应的N幅图片，并计算Psin和Pcos
		for (int j = 0; j < N; j++)
		{
			int kk = i * N + j;
			sprintf_s(filename, filepath, kk);
			cout << "现在读的是000" << kk << "图" << endl;
			Object.Img = imread(filename);  //获取同一频率下对应的多幅里的某张图
			Object.Get_W_H();
			Object.Mat8UC3To8U();
			Object.Mat8UTo32F();
			Object.Psin_Pcos(F, j, N);

			if (F == 1)
			{
				Ac = Ac + Object.Img_32F;
			}

		}

		if (F == 1)
		{
			//遍历每一个元素计算相位值
			for (int ii = 0; ii < Object.height; ii++)  //r_Img=480行
			{
				for (int jj = 0; jj < Object.width; jj++)
				{
					Phase.at<double>(ii, jj) = atan2(-Object.Psin.at<double>(ii, jj), -Object.Pcos.at<double>(ii, jj)) + M_PI;

				}
			}
			Ac = Ac / N;
			// sqrt( A, B)的解释为将矩阵A开平方结果放到矩阵B中，不需要重新赋值。
			sqrt(Object.Psin.mul(Object.Psin) + Object.Pcos.mul(Object.Pcos), Bc);
			Bc = 2.0 / N * Bc;

		}
		else
		{
			//计算出每一点的TempPhase
			for (int ii = 0; ii < Object.height; ii++)
			{
				for (int jj = 0; jj < Object.width; jj++)
				{
					//cout << "Psin.at<float>"<<"("<<ii<<","<<jj<<")与Pcos: " << obj.Psin.at<float>(ii, jj)<<"\t" << obj.Pcos.at<float>(ii,jj)<< endl;
					TempPhase.at<double>(ii, jj) = atan2(-Object.Psin.at<double>(ii, jj), -Object.Pcos.at<double>(ii, jj)) + M_PI;
					k.at<double>(ii, jj) = round((F * Phase.at<double>(ii, jj) - TempPhase.at<double>(ii, jj)) / (2*M_PI));


				}
			}
			Phase = TempPhase / F + 2 * k * M_PI / F;

		}

	}

	return Object;
}
