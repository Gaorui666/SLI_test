#include "GetPhase.h"
#include"show_randc.h"
#include"SaveTxt.h"

void Pattern::Get_W_H()
{
	height = Img.rows;
	width = Img.cols;
}

Mat Pattern::Mat8UC3To8U() //����ͨ����ͼ��Mat��ɵ�ͨ�������ܽ��к�������
{
	split(Img, Img_split);
	Img_one = Img_split[0].clone();
	return Img_one;
}
Mat Pattern:: Mat8UTo32F()   				//��mat���������ʹ�CV_8UC(n)ת��CV_32FC(n)��
//����8UΪUnsigned 8bits uchar 0~255��32FΪFloat 32bits float 3.4E38��3.4E38
{
	Img_one.convertTo(Img_32F, CV_64F);
	return Img_32F;
}
void Pattern::Psin_Pcos(int& f,int& num,int& N)
{

	//Ƶ��Ϊ1��ʱ��ֱ�ӽ��м���
	//cout << num;
	//cout<< sin(2 * M_PI * num / N);
		if (num == 0)  //ÿ��Ƶ�ʱ仯ʱ��Psin��Pcos��Ϊ0
		{
			Psin = Mat::zeros(480, 640, CV_64F);
			Pcos = Mat::zeros(480, 640, CV_64F);
		}
		//for (int ii = 0; ii < 640; ii++)
		//{
		//	cout << Psin.at<float>(0, ii) << "\t";
		//}
//		cout << "===================================" << endl;
		Psin = Psin + Img_32F * sin(2 * M_PI * num / N);
		Pcos = Pcos + Img_32F * cos(2 * M_PI * num / N);

}
void Pattern::Func_SaveAsBMP(Mat& InputMat,int Scale1No0,int n)
{
	if (Scale1No0 == 1)  //���������Сֵ��������
	{
		cout << "�������Mat����������ΪBMP" << endl;
		double MinValue, MaxValue;
		minMaxLoc(InputMat, &MinValue, &MaxValue, 0, 0);
		cout << "MinValue=" << MinValue << "�Լ�" << "MaxValue=" << MaxValue << endl;
		Mat InputMat_s = (InputMat - MinValue) / (MaxValue - MinValue);
		Mat InputMat_s_end = InputMat_s * 255;
		//������õ�end
		Mat end;
		InputMat_s_end.convertTo(end, CV_8U);  //imwrite�Ľ������й���8bit����16�Լ�32bit��Ӧ��ʽ��˵��
		//cout << "unit8�������Ϊ" << endl;
		//for (int ccc = 0; ccc < 640; ccc++)
		//{
		//	cout << (float)end.at<uchar>(100,ccc) << "\t";
		//}
		if (n == 1)
		{
			string file_name = "..\\original_data\\TESTC.bmp";
			imwrite(file_name, end);
		}
		else
		{
			string file_name = "..\\original_data\\TESTI.bmp";
			imwrite(file_name, end);
		}

	}
	else          //ֱ��ȡ��
	{
		Mat end;
		cout << "�������Matֱ��ȡ��������ΪBMP" << endl;
		InputMat.convertTo(end, CV_8U);//convertTo����ȡ���Ĺ���
		if (n == 1)
		{
			string file_name = "..\\original_data\\TESTC.bmp";
			imwrite(file_name, end);
		}
		else
		{
			string file_name = "..\\original_data\\TESTI.bmp";
			imwrite(file_name, end);
		}
		
	}

}
void Pattern::Func_file(char* s,Mat& Input_64F)
{
	Mat InputMat;
	Input_64F.convertTo(InputMat, CV_32F);
	FILE* fp;
	errno_t err; char FileName[100];
	sprintf_s(FileName, "..\\original_data\\%s.byt", s);
	err = fopen_s(&fp, FileName, "wb");
	if (err == 1)
	{
		cout << "fopen error!" << endl;
	}
	else
	{
		cout << "sizeof(float)=" << sizeof(float) << endl;
		cout << "InputMat.rows=" << InputMat.rows << endl;

		fwrite(InputMat.data, sizeof(float), InputMat.rows, fp);
		fclose(fp);
	}
}

void Pattern::Func_Save()
{
	//string name_5 = "obj.X";   //��ʾC������������ʽ��100��
	//Show_rowandcol(X, 0, 0, name_5);
	//Show_rowandcol(X, 0, 99, name_5);
	//Show_rowandcol(X, 1, 0, name_5);
	//Show_rowandcol(X, 1, 99, name_5);
	
	Mat X_end = X.reshape(0, 1).t();
	//cout << "\nX���һά�������������" << endl;
	//for (int kk = 0; kk < 1440; kk++)
	//{
	//	cout << X_end.at<double>(kk) << endl;;
	//}
	//���﷢��X�зǳ���1890��ֵ����-200��ֵ�����Ƕ�Ӧ��matlab�������Сֵ��40 -40����
	
	Mat Y_end = Y.reshape(0, 1).t();
	Mat Z_end = Z.reshape(0, 1).t();

	char s_X[] = "TESTX";
	char s_Y[] = "TESTY";
	char s_Z[] = "TESTZ";
	Func_file(s_X, X_end);
	Func_file(s_Y, Y_end);
	Func_file(s_Z, Z_end);
}


