#pragma once
#ifndef CHZ_QPMOMENT_H
#define CHZ_QPMOMENT_H
#include "../Chz_control_lib/Chz_Base.h"
#include "../../SDFAST/ChzSD_sdfastdefs.h"
#include <EigenQP\QuadProg.h>
#ifdef CHZ_QPMOMENT_CPP
#define Extern
#else 
#define Extern extern
#endif

namespace Chz
{
#ifdef CHZFRAME_BHR7P1
	constexpr int neq = 1, nieq = 12;
#endif
#ifdef CHZFRAME_BHR7P1_SIM
	constexpr int neq = 1, nieq = 12;
#endif
#ifdef CHZFRAME_BHR7P2
	constexpr int neq = 5, nieq = 12;
#endif

#define Matrix6d Matrix<double, 6, 6>
#define Vector6d Matrix<double, 6, 1>
#define Matrix12d Matrix<double, 12, 12>
#define Vector12d Matrix<double, 12, 1>
#define Matrixnd Matrix<double, ndof, ndof>
#define Vectornd Matrix<double, ndof, 1>

	class QP_Moment_Controller
	{
		double T;
		int ifinit;
		char supleg;

		//Joint
		Eigen::Vectornd q, dq, ddq;
		Eigen::Vectornd D_joint;
		Eigen::Vectornd ddqd;
		void _GetQcAb_Joint();
		//Foot
		double J[6][ndof];
		Eigen::Vector12d D_ank;
		Eigen::Vector12d Ank[3], dAnk, ddAnk;
		Eigen::Vector12d ddAnkd;
		Eigen::Matrix<double, 12, ndof> J_ank, J_anklast, dJ_ank, D_ank_J_ank;
		void _GetQcAb_Foot();
		//Force
		double Ms[ndof][ndof], fs[ndof];
		Eigen::Vector6d D_ft;
		Eigen::Matrix<double, 6, ndof> M, TM;
		Eigen::Vector6d f, Tf;
		Eigen::Matrix6d T_wai2foot;
		Eigen::Vector6d GRF;
		void _GetQcAb_FT();
		//Momentum
		double Hs[2][6];
		Eigen::Vector6d D_mom;
		Eigen::Vector3d CoM, CoM_last, dCoM;
		Eigen::Vector6d Mom, Mom_last, dMom, dMomd;
		Eigen::Matrix<double, 6, ndof> H, H_last, dH, D_mom_H;
		void _GetQcAb_Momentum();
		// QP
		Eigen::Matrixnd Q;
		Eigen::Vectornd c;
		Eigen::Matrix<double, nieq, ndof> A;
		Eigen::Matrix<double, nieq, 1> b;
		Eigen::Matrix<double, neq, ndof> Aeq;
		Eigen::Matrix<double, neq, 1> beq;
		Eigen::Matrix<double, 1, ndof> Atemp;
		double btemp;
		double qs[ndof], dqs[ndof];
		int neqnow, nieqnow;
		void _AddCons(char eq, Eigen::Matrix<double, 1, ndof>& Aeq1, double beq1, char c = '<');
		void _GetQcAb();
	public:
		QP_Moment_Controller();
		void SetPeriod(double t1);
		//Joint
		void Resetq(Eigen::Vectornd& q1, Eigen::Vectornd& dq1);
		void Outputq(Eigen::Vectornd& q1, Eigen::Vectornd& dq1, Eigen::Vectornd& ddq_last1);
		void OutputWaist(Eigen::Vector3d& Waist1, Eigen::Vector3d& dWaist1);
		void SetD_joint(Eigen::Vectornd& D_joint1);
		void Setddqd(Eigen::Vectornd& ddqd1);
		//Foot
		void OutputAnk(Eigen::Vector12d& Ank1, Eigen::Vector12d& dAnk1);
		void OutputFT(Eigen::Vector6d& FT1);
		void SetddAnkd(Eigen::Vector12d& ddAnkd1);
		void SetSupleg(char _supleg);
		//Mom
		void OutputCoM(Eigen::Vector3d& CoM1, Eigen::Vector3d& dCoM1);
		void OutputMom(Eigen::Vector6d& Mom1, Eigen::Vector6d& dMom1);
		void SetD_mom(Eigen::Vector6d& D_mom1);
		void SetdMomd(Eigen::Vector6d& dMomd1);
		//QP
		int Update();
	};

	Extern QP_Moment_Controller QMC1;
}
#undef Extern 
#endif