// DWholeBC.h
// 20230217 dcc <3120195094@bit.edu.cn>
/*支持两种WBC：
1）轨迹规划：将WBC更新的sta给SD当成真实值算rel，用ref和rel做反馈控制，得到con，通过优化得到ddq，积分更新WBC的sta；
2）在线控制：将从仿真、实际机器人身上估计得到的真实sta给SD算rel，用ref和rel做反馈控制得到con， 优化得到ddq后，积分更新WBC的sta
*/ 
#pragma once
#ifndef DWHOLEBC_H
#define DWHOLEBC_H
#include "ControlHeaders.h"

_D_CONTROL_BEGIN
_D_USING_SDT

// state seq: trunk [z, y, x, rz, ry, rx], waist yaw, L arm, R arm, L leg [1-6], R leg [1-6]
struct st_WBCData{
    struct { // state
        double q[__DoFNum];
        double dq[__DoFNum];
    }sta;       
    struct { // reference
        double c_ref[3];
        double dc_ref[3];
        double pos_ref[3];
        double dpos_ref[3];
        double h_ref[6];
        double Ank_ref[2][6];
        double dAnk_ref[2][6];
    }ref;        
    struct { // real value:
        double c_rel[3];
        double dc_rel[3];
        double pos_rel[3];
        double dpos_rel[3];
        double h_rel[6];
        double Ank_rel[2][6];
        double dAnk_rel[2][6];
    }rel;        
    struct { // conval
        double dh_ref[6];
        double ddAnk_ref[2][6];
    }con;        
    double ddq[__JointNum]; // optival:
};

struct st_CalcuDat{
    double H[__DoFNum][__DoFNum];
    double f[__DoFNum];
};

#define _SD     c_SDCalcu::

class c_WholeBC:protected c_SDCalcu{
public:
    c_WholeBC(st_WBCData * stDataIn, tp_stSDMech * stptMechIn, double dTimeIn):c_SDCalcu(this->m_stptMech, &this->m_stSDState, dTimeIn) {
        this->m_stptWBCDat = stDataIn;
        this->m_stptMech = stptMechIn;
        this->dTime = dTimeIn;
    }
    ~c_WholeBC() {

    }
    bool fnbInit(double dQInitIn[__DoFNum]) {
        memset(this->m_stptWBCDat, 0, sizeof(st_WBCData));     // clear all the states
        memset(&this->m_stCalcu, 0, sizeof(st_CalcuDat)); // clear all the calculation matrix
        this->_SD fnbInitState(dQInitIn); // init sdfast
        for(int i = 0; i < __DoFNum; i++) this->m_stptWBCDat->sta.q[i] = dQInitIn[i], this->m_stptWBCDat->sta.dq[i] = 0.0; // init state of WBC
        return true;
    }
    bool fnbUpdateSD(double dQIn[__DoFNum], double dUIn[__DoFNum]) {
        this->_SD fnbSetState(dQIn, dUIn); // update state for sdfast by real state
        return true;
    }
    bool fnbUpdateWBC() {
        for(int i = 0; i < __DoFNum; i++) this->m_stptWBCDat->sta.dq[i] += this->m_stptWBCDat->ddq[i] * this->dTime; // intergrate dq
        for(int i = 0; i < __DoFNum; i++) this->m_stptWBCDat->sta.q[i] += this->m_stptWBCDat->sta.dq[i] * this->dTime; // intergrate q
        return true;
    }
    bool fnbGiveRef() {

        return true;
    }
    bool fnbUpdate() {

        return true;
    }
private:
    st_WBCData * m_stptWBCDat;
    st_CalcuDat m_stCalcu;
    tp_stSDMech * m_stptMech;
    tp_stSDState m_stSDState;
    double dTime;
    
};

_D_CONTROL_END

#endif