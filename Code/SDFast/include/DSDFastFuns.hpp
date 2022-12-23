// DSDFastFuns.hpp
// 20221223 Dcc <3120195094@bit.edu.cn>

#pragma once
#ifndef DSDFASTFUNS_HPP
#define DSDFASTFUNS_HPP
#include "../../../SDK/SDFast_SDK/SDFastDefs.h"

_D_SDFAST_BEGIN

#define __BodyNum 10
#define __DoFNum 21
#define __MechParasNum 10
typedef struct{ // mass, iner_x, iner_y, iner_z, bodytojoint_x, bodytojoint_y, bodytojoint_z, inbtojoint_x, inbtojoint_y, inbtojoint_z           
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
    int nBodNum = __BodyNum;
    int nDoFNum = __DoFNum;
}tp_stRobotMech;

typedef struct{
    double dQ[__DoFNum]; // q of the robot
    double dU[__DoFNum]; // dq of the robot
    double dT[__DoFNum]; // torque of the robot
    double dCoM[3];      // com of the robot
    double dMom[6];      // linear and angular momentum of the robot responding to the ground
    double dIner[3][3];  // total inertia of the robot 
    double dEng;         // total kinematic energy of the robot
    double dMass;        // total mass of the robot
    double dMatA[6][__DoFNum]; // centroidal kinematics metrix
    double dMatdA[6][__DoFNum]; // rate of centroidal kinematics metrix
}tp_stRobotState;

class c_SDCalcu {
public:
    inline c_SDCalcu(tp_stRobotMech * stptRobotMechIn, tp_stRobotState * stptRobotStateOut) {
        this->fnbResetMech(stptRobotMechIn);
        stptRobotStateOut = this->fnstSetStateIO();
    }
    inline ~c_SDCalcu() {

    }
    inline bool fnbResetMech(tp_stRobotMech * stptRobotMechIn) { // reset the mechanism parameters of the robot
        this->m_stptRobotMech = stptRobotMechIn;
        this->fnbSetMechParas();
        return true;
    }
    inline bool fnbInitState(double * dptQIn, double * dptUIn) {
        this->fnbSetState(dptQIn, dptUIn);
        this->fnbUpdateFK();
    }
    inline bool fnbSetState(double * dptQIn, double * dptUIn) { // set the state of the robot
        for(int i = 0; i < this->m_stptRobotMech->nDoFNum - 1; i++) {
            this->m_stptRobotState->dQ[i] = dptQIn[i], this->m_stptRobotState->dU[i] = dptUIn[i];
        }
        sdstate(0, this->m_stptRobotState->dQ, this->m_stptRobotState->dU);
        return true;
    }
    inline bool fnbUpdateCoM() { // update the [ mass & com & inertia ] of the robot (use after fnbSetState)
        sdsys(&(this->m_stptRobotState->dMass), this->m_stptRobotState->dCoM, this->m_stptRobotState->dIner);
        return true;
    }
    inline bool fnbUpdateMom() { // update the [ momentum & energy ] of the robot (use after fnbSetState)
        sdmom(this->m_stptRobotState->dMom, this->m_stptRobotState->dMom + 3, &(this->m_stptRobotState->dEng));
        return true;
    }
    inline bool fnbUpdateMatA() {
        double dDeltaU = 1e-5;
        double dUTemp[__DoFNum], dMomTemp[6], dEngTemp;
        for(int i = 0; i < this->m_stptRobotMech->nDoFNum - 1; i++) dUTemp[i] = this->m_stptRobotState->dU[i];
        for(int i = 0; i < this->m_stptRobotMech->nDoFNum - 1; i++) { // obtain A by columns
            dUTemp[i] = this->m_stptRobotState->dU[i] + dDeltaU; // numerical calculate jacobian: +deltaU
            sdstate(0, this->m_stptRobotState->dQ, dUTemp);
            sdmom(dMomTemp, dMomTemp + 3, &dEngTemp);
            for(int j = 0; j < 6; j++) this->m_stptRobotState->dMatA[j][i] = dMomTemp[j]; // fill A in column i by rows: +H
            dUTemp[i] = this->m_stptRobotState->dU[i] - dDeltaU; // numerical calculate jacobian: -deltaU
            sdstate(0, this->m_stptRobotState->dQ, dUTemp);
            sdmom(dMomTemp, dMomTemp + 3, &dEngTemp);
            for(int j = 0; j < 6; j++) this->m_stptRobotState->dMatA[j][i] = 0.5 * (this->m_stptRobotState->dMatA[j][i] - dMomTemp[j]) / dDeltaU; // fill A in column i by rows: (+H -H) / (2 * deltaU)
        }
        sdstate(0, this->m_stptRobotState->dQ, this->m_stptRobotState->dU); // return the sdfast to the current state
        return true; 
    }
    inline bool fnbUpdateFK() {
        this->fnbUpdateCoM();
        this->fnbUpdateMom();
        this->fnbUpdateMatA();
        return true;
    }
private:
    double dMatAOld[6][__DoFNum]; // dcchere: add stateOld, and the update of stateOld
    tp_stRobotMech * m_stptRobotMech;
    tp_stRobotState * m_stptRobotState;
    inline bool fnbSetMechParas() {
        for(int i = 0; i < this->m_stptRobotMech->nBodNum - 1; i++) {
            sdmass(i, *((double *)m_stptRobotMech + i * __MechParasNum + 0)); // reset mass
            double dInerTemp[3][3] = {
                { *((double *)m_stptRobotMech + i * __MechParasNum + 1), 0.0, 0.0 }, 
                { 0.0, *((double *)m_stptRobotMech + i * __MechParasNum + 2), 0.0 },
                { 0.0, 0.0, *((double *)m_stptRobotMech + i * __MechParasNum + 3) }
            };
            sdiner(i, dInerTemp); // reset inertia
            sdbtj(i, (double *)m_stptRobotMech + i * __MechParasNum + 4); // reset bodytojoint
            sditj(i, (double *)m_stptRobotMech + i * __MechParasNum + 4); // reset inbtojoint
        }
        // notation: sdgrav() and sdpin() are required to be set in SDRobot.sd file
		sdinit();
        return true;
    }
    inline tp_stRobotState * fnstSetStateIO() {
        return(this->m_stptRobotState);
    }

};

_D_SDFAST_END

#endif
