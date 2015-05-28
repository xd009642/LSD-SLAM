#include "GaussNewtonSolver.h"


LSD::GaussNewtonSolver::GaussNewtonSolver()
{

}

void LSD::GaussNewtonSolver::solve(const cv::Mat& ref, const cv::Mat& in)
{
	//LM does it by:
	//approximate hessian with 2 * J^T * J
	//a[k+1]=a[k]-(mu*I+H)^(-1)*(df) 

	/*
		Instead of that this algorithm:
		computes newton direction
			-(mu*I+H)*a[k] = df
		Updates motion parameters
			M[k] <- K*M[k-1]
		Update reprojections and compute mean error
		Repeat until convergence

		cost is squared distance
	*/
}