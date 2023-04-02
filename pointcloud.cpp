#include"pointcloud.h"
#include"show_randc.h"
/*点云计算
Input: 校准矩阵Mc Mp obj Phase
Output: obj.X obj.Y obj.Z
*/
Pattern pointcloud(Mat& Mc,Mat& Mp,Pattern& object,Mat& Phase)  //传入校准矩阵
{
	//图案xc和yc的行列矩阵
	Mat orig_xc = Mat::ones(object.height, object.width, CV_64F);
	Mat orig_yc = Mat::ones(object.height, object.width, CV_64F);
	for (int ii = 1; ii < object.width; ii++)  //480
	{
		orig_xc.col(ii) = orig_xc.col(0)*(ii+1); //第ii行全部加之前一行的值,使得第0行为1第1行全...
		//string name = "orig_xc";
		//Show_rowandcol(orig_xc, 1, 479, name);
		
	//...是2，第2行全是3
	}
	for (int jj = 1; jj < object.height; jj++)  //480
	{
		orig_yc.row(jj) = orig_yc.row(0)*(jj+1); //第ii列全部加之前一列的值,使得第0列为1,第1列全...
		//...是2，第2行全是3

	}
	//至此形成了图案xc和yc的行列矩阵
	cout << "Mc.at<double>(0, 0)" << Mc.at<double>(0, 0) << endl;
	cout << "Mc.at<double>(2, 0)" << Mc.at<double>(2, 0) << endl;

	Mat C11 = Mc.at<double>(0, 0) - Mc.at<double>(2, 0) * orig_xc;
	Mat C12 = Mc.at<double>(0, 1) - Mc.at<double>(2, 1) * orig_xc;
	Mat C13 = Mc.at<double>(0, 2) - Mc.at<double>(2, 2) * orig_xc;
	//string name = "orig_xc";
	//Show_rowandcol(orig_xc, 0, 100, name);
	//string name_2 = "C13";
	//Show_rowandcol(C13, 0, 100, name_2);
	Mat C21 = Mc.at<double>(1, 0) - Mc.at<double>(2, 0) * orig_yc;
	Mat C22 = Mc.at<double>(1, 1) - Mc.at<double>(2, 1) * orig_yc;
	Mat C23 = Mc.at<double>(1, 2) - Mc.at<double>(2, 2) * orig_yc;
	//string name_3 = "orig_yc";
	//Show_rowandcol(orig_yc, 1, 100, name_3);   //显示100那一行
	//string name_4 = "C23";
	//Show_rowandcol(C23, 1, 100, name_4);
	Mat C31 = Mp.at<double>(1, 0) - Mp.at<double>(2, 0) * Phase;
	Mat C32 = Mp.at<double>(1, 1) - Mp.at<double>(2, 1) * Phase;
	Mat C33 = Mp.at<double>(1, 2) - Mp.at<double>(2, 2) * Phase;

	Mat D11 = Mc.at<double>(2, 3) * orig_xc - Mc.at<double>(0, 3);
	Mat D21 = Mc.at<double>(2, 3) * orig_yc - Mc.at<double>(1, 3);
	Mat D31 = Mp.at<double>(2, 3) * Phase - Mp.at<double>(1, 3);

	Mat detC = C11.mul(C22.mul(C33)) + C12.mul(C23.mul(C31)) + C13.mul(C21.mul(C32))
		- C11.mul(C23.mul(C32)) - C12.mul(C21.mul(C33)) - C13.mul(C22.mul(C31));

	//string name = "det_C";   //显示C矩阵行列式第100列
	//Show_rowandcol(detC, 0, 0, name);
	//Show_rowandcol(detC, 0, 99, name);
	//string name_2 = "det_C";//显示C矩阵行列式第100行
	//Show_rowandcol(detC, 1, 0, name_2);
	//Show_rowandcol(detC, 1, 99, name_2);

	Mat reverse_det = 1.0 / detC;

	//string name_3 = "reverse_det";   //显示C矩阵求倒数行列式第100列
	//Show_rowandcol(reverse_det, 1, 0, name_3);
	//Show_rowandcol(reverse_det, 0, 1, name_3);
	//string name_4 = "reverse_det";//显示C矩阵倒数行列式第100行
	//Show_rowandcol(reverse_det, 1, 0, name_4);
	//Show_rowandcol(reverse_det, 1, 99, name_4);

	Mat A11 = C22.mul(C33) - C23.mul(C32);
	Mat A12 = -C12.mul(C33) + C13.mul(C32);
	Mat A13 = C12.mul(C23) - C13.mul(C22);
	Mat A21 = -C21.mul(C33) + C23.mul(C31);
	Mat A22 = C11.mul(C33) - C13.mul(C31);
	Mat A23 = -C11.mul(C23) + C13.mul(C21);
	Mat A31 = C21.mul(C32) - C22.mul(C31);
	Mat A32 = -C11.mul(C32) + C21.mul(C31);
	Mat A33 = C11.mul(C22) - C12.mul(C21);
	//string name_4 = "test";   //显示C矩阵求倒数行列式第100列
	//Show_rowandcol(test, 1, 0, name_4);
	object.X = reverse_det.mul( A11.mul(D11) + A12.mul(D21) + A13.mul(D31) );
	//string name_5 = "object.X";   //显示C矩阵求倒数行列式第100列
	//Show_rowandcol(object.X, 1, 0, name_5);
	object.Y = reverse_det.mul( A21.mul(D11) + A22.mul(D21) + A23.mul(D31) );
	object.Z = reverse_det.mul( A31.mul(D11) + A32.mul(D21) + A33.mul(D31) );
	//string name_6 = "object.Z";   //显示C矩阵求倒数行列式第100列
	//Show_rowandcol(object.Z, 1, 0, name_6);
	return object;

}