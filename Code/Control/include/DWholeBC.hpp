// DWholeBC.h
// 20230217 dcc <3120195094@bit.edu.cn>
/*支持两种WBC：
1）轨迹规划：将WBC更新的sta给SD当成真实值算rel，用ref和rel做反馈控制，得到con，通过优化得到ddq，积分更新WBC的sta；
2）在线控制：将从仿真、实际机器人本体估计得到的真实sta给SD算rel，用ref和rel做反馈控制得到con， 优化得到ddq后，积分更新WBC的sta
*/ 
#pragma once
#ifndef DWHOLEBC_H
#define DWHOLEBC_H
#include "ControlHeaders.h"

_D_CONTROL_BEGIN
_D_USING_SDT

struct st_Target {
    double c[3]; // [x, y, z]
    double dc[3]; // [x, y, z]
    double pos[3]; // [rx, ry, rz]
    double dpos[3]; // [rx, ry, rz]
    double h[6]; // [x, y, z, rx, ry, rz]
    double dh[6]; // [x, y, z, rx, ry, rz]
    double Ank[2][6]; // [L, R][x, y, z, rx, ry, rz]
    double dAnk[2][6]; // [L, R][x, y, z, rx, ry, rz]
    double ddAnk[2][6]; // [L, R][x, y, z, rx, ry, rz]
};

// state seq: trunk [z, y, x, rz, ry, rx], waist yaw, L arm, R arm, L leg [1-6], R leg [1-6]
struct st_WBCData {
    struct { // state
        double q[__DoFNum];
        double dq[__DoFNum];
    }sta;       
    st_Target ref;
    st_Target rel;        
    struct { // conval
        double dh_ref[6];
        double ddAnk_ref[2][6];
    }con;        
    double ddq[__JointNum]; // optival:
};

struct st_CalcuDat {
    double H[__DoFNum][__DoFNum];
    double f[__DoFNum];
};

struct st_Gains {
    double dh[3][6]; // [x/rx, y/ry, z/rz][kl, kc, kdc, kk, kpos, kdpos]
    double ddAnk[3][4]; // [x/rx, y/ry, z/rz][kp, kd, krp, krd]
};

#define _SD     c_SDCalcu::

class c_WholeBC:protected c_SDCalcu {
public:
    int nInited = 0;
    inline c_WholeBC(st_WBCData * stDataIn, tp_stSDMech * stptMechIn, st_Gains * stptGainsIn, double dTimeIn):c_SDCalcu(stptMechIn, &this->m_stSDState, dTimeIn) {
        this->m_stptWBCDat = stDataIn;
        this->m_stptMech = stptMechIn;
        this->m_stGains = stptGainsIn;
        this->dTime = dTimeIn;
    }
    inline ~c_WholeBC() {

    }
    bool fnbInit(double dQInitIn[__DoFNum]) {
        if(this->nInited) return false; // only init once
        memset(this->m_stptWBCDat, 0, sizeof(st_WBCData)); // clear all the states
        memset(&this->m_stCalcu, 0, sizeof(st_CalcuDat)); // clear all the calculation matrix
        this->_SD fnbInitState(dQInitIn); // init sdfast
        for(int i = 0; i < __DoFNum; i++) this->m_stptWBCDat->sta.q[i] = dQInitIn[i], this->m_stptWBCDat->sta.dq[i] = 0.0; // init state of WBC
        this->nInited = 1; // set init flag
        return true;
    }
    bool fnbUpdateWBC(double dSensQIn[__DoFNum], double dSensUIn[__DoFNum], st_Target stRefIn, double dCmdJointsOut[__JointNum]) {
        this->fnbGetRef(stRefIn); // update refence states
        this->fnbUpdateSD(dSensQIn, dSensUIn); // update SDFAST
        this->fnbGetRel(); // update real states from SDFAST
        this->fnbControllers(); // get conval
        this->fnbUpdateConval(); // get ddq
        this->fnbUpdateJoint(dCmdJointsOut);
        return true;
    }
    void fnvShowCoM() {
        this->_SD fnbDisp(CoM);
    }
    void fnvShowAnk() {
        this->_SD fnbDisp(Ank);
    }
private:
    st_WBCData * m_stptWBCDat;
    st_CalcuDat m_stCalcu;
    tp_stSDMech * m_stptMech;
    tp_stSDState m_stSDState;
    st_Gains * m_stGains;
    double dTime;    
    bool fnbGetRef(st_Target stRefIn) {
        this->m_stptWBCDat->ref = stRefIn; // get reference from upper level
        return true;
    }
    bool fnbUpdateSD(double dQIn[__DoFNum], double dUIn[__DoFNum]) {
        // this->_SD fnbSetState(dQIn, dUIn); // update state for sdfast by sens state
        this->_SD fnbSetState(this->m_stptWBCDat->sta.q, this->m_stptWBCDat->sta.dq); // for test 1）
        this->_SD fnbUpdateFK(); // update calculate data
        return true;
    }
    bool fnbGetRel() {
        for(int i = 0; i < 2; i++) for(int j = 0; j < 6; j++) 
            this->m_stptWBCDat->rel.Ank[i][j] = this->m_stSDState.dAnk[i][j],
            this->m_stptWBCDat->rel.dAnk[i][j] = this->m_stSDState.ddAnk[i][j];
        for(int i = 0; i < 3; i++) 
            this->m_stptWBCDat->rel.c[i] = this->m_stSDState.dCoM[i],
            this->m_stptWBCDat->rel.dc[i] = this->m_stSDState.ddCoM[i],
            this->m_stptWBCDat->ref.h[i] = this->m_stSDState.dMom[i], this->m_stptWBCDat->ref.h[3 + i] = this->m_stSDState.dMom[3 + i];
        return true;
    }
    bool fnbControllers() {
        for(int i = 0; i < 2; i++) for(int j = 0; j < 3; j++) // ankle position and orientation controller
        this->m_stptWBCDat->con.ddAnk_ref[i][j] = this->m_stptWBCDat->ref.ddAnk[i][j]                                                                               // feedforward
                                                + this->m_stGains->ddAnk[j][0] * (this->m_stptWBCDat->ref.Ank[i][j]  - this->m_stptWBCDat->rel.Ank[i][j])           // kp
                                                + this->m_stGains->ddAnk[j][1] * (this->m_stptWBCDat->ref.dAnk[i][j] - this->m_stptWBCDat->rel.dAnk[i][j]),         // kd  
        this->m_stptWBCDat->con.ddAnk_ref[i][3 + j] = this->m_stptWBCDat->ref.ddAnk[i][3 + j]                                                                       // feedforward
                                                + this->m_stGains->ddAnk[j][2] * (this->m_stptWBCDat->ref.Ank[i][3 + j]  - this->m_stptWBCDat->rel.Ank[i][3 + j])   // krp
                                                + this->m_stGains->ddAnk[j][3] * (this->m_stptWBCDat->ref.dAnk[i][3 + j] - this->m_stptWBCDat->rel.dAnk[i][3 + j]); // krd   
        for(int i = 0; i < 3; i++)
        this->m_stptWBCDat->con.dh_ref[i] = this->m_stptWBCDat->ref.dh[i]                                                                       // feedforward
                                        + this->m_stGains->dh[i][0] * (this->m_stptWBCDat->ref.h[i]  - this->m_stptWBCDat->rel.h[i])            // kh  
                                        + this->m_stGains->dh[i][1] * (this->m_stptWBCDat->ref.c[i]  - this->m_stptWBCDat->rel.c[i])            // kc
                                        + this->m_stGains->dh[i][2] * (this->m_stptWBCDat->ref.dc[i] - this->m_stptWBCDat->rel.dc[i]),          // kdc
        this->m_stptWBCDat->con.dh_ref[3 + i] = this->m_stptWBCDat->ref.dh[3 + i]                                                               // feedforward
                                        + this->m_stGains->dh[i][3] * (this->m_stptWBCDat->ref.h[3 + i]  - this->m_stptWBCDat->rel.h[3 + i])    // kh  
                                        + this->m_stGains->dh[i][4] * (this->m_stptWBCDat->ref.pos[i]  - this->m_stptWBCDat->rel.pos[i])        // kc
                                        + this->m_stGains->dh[i][5] * (this->m_stptWBCDat->ref.dpos[i] - this->m_stptWBCDat->rel.dpos[i]);      // kdc
        return true;
    }
    bool fnbUpdateConval() {
        for(int i = 0; i < __DoFNum; i++) this->m_stptWBCDat->ddq[i] = 0.0; // for test
        return true;
    }
    bool fnbUpdateJoint(double dCmdJointsOut[__JointNum]) {
        for(int i = 0; i < __DoFNum; i++) this->m_stptWBCDat->sta.dq[i] += this->m_stptWBCDat->ddq[i] * this->dTime; // intergrate dq
        for(int i = 0; i < __DoFNum; i++) this->m_stptWBCDat->sta.q[i] += this->m_stptWBCDat->sta.dq[i] * this->dTime; // intergrate q
        for(int i = 0; i < __JointNum; i++) dCmdJointsOut[i] = this->m_stptWBCDat->sta.q[6 + i];
        return true;
    }
};

_D_CONTROL_END

#endif