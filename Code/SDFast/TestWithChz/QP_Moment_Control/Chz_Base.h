#pragma once
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include "ChzFramePlatformSelector.h"

#include CHZFRAME_EIGEN_PATH__

#define ChzF(a, b, c) for(int a = (b); a <= (c); a++)
typedef long long ll;

namespace Chz
{
	constexpr double inf = 1e20;
	constexpr double eps = 1e-7;
	constexpr double pi = 3.141592653589793;
	constexpr double e = 2.718281828459045;
	constexpr double g = 9.8;
	constexpr double mu = 0.6;
}