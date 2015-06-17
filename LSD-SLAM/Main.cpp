#include "LieAlgebra.h"


int main()
{
	cv::Vec<double, 6> M(0, 0, 0.1, 1, 1, 0);
	cv::Mat I = cv::imread("lena.bmp");
	cv::Mat in;
	
	cv::cvtColor(I, in, CV_BGR2GRAY);
	in = LSD::transformImage(in, cv::Mat::ones(cv::Size(in.cols, in.rows), CV_64FC1), M);

	return 0;
}