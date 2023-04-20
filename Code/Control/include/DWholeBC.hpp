// DWholeBC.h
// 20230217 dcc <3120195094@bit.edu.cn>
/*支持两种WBC：
1）轨迹规划：将WBC更新的sta给SD当成真实值算rel，用ref和rel做反馈控制，得到con，通过优化得到ddq，积分更新WBC的sta；
2）在线控制：将从仿真、实际机器人本体估计得到的真实sta给SD算rel，用ref和rel做反馈控制得到con， 优化得到ddq后，积分更新WBC的sta
*/
#pragma once
#ifndef DWHOLEBC_HPP
#define DWHOLEBC_HPP
#include "ControlHeaders.h"

_D_CONTROL_BEGIN
_D_USING_SDT

// hard set parameters
const static double dUrgGain = 1.0;

lee::LEigenQP<__DoFNum,0,0> qp; // init QP

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
    Eigen::Matrix<double, __DoFNum, __DoFNum> H; // mat for QP
    Eigen::Matrix<double, __DoFNum, 1> f; // vec for QP
    Eigen::Matrix<double, __DoFNum, 1> dq; // dq for QP
    Eigen::Matrix<double, 6, __DoFNum> J;
    Eigen::Matrix<double, 6, __DoFNum> dJ;
    Eigen::Matrix<double, 6, 6> w;
    Eigen::Matrix<double, 6, 1> P;
    Eigen::Matrix<double, 6, __DoFNum> wJ;
    Eigen::Matrix<double, 6, 1> _P;
};

struct st_Gains {
    double dh[3][6]; // [x/rx, y/ry, z/rz][kl, kc, kdc, kk, kpos, kdpos]
    double ddAnk[3][4]; // [x/rx, y/ry, z/rz][kp, kd, krp, krd]
    double wh[6]; // weight for momentum tracking [x, y, z, rx, ry, rz]
    double wa[6]; // weight for ankle tracking [x, y, z, rx, ry, rz]
};

#define __DEBUG getchar(); // for test
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
        this->nIsUrg = 0; // clear urg flag
        this->nInited = 1; // set init flag
        return true;
    }
    bool fnbUpdateWBC(double dSensQIn[__DoFNum], double dSensUIn[__DoFNum], st_Target stRefIn, double dCmdJointsOut[__JointNum]) {
        this->fnbGetRef(stRefIn); // update refence states
        fnbUpdateSD(dSensQIn, dSensUIn); // update SDFAST
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
    // for test s ============================
    void fnvShowTrackingErr() {
        double dCoMErr[3], dCoMdErr[3], dPosErr[3], dPosdErr[3], dMomErr[6];
        double dAnkErr[2][6], dAnkdErr[2][6];
        for(int i = 0; i < 6; i++) { // cal ank err
            dAnkErr[0][i] = this->m_stptWBCDat->rel.Ank[0][i] - this->m_stptWBCDat->ref.Ank[0][i], dAnkErr[1][i] = this->m_stptWBCDat->rel.Ank[1][i] - this->m_stptWBCDat->ref.Ank[1][i];
            dAnkdErr[0][i] = this->m_stptWBCDat->rel.dAnk[0][i] - this->m_stptWBCDat->ref.dAnk[0][i], dAnkdErr[1][i] = this->m_stptWBCDat->rel.dAnk[1][i] - this->m_stptWBCDat->ref.dAnk[1][i];
            dMomErr[i] = this->m_stptWBCDat->rel.h[i] - this->m_stptWBCDat->ref.h[i];
        }
        for(int i = 0; i < 3; i++) {
            dCoMErr[i] = this->m_stptWBCDat->rel.c[i] - this->m_stptWBCDat->ref.c[i], dPosErr[i] = this->m_stptWBCDat->rel.pos[i] - this->m_stptWBCDat->ref.pos[i];
            dCoMdErr[i] = this->m_stptWBCDat->rel.dc[i] - this->m_stptWBCDat->ref.dc[i], dPosdErr[i] = this->m_stptWBCDat->rel.dpos[i] - this->m_stptWBCDat->ref.dpos[i];
        }
        printf("CoM Err: "); for(int i = 0; i < 3; i++) printf("%lf, ", dCoMErr[i]); printf("\n");
        printf("dCoM Err: "); for(int i = 0; i < 3; i++) printf("%lf, ", dCoMdErr[i]); printf("\n");
        printf("Pos Err: "); for(int i = 0; i < 3; i++) printf("%lf, ", dPosErr[i]); printf("\n");
        printf("dPos Err: "); for(int i = 0; i < 3; i++) printf("%lf, ", dPosdErr[i]); printf("\n");
        printf("Mom Err: "); for(int i = 0; i < 6; i++) printf("%lf, ", dMomErr[i]); printf("\n");
        printf("LAnk Err: "); for(int i = 0; i < 6; i++) printf("%lf, ", dAnkErr[0][i]); printf("\n");
        printf("RAnk Err: "); for(int i = 0; i < 6; i++) printf("%lf, ", dAnkErr[1][i]); printf("\n");
        printf("LdAnk Err: "); for(int i = 0; i < 6; i++) printf("%lf, ", dAnkdErr[0][i]); printf("\n");
        printf("RdAnk Err: "); for(int i = 0; i < 6; i++) printf("%lf, ", dAnkdErr[1][i]); printf("\n");
    }
    void fnvShowHf() {
        printf("H:\n"); for(int i = 0; i < __DoFNum; i++) { for(int j = 0; j < __DoFNum; j++) printf("%.3lf, ", this->m_stCalcu.H(i, j)); printf("\n"); }printf("\n");
        printf("f:\n"); for(int i = 0; i < __DoFNum; i++) printf("%.3lf, ", this->m_stCalcu.f(i)); printf("\n");
    }
    void fnvShowddq() {
        printf("H:\n"); for(int i = 0; i < __DoFNum; i++) printf("%.3lf, ", this->m_stptWBCDat->ddq[i]); printf("\n");
    }
    void fnvShowCon_dh() {
        printf("dh_ref:\n"); for(int i = 0; i < 6; i++) printf("%.3lf, ", this->m_stptWBCDat->con.dh_ref[i]); printf("\n");
    }
    void fnvShowCon_ddank() {
        printf("Lddank_ref:\n"); for(int i = 0; i < 6; i++) printf("%.3lf, ", this->m_stptWBCDat->con.ddAnk_ref[0][i]); printf("\n");
        printf("Rddank_ref:\n"); for(int i = 0; i < 6; i++) printf("%.3lf, ", this->m_stptWBCDat->con.ddAnk_ref[1][i]); printf("\n");
    }
    // for test e ============================
private:
    st_WBCData * m_stptWBCDat;
    st_CalcuDat m_stCalcu;
    tp_stSDMech * m_stptMech;
    tp_stSDState m_stSDState;
    st_Gains * m_stGains;
    int nIsUrg; // flag of urgency
    double dTime;
    bool fnbGetRef(st_Target stRefIn) {
        this->m_stptWBCDat->ref = stRefIn; // get reference from upper level
        return true;
    }
    bool fnbUpdateSD(double dQIn[__DoFNum], double dUIn[__DoFNum]) {
        // for(int i = 0; i < __DoFNum; i++) this->m_stCalcu.dq(i) = dUIn[i]; // update dq for qp
        // this->_SD fnbSetState(dQIn, dUIn); // update state for sdfast by sens state
        for(int i = 0; i < __DoFNum; i++) this->m_stCalcu.dq(i) = this->m_stptWBCDat->sta.dq[i]; // for test 1）
        this->_SD fnbSetState(this->m_stptWBCDat->sta.q, this->m_stptWBCDat->sta.dq); // for test 1）
        this->_SD fnbUpdateFK(); // update calculate data
        return true;
    }
    bool fnbGetRel() {
        double dPosTemp[3] = { 0.0 }, dptSpcTemp[6], dptdSpcTemp[6];
        this->_SD fnbGetPointPosRot(midbody, dPosTemp, dptSpcTemp);
        this->_SD fnbGetPointdPosRot(midbody, dPosTemp, dptdSpcTemp);
        for(int i = 0; i < 2; i++) for(int j = 0; j < 6; j++)
            this->m_stptWBCDat->rel.Ank[i][j] = this->m_stSDState.dAnk[i][j],
            this->m_stptWBCDat->rel.dAnk[i][j] = this->m_stSDState.ddAnk[i][j];
        for(int i = 0; i < 3; i++)
            this->m_stptWBCDat->rel.c[i] = this->m_stSDState.dCoM[i],
            this->m_stptWBCDat->rel.dc[i] = this->m_stSDState.ddCoM[i],
            this->m_stptWBCDat->rel.h[i] = this->m_stSDState.dMom[i], this->m_stptWBCDat->rel.h[3 + i] = this->m_stSDState.dMom[3 + i],
            this->m_stptWBCDat->rel.pos[i] = dptSpcTemp[3 + i], 
            this->m_stptWBCDat->rel.dpos[i] = dptdSpcTemp[3 + i];
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
                                        + this->m_stGains->dh[i][1] * (this->m_stptWBCDat->ref.c[i]  - this->m_stptWBCDat->rel.c[i]),            // kc
                                        + this->m_stGains->dh[i][2] * (this->m_stptWBCDat->ref.dc[i] - this->m_stptWBCDat->rel.dc[i]),          // kdc
        this->m_stptWBCDat->con.dh_ref[3 + i] = this->m_stptWBCDat->ref.dh[3 + i]                                                               // feedforward
                                        + this->m_stGains->dh[i][3] * (this->m_stptWBCDat->ref.h[3 + i]  - this->m_stptWBCDat->rel.h[3 + i])    // kh
                                        + this->m_stGains->dh[i][4] * (this->m_stptWBCDat->ref.pos[i]  - this->m_stptWBCDat->rel.pos[i])        // kc
                                        + this->m_stGains->dh[i][5] * (this->m_stptWBCDat->ref.dpos[i] - this->m_stptWBCDat->rel.dpos[i]);      // kdc
        // printf("%.3lf, %.3lf\n", this->m_stptWBCDat->ref.c[1], this->m_stptWBCDat->rel.c[1]);
        // printf("%.3lf, %.3lf, %.3lf, %.3lf \n", this->m_stptWBCDat->ref.c[2], this->m_stptWBCDat->rel.c[2], this->m_stptWBCDat->rel.dc[2], this->m_stptWBCDat->con.dh_ref[2]); __DEBUG // for test
        
        // FrameAddLogsC(987, "Zc_ref",  &this->m_stptWBCDat->ref.c[2], 1);
        // FrameAddLogsC(987, "Zc_rel",  &this->m_stptWBCDat->rel.c[2], 1);
        return true;
    }
    bool fnbClearHf() {
        this->m_stCalcu.H.setIdentity(), this->m_stCalcu.H.setIdentity() *= 1e-6;
        this->m_stCalcu.f.setZero();
        this->m_stCalcu.w.setZero();
        return true;
    }
    bool fnbAddCost(double J[6][__DoFNum], double dJ[6][__DoFNum], double P[6], double w[6]) { // system jacobian, jacobian rate, reference, weight
        for(int i = 0; i < 6; i++) {
            this->m_stCalcu.P(i) = P[i], this->m_stCalcu.w(i, i) = w[i];
            for(int j = 0; j < __DoFNum; j++) this->m_stCalcu.J(i, j) =  J[i][j], this->m_stCalcu.dJ(i, j) =  dJ[i][j];
        }
        this->m_stCalcu.wJ = this->m_stCalcu.w * this->m_stCalcu.J;
        this->m_stCalcu._P = this->m_stCalcu.dJ * this->m_stCalcu.dq - this->m_stCalcu.P;
        this->m_stCalcu.H += this->m_stCalcu.J.transpose() * this->m_stCalcu.wJ;
        this->m_stCalcu.f += 2 * this->m_stCalcu._P.transpose() * this->m_stCalcu.wJ;
        return true;
    }
    bool fnbUpdateConval() { // get ddq by QP
        this->fnbClearHf(); // reset H and f
        // momentum tracking
        this->fnbAddCost(this->m_stSDState.dMatA, this->m_stSDState.dMatdA, this->m_stptWBCDat->con.dh_ref, this->m_stGains->wh);
        // ankle tracking
        for(int i = 0; i < 2; i++ )this->fnbAddCost(this->m_stSDState.dJacoFt[i], this->m_stSDState.dJacoFt[i], this->m_stptWBCDat->con.ddAnk_ref[i], this->m_stGains->wa);
        // fnvShowHf(); __DEBUG // for test
        qp.updateHf(this->m_stCalcu.H, this->m_stCalcu.f); // send H and f to QP solver
        if(!qp.getResult()) { // if QP failed
            this->nIsUrg = 1; // urgency !!!
            return false;
        }
        // for(int i = 0; i < __DoFNum; i++) this->m_stptWBCDat->ddq[i] = 0.0; // for test
        for(int i = 0; i < __DoFNum; i++) this->m_stptWBCDat->ddq[i] = qp.x(i);
        return true;
    }
    bool fnbUrgRescue() { // make joints stop
        for(int i = 0; i < __DoFNum; i++) this->m_stptWBCDat->ddq[i] = -dUrgGain * this->m_stptWBCDat->sta.dq[i];
        _STD cout << "Urgency detected!" << _STD endl;
        return true;
    }
    bool fnbUpdateJoint(double dCmdJointsOut[__JointNum]) {
        if(this->nIsUrg) fnbUrgRescue();
        for(int i = 0; i < __DoFNum; i++) this->m_stptWBCDat->sta.dq[i] += this->m_stptWBCDat->ddq[i] * this->dTime; // intergrate dq
        for(int i = 0; i < __DoFNum; i++) this->m_stptWBCDat->sta.q[i] += this->m_stptWBCDat->sta.dq[i] * this->dTime; // intergrate q
        for(int i = 0; i < __JointNum; i++) dCmdJointsOut[i] = this->m_stptWBCDat->sta.q[6 + i];
        return true;
    }
};

_D_CONTROL_END

#endif