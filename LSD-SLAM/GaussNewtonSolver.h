#pragma once

#include "Metrics.h"
#include "LieAlgebra.h"
#include "opencv2\opencv.hpp"
#include <math.h>
#include <functional>

namespace LSD
{
	template<int params>
	using F = std::function<cv::Mat(const cv::Mat& src, const cv::Vec<double, params>& arg)>;

	template<int params>
	class GaussNewtonSolver
	{
		
	public:
		GaussNewtonSolver(F<params> f);

		void solve(const cv::Mat& ref, const cv::Mat& src, cv::Vec<double, params>& arg);

	protected:
		void residual(const cv::Mat& ref, const cv::Mat& src, cv::Vec<double, params>& arg, cv::Mat& dst);

		void delta(const cv::Mat& r, cv::Mat& dst);
	private:
		F<params> fn;
		//stores value limits (e.g. rotations are 0<= w < 360)
		cv::Vec<double, params> limits;
	};

	template<int _T>
	GaussNewtonSolver<_T>::GaussNewtonSolver(F<_T> f) :
	fn(f)
	{
		
	}

	template<int _T>
	void GaussNewtonSolver<_T>::solve(const cv::Mat& ref, const cv::Mat& src, cv::Vec<double, _T>& args)
	{
		//calculate error residual with 
		cosineDistance(ref, fn(src, args));

		//so we want to find args*= argmin(cosineDistance(ref, fn(src, args)));
	}

	template<int _T>
	void GaussNewtonSolver<_T>::residual(const cv::Mat& ref, const cv::Mat& src, cv::Vec<double, _T>& args, cv::Mat& dst)
	{
		//The residual is the difference between the actual output and the predicted output using the parameterised model
		//In GN there are often multiple residuals however I'm currently implementing it for trying to transform one matrix
		//into another. So it takes the form r=y-f(x, b)

		//Need to consider if doing it on a per pixel basis is better
		dst = ref - fn(src, args);
	}

	template<int _T>
	void GaussNewtonSolver<_T>::delta(const cv::Mat& r, cv::Mat& dst)
	{
		/*
		delta is calculated by: d=((J^T * J)^-1)(J^T*r) where J is the Jacobian.
		*/
	}
}