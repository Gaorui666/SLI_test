/*��ʾ480*640��Mat��ĳһ�л�ĳһ�У�ע��Mat�ڵ�Ԫ����double����*/
#include"GetPhase.h"
void Show_rowandcol(Mat& mat, int r1_c0,int n,string& name)    //n��ʾ�ڼ���/��
{
	if (r1_c0 == 1)   //��ʾĳһ��ʱr1_c0==1
	{
		cout << "\n===================================" <<name<<"��" <<n+1<<"������" <<"==================" << endl;
		for (int mm = 0; mm < 640; mm++)
		{
			cout << mat.at<double>(n, mm) << "\t";
		}
	}
	if (r1_c0 == 0)      //��ʾĳһ��ʱr1_c0==0
	{
		cout << "\n==================================="<<name << "��" << n+1 << "������" << "==================" << endl;
		for (int mm = 0; mm < 480; mm++)
		{
			cout << mat.at<double>(mm, n) << "\t";
		}
	}



}