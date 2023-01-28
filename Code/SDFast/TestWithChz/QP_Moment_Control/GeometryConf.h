#ifndef GEOMETRYCONF_H
#define GEOMETRYCONF_H
#include "..\\Chz_Control_lib\\Chz_Base.h"
#include "..\\..\\ChzFramePlatformSelector.h"
#include "..\\..\\SDFAST\\ChzSD_sdfastdefs.h"

#ifdef GEOMETRYCONF_CPP
#define Extern
#else
#define Extern extern
#endif
namespace Chz
{
	class sdfastbody
	{
	public:
		std::string name;
		double mass;
		double inertia[3][3];
		double bodytojoint[3];
		double inbtojoint[3];
	};

	class RobotGeometry
	{
	public:
		sdfastbody bodies[nbod];
		RobotGeometry();
		sdfastbody FindBody(std::string name);
	};
	Extern RobotGeometry RobotGeom;
}
#undef Extern
#endif