#include "LieAlgebra.h"


int main()
{
	cv::Vec<double, 6> M(2, 1, 0, 1, 1, 0);
	cv::Mat I = cv::imread("lena.bmp");
	LSD::transformImage(I, M);
	return 0;
}