#pragma once

#include "opencv2\opencv.hpp"
#include <math.h>

namespace LSD
{
	double cosineDistance(const cv::Mat& a, const cv::Mat& b);

	double MSE(const cv::Mat& exp, const cv::Mat& act);
	
	//euclidean distance works on cv points and matrices
	template<typename T>
	double L2norm(const T& a)
	{
		return sqrt(a.dot(a));
	}


}