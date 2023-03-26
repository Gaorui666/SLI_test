/*
Bc>5的置为1，其他的为0作为掩膜对Ac Bc Phase进行处理
*/
#include"Filter_Kernel.h"
void filter_Kernel(Mat& B, Mat& InputMat1, Mat& InputMat2, Mat& InputMat3)
{
	Mat MyKernel = Mat::ones(InputMat1.rows, InputMat1.cols, CV_64F);
	threshold(B, MyKernel, 5, 1, THRESH_BINARY);  //kernel里Bc对应值大于5的索引位置置1，小于的0
	InputMat1 = InputMat1.mul(MyKernel);   //kernel作为掩膜
	InputMat2 = InputMat2.mul(MyKernel);   //kernel作为掩膜
	InputMat3 = InputMat3.mul(MyKernel);   //kernel作为掩膜
	double test_MinValue, test_MaxValue;
	minMaxLoc(InputMat1, &test_MinValue, &test_MaxValue, 0, 0);
	cout << "MinValue=" << test_MinValue << "以及" << "MaxValue=" << test_MaxValue << endl;
	minMaxLoc(InputMat2, &test_MinValue, &test_MaxValue, 0, 0);
	cout << "MinValue=" << test_MinValue << "以及" << "MaxValue=" << test_MaxValue << endl;
	minMaxLoc(InputMat3, &test_MinValue, &test_MaxValue, 0, 0);
	cout << "MinValue=" << test_MinValue << "以及" << "MaxValue=" << test_MaxValue << endl;

}