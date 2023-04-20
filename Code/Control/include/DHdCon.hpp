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

struct st_RobotConfig{
    double Tc; 
    double Mass;
    double UpperMass;
    double UpperIner;
    double Zc; // height of the nominal CoM
    double AnkWidth;
    double AnkHeight;
    double FootGeom[4]; // positive: forw, back, iner, outer
};

struct st_DHdConData{
    double Base[6]; // Base position and posture in world frame [x, y, z, rx, ry, rz]
    double dBase[6]; // Base position and posture rate in world frame [x, y, z, rx, ry, rz]
    double ddBase[6]; // Base position and posture acc in world frame [x, y, z, rx, ry, rz]
    struct {
        double B[2]; // ZMP in base frame [x, y]
        double W[2]; // ZMP in world frame [x, y]
    }ZMP;
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

struct st_DHdConIO{
    // input
    double BasePG[6]; // pattern generated base position and posture [x, y, z, rx, ry, rz]
    double ZMPPG_W[2]; // pattern generated ZMP in world frame [x, y]
    double LAnkPG_W[6]; // pattern generated left ankle position and posture in world frame [x, y, z, rx, ry, rz]
    double RAnkPG_W[6]; // pattern generated right ankle position and posture in world frame [x, y, z, rx, ry, rz]
    double LFTPG_B[6]; // left reference foot contact force and torque in base frame [fx, fy, fz, tx, ty, tz]
    double RFTPG_B[6]; // right reference foot contact force and torque in base frame [fx, fy, fz, tx, ty, tz]
    double IMUSen[2]; // sensed IMU data [rx, ry]
    double ZMPSen_B[2]; // sensed ZMP in body frame [x, y]
    int SupSignal;
    int PressKey;
    // output
    double BaseCmd[6]; // commanded base position and posture [x, y, z, rx, ry, rz]
    double LAnkCmd_W[6]; // commanded left ankle position and posture in world frame [x, y, z, rx, ry, rz]
    double RAnkCmd_W[6]; // commanded right ankle position and posture in world frame [x, y, z, rx, ry, rz]
};

struct st_DHdConGains{
    double UpperPos[3]; // [k_posture, kp, kd]
    double CalMStab[2]; // [kp, kd]
    double MdZMP[2]; // [kp_pos, kd_pos, kp_rot, kd_rot]
    double GRFC[18];
    double TrqBias[2];
};

class c_DHcCon {
public:
    inline c_DHcCon(st_DHdConIO * stConIO, st_DHdConGains * stDHdConGains, st_RobotConfig * stRobConfig) {
        this->m_stIO = stConIO;
        this->m_stGains = stDHdConGains;
        this->m_stRobConfig = stRobConfig;
    }
    inline ~c_DHcCon() {
        
    }
private:
    st_DHdConData m_stPG, m_stRef, m_stSen, m_stErr, m_stCoV, m_stCmd;
    st_DHdConGains * m_stGains;
    st_DHdConIO * m_stIO;
    st_RobotConfig * m_stRobConfig;
    double m_dSubPoly_B[4]; // [-x, x, -y, y]
    double m_dMStabLimit[4]; // [-tx, tx, -ty, ty]
    double m_dMStab[6], m_dMFeet[6], m_dMMdZMP[6], m_dMPend[6], m_dMWheel[6];
    double m_dMdZMPBase[6], m_dMdZMPdBase[6], m_dMdZMPddBase[6];
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
    inline int fnnEulerNum(int nIn) { // transpose the rotational to positional cite number and vise versa
        if(nIn < _ya && nIn != __z) return (__z + __z - nIn);
        return nIn;
    }
    bool fnbUpperPosCon(int nIfCon) { // upper body posture control of the robot to make the robot behave more like a LIPM
        double dLimit[6] = { -__D2R(15.0), __D2R(15.0), -100.0, 100.0, -50.0, 50.0 };
        static double BasePosCon[6] = { 0.0 }, dBasePosCon[6] = { 0.0 }, ddBasePosCon[6] = { 0.0 };
        auto k_posture = this->m_stGains->UpperPos[0], kp = this->m_stGains->UpperPos[1], kd = this->m_stGains->UpperPos[2];
        auto ref = this->m_stRef, sen = this->m_stSen, con = this->m_stCoV;
        for(int i = _rl; i < _pt; i++) {
            ddBasePosCon[i] = this->fndIfTD() * k_posture * (ref.Base[i] - sen.Base[i]) - kp * BasePosCon[i] - kd * dBasePosCon[i];
            fnvIntegAccLimit(&BasePosCon[i], &dBasePosCon[i], ddBasePosCon[i], dLimit, this->m_stRobConfig->Tc);
        }
        if(nIfCon) {
            for(int i = _rl; i < _pt; i++) con.Base[i] = BasePosCon[i];
            return true;
        }
        return false;
    }
    bool fnbCalSupPolyPG() { // calculate the support polygon region
        auto cfg = this->m_stRobConfig;
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
    bool fnbCalMStabLimitPG() { // calculate the moment limitation due to the foot region
        auto cfg = this->m_stRobConfig;
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
    bool fnbCalCoMErr() { // calculate the CoM error using simple direct reading state estimate method
        auto ref = this->m_stRef, sen = this->m_stSen, con = this->m_stCoV, err = this->m_stErr;
        auto cfg = this->m_stRobConfig;
        for(int i = _rl; i < _pt; i++ ) {
            err.Base[i] = sen.Base[i] - ref.Base[i] - con.Base[i]; // calculate posture error
            err.dBase[i] = sen.dBase[i] - ref.dBase[i] - con.dBase[i]; // calculate posture rate error
            err.Base[this->fnnEulerNum(i)] = this->fnbEulerSign(i) * cfg->Zc * sin(err.Base[i]); // calculate the CoM error
            err.dBase[this->fnnEulerNum(i)] = this->fnbEulerSign(i) * cfg->Zc * sin(err.dBase[i]); // calculate the CoM rate error
        }
        return true;
    }
    bool fnbCalMStabFB() { // calculate the feedback moment to stablize the CoM and CoM rate error
        double dLagTSplit = 0.1;
        auto err = this->m_stErr;
        auto kp = this->m_stGains->CalMStab[0], kd = this->m_stGains->CalMStab[1];
        // calculate Mfeet, Mmdzmp and Mstab
        for(int i = _rl; i < _pt; i++) this->m_dMStab[i] = this->fnbEulerSign(i) * (kp * err.Base[this->fnnEulerNum(i)] + kd * err.dBase[this->fnnEulerNum(i)]); // calculate the stablize moment
        this->m_dMFeet[_rl] = fndAddLimit(this->m_dMStab[_rl], 0.0, &this->m_dMMdZMP[_rl], this->m_dMStabLimit);
        this->m_dMFeet[_pt] = fndAddLimit(this->m_dMStab[_pt], 0.0, &this->m_dMMdZMP[_pt], this->m_dMStabLimit + 2);
        this->m_dMFeet[__z] = 0.5 * this->m_dMFeet[_rl] / this->m_stRobConfig->AnkWidth; // left foot positive, Todo[more accurate split]
        // calculate Mpend and Mwheel by spliting Mmdzmp
        for(int i = _rl; i < _pt; i++) {
            this->m_dMPend[i] = fndFilterTimeLag(this->m_dMPend[i], this->m_dMMdZMP[i], this->m_stRobConfig->Tc, dLagTSplit);
            this->m_dMWheel[i] = this->m_dMMdZMP[i] - this->m_dMPend[i];
        }
        return true;
    }
    bool fnbMdZMPCon(int nIfCon) { // calculate the positional and rotational control value of model ZMP
        double dLimit_pos[6] = { -0.03, 0.03, -10.0, 10.0, -2500.0, 2500.0 };
        double dLimit_rot[6] = { -0.03 * 6.0, 0.03 * 6.0, -10.0 * 6.0, 10.0 * 6.0, -2500.0 * 6.0, 2500.0 * 6.0 };
        auto kp_pos = this->m_stGains->MdZMP[0], kd_pos = this->m_stGains->MdZMP[1], kp_rot = this->m_stGains->MdZMP[2], kd_rot = this->m_stGains->MdZMP[3];
        auto con = this->m_stCoV;
        auto cfg = this->m_stRobConfig;
        for(int i = __x; i < __y; i++) {
            m_dMdZMPddBase[i] = -this->fnbEulerSign(i) * this->m_dMPend[this->fnnEulerNum(i)] / cfg->UpperMass / cfg->Zc - kp_pos * m_dMdZMPBase[i] - kd_pos * m_dMdZMPdBase[i];
            m_dMdZMPddBase[this->fnnEulerNum(i)] = -this->m_dMWheel[this->fnnEulerNum(i)] / cfg->UpperIner - kp_rot * m_dMdZMPBase[this->fnnEulerNum(i)] - kd_pos * m_dMdZMPdBase[this->fnnEulerNum(i)];
            fnvIntegAccLimit(&m_dMdZMPBase[i], &m_dMdZMPdBase[i], m_dMdZMPddBase[i], dLimit_pos, cfg->Tc);
            fnvIntegAccLimit(&m_dMdZMPBase[this->fnnEulerNum(i)], &m_dMdZMPdBase[this->fnnEulerNum(i)], m_dMdZMPddBase[this->fnnEulerNum(i)], dLimit_rot, cfg->Tc);
        }
        if(nIfCon) {
            for(int i = __x; i < __y; i++) con.Base[i] = m_dMdZMPBase[i], con.Base[this->fnnEulerNum(i)] += m_dMdZMPBase[this->fnnEulerNum(i)];
            return true;
        }
        return false;
    }
    bool fnbAddFftFb(int nIfCon) { // split the feedback moment to each foot and add them to the reference
        double dFzAmp = 1.0;
        auto dIfCon = (double)nIfCon;
        auto pg = this->m_stPG, ref = this->m_stRef, sen = this->m_stSen;
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

};

_D_CONTROL_END

#endif