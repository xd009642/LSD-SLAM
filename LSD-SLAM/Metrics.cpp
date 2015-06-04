#include "Metrics.h"


double LSD::cosineDistance(const cv::Mat& a, const cv::Mat& b)
{
	return 1 - (a.dot(b) / (L2norm(a)*L2norm(b)));
}

double LSD::MSE(const cv::Mat& exp, const cv::Mat& act)
{
	assert((act.rows == exp.rows) && (act.cols == exp.cols));
	const double N = act.rows*act.cols;
	double result = 0;

	for (int r = 0; r<act.rows; r++)
	{
		for (int c = 0; c<act.cols; c++)
		{
			result += pow((double)(exp.at<uchar>(r, c) - act.at<uchar>(r, c)), 2);
		}
	}
	return result / N;
}