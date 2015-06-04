#include "LieAlgebra.h"


int main()
{
	cv::Vec<double, 6> M(2, 1, 0, 1, 1, 0);
	cv::Mat I = cv::imread("lena.bmp");
	cv::Mat in;
	
	I.convertTo(in, CV_64FC3);
	in = LSD::transformImage(in, M);
	in.convertTo(in, CV_8UC3);
	return 0;
}