#include"Readtxt.h"
//Mat Readtxt(char* path)
//{
//	Mat MM;
//	FILE* fp;
//	errno_t err;
//	err = fopen_s(&fp, path, "r");
//	if (err == 1)
//		cout << "fread failed!" << endl;
//	else
//	{
//		fread_s()
//	}
//}
Mat CameraM;
Mat ProjectorM;
string testsss = "sdddddddddddd";
//Mat StrToMat(string& str,Mat& Input_res)
//{
//	vector<double> res;   //�洢�ָ���double����
//	stringstream InputS(str);  //��str1���뵽�ַ�����
//	string Temp;
//	while (getline(InputS, Temp, ','))
//	{
//		double n;
//		stringstream TempInputS(Temp);  //��str1���뵽�ַ�����
//		TempInputS >> n;
//		res.push_back(n);
//	}
//	//for (int i = 0; i < res.size(); i++)
//	//	cout << "mc��" << i + 1 << "����" << res[i] << endl;
//	Mat M = Mat(res).reshape(0, 3);
//	for (int ii = 0; ii < M.rows; ii++)
//	{
//		for (int jj = 0; jj < M.cols; jj++)
//			cout << M.at<double>(ii, jj)<<"\t";
//		cout << endl;
//	}
//	M.copyTo(Input_res);
//	return Input_res;
//}
Mat StrToMat(string& str, Mat& Input_res)
{
	vector<double> res;   //�洢�ָ���double����
	stringstream InputS(str);  //��str1���뵽�ַ�����
	string Temp;
	while (getline(InputS, Temp, ','))
	{
		double n;
		stringstream TempInputS(Temp);  //��str1���뵽�ַ�����
		TempInputS >> n;
		res.push_back(n);
	}
	//for (int i = 0; i < res.size(); i++)
	//	cout << "mc��" << i + 1 << "����" << res[i] << endl;
	Mat M= Mat(res).reshape(0, 3);  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	for (int ii = 0; ii < M.rows; ii++)
	{
		for (int jj = 0; jj < M.cols; jj++)
			cout << M.at<double>(ii, jj) << "\t";
		cout << endl;
	}
	M.copyTo(Input_res);
	return Input_res;
}
void Readtxt(char* path)
{

	string str1;
	string str2;
	std::ifstream InFile(path, std::ios::binary);
	if (!InFile.is_open())
	{
		cout << "Unable to read this txt!" << endl;
		exit(1);
	}
	else

		while (!InFile.eof())   //û�е����ļ�ĩβ
		{
			//InFile.seekg(0, ios::end);
			//static int length = InFile.tellg();  //��ȡ�ļ��ĳ���
			//string str(length,'\0');
			// 
			// 
			//double n;
			//InFile.ignore(std::numeric_limits<std::streamsize>::max(), '[');
			//char mc[800];
			//InFile.getline(mc, 800, ']');
			//cout << mc << endl;
			//InFile.ignore(std::numeric_limits<std::streamsize>::max(), '[');
			//char mp[800];
			//InFile.getline(mp, 800, ']');
			//cout << mp << endl;
			//InFile >> n;
			//cout << n << endl;
			InFile.ignore(std::numeric_limits<std::streamsize>::max(), '[');
			//string str1;
			getline(InFile, str1, ']');
			InFile.ignore(std::numeric_limits<std::streamsize>::max(), '[');
			//string str2;
			getline(InFile, str2, ']');
			replace(str1.begin(), str1.end(), ';', ',');
			replace(str2.begin(), str2.end(), ';', ',');
			//cout << str1 << endl;
			//cout << str2 << endl;
			break;
			
			//string Temp
			/*while(getline(InputS,Temp,','))*/
		}
	StrToMat(str1, CameraM);
	StrToMat(str2, ProjectorM);
	//�����е�StrToMat����Input_res����������ʹ��copyTo��CameraMʱ...
	//������۲�CamersaMʱ������Ѿ�����ϣ����ֵ��,��StrToMat�Ĳ��������CameraM����Գɹ�
	//����ֻ�ǰ�StrToMat��M���Ǽ򵥸�ֵ���ǲ���cloneҲ���Խ�ֵ��ȷ����У׼��
	//���ǲ���ȫ��stringʱ�Ϳ�������
	testsss = "change";
	cout << "�������testsss" << testsss << endl;
	cout << "CAMERAm================================="<<endl;
	for (int ii = 0; ii < CameraM.rows; ii++)
	{
		for (int jj = 0; jj < CameraM.cols; jj++)
			cout << CameraM.at<double>(ii, jj) << "\t";
		cout << endl;
	}


}