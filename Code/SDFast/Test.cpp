// test the SDFast functions
// 20221223 Dcc <3120195094@bit.edu.cn>
#include <DSDFastTools.h>
#include <iostream>
#include <stdio.h>

_D_USING_SDT

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
    c_SDCalcu cSDCalcu7p2(&stptRobotMech, &stptRobotStateOut, 0.004);
    cSDCalcu7p2.fnbInitState(dQInit); // init state
    cSDCalcu7p2.fnbSetState(dQIn, dUIn); // set state
    cSDCalcu7p2.fnbUpdateFK(); // update state

    _STD cout << "dMatA from dcc:" << _STD endl;
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < __DoFNum; j++) {
            printf("%lf, ", stptRobotStateOut.dMatA[i][j]);
        }
        printf("\n");
    }

    _STD cout << "dMatdA from dcc:" << _STD endl;
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < __DoFNum; j++) {
            printf("%lf, ", stptRobotStateOut.dMatdA[i][j]);
        }
        printf("\n");
    }

    _STD cout << "dCoM from dcc:" << _STD endl;
    for(int i = 0; i < 6; i++) {
        printf("%lf, ", stptRobotStateOut.dCoM[i]);
    }

    _STD cout << "dMom from dcc:" << _STD endl;
    for(int i = 0; i < 6; i++) {
        printf("%lf, ", stptRobotStateOut.dMom[i]);
    }
    


    
}