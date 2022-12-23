/*
Generated 01-Jan-1999 11:47:59 by SD/FAST, Kane's formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
#include <math.h>
#include "..\SDFastDefs.h"

_D_SDFAST_BEGIN

/* These routines are passed to sdroot. */
void sdposfunc(double vars[21],
    double param[1],
    double resid[1])
{
    int i;
    double pos[21],vel[21];

    for (i = 0; i < 21; i++) {
        vel[i] = 0.;
    }
    sdang2st(vars,pos);
    sdstate(param[0],pos,vel);
    sdperr(resid);
}

void sdvelfunc(double vars[21],
    double param[22],
    double resid[1])
{

    sdstate(param[21],param,vars);
    sdverr(resid);
}

void sdstatfunc(double vars[21],
    double param[22],
    double resid[21])
{
    double pos[21],qdotdum[21];

    sdang2st(vars,pos);
    sdstate(param[21],pos,param);
    sduforce(param[21],pos,param);
    sdperr(resid);
    sdderiv(qdotdum,&resid[0]);
}

void sdstdyfunc(double vars[42],
    double param[1],
    double resid[21])
{
    double pos[21],qdotdum[21];

    sdang2st(vars,pos);
    sdstate(param[0],pos,&vars[21]);
    sduforce(param[0],pos,&vars[21]);
    sdperr(resid);
    sdverr(&resid[0]);
    sdderiv(qdotdum,&resid[0]);
}

/* This routine is passed to the integrator. */

void sdmotfunc(double time,
    double state[42],
    double dstate[42],
    double param[1],
    int *status)
{

    sdstate(time,state,&state[21]);
    sduforce(time,state,&state[21]);
    sdderiv(dstate,&dstate[21]);
    *status = 0;
}

/* This routine performs assembly analysis. */

void sdassemble(double time,
    double state[42],
    int lock[21],
    double tol,
    int maxevals,
    int *fcnt,
    int *err)
{
    double perrs[1],param[1];
    int i;

    sdgentime(&i);
    if (i != 114759) {
        sdseterr(50,42);
    }
    param[0] = time;
    *err = 0;
    *fcnt = 0;
    sdposfunc(state,param,perrs);
    *fcnt = *fcnt+1;
}

/* This routine performs initial velocity analysis. */

void sdinitvel(double time,
    double state[42],
    int lock[21],
    double tol,
    int maxevals,
    int *fcnt,
    int *err)
{
    double verrs[1],param[22];
    int i;

    sdgentime(&i);
    if (i != 114759) {
        sdseterr(51,42);
    }
    for (i = 0; i < 21; i++) {
        param[i] = state[i];
    }
    param[21] = time;
    *err = 0;
    *fcnt = 0;
    sdvelfunc(&state[21],param,verrs);
    *fcnt = *fcnt+1;
}

/* This routine performs static analysis. */

void sdstatic(double time,
    double state[42],
    int lock[21],
    double ctol,
    double tol,
    int maxevals,
    int *fcnt,
    int *err)
{
    double resid[21],param[22],jw[441],dw[3528],rw[336];
    int iw[168],rooterr,i;

    sdgentime(&i);
    if (i != 114759) {
        sdseterr(52,42);
    }
    for (i = 0; i < 21; i++) {
        param[i] = state[21+i];
    }
    param[21] = time;
    sdroot(sdstatfunc,state,param,21,21,21,lock,
      ctol,tol,maxevals,jw,dw,rw,iw,resid,fcnt,&rooterr);
    sdstatfunc(state,param,resid);
    *fcnt = *fcnt+1;
    if (rooterr == 0) {
        *err = 0;
    } else {
        if (*fcnt >= maxevals) {
            *err = 2;
        } else {
            *err = 1;
        }
    }
}

/* This routine performs steady motion analysis. */

void sdsteady(double time,
    double state[42],
    int lock[42],
    double ctol,
    double tol,
    int maxevals,
    int *fcnt,
    int *err)
{
    double resid[21],param[1];
    double jw[882],dw[7938],rw[525];
    int iw[252],rooterr,i;

    sdgentime(&i);
    if (i != 114759) {
        sdseterr(53,42);
    }
    param[0] = time;
    sdroot(sdstdyfunc,state,param,21,42,21,lock,
      ctol,tol,maxevals,jw,dw,rw,iw,resid,fcnt,&rooterr);
    sdstdyfunc(state,param,resid);
    *fcnt = *fcnt+1;
    if (rooterr == 0) {
        *err = 0;
    } else {
        if (*fcnt >= maxevals) {
            *err = 2;
        } else {
            *err = 1;
        }
    }
}

/* This routine performs state integration. */

void sdmotion(double *time,
    double state[42],
    double dstate[42],
    double dt,
    double ctol,
    double tol,
    int *flag,
    int *err)
{
    static double step;
    double work[252],ttime,param[1];
    int vintgerr,which,ferr,i;

    sdgentime(&i);
    if (i != 114759) {
        sdseterr(54,42);
    }
    param[0] = ctol;
    ttime = *time;
    if (*flag != 0) {
        sdmotfunc(ttime,state,dstate,param,&ferr);
        step = dt;
        *flag = 0;
    }
    if (step <= 0.) {
        step = dt;
    }
    sdvinteg(sdmotfunc,&ttime,state,dstate,param,dt,&step,42,tol,work,&vintgerr,
      &which);
    *time = ttime;
    *err = vintgerr;
}

/* This routine performs state integration with a fixed-step integrator. */

void sdfmotion(double *time,
    double state[42],
    double dstate[42],
    double dt,
    double ctol,
    int *flag,
    double *errest,
    int *err)
{
    double work[168],ttime,param[1];
    int ferr,i;

    sdgentime(&i);
    if (i != 114759) {
        sdseterr(55,42);
    }
    param[0] = ctol;
    *err = 0;
    ttime = *time;
    if (*flag != 0) {
        sdmotfunc(ttime,state,dstate,param,&ferr);
        *flag = 0;
    }
    sdfinteg(sdmotfunc,&ttime,state,dstate,param,dt,42,work,errest,&ferr);
    if (ferr != 0) {
        *err = 1;
    }
    *time = ttime;
}

_D_SDFAST_END