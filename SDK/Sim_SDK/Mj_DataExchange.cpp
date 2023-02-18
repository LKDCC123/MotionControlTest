#ifndef MJ_DATAEXCHENGE_C
#define MJ_DATAEXCHENGE_C
#include "Mj_DataExchange.h"
#include <Test_control.h>

extern double dCmdJointsPos[15];

int fndMjDataExchange(double dptJointsPosition[50], double dptJointsVelocity[50], double dptGyroSensor[2][3], double dptFootFT[10][6], int k_pre, double dptCmdJointsPosition[50]) {
    // IMU mapping
	// XS_Pitch = dptGyroSensor[0][0];
	// // if (XS_Pitch > 0) XS_Pitch = XS_Pitch - 3.14;
	// // else if (XS_Pitch < 0) XS_Pitch = XS_Pitch + 3.14;
	// // else XS_Pitch = 0.0;
    // XS_Roll = dptGyroSensor[0][1];
	// XS_Yaw = dptGyroSensor[0][2];
	// // printf("%lf\t%lf\n", XS_Pitch * 57.3, XS_Roll * 57.3);
	// for (int i = 0; i < 6; i++) {
	// 	Real_LegJoint.qr[i] = dptJointsPosition[i];
	// 	Real_LegJoint.ql[i] = dptJointsPosition[i + 6];
    // }
    // // FootFT mapping
	// double dTrqLimit[2] = {-800.0, 800.0};
	// double dFrcLimit[2] = {-1800.0, 1800.0};
	// FootFT[1][0] = dptFootFT[1][0];
	// FootFT[1][1] = dptFootFT[1][1];
	// FootFT[1][2] = fndLimit(dptFootFT[1][2], dFrcLimit);
	// FootFT[1][3] = fndLimit(dptFootFT[1][4], dTrqLimit); // pit
	// FootFT[1][4] = fndLimit(-dptFootFT[1][3], dTrqLimit); // rol
	// FootFT[1][5] = dptFootFT[1][5];
	// FootFT[2][0] = dptFootFT[0][0];
	// FootFT[2][1] = dptFootFT[0][1];
	// FootFT[2][2] = fndLimit(dptFootFT[0][2], dFrcLimit);
	// FootFT[2][3] = fndLimit(dptFootFT[0][4], dTrqLimit); // pit
	// FootFT[2][4] = fndLimit(-dptFootFT[0][3], dTrqLimit); // rol
	// FootFT[2][5] = dptFootFT[0][5];
	// printf("%lf\t%lf\n", FootFT[1][4], FootFT[2][4]);

    // K_Preview_Con = k_pre;

	// your control should be added here s--------------------------------------
	
	fnvTestCon();

	// your control should be added here e--------------------------------------

	for (int i = 0; i < 15; i++) dptCmdJointsPosition[i] = dCmdJointsPos[i];
	
    return 0;
}

#endif