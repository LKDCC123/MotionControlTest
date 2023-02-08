// test the SDFast functions
// 20221223 Dcc <3120195094@bit.edu.cn>
#include <DSDFastTools.h> // dcc sdteol
#include <iostream>
#include <stdio.h>

#include "TestWithChz/QP_Moment_Control/Chz_QPMoment.h" // chz momcon
#include "TestWithChz/SDFAST/ChzSD_sdfastdefs.h"

// tests
// #define __TEST_COM
// #define __TEST_DCOM
#define __TEST_MOM // prob
// #define __TEST_DMOM // prob
// #define __TEST_ANK
// #define __TEST_DANK // prob
// #define __TEST_MATA // prob
// #define __TEST_MATDA // prob
// #define __TEST_JACO
// #define __TEST_DJACO 
// #define __TEST_DISP

_D_USING_SDT // dcc
using namespace Chz; // chz
using namespace ChzSD; // chz

tp_stSDMech stptRobotMech = {
//		      mass     inerx   inery   inerz    bodytojoint           inbtojoint
/*midbody*/	{ 15.733,  0.1760, 0.1149, 0.1099,  0.000, 0.000, 0.000,  0.000, 0.000, 0.000 }, 
/*uppbody*/	{ 15.401,  0.4813, 0.1584, 0.4315,  0.000, 0.000,-0.167,  0.008, 0.000, 0.150 }, // 12.297 + 3.104
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

tp_stSDState stptRobotStateOut;
double  // initial joints position
        dQInit[__DoFNum] = {    10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
                                0.0, 0.0, 0.0, 
                                0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                0.0, 0.0, 0.0, 0.0, 0.0, 0.0    },
        // input joints position
        dQIn[__DoFNum]   = {    10.0, 0.4, 0.3, 0.2, 0.3, 0.2, 
                                0.2, 0.2, 0.2, 
                                0.1, 0.12, -0.15, 0.11, 0.2, 0.2,
                                0.2, 0.11, -0.13, 0.2, 0.1, 0.3    },
        // input joint speed
        dUIn[__DoFNum] = { 0.0 };
void main() {
    double dControlT = 0.004;
    for(int i = 0; i < __DoFNum; i++) dUIn[i] = (dQIn[i] - dQInit[i]) / dControlT;
    // dcc calcuprog
    c_SDCalcu cSDCalcu7p2(&stptRobotMech, &stptRobotStateOut, dControlT);
    #define _SD7p2 cSDCalcu7p2
    _SD7p2.fnbInitState(dQInit); // init state
    _SD7p2.fnbSetState(dQIn, dUIn); // set state
    _SD7p2.fnbUpdateFK(); // update state
    double dSpc[6] = { 0.0 }, ddSpc[6] = { 0.0 }, dJaco[6][__DoFNum] = { 0.0 },  ddJaco[6][__DoFNum] = { 0.0 }, dPosTemp[3] = { 0.01, 0.02, 0.03 };
    _SD7p2.fnbGetPointState(lfoot, dPosTemp, dSpc, ddSpc, dJaco, ddJaco);

    // chz calcuprog
    Eigen::Vectornd qin, q, dq;
    QMC1.ifinit = 1;
    qin <<  10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
            0.0, 0.0, 0.0, 
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0;
    dq <<   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
            0.0, 0.0, 0.0, 
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0;
    QMC1.Setq(qin, dq);
    QMC1.Update();
    q <<    10.0, 0.4, 0.3, 0.2, 0.3, 0.2, 
            0.2, 0.2, 0.2, 
            0.1, 0.12, -0.15, 0.11, 0.2, 0.2,
            0.2, 0.11, -0.13, 0.2, 0.1, 0.3;
    dq = (q - qin) / dControlT;
    Eigen::Vector3d cCoM, dCoM;
    Eigen::Vector6d cMom, dMom;
    Eigen::Vector12d cAnk, dAnk;
    QMC1.SetPeriod(dControlT);
    QMC1.Setq(q, dq);
    QMC1.Update();
	QMC1.OutputCoM(cCoM, dCoM);
	QMC1.OutputMom(cMom, dMom);
    QMC1.OutputAnk(cAnk, dAnk);
    double dJacoChz[6][__DoFNum] = { 0.0 }, ddJacoChz[6][__DoFNum] = { 0.0 };;
    sdjacobian(6, dPosTemp, dJacoChz);
    sddjacobian(dQIn, dUIn, 6, dPosTemp, ddJacoChz);
    

    // plot 
    // _STD cout << "dMatdA from dcc:" << _STD endl;
    // for(int i = 0; i < 6; i++) {
    //     for(int j = 0; j < __DoFNum; j++) {
    //         printf("%lf, ", stptRobotStateOut.dMatdA[i][j]);
    //     }
    //     printf("\n");
    // }

#ifdef __TEST_COM
    _STD cout << "===================== dCoM: ======================" << _STD endl;
    printf("from dcc: \t");
    for(int i = 0; i < 3; i++) printf("%lf, ", stptRobotStateOut.dCoM[i]);
    printf("\n");
    printf("from chz: \t");
    for(int i = 0; i < 3; i++) printf("%lf, ", cCoM(i));
    printf("\n");
    _STD cout << "==================================================" << _STD endl;
#endif

#ifdef __TEST_DCOM
    _STD cout << "===================== ddCoM: ======================" << _STD endl;
    printf("from dcc: \t");
    for(int i = 0; i < 3; i++) printf("%lf, ", stptRobotStateOut.ddCoM[i]);
    printf("\n");
    printf("from chz: \t");
    for(int i = 0; i < 3; i++) printf("%lf, ", dCoM(i));
    printf("\n");
    _STD cout << "==================================================" << _STD endl;
#endif

#ifdef __TEST_MOM
    _STD cout << "===================== dMom: ======================" << _STD endl;
    printf("from dcc: \t");
    for(int i = 0; i < 6; i++) printf("%lf, ", stptRobotStateOut.dMom[i]);
    printf("\n");
    printf("from chz: \t");
    for(int i = 0; i < 6; i++) printf("%lf, ", cMom(i));
    printf("\n");
    _STD cout << "==================================================" << _STD endl;
#endif

#ifdef __TEST_DMOM
    _STD cout << "===================== ddMom: ======================" << _STD endl;
    printf("from dcc: \t");
    for(int i = 0; i < 6; i++) printf("%lf, ", stptRobotStateOut.ddMom[i]);
    printf("\n");
    printf("from chz: \t");
    for(int i = 0; i < 6; i++) printf("%lf, ", dMom(i));
    printf("\n");
    _STD cout << "==================================================" << _STD endl;
#endif

#ifdef __TEST_ANK
    _STD cout << "===================== dAnk: ======================" << _STD endl;
    printf("from dcc: \t");
    for(int i = 0; i < 3; i++) printf("%lf, ", stptRobotStateOut.dAnk[0][i]);
    for(int i = 0; i < 3; i++) printf("%lf, ", stptRobotStateOut.dAnk[1][i]);
    printf("\n");
    printf("from chz: \t");
    for(int i = 0; i < 3; i++) printf("%lf, ", cAnk(i));
    for(int i = 0; i < 3; i++) printf("%lf, ", cAnk(i + 6));
    printf("\n");
    _STD cout << "==================================================" << _STD endl;
#endif

#ifdef __TEST_DANK
    _STD cout << "===================== ddAnk: ======================" << _STD endl;
    printf("from dcc: \t");
    for(int i = 0; i < 3; i++) printf("%lf, ", stptRobotStateOut.ddAnk[0][i]);
    for(int i = 0; i < 3; i++) printf("%lf, ", stptRobotStateOut.ddAnk[1][i]);
    printf("\n");
    printf("from chz: \t");
    for(int i = 0; i < 3; i++) printf("%lf, ", dAnk(i));
    for(int i = 0; i < 3; i++) printf("%lf, ", dAnk(i + 6));
    printf("\n");
    _STD cout << "==================================================" << _STD endl;
#endif

#ifdef __TEST_MATA
    _STD cout << "===================== dMatA: ======================" << _STD endl;
    printf("from dcc: \n");
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < __DoFNum; j++) {
            printf("%lf, ", stptRobotStateOut.dMatA[i][j]);
        }
        printf("\n");
    }
    printf("from chz: \n");
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < __DoFNum; j++) {
            printf("%lf, ", QMC1.H(i, j));
        }
        printf("\n");
    }
    double dErrMatA = 0.0;
    for(int i = 0; i < 6; i++) for(int j = 0; j < __DoFNum; j++) dErrMatA += (stptRobotStateOut.dMatA[i][j] - QMC1.H(i, j));
    printf("MatA Err: \n %lf\n", dErrMatA);
    _STD cout << "==================================================" << _STD endl;
#endif

#ifdef __TEST_MATDA
    _STD cout << "===================== dMatdA: ======================" << _STD endl;
    printf("from dcc: \n");
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < __DoFNum; j++) {
            printf("%lf, ", stptRobotStateOut.dMatdA[i][j]);
        }
        printf("\n");
    }
    printf("from chz: \n");
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < __DoFNum; j++) {
            printf("%lf, ", QMC1.dH(i, j));
        }
        printf("\n");
    }
    double dErrMatdA = 0.0;
    for(int i = 0; i < 6; i++) for(int j = 0; j < __DoFNum; j++) dErrMatdA += (stptRobotStateOut.dMatdA[i][j] - QMC1.dH(i, j));
    printf("MatdA Err: \n %lf\n", dErrMatdA);
    _STD cout << "==================================================" << _STD endl;
#endif

#ifdef __TEST_JACO
    _STD cout << "===================== dJaco: ======================" << _STD endl;
    printf("from dcc: \n");
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < __DoFNum; j++) {
            printf("%lf, ", dJaco[i][j]);
        }
        printf("\n");
    }
    printf("from chz: \n");
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < __DoFNum; j++) {
            printf("%lf, ", dJacoChz[i][j]);
        }
        printf("\n");
    }
    double dErrJaco = 0.0;
    for(int i = 0; i < 6; i++) for(int j = 0; j < __DoFNum; j++) dErrJaco += (dJaco[i][j] - dJacoChz[i][j]);
    printf("dJaco Err: \n %lf\n", dErrJaco);
    _STD cout << "==================================================" << _STD endl;
#endif

#ifdef __TEST_DJACO
    _STD cout << "===================== ddJaco: ======================" << _STD endl;
    printf("from dcc: \n");
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < __DoFNum; j++) {
            printf("%lf, ", ddJaco[i][j]);
        }
        printf("\n");
    }
    printf("from chz: \n");
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < __DoFNum; j++) {
            printf("%lf, ", ddJacoChz[i][j]);
        }
        printf("\n");
    }
    double dErrdJaco = 0.0;
    for(int i = 0; i < 6; i++) for(int j = 0; j < __DoFNum; j++) dErrdJaco += (ddJaco[i][j] - ddJacoChz[i][j]);
    printf("ddJaco Err: \n %lf\n", dErrdJaco);
    _STD cout << "==================================================" << _STD endl;
#endif

#ifdef __TEST_DISP
    _SD7p2.fnbDisp(Q);
    _SD7p2.fnbDisp(CoM);
    _SD7p2.fnbDisp(Mom);
    _SD7p2.fnbDisp(A);
    _SD7p2.fnbDisp(Ank);
    _SD7p2.fnbDisp(Jaco);
#endif
}