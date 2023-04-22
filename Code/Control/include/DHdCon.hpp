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
    double UpperPos[3]; // [k_posture, kp, kd]
    double CalMStab[2]; // [kp, kd]
    double MdZMP[2]; // [kp_pos, kd_pos, kp_rot, kd_rot]
    double GRFC[9];
    double Compliance[2];
};

struct st_Filters{ // init required
    double TLagIMU;
    double TLagGro;
    double TLagFrc;
    double TLagTrq;
};

struct st_DHdConIO{ // init required
    // input
    double BasePG[6]; // pattern generated base position and posture [x, y, z, rx, ry, rz]
    double LAnkPG_W[6]; // pattern generated left ankle position and posture in world frame [x, y, z, rx, ry, rz]
    double RAnkPG_W[6]; // pattern generated right ankle position and posture in world frame [x, y, z, rx, ry, rz]
    double LFTPG_B[6]; // left reference foot contact force and torque in base frame [fx, fy, fz, tx, ty, tz]
    double RFTPG_B[6]; // right reference foot contact force and torque in base frame [fx, fy, fz, tx, ty, tz]
    double IMUSen[2]; // sensed IMU data [rx, ry]
    double LFTSen_B[6]; // left sensed foot contact force and torque in base frame
    double RFTSen_B[6]; // right sensed foot contact force and torque in base frame
    int SupSignal;
    int PressKey;
    // output
    double BaseCmd[6]; // commanded base position and posture [x, y, z, rx, ry, rz]
    double LAnkCmd_W[6]; // commanded left ankle position and posture in world frame [x, y, z, rx, ry, rz]
    double RAnkCmd_W[6]; // commanded right ankle position and posture in world frame [x, y, z, rx, ry, rz]
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
    int SupLeg;
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
        int nComp) {
        this->SetCon(nPosCon, nMdZMP, nFftFB, nGRFC, nComp);
        this->Reset();
        this->m_nIfInit = 1;
    }
    // set control flag
    void SetCon(int nPosCon, int nMdZMP, int nFftFB, int nGRFC, int nComp) {
        this->m_nPosCon = nPosCon, this->m_nMdZMP = nMdZMP, this->m_nFftFB = nFftFB, this->m_nGRFC = nGRFC, this->m_nComp = nComp;
    }
    // reset the control
    void Reset() {
        memset(&this->m_stPG, 0, sizeof(this->m_stPG));
        memset(&this->m_stRef, 0, sizeof(this->m_stRef));
        memset(&this->m_stSen, 0, sizeof(this->m_stSen));
        memset(&this->m_stErr, 0, sizeof(this->m_stErr));
        memset(&this->m_stCoV, 0, sizeof(this->m_stCoV));
        memset(&this->m_stCmd, 0, sizeof(this->m_stCmd));
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
    inline void On() { this->m_nIfConOn = 1; }
    inline void Off() { this->m_nIfConOn = 0; }
private:
    st_DHdConData m_stPG, m_stRef, m_stSen, m_stErr, m_stCoV, m_stCmd;
    st_DHdConGains * m_stGains;
    st_Filters * m_stFilters;
    st_DHdConIO * m_stIO;
    st_RobotConfig * m_stRobConfig;
    int m_nPosCon, m_nMdZMP, m_nFftFB, m_nGRFC, m_nComp; // singal control flag
    int m_nIfInit, m_nIfConOn; // init flag and total control flag
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
            break;
        case __y: // to _rl
            return -1.0;
            break;
        case _rl: // to __y
            return -1.0;
            break;
        case _pt: // to __x
            return 1.0;
            break;
        default:
            return 1.0;
        }
    }
    // transpose the rotational to positional cite number and vise versa
    inline int fnnEulerNum(int nIn) { 
        if(nIn < _ya && nIn != __z) return (__z + __z - nIn);
        return nIn;
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
            for(int i = _rl; i < _pt; i++) cmd.Base[i] += con.Base[i];
            return true;
        }
        return false;
    }
    // calculate the support polygon region
    bool fnbCalSupPolyPG() { 
        auto &cfg = this->m_stRobConfig;
        switch(this->m_stIO->SupSignal) {
        case DSup: // double leg support phase
            m_dSubPoly_B[0] = __MinOf((this->m_stPG.Ank.L.B[__x] - cfg->FootGeom[1]), (this->m_stPG.Ank.R.B[__x] - cfg->FootGeom[1]));
            m_dSubPoly_B[1] = __MaxOf((this->m_stPG.Ank.L.B[__x] + cfg->FootGeom[0]), (this->m_stPG.Ank.R.B[__x] + cfg->FootGeom[0]));
            m_dSubPoly_B[2] = m_stPG.Ank.R.B[__y] - cfg->FootGeom[3];
            m_dSubPoly_B[3] = m_stPG.Ank.L.B[__y] + cfg->FootGeom[3];
            break;
        case LSup: // left leg support phase
            m_dSubPoly_B[0] = this->m_stPG.Ank.L.B[__x] - cfg->FootGeom[1];
            m_dSubPoly_B[1] = this->m_stPG.Ank.L.B[__x] + cfg->FootGeom[0];
            m_dSubPoly_B[2] = this->m_stPG.Ank.L.B[__y] - cfg->FootGeom[2];
            m_dSubPoly_B[3] = this->m_stPG.Ank.L.B[__y] + cfg->FootGeom[3];
            break;
        case RSup: // right leg support phase
            m_dSubPoly_B[0] = this->m_stPG.Ank.R.B[__x] - cfg->FootGeom[1];
            m_dSubPoly_B[1] = this->m_stPG.Ank.R.B[__x] + cfg->FootGeom[0];
            m_dSubPoly_B[2] = this->m_stPG.Ank.R.B[__y] - cfg->FootGeom[3];
            m_dSubPoly_B[3] = this->m_stPG.Ank.R.B[__y] + cfg->FootGeom[2];
            break;
        default: // fly phase or other
            memset(m_dSubPoly_B, 0, sizeof(m_dSubPoly_B));
            return false;
        }
        return true;
    }
    // calculate the moment limitation due to the foot region
    bool fnbCalMStabLimitPG() { 
        auto &cfg = this->m_stRobConfig;
        switch(this->m_stIO->SupSignal) {
        case DSup: // double leg support phase
            m_dMStabLimit[0] = -cfg->FootGeom[3] * cfg->Mass * __Gravity;
            m_dMStabLimit[1] = cfg->FootGeom[3] * cfg->Mass * __Gravity;
            break;
        case LSup: // left leg support phase
            m_dMStabLimit[0] = -cfg->FootGeom[2] * cfg->Mass * __Gravity;
            m_dMStabLimit[1] = cfg->FootGeom[3] * cfg->Mass * __Gravity;
            break;
        case RSup: // right leg support phase
            m_dMStabLimit[0] = -cfg->FootGeom[3] * cfg->Mass * __Gravity;
            m_dMStabLimit[1] = cfg->FootGeom[2] * cfg->Mass * __Gravity;
            break;
        default: // fly phase or other
            memset(m_dMStabLimit, 0, sizeof(m_dMStabLimit));
            return false;
        }
        m_dMStabLimit[2] = -cfg->FootGeom[0] * cfg->Mass * __Gravity;
        m_dMStabLimit[3] = cfg->FootGeom[1] * cfg->Mass * __Gravity;
        return true;
    }
    // calculate the CoM error using simple direct reading state estimate method
    bool fnbCalCoMErr() { 
        auto &ref = this->m_stRef, &sen = this->m_stSen, &con = this->m_stCoV, &err = this->m_stErr;
        auto &cfg = this->m_stRobConfig;
        for(int i = _rl; i <= _pt; i++ ) {
            err.Base[i] = sen.Base[i] - ref.Base[i] - con.Base[i]; // calculate posture error
            err.dBase[i] = sen.dBase[i] - ref.dBase[i] - con.dBase[i]; // calculate posture rate error
            err.Base[this->fnnEulerNum(i)] = this->fnbEulerSign(i) * cfg->Zc * sin(err.Base[i]); // calculate the CoM error
            err.dBase[this->fnnEulerNum(i)] = this->fnbEulerSign(i) * cfg->Zc * sin(err.dBase[i]); // calculate the CoM rate error
        }
        return true;
    }
    // calculate the footft error
    bool fnbCalFftErr() { 
        auto &ref = this->m_stRef, &sen = this->m_stSen, &err = this->m_stErr;
        for(int i = __x; i <= _ya; i++) err.Fft.L.B[i] = sen.Fft.L.B[i] - ref.Fft.L.B[i], err.Fft.L.B[i] =  sen.Fft.R.B[i] - ref.Fft.R.B[i];
        return true;
    }
    // calculate the feedback moment to stablize the CoM and CoM rate error
    bool fnbCalMStabFB() { 
        double dLagTSplit = 0.1;
        auto &err = this->m_stErr;
        auto &kp = this->m_stGains->CalMStab[0], &kd = this->m_stGains->CalMStab[1];
        this->fnbCalMStabLimitPG();
        this->fnbCalCoMErr();
        // calculate Mfeet, Mmdzmp and Mstab
        for(int i = _rl; i <= _pt; i++) this->m_dMStab[i] = this->fnbEulerSign(i) * (kp * err.Base[this->fnnEulerNum(i)] + kd * err.dBase[this->fnnEulerNum(i)]); // calculate the stablize moment
        this->m_dMFeet[_rl] = fndAddLimit(this->m_dMStab[_rl], 0.0, &this->m_dMMdZMP[_rl], this->m_dMStabLimit);
        this->m_dMFeet[_pt] = fndAddLimit(this->m_dMStab[_pt], 0.0, &this->m_dMMdZMP[_pt], this->m_dMStabLimit + 2);
        this->m_dMFeet[__z] = 0.5 * this->m_dMFeet[_rl] / this->m_stRobConfig->AnkWidth; // left foot positive, Todo[more accurate split]
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
        static double dMdZMPBase[6], dMdZMPddBase[6], dMdZMPdBase[6];
        this->fnbCalMStabFB();
        for(int i = __x; i <= __y; i++) {
            dMdZMPddBase[i] = -this->fnbEulerSign(i) * this->m_dMPend[this->fnnEulerNum(i)] / cfg->UpperMass / cfg->Zc - kp_pos * dMdZMPBase[i] - kd_pos * dMdZMPdBase[i];
            dMdZMPddBase[this->fnnEulerNum(i)] = -this->m_dMWheel[this->fnnEulerNum(i)] / cfg->UpperIner - kp_rot * dMdZMPBase[this->fnnEulerNum(i)] - kd_pos * dMdZMPdBase[this->fnnEulerNum(i)];
            fnvIntergAccLimit(&dMdZMPBase[i], &dMdZMPdBase[i], dMdZMPddBase[i], dLimit_pos, cfg->Tc);
            fnvIntergAccLimit(&dMdZMPBase[this->fnnEulerNum(i)], &dMdZMPdBase[this->fnnEulerNum(i)], dMdZMPddBase[this->fnnEulerNum(i)], dLimit_rot, cfg->Tc);
        }
        if(nIfCon) {
            for(int i = __x; i < __y; i++) cmd.Base[i] += dMdZMPBase[i], ref.Base[this->fnnEulerNum(i)] += dMdZMPBase[this->fnnEulerNum(i)];
            return true;
        }
        return false;
    }
    // split the feedback moment to each foot and add them to the reference
    bool fnbAddFftFb(int nIfCon) { 
        double dFzAmp = 1.0;
        auto &dIfCon = (double)nIfCon;
        auto &pg = this->m_stPG, &ref = this->m_stRef, &sen = this->m_stSen;
        double dAlphaL;
        if(this->fnnIfTD()) dAlphaL = sen.Fft.L.B[__z] / (sen.Fft.L.B[__z] + sen.Fft.R.B[__z]); // calculate the split rate for the feedback force
        else dAlphaL = 0.5; // if fly
        double dAlphaR = 1.0 - dAlphaL;
        dAlphaL *= dIfCon, dAlphaR *= dIfCon, dFzAmp *= dIfCon; // check if feedback control is triggered Todo[these 3 val add filter]
        memset(ref.Fft.L.B, 0, sizeof(ref.Fft.L.B)), memset(ref.Fft.R.B, 0, sizeof(ref.Fft.R.B)); // init referenced footft every control circle
        ref.Fft.L.B[__z] = pg.Fft.L.B[__z], ref.Fft.R.B[__z] = pg.Fft.R.B[__z]; // init referenced footft z
        if(this->fnnIfTD()) { // add feedback force when the robot touch down
            switch(this->m_stIO->SupSignal) {
            case DSup: // double leg support phase
                if(this->fnnIfLTD()) for(int i = _rl; i < _pt; i++) ref.Fft.L.B[i] = pg.Fft.L.B[i] + dAlphaL * this->m_dMStab[i];
                if(this->fnnIfRTD()) for(int i = _rl; i < _pt; i++) ref.Fft.R.B[i] = pg.Fft.R.B[i] + dAlphaR * this->m_dMStab[i];
                ref.Fft.L.B[__z] += dFzAmp * this->m_dMFeet[__z];
                ref.Fft.R.B[__z] -= dFzAmp * this->m_dMFeet[__z];
                break;
            case LSup: // left leg support phase
                if(this->fnnIfLTD()) for(int i = _rl; i < _pt; i++) ref.Fft.L.B[i] = pg.Fft.L.B[i] + dAlphaL * this->m_dMStab[i];
                break;
            case RSup: // right leg support phase
                if(this->fnnIfRTD()) for(int i = _rl; i < _pt; i++) ref.Fft.R.B[i] = pg.Fft.R.B[i] + dAlphaR * this->m_dMStab[i];
                break;
            default: // fly
                ref.Fft.L.B[__z] = ref.Fft.R.B[__z] = 0.0;
                break;
            }
        }
        return nIfCon;
    }
    // the ground reaction force control, simple compliance if the feedback moment is not applied
    bool fnbGRFC(int nIfCon) { 
        double dlimit_z[6] = { -0.0 * 0.02, 0.04, -10.0, 10.0, -2500.0, 2500.0 }, dLimit_r[4] = { -__D2R(15.0), __D2R(15.0), -60.0, 60.0 };
        double dThresh_z[2] = { -10.0, 10.0 }, dThresh_r[2] = { -1.0, 1.0 };
        auto &ga = this->m_stGains;
        auto &kfz = ga->GRFC[0], &kpz = ga->GRFC[1], &kdz = ga->GRFC[2], &kvcz = ga->GRFC[3], &kacz = ga->GRFC[4], &kdfz = ga->GRFC[5], &kdfcz = ga->GRFC[6], &kfr = ga->GRFC[7], &kpr = ga->GRFC[8];
        auto &con = this->m_stCoV, &err = this->m_stErr, &cmd = this->m_stCmd;
        auto &Tc = this->m_stRobConfig->Tc;
        static double dFzLErr, dFzRErr, dFzLdErr, dFzRdErr;
        this->fnbCalFftErr();
        // calculate compliance z
        dFzLdErr = (err.Fft.L.B[__z] - dFzLErr) / Tc, dFzRdErr = (err.Fft.R.B[__z] - dFzRErr) / Tc;
        con.ddAnk.L.B[__z] = kfz * fndThreshold(err.Fft.L.B[__z], dThresh_z) - kpz * con.Ank.L.B[__z] - kdz * con.dAnk.L.B[__z] + kvcz * con.dAnk.R.B[__z] + kacz * con.ddAnk.R.B[__z] + kdfz * dFzLdErr + kdfcz * dFzRdErr;
        con.ddAnk.R.B[__z] = kfz * fndThreshold(err.Fft.R.B[__z], dThresh_z) - kpz * con.Ank.R.B[__z] - kdz * con.dAnk.R.B[__z] + kvcz * con.dAnk.L.B[__z] + kacz * con.ddAnk.L.B[__z] + kdfz * dFzRdErr + kdfcz * dFzLdErr;
        dFzLErr = err.Fft.L.B[__z], dFzRErr = err.Fft.R.B[__z];
        fnvIntergAccLimit(&con.Ank.L.B[__z], &con.dAnk.L.B[__z], con.ddAnk.L.B[__z], dlimit_z, Tc);
        fnvIntergAccLimit(&con.Ank.R.B[__z], &con.dAnk.R.B[__z], con.ddAnk.R.B[__z], dlimit_z, Tc);
        // calculate dAnk pitch and roll
        for(int i = _rl; i <= _pt; i++) {
            con.dAnk.L.B[i] = kfr * fndThreshold(err.Fft.L.B[i], dThresh_r) - kpr * con.Ank.L.B[i];
            con.dAnk.R.B[i] = kfr * fndThreshold(err.Fft.R.B[i], dThresh_r) - kpr * con.Ank.R.B[i];
            fnvIntergVeloLimit(&con.Ank.L.B[i], con.dAnk.L.B[i], dLimit_r, Tc);
            fnvIntergVeloLimit(&con.Ank.R.B[i], con.dAnk.R.B[i], dLimit_r, Tc);
        }
        if(nIfCon) {
            for(int i = __x; i <= _ya; i++) cmd.Ank.L.W[i] += con.Ank.L.B[i], cmd.Ank.R.W[i] += con.Ank.R.B[i];
            return true;
        }
        return false;
    }
    // simple compliance control to absorb the impact
    bool fnvCompliance(int nIfCon) {
        double dLimit[4] = { -__D2R(5.0), __D2R(5.0), -60.0, 60.0 };
        auto &kf = this->m_stGains->Compliance[0], &kp = this->m_stGains->Compliance[1];
        static double AnkL[6], AnkR[6], dAnkL[6], dAnkR[6];
        auto &sen = this->m_stSen, &cmd = this->m_stCmd;
        for(int i = _rl; i <= _pt; i++) {
            dAnkL[i] = kf * sen.Fft.L.B[i] - kp * AnkL[i];
            dAnkR[i] = kf * sen.Fft.R.B[i] - kp * AnkR[i];
            fnvIntergVeloLimit(&AnkL[i], dAnkL[i], dLimit, this->m_stRobConfig->Tc);
            fnvIntergVeloLimit(&AnkR[i], dAnkR[i], dLimit, this->m_stRobConfig->Tc);
        }
        if(nIfCon) {
            for(int i = _rl; i <= _pt; i++) cmd.Ank.L.B[i] += AnkL[i], cmd.Ank.R.B[i] += AnkR[i]; 
            return true;
        }
        return false;
    }
    // read pg trajectory and reference
    bool fnbGetTra() {
        auto &pg = this->m_stPG, &ref = this->m_stRef, &cmd = this->m_stCmd;
        auto &io = this->m_stIO;
        for(int i = __x; i <= _ya; i++) {
            cmd.Base[i]     = pg.Base[i]        = io->BasePG[i];
            cmd.Ank.L.W[i]  = pg.Ank.L.W[i]     = io->LAnkPG_W[i];
            cmd.Ank.R.W[i]  = pg.Ank.R.W[i]     = io->RAnkPG_W[i];
            pg.Fft.L.B[i]   = io->LFTPG_B[i];
            pg.Fft.R.B[i]   = io->RFTPG_B[i];
        }
        for(int i = _rl; i <= _pt; i++) ref.Base[i] = pg.Base[i];
        return true;
    }
    // read sensors data
    bool fnbGetSen() {
        auto &sen = this->m_stSen;
        auto &io = this->m_stIO;
        auto &filter = this->m_stFilters;
        auto &Tc = this->m_stRobConfig->Tc;
        static int nIfFirst = 1;
        if(nIfFirst) {
            for(int i = _rl; i <= _pt; i++) sen.Base[i] = io->IMUSen[this->fnnEulerNum(i)];
            nIfFirst = 0;
        }
        for(int i = _rl; i <= _pt; i++) {
            sen.dBase[i] = fndFilterTimeLag(sen.dBase[i], (io->IMUSen[this->fnnEulerNum(i)] - sen.Base[i]) / Tc, Tc, filter->TLagGro); // Todo[filter maybe wrong]
            sen.Base[i] =  fndFilterTimeLag(sen.Base[i], io->IMUSen[this->fnnEulerNum(i)], Tc, filter->TLagIMU);
        }
        for(int i = __x; i <= __z; i++) {
            sen.Fft.L.B[i] = fndFilterTimeLag(sen.Fft.L.B[i], io->LFTSen_B[i], Tc, filter->TLagFrc);
            sen.Fft.R.B[i] = fndFilterTimeLag(sen.Fft.R.B[i], io->RFTSen_B[i], Tc, filter->TLagFrc);
        }
        for(int i = _rl; i <= _pt; i++) {
            sen.Fft.L.B[i] = fndFilterTimeLag(sen.Fft.L.B[i], io->LFTSen_B[i], Tc, filter->TLagTrq);
            sen.Fft.R.B[i] = fndFilterTimeLag(sen.Fft.R.B[i], io->RFTSen_B[i], Tc, filter->TLagTrq);
        }
        return true;
    }
    // get the control value
    bool fnbGetConV() {
        this->fnbUpperPosCon(this->m_nPosCon);
        this->fnbMdZMPCon(this->m_nMdZMP);
        this->fnbAddFftFb(this->m_nFftFB);
        this->fnbGRFC(this->m_nGRFC);
        this->fnvCompliance(this->m_nComp);
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
        return true;
    }
};

_D_CONTROL_END

#endif