/*
Bc>5����Ϊ1��������Ϊ0��Ϊ��Ĥ��Ac Bc Phase���д���
*/
#include"Filter_Kernel.h"
void filter_Kernel(Mat& B, Mat& InputMat1, Mat& InputMat2, Mat& InputMat3)
{
	Mat MyKernel = Mat::ones(InputMat1.rows, InputMat1.cols, CV_64F);
	threshold(B, MyKernel, 5, 1, THRESH_BINARY);  //kernel��Bc��Ӧֵ����5������λ����1��С�ڵ�0
	InputMat1 = InputMat1.mul(MyKernel);   //kernel��Ϊ��Ĥ
	InputMat2 = InputMat2.mul(MyKernel);   //kernel��Ϊ��Ĥ
	InputMat3 = InputMat3.mul(MyKernel);   //kernel��Ϊ��Ĥ
	double test_MinValue, test_MaxValue;
	minMaxLoc(InputMat1, &test_MinValue, &test_MaxValue, 0, 0);
	cout << "MinValue=" << test_MinValue << "�Լ�" << "MaxValue=" << test_MaxValue << endl;
	minMaxLoc(InputMat2, &test_MinValue, &test_MaxValue, 0, 0);
	cout << "MinValue=" << test_MinValue << "�Լ�" << "MaxValue=" << test_MaxValue << endl;
	minMaxLoc(InputMat3, &test_MinValue, &test_MaxValue, 0, 0);
	cout << "MinValue=" << test_MinValue << "�Լ�" << "MaxValue=" << test_MaxValue << endl;

}