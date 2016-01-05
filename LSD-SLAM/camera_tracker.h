#pragma once

#include "opencv2\opencv.hpp"
#include "sophus\se3.hpp"

namespace LSD
{
	class camera_tracker
	{
	public:
		camera_tracker();
		//sets the initial frame
		void init(const cv::Mat3f& initialFrame);
		//takes new frame and estimates camera movement. Returns matrix describing translation
		cv::Mat3f calculate_translation(const cv::Mat3f& mat);
    protected:
        void stereo_depthmap_update(const cv::Mat3f& mat);
	private:
		cv::Mat3f last_frame;
        cv::Mat3f warp_mat; //pixel 1x1 shows the [x, y, z] of that pixel on the inputted image
	};

}