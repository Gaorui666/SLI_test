#include "GetPhase.h"
#include"show_randc.h"
#include"SaveTxt.h"

void Pattern::Get_W_H()
{
	height = Img.rows;
	width = Img.cols;
}

Mat Pattern::Mat8UC3To8U() //将三通道的图像Mat变成单通道，才能进行后续计算
{
	split(Img, Img_split);
	Img_one = Img_split[0].clone();
	return Img_one;
}
Mat Pattern:: Mat8UTo32F()   				//把mat的数据类型从CV_8UC(n)转到CV_32FC(n)，
//其中8U为Unsigned 8bits uchar 0~255，32F为Float 32bits float 3.4E38～3.4E38
{
	Img_one.convertTo(Img_32F, CV_64F);
	return Img_32F;
}
void Pattern::Psin_Pcos(int& f,int& num,int& N)
{

	//频率为1的时候直接进行计算
	//cout << num;
	//cout<< sin(2 * M_PI * num / N);
		if (num == 0)  //每次频率变化时将Psin和Pcos置为0
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
	if (Scale1No0 == 1)  //按照最大最小值比例放缩
	{
		cout << "将输入的Mat放缩并保存为BMP" << endl;
		double MinValue, MaxValue;
		minMaxLoc(InputMat, &MinValue, &MaxValue, 0, 0);
		cout << "MinValue=" << MinValue << "以及" << "MaxValue=" << MaxValue << endl;
		Mat InputMat_s = (InputMat - MinValue) / (MaxValue - MinValue);
		Mat InputMat_s_end = InputMat_s * 255;
		//放缩后得到end
		Mat end;
		InputMat_s_end.convertTo(end, CV_8U);  //imwrite的介绍里有关于8bit还是16以及32bit对应格式的说明
		//cout << "unit8后的数据为" << endl;
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
	else          //直接取整
	{
		Mat end;
		cout << "将输入的Mat直接取整并保存为BMP" << endl;
		InputMat.convertTo(end, CV_8U);//convertTo包含取整的功能
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
	//string name_5 = "obj.X";   //显示C矩阵求倒数行列式第100列
	//Show_rowandcol(X, 0, 0, name_5);
	//Show_rowandcol(X, 0, 99, name_5);
	//Show_rowandcol(X, 1, 0, name_5);
	//Show_rowandcol(X, 1, 99, name_5);
	
	Mat X_end = X.reshape(0, 1).t();
	//cout << "\nX变成一维列向量后的数据" << endl;
	//for (int kk = 0; kk < 1440; kk++)
	//{
	//	cout << X_end.at<double>(kk) << endl;;
	//}
	//这里发现X有非常大1890的值或者-200的值，但是对应的matlab里最大最小值是40 -40左右
	
	Mat Y_end = Y.reshape(0, 1).t();
	Mat Z_end = Z.reshape(0, 1).t();

	char s_X[] = "TESTX";
	char s_Y[] = "TESTY";
	char s_Z[] = "TESTZ";
	Func_file(s_X, X_end);
	Func_file(s_Y, Y_end);
	Func_file(s_Z, Z_end);
}


