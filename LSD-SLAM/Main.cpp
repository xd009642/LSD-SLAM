#include "LieAlgebra.h"
#include "Metrics.h"

int main()
{
	cv::Vec<double, 6> M(0, 0, 0, 0, 0, 0.);//(0, 0, M_PI_2, 510, 17, 0);

	cv::Mat out;
	cv::Mat ref = cv::imread("L1.bmp");
	cv::Mat in = cv::imread("L2.bmp");
	
	cv::cvtColor(in, in, CV_BGR2GRAY);
	cv::Mat T;
	LSD::generateSE3Mat(M, T);
	LSD::transformImage(in, cv::Mat::ones(cv::Size(in.cols, in.rows), CV_64FC1), T, in);

	cv::cvtColor(ref, ref, CV_BGR2GRAY);
	cv::absdiff(in, ref, out);

	return 0;
}