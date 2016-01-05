#include "camera_tracker.h"



LSD::camera_tracker::camera_tracker()
{

}

void LSD::camera_tracker::init(const cv::Mat3f& initialFrame)
{
	last_frame = initialFrame.clone();
}

cv::Mat3f LSD::camera_tracker::calculate_translation(const cv::Mat3f& frame)
{
	//translation/rotation matrix
	cv::Mat ret=cv::Mat::zeros(cv::Size(4, 4), CV_64F);
	ret.at<double>(cv::Point(3, 3)) = 1.0;

	return ret;
}

void LSD::camera_tracker::stereo_depthmap_update(const cv::Mat3f& mat)
{
    //First find subset of pixels with high accuracy of disparity search
        /*
        optimal inverse depth d*=d(I0, I1, e, pi)

        Need geometric error and the photometric error
        */

    //For each pixel select a suitable reference frame and perform 1D dimensional disparity search
        //use oldest frame pixel was observed in where disparity search range
        //and observation angle do not exceed threshold
        //if disparity search is unsuccessful (no good match found) pixels age is increased so new searches
        //use newer frames instead

    //propagated prior knowledge is used to reduce search range where possible
    
    //obtained inverse depth estimate is fused into depth map
}

/*
To track a frame:
    Start from initial SE3 estimate
    Do stuff...

*/