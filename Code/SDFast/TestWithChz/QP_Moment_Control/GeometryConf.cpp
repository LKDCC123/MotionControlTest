#ifndef GEOMETRYCONF_CPP
#define GEOMETRYCONF_CPP
#include "GeometryConf.h"
namespace Chz
{
	RobotGeometry::RobotGeometry()
	{
		using namespace ChzSD;
		const std::string bodynames[nbod] = { "midbody", "uppbody", "larm", "rarm", "lthigh", "lshank", "lfoot", "rthigh", "rshank", "rfoot" };
		
		ChzF(i, 0, nbod - 1)
		{
			int k = 0;
			bodies[i].name = bodynames[i];
			bodies[i].mass = bodygeoms[i][k++];
			ChzF(m, 0, 2) ChzF(n, 0, 2)
				if (m == n) bodies[i].inertia[m][m] = bodygeoms[i][k++];
				else bodies[i].inertia[m][n] = 0.0;
			ChzF(j, 0, 2) bodies[i].bodytojoint[j] = bodygeoms[i][k++];
			ChzF(j, 0, 2) bodies[i].inbtojoint[j] = bodygeoms[i][k++];
		}
		ChzF(i, 0, nbod - 1)
		{
			sdmass(i, bodies[i].mass);
			sdiner(i, bodies[i].inertia);
			sdbtj(i, bodies[i].bodytojoint);
			sditj(i, bodies[i].inbtojoint);
		}
		sdinit();
	}

	sdfastbody RobotGeometry::FindBody(std::string name)
	{
		ChzF(i, 0, nbod - 1) if(bodies[i].name == name) return bodies[i];
		return sdfastbody();
	}



}
#endif