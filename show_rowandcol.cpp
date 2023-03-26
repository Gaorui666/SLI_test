/*显示480*640的Mat的某一行或某一列，注意Mat内的元素是double类型*/
#include"GetPhase.h"
void Show_rowandcol(Mat& mat, int r1_c0,int n,string& name)    //n表示第几行/列
{
	if (r1_c0 == 1)   //显示某一行时r1_c0==1
	{
		cout << "\n===================================" <<name<<"第" <<n+1<<"行如下" <<"==================" << endl;
		for (int mm = 0; mm < 640; mm++)
		{
			cout << mat.at<double>(n, mm) << "\t";
		}
	}
	if (r1_c0 == 0)      //显示某一列时r1_c0==0
	{
		cout << "\n==================================="<<name << "第" << n+1 << "列如下" << "==================" << endl;
		for (int mm = 0; mm < 480; mm++)
		{
			cout << mat.at<double>(mm, n) << "\t";
		}
	}



}