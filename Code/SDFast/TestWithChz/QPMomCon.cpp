#ifndef CHZFRAME_CTRL_CHZQPMONCON_CPP
#define CHZFRAME_CTRL_CHZQPMONCON_CPP
#include "QPMomCon.h"
#include "Chz_online/HondaPGParam.h"
#include "QP_Moment_Control/GeometryConf.h"
#include "../FullDoFIK.h"
#include "../ChzFrameLogger.h"
#include <windows.h>
using namespace Eigen;
namespace ChzFrame
{
	// warining! cannot reset twice
	int QPMomCon::Reset()
	{
		using namespace Chz;
		using namespace ChzSD;
		static int iffirst = 1;
		if(!iffirst) return 1;
		QMC1.SetPeriod(Control_T);
		D_joint.setZero();
		D_mom.setZero();
		ddqd.setZero();
#ifndef CHZFRAME_BHRGAO2
#ifdef CHZFRAME_BHR7P1_SIM
		double qleg_ini = 12.5;
#endif
#ifdef CHZFRAME_BHR7P1
		double qleg_ini = 12.5;
#endif
#ifdef CHZFRAME_BHR7P2
		double qleg_ini = 12.5;
#endif
#ifdef CHZFRAME_ATHLETE
		double qleg_ini = 20.0;
#endif
		q << 2.0 * cos(qleg_ini / 57.3) * THIGH_LEN / 1e3 + Ankposz + (-RobotGeom.FindBody("lthigh").inbtojoint[2]), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, -qleg_ini / 57.3, qleg_ini * 2.0 / 57.3, -qleg_ini / 57.3, 0.0,
			0.0, 0.0, -qleg_ini / 57.3, qleg_ini * 2.0 / 57.3, -qleg_ini / 57.3, 0.0;
		//std::cout << q << std::endl << std::endl;
#else
		q << 0.719, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, -0.17740569, 0.34476912, -0.16736343, 0.0,
			0.0, 0.0, -0.17740569, 0.34476912, -0.16736343, 0.0;
#endif
		QMC1.Resetq(q, dq);
		iffirst = 0;
		return 1;
	}
	int QPMomCon::Update(RobotState* PState, RobotState* SState, RobotState* CState)
	{
		using namespace Chz;
		using namespace ChzSD;
		static double m_total_qp, cm1[3], im1[3][3];
		static GaitInfo* Info;
		if (FrameHandler.IfFirstUpdate())
		{
			sdsys(&m_total_qp, cm1, im1);
			FrameHandler.GetGaitInfo(&Info);
		}

		bool Ifcon = !(PState->GaitState == 'S' || PState->Stepnow == 0 || PState->Stepnow == Info->stepnum - 1);
		static bool Ifconlast = -1;
		
		QMC1.OutputAnk(Ank, dAnk);
		QMC1.OutputCoM(CoM, dCoM);
		QMC1.OutputMom(Mom, dMom);
	// CoM following
		CoMp << CState->CoM[0], CState->CoM[1], CState->CoM[2];
		dCoMp << CState->dCoM[0], CState->dCoM[1], CState->dCoM[2];
		ChzF(i, 0, 2) dMomd(i) = -12.0 * m_total_qp * (CoM(i) - CoMp(i)) - 5.0 * m_total_qp * (dCoM(i) - dCoMp(i)) + m_total_qp * CState->ddCoM[i];
		if (Ifcon)
		{
			dMomd(3) = -100.0 * (Mom(3) - (CState->Lc[0])) - (CState->dLc[0]);
			dMomd(4) = -100.0 * (Mom(4) - (CState->Lc[1])) - (CState->dLc[1]);
			dMomd(5) = -100.0 * Mom(5);
		}
		else dMomd(3) = dMomd(4) = dMomd(5) = 0.0;
		if (Ifconlast != Ifcon && !Ifcon)
		{
			ChzF(i, 0, 2) D_mom(i) = 3.0;
			ChzF(i, 3, 5) D_mom(i) = 0.0;
			QMC1.SetD_mom(D_mom);
		}
		else if(Ifconlast != Ifcon)
		{
			ChzF(i, 0, 2) D_mom(i) = 3.0;
			ChzF(i, 3, 5) D_mom(i) = 3.0;
			QMC1.SetD_mom(D_mom);
		}
		QMC1.SetdMomd(dMomd);
	// Ankle following
		ChzF(i, 0, 5)
		{
			Ankp(i) = CState->LAnk[i], Ankp(i + 6) = CState->RAnk[i];
			dAnkp(i) = CState->dLAnk[i], dAnkp(i + 6) = CState->dRAnk[i];
		}
		ddAnkd = -200.0 * (Ank - Ankp) - 30.0 * (dAnk - dAnkp);
		ChzF(i, 0, 5) ddAnkp(i) = CState->ddLAnk[i];
		ChzF(i, 0, 5) ddAnkp(i + 6) = CState->ddRAnk[i];
		ddAnkd += ddAnkp;
		QMC1.SetddAnkd(ddAnkd);
	// Posture regulating
		double Yaw_coef = 0.6;
		double Del_Ank[3] = { Yaw_coef * (CState->RAnk[0] - CState->LAnk[0]),
								Yaw_coef * (CState->dRAnk[0] - CState->dLAnk[0]),
								Yaw_coef * (CState->ddRAnk[0] - CState->ddLAnk[0]) };
		ddqd(3) = 50.0 * (Del_Ank[0] - q(3)) + 10.0 * (Del_Ank[1] - dq(3)) + Del_Ank[2];
		//ddqd(3) += -10.0 * (q(3) - 0.0) - 4.0 * dq(3);
		ddqd(4) = -10.0 * (q(4) - 0.0) - 4.0 * dq(4);
		ddqd(5) = -10.0 * (q(5) - 0.0) - 4.0 * dq(5);
		ddqd(6) = -10.0 * (q(6) - 0.0) - 4.0 * dq(6);
		ddqd(7) = -7.0 * (q(7) - 0.0) - 3.34 * dq(7);
		QMC1.Setddqd(ddqd);

		if (Ifconlast != Ifcon && !Ifcon)
		{
			D_joint(3) = 100.0; // yaw
			D_joint(4) = 380.0; // pitch
			D_joint(5) = 200.0; // roll
			D_joint(6) = 180.0; // waist joint
			D_joint(7) = 7.0;
			QMC1.SetD_joint(D_joint);
		}
		else if(Ifconlast != Ifcon)
		{
			D_joint(3) = 10.0;
			D_joint(4) = 1.0;
			D_joint(5) = 3.0;
			D_joint(6) = 3.0;
			D_joint(7) = 7.0;
			QMC1.SetD_joint(D_joint);
		}
		
	// FootFT
		QMC1.SetSupleg(CState->Supleg);
	//
		Ifconlast = Ifcon;
		if (!QMC1.Update())
		{
			printf("QP Failed!\n");
			return 0;
		}
	// Output
		QMC1.Outputq(q, dq, ddq);
		QMC1.OutputFT(FT);
		double pos[3] = { RobotGeom.FindBody("lthigh").inbtojoint[0], 0.0, RobotGeom.FindBody("lthigh").inbtojoint[2] };
		double posw[3], velw[3];
		ChzF(i, 0, ndof - 1) qs[i] = q(i), dqs[i] = dq(i);
		sdstate(0, qs, dqs);
		sdpos(0, pos, posw);
		sdvel(0, pos, velw);

		ChzF(i, 0, 2) CState->CoM[i] = CoM(i), CState->dCoM[i] = dCoM(i);
		ChzF(i, 0, 2) CState->Lc[i] = Mom(i + 3), CState->dLc[i] = dMom(i + 3);

		// Safety check
		if(FrameHandler.N_Control() > 400)
		{
			ChzF(i, 0, 2) if(fabs(CState->CoM[i] - PState->CoM[i]) > 0.1) return 0;
			ChzF(i, 0, 1) if(fabs(CState->Lc[i] - PState->Lc[i]) > 0.4) return 0;
		}

		ChzF(i, 0, 2) CState->Waist[i] = posw[i], CState->dWaist[i] = velw[i];
		ChzF(i, 0, 2) CState->Waist[i + 3] = q(5 - i), CState->dWaist[i + 3] = dq(5 - i);
		CState->WaistJoint[0] = q(6), CState->dWaistJoint[0] = dq(6);
		ChzF(i, 0, 5) CState->LAnk[i] = Ank(i), CState->RAnk[i] = Ank(i + 6);
		CState->LArm[0] = q(7), CState->RArm[0] = q(8);
		if (CState->Supleg == 'L')
		{
			ChzF(i, 0, 2) CState->LFootFT[i] = FT(i), CState->LFootFT[i + 3] = FT(i + 3);
			ChzF(i, 0, 2) CState->RFootFT[i] = 0.0, CState->RFootFT[i + 3] = 0.0;
		}
		else if (CState->Supleg == 'R')
		{
			ChzF(i, 0, 2) CState->RFootFT[i] = FT(i), CState->RFootFT[i + 3] = FT(i + 3);
			ChzF(i, 0, 2) CState->LFootFT[i] = 0.0, CState->LFootFT[i + 3] = 0.0;
		}
		else if (CState->Supleg == 'N')
		{
			ChzF(i, 0, 2) CState->LFootFT[i] = 0.0, CState->LFootFT[i + 3] = 0.0;
			ChzF(i, 0, 2) CState->RFootFT[i] = 0.0, CState->RFootFT[i + 3] = 0.0;
		}
		else // suppose Tx = 0 for both l and r
		{
			// Fzl + Fzr = Fz, (Fl - Fr) * l = Tx
			double ly = 0.5 * (CState->LAnk[1] - CState->RAnk[1]);
			if (FT(3) > FT(2)* ly) FT(3) = FT(2) * ly;
			if (FT(3) < -FT(2) * ly) FT(3) = -FT(2) * ly;
			double lprop = 0.5 + FT(3) / (2.0 * FT(2) * ly);
			lprop = fmin(fmax(lprop, 0.0), 1.0);
			double rprop = 1.0 - lprop;
			ChzF(i, 0, 2) CState->LFootFT[i] = lprop * FT(i), CState->RFootFT[i] = rprop * FT(i);
			double lx = 0.5 * (CState->LAnk[0] - CState->RAnk[0]);
			FT(4) -= lx * (CState->RFootFT[2] - CState->LFootFT[2]);
			FT(5) -= lx * (CState->LFootFT[1] - CState->RFootFT[1]);
			FT(5) -= ly * (CState->RFootFT[0] - CState->LFootFT[0]);
			CState->LFootFT[3] = CState->RFootFT[3] = 0.0;
			CState->LFootFT[4] = lprop * FT(4), CState->RFootFT[4] = rprop * FT(4);
			CState->LFootFT[5] = lprop * FT(5), CState->RFootFT[5] = rprop * FT(5);
		}
		CState->CalZMP();
		
		double difcon = 1.0 * Ifcon;
		// ChzLogger.AddLog(-123, "Ifcon", &difcon);
		// ChzLogger.AddLog(-123, "Lc_P", &PState->Lc[0], 2);
		// ChzLogger.AddLog(-123, "dLc_P", &PState->dLc[0], 2);
		// ChzLogger.AddLog(-123, "Lc_C", &CState->Lc[0], 2);
		// ChzLogger.AddLog(-123, "dLc_C", &CState->dLc[0], 2);
		return 1;
	}
}
#endif