#pragma once
// Lee Eigen tools
// 2020/06/26 v1
#include "Dense"
// 头文件中直接定义模板函数，当头文件被多个源文件include时，不会出现重定义错误。如果函数是具体的定义，则会有重定义错误
namespace Eigen
{
	typedef Matrix<double, 4, 4> MatT;
	typedef Matrix<double, 3, 3> MatRot;
	typedef Matrix<double, 3, 1> MatVec;

	template<class T, typename Type>
	void setMatrix(T& M, const Type *p)
	{
		auto m = M.rows();
		auto n = M.cols();
		for (auto i = 0; i < m; i++)
		{
			for (auto j = 0; j < n; j++)
			{
				M(i, j) = *(p + n*i + j);
			}
		}
	}

	template<class T, typename Type>
	void setMatrix(T& M, std::initializer_list<Type> p)
	{
		setMatrix(M, p.begin());
	}

	template<class T, typename Type>
	void setMatrix(T& M, std::initializer_list<int> range, const Type *p)
	{
		auto pr = range.begin();
		int m[2] = { *pr,*(pr + 1) };
		int n[2] = { *(pr + 2),*(pr + 3) };
		int msize = m[1] - m[0] + 1;
		int nsize = n[1] - n[0] + 1;
		for (auto i = 0; i < msize; i++)
		{
			for (auto j = 0; j < nsize; j++)
			{
				M(m[0]+i, n[0]+j) = *(p + nsize*i + j);
			}
		}
	}

	template<class T, typename Type>
	void setMatrix(T& M, std::initializer_list<int> range, std::initializer_list<Type> p)
	{
		setMatrix(M, range, p.begin());
	}

	template<typename Type>
	void setT(MatT& T, Type R[3][3], Type P[3])
	{
		setMatrix(T, { 0,2,0,2 }, &R[0][0]);
		setMatrix(T, { 0,2,3,3 }, P);
		setMatrix(T, { 3,3,0,2 }, { 0,0,0,1 });
	}

}