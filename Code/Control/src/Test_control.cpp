#include <Test_control.h>
#include <DWholeBC.hpp>
_D_USING_WBC

double dControlT = 0.004;
double dCmdJointsPos[__JointNum] = {
    0.0, 0.0, 0.0, // waist yaw, L arm, R arm
    0.0, 0.0, -12.5 / 57.3, 25.0 / 57.3, -12.5 / 57.3, 0.0, // left leg
    0.0, 0.0, -12.5 / 57.3, 25.0 / 57.3, -12.5 / 57.3, 0.0 // right leg 
};
double dStateInit[__DoFNum] = {
    0.760832, 0.0, 0.0, 0.0, 0.0, 0.0, // trunk [z, y, x, rz, ry, rx]
    0.0, 0.0, 0.0, // waist yaw, L arm, R arm
    0.0, 0.0, -12.5 / 57.3, 25.0 / 57.3, -12.5 / 57.3, 0.0, // left leg
    0.0, 0.0, -12.5 / 57.3, 25.0 / 57.3, -12.5 / 57.3, 0.0 // right leg 
};
tp_stSDMech stRobotMech = {
//		      mass     inerx   inery   inerz    bodytojoint           inbtojoint
/*midbody*/	{ 15.733,  0.1760, 0.1149, 0.1099,  0.000, 0.000, 0.000,  0.000, 0.000, 0.000 }, 
/*uppbody*/	{ 15.401,  0.4813, 0.1584, 0.4315,  0.000, 0.000,-0.167,  0.008, 0.000, 0.150 }, 
/*larm*/	  { 01.520,  0.0264, 0.0277, 0.0021,  0.000, 0.000, 0.291,  0.000, 0.268, 0.017 },
/*rarm*/    { 01.520,  0.0264, 0.0277, 0.0021,  0.000, 0.000, 0.291,  0.000,-0.268, 0.017 },
/*lthigh*/	{ 06.042,  0.0530, 0.0550, 0.0140,  0.000, 0.000, 0.196,  0.000, 0.080,-0.086 },
/*lshank*/	{ 00.719,  0.0121, 0.0124, 0.0005,  0.000, 0.000, 0.132,  0.000, 0.000,-0.124 },
/*lfoot*/	  { 01.152,  0.0017, 0.0047, 0.0052,  0.000, 0.000, 0.050,  0.000, 0.000,-0.188 },
/*rthigh*/	{ 06.042,  0.0530, 0.0550, 0.0140,  0.000, 0.000, 0.196,  0.000,-0.080,-0.086 },
/*rshank*/	{ 00.719,  0.0121, 0.0124, 0.0005,  0.000, 0.000, 0.132,  0.000, 0.000,-0.124 },
/*rfoot*/	  { 01.152,  0.0017, 0.0047, 0.0052,  0.000, 0.000, 0.050,  0.000, 0.000,-0.188 },
            __BodyNum,
            __DoFNum,
};
st_WBCData stWBC = { 0.0 };
st_Gains stGains = {
    // for central kinematics
    { 120.0, 2500.0, 600.0, 120.0, 10.0, 2.0,     // [x/rx][kl, kc, kdc, kk, kpos, kdpos]
      120.0, 2500.0, 600.0, 120.0, 10.0, 2.0,     // [y/ry][kl, kc, kdc, kk, kpos, kdpos]
      120.0, 2500.0, 600.0, 120.0, 10.0, 2.0 },   // [z/rz][kl, kc, kdc, kk, kpos, kdpos]
    // for ankles
    { 1000.0, 200.0, 1000.0, 200.0,               // [x/rx][kp, kd, krp, krd]
      1000.0, 200.0, 1000.0, 200.0,               // [y/ry][kp, kd, krp, krd]
      1000.0, 200.0, 1000.0, 200.0 },             // [z/rz][kp, kd, krp, krd]
    // weights
    { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 },   // [mom tracking][wx, wy, wz, wrx, wry, wrz]
    { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 },   // [ank tracking][wx, wy, wz, wrx, wry, wrz]
};
double dSensQIn[__DoFNum], dSensUIn[__DoFNum];
st_Target stRefIn;

c_WholeBC cProgWBC(&stWBC, &stRobotMech, &stGains, dControlT);

double Zc, Zc_last = 0.0, dZc, T1 = 5.0, T2 = 1.0, T3 = 2.0;
void fnvTestCon(int nKpre) {
    // printf("%d\n", nKpre);
    cProgWBC.fnbInit(dStateInit);
    Zc = 0.743834; 
    // if(nKpre * dControlT <= T1 * 0.5) Zc = 0.743834 - 0.3 * sin(2 * 3.1415 / T1 * nKpre * dControlT);
    // else if(nKpre * dControlT <= T1 * 0.5 + T2 * 0.5) Zc = 0.743834 - 0.3 + 0.3 * sin(2 * 3.1415 / T2 * (nKpre * dControlT - T1 * 0.5));
    // else if(nKpre * dControlT <= T1 * 0.5 + T2 * 0.5 + T3 * 0.5) Zc = 0.743834 - 0.2 * sin(2 * 3.1415 / T3 * (nKpre * dControlT - T1 * 0.5 - T2 * 0.5));
    // else Zc = 0.743834 - 0.2;
    // dZc = (Zc - Zc_last) / dControlT;
    Zc_last = Zc;

    
    // c and dc
    stRefIn.c[0] = 0.014373, stRefIn.c[1] = 0.000000, stRefIn.c[2] = Zc;
    stRefIn.dc[0] = 0.0, stRefIn.dc[1] = 0.000000, stRefIn.dc[2] = dZc;
    // mom and dmom
    stRefIn.h[0] = 0.0, stRefIn.h[1] = 0.0, stRefIn.h[2] = 0.0;
    stRefIn.h[3] = 0.0, stRefIn.h[4] = 0.0, stRefIn.h[5] = 0.0;
    stRefIn.dh[0] = 0.0, stRefIn.dh[1] = 0.0, stRefIn.dh[2] = 0.0;
    stRefIn.dh[3] = 0.0, stRefIn.dh[4] = 0.0, stRefIn.dh[5] = 0.0;
    // posture
    stRefIn.pos[0] = 0.0, stRefIn.pos[1] = 0.0, stRefIn.pos[2] = 0.0;
    stRefIn.dpos[0] = 0.0, stRefIn.dpos[1] = 0.0, stRefIn.dpos[2] = 0.0;
    // left ank
    stRefIn.Ank[0][0] = 0.0, stRefIn.Ank[0][1] = 0.08, stRefIn.Ank[0][2] = 0.05; 
    stRefIn.Ank[0][3] = 0.0, stRefIn.Ank[0][4] = 0.0, stRefIn.Ank[0][5] = 0.0;
    stRefIn.dAnk[0][0] = 0.0, stRefIn.dAnk[0][1] = 0.0, stRefIn.dAnk[0][2] = 0.0;
    stRefIn.dAnk[0][3] = 0.0, stRefIn.dAnk[0][4] = 0.0, stRefIn.dAnk[0][5] = 0.0;
    stRefIn.ddAnk[0][0] = 0.0, stRefIn.ddAnk[0][1] = 0.0, stRefIn.ddAnk[0][2] = 0.0;
    stRefIn.ddAnk[0][3] = 0.0, stRefIn.ddAnk[0][4] = 0.0, stRefIn.ddAnk[0][5] = 0.0;
    // right ank
    stRefIn.Ank[1][0] = 0.0, stRefIn.Ank[1][1] = -0.08, stRefIn.Ank[1][2] = 0.05;
    stRefIn.Ank[1][3] = 0.0, stRefIn.Ank[1][4] = 0.0, stRefIn.Ank[1][5] = 0.0;
    stRefIn.dAnk[1][0] = 0.0, stRefIn.dAnk[1][1] = 0.0, stRefIn.dAnk[1][2] = 0.0;
    stRefIn.dAnk[1][3] = 0.0, stRefIn.dAnk[1][4] = 0.0, stRefIn.dAnk[1][5] = 0.0;
    stRefIn.ddAnk[1][0] = 0.0, stRefIn.ddAnk[1][1] = 0.0, stRefIn.ddAnk[1][2] = 0.0;
    stRefIn.ddAnk[1][3] = 0.0, stRefIn.ddAnk[1][4] = 0.0, stRefIn.ddAnk[1][5] = 0.0;

    cProgWBC.fnbUpdateWBC(dSensQIn, dSensUIn, stRefIn, dCmdJointsPos);
  
    // cProgWBC.fnvShowTrackingErr();
    // cProgWBC.fnvShowHf();
}