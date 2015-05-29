#include "LieAlgebra.h"





void LSD::projectiveWarp(const cv::Mat& src, cv::Mat& dst)
{

}

void LSD::expm(const cv::Point3d& w, cv::Mat& dst, bool calcFull)
{
	//get skew symmetric matrix
	cv::Mat theta;
	skewSymmetricMatrix(w, theta);

	if (false == calcFull)
	{
		dst = cv::Mat::eye(cv::Size(3, 3), CV_64F) + theta;
	}
	else
	{
		double magW = L2norm(w);
		dst = cv::Mat::eye(cv::Size(3, 3), CV_64F) + (sin(magW)/magW)*theta +
			((1-cos(magW))/pow(magW, 2))*(theta*theta);
	}
}

void LSD::skewSymmetricMatrix(const cv::Point3d& w, cv::Mat& dst)
{
	dst = cv::Mat::zeros(cv::Size(3, 3), CV_64F);

	dst.at<double>(cv::Point(2, 1)) = -w.x;
	dst.at<double>(cv::Point(1, 2)) = w.x;

	dst.at<double>(cv::Point(0, 2)) = -w.y;
	dst.at<double>(cv::Point(2, 0)) = w.y;

	dst.at<double>(cv::Point(1, 0)) = -w.z;
	dst.at<double>(cv::Point(0, 1)) = w.z;
}