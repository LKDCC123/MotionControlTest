// DSDFastFuns.hpp
// 20221223 Dcc <3120195094@bit.edu.cn>

#pragma once
#ifndef DSDFASTFUNS_H
#define DSDFASTFUNS_H
#include <SDFastDefs.h>

_D_SDFAST_BEGIN

typedef struct { // mass, iner_x, iner_y, iner_z, bodytojoint_x, bodytojoint_y, bodytojoint_z, inbtojoint_x, inbtojoint_y, inbtojoint_z           
    double midbody[__MechParasNum];
    double uppbody[__MechParasNum];
    double larm[__MechParasNum];
    double rarm[__MechParasNum];
    double lthigh[__MechParasNum];
    double lshank[__MechParasNum];
    double lfoot[__MechParasNum];
    double rthigh[__MechParasNum];
    double rshank[__MechParasNum];
    double rfoot[__MechParasNum];
    int nBodNum;
    int nDoFNum;
}tp_stSDMech;

// state seq: trunk [z, y, x, rz, ry, rx], waist yaw, L arm, R arm, L leg [1-6], R leg [1-6]
typedef struct { // input [ dQ & dU ], then update the others for kinematics & dynamics
    double dQ[__DoFNum]; // q of the robot
    double dU[__DoFNum]; // dq of the robot
    double dCoM[3];      // com of the robot
    double ddCoM[3];     // rate of com
    double dMom[6];      // linear and angular momentum of the robot responding to the ground
    double ddMom[6];     // rate of momentum
    double dIner[3][3];  // total inertia of the robot 
    double dEng;         // total kinematic energy of the robot
    double dMass;        // total mass of the robot
    double dMatA[6][__DoFNum]; // centroidal kinematics metrix
    double dMatdA[6][__DoFNum]; // rate of centroidal kinematics metrix
    double dAnk[2][6]; // ankle position & rotation: [L, R][pos3, rot3]
    double ddAnk[2][6]; // ankle position & rotation rate: [L, R][pos3, rot3]
    double dJacoFt[2][6][__DoFNum]; // foot jacobian: [L, R][spacevect][DoF]
    double ddJacoFt[2][6][__DoFNum]; // foot jacobian derivative: [L, R][spacevect][DoF]
}tp_stSDState; 

enum enState { // state name
    Q, CoM, Mom, A, Ank, Jaco
};

class c_SDCalcu {
public:
    inline c_SDCalcu(tp_stSDMech * stptRobotMechIn, tp_stSDState * stptRobotStateOut, double dTimeIn) {
        this->fnbResetMech(stptRobotMechIn);
        this->dTime = dTimeIn;
        this->m_stptRobotState = stptRobotStateOut;
    }
    inline ~c_SDCalcu() {

    }
    inline bool fnbResetMech(tp_stSDMech * stptRobotMechIn) { // reset the mechanism parameters of the robot
        this->m_stptRobotMech = stptRobotMechIn;
        this->fnbSetMechParas();
        return true;
    }
    inline bool fnbInitState(double dptQInitIn[__DoFNum]) {
        double dptUInitIn[__DoFNum] = { 0.0 };
        this->fnbSetState(dptQInitIn, dptUInitIn);
        for(int i = 0; i < 3; i++) { // initiate the com, momentum, A
            this->m_stptRobotState->dCoM[i] = this->m_stptRobotState->dMom[i] = this->m_stptRobotState->dMom[i + 3] = 0.0;
            for(int j = 0; j < this->m_stptRobotMech->nDoFNum; j++) this->dMatAOld[i][j] = this->dMatAOld[i + 3][j] = this->m_stptRobotState->dMatA[i][j] = this->m_stptRobotState->dMatA[i + 3][j] = 0.0;
        }
        this->fnbUpdateFK();
        for(int i = 0; i < 3; i++) { // initiate the rate of com, momentum, A
            this->m_stptRobotState->ddCoM[i] = this->m_stptRobotState->ddMom[i] = this->m_stptRobotState->ddMom[i + 3] = 0.0;
            for(int j = 0; j < this->m_stptRobotMech->nDoFNum; j++) this->m_stptRobotState->dMatdA[i][j] = this->m_stptRobotState->dMatdA[i + 3][j] = 0.0;
        }
        return true;
    }
    inline bool fnbSetState(double dptQIn[__DoFNum], double dptUIn[__DoFNum]) { // set the state of the robot
        for(int i = 0; i < this->m_stptRobotMech->nDoFNum; i++) {
            this->m_stptRobotState->dQ[i] = dptQIn[i], this->m_stptRobotState->dU[i] = dptUIn[i];
        }
        sdstate(0, this->m_stptRobotState->dQ, this->m_stptRobotState->dU);
        return true;
    }
    inline bool fnbUpdateFK() { // obtain: major -> [ com, momentum, A, ank ] and their rate; minor -> [ inertia, energy, mass ]
        this->fnbUpdateCoM();
        this->fnbUpdateMom();
        this->fnbUpdateMatA();
        this->fnbUpdateAnk();
        return true;
    }
    inline bool fnbGetPointJacobian(int nBody, double dptPosIn[3], double dptJacobian[6][__DoFNum]) {
        static double dLinTemp[3] = { 0.0 }, dLinW[3] = { 0.0 }, dRotTemp[3] = { 0.0 }, dRotW[3] = { 0.0 };
        for(int i = 0; i < this->m_stptRobotMech->nDoFNum; i++) {
            sdrel2cart(i, nBody, dptPosIn, dLinTemp, dRotTemp); // obatin the change
            sdtrans(nBody, dLinTemp, -1, dLinW); // transform the linear change
            sdtrans(nBody, dRotTemp, -1, dRotW); // transform the rotational change
            for(int j = 0; j < 3; j++) dptJacobian[j][i] = dLinW[j], dptJacobian[j + 3][i] = dRotW[j];
        }
        return true;
    }
    inline bool fnvGetPointdJacobian(int nBody, double dptPosIn[3], double dptdJacobian[6][__DoFNum]) { // calculate the dJ by using numerical differentiation 
        double dDeltaQ = 1e-5;
        static double dQ[__DoFNum] = { 0.0 }, dJacoTemp[__DoFNum][2][6][__DoFNum] = { 0.0 };
        for(int i = 0; i < this->m_stptRobotMech->nDoFNum; i++) dQ[i] = this->m_stptRobotState->dQ[i];
        for(int i = 0; i < this->m_stptRobotMech->nDoFNum; i++) {
            dQ[i] = this->m_stptRobotState->dQ[i] + dDeltaQ;
            sdstate(0, dQ, this->m_stptRobotState->dU);
            this->fnbGetPointJacobian(nBody, dptPosIn, dJacoTemp[i][0]); // q+
            dQ[i] = this->m_stptRobotState->dQ[i] - dDeltaQ;
            sdstate(0, dQ, this->m_stptRobotState->dU);
            this->fnbGetPointJacobian(nBody, dptPosIn, dJacoTemp[i][1]); // q-
            dQ[i] = this->m_stptRobotState->dQ[i];
        }
        sdstate(0, this->m_stptRobotState->dQ, this->m_stptRobotState->dU); // reset the sdfast to the current state
        for(int i = 0; i < this->m_stptRobotMech->nDoFNum; i++) for(int j = 0; j < 6; j++) {
            dptdJacobian[j][i] = 0.0;
            for(int k = 0; k < this->m_stptRobotMech->nDoFNum; k++) dptdJacobian[j][i] += (dJacoTemp[k][0][j][i] - dJacoTemp[k][1][j][i]) / 2.0 / dDeltaQ * this->m_stptRobotState->dU[k];
        }
        return true;
    }
    inline bool fnbGetPointPosRot(int nBody, double dptPosIn[3], double dptSpcOut[6]) {
        sdpos(nBody, dptPosIn, dptSpcOut); // input the local position and obtain the world postion 
        double dTRotTemp[3][3] = { 0.0 };
        sdorient(nBody, dTRotTemp); // obtain the world rotation
        *(dptSpcOut + 3) = atan2(dTRotTemp[2][1], dTRotTemp[2][2]);
        *(dptSpcOut + 4) = atan2(-dTRotTemp[2][0], sqrt(dTRotTemp[2][1] * dTRotTemp[2][1] + dTRotTemp[2][2] * dTRotTemp[2][2]));
        *(dptSpcOut + 5) = atan2(dTRotTemp[1][0], dTRotTemp[0][0]);
        return true;
    }
    inline bool fnbGetPointdPosRot(int nBody, double dptPosIn[3], double dptdSpcOut[6]) {
        double dDeltaQ = 1e-5;
        static double dQ[__DoFNum] = { 0.0 }, dAnkTemp[__DoFNum][2][6] = { 0.0 };
        for(int i = 0; i < this->m_stptRobotMech->nDoFNum; i++) dQ[i] = this->m_stptRobotState->dQ[i];
        for(int i = 0; i < this->m_stptRobotMech->nDoFNum; i++) {
            dQ[i] = this->m_stptRobotState->dQ[i] + dDeltaQ;
            sdstate(0, dQ, this->m_stptRobotState->dU);
            this->fnbGetPointPosRot(nBody, dptPosIn, dAnkTemp[i][0]); // q+
            dQ[i] = this->m_stptRobotState->dQ[i] - dDeltaQ;
            sdstate(0, dQ, this->m_stptRobotState->dU);
            this->fnbGetPointPosRot(nBody, dptPosIn, dAnkTemp[i][1]); // q-
            dQ[i] = this->m_stptRobotState->dQ[i];
        }
        sdstate(0, this->m_stptRobotState->dQ, this->m_stptRobotState->dU); // reset the sdfast to the current state
        for(int i = 0; i < 6; i++) {
            dptdSpcOut[i] = 0.0;
            for(int j = 0; j <= this->m_stptRobotMech->nDoFNum; j++) dptdSpcOut[i] += (dAnkTemp[j][0][i] - dAnkTemp[j][1][i]) / 2.0 / dDeltaQ * this->m_stptRobotState->dU[j];
        }
        return true;
    }
    inline bool fnbGetPointState(int nBody, double dptPosIn[3], double dptSpcOut[6], double dptdSpcOut[6], double dptJacoOut[6][__DoFNum], double dptdJacoOut[6][__DoFNum]) {
        fnbGetPointPosRot(nBody, dptPosIn, dptSpcOut);
        fnbGetPointdPosRot(nBody, dptPosIn, dptdSpcOut);
        fnbGetPointJacobian(nBody, dptPosIn, dptJacoOut);
        fnvGetPointdJacobian(nBody, dptPosIn, dptdJacoOut);
        return true;
    }
    // Q, U, CoM, dCoM, Mom, dMom, A, dA, Ank, dAnk, Jaco, dJaco
    inline bool fnbDisp(int nDispName) { 
        switch(nDispName) {
        case Q: 
            _STD cout << "==================================== Q ====================================:" << _STD endl;
            for(int i = 0; i < this->m_stptRobotMech->nDoFNum; i++) printf("%lf, ", this->m_stptRobotState->dQ[i]);
            printf("\n");
            _STD cout << "==================================== U ====================================:" << _STD endl;
            for(int i = 0; i < this->m_stptRobotMech->nDoFNum; i++) printf("%lf, ", this->m_stptRobotState->dU[i]);
            printf("\n");
            break;
        case CoM:
            _STD cout << "==================================== CoM ====================================:" << _STD endl;
            for(int i = 0; i < 3; i++) printf("%lf, ", this->m_stptRobotState->dCoM[i]);
            printf("\n");
            _STD cout << "==================================== dCoM ====================================:" << _STD endl;
            for(int i = 0; i < 3; i++) printf("%lf, ", this->m_stptRobotState->ddCoM[i]);
            printf("\n");
            break;
        case Mom:
            _STD cout << "==================================== Mom ====================================:" << _STD endl;
            for(int i = 0; i < 6; i++) printf("%lf, ", this->m_stptRobotState->dMom[i]);
            printf("\n");
            _STD cout << "==================================== dMom ====================================:" << _STD endl;
            for(int i = 0; i < 6; i++) printf("%lf, ", this->m_stptRobotState->ddMom[i]);
            printf("\n");
            break;
        case A:
            _STD cout << "==================================== A ====================================:" << _STD endl;
            for(int i = 0; i < 6; i++) {
                for(int j = 0; j < this->m_stptRobotMech->nDoFNum; j++) printf("%lf, ", this->m_stptRobotState->dMatA[i][j]);
                printf("\n");
            }
            _STD cout << "==================================== dA ====================================:" << _STD endl;
            for(int i = 0; i < 6; i++) {
                for(int j = 0; j < this->m_stptRobotMech->nDoFNum; j++) printf("%lf, ", this->m_stptRobotState->dMatdA[i][j]);
                printf("\n");
            }
            break;
        case Ank:
            _STD cout << "==================================== Ank ====================================:" << _STD endl;
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 6; j++) printf("%lf, ", this->m_stptRobotState->dAnk[i][j]);
                printf("\n");
            }
            _STD cout << "==================================== dAnk ====================================:" << _STD endl;
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 6; j++) printf("%lf, ", this->m_stptRobotState->ddAnk[i][j]);
                printf("\n");
            }
            break;
        case Jaco:
            _STD cout << "==================================== Jaco ====================================:" << _STD endl;
            _STD cout << "left:" << _STD endl;
            for(int i = 0; i < 6; i++) {
                for(int j = 0; j < this->m_stptRobotMech->nDoFNum; j++) printf("%lf, ", this->m_stptRobotState->dJacoFt[0][i][j]);
                printf("\n");
            }
            _STD cout << "right:" << _STD endl;
            for(int i = 0; i < 6; i++) {
                for(int j = 0; j < this->m_stptRobotMech->nDoFNum; j++) printf("%lf, ", this->m_stptRobotState->dJacoFt[1][i][j]);
                printf("\n");
            }
            _STD cout << "==================================== dJaco ====================================:" << _STD endl;
            _STD cout << "left:" << _STD endl;
            for(int i = 0; i < 6; i++) {
                for(int j = 0; j < this->m_stptRobotMech->nDoFNum; j++) printf("%lf, ", this->m_stptRobotState->ddJacoFt[0][i][j]);
                printf("\n");
            }
            _STD cout << "right:" << _STD endl;
            for(int i = 0; i < 6; i++) {
                for(int j = 0; j < this->m_stptRobotMech->nDoFNum; j++) printf("%lf, ", this->m_stptRobotState->ddJacoFt[1][i][j]);
                printf("\n");
            }
            break;
        default:
            break;
        }
        return true;
    }
private:
    double dCoMOld[3], dMomOld[6], dMatAOld[6][__DoFNum], dTime;
    tp_stSDMech * m_stptRobotMech;
    tp_stSDState * m_stptRobotState;
    inline bool fnbSetMechParas() {
        for(int i = 0; i < this->m_stptRobotMech->nBodNum; i++) {
            sdmass(i, *((double *)m_stptRobotMech + i * __MechParasNum + 0)); // reset mass
            double dInerTemp[3][3] = {
                { *((double *)m_stptRobotMech + i * __MechParasNum + 1), 0.0, 0.0 }, 
                { 0.0, *((double *)m_stptRobotMech + i * __MechParasNum + 2), 0.0 },
                { 0.0, 0.0, *((double *)m_stptRobotMech + i * __MechParasNum + 3) }
            };
            sdiner(i, dInerTemp); // reset inertia
            sdbtj(i, (double *)m_stptRobotMech + i * __MechParasNum + 4); // reset bodytojoint
            sditj(i, (double *)m_stptRobotMech + i * __MechParasNum + 7); // reset inbtojoint
        }
        // notation: sdgrav() and sdpin() are required to be set in SDRobot.sd file
		sdinit();
        return true;
    }
    inline bool fnbUpdateCoM() { // update the [ mass & com & inertia ] of the robot (use after fnbSetState)
        sdsys(&(this->m_stptRobotState->dMass), this->m_stptRobotState->dCoM, this->m_stptRobotState->dIner);
        for (int i = 0; i < 3; i++) {
            this->m_stptRobotState->ddCoM[i] = (this->m_stptRobotState->dCoM[i] - this->dCoMOld[i]) / this->dTime; // calculate the rate of com
            this->dCoMOld[i] = this->m_stptRobotState->dCoM[i]; // update dCoMOld
        }
        return true;
    }
    inline bool fnbUpdateMom() { // update the [ momentum & energy ] of the robot (use after fnbSetState)
        sdmom(this->m_stptRobotState->dMom, this->m_stptRobotState->dMom + 3, &(this->m_stptRobotState->dEng));
        for (int i = 0; i < 6; i++) {
            this->m_stptRobotState->ddMom[i] = (this->m_stptRobotState->dMom[i] - this->dMomOld[i]) / this->dTime; // calculate the rate of momentum
            this->dMomOld[i] = this->m_stptRobotState->dMom[i]; // update dMomOld
        }
        return true;
    }
    inline bool fnbUpdateMatA() {
        double dDeltaU = 1e-5;
        double dUTemp[__DoFNum], dMomTemp[6], dEngTemp;
        for(int i = 0; i < this->m_stptRobotMech->nDoFNum; i++) dUTemp[i] = this->m_stptRobotState->dU[i];
        for(int i = 0; i < this->m_stptRobotMech->nDoFNum; i++) { // obtain A by columns
            dUTemp[i] = this->m_stptRobotState->dU[i] + dDeltaU; // numerical calculate jacobian: +deltaU -> H(+)
            sdstate(0, this->m_stptRobotState->dQ, dUTemp);
            sdmom(dMomTemp, dMomTemp + 3, &dEngTemp);
            for(int j = 0; j < 6; j++) this->m_stptRobotState->dMatA[j][i] = dMomTemp[j]; // fill A in column i by rows: H(+)
            dUTemp[i] = this->m_stptRobotState->dU[i] - dDeltaU; // numerical calculate jacobian: -deltaU -> H(-)
            sdstate(0, this->m_stptRobotState->dQ, dUTemp);
            sdmom(dMomTemp, dMomTemp + 3, &dEngTemp);
            for(int j = 0; j < 6; j++) {
                this->m_stptRobotState->dMatA[j][i] = 0.5 * (this->m_stptRobotState->dMatA[j][i] - dMomTemp[j]) / dDeltaU; // fill A in column i by rows: (H(+) - H(-)) / (2 * deltaU)
                this->m_stptRobotState->dMatdA[j][i] = (this->m_stptRobotState->dMatA[j][i] - this->dMatAOld[j][i]) / this->dTime; // calculate the rate of A
                this->dMatAOld[j][i] = this->m_stptRobotState->dMatA[j][i]; // update dMatAOld
            }
        }
        sdstate(0, this->m_stptRobotState->dQ, this->m_stptRobotState->dU); // return the sdfast to the current state
        return true; 
    }
    inline bool fnbUpdateAnk() { 
        double dPosAnkTemp[3] = { 0.0 }, dTRotTemp[3][3] = { 0.0 };
        dPosAnkTemp[2] = this->m_stptRobotMech->rfoot[6]; // find the position of the ankle
        this->fnbGetPointState(lfoot, dPosAnkTemp, this->m_stptRobotState->dAnk[0], this->m_stptRobotState->ddAnk[0], this->m_stptRobotState->dJacoFt[0], this->m_stptRobotState->ddJacoFt[0]);
        this->fnbGetPointState(rfoot, dPosAnkTemp, this->m_stptRobotState->dAnk[1], this->m_stptRobotState->ddAnk[1], this->m_stptRobotState->dJacoFt[1], this->m_stptRobotState->ddJacoFt[1]);
        return true;
    }
};

_D_SDFAST_END

#endif
