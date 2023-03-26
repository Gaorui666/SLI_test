#include"show_float.h"

void imshow_float(Mat& Ac, Mat& Bc, Mat& Phase)
{
	Mat norm_Ac, norm_Bc, norm_Phase;
	normalize(Ac, norm_Ac, 1.0, 0, NORM_MINMAX);
	normalize(Bc, norm_Bc, 1.0, 0, NORM_MINMAX);
	normalize(Phase, norm_Phase, 1.0, 0, NORM_MINMAX);
	namedWindow("norm_Ac");
	imshow("norm_Ac", norm_Ac);
	waitKey(0);
	namedWindow("norm_Bc");
	imshow("norm_Bc", norm_Bc);
	waitKey(0);
	namedWindow("norm_Phase");
	imshow("norm_Phase", norm_Phase);
	waitKey(0);

}