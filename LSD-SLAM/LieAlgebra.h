#pragma once

#include "Metrics.h"
#include "opencv2\opencv.hpp"
#define _USE_MATH_DEFINES
#include <math.h>


namespace LSD
{

	void generateSE3Mat(const cv::Mat& arg, cv::Mat& dst);

	void transformImage(const cv::Mat& src, const cv::Mat& depth, const cv::Mat& transform, cv::Mat& dst);
}