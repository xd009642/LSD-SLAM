
#include "Metrics.h"
#include "opencv2\opencv.hpp"
#include "img_common.h"
#include <functional>


	using namespace std::placeholders;

int main()
{

	cv::Mat3b out;
	cv::Mat3b ref = cv::imread("L1.bmp");
	cv::Mat3b in = cv::imread("L2.bmp");
	
    using namespace Sophus;

    SE3f se3(SE3f(SO3f::exp(SE3f::Point(0.0001, 0, 0.0)), SE3f::Point(-0, 0, 0)));
    cv::Mat1f depth(ref.rows, ref.cols);

    cv::Mat mean = cv::Mat::ones(1, 1, CV_64FC1)*60;
    cv::Mat sigma = cv::Mat::ones(1, 1, CV_64FC1)*20;
    cv::randn(depth, mean, sigma);

    warp_image(ref, depth, se3, out);
	return 0;
}