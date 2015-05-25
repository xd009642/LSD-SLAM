#include "CameraTracker.h"

LSD::CameraTracker::CameraTracker()
{

}

void LSD::CameraTracker::init(const cv::Mat& initialFrame)
{
	lastFrame = initialFrame.clone();
}

cv::Mat LSD::CameraTracker::calculateTranslation(const cv::Mat& frame)
{
	//translation/rotation matrix
	cv::Mat ret=cv::Mat::zeros(cv::Size(4, 4), CV_64F);
	ret.at<double>(cv::Point(3, 3)) = 1.0;

	return ret;
}