#ifndef CHZFRAME_CHZFRAMEPLATFORMSELECTOR_H
#define CHZFRAME_CHZFRAMEPLATFORMSELECTOR_H

//#define CHZFRAME_DEBUG
//#define CHZFRAME_BHR7P1_SIM
//#define CHZFRAME_BHR7P1
#define CHZFRAME_BHR7P2
//#define CHZFRAME_ATHLETE

#ifdef CHZFRAME_DEBUG
#endif


#ifdef __cplusplus
extern "C" {
#endif

#ifdef CHZFRAME_BHR7P1_SIM
	extern double FootFT[5][6];
	extern double XS_Pitch, XS_Roll;
	extern double Ref_Leg_Joint[3][7], Joint[3][7], Ref_Val[3][7], Gear_Rate_Joint[3][6];
	extern double Ref_Arm_Joint[3][8], Joint_Arm[3][8], Ref_Arm_Val[3][8], Gear_Arm_Rate_Joint[3][7];
	extern double Ref_Waist_Joint[4], Joint_Waist[2][4], Ref_Waist_Val[4], Gear_Waist_Rate_Joint[3];
	extern double Body_VX, Body_VY;
	//#define CHZ_FixedWaistMotion
	#ifdef CHZ_FixedWaistMotion
		extern double Ref_Waist_Pos[6];
	#endif
#endif

#ifdef CHZFRAME_BHR7P1
	extern double FootFT[5][6];
	extern double XS_Pitch, XS_Roll, XS_GyrX, XS_GyrY;
	extern double Ref_Leg_Joint[3][7], Joint[3][9], Ref_Val[3][9], Gear_Rate_Joint[3][8];
	extern double Ref_Arm_Joint[3][8], Joint_Arm[3][8], Ref_Arm_Val[3][8], Gear_Arm_Rate_Joint[3][7];
	extern double Ref_Waist_Joint[4], Joint_Waist[2][4], Ref_Waist_Val[4], Gear_Waist_Rate_Joint[3];
#endif

#ifdef CHZFRAME_BHR7P2
	extern double FootFT[5][6];
	extern double XS_Pitch, XS_Roll, XS_GyrX, XS_GyrY;
	extern double Ref_Leg_Joint[3][7], Joint[3][10], Ref_Val[3][10], Gear_Rate_Joint[3][9];
	extern double Ref_Arm_Joint[3][8], Joint_Arm[3][8], Ref_Arm_Val[3][8], Gear_Arm_Rate_Joint[3][7];
#endif

#ifdef CHZFRAME_ATHLETE
	#include "..\\hardware_conf.h" 
#endif

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
	#ifdef CHZFRAME_DEBUG
		#define CHZFRAME_EIGEN_PATH "..\\Eigen\\Dense"
		#define CHZFRAME_EIGEN_PATH_ "..\\..\\Eigen\\Dense"
		#define CHZFRAME_EIGEN_PATH__ "..\\..\\..\\Eigen\\Dense"
	#endif
	#ifdef CHZFRAME_BHR7P1_SIM
		#define CHZFRAME_EIGEN_PATH "..\\Eigen\\Dense"
		#define CHZFRAME_EIGEN_PATH_ "..\\..\\Eigen\\Dense"
		#define CHZFRAME_EIGEN_PATH__ "..\\..\\..\\Eigen\\Dense"
	#endif
	#ifdef CHZFRAME_BHR7P1
		#define CHZFRAME_EIGEN_PATH <Eigen\\Dense>
		#define CHZFRAME_EIGEN_PATH_ <Eigen\\Dense>
		#define CHZFRAME_EIGEN_PATH__ <Eigen\\Dense>
	#endif
	#ifdef CHZFRAME_BHR7P2
		#define CHZFRAME_EIGEN_PATH <Eigen\\Dense>
		#define CHZFRAME_EIGEN_PATH_ <Eigen\\Dense>
		#define CHZFRAME_EIGEN_PATH__ <Eigen\\Dense>
	#endif
	#ifdef CHZFRAME_ATHLETE
		#define CHZFRAME_EIGEN_PATH "..\\QP_lib\\Eigen\\Dense"
		#define CHZFRAME_EIGEN_PATH_ "..\\..\\\QP_lib\\Eigen\\Dense"
		#define CHZFRAME_EIGEN_PATH__ "..\\..\\..\\\QP_lib\\Eigen\\Dense"
	#endif
#endif

#endif