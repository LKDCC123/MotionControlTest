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
    0.776, 0.0, 0.0, 0.0, 0.0, 0.0, // trunk [z, y, x, rz, ry, rx]
    0.0, 0.0, 0.0, // waist yaw, L arm, R arm
    0.0, 0.0, -0.0 * 12.5 / 57.3, 0.0 * 25.0 / 57.3, -0.0 * 12.5 / 57.3, 0.0, // left leg
    0.0, 0.0, -0.0 * 12.5 / 57.3, 0.0 * 25.0 / 57.3, -0.0 * 12.5 / 57.3, 0.0 // right leg 
};
tp_stSDMech stRobotMech = {
//		      mass     inerx   inery   inerz    bodytojoint           inbtojoint
/*midbody*/	{ 15.733,  0.1760, 0.1149, 0.1099,  0.000, 0.000, 0.000,  0.000, 0.000, 0.000 }, 
/*uppbody*/	{ 15.401,  0.4813, 0.1584, 0.4315,  0.000, 0.000,-0.167,  0.008, 0.000, 0.150 }, 
/*larm*/	{ 01.520,  0.0264, 0.0277, 0.0021,  0.000, 0.000, 0.291,  0.000, 0.268, 0.017 },
/*rarm*/    { 01.520,  0.0264, 0.0277, 0.0021,  0.000, 0.000, 0.291,  0.000,-0.268, 0.017 },
/*lthigh*/	{ 06.042,  0.0530, 0.0550, 0.0140,  0.000, 0.000, 0.196,  0.000, 0.080,-0.086 },
/*lshank*/	{ 00.719,  0.0121, 0.0124, 0.0005,  0.000, 0.000, 0.132,  0.000, 0.000,-0.124 },
/*lfoot*/	{ 01.152,  0.0017, 0.0047, 0.0052,  0.000, 0.000, 0.050,  0.000, 0.000,-0.188 },
/*rthigh*/	{ 06.042,  0.0530, 0.0550, 0.0140,  0.000, 0.000, 0.196,  0.000,-0.080,-0.086 },
/*rshank*/	{ 00.719,  0.0121, 0.0124, 0.0005,  0.000, 0.000, 0.132,  0.000, 0.000,-0.124 },
/*rfoot*/	{ 01.152,  0.0017, 0.0047, 0.0052,  0.000, 0.000, 0.050,  0.000, 0.000,-0.188 },
            __BodyNum,
            __DoFNum,
};
st_WBCData stWBC = { 0.0 };
st_Gains stGains = {
    { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,     // [x/rx][kl, kc, kdc, kk, kpos, kdpos]
      1.0, 1.0, 1.0, 1.0, 1.0, 1.0,     // [y/ry][kl, kc, kdc, kk, kpos, kdpos]
      1.0, 1.0, 1.0, 1.0, 1.0, 1.0 },   // [z/rz][kl, kc, kdc, kk, kpos, kdpos]
    { 1.0, 1.0, 1.0, 1.0,               // [x/rx][kp, kd, krp, krd]
      1.0, 1.0, 1.0, 1.0,               // [y/ry][kp, kd, krp, krd]
      1.0, 1.0, 1.0, 1.0 },             // [z/rz][kp, kd, krp, krd]
};
double dSensQIn[__DoFNum], dSensUIn[__DoFNum];
st_Target stRefIn;
c_WholeBC cProgWBC(&stWBC, &stRobotMech, &stGains, dControlT);

// 0.014373, 0.000000, 0.703002
void fnvTestCon() {
    cProgWBC.fnbInit(dStateInit);
    cProgWBC.fnbUpdateWBC(dSensQIn, dSensUIn, stRefIn, dCmdJointsPos);
    cProgWBC.fnvShowAnk();
    

}