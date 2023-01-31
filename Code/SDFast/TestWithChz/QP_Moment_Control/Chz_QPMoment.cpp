#ifndef CHZ_QPMOMENT_CPP
#define CHZ_QPMOMENT_CPP
#include "Chz_QPMoment.h"
#include "GeometryConf.h"
#ifdef CHZFRAME_BHR7P1_SIM
#include "..\\..\\ChzFrameLogger.h"
#include <windows.h>
#endif
using namespace Eigen;
using namespace ChzSD;

namespace Chz
{
	//QuadProgDense QPDense1;
}
// neq = 1 for 7p1, neq = 7 for 7p2 (fixed constraints)
void Chz::QP_Moment_Controller::_GetQcAb_Joint()
{
	//Q += D_joint;
	ChzF(i, 0, ndof - 1) Q(i, i) += D_joint(i);
	//c += (-ddqd.transpose() * D_joint).transpose();
	ChzF(i, 0, ndof - 1) c(i) += -ddqd(i) * D_joint(i);
	ChzF(i, 0, ndof - 1) 
	{
		//if (i != 3 && i != 6 && i != 7 && i != 8 && i != 9 && i != 15) continue;
		//if (i != 3 && i != 7 && i != 8 && i != 9 && i != 15) continue;
		//if (i != 3 && i != 7 && i != 8) continue;
		//if (i != 7 && i != 8) continue;
#ifdef CHZFRAME_BHR7P1
		continue;
#endif
#ifdef CHZFRAME_BHR7P1_SIM
		//if (i != 3 && i != 6 && i != 7 && i != 8 && i != 9 && i != 15) continue;
		continue;
#endif
#ifdef CHZFRAME_BHR7P2
		if (i != 3 && i != 6 && i != 9 && i != 15) continue;
#endif	
#ifdef CHZFRAME_BHRGAO2
		if (i != 3 && i != 6 && i != 7 && i != 8 && i != 9 && i != 15) continue;
#endif	
		if (!ifinit)
		{
			Atemp.setZero(); Atemp(i) = 1.0;
			_AddCons('e', Atemp, 0.0);
		}
		else neqnow++;
	}
#ifdef CHZFRAME_BHR7P1
	if (!ifinit)
	{
		Atemp.setZero(); Atemp(7) = Atemp(8) = 1.0;
		_AddCons('e', Atemp, 0.0);
	}
	else neqnow++;
#endif
#ifdef CHZFRAME_BHR7P1_SIM
	if (!ifinit)
	{
		Atemp.setZero(); Atemp(7) = Atemp(8) = 1.0;
		_AddCons('e', Atemp, 0.0);
	}
	else neqnow++;
#endif
#ifdef CHZFRAME_BHR7P2
	if (!ifinit)
	{
		Atemp.setZero(); Atemp(7) = Atemp(8) = 1.0;
		_AddCons('e', Atemp, 0.0);
	}
	else neqnow++;
#endif
}
// no constraint
void Chz::QP_Moment_Controller::_GetQcAb_Foot()
{
	double pos[3], posw[3], Rot[3][3], Eul[3];
	pos[0] = 0.01; pos[1] = 0.01; pos[2] = RobotGeom.FindBody("lfoot").bodytojoint[2];
	if(!ifinit) ChzF(i, 0, 2) D_ank(i) = D_ank(i + 6) = 3000.0, D_ank(i + 3) = D_ank(i + 9) = 300.0;

	if (ifinit) Ank[0] = Ank[1], Ank[1] = Ank[2];
	sdpos(6, pos, posw);
	sdorient(6, Rot);
	Eul[0] = atan2(Rot[2][1], Rot[2][2]);
	Eul[1] = atan2(-Rot[2][0], sqrt(Rot[2][1] * Rot[2][1] + Rot[2][2] * Rot[2][2]));
	Eul[2] = atan2(Rot[1][0], Rot[0][0]);
	ChzF(i, 0, 2) if (Eul[i] > pi) Eul[i] -= 2.0 * pi; else if (Eul[i] < -pi) Eul[i] += 2.0 * pi;
	ChzF(i, 0, 2) Ank[2](i) = posw[i], Ank[2](i + 3) = Eul[i];

	sdpos(9, pos, posw);
	sdorient(9, Rot);
	Eul[0] = atan2(Rot[2][1], Rot[2][2]);
	Eul[1] = atan2(-Rot[2][0], sqrt(Rot[2][1] * Rot[2][1] + Rot[2][2] * Rot[2][2]));
	Eul[2] = atan2(Rot[1][0], Rot[0][0]);
	ChzF(i, 0, 2) if (Eul[i] > pi) Eul[i] -= 2.0 * pi; else if (Eul[i] < -pi) Eul[i] += 2.0 * pi;
	ChzF(i, 0, 2) Ank[2](i + 6) = posw[i], Ank[2](i + 9) = Eul[i];

	if (!ifinit) Ank[0] = Ank[1] = Ank[2];
	dAnk = (Ank[2] - Ank[1]) / T;
	ddAnk = (Ank[2] - 2.0 * Ank[1] + Ank[0]) / T / T;

	sdjacobian(6, pos, J); ChzF(i, 0, 5) ChzF(j, 0, ndof - 1) J_ank(i, j) = J[i][j];
	sdjacobian(9, pos, J); ChzF(i, 0, 5) ChzF(j, 0, ndof - 1) J_ank(i + 6, j) = J[i][j];
	if (!ifinit) J_anklast = J_ank;
	dJ_ank = (J_ank - J_anklast) / T;
	J_anklast = J_ank;
	ChzF(i, 0, 12 - 1) ChzF(j, 0, ndof - 1) D_ank_J_ank(i, j) = D_ank(i) * J_ank(i, j);
	//Q += J_ank.transpose() * D_ank * J_ank;
	Q += J_ank.transpose() * D_ank_J_ank;
	//c += ((dJ_ank * dq - ddAnkd).transpose() * D_ank * J_ank).transpose();
	c += (D_ank_J_ank.transpose()) * (dJ_ank * dq - ddAnkd);
}
// nieq = 12
void Chz::QP_Moment_Controller::_GetQcAb_FT()
{
	sdmassmat(Ms); sdfrcmat(fs);
	ChzF(i, 0, 5) ChzF(j, 0, ndof - 1) M(i, j) = Ms[i][j];
	ChzF(i, 0, 5) f(i) = -fs[i];
	
	double waistpos_rel[3] = { 0.0, 0.0, 0.0 };
	double waistpos[3], suppos[3], x, y, z;
	double zmpx_lim[2], zmpy_lim[2], zmpz_lim[2];
	zmpx_lim[0] = -0.08; zmpx_lim[1] = 0.12;
	zmpy_lim[0] = -0.04; zmpy_lim[1] = 0.05;
	zmpz_lim[0] = -0.4; zmpz_lim[1] = 0.4;

	sdpos(0, waistpos_rel, waistpos);
	if (supleg == 'L') ChzF(i, 0, 2) suppos[i] = Ank[2](i);
	else if (supleg == 'R')
	{
		ChzF(i, 0, 2) suppos[i] = Ank[2](i + 6);
		double temp = zmpy_lim[1];
		zmpy_lim[1] = -zmpy_lim[0];
		zmpy_lim[0] = -temp;
	}
	else if (supleg == 'D')
	{
		ChzF(i, 0, 2) suppos[i] = 0.5 * (Ank[2](i) + Ank[2](i + 6));
		zmpx_lim[1] += 0.5 * fabs(Ank[2](0) - Ank[2](6));
		zmpx_lim[0] -= 0.5 * fabs(Ank[2](0) - Ank[2](6));
		zmpy_lim[1] += 0.5 * fabs(Ank[2](1) - Ank[2](7));
		zmpy_lim[0] -= 0.5 * fabs(Ank[2](1) - Ank[2](7));
	}
	else if (supleg == 'N') ChzF(i, 0, 2) suppos[i] = waistpos[i];
	x = waistpos[0] - suppos[0]; y = waistpos[1] - suppos[1]; z = waistpos[2] - suppos[2];
	//if(!ifinit) T_wai2foot.setIdentity();
	//T_wai2foot(3, 1) = x; T_wai2foot(3, 2) = -y;
	//T_wai2foot(4, 0) = -x; T_wai2foot(4, 2) = z;
	//T_wai2foot(5, 0) = y; T_wai2foot(5, 1) = -z;
	/* 
	T_wai2foot =	[1  0  0  0  0  0
						 0  1  0  0  0  0
						 0  0  1  0  0  0
						 0  x -y  1  0  0
						-x  0  z  0  1  0
						 y -z  0  0  0  1]
	*/
	// TM = T_wai2foot * M;
	ChzF(j, 0, ndof - 1)
	{
		ChzF(i, 0, 2) TM(i, j) = M(i, j);
		TM(3, j) = M(3, j) + x * M(1, j) - y * M(2, j);
		TM(4, j) = M(4, j) - x * M(0, j) + z * M(2, j);
		TM(5, j) = M(5, j) + y * M(0, j) - z * M(1, j);
	}
	// Tf = T_wai2foot * f;
	ChzF(i, 0, 2) Tf(i) = f(i);
	Tf(3) = f(3) + x * f(1) - y * f(2);
	Tf(4) = f(4) - x * f(0) + z * f(2);
	Tf(5) = f(5) + y * f(0) - z * f(1);

	static double m_total = 0.0;
	if (!ifinit) ChzF(i, 0, nbod - 1) m_total += RobotGeom.bodies[i].mass;
	//x 2 y 1 z 0 tx 5 ty 4 tz 3
//Fz > 0 and Fz < 1.5 * dMomd(2)
	Atemp = TM.block(0, 0, 1, ndof);
	btemp = 0.0 - f(0);
	_AddCons('i', Atemp, btemp, '>'); // M(0)q + f(0) > 0
	Atemp = TM.block(0, 0, 1, ndof);
	btemp = 1.5 * fmax(dMomd(2) + m_total * g, 0.0) + 0.1 - f(0);
	_AddCons('i', Atemp, btemp); // M(0)q + f(0) < 1.5 * Fzd

//Friction x
	Atemp = TM.block(2, 0, 1, ndof) - mu * TM.block(0, 0, 1, ndof);
	btemp = 0.1 - Tf(2) + mu * Tf(0);
	_AddCons('i', Atemp, btemp); // M(2)q + f(2) < mu * Fz = mu * M(0)q + mu *f(0)
	Atemp = TM.block(2, 0, 1, ndof) + mu * TM.block(0, 0, 1, ndof);
	btemp = -0.1 - Tf(2) - mu * Tf(0); // M(2)q + f(2) > -mu * Fz = -mu * M(0)q - mu *f(0)
	_AddCons('i', Atemp, btemp, '>');

//Friction y
	Atemp = TM.block(1, 0, 1, ndof) - mu * TM.block(0, 0, 1, ndof);
	btemp = 0.1 - Tf(1) + mu * Tf(0);
	_AddCons('i', Atemp, btemp); // M(1)q + f(1) < mu * Fz = mu * M(0)q + mu *f(0)
	Atemp = TM.block(1, 0, 1, ndof) + mu * TM.block(0, 0, 1, ndof);
	btemp = -0.1 - Tf(1) - mu * Tf(0); // M(1)q + f(1) > -mu * Fz = -mu * M(0)q - mu *f(0)
	_AddCons('i', Atemp, btemp, '>');

//Tau x (ZMP y)
	Atemp = TM.block(5, 0, 1, ndof) - zmpy_lim[1] * TM.block(0, 0, 1, ndof);
	btemp = 0.1 - Tf(5) + zmpy_lim[1] * Tf(0);
	_AddCons('i', Atemp, btemp);
	// M(5)q + f(5) < zmpy_lim[1] * Fz = zmpy_lim[1] * M(0)q + zmpy_lim[1] *f(0)
	Atemp = TM.block(5, 0, 1, ndof) - zmpy_lim[0] * TM.block(0, 0, 1, ndof);
	btemp = -0.1 - Tf(5) + zmpy_lim[0] * Tf(0);
	_AddCons('i', Atemp, btemp, '>');
	// M(5)q + f(5) > zmpy_lim[0] * Fz = zmpy_lim[0] * M(0)q + zmpy_lim[0] *f(0)

//Tau y (ZMP x) (they are in different direction)
	Atemp = TM.block(4, 0, 1, ndof) + zmpx_lim[0] * TM.block(0, 0, 1, ndof);
	btemp = 0.1 - Tf(4) - zmpx_lim[0] * Tf(0);
	_AddCons('i', Atemp, btemp);
	// M(4)q + f(4) < -zmpx_lim[0] * Fz = -zmpx_lim[0] * M(0)q - zmpx_lim[0] *f(0)
	Atemp = TM.block(4, 0, 1, ndof) + zmpx_lim[1] * TM.block(0, 0, 1, ndof);
	btemp = -0.1 - Tf(4) - zmpx_lim[1] * Tf(0);
	_AddCons('i', Atemp, btemp, '>');
	// M(4)q + f(4) > -zmpx_lim[1] * Fz = -zmpx_lim[1] * M(0)q - zmpx_lim[1] *f(0)

//Tau z
	Atemp = TM.block(3, 0, 1, ndof) - zmpz_lim[1] * TM.block(0, 0, 1, ndof);
	btemp = 0.1 - Tf(3) + zmpz_lim[1] * Tf(0);
	_AddCons('i', Atemp, btemp);
	// M(3)q + f(3) < zmpz_lim[1] * Fz = zmpz_lim[1] * M(0)q + zmpz_lim[1] *f(0)
	Atemp = TM.block(3, 0, 1, ndof) - zmpz_lim[0] * TM.block(0, 0, 1, ndof);
	btemp = -0.1 - Tf(3) + zmpz_lim[0] * Tf(0);
	_AddCons('i', Atemp, btemp, '>');
	// M(3)q + f(3) > zmpz_lim[0] * Fz = zmpz_lim[0] * M(0)q + zmpz_lim[0] *f(0)
}
// no constraint
void Chz::QP_Moment_Controller::_GetQcAb_Momentum()
{
	double deltaq = 1e-5, temp;
	double mtemp, comtemp[3], Itemp[3][3];
	if (ifinit) CoM_last = CoM;
	sdsys(&mtemp, comtemp, Itemp);
	ChzF(i, 0, 2) CoM(i) = comtemp[i];
	if (!ifinit) CoM_last = CoM;
	dCoM = (CoM - CoM_last) / T;

	if (ifinit) Mom_last = Mom;
	sdmom(&Hs[0][0], &Hs[0][3], &temp);
	ChzF(i, 0, 5) Mom(i) = Hs[0][i];
	if (!ifinit) Mom_last = Mom;
	dMom = (Mom - Mom_last) / T;

	if (ifinit) H_last = H;
	ChzF(i, 0, ndof - 1) qs[i] = q(i), dqs[i] = dq(i);
	ChzF(i, 0, ndof - 1)
	{
		dqs[i] = dq(i) + deltaq;
		sdstate(0, qs, dqs);
		sdmom(&Hs[0][0], &Hs[0][3], &temp);

		dqs[i] = dq(i) - deltaq;
		sdstate(0, qs, dqs);
		sdmom(&Hs[1][0], &Hs[1][3], &temp);

		dqs[i] = dq(i);
		ChzF(j, 0, 5) H(j, i) = (Hs[0][j] - Hs[1][j]) / (2.0 * deltaq);
	}
	sdstate(0, qs, dqs);
	if (!ifinit) H_last = H;
	dH = (H - H_last) / T;
	ChzF(i, 0, 5) ChzF(j, 0, ndof - 1) D_mom_H(i, j) = D_mom(i) * H(i, j);
	// Q += H.transpose() * D_mom * H;
	Q += H.transpose() * D_mom_H;
	// c += ((dH * dq - dMomd).transpose() * D_mom * H).transpose();
	c += D_mom_H.transpose() * (dH * dq - dMomd);
}

void Chz::QP_Moment_Controller::_AddCons(char eq, Matrix<double, 1, ndof>& A1, double b1, char c)
{
	if (eq == 'e')
	{
		Aeq.block(neqnow, 0, 1, ndof) = (c == '>' ? -A1 : A1);
		beq(neqnow) = (c == '>' ? -b1 : b1);
		neqnow++;
	}
	else if (eq == 'i')
	{
		A.block(nieqnow, 0, 1, ndof) = (c == '>' ? -A1 : A1);
		b(nieqnow) = (c == '>' ? -b1 : b1);
		nieqnow++;
	}
	else return;
}

void Chz::QP_Moment_Controller::_GetQcAb()
{
	Q.setIdentity(); Q = Q * 1e-6;
	c.setZero();
	neqnow = nieqnow = 0;
	ChzF(i, 0, ndof - 1) qs[i] = q(i), dqs[i] = dq(i);
	sdstate(0, qs, dqs);

#ifdef CHZFRAME_BHR7P1_SIM
	LARGE_INTEGER t1, t2, tc; QueryPerformanceFrequency(&tc); double t;
	QueryPerformanceCounter(&t1);
#endif
	_GetQcAb_Foot();
#ifdef CHZFRAME_BHR7P1_SIM
	QueryPerformanceCounter(&t2);
	t = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart * 1000.0;
	ChzFrame::ChzLogger.AddLog(127, "t_foot", t);
	QueryPerformanceCounter(&t1);
#endif
	_GetQcAb_Joint();
#ifdef CHZFRAME_BHR7P1_SIM
	QueryPerformanceCounter(&t2);
	t = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart * 1000.0;
	ChzFrame::ChzLogger.AddLog(127, "t_joint", t);
	QueryPerformanceCounter(&t1);
#endif
	_GetQcAb_Momentum();
#ifdef CHZFRAME_BHR7P1_SIM
	QueryPerformanceCounter(&t2);
	t = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart * 1000.0;
	ChzFrame::ChzLogger.AddLog(127, "t_mom", t);
	QueryPerformanceCounter(&t1);
#endif
	_GetQcAb_FT();
#ifdef CHZFRAME_BHR7P1_SIM
	QueryPerformanceCounter(&t2);
	t = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart * 1000.0;
	ChzFrame::ChzLogger.AddLog(127, "t_ft", t);
#endif
}

Chz::QP_Moment_Controller::QP_Moment_Controller()
{
	ifinit = 0;
	//Joint
	D_joint.setZero();
	//Foot
	
	//Force
	D_ft.setZero();
	T_wai2foot.setIdentity();
	//Moment
	D_mom.setZero();
	//QP
	neqnow = nieqnow = 0;
	A.setZero(); b = 1e-4 * Eigen::Matrix<double, nieq, 1>::Ones();
	Aeq.setZero(); beq = 1e-4 * Eigen::Matrix<double, neq, 1>::Ones();
	Atemp.setZero(); btemp = 1e-4;
}

void Chz::QP_Moment_Controller::SetPeriod(double t1)
{
	T = t1;
}

void Chz::QP_Moment_Controller::Resetq(Vectornd& q1, Vectornd& dq1)
{
	//QPDense1.problem(ndof, neq, nieq);
	ifinit = 0;
	q = q1; dq = dq1; ddq.setZero();
	supleg = 'D';
	_GetQcAb();
	ifinit = 1;
}

void Chz::QP_Moment_Controller::Setq(Vectornd& q1, Vectornd& dq1)
{
	//QPDense1.problem(ndof, neq, nieq);
	q = q1; dq = dq1; ddq.setZero();
}

void Chz::QP_Moment_Controller::Outputq(Vectornd& q1, Vectornd& dq1, Vectornd& ddq_last1)
{
	q1 = q; dq1 = dq; ddq_last1 = ddq;
}

void Chz::QP_Moment_Controller::OutputWaist(Vector3d& Waist1, Vector3d& dWaist1)
{
	ChzF(i, 0, 2) Waist1(i) = q(2 - i), Waist1(i + 3) = q(5 - i);
	ChzF(i, 0, 2) dWaist1(i) = dq(2 - i), dWaist1(i + 3) = dq(5 - i);
}

void Chz::QP_Moment_Controller::SetD_joint(Vectornd& D_joint1) { D_joint = D_joint1; }
void Chz::QP_Moment_Controller::Setddqd(Vectornd& ddqd1) { ddqd = ddqd1; }
void Chz::QP_Moment_Controller::OutputAnk(Vector12d& Ank1, Vector12d& dAnk1) { Ank1 = Ank[2]; dAnk1 = dAnk; }
void Chz::QP_Moment_Controller::OutputFT(Vector6d& FT1)
{
	GRF = TM * ddq + Tf;
	ChzF(i, 0, 2) FT1(i) = GRF(2 - i), FT1(i + 3) = GRF(2 - i + 3);
}

void Chz::QP_Moment_Controller::SetddAnkd(Vector12d& ddAnkd1) { ddAnkd = ddAnkd1; }

void Chz::QP_Moment_Controller::SetSupleg(char _supleg) { supleg = _supleg; }

void Chz::QP_Moment_Controller::OutputCoM(Vector3d& CoM1, Vector3d& dCoM1) { CoM1 = CoM; dCoM1 = dCoM; }

void Chz::QP_Moment_Controller::OutputMom(Vector6d& Mom1, Vector6d& dMom1) { Mom1 = Mom; dMom1 = dMom; }

void Chz::QP_Moment_Controller::SetD_mom(Vector6d& D_mom1) { D_mom = D_mom1; }

void Chz::QP_Moment_Controller::SetdMomd(Vector6d& dMomd1) { dMomd = dMomd1; }

int Chz::QP_Moment_Controller::Update()
{
	_GetQcAb();
	int qpflag = 1;
	// qpflag = QPDense1.solve(Q, c, Aeq, beq, A, b, 0);
	// ddq = QPDense1.result();
	//ddq.setZero();
	dq += ddq * T;
	q += dq * T;
	return qpflag;
}
#endif