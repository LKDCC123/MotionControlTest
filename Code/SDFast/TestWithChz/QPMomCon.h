#ifndef CHZFRAME_CTRL_CHZQPMONCON_H
#define CHZFRAME_CTRL_CHZQPMONCON_H
#include "../RobotState.h"
#include "../ChzFrameSwitch.h"
#include "../SDFAST/ChzSD_sdfastdefs.h"
#include "QP_Moment_Control/Chz_QPMoment.h"

#ifdef CHZFRAME_CTRL_CHZQPMONCON_CPP
#define Extern
#else
#define Extern extern
#endif

namespace ChzFrame
{
	class QPMomCon :public ControllerBase
	{
	public:
		int Reset();
		int Update(RobotState* PState, RobotState* SState, RobotState* CState);
	private:
		double qs[ndof], dqs[ndof];
		Eigen::Vectornd q, dq, ddq, ddqd;
		Eigen::Vector3d CoM, dCoM, CoMp, dCoMp;
		Eigen::Vector6d Mom, dMom, dMomd, FT;
		Eigen::Vector12d Ank, dAnk, Ankp, dAnkp, ddAnkp, ddAnkd;
		Eigen::Vectornd D_joint;
		Eigen::Vector6d D_mom;
	};
	Extern QPMomCon QPMomCon1;
}
#undef Extern
#endif