// SDFastDefs.h
#include <SDFastHeaders.h>
#include <stdio.h>
#include <iostream>
#include <SDMechDefs.h>

_D_SDFAST_BEGIN

// sdlib
void sdprerrmsg(FILE* fnum, int routine, int errnum);
void sderror(int* routine, int* errnum);
void sdprinterr(FILE* fnum);
void sdclearerr(void);
void sdseterr(int routine, int errnum);
void sdldudcomp(int n, int na, int map[], double tol, double ld[], double sum[], double m[], double l[], double d[]);
void sdldubsl(int n, int na, int map[], double l[], double b[], double x[]);
void sdldubsd(int n, int na, int map[], double d[], double b[], double x[]);
void sdldubsu(int n, int na, int map[], double l[], double b[], double x[]);
void sdldubslv(int n, int na, int map[], double work[], double l[], double d[], double b[], double x[]);
void sdlduslv(int n, int na, int map[], double tol, double work1[], double work2[], double m[], double b[], double l[], double d[], double x[]);
void sdqrdcomp(int nr, int nc, int nra, int nca, int mapr[], int mapc[], double w[], double qraux[], int jpvt[]);
void sdqrsl(int nr, int nc, int nra, int nca, int mapr[], int mapc[], int k, double work[], double w[], double qraux[], double b[], double x[]);
void sdqrbslv(int nr, int nc, int nra, int nca, int mapr[], int mapc[], double tol, double work[], int iwork[], double w[], double qraux[], int jpvt[], double b[], double x[], int* rank);
void sdqrslv(int nr, int nc, int nra, int nca, int mapr[], int mapc[], double tol, int jpvt[], double qraux[], double work[], int iwork[], double w[], double b[], double x[], int* rank);
void sdlsslv(int nr, int nc, int nra, int nca, int ndes, int mapr[], int mapc[], double tol, double dw[], double rw[], int iw[], double w[], double b[], double x[]);
void sdcalcerrs(double fval[], int nfunc, int ndes, int dnorm, double* maxderr, double* maxrerr, double* derrnorm);
void sdadjvars(void(*func) (double[], double[], double[]), double vars[], double param[], int nfunc, int ndes, int dnorm, int nvar, double deltas[], double step, double rerr, double tderr, double rtol, int* fcnt, double newvars[], double newerrs[]);
void sdcalcjac(void(*func) (double[], double[], double[]), double vars[], double param[], int nfunc, int nvar, int lock[], double delta, double fval[], double ftmp[], double jw[], int* fcnt, double scale[]);
void sdroot(void(*func) (double[], double[], double[]), double vars[], double param[], int nfunc, int nvar, int ndesin, int lock[], double rtol, double dtol, int maxeval, double jw[], double dw[], double rw[], int iw[], double fret[], int* fcnt, int* err);
void sdrk4m(void(*func) (double, double[], double*, double[], int*), double time, double st[], double dst0[], double param[], double step, double nst[], int neq, double work[], double errs[], double* maxerr, int* which);
void sdfinteg(void(*func) (double, double[], double[], double[], int*), double* time, double st[], double dst[], double param[], double step, int neq, double work[], double* errest, int* status);
void sdvinteg(void(*func) (double, double[], double[], double[], int*), double* time, double st[], double dst[], double param[], double dt, double* step, int neqin, double tol, double work[], int* err, int* which);
void sddc2ang(double dircos[3][3], double* a1, double* a2, double* a3);
void sddc2quat(double dircos[3][3], double* e1, double* e2, double* e3, double* e4);
void sdang2dc(double a1, double a2, double a3, double dircos[3][3]);
void sdquat2dc(double ie1, double ie2, double ie3, double ie4, double dircos[3][3]);
double sdvdot(double ivec1[3], double ivec2[3]);
double sdvnorm(double ivec[3]);
void sdvcopy(double ivec[3], double ovec[3]);
void sdvset(double sclr1, double sclr2, double sclr3, double ovec[3]);
void sdvadd(double ivec1[3], double ivec2[3], double ovec[3]);
void sdvsub(double ivec1[3], double ivec2[3], double ovec[3]);
void sdvmul(double sclr, double ivec[3], double ovec[3]);
void sdvaxpy(double sclr, double ivec1[3], double ivec2[3], double ovec[3]);
void sdvcross(double ivec1[3], double ivec2[3], double ovec[3]);
void sdvrot(double ivec[3], double rvec[3], double theta, double ovec[3]);
void sdserialno(int* serno);

// SDRobot_d
void sdinit(void);
void sdst2ang(double st[21], double stang[21]);
void sdang2st(double stang[21], double st[21]);
void sdnrmsterr(double st[21], double normst[21], int routine);
void sdnormst(double st[21], double normst[21]);
void sdstate(double timein, double qin[21], double uin[21]);
void sdqdot(double oqdot[21]);
void sdu2qdot(double uin[21], double oqdot[21]);
void sdpsstate(double lqin[1]);
void sddovpk(void);
void sddoltau(void);
void sddoiner(void);
void sddofs0(void);
void sddomm(int routine);
void sddommldu(int routine);
void sdlhs(int routine);
void sdmfrc(double imult[1]);
void sdequivht(double tau[21]);
void sdfs0(void);
void sdfsmult(void);
void sdfsfull(void);
void sdfsgenmult(void);
void sdfsgenfull(void);
void sdfulltrq(double udotin[21], double multin[1], double trqout[21]);
void sdcomptrq(double udotin[21], double trqout[21]);
void sdmulttrq(double multin[1], double trqout[21]);
void sdrhs(void);
void sdmassmat(double mmat[21][21]);
void sdfrcmat(double fmat[21]);
void sdpseudo(double lqout[1], double luout[1]);
void sdpsqdot(double lqdout[1]);
void sdpsudot(double ludout[1]);
void sdperr(double errs[1]);
void sdverr(double errs[1]);
void sdaerr(double errs[1]);
int sdchkbnum(int routine, int bnum);
int sdchkjnum(int routine, int jnum);
int sdchkucnum(int routine, int ucnum);
int sdchkjaxis(int routine, int jnum, int axnum);
int sdchkjpin(int routine, int jnum, int pinno);
int sdindx(int joint, int axis);
void sdpresacc(int joint, int axis, double prval);
void sdpresvel(int joint, int axis, double prval);
void sdprespos(int joint, int axis, double prval);
void sdgetht(int joint, int axis, double* torque);
void sdhinget(int joint, int axis, double torque);
void sdpointf(int body, double point[3], double force[3]);
void sdbodyt(int body, double torque[3]);
void sddoww(int routine);
void sdxudot0(int routine, double oudot0[21]);
void sdudot0(double oudot0[21]);
void sdsetudot(double iudot[21]);
void sdxudotm(int routine, double imult[1], double oudotm[21]);
void sdudotm(double imult[1], double oudotm[21]);
void sdderiv(double oqdot[21], double oudot[21]);
void sdresid(double eqdot[21], double eudot[21], double emults[1], double resid[42]);
void sdmult(double omults[1], int* owrank, int omultmap[1]);
void sdreac(double force[10][3], double torque[10][3]);
void sdmom(double lm[3], double am[3], double* ke);
void sdsys(double* mtoto, double cm[3], double icm[3][3]);
void sdpos(int body, double pt[3], double loc[3]);
void sdvel(int body, double pt[3], double velo[3]);
void sdorient(int body, double dircos[3][3]);
void sdangvel(int body, double avel[3]);
void sdtrans(int frbod, double ivec[3], int tobod, double ovec[3]);
void sdrel2cart(int coord, int body, double point[3], double linchg[3], double rotchg[3]);
void sdacc(int body, double pt[3], double accel[3]);
void sdangacc(int body, double aacc[3]);
void sdgrav(double gravin[3]);
void sdmass(int body, double massin);
void sdiner(int body, double inerin[3][3]);
void sdbtj(int joint, double btjin[3]);
void sditj(int joint, double itjin[3]);
void sdpin(int joint, int pinno, double pinin[3]);
void sdpres(int joint, int axis, int presin);
void sdconschg(void);
void sdstab(double velin, double posin);
void sdgetgrav(double gravout[3]);
void sdgetmass(int body, double* massout);
void sdgetiner(int body, double inerout[3][3]);
void sdgetbtj(int joint, double btjout[3]);
void sdgetitj(int joint, double itjout[3]);
void sdgetpin(int joint, int pinno, double pinout[3]);
void sdgetpres(int joint, int axis, int* presout);
void sdgetstab(double* velout, double* posout);
void sdinfo(int info[50]);
void sdjnt(int joint, int info[50], int tran[6]);
void sdcons(int consno, int info[50]);
void sdgentime(int* gentm);

// SDRobot_s
void sduforce(double param1, double pos[], double param[]);
void sdumotion();

_D_SDFAST_END