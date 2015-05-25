#pragma once

#include "opencv2\opencv.hpp"
#include <math.h>

namespace LSD
{
	double cosineDistance(const cv::Mat& a, const cv::Mat& b);
	
	//euclidean distance works on cv points and matrices
	template<typename T>
	double L2norm(const T& a)
	{
		return sqrt(a.dot(a));
	}
}