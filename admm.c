#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Eigen/Core>
#include <Eigen/LU>
#define PRINT_MAT(X) cout << #X << ":\n" << X << endl << endl
#define PRINT_MAT2(X,DESC) cout << DESC << ":\n" << X << endl
#define PRINT_FNC	cout << "[" << __func__ << "]" << endl

using namespace std;
using namespace Eigen;

int main()
{
	int i,j,k,l,m;
	int N = 50;
	int M = 25;
	int K = 5;

	int T = 50;

//initial conditions

	MatrixXd x = MatrixXd::Zero(N,1);
	MatrixXd z = MatrixXd::Zero(N,1);
	MatrixXd z1 = MatrixXd::Zero(N,1);
	MatrixXd u = MatrixXd::Zero(N,1);
	MatrixXd y = MatrixXd::Zero(N,1);

	MatrixXd x1 = MatrixXd::Random(K,1);
	MatrixXd x2 = MatrixXd::Zero(N-K,1);
	MatrixXd x0 = MatrixXd::Zero(N,1);

	MatrixXd A = MatrixXd::Random(M,N);
	MatrixXd A1 = MatrixXd::Zero(M,N);
	MatrixXd A2 = MatrixXd::Zero(N,N);
	MatrixXd A3 = MatrixXd::Zero(M,N);
	MatrixXd A4 = MatrixXd::Identity(N,N);
	MatrixXd AX = MatrixXd::Identity(N,N);
	MatrixXd AY = MatrixXd::Identity(N,N);

	MatrixXd ary = MatrixXd::Zero(N,1);

//
// Creating Original Signal (x0)
//
        for (k = 0; k < N; k++)
        {
                ary(k) = k;
        }

	for (k = 0; k < N; k++)
	{
		int l = rand()%N;
		int m = ary(k);
		ary(k) = ary(l);
		ary(l) = m;
	}

	for (k = 0; k < K; k++)
	{
		x0(ary(k)) = x1(k);
	}
	
	y = A * x0;

//
//Defining Fine term coefficient 
//
	double mu = 1.0;

	A3 = A * A.transpose();
	A1 = A.transpose() * (A3.inverse());
	AX = A1 * y;
        AY = A2 * (z - u);
	A2 = A4 - A1 * A;

//
// ADMM variable update
//
	for (i = 0; i < T; i++) {
		x = A1 * y + A2 * (z - u);
		z1 = x + u;
//
//	Soft Threshold function
//
		for (j = 0; j < N; j++){
			if(z1(j) > mu)
				z(j) = z1(j) - mu;
			else if (-z1(j) > mu)
				z(j) = z1(j) + mu;
			else
				z(j) = 0;
		}
		u = u + x -z;
	}

//Print Original signal

	PRINT_MAT(x0);

//Print Esitmated Signal

	PRINT_MAT(x);

}

