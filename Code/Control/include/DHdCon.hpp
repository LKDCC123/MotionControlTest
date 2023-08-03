// DHdCon.hpp
// 20230413 dcc <3120195094@bit.edu.cn>
// Honda posture control for position-controlled robot based on DCC_RunningHonda.c & DCC_RunningCon.c
#pragma once
#ifndef DHDCON_HPP
#define DHDCON_HPP
#include "ControlHeaders.h"

_D_CONTROL_BEGIN
_D_USING_BASE

#define __FzMin 50.0

/*  for data filter  *///=========================
// #define __Aver3Filter

/*    for varstiff   *///=========================
// #define __VarStiff
#define __TouchSoft
// #define __UntouchRe

/*  for mstab limit  *///=========================
// #define __Direct
#define __AnkPos

/*for alpha calculate*///=========================
#define __ZMPSplit
// #define __FzSplit

/*    for stepcon    *///=========================
// #define __Theta
// #define __Theta2
// #define __ThetaInt 
#define __CaptureP
// #define __CapturePInt

static double dPr[10]; // test
static double dConL[6], dConR[6], dCondL[6], dCondR[6], dConddL[6], dConddR[6]; // test
static int nKInStep; // test
static double dErr[2]; // test
static double dAlphaRe; // test

#ifdef __Aver3Filter
double3 dWeightT = { 0.05, 0.1, 0.95 }, dWeightF = { 0.05, 0.15, 0.85 }, dWeightM = { 0.15, 0.26, 0.62 };
c_Filter3Aver cPitL(dWeightT), cPitR(dWeightT), cRolL(dWeightT), cRolR(dWeightT), cZL(dWeightF), cZR(dWeightF), cMPit(dWeightM), cMRol(dWeightM);
double3 dWT = { 0.05, 0.1, 0.95 }, dWF = { 0.05, 0.1, 0.8 };
c_Filter3Aver cTPitL(dWT), cTPitR(dWT), cTRolL(dWT), cTRolR(dWT), cFzL(dWF), cFzR(dWF);
#endif

struct st_RobotConfig{ // init required
    double Tc; 
    double Mass;
    double UpperMass;
    double UpperIner;
    double Zc; // height of the nominal CoM
    double AnkWidth;
    double FootGeom[4]; // positive: forw, back, iner, outer
};

struct st_DHdConGains{ // init required
    double Vip;
    double UpperPos[3]; // [k_posture, kp, kd]
    double CalMStab[2]; // [kp, kd]
    double MdZMP[4]; // [kp_pos, kd_pos, kp_rot, kd_rot]
    double GRFC[9];
    double Compliance[2];
    double ArmSwi[2]; // [k_angluar, M_virtual]
    double StepCon[4]; // [k_adj, ts, te, thresh]
};

struct st_Filters{ // init required
    double TLagZMP;
    double TLagIMU;
    double TLagGro;
    double TLagFrc;
    double TLagTrq;
    double AmpTrq;
};

struct st_DHdConIO{ // init required
    // input
    double BasePG[6]; // pattern generated base position and posture [x, y, z, rx, ry, rz]
    double dBasePG[6]; // pattern generated base position and posture rate [x, y, z, rx, ry, rz]
    double LAnkPG_W[6]; // pattern generated left ankle position and posture in world frame [x, y, z, rx, ry, rz]
    double RAnkPG_W[6]; // pattern generated right ankle position and posture in world frame [x, y, z, rx, ry, rz]
    double LFTPG_B[6]; // left reference foot contact force and torque in base frame [fx, fy, fz, tx, ty, tz]
    double RFTPG_B[6]; // right reference foot contact force and torque in base frame [fx, fy, fz, tx, ty, tz]
    double IMUSen[2]; // sensed IMU data [rx, ry]
    double ZMPSen_B[2]; // sensed ZMP in base frame [x, y]
    double LFTSen_B[6]; // left sensed foot contact force and torque in base frame
    double RFTSen_B[6]; // right sensed foot contact force and torque in base frame
    double LegQ[12]; // leg joints angle [left 1~6, right 1~6] 
    double ArmQ[2]; // arm joints angle [left 1, right 1]
    double TStepSS; // current step span of single support
    int SupSignal; // support leg of current time circle
    int PressKey;
    // output
    double BaseCmd[6]; // commanded base position and posture [x, y, z, rx, ry, rz]
    double LAnkCmd_W[6]; // commanded left ankle position and posture in world frame [x, y, z, rx, ry, rz]
    double RAnkCmd_W[6]; // commanded right ankle position and posture in world frame [x, y, z, rx, ry, rz]
    double ArmQcmd[2]; // commanded arm joints angle [left 1, right 1]
    double DeltaL_B[2]; // commanded step location adjustment in base frame [x, y]
};

struct st_DHdConData{
    double Base[6]; // Base position and posture in world frame [x, y, z, rx, ry, rz]
    double dBase[6]; // Base position and posture rate in world frame [x, y, z, rx, ry, rz]
    double ddBase[6]; // Base position and posture acc in world frame [x, y, z, rx, ry, rz]
    struct {
        struct{
            double B[6]; // left ankle position and posture in base frame [x, y, z, rx, ry, rz]
            double W[6]; // left ankle position and posture in world frame [x, y, z, rx, ry, rz]
        }L;
        struct{
            double B[6]; // right ankle position and posture in base frame [x, y, z, rx, ry, rz]
            double W[6]; // right ankle position and posture in world frame [x, y, z, rx, ry, rz]
        }R;
    }Ank;
    struct {
        struct{
            double B[6]; // left ankle position and posture rate in base frame [x, y, z, rx, ry, rz]
            double W[6]; // left ankle position and posture rate in world frame [x, y, z, rx, ry, rz]
        }L;
        struct{
            double B[6]; // right ankle position and posture rate in base frame [x, y, z, rx, ry, rz]
            double W[6]; // right ankle position and posture rate in world frame [x, y, z, rx, ry, rz]
        }R;
    }dAnk;
    struct {
        struct{
            double B[6]; // left ankle position and posture acc in base frame [x, y, z, rx, ry, rz]
            double W[6]; // left ankle position and posture acc in world frame [x, y, z, rx, ry, rz]
        }L;
        struct{
            double B[6]; // right ankle position and posture acc in base frame [x, y, z, rx, ry, rz]
            double W[6]; // right ankle position and posture acc in world frame [x, y, z, rx, ry, rz]
        }R;
    }ddAnk;
    struct {
        struct{
            double B[6]; // left foot contact force and torque in base frame [fx, fy, fz, tx, ty, tz]
            double W[6]; // left foot contact force and torque in world frame [fx, fy, fz, tx, ty, tz]
        }L;
        struct{
            double B[6]; // right foot contact force and torque in base frame [fx, fy, fz, tx, ty, tz]
            double W[6]; // right foot contact force and torque in world frame [fx, fy, fz, tx, ty, tz]
        }R;
    }Fft;
    struct {
        double L[6]; // left leg joints angle
        double R[6]; // right leg joints angle
    }LegQ;
    struct {
        double L[6]; // left leg joints speed
        double R[6]; // right leg joints speed
    }LegdQ;
    struct {
        double L; // left arm joints speed
        double R; // right arm joints speed
    }ArmQ;
    double ZMP[2]; // ZMP in base frame [x, y]
    double DeltaL[2]; // step adjustment value in base frame [x, y]
};

class c_DHdCon {
public:
    inline c_DHdCon(st_DHdConIO * stConIO, st_RobotConfig * stRobConfig, st_DHdConGains * stDHdConGains, st_Filters * stFilters) {
        this->m_stIO = stConIO;
        this->m_stGains = stDHdConGains;
        this->m_stFilters = stFilters;
        this->m_stRobConfig = stRobConfig;
        this->m_nIfConOn = this->m_nIfInit = 0;
    }
    inline ~c_DHdCon() {

    }
    // init the control
    void Init(
        int nPosCon, 
        int nMdZMP,
        int nFftFB, 
        int nGRFC, 
        int nComp,
        int nArmSwi,
        int nStepCon) {
        this->SetCon(
            nPosCon, 
            nMdZMP, 
            nFftFB, 
            nGRFC, 
            nComp, 
            nArmSwi,
            nStepCon);
        this->Reset();
        #ifdef __Aver3Filter
        cPitL.Init(0.0), cPitR.Init(0.0), cRolL.Init(0.0), cRolR.Init(0.0), cZL.Init(0.0), cZR.Init(0.0), cMPit.Init(0.0), cMRol.Init(0.0);
        cTPitL.Init(0.0), cTPitR.Init(0.0), cTRolL.Init(0.0), cTRolR.Init(0.0), cFzL.Init(0.5 * this->m_stRobConfig->Mass * __Gravity), cFzR.Init(0.5 * this->m_stRobConfig->Mass * __Gravity);
        #endif
        this->m_nIfInit = 1;
    }
    // set control flag
    void SetCon(
        int nPosCon, 
        int nMdZMP, 
        int nFftFB, 
        int nGRFC, 
        int nComp, 
        int nArmSwi, 
        int nStepCon) {
        this->m_nPosCon = nPosCon;
        this->m_nMdZMP = nMdZMP;
        this->m_nFftFB = nFftFB;
        this->m_nGRFC = nGRFC;
        this->m_nComp = nComp;
        this->m_nArmSwi = nArmSwi;
        this->m_nStepCon = nStepCon;
    }
    // reset the control
    void Reset() {
        memset(&this->m_stPG, 0, sizeof(this->m_stPG));
        memset(&this->m_stRef, 0, sizeof(this->m_stRef));
        memset(&this->m_stSen, 0, sizeof(this->m_stSen));
        memset(&this->m_stErr, 0, sizeof(this->m_stErr));
        memset(&this->m_stCoV, 0, sizeof(this->m_stCoV));
        memset(&this->m_stCmd, 0, sizeof(this->m_stCmd));
        this->m_SupLegLast = DSup;
    }
    // return 1: control applied, 0: control banished, -1: didn't init yet
    int Loop() { 
        int nErrCode;
        this->fnbGetTra(); 
        this->fnbGetSen();
        if(this->m_nIfInit) {
            if(this->m_nIfConOn) {
                this->fnbGetConV();
                nErrCode = 1;
            }
            nErrCode = 0;
        }
        nErrCode = -1;
        this->fnbSendCmd();
        return nErrCode;
    }
    void Clear() {
        
    }
    inline void On() { this->m_nIfConOn = 1; } // turn on the control
    inline void Off() { this->m_nIfConOn = 0; } // turn off the control
    st_DHdConData GetPGData() { return this->m_stPG; }
    st_DHdConData GetRefData() { return this->m_stRef; }
    st_DHdConData GetSenData() { return this->m_stSen; }
    st_DHdConData GetErrData() { return this->m_stErr; }
    st_DHdConData GetCoVData() { return this->m_stCoV; }
    st_DHdConData GetCmdData() { return this->m_stCmd; }
    double *GetSupPolyData() { return this->m_dSubPoly_B; };
    double *GetMStabLimitData() { return this->m_dMStabLimit; };
    double *GetMStabData() { return this->m_dMStab; };
    double *GetMFeetData() { return this->m_dMFeet; };
    double *GetMdZMPData() { return this->m_dMMdZMP; };
    double *GetMPendData() { return this->m_dMPend; };
    double *GetMWheelData() { return this->m_dMWheel; };
private:
    st_DHdConData m_stPG, m_stRef, m_stSen, m_stErr, m_stCoV, m_stCmd;
    st_DHdConGains * m_stGains;
    st_Filters * m_stFilters;
    st_DHdConIO * m_stIO;
    st_RobotConfig * m_stRobConfig;
    int m_nPosCon, m_nMdZMP, m_nFftFB, m_nGRFC, m_nComp, m_nArmSwi, m_nStepCon; // singal control flag
    int m_nIfInit, m_nIfConOn; // init flag and total control flag
    int m_SupLegLast; // support leg of the last time circle, not the last step!!
    double m_dSubPoly_B[4]; // [-x, x, -y, y]
    double m_dMStabLimit[4]; // [-tx, tx, -ty, ty]
    double m_dMStab[6], m_dMFeet[6], m_dMMdZMP[6], m_dMPend[6], m_dMWheel[6];
    inline double fndIfLTD() { if(this->m_stSen.Fft.L.B[__z] > __FzMin) return 1.0; return 0.0; } // check if left foot touch down the ground
    inline double fndIfRTD() { if(this->m_stSen.Fft.R.B[__z] > __FzMin) return 1.0; return 0.0; } // check if right foot touch down the ground
    inline double fndIfTD() { if(this->m_stSen.Fft.L.B[__z] + this->m_stSen.Fft.R.B[__z] > __FzMin) return 1.0; return 0.0; } // check if the robot touch down the ground
    inline int fnnIfTD() { if(this->m_stSen.Fft.L.B[__z] + this->m_stSen.Fft.R.B[__z] > __FzMin) return 1; return 0; } // check if the robot touch down the ground
    inline int fnnIfLTD() { if(this->m_stSen.Fft.L.B[__z] > __FzMin) return 1; return 0; } // check if left foot touch down the ground
    inline int fnnIfRTD() { if(this->m_stSen.Fft.R.B[__z] > __FzMin) return 1; return 0; } // check if right foot touch down the ground
    inline double fnbEulerSign(int nIn) { // transpose the rotational to positional sign and vise versa
        switch (nIn) {
        case __x: // to _pt
            return 1.0;
        case __y: // to _rl
            return -1.0;
        case _rl: // to __y
            return -1.0;
        case _pt: // to __x
            return 1.0;
        default:
            return 1.0;
        }
    }
    // transpose the rotational to positional cite number and vise versa
    inline int fnnEulerNum(int nIn) { 
        if(nIn != __z && nIn <= _pt) return (__z + __z - nIn);
        else return nIn;
    }
    // upper body posture control of the robot to make the robot behave more like a LIPM
    bool fnbUpperPosCon(int nIfCon) { 
        double dLimit[6] = { -__D2R(15.0), __D2R(15.0), -100.0, 100.0, -50.0, 50.0 };
        auto &k_posture = this->m_stGains->UpperPos[0], &kp = this->m_stGains->UpperPos[1], &kd = this->m_stGains->UpperPos[2];
        auto &ref = this->m_stRef, &sen = this->m_stSen, &con = this->m_stCoV, &cmd = this->m_stCmd;;
        for(int i = _rl; i <= _pt; i++) {
            con.ddBase[i] = this->fndIfTD() * k_posture * (ref.Base[i] - sen.Base[i]) - kp * con.Base[i] - kd * con.dBase[i];
            fnvIntergAccLimit(&con.Base[i], &con.dBase[i], con.ddBase[i], dLimit, this->m_stRobConfig->Tc);
        }
        if(nIfCon) {
            for(int i = _rl; i <= _pt; i++) cmd.Base[i] += con.Base[i];
            return true;
        }
        return false;
    }
    // calculate the support polygon region
    bool fnbCalSupPolyPG() { 
        auto &cfg = this->m_stRobConfig;
        switch(this->m_stIO->SupSignal) {
        case DSup: // double leg support phase
            this->m_dSubPoly_B[0] = __MinOf((this->m_stCmd.Ank.L.B[__x] - cfg->FootGeom[1]), (this->m_stCmd.Ank.R.B[__x] - cfg->FootGeom[1]));
            this->m_dSubPoly_B[1] = __MaxOf((this->m_stCmd.Ank.L.B[__x] + cfg->FootGeom[0]), (this->m_stCmd.Ank.R.B[__x] + cfg->FootGeom[0]));
            this->m_dSubPoly_B[2] = this->m_stCmd.Ank.R.B[__y] - cfg->FootGeom[3];
            this->m_dSubPoly_B[3] = this->m_stCmd.Ank.L.B[__y] + cfg->FootGeom[3];
            break;
        case LSup: // left leg support phase
            this->m_dSubPoly_B[0] = this->m_stCmd.Ank.L.B[__x] - cfg->FootGeom[1];
            this->m_dSubPoly_B[1] = this->m_stCmd.Ank.L.B[__x] + cfg->FootGeom[0];
            this->m_dSubPoly_B[2] = this->m_stCmd.Ank.L.B[__y] - cfg->FootGeom[2];
            this->m_dSubPoly_B[3] = this->m_stCmd.Ank.L.B[__y] + cfg->FootGeom[3];
            break;
        case RSup: // right leg support phase
            this->m_dSubPoly_B[0] = this->m_stCmd.Ank.R.B[__x] - cfg->FootGeom[1];
            this->m_dSubPoly_B[1] = this->m_stCmd.Ank.R.B[__x] + cfg->FootGeom[0];
            this->m_dSubPoly_B[2] = this->m_stCmd.Ank.R.B[__y] - cfg->FootGeom[3];
            this->m_dSubPoly_B[3] = this->m_stCmd.Ank.R.B[__y] + cfg->FootGeom[2];
            break;
        default: // fly phase or other
            memset(this->m_dSubPoly_B, 0, sizeof(this->m_dSubPoly_B));
            return false;
        }
        return true;
    }
    // calculate the moment limitation due to the foot region
    bool fnbCalMStabLimitPG() { 
        auto &cfg = this->m_stRobConfig;
        double dMargin[3] = { 0.015, 0.01, 0.01 }; // [forw, back, side]
        #ifdef __Direct
            switch(this->m_stIO->SupSignal) {
            case DSup: // double leg support phase
                this->m_dMStabLimit[0] = -(cfg->FootGeom[3] - (double)this->m_nPosCon * dMargin[2]) * cfg->Mass * __Gravity;
                this->m_dMStabLimit[1] =  (cfg->FootGeom[3] - (double)this->m_nPosCon * dMargin[2]) * cfg->Mass * __Gravity;
                break;
            case LSup: // left leg support phase
                this->m_dMStabLimit[0] = -(cfg->FootGeom[2] - (double)this->m_nPosCon * dMargin[2]) * cfg->Mass * __Gravity;
                this->m_dMStabLimit[1] =  (cfg->FootGeom[3] - (double)this->m_nPosCon * dMargin[2]) * cfg->Mass * __Gravity;
                break;
            case RSup: // right leg support phase
                this->m_dMStabLimit[0] = -(cfg->FootGeom[3] - (double)this->m_nPosCon * dMargin[2]) * cfg->Mass * __Gravity;
                this->m_dMStabLimit[1] =  (cfg->FootGeom[2] - (double)this->m_nPosCon * dMargin[2]) * cfg->Mass * __Gravity;
                break;
            default: // fly phase or other
                memset(this->m_dMStabLimit, 0, sizeof(this->m_dMStabLimit));
                return false;
            }
        #endif
        #ifdef __AnkPos
            double dSupAnkPosLat[2] = { 0.0 }; // left, right
            this->fnbCalSupPolyPG(); // calculate support polygon
            switch(this->m_stIO->SupSignal) {
            case DSup: // double leg support phase
                dSupAnkPosLat[0] = this->m_stCmd.Ank.L.B[__y], dSupAnkPosLat[1] = this->m_stCmd.Ank.R.B[__y];
                break;
            case LSup: // left leg support phase
                dSupAnkPosLat[0] = dSupAnkPosLat[1] = this->m_stCmd.Ank.L.B[__y];
                break;
            case RSup: // right leg support phase
                dSupAnkPosLat[0] = dSupAnkPosLat[1] = this->m_stCmd.Ank.R.B[__y];
                break;
            default: // fly phase or other
                dSupAnkPosLat[0] = this->m_dSubPoly_B[3], dSupAnkPosLat[1] = this->m_dSubPoly_B[2];
                break;
            }
            this->m_dMStabLimit[0] = (this->m_dSubPoly_B[2] - dSupAnkPosLat[1] + (double)this->m_nPosCon * dMargin[2]) * cfg->Mass * __Gravity;
            this->m_dMStabLimit[1] = (this->m_dSubPoly_B[3] - dSupAnkPosLat[0] - (double)this->m_nPosCon * dMargin[2]) * cfg->Mass * __Gravity;
        #endif
        this->m_dMStabLimit[2] = -(cfg->FootGeom[0] - (double)this->m_nPosCon * dMargin[0]) * cfg->Mass * __Gravity;
        this->m_dMStabLimit[3] =  (cfg->FootGeom[1] - (double)this->m_nPosCon * dMargin[1]) * cfg->Mass * __Gravity;
        return true;
    }
    // calculate the CoM error using simple direct reading state estimate method
    bool fnbCalCoMErr() { 
        auto &ref = this->m_stRef, &sen = this->m_stSen, &con = this->m_stCoV, &err = this->m_stErr;
        auto &cfg = this->m_stRobConfig;
        for(int i = _rl; i <= _pt; i++ ) {
            err.Base[i] = sen.Base[i] - ref.Base[i] - (double)this->m_nPosCon * con.Base[i]; // calculate posture error
            err.dBase[i] = sen.dBase[i] - ref.dBase[i] - (double)this->m_nPosCon * con.dBase[i]; // calculate posture rate error 
            err.Base[this->fnnEulerNum(i)] = this->fnbEulerSign(i) * cfg->Zc * sin(err.Base[i]); // calculate the CoM error
            err.dBase[this->fnnEulerNum(i)] = this->fnbEulerSign(i) * cfg->Zc * sin(err.dBase[i]); // calculate the CoM rate error
        }
        return true;
    }
    // calculate the footft error
    bool fnbCalFftErr() { 
        auto &ref = this->m_stRef, &sen = this->m_stSen, &err = this->m_stErr;
        for(int i = __x; i <= _ya; i++) err.Fft.L.B[i] = sen.Fft.L.B[i] - ref.Fft.L.B[i], err.Fft.R.B[i] =  sen.Fft.R.B[i] - ref.Fft.R.B[i];
        return true;
    }
    // calculate the feedback moment to stablize the CoM and CoM rate error
    bool fnbCalMStabFB() { 
        double dLagTSplit = 0.1, dLagTFz = 0.002;
        double dFBMAmp[2] = { 1.0, 1.0 }, dFBkd[2] = { 1.5, 1.0 }; // [rl, pt]
        auto &err = this->m_stErr;
        auto &kp = this->m_stGains->CalMStab[0], &kd = this->m_stGains->CalMStab[1];
        auto &Lx = this->m_stCmd.Ank.L.B[__x], &Ly = this->m_stCmd.Ank.L.B[__y], &Rx = this->m_stCmd.Ank.R.B[__x], &Ry = this->m_stCmd.Ank.R.B[__y];
        this->fnbCalMStabLimitPG();
        this->fnbCalCoMErr(); 
        // calculate Mfeet, Mmdzmp and Mstab
        for(int i = _rl; i <= _pt; i++) this->m_dMStab[i] = -this->fnbEulerSign(i) * dFBMAmp[i - 3] * (kp * err.Base[this->fnnEulerNum(i)] + kd * dFBkd[i - 3] * err.dBase[this->fnnEulerNum(i)]); // calculate the stablize moment
        #ifdef __Aver3Filter
        this->m_dMStab[_pt] = cMPit.Filter(this->m_dMStab[_pt]);
        this->m_dMStab[_rl] = cMRol.Filter(this->m_dMStab[_rl]);
        #endif
        this->m_dMFeet[_rl] = fndAddLimit(this->m_dMStab[_rl], 0.0, &this->m_dMMdZMP[_rl], this->m_dMStabLimit);
        this->m_dMFeet[_pt] = fndAddLimit(this->m_dMStab[_pt], 0.0, &this->m_dMMdZMP[_pt], this->m_dMStabLimit + 2);
        if(this->fndIfTD()) {
            // if(this->m_stIO->SupSignal == DSup) this->m_dMFeet[__z] = fndFilterTimeLag(this->m_dMFeet[__z], (this->m_dMFeet[_rl]/pow(((Lx - Rx)*(Lx - Rx))/((Ly - Ry)*(Ly - Ry)) + 1, 0.5) - (this->m_dMFeet[_pt]*(Lx - Rx)/(pow(((Lx - Rx)*(Lx - Rx))/((Ly - Ry)*(Ly - Ry)) + 1, 0.5)*(Ly - Ry)))) / sqrt((Lx - Rx)*(Lx - Rx) + (Ly - Ry)*(Ly - Ry)), this->m_stRobConfig->Tc, dLagTFz);
            if(this->m_stIO->SupSignal == DSup) this->m_dMFeet[__z] = fndFilterTimeLag(this->m_dMFeet[__z], this->m_dMFeet[_rl] / this->m_stRobConfig->AnkWidth, this->m_stRobConfig->Tc, dLagTFz);
            else this->m_dMFeet[__z] = fndFilterTimeLag(this->m_dMFeet[__z], 0.0, this->m_stRobConfig->Tc, dLagTFz); // left foot positive, Todo[more accurate split]
        }
        // calculate Mpend and Mwheel by spliting Mmdzmp
        for(int i = _rl; i <= _pt; i++) {
            this->m_dMPend[i] = fndFilterTimeLag(this->m_dMPend[i], this->m_dMMdZMP[i], this->m_stRobConfig->Tc, dLagTSplit);
            this->m_dMWheel[i] = this->m_dMMdZMP[i] - this->m_dMPend[i];
        }
        return true;
    }
    // calculate the positional and rotational control value of model ZMP
    bool fnbMdZMPCon(int nIfCon) { 
        double dLimit_pos[6] = { -0.03, 0.03, -10.0, 10.0, -2500.0, 2500.0 };
        double dLimit_rot[6] = { -0.03 * 6.0, 0.03 * 6.0, -10.0 * 6.0, 10.0 * 6.0, -2500.0 * 6.0, 2500.0 * 6.0 };
        auto &kp_pos = this->m_stGains->MdZMP[0], &kd_pos = this->m_stGains->MdZMP[1], &kp_rot = this->m_stGains->MdZMP[2], &kd_rot = this->m_stGains->MdZMP[3];
        auto &ref = this->m_stRef, &con = this->m_stCoV, &cmd = this->m_stCmd;
        auto &cfg = this->m_stRobConfig;
        static double dMdZMPBase[6], dMdZMPddBase[6], dMdZMPdBase[6]; // test
        this->fnbCalMStabFB();
        for(int i = __x; i <= __y; i++) {
            dMdZMPddBase[i] = -this->fnbEulerSign(i) * this->m_dMPend[this->fnnEulerNum(i)] / cfg->UpperMass / cfg->Zc - kp_pos * dMdZMPBase[i] - kd_pos * dMdZMPdBase[i];
            dMdZMPddBase[this->fnnEulerNum(i)] = -this->m_dMWheel[this->fnnEulerNum(i)] / cfg->UpperIner - kp_rot * dMdZMPBase[this->fnnEulerNum(i)] - kd_rot * dMdZMPdBase[this->fnnEulerNum(i)];
            fnvIntergAccLimit(&dMdZMPBase[i], &dMdZMPdBase[i], dMdZMPddBase[i], dLimit_pos, cfg->Tc);
            fnvIntergAccLimit(&dMdZMPBase[this->fnnEulerNum(i)], &dMdZMPdBase[this->fnnEulerNum(i)], dMdZMPddBase[this->fnnEulerNum(i)], dLimit_rot, cfg->Tc);
        }
        if(nIfCon) {
            for(int i = __x; i <= __y; i++) cmd.Base[i] += dMdZMPBase[i], ref.Base[this->fnnEulerNum(i)] += dMdZMPBase[this->fnnEulerNum(i)];
            return true;
        }
        return false;
    }
    // split the feedback moment to each foot and add them to the reference
    bool fnbAddFftFb(int nIfCon) { 
        double dFzAmp = 1.0;
        auto dIfCon = (double)nIfCon;
        auto &pg = this->m_stPG, &ref = this->m_stRef;
        auto &Lx = this->m_stCmd.Ank.L.B[__x], &Ly = this->m_stCmd.Ank.L.B[__y], &Rx = this->m_stCmd.Ank.R.B[__x], &Ry = this->m_stCmd.Ank.R.B[__y];
        auto &Zx = this->m_stSen.ZMP[__x], &Zy = this->m_stSen.ZMP[__y];
        double dLimitAlpha[2] = { 0.0, 1.0 }, dAlphaL, dAlphaR;
        #ifdef __ZMPSplit
            double dMidPoint_y = (Lx*Lx*Ry - Lx*Ly*Rx + Zx*Lx*Ly - Lx*Rx*Ry - Zx*Lx*Ry + Zy*Ly*Ly + Ly*Rx*Rx - Zx*Ly*Rx - 2*Zy*Ly*Ry + Zx*Rx*Ry + Zy*Ry*Ry)/(Lx*Lx - 2*Lx*Rx + Ly*Ly - 2*Ly*Ry + Rx*Rx + Ry*Ry);
            dAlphaL = fndLimit((dMidPoint_y - Ry) / (Ly - Ry), dLimitAlpha);
        #endif
        #ifdef __FzSplit
            dAlphaL = this->m_stSen.Fft.L.B[__z] / (this->m_stSen.Fft.L.B[__z] + this->m_stSen.Fft.R.B[__z]); // calculate the split rate for the feedback force
        #endif
        dAlphaRe = dAlphaR = 1.0 - dAlphaL;
        dAlphaL *= dIfCon, dAlphaR *= dIfCon, dFzAmp *= dIfCon; // check if feedback control is triggered Todo[these 3 val add filter]
        memset(ref.Fft.L.B, 0, sizeof(ref.Fft.L.B)), memset(ref.Fft.R.B, 0, sizeof(ref.Fft.R.B)); // init referenced footft every control circle
        ref.Fft.L.B[__z] = this->m_stGains->Vip * pg.Fft.L.B[__z], ref.Fft.R.B[__z] = this->m_stGains->Vip * pg.Fft.R.B[__z]; // init referenced footft z
        if(this->fnnIfTD()) { // add feedback force when the robot touch down
            ref.Fft.L.B[__z] += dFzAmp * this->m_dMFeet[__z];
            ref.Fft.R.B[__z] -= dFzAmp * this->m_dMFeet[__z];
            switch(this->m_stIO->SupSignal) {
            case DSup: // double leg support phase
                if(this->fnnIfLTD()) for(int i = _rl; i <= _pt; i++) ref.Fft.L.B[i] = pg.Fft.L.B[i] + dAlphaL * this->m_dMFeet[i];
                if(this->fnnIfRTD()) for(int i = _rl; i <= _pt; i++) ref.Fft.R.B[i] = pg.Fft.R.B[i] + dAlphaR * this->m_dMFeet[i];
                break;
            case LSup: // left leg support phase
                if(this->fnnIfLTD()) for(int i = _rl; i <= _pt; i++) ref.Fft.L.B[i] = pg.Fft.L.B[i] + dAlphaL * this->m_dMFeet[i];
                break;
            case RSup: // right leg support phase
                if(this->fnnIfRTD()) for(int i = _rl; i <= _pt; i++) ref.Fft.R.B[i] = pg.Fft.R.B[i] + dAlphaR * this->m_dMFeet[i];
                break;
            default: // fly
                ref.Fft.L.B[__z] = ref.Fft.R.B[__z] = 0.0;
                break;
            }
        }
        return nIfCon;
    }
    // obtian the paramaters for ground reaction force control
    bool fnbVarStiff(
        double dPr[10] // [kfr_L, kfr_R, kpr_L, kpr_R], [kfz_L, kfz_R, kpz_L, kpz_R, kdz_L, kdz_R]
        ) {
        double dDouAmp[2] = { 1.0, 1.0 }, dDouStiff[2] = { 0.5, 0.8 };
        double dSupAmp[2] = { 1.2, 1.3 }, dSupStiff[2] = { 0.2, 1.0 };
        double dSwiAmp[2] = { 1.5, 1.1 }, dSwiStiff[2] = { 0.05, 0.2 };
        double dSupAmpKdz = 0.5,          dRecStiff[2] = { 5.0, 2.5 };
        auto &ga = this->m_stGains;
        auto &kfz = ga->GRFC[0], &kpz = ga->GRFC[1], &kdz = ga->GRFC[2], &kfr = ga->GRFC[7], &kpr = ga->GRFC[8];
        auto &kfr_L = dPr[0], &kfr_R = dPr[1], &kpr_L = dPr[2], &kpr_R = dPr[3], &kfz_L = dPr[4], &kfz_R = dPr[5], &kpz_L = dPr[6], &kpz_R = dPr[7], &kdz_L = dPr[8], &kdz_R = dPr[9];
        kfr_L = kfr_R = kfr, kpr_L = kpr_R = kpr, kfz_L = kfz_R = kfz, kpz_L = kpz_R = kpz, kdz_L = kdz_R = kdz;
        #ifdef __VarStiff
        switch(this->m_stIO->SupSignal) {
        #ifdef __UntouchRe
            case DSup: // double support phase
                /*rot*/ kfr_L = kfr_R = dDouAmp[0] * kfr, kpr_L = kpr_R = dDouStiff[0] * kpr, /*z*/ kfz_L = kfz_R = dDouAmp[1] * kfz, kpz_L = kpz_R = dDouStiff[1] * kpz, kdz_L = kdz_R = kdz;
                if(!this->fndIfLTD()) /*rot*/ kpr_L = dRecStiff[0] * kpr, /*z*/ kpz_L = dRecStiff[1] * kpz; // if left foot untouched -> faster recover
                if(!this->fndIfRTD()) /*rot*/ kpr_R = dRecStiff[0] * kpr, /*z*/ kpz_R = dRecStiff[1] * kpz; // if right foot untouched -> faster recover
                break;
            case LSup: // left leg support phase
                /*rot*/ kfr_L = dSupAmp[0] * kfr, kpr_L = dSupStiff[0] * kpr, /*z*/ kfz_L = dSupAmp[1] * kfz, kpz_L = dSupStiff[1] * kpz, kdz_L = kdz_R = kdz; // better stabilzity
                /*rot*/ kfr_R = dSwiAmp[0] * kfr, kpr_R = dSwiStiff[0] * kpr, /*z*/ kfz_R = dSwiAmp[1] * kfz, kpz_R = dSwiStiff[1] * kpz, kdz_R = kdz_R = dSupAmpKdz * kdz; // better adaption
                if(!this->fndIfRTD()) /*rot*/ kpr_R = dRecStiff[0] * kpr, /*z*/ kpz_R = dRecStiff[1] * kpz; // if right foot untouched -> faster recover 
                break;
            case RSup: // right leg support phase
                /*rot*/ kfr_L = dSwiAmp[0] * kfr, kpr_L = dSwiStiff[0] * kpr, /*z*/ kfz_L = dSwiAmp[1] * kfz, kpz_L = dSwiStiff[1] * kpz, kdz_L = kdz_R = dSupAmpKdz * kdz; // better adaption
                /*rot*/ kfr_R = dSupAmp[0] * kfr, kpr_R = dSupStiff[0] * kpr, /*z*/ kfz_R = dSupAmp[1] * kfz, kpz_R = dSupStiff[1] * kpz, kdz_R = kdz_R = kdz; // better stabilzity
                if(!this->fndIfLTD()) /*rot*/ kpr_L = dRecStiff[0] * kpr, /*z*/ kpz_L = dRecStiff[1] * kpz; // if left foot untouched -> faster recover
                break;
            default: // fly
                if(!this->fndIfLTD()) /*rot*/ kpr_L = dRecStiff[0] * kpr, /*z*/ kpz_L = dRecStiff[1] * kpz; // if left foot untouched -> faster recover
                if(!this->fndIfRTD()) /*rot*/ kpr_R = dRecStiff[0] * kpr, /*z*/ kpz_R = dRecStiff[1] * kpz; // if right foot untouched -> faster recover 
                break;
        #endif
        #ifdef __TouchSoft
            case DSup: // double support phase
                /*rot*/ kpr_L = kpr_R = dRecStiff[0] * kpr, /*z*/ kpz_L = kpz_R = dRecStiff[1] * kpz; // faster recover
                if(this->fndIfLTD()) /*rot*/ kfr_L = dDouAmp[0] * kfr, kpr_L = dDouStiff[0] * kpr, /*z*/ kfz_L = dDouAmp[1] * kfz, kpz_L = dDouStiff[1] * kpz, kdz_L = kdz;
                if(this->fndIfRTD()) /*rot*/ kfr_R = dDouAmp[0] * kfr, kpr_R = dDouStiff[0] * kpr, /*z*/ kfz_R = dDouAmp[1] * kfz, kpz_R = dDouStiff[1] * kpz, kdz_R = kdz;
                break;
            case LSup: // left leg support phase
                /*rot*/ kpr_R = dRecStiff[0] * kpr, /*z*/ kpz_R = dRecStiff[1] * kpz; // if right foot untouched -> faster recover 
                if(this->fndIfLTD()) /*rot*/ kfr_L = dSupAmp[0] * kfr, kpr_L = dSupStiff[0] * kpr, /*z*/ kfz_L = dSupAmp[1] * kfz, kpz_L = dSupStiff[1] * kpz, kdz_L = kdz_R = kdz; // better stabilzity
                if(this->fndIfRTD()) /*rot*/ kfr_R = dSwiAmp[0] * kfr, kpr_R = dSwiStiff[0] * kpr, /*z*/ kfz_R = dSwiAmp[1] * kfz, kpz_R = dSwiStiff[1] * kpz, kdz_R = kdz_R = dSupAmpKdz * kdz; // better adaption
                break;
            case RSup: // right leg support phase
                /*rot*/ kpr_L = dRecStiff[0] * kpr, /*z*/ kpz_L = dRecStiff[1] * kpz; // if right foot untouched -> faster recover
                if(this->fndIfLTD()) /*rot*/ kfr_L = dSwiAmp[0] * kfr, kpr_L = dSwiStiff[0] * kpr, /*z*/ kfz_L = dSwiAmp[1] * kfz, kpz_L = dSwiStiff[1] * kpz, kdz_L = kdz_R = dSupAmpKdz * kdz; // better adaption
                if(this->fndIfRTD()) /*rot*/ kfr_R = dSupAmp[0] * kfr, kpr_R = dSupStiff[0] * kpr, /*z*/ kfz_R = dSupAmp[1] * kfz, kpz_R = dSupStiff[1] * kpz, kdz_R = kdz_R = kdz; // better stabilzity
                break;
            default: // fly
                /*rot*/ kpr_L = kpr_R = dRecStiff[0] * kpr, /*z*/ kpz_L = kpz_R = dRecStiff[1] * kpz; // faster recover
                break;
        #endif
        }
        #endif
        return true;
    }
    // the ground reaction force control, simple compliance if the feedback moment is not applied
    bool fnbGRFC(int nIfCon) { 
        double dlimit_z[6] = { -1.0 * 0.02, 0.04, -10.0, 10.0, -2500.0, 2500.0 }, dLimit_r[4] = { -__D2R(15.0), __D2R(15.0), -60.0, 60.0 };
        double dThresh_z[2] = { -10.0, 10.0 }, dThresh_r[2] = { -1.0, 1.0 }; //, dPr[4]; test
        auto ga = this->m_stGains;
        auto kfz = ga->GRFC[0], kpz = ga->GRFC[1], kdz = ga->GRFC[2], kvcz = ga->GRFC[3], kacz = ga->GRFC[4], kdfz = ga->GRFC[5], kdfcz = ga->GRFC[6];
        auto &con = this->m_stCoV, &err = this->m_stErr, &cmd = this->m_stCmd;
        auto Tc = this->m_stRobConfig->Tc;
        static double dFzLErr, dFzRErr, dFzLdErr, dFzRdErr;
        this->fnbCalFftErr();
        this->fnbVarStiff(dPr);
        auto /*rot*/ &kfr_L = dPr[0], &kfr_R = dPr[1], &kpr_L = dPr[2], &kpr_R = dPr[3], /*z*/ &kfz_L = dPr[4], &kfz_R = dPr[5], &kpz_L = dPr[6], &kpz_R = dPr[7], &kdz_L = dPr[8], &kdz_R = dPr[9];
        // calculate compliance z
        dFzLdErr = (err.Fft.L.B[__z] - dFzLErr) / Tc, dFzRdErr = (err.Fft.R.B[__z] - dFzRErr) / Tc;
        dConddL[__z] = kfz_L * fndThreshold(err.Fft.L.B[__z], dThresh_z) - kpz_L * dConL[__z] - kdz_L * dCondL[__z] + kvcz * dCondR[__z] + kacz * dConddR[__z] + kdfz * dFzLdErr + kdfcz * dFzRdErr;
        dConddR[__z] = kfz_R * fndThreshold(err.Fft.R.B[__z], dThresh_z) - kpz_R * dConR[__z] - kdz_R * dCondR[__z] + kvcz * dCondL[__z] + kacz * dConddL[__z] + kdfz * dFzRdErr + kdfcz * dFzLdErr;
        dFzLErr = err.Fft.L.B[__z], dFzRErr = err.Fft.R.B[__z];
        fnvIntergAccLimit(&dConL[__z], &dCondL[__z], dConddL[__z], dlimit_z, Tc);
        fnvIntergAccLimit(&dConR[__z], &dCondR[__z], dConddR[__z], dlimit_z, Tc);
        con.Ank.L.B[__z] = dConL[__z];
        con.Ank.R.B[__z] = dConR[__z];
        // calculate dAnk pitch and roll
        // static double dConL[6], dConR[6], dCondL[6], dCondR[6]; // test
        for(int i = _rl; i <= _pt; i++) {
            dCondL[i] = kfr_L * fndThreshold(err.Fft.L.B[i], dThresh_r) - kpr_L * dConL[i];
            dCondR[i] = kfr_R * fndThreshold(err.Fft.R.B[i], dThresh_r) - kpr_R * dConR[i];
            fnvIntergVeloLimit(&dConL[i], dCondL[i], dLimit_r, Tc);
            fnvIntergVeloLimit(&dConR[i], dCondR[i], dLimit_r, Tc);
            con.Ank.L.B[i] = dConL[i];
            con.Ank.R.B[i] = dConR[i];
        }
        #ifdef __Aver3Filter
        con.Ank.L.B[_pt] = cPitL.Filter(dConL[_pt]), con.Ank.L.B[_rl] = cRolL.Filter(dConL[_rl]), con.Ank.L.B[__z] = cZL.Filter(dConL[__z]);
        con.Ank.R.B[_pt] = cPitR.Filter(dConR[_pt]), con.Ank.R.B[_rl] = cRolR.Filter(dConR[_rl]), con.Ank.R.B[__z] = cZR.Filter(dConR[__z]);
        #endif
        if(nIfCon) {
            for(int i = __x; i <= _ya; i++) cmd.Ank.L.W[i] += con.Ank.L.B[i], cmd.Ank.R.W[i] += con.Ank.R.B[i]; // test
            return true;
        }
        return false;
    }
    // simple compliance control to absorb the impact
    bool fnvCompliance(int nIfCon) {
        double dLimit[4] = { -__D2R(5.0), __D2R(5.0), -60.0, 60.0 };
        auto kf = this->m_stGains->Compliance[0], kp = this->m_stGains->Compliance[1];
        static double AnkL[6], AnkR[6], dAnkL[6], dAnkR[6];
        auto &sen = this->m_stSen, &cmd = this->m_stCmd;
        for(int i = _rl; i <= _pt; i++) {
            dAnkL[i] = kf * sen.Fft.L.B[i] - kp * AnkL[i];
            dAnkR[i] = kf * sen.Fft.R.B[i] - kp * AnkR[i];
            fnvIntergVeloLimit(&AnkL[i], dAnkL[i], dLimit, this->m_stRobConfig->Tc);
            fnvIntergVeloLimit(&AnkR[i], dAnkR[i], dLimit, this->m_stRobConfig->Tc);
        }
        if(nIfCon) {
            for(int i = _rl; i <= _ya; i++) cmd.Ank.L.B[i] += AnkL[i], cmd.Ank.R.B[i] += AnkR[i]; 
            return true;
        }
        return false;
    }
    // armswing based on leg joint speed
    bool fnbArmSwing(int nIfCon) {
        double dAnkWth = 0.16, dShouderWth = 0.4, dLArm = 0.4, dLShank = 0.32, dLThigh = 0.32, dMArm = 5.0, dMThigh = 9.0, dMShank = 2.0, dMFoot = 1.0;
        static double dArmQL, dArmQR;
        auto K_L = this->m_stGains->ArmSwi[0], v_M = this->m_stGains->ArmSwi[1];
        auto dQ = this->m_stPG.LegdQ;
        auto &cmd = this->m_stCmd, &pg = this->m_stPG;
        double K_P = 1.0 - K_L;
	    double dql_arm[3], dqr_arm[3]; // L, P, L + P
        dqr_arm[0] = 2.0 * dAnkWth / (dShouderWth * dLArm * (dMArm + v_M)) * ((0.5 * dMThigh + dMShank + dMFoot) * dLThigh * dQ.L[2] + (0.5 * dMShank + dMFoot) * dLShank * dQ.L[3]);
        dql_arm[0] = 2.0 * dAnkWth / (dShouderWth * dLArm * (dMArm + v_M)) * ((0.5 * dMThigh + dMShank + dMFoot) * dLThigh * dQ.R[2] + (0.5 * dMShank + dMFoot) * dLShank * dQ.R[3]);
        dql_arm[1] = -2.0 / (dLArm * (dMArm + v_M)) * ((0.5 * dMThigh + dMShank + dMFoot) * dLThigh * dQ.L[2] + (0.5 * dMShank + dMFoot) * dLShank * dQ.L[3]);
        dqr_arm[1] = -2.0 / (dLArm * (dMArm + v_M)) * ((0.5 * dMThigh + dMShank + dMFoot) * dLThigh * dQ.R[2] + (0.5 * dMShank + dMFoot) * dLShank * dQ.R[3]);
        dql_arm[2] = K_L * dql_arm[0] + K_P * dql_arm[1];
        dqr_arm[2] = K_L * dqr_arm[0] + K_P * dqr_arm[1];
        dArmQL += dql_arm[2] * this->m_stRobConfig->Tc, dArmQR += dqr_arm[2] * this->m_stRobConfig->Tc;
        if(nIfCon) {
            cmd.ArmQ.L = pg.ArmQ.L + dArmQL, cmd.ArmQ.R = pg.ArmQ.R + dArmQR;
            return true;
        }
        return false;
    }
    //  model-free heuristic method of adjusting step location
    bool fnbStepCon(int nIfCon) {
        // static int nKInStep; // test
        // static double dErr; // test
        double dLimit[4] = { -0.18, 0.18, -2.0, 2.0 };
        double dThresh[2] = { -this->m_stGains->StepCon[3], this->m_stGains->StepCon[3] }, dLTemp;
        auto kp = this->m_stGains->StepCon[0], ts = this->m_stGains->StepCon[1], te = this->m_stGains->StepCon[2], kL = 3.5 / te;
        auto &err = this->m_stErr, &ref = this->m_stRef, &cmd = this->m_stCmd;
        auto &io = this->m_stIO;
        if(io->SupSignal == DSup) kp = 0.0; // recover in double support phase
        for(int i = __x; i <= __y; i++) { // calculate dErr & deltaL
            #ifdef __Theta
            dErr[i] = 2.0 * fndThreshold(err.Base[i], dThresh);
            #endif
            #ifdef __Theta2
            dErr[i] = 3.0 * fndGetSign(err.Base[i]) * pow(fndThreshold(err.Base[i], dThresh), 2);
            #endif
            #ifdef __ThetaInt
            if(io->SupSignal == DSup) dErr[i] =  0.0;
            dErr[i] += 3.0 * fndThreshold(err.Base[i], dThresh) * this->m_stRobConfig->Tc;
            #endif
            #ifdef __CaptureP
            dErr[i] = 1.0 * fndThreshold((err.Base[i] + err.dBase[i] / 15.0), dThresh);
            #endif
            ref.DeltaL[i] = kp * dErr[i];
        }
        if(this->m_SupLegLast == DSup && io->SupSignal != DSup) nKInStep = 0;
        if(nKInStep * this->m_stRobConfig->Tc >= 0.0 && nKInStep * this->m_stRobConfig->Tc < ts) kL = 0.0;
        if(nKInStep * this->m_stRobConfig->Tc >= (io->TStepSS - te) && nKInStep * this->m_stRobConfig->Tc < io->TStepSS) kL = 0.0;  
        for(int i = __x; i <= __y; i++) {
            dLTemp = kL * (ref.DeltaL[i] - cmd.DeltaL[i]);
            if(nIfCon) fnvIntergVeloLimit(&cmd.DeltaL[i], dLTemp, dLimit, this->m_stRobConfig->Tc);
        }
        if(nKInStep < 1000) nKInStep++;
        return nIfCon;
    }
    // read pg trajectory and reference
    bool fnbGetTra() {
        static int nIfFirst = 2;
        static double dLegQL_old[6], dLegQR_old[6];
        auto &pg = this->m_stPG, &ref = this->m_stRef, &cmd = this->m_stCmd;
        auto &io = this->m_stIO;
        for(int i = __x; i <= _ya; i++) {
            cmd.Base[i]     = pg.Base[i]        = io->BasePG[i];
                              pg.dBase[i]       = io->dBasePG[i];
            cmd.Ank.L.W[i]  = pg.Ank.L.W[i]     = io->LAnkPG_W[i];
            cmd.Ank.R.W[i]  = pg.Ank.R.W[i]     = io->RAnkPG_W[i];
            pg.Ank.L.B[i]   = io->LAnkPG_W[i] - io->BasePG[i];
            pg.Ank.R.B[i]   = io->RAnkPG_W[i] - io->BasePG[i];
            pg.Fft.L.B[i]   = io->LFTPG_B[i];
            pg.Fft.R.B[i]   = io->RFTPG_B[i];
        }
        for(int i = __x; i <= __z; i++) cmd.Ank.L.B[i] = pg.Ank.L.B[i], cmd.Ank.R.B[i] = pg.Ank.R.B[i];
        for(int i = _rl; i <= _pt; i++) ref.Base[i] = pg.Base[i], ref.dBase[i] = pg.dBase[i];
        for(int i = 0; i < 6; i++) pg.LegQ.L[i] = io->LegQ[i], pg.LegQ.R[i] = io->LegQ[i + 6];
        if(nIfFirst > 0) {
            for(int i = 0; i < 6; i++) dLegQL_old[i] = pg.LegQ.L[i], dLegQR_old[i] = pg.LegQ.R[i]; // if is first
            nIfFirst--;
        }
        for(int i = 0; i < 6; i++) {
            pg.LegdQ.L[i] = (pg.LegQ.L[i] - dLegQL_old[i]) / this->m_stRobConfig->Tc;
            pg.LegdQ.R[i] = (pg.LegQ.R[i] - dLegQR_old[i]) / this->m_stRobConfig->Tc;
        }
        for(int i = 0; i < 6; i++) dLegQL_old[i] = pg.LegQ.L[i], dLegQR_old[i] = pg.LegQ.R[i];
        cmd.ArmQ.L = pg.ArmQ.L = io->ArmQ[0], cmd.ArmQ.R = pg.ArmQ.R = io->ArmQ[1];
        return true;
    }
    // read sensors data
    bool fnbGetSen() {
        static double dFftL[6], dFftR[6];
        auto &sen = this->m_stSen;
        auto &io = this->m_stIO;
        auto &filter = this->m_stFilters;
        auto &Tc = this->m_stRobConfig->Tc;
        static int nIfFirst = 1;
        if(nIfFirst) {
            for(int i = _rl; i <= _pt; i++) sen.Base[i] = io->IMUSen[i - 3];
            for(int i = __x; i <= __y; i++) sen.ZMP[i] = 0.0;
            nIfFirst = 0;
        }
        for(int i = __x; i <= __y; i++) sen.ZMP[i] =  fndFilterTimeLag(sen.ZMP[i], io->ZMPSen_B[i], Tc, filter->TLagZMP);
        for(int i = _rl; i <= _pt; i++) {
            sen.dBase[i] = fndFilterTimeLag(sen.dBase[i], (io->IMUSen[i - 3] - sen.Base[i]) / Tc, Tc, filter->TLagGro); // Todo[filter maybe wrong]
            sen.Base[i] =  fndFilterTimeLag(sen.Base[i], io->IMUSen[i - 3], Tc, filter->TLagIMU);
        }
        for(int i = __x; i <= __z; i++) {
            sen.Fft.L.B[i] = dFftL[i] = fndFilterTimeLag(dFftL[i], io->LFTSen_B[i], Tc, filter->TLagFrc);
            sen.Fft.R.B[i] = dFftR[i] = fndFilterTimeLag(dFftR[i], io->RFTSen_B[i], Tc, filter->TLagFrc);
            
        }
        for(int i = _rl; i <= _pt; i++) {
            sen.Fft.L.B[i] = dFftL[i] = fndFilterTimeLag(dFftL[i], filter->AmpTrq * io->LFTSen_B[i], Tc, filter->TLagTrq);
            sen.Fft.R.B[i] = dFftR[i] = fndFilterTimeLag(dFftR[i], filter->AmpTrq * io->RFTSen_B[i], Tc, filter->TLagTrq);
        } 
        #ifdef __Aver3Filter
        sen.Fft.L.B[_pt] = cTPitL.Filter(dFftL[_pt]), sen.Fft.L.B[_rl] = cTRolL.Filter(dFftL[_rl]), sen.Fft.L.B[__z] = cFzL.Filter(dFftL[__z]);
        sen.Fft.R.B[_pt] = cTPitR.Filter(dFftR[_pt]), sen.Fft.R.B[_rl] = cTRolR.Filter(dFftR[_rl]), sen.Fft.R.B[__z] = cFzR.Filter(dFftR[__z]);
        #endif
        return true;
    }
    // get the control value
    bool fnbGetConV() {
        this->fnbUpperPosCon(this->m_nPosCon);
        this->fnbMdZMPCon(this->m_nMdZMP);
        this->fnbAddFftFb(this->m_nFftFB); // must after the step position control
        this->fnbGRFC(this->m_nGRFC);
        this->fnvCompliance(this->m_nComp);
        this->fnbArmSwing(this->m_nArmSwi);
        this->fnbStepCon(this->m_nStepCon);
        return true;
    }
    // send commands data 
    bool fnbSendCmd() {
        auto &cmd = this->m_stCmd;
        auto &io = this->m_stIO;
        for(int i = __x; i <= _ya; i++) {
            io->BaseCmd[i] = cmd.Base[i];
            io->LAnkCmd_W[i] = cmd.Ank.L.W[i];
            io->RAnkCmd_W[i] = cmd.Ank.R.W[i];
        }
        io->ArmQcmd[0] = cmd.ArmQ.L, io->ArmQcmd[1] = cmd.ArmQ.R;
        for(int i = __x; i <= __y; i++) io->DeltaL_B[i] = cmd.DeltaL[i];
        this->m_SupLegLast = io->SupSignal; // update support signal
        return true;
    }
};

_D_CONTROL_END

#endif