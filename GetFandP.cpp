#include"GetFandP.h"
vector<int> Freq;
vector<int> Pattern_num;

vector<int> StrToVec(string& str)
{
	vector<int> res;   //存储分割后的double数据
	stringstream InputS(str);  //那str1传入到字符串流
	string Temp;
	while (getline(InputS, Temp, ','))
	{
		int n;
		stringstream TempInputS(Temp);  //把str1传入到字符串流
		TempInputS >> n;
		res.push_back(n);
	}
	return res;
}
 void Raedtxt_FnP(char* path)
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

		while (!InFile.eof())   //没有到达文件末尾
		{
			
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


		}
	Pattern_num = StrToVec(str1);
	Freq = StrToVec(str2);
	for (int ii = 0; ii < Pattern_num.size(); ii++)
	{
		cout << Pattern_num[ii] << "\t";
	}

}
