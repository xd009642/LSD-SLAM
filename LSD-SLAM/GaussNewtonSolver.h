#pragma once

#include "Metrics.h"
#include "LieAlgebra.h"
#include "opencv2\opencv.hpp"
#include <math.h>


namespace LSD
{
	class GaussNewtonSolver
	{
	public:
		GaussNewtonSolver();

		void solve(const cv::Mat& ref, const cv::Mat& in);

	protected:

	private:
		
	};
}