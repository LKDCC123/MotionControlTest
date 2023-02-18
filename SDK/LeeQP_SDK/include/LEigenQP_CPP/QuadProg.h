// This file is part of EigenQP.
//
// EigenQP is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// EigenQP is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with EigenQP.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

//includes
//Eigen
#include <Eigen/Core>
#include <Eigen/Sparse>

int qpgen1_(double* dmat, double* dvec,  int* fddmat,
	 int* n, double* sol, double* crval, double* amat,  int* iamat,
	double* bvec,  int* fdamat,  int* q,  int* meq, int* iact,
	int* nact, int* iter, double* work,  int* ierr);

int qpgen2_(double* dmat, double* dvec,  int* fddmat,
	 int* n, double* sol, double* crval, double* amat, double* bvec,
	 int* fdamat,  int* q,  int* meq, int* iact, int* nact,
	int* iter, double* work,  int* ierr);

namespace Eigen
{
class QuadProgCommon
{
public:
	QuadProgCommon();

	const VectorXi& iter() const;
	int fail() const;

	const VectorXd& result() const;

	void problem(int nrvar, int nreq, int nrineq);

protected:
	void fillQCBf(int nreq, int nrineq,
		const MatrixXd& Q, const VectorXd& C,
		const VectorXd& Beq, const VectorXd& Bineq,
		bool isDecomp);

protected:
	MatrixXd Q_;
	VectorXd C_, B_, X_;
	int fail_;
	VectorXi iact_;
	VectorXi iter_;
	VectorXd work_;
};


class QuadProgDense : public QuadProgCommon
{
public:
	QuadProgDense();
	QuadProgDense(int nrvar, int nreq, int nrineq);

	void problem(int nrvar, int nreq, int nrineq);

	bool solve(const MatrixXd& Q, const VectorXd& C,
		const MatrixXd& Aeq, const VectorXd& Beq,
		const MatrixXd& Aineq, const VectorXd& Bineq,
		bool isDecomp=false);

private:
	MatrixXd A_;
};


class QuadProgSparse : public QuadProgCommon
{
public:
	QuadProgSparse();
	QuadProgSparse(int nrvar, int nreq, int nrineq);

	void problem(int nrvar, int nreq, int nrineq);

	bool solve(const MatrixXd& Q, const VectorXd& C,
		const SparseMatrix<double>& Aeq, const VectorXd& Beq,
		const SparseMatrix<double>& Aineq, const VectorXd& Bineq,
		bool isDecomp=false);

private:
	MatrixXd A_;
	MatrixXi iA_;
};

} // namespace Eigen
