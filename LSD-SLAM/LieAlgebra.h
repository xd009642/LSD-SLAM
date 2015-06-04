#pragma once

#include "Metrics.h"
#include "opencv2\opencv.hpp"
#include <math.h>


namespace LSD
{
	/*
	maps from lie algebra to lie group to get rotation matrix
	calcFull specifies that full calculation is done, for small
	perturbations the difference between the full version and approximation are
	small but the error increases as the magnitude of rotation increases.
	*/
	void expm(const cv::Point3d& w, cv::Mat& dst, bool calcFull=true);

	void skewSymmetricMatrix(const cv::Point3d& w, cv::Mat& dst);

	//Input an intensity image where the intensity refers to the inverse depth
	void projectiveWarp(const cv::Mat& src, cv::Mat& dst);


	cv::Mat transformImage(const cv::Mat& src, const cv::Vec<double, 6>& arg);
}