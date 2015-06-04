#pragma once

#include "Metrics.h"
#include "LieAlgebra.h"
#include "opencv2\opencv.hpp"
#include <math.h>
#include <functional>

namespace LSD
{
	template<int params>
	typedef std::function<cv::Mat(const cv::Mat& src, const cv::Vec<double, int>& arg)> F;

	template<int params>
	class GaussNewtonSolver
	{
		
	public:
		GaussNewtonSolver(F f);

		void solve(const cv::Mat& ref, const cv::Mat& src, cv::Vec<double, params>& arg);

	protected:

	private:
		F fn;
	};

	template<int params>
	GaussNewtonSolver::GaussNewtonSolver(F f) :
	fn(f)
	{
		
	}

	template<int params>
	void GaussNewtonSolver::solve(const cv::Mat& ref, const cv::Mat& src, cv::Vec<double, params>& args)
	{
		//calculate error residual with 
		cosineDistance(ref, fn(src, args));
	}

	
}