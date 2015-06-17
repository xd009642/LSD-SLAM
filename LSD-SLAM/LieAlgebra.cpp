#include "LieAlgebra.h"





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
		if (magW == 0.0)
			dst = cv::Mat::eye(cv::Size(3, 3), CV_64F);
		else
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

/*
	Creates SE(3) transformation matrix given the parameters x, y, z rotation then translation.

	This matrix assumes the bodies being transformed are rigid.
*/
void LSD::generateSE3Mat(const cv::Vec<double, 6>& arg, cv::Mat& dst)
{
	dst = cv::Mat::eye(cv::Size(4, 4), CV_64F);
	//set rotation
	expm(cv::Point3d(arg[0], arg[1], arg[2]), dst(cv::Range(0, 3), cv::Range(0, 3)));
	//set translation
	dst.at<double>(cv::Point(3, 0)) = arg[3];
	dst.at<double>(cv::Point(3, 1)) = arg[4];
	dst.at<double>(cv::Point(3, 2)) = arg[5];
}

/*
	Transforms image given pixel values and depth map and a given transformation.

	assumes use of 8 bit 1 channel image
*/
void LSD::transformImage(const cv::Mat& src, const cv::Mat& depth, const cv::Mat& transform, cv::Mat& dst)
{
	dst=cv::Mat::zeros(src.rows, src.cols, src.type());

	for (int r = 0; r < src.rows; r++)
	{
		for (int c = 0; c < src.cols; c++)
		{
			cv::Mat p = cv::Mat::zeros(4, 1, CV_64FC1);
			p.at<double>(cv::Point(0, 0)) = static_cast<double>(r);
			p.at<double>(cv::Point(0, 1)) = static_cast<double>(c);
			p.at<double>(cv::Point(0, 2)) = depth.at<double>(cv::Point(r, c));
			p.at<double>(cv::Point(0, 3)) = 1.0;

			cv::Mat newPoint = transform * p;
			int newX = static_cast<int>(newPoint.at<double>(0, 0) / newPoint.at<double>(2, 0));
			int newY = static_cast<int>(newPoint.at<double>(1, 0) / newPoint.at<double>(2, 0));
			if (newX>-1 && newX < dst.cols && newY>-1 && newY<dst.rows)
				dst.at<uchar>(cv::Point(newX, newY)) = src.at<uchar>(cv::Point(r, c));
		}
	}
}