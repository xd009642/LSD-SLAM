#pragma once

#include "opencv2\opencv.hpp"


namespace LSD
{
	class CameraTracker
	{
	public:
		CameraTracker();
		//sets the initial frame
		void init(const cv::Mat& initialFrame);
		//takes new frame and estimates camera movement. Returns matrix describing translation
		cv::Mat calculateTranslation(const cv::Mat& mat);

	private:
		cv::Mat lastFrame;
	};

}