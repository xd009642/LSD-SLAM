#include "LieAlgebra.h"




//src is inverse depth image
void LSD::projectiveWarp(const cv::Mat& src, cv::Mat& dst)
{
	/*
		for each pixel p=src(r, c) that pixel is in 3D space
		
		w=(x/z, y/z, 1/z)   

		where

		(x, y, z) = exp(se(3))(c/src(r, c), r/src(r, c), 1/src(r, c))

		Not sure what the exponential map for the vector is yet though, need to 
		learn lie algebras better.
	*/
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