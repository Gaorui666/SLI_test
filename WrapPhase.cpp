#include"WrapPhase.h"
#include"show_float.h"
#include"SaveTxt.h"

Pattern WrapPhase(Pattern& Object, Mat& Ac, Mat& Bc, Mat& Phase,Mat& TempPhase,Mat& k)
{
	//��ͼ��������Ƶ��vectorȫ�ֱ�����������
	vector<int>& NSet = Pattern_num;
	vector<int>& fSet = Freq;
	//��ȡƵ���������Լ�����ԭʼ������Դ洢·��
	int Freqlevel = sizeof(fSet) / sizeof(fSet[0]);   //Ƶ����
	char filename[100];
	const char filepath[100] = "..\\original_data\\%04d.bmp";

	for (int i = 0; i < Freqlevel; i++)//��������Ƶ��
	{

		int F = *(fSet.data() + i); //ĳһ��Ƶ��ֵ	
		int N = *(NSet.data() + i); //��Ƶ�ʶ�Ӧ��n��ͼ
		//! Ϊʲô�������obj.Psin.zeros���޷�������أ�
		cout << " Ƶ��������" << *(fSet.data() + i) << "��Ƶ�ʶ�Ӧ��ͼƬ����" << *(NSet.data() + i) << endl;

		//����ĳ��F��Ӧ��N��ͼƬ��������Psin��Pcos
		for (int j = 0; j < N; j++)
		{
			int kk = i * N + j;
			sprintf_s(filename, filepath, kk);
			cout << "���ڶ�����000" << kk << "ͼ" << endl;
			Object.Img = imread(filename);  //��ȡͬһƵ���¶�Ӧ�Ķ�����ĳ��ͼ
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
			//����ÿһ��Ԫ�ؼ�����λֵ
			for (int ii = 0; ii < Object.height; ii++)  //r_Img=480��
			{
				for (int jj = 0; jj < Object.width; jj++)
				{
					Phase.at<double>(ii, jj) = atan2(-Object.Psin.at<double>(ii, jj), -Object.Pcos.at<double>(ii, jj)) + M_PI;

				}
			}
			Ac = Ac / N;
			// sqrt( A, B)�Ľ���Ϊ������A��ƽ������ŵ�����B�У�����Ҫ���¸�ֵ��
			sqrt(Object.Psin.mul(Object.Psin) + Object.Pcos.mul(Object.Pcos), Bc);
			Bc = 2.0 / N * Bc;

		}
		else
		{
			//�����ÿһ���TempPhase
			for (int ii = 0; ii < Object.height; ii++)
			{
				for (int jj = 0; jj < Object.width; jj++)
				{
					//cout << "Psin.at<float>"<<"("<<ii<<","<<jj<<")��Pcos: " << obj.Psin.at<float>(ii, jj)<<"\t" << obj.Pcos.at<float>(ii,jj)<< endl;
					TempPhase.at<double>(ii, jj) = atan2(-Object.Psin.at<double>(ii, jj), -Object.Pcos.at<double>(ii, jj)) + M_PI;
					k.at<double>(ii, jj) = round((F * Phase.at<double>(ii, jj) - TempPhase.at<double>(ii, jj)) / (2*M_PI));
					//cout << "TempPhase.at<float>(ii,jj)=" << TempPhase.at<float>(ii, jj) << endl;
					//cout << "k(ii,jj)=" << k.at<float>(ii, jj) << endl;

				}
			}
			Phase = TempPhase / F + 2 * k * M_PI / F;

		}

	}

	return Object;
}