#include "LieAlgebra.h"





/*
	Creates SE(3) transformation matrix given the parameters x, y, z rotation then translation.

	This matrix assumes the bodies being transformed are rigid.
*/
void LSD::generateSE3Mat(const cv::Mat& arg, cv::Mat& dst)
{
	dst = cv::Mat::eye(cv::Size(4, 4), CV_64F);
	//set rotation
	cv::Rodrigues(arg(cv::Range(0,3), cv::Range(0,1)), dst(cv::Range(0, 3), cv::Range(0, 3)));
	//set translation
	dst.at<double>(cv::Point(3, 0)) = arg.at<double>(cv::Point(0, 3));
	dst.at<double>(cv::Point(3, 1)) = arg.at<double>(cv::Point(0, 4));
	dst.at<double>(cv::Point(3, 2)) = arg.at<double>(cv::Point(0, 5));
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