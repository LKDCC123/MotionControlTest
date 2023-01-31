// test the SDFast functions
// 20221223 Dcc <3120195094@bit.edu.cn>
#include <DSDFastTools.h> // dcc sdteol
#include <iostream>
#include <stdio.h>

#include "TestWithChz/QP_Moment_Control/Chz_QPMoment.h" // chz momcon

// tests
// #define __TEST_COM
// #define __TEST_DCOM
// #define __TEST_MOM
// #define __TEST_DMOM
// #define __TEST_ANK
// #define __TEST_MATA
#define __TEST_MATDA


_D_USING_SDT // dcc
using namespace Chz; // chz

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
        // input joints position
        dUIn[__DoFNum]   = {    0.4, 0.3, 0.2, 0.1, 0.1, 0.1, 
                                0.2, 0.2, 0.2, 
                                0.2, 0.2, 0.1, 0.1, 0.1, 0.1,
                                0.1, 0.1, 0.1, 0.2, 0.2, 0.1    };   

void main() {
    double dControlT = 0.004;
    // dcc calcuprog
    c_SDCalcu cSDCalcu7p2(&stptRobotMech, &stptRobotStateOut, dControlT);
    cSDCalcu7p2.fnbInitState(dQInit); // init state
    cSDCalcu7p2.fnbSetState(dQIn, dUIn); // set state
    cSDCalcu7p2.fnbUpdateFK(); // update state

    // chz calcuprog
    Eigen::Vectornd q, dq;
    QMC1.ifinit = 1;
    q <<    10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
            0.0, 0.0, 0.0, 
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0;
    dq <<   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
            0.0, 0.0, 0.0, 
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0;
    QMC1.Setq(q, dq);
    QMC1.Update();
    q <<    10.0, 0.4, 0.3, 0.2, 0.3, 0.2, 
            0.2, 0.2, 0.2, 
            0.1, 0.12, -0.15, 0.11, 0.2, 0.2,
            0.2, 0.11, -0.13, 0.2, 0.1, 0.3;
    dq <<   0.4, 0.3, 0.2, 0.1, 0.1, 0.1, 
            0.2, 0.2, 0.2, 
            0.2, 0.2, 0.1, 0.1, 0.1, 0.1,
            0.1, 0.1, 0.1, 0.2, 0.2, 0.1;
    Eigen::Vector3d CoM, dCoM;
    Eigen::Vector6d Mom, dMom;
    Eigen::Vector12d Ank, dAnk;
    QMC1.SetPeriod(dControlT);
    QMC1.Setq(q, dq);
    QMC1.Update();
	QMC1.OutputCoM(CoM, dCoM);
	QMC1.OutputMom(Mom, dMom);
    QMC1.OutputAnk(Ank, dAnk);

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
    for(int i = 0; i < 3; i++) printf("%lf, ", CoM(i));
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
    for(int i = 0; i < 6; i++) printf("%lf, ", Mom(i));
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
    for(int i = 0; i < 3; i++) printf("%lf, ", Ank(i));
    for(int i = 0; i < 3; i++) printf("%lf, ", Ank(i + 6));
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

}