#include "Metrics.h"


double LSD::cosineDistance(const cv::Mat& a, const cv::Mat& b)
{
	return 1 - (a.dot(b) / (L2norm(a)*L2norm(b)));
}
