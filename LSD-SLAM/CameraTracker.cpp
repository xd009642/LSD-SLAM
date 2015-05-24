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

}