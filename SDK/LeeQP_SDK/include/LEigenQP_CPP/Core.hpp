// All C++ codes version of EigenQuadProg for multi-thread programs
// Jan. 09, 2023
// Qingqing Li
// liqingqing.kevin@qq.com

// QP formulation
// min  0.5x'Hx + f'x
// s.t. Ae*x=be, Ai*x<=bi

#pragma once
#include "QPBase.h"
#include "QuadProg.h"
#include <iostream>
_L_EIGEN_QP_CPP_BEGIN

template <const int NX, const int NEQ=0, const int NIQ=0>
class LEigenQP:private Eigen::QuadProgDense
{
public:
    Eigen::MatrixXd H,f,A,b,Ae,be,Ai,bi,x,w;
    int nx,neq,niq,ncost;
public:
    LEigenQP():QuadProgDense(){
        setProblem(NX, NEQ, NIQ, 0);
    };
    LEigenQP(int ncost):QuadProgDense(){
        setProblem(NX, NEQ, NIQ, ncost);
    };
    void setProblem(const int nx, const int neq, const int niq, const int ncost){
        this->nx    = nx    ; 
        this->neq   = neq   ; 
        this->niq   = niq   ; 
        this->ncost = ncost ;
        this->H. conservativeResize (nx,   nx);    this->f. conservativeResize (nx,   1);
        this->A. conservativeResize (ncost,nx);    this->b. conservativeResize (ncost,1);
        this->Ae.conservativeResize (neq,  nx);    this->be.conservativeResize (neq,  1);
        this->Ai.conservativeResize (niq,  nx);    this->bi.conservativeResize (niq,  1);
        this->x. conservativeResize (nx,    1);    this->w. conservativeResize (ncost,1);
        this->H.setZero();
        this->f.setZero();
        this->A.setZero();
        this->b.setZero();
        this->Ae.setZero();
        this->be.setZero();
        this->Ai.setZero();
        this->bi.setZero();
        this->x.setZero();
        this->w.setZero();
        this->problem(nx,neq,niq);
    };
    inline void updateHf(){
        this->H =  A.transpose()*A;
        this->f = -A.transpose()*b;
    };
    inline void updateHf(const Eigen::MatrixXd& H, const Eigen::MatrixXd& f){
        this->H = H;
        this->f = f;
    };
    inline bool getResult(){
        auto res = this->solve(H,f,Ae,be,Ai,bi);
        this->x  = this->result();
        return res;
    };
    inline bool getResult(double * x){
        auto res = getResult();
        for(int i=0;i<nx;i++) x[i] = this->x(i);
        return res;
    };
    inline void setCost(const int k, const double w, const double * Ak, const double bk){
        for(int i=0;i<nx;i++)
        {
            A(k,i) = w*Ak[i];   b(k) = w*bk;
        }
    };
    inline void setEqConstraint(const int k, const double * Aek, const double bek){
        for(int i=0;i<nx;i++)
        {
            Ae(k,i) = Aek[i];   be(k) = bek;
        }
    };
    inline void setIqConstraint(const int k, const double * Aik, const double bik){
        for(int i=0;i<nx;i++)
        {
            Ai(k,i) = Aik[i];   bi(k) = bik;
        }
    };
    inline void resizeCost(const int CostNum){
        this->ncost = CostNum;
        this->A.conservativeResize(CostNum, NX);
        this->b.conservativeResize(CostNum,  1);
    };
};

_L_EIGEN_QP_CPP_END

namespace lee{using eigen_qp::LEigenQP;}