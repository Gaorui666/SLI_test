#include"SaveTxt.h"
void SaveTxt(Mat& InputMat, string filename)
{
	ofstream fout(filename);
	if (!fout)
		cout << "文件打开失败" << endl;
	else
	{

		for (int ii = 0; ii < InputMat.rows; ii++)
		{
			for (int jj = 0; jj < InputMat.cols; jj++)
			{
				fout << InputMat.at<double>(ii, jj) << "\t";
			}
			fout << endl;

		}
		fout.close();

	}

}

