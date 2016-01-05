#pragma once

#include "opencv2\opencv.hpp"
#include "sophus\se3.hpp"

/*
    Doesn't take into account occlusion.
*/
void warp_image(const cv::Mat3b& src, const cv::Mat1f& inverse_depth, const Sophus::SE3f& warp_mat, cv::Mat3b& dst)
{
    assert(src.rows == inverse_depth.rows && src.cols == inverse_depth.cols);
    cv::Mat3b temp(src.rows, src.cols, cv::Vec3b(0,0,0));

    for (size_t r = 0; r < src.rows; r++)
    {
        for (size_t c = 0; c < src.cols; c++)
        {
            float d = 1.0f / inverse_depth(cv::Point(c, r));
            Eigen::Vector4f point(c*d, r*d, d, 1);
            auto res = warp_mat.matrix()*point;
            cv::Point new_point(static_cast<int>(res(1) / res(2)),
                static_cast<int>(res(0) / res(2)));
            if (new_point.x > -1 && new_point.x<src.cols && new_point.y>-1 && new_point.y<src.rows)
                temp.at<cv::Vec3b>(new_point) = src(cv::Point(r, c));
        }
    }

    temp.copyTo(dst);
}