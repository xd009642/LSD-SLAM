#include "LieAlgebra.h"
#include "Metrics.h"
#include "opencv2\opencv.hpp"

#include <functional>

auto lowPass = [](double d, double D)
{
	return static_cast<double>(d>D)*0.1 + 0.9;
};
double distance(int x1, int y1, int x2, int y2)
{
	double res = pow(x1 - x2, 2) + pow(y1 - y2, 2);
	return sqrt(res);
}
void createFDFilter(cv::Mat &dst, int rows, int cols, std::function<float(float)> fn)
{
	cv::Point2i centre(cols / 2, rows / 2);
	dst = cv::Mat::zeros(rows, cols, CV_64F);
	for (int i = 0; i<rows; i++)
		for (int j = 0; j<cols; j++)
			dst.at<double>(i, j) = fn(distance(j, i, centre.x, centre.y));
}

	using namespace std::placeholders;

int main()
{
	cv::Vec<double, 6> M(0, 0, 0.001, 0, 0, 0.0);

	cv::Mat out;
	cv::Mat ref = cv::imread("L1.bmp");
	cv::Mat in = cv::imread("L2.bmp");
	
	cv::Mat filter;

	//filter =cv::Mat::ones(cv::Size(in.cols, in.rows), CV_64FC1);
	createFDFilter(filter, ref.rows, ref.cols, std::bind(lowPass, _1, 10.0));

	cv::cvtColor(in, in, CV_BGR2GRAY);
	cv::Mat T;
	LSD::generateSE3Mat(cv::Mat(M), T);
	LSD::transformImage(in, filter, T, out);

	cv::cvtColor(ref, ref, CV_BGR2GRAY);
	cv::absdiff(in, ref, out);

	return 0;
}