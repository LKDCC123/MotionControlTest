/*
Generated 01-Jan-1999 18:58:22 by SD/FAST, Kane's formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041


ROADMAP (Robot.sd)

Bodies        Inb
No  Name      body Joint type  Coords q
--- --------- ---- ----------- ----------------
 -1 $ground                                    
  0 midbody    -1  Bushing       0   1   2 
                   ...           3   4   5     
  1 uppbody     0  Pin           6             
  2 larm        1  Pin           7             
  3 rarm        1  Pin           8             
  4 lthigh      0  Gimbal        9  10  11     
  5 lshank      4  Pin          12             
  6 lfoot       5  U-joint      13  14         
  7 rthigh      0  Gimbal       15  16  17     
  8 rshank      7  Pin          18             
  9 rfoot       8  U-joint      19  20         

*/

#include <math.h>
#include <stdio.h>

#include "ChzSD_sdfastfuncs.h"
namespace ChzSD
{

typedef struct {
    int ground_,nbod_,ndof_,ncons_,nloop_,nldof_,nloopc_,nball_,nlball_,npres_,
      nuser_;
    int jtype_[10],inb_[10],outb_[10],njntdof_[10],njntc_[10],njntp_[10],firstq_
      [10],ballq_[10],firstm_[10],firstp_[10];
    int trans_[21];
} sdgtopo_t;
#define ground (sdgtopo.ground_)
#define nbod (sdgtopo.nbod_)
#define ndof (sdgtopo.ndof_)
#define ncons (sdgtopo.ncons_)
#define nloop (sdgtopo.nloop_)
#define nldof (sdgtopo.nldof_)
#define nloopc (sdgtopo.nloopc_)
#define nball (sdgtopo.nball_)
#define nlball (sdgtopo.nlball_)
#define npres (sdgtopo.npres_)
#define nuser (sdgtopo.nuser_)
#define jtype (sdgtopo.jtype_)
#define inb (sdgtopo.inb_)
#define outb (sdgtopo.outb_)
#define njntdof (sdgtopo.njntdof_)
#define njntc (sdgtopo.njntc_)
#define njntp (sdgtopo.njntp_)
#define firstq (sdgtopo.firstq_)
#define ballq (sdgtopo.ballq_)
#define firstm (sdgtopo.firstm_)
#define firstp (sdgtopo.firstp_)
#define trans (sdgtopo.trans_)

typedef struct {
    double grav_[3],mk_[10],ik_[10][3][3],pin_[21][3];
    double rk_[10][3],ri_[10][3],pres_[21],stabvel_,stabpos_;
    int mfrcflg_,roustate_,vpkflg_,inerflg_,mmflg_,mmlduflg_,wwflg_,ltauflg_,
      fs0flg_,ii_,mmap_[21];
    int gravq_[3],mkq_[10],ikq_[10][3][3],pinq_[21][3],rkq_[10][3],riq_[10][3],
      presq_[21],stabvelq_,stabposq_;
    double mtot_,psmkg_,rhead_[10][3],rcom_[10][3],mkrcomt_[10][3][3],psikg_[3][
      3],psrcomg_[3],psrkg_[3],psrig_[3],psmk_[21],psik_[21][3][3],psrcom_[21][3
      ],psrk_[21][3],psri_[21][3];
} sdginput_t;
#define grav (sdginput.grav_)
#define mk (sdginput.mk_)
#define ik (sdginput.ik_)
#define pin (sdginput.pin_)
#define rk (sdginput.rk_)
#define ri (sdginput.ri_)
#define pres (sdginput.pres_)
#define stabvel (sdginput.stabvel_)
#define stabpos (sdginput.stabpos_)
#define rhead (sdginput.rhead_)
#define rcom (sdginput.rcom_)
#define psrcomg (sdginput.psrcomg_)
#define psrcom (sdginput.psrcom_)
#define mkrcomt (sdginput.mkrcomt_)
#define psmk (sdginput.psmk_)
#define psik (sdginput.psik_)
#define psrk (sdginput.psrk_)
#define psri (sdginput.psri_)
#define psmkg (sdginput.psmkg_)
#define psikg (sdginput.psikg_)
#define psrkg (sdginput.psrkg_)
#define psrig (sdginput.psrig_)
#define mtot (sdginput.mtot_)
#define mfrcflg (sdginput.mfrcflg_)
#define roustate (sdginput.roustate_)
#define vpkflg (sdginput.vpkflg_)
#define inerflg (sdginput.inerflg_)
#define mmflg (sdginput.mmflg_)
#define mmlduflg (sdginput.mmlduflg_)
#define wwflg (sdginput.wwflg_)
#define ltauflg (sdginput.ltauflg_)
#define fs0flg (sdginput.fs0flg_)
#define ii (sdginput.ii_)
#define mmap (sdginput.mmap_)
#define gravq (sdginput.gravq_)
#define mkq (sdginput.mkq_)
#define ikq (sdginput.ikq_)
#define pinq (sdginput.pinq_)
#define rkq (sdginput.rkq_)
#define riq (sdginput.riq_)
#define presq (sdginput.presq_)
#define stabvelq (sdginput.stabvelq_)
#define stabposq (sdginput.stabposq_)

typedef struct {
    double curtim_,q_[21],qn_[21],u_[21],cnk_[21][3][3],cnb_[10][3][3];
    double rnk_[21][3],vnk_[21][3],wk_[21][3],rnb_[10][3],vnb_[10][3],wb_[10][3]
      ,wbrcom_[10][3],com_[3],rnkg_[3];
    double Cik_[21][3][3],rikt_[21][3][3],Iko_[21][3][3],mkrk_[21][3][3],Cib_[10
      ][3][3];
    double Wkk_[21][3],Vkk_[21][3],dik_[21][3],rpp_[21][3],rpk_[21][3],rik_[21][
      3],rik2_[21][3];
    double rpri_[21][3],Wik_[21][3],Vik_[21][3],Wirk_[21][3],rkWkk_[21][3],
      Wkrpk_[21][3],VikWkr_[21][3];
    double perr_[1],verr_[1],aerr_[1],mult_[1],ufk_[10][3],utk_[10][3],mfk_[10][
      3],mtk_[10][3];
    double utau_[21],mtau_[21],uacc_[21],uvel_[21],upos_[21];
    double s3_,c3_,s4_,c4_,s5_,c5_,s6_,c6_,s7_,c7_,s8_,c8_,s9_,c9_,s10_,c10_,
      s11_,c11_,s12_,c12_,s13_,c13_,s14_,c14_,s15_,c15_,s16_,c16_,s17_,c17_,s18_
      ,c18_,s19_,c19_,s20_,c20_;
} sdgstate_t;
#define curtim (sdgstate.curtim_)
#define q (sdgstate.q_)
#define qn (sdgstate.qn_)
#define u (sdgstate.u_)
#define cnk (sdgstate.cnk_)
#define cnb (sdgstate.cnb_)
#define rnkg (sdgstate.rnkg_)
#define rnk (sdgstate.rnk_)
#define rnb (sdgstate.rnb_)
#define vnk (sdgstate.vnk_)
#define vnb (sdgstate.vnb_)
#define wk (sdgstate.wk_)
#define wb (sdgstate.wb_)
#define com (sdgstate.com_)
#define Cik (sdgstate.Cik_)
#define Cib (sdgstate.Cib_)
#define rikt (sdgstate.rikt_)
#define Iko (sdgstate.Iko_)
#define mkrk (sdgstate.mkrk_)
#define Wkk (sdgstate.Wkk_)
#define Vkk (sdgstate.Vkk_)
#define dik (sdgstate.dik_)
#define rpp (sdgstate.rpp_)
#define rpk (sdgstate.rpk_)
#define rik (sdgstate.rik_)
#define rik2 (sdgstate.rik2_)
#define rpri (sdgstate.rpri_)
#define Wik (sdgstate.Wik_)
#define Vik (sdgstate.Vik_)
#define Wirk (sdgstate.Wirk_)
#define rkWkk (sdgstate.rkWkk_)
#define Wkrpk (sdgstate.Wkrpk_)
#define VikWkr (sdgstate.VikWkr_)
#define wbrcom (sdgstate.wbrcom_)
#define perr (sdgstate.perr_)
#define verr (sdgstate.verr_)
#define aerr (sdgstate.aerr_)
#define mult (sdgstate.mult_)
#define ufk (sdgstate.ufk_)
#define utk (sdgstate.utk_)
#define utau (sdgstate.utau_)
#define mfk (sdgstate.mfk_)
#define mtk (sdgstate.mtk_)
#define mtau (sdgstate.mtau_)
#define uacc (sdgstate.uacc_)
#define uvel (sdgstate.uvel_)
#define upos (sdgstate.upos_)
#define s3 (sdgstate.s3_)
#define c3 (sdgstate.c3_)
#define s4 (sdgstate.s4_)
#define c4 (sdgstate.c4_)
#define s5 (sdgstate.s5_)
#define c5 (sdgstate.c5_)
#define s6 (sdgstate.s6_)
#define c6 (sdgstate.c6_)
#define s7 (sdgstate.s7_)
#define c7 (sdgstate.c7_)
#define s8 (sdgstate.s8_)
#define c8 (sdgstate.c8_)
#define s9 (sdgstate.s9_)
#define c9 (sdgstate.c9_)
#define s10 (sdgstate.s10_)
#define c10 (sdgstate.c10_)
#define s11 (sdgstate.s11_)
#define c11 (sdgstate.c11_)
#define s12 (sdgstate.s12_)
#define c12 (sdgstate.c12_)
#define s13 (sdgstate.s13_)
#define c13 (sdgstate.c13_)
#define s14 (sdgstate.s14_)
#define c14 (sdgstate.c14_)
#define s15 (sdgstate.s15_)
#define c15 (sdgstate.c15_)
#define s16 (sdgstate.s16_)
#define c16 (sdgstate.c16_)
#define s17 (sdgstate.s17_)
#define c17 (sdgstate.c17_)
#define s18 (sdgstate.s18_)
#define c18 (sdgstate.c18_)
#define s19 (sdgstate.s19_)
#define c19 (sdgstate.c19_)
#define s20 (sdgstate.s20_)
#define c20 (sdgstate.c20_)

typedef struct {
    double fs0_[21],qdot_[21],Otk_[21][3],Atk_[21][3],AiOiWi_[21][3],Fstar_[21][
      3];
    double Tstar_[21][3],Fstark_[21][3],Tstark_[21][3],IkWk_[21][3],WkIkWk_[21][
      3],gk_[21][3],IkbWk_[10][3],WkIkbWk_[10][3];
    double w0w0_[10],w1w1_[10],w2w2_[10],w0w1_[10],w0w2_[10],w1w2_[10];
    double w00w11_[10],w00w22_[10],w11w22_[10],ww_[1][1],qraux_[1];
    double mm_[21][21],mlo_[21][21],mdi_[21],IkWpk_[21][21][3],works_[21],
      workss_[21][21];
    double Wpk_[21][21][3],Vpk_[21][21][3],VWri_[21][21][3];
    int wmap_[1],multmap_[1],jpvt_[1],wsiz_,wrank_;
} sdglhs_t;
#define qdot (sdglhs.qdot_)
#define Otk (sdglhs.Otk_)
#define Atk (sdglhs.Atk_)
#define AiOiWi (sdglhs.AiOiWi_)
#define Fstar (sdglhs.Fstar_)
#define Tstar (sdglhs.Tstar_)
#define fs0 (sdglhs.fs0_)
#define Fstark (sdglhs.Fstark_)
#define Tstark (sdglhs.Tstark_)
#define IkWk (sdglhs.IkWk_)
#define IkbWk (sdglhs.IkbWk_)
#define WkIkWk (sdglhs.WkIkWk_)
#define WkIkbWk (sdglhs.WkIkbWk_)
#define gk (sdglhs.gk_)
#define w0w0 (sdglhs.w0w0_)
#define w1w1 (sdglhs.w1w1_)
#define w2w2 (sdglhs.w2w2_)
#define w0w1 (sdglhs.w0w1_)
#define w0w2 (sdglhs.w0w2_)
#define w1w2 (sdglhs.w1w2_)
#define w00w11 (sdglhs.w00w11_)
#define w00w22 (sdglhs.w00w22_)
#define w11w22 (sdglhs.w11w22_)
#define ww (sdglhs.ww_)
#define qraux (sdglhs.qraux_)
#define mm (sdglhs.mm_)
#define mlo (sdglhs.mlo_)
#define mdi (sdglhs.mdi_)
#define IkWpk (sdglhs.IkWpk_)
#define works (sdglhs.works_)
#define workss (sdglhs.workss_)
#define Wpk (sdglhs.Wpk_)
#define Vpk (sdglhs.Vpk_)
#define VWri (sdglhs.VWri_)
#define wmap (sdglhs.wmap_)
#define multmap (sdglhs.multmap_)
#define jpvt (sdglhs.jpvt_)
#define wsiz (sdglhs.wsiz_)
#define wrank (sdglhs.wrank_)

typedef struct {
    double fs_[21],udot_[21],tauc_[21],dyad_[10][3][3],fc_[21][3],tc_[21][3];
    double ank_[21][3],onk_[21][3],Onkb_[21][3],AOnkri_[21][3],Ankb_[21][3],
      AnkAtk_[21][3],anb_[10][3],onb_[10][3],dyrcom_[10][3];
    double ffk_[21][3],ttk_[21][3],fccikt_[21][3],ffkb_[10][3],ttkb_[10][3];
} sdgrhs_t;
#define fs (sdgrhs.fs_)
#define udot (sdgrhs.udot_)
#define ank (sdgrhs.ank_)
#define anb (sdgrhs.anb_)
#define onk (sdgrhs.onk_)
#define onb (sdgrhs.onb_)
#define Onkb (sdgrhs.Onkb_)
#define AOnkri (sdgrhs.AOnkri_)
#define Ankb (sdgrhs.Ankb_)
#define AnkAtk (sdgrhs.AnkAtk_)
#define dyrcom (sdgrhs.dyrcom_)
#define ffk (sdgrhs.ffk_)
#define ttk (sdgrhs.ttk_)
#define fccikt (sdgrhs.fccikt_)
#define ffkb (sdgrhs.ffkb_)
#define ttkb (sdgrhs.ttkb_)
#define dyad (sdgrhs.dyad_)
#define fc (sdgrhs.fc_)
#define tc (sdgrhs.tc_)
#define tauc (sdgrhs.tauc_)

typedef struct {
    double temp_[3000],tmat1_[3][3],tmat2_[3][3],tvec1_[3],tvec2_[3],tvec3_[3],
      tvec4_[3],tvec5_[3];
    double tsc1_,tsc2_,tsc3_;
} sdgtemp_t;
#define temp (sdgtemp.temp_)
#define tmat1 (sdgtemp.tmat1_)
#define tmat2 (sdgtemp.tmat2_)
#define tvec1 (sdgtemp.tvec1_)
#define tvec2 (sdgtemp.tvec2_)
#define tvec3 (sdgtemp.tvec3_)
#define tvec4 (sdgtemp.tvec4_)
#define tvec5 (sdgtemp.tvec5_)
#define tsc1 (sdgtemp.tsc1_)
#define tsc2 (sdgtemp.tsc2_)
#define tsc3 (sdgtemp.tsc3_)

sdgtopo_t sdgtopo = {
/*  Topological information
*/
    /* ground */ 1,
    /* nbod */ 10,
    /* ndof */ 21,
    /* ncons */ 0,
    /* nloop */ 0,
    /* nldof */ 0,
    /* nloopc */ 0,
    /* nball */ 0,
    /* nlball */ 0,
    /* npres */ 0,
    /* nuser */ 0,
    /* jtype[0] */ 10,
    /* jtype[1] */ 1,
    /* jtype[2] */ 1,
    /* jtype[3] */ 1,
    /* jtype[4] */ 3,
    /* jtype[5] */ 1,
    /* jtype[6] */ 2,
    /* jtype[7] */ 3,
    /* jtype[8] */ 1,
    /* jtype[9] */ 2,
    /* inb[0] */ -1,
    /* inb[1] */ 0,
    /* inb[2] */ 1,
    /* inb[3] */ 1,
    /* inb[4] */ 0,
    /* inb[5] */ 4,
    /* inb[6] */ 5,
    /* inb[7] */ 0,
    /* inb[8] */ 7,
    /* inb[9] */ 8,
    /* outb[0] */ 0,
    /* outb[1] */ 1,
    /* outb[2] */ 2,
    /* outb[3] */ 3,
    /* outb[4] */ 4,
    /* outb[5] */ 5,
    /* outb[6] */ 6,
    /* outb[7] */ 7,
    /* outb[8] */ 8,
    /* outb[9] */ 9,
    /* njntdof[0] */ 6,
    /* njntdof[1] */ 1,
    /* njntdof[2] */ 1,
    /* njntdof[3] */ 1,
    /* njntdof[4] */ 3,
    /* njntdof[5] */ 1,
    /* njntdof[6] */ 2,
    /* njntdof[7] */ 3,
    /* njntdof[8] */ 1,
    /* njntdof[9] */ 2,
    /* njntc[0] */ 0,
    /* njntc[1] */ 0,
    /* njntc[2] */ 0,
    /* njntc[3] */ 0,
    /* njntc[4] */ 0,
    /* njntc[5] */ 0,
    /* njntc[6] */ 0,
    /* njntc[7] */ 0,
    /* njntc[8] */ 0,
    /* njntc[9] */ 0,
    /* njntp[0] */ 0,
    /* njntp[1] */ 0,
    /* njntp[2] */ 0,
    /* njntp[3] */ 0,
    /* njntp[4] */ 0,
    /* njntp[5] */ 0,
    /* njntp[6] */ 0,
    /* njntp[7] */ 0,
    /* njntp[8] */ 0,
    /* njntp[9] */ 0,
    /* firstq[0] */ 0,
    /* firstq[1] */ 6,
    /* firstq[2] */ 7,
    /* firstq[3] */ 8,
    /* firstq[4] */ 9,
    /* firstq[5] */ 12,
    /* firstq[6] */ 13,
    /* firstq[7] */ 15,
    /* firstq[8] */ 18,
    /* firstq[9] */ 19,
    /* ballq[0] */ -104,
    /* ballq[1] */ -104,
    /* ballq[2] */ -104,
    /* ballq[3] */ -104,
    /* ballq[4] */ -104,
    /* ballq[5] */ -104,
    /* ballq[6] */ -104,
    /* ballq[7] */ -104,
    /* ballq[8] */ -104,
    /* ballq[9] */ -104,
    /* firstm[0] */ -1,
    /* firstm[1] */ -1,
    /* firstm[2] */ -1,
    /* firstm[3] */ -1,
    /* firstm[4] */ -1,
    /* firstm[5] */ -1,
    /* firstm[6] */ -1,
    /* firstm[7] */ -1,
    /* firstm[8] */ -1,
    /* firstm[9] */ -1,
    /* firstp[0] */ -1,
    /* firstp[1] */ -1,
    /* firstp[2] */ -1,
    /* firstp[3] */ -1,
    /* firstp[4] */ -1,
    /* firstp[5] */ -1,
    /* firstp[6] */ -1,
    /* firstp[7] */ -1,
    /* firstp[8] */ -1,
    /* firstp[9] */ -1,
    /* trans[0] */ 1,
    /* trans[1] */ 1,
    /* trans[2] */ 1,
    /* trans[3] */ 0,
    /* trans[4] */ 0,
    /* trans[5] */ 0,
    /* trans[6] */ 0,
    /* trans[7] */ 0,
    /* trans[8] */ 0,
    /* trans[9] */ 0,
    /* trans[10] */ 0,
    /* trans[11] */ 0,
    /* trans[12] */ 0,
    /* trans[13] */ 0,
    /* trans[14] */ 0,
    /* trans[15] */ 0,
    /* trans[16] */ 0,
    /* trans[17] */ 0,
    /* trans[18] */ 0,
    /* trans[19] */ 0,
    /* trans[20] */ 0,
};
sdginput_t sdginput = {
/* Model parameters from the input file */

/* gravity */
    /* grav[0] */ 0.,
    /* grav[1] */ 0.,
    /* grav[2] */ -9.8,

/* mass */
    /* mk[0] */ 0.,
    /* mk[1] */ 0.,
    /* mk[2] */ 0.,
    /* mk[3] */ 0.,
    /* mk[4] */ 0.,
    /* mk[5] */ 0.,
    /* mk[6] */ 0.,
    /* mk[7] */ 0.,
    /* mk[8] */ 0.,
    /* mk[9] */ 0.,

/* inertia */
    /* ik[0][0][0] */ 0.,
    /* ik[0][0][1] */ 0.,
    /* ik[0][0][2] */ 0.,
    /* ik[0][1][0] */ 0.,
    /* ik[0][1][1] */ 0.,
    /* ik[0][1][2] */ 0.,
    /* ik[0][2][0] */ 0.,
    /* ik[0][2][1] */ 0.,
    /* ik[0][2][2] */ 0.,
    /* ik[1][0][0] */ 0.,
    /* ik[1][0][1] */ 0.,
    /* ik[1][0][2] */ 0.,
    /* ik[1][1][0] */ 0.,
    /* ik[1][1][1] */ 0.,
    /* ik[1][1][2] */ 0.,
    /* ik[1][2][0] */ 0.,
    /* ik[1][2][1] */ 0.,
    /* ik[1][2][2] */ 0.,
    /* ik[2][0][0] */ 0.,
    /* ik[2][0][1] */ 0.,
    /* ik[2][0][2] */ 0.,
    /* ik[2][1][0] */ 0.,
    /* ik[2][1][1] */ 0.,
    /* ik[2][1][2] */ 0.,
    /* ik[2][2][0] */ 0.,
    /* ik[2][2][1] */ 0.,
    /* ik[2][2][2] */ 0.,
    /* ik[3][0][0] */ 0.,
    /* ik[3][0][1] */ 0.,
    /* ik[3][0][2] */ 0.,
    /* ik[3][1][0] */ 0.,
    /* ik[3][1][1] */ 0.,
    /* ik[3][1][2] */ 0.,
    /* ik[3][2][0] */ 0.,
    /* ik[3][2][1] */ 0.,
    /* ik[3][2][2] */ 0.,
    /* ik[4][0][0] */ 0.,
    /* ik[4][0][1] */ 0.,
    /* ik[4][0][2] */ 0.,
    /* ik[4][1][0] */ 0.,
    /* ik[4][1][1] */ 0.,
    /* ik[4][1][2] */ 0.,
    /* ik[4][2][0] */ 0.,
    /* ik[4][2][1] */ 0.,
    /* ik[4][2][2] */ 0.,
    /* ik[5][0][0] */ 0.,
    /* ik[5][0][1] */ 0.,
    /* ik[5][0][2] */ 0.,
    /* ik[5][1][0] */ 0.,
    /* ik[5][1][1] */ 0.,
    /* ik[5][1][2] */ 0.,
    /* ik[5][2][0] */ 0.,
    /* ik[5][2][1] */ 0.,
    /* ik[5][2][2] */ 0.,
    /* ik[6][0][0] */ 0.,
    /* ik[6][0][1] */ 0.,
    /* ik[6][0][2] */ 0.,
    /* ik[6][1][0] */ 0.,
    /* ik[6][1][1] */ 0.,
    /* ik[6][1][2] */ 0.,
    /* ik[6][2][0] */ 0.,
    /* ik[6][2][1] */ 0.,
    /* ik[6][2][2] */ 0.,
    /* ik[7][0][0] */ 0.,
    /* ik[7][0][1] */ 0.,
    /* ik[7][0][2] */ 0.,
    /* ik[7][1][0] */ 0.,
    /* ik[7][1][1] */ 0.,
    /* ik[7][1][2] */ 0.,
    /* ik[7][2][0] */ 0.,
    /* ik[7][2][1] */ 0.,
    /* ik[7][2][2] */ 0.,
    /* ik[8][0][0] */ 0.,
    /* ik[8][0][1] */ 0.,
    /* ik[8][0][2] */ 0.,
    /* ik[8][1][0] */ 0.,
    /* ik[8][1][1] */ 0.,
    /* ik[8][1][2] */ 0.,
    /* ik[8][2][0] */ 0.,
    /* ik[8][2][1] */ 0.,
    /* ik[8][2][2] */ 0.,
    /* ik[9][0][0] */ 0.,
    /* ik[9][0][1] */ 0.,
    /* ik[9][0][2] */ 0.,
    /* ik[9][1][0] */ 0.,
    /* ik[9][1][1] */ 0.,
    /* ik[9][1][2] */ 0.,
    /* ik[9][2][0] */ 0.,
    /* ik[9][2][1] */ 0.,
    /* ik[9][2][2] */ 0.,

/* tree hinge axis vectors */
    /* pin[0][0] */ 0.,
    /* pin[0][1] */ 0.,
    /* pin[0][2] */ 1.,
    /* pin[1][0] */ 0.,
    /* pin[1][1] */ 1.,
    /* pin[1][2] */ 0.,
    /* pin[2][0] */ 1.,
    /* pin[2][1] */ 0.,
    /* pin[2][2] */ 0.,
    /* pin[3][0] */ 0.,
    /* pin[3][1] */ 0.,
    /* pin[3][2] */ 1.,
    /* pin[4][0] */ 0.,
    /* pin[4][1] */ 1.,
    /* pin[4][2] */ 0.,
    /* pin[5][0] */ 1.,
    /* pin[5][1] */ 0.,
    /* pin[5][2] */ 0.,
    /* pin[6][0] */ 0.,
    /* pin[6][1] */ 0.,
    /* pin[6][2] */ 1.,
    /* pin[7][0] */ 0.,
    /* pin[7][1] */ 1.,
    /* pin[7][2] */ 0.,
    /* pin[8][0] */ 0.,
    /* pin[8][1] */ 1.,
    /* pin[8][2] */ 0.,
    /* pin[9][0] */ 0.,
    /* pin[9][1] */ 0.,
    /* pin[9][2] */ 1.,
    /* pin[10][0] */ 1.,
    /* pin[10][1] */ 0.,
    /* pin[10][2] */ 0.,
    /* pin[11][0] */ 0.,
    /* pin[11][1] */ 1.,
    /* pin[11][2] */ 0.,
    /* pin[12][0] */ 0.,
    /* pin[12][1] */ 1.,
    /* pin[12][2] */ 0.,
    /* pin[13][0] */ 0.,
    /* pin[13][1] */ 1.,
    /* pin[13][2] */ 0.,
    /* pin[14][0] */ 1.,
    /* pin[14][1] */ 0.,
    /* pin[14][2] */ 0.,
    /* pin[15][0] */ 0.,
    /* pin[15][1] */ 0.,
    /* pin[15][2] */ 1.,
    /* pin[16][0] */ 1.,
    /* pin[16][1] */ 0.,
    /* pin[16][2] */ 0.,
    /* pin[17][0] */ 0.,
    /* pin[17][1] */ 1.,
    /* pin[17][2] */ 0.,
    /* pin[18][0] */ 0.,
    /* pin[18][1] */ 1.,
    /* pin[18][2] */ 0.,
    /* pin[19][0] */ 0.,
    /* pin[19][1] */ 1.,
    /* pin[19][2] */ 0.,
    /* pin[20][0] */ 1.,
    /* pin[20][1] */ 0.,
    /* pin[20][2] */ 0.,

/* tree bodytojoint vectors */
    /* rk[0][0] */ 0.,
    /* rk[0][1] */ 0.,
    /* rk[0][2] */ 0.,
    /* rk[1][0] */ 0.,
    /* rk[1][1] */ 0.,
    /* rk[1][2] */ 0.,
    /* rk[2][0] */ 0.,
    /* rk[2][1] */ 0.,
    /* rk[2][2] */ 0.,
    /* rk[3][0] */ 0.,
    /* rk[3][1] */ 0.,
    /* rk[3][2] */ 0.,
    /* rk[4][0] */ 0.,
    /* rk[4][1] */ 0.,
    /* rk[4][2] */ 0.,
    /* rk[5][0] */ 0.,
    /* rk[5][1] */ 0.,
    /* rk[5][2] */ 0.,
    /* rk[6][0] */ 0.,
    /* rk[6][1] */ 0.,
    /* rk[6][2] */ 0.,
    /* rk[7][0] */ 0.,
    /* rk[7][1] */ 0.,
    /* rk[7][2] */ 0.,
    /* rk[8][0] */ 0.,
    /* rk[8][1] */ 0.,
    /* rk[8][2] */ 0.,
    /* rk[9][0] */ 0.,
    /* rk[9][1] */ 0.,
    /* rk[9][2] */ 0.,

/* tree inbtojoint vectors */
    /* ri[0][0] */ 0.,
    /* ri[0][1] */ 0.,
    /* ri[0][2] */ 0.,
    /* ri[1][0] */ 0.,
    /* ri[1][1] */ 0.,
    /* ri[1][2] */ 0.,
    /* ri[2][0] */ 0.,
    /* ri[2][1] */ 0.,
    /* ri[2][2] */ 0.,
    /* ri[3][0] */ 0.,
    /* ri[3][1] */ 0.,
    /* ri[3][2] */ 0.,
    /* ri[4][0] */ 0.,
    /* ri[4][1] */ 0.,
    /* ri[4][2] */ 0.,
    /* ri[5][0] */ 0.,
    /* ri[5][1] */ 0.,
    /* ri[5][2] */ 0.,
    /* ri[6][0] */ 0.,
    /* ri[6][1] */ 0.,
    /* ri[6][2] */ 0.,
    /* ri[7][0] */ 0.,
    /* ri[7][1] */ 0.,
    /* ri[7][2] */ 0.,
    /* ri[8][0] */ 0.,
    /* ri[8][1] */ 0.,
    /* ri[8][2] */ 0.,
    /* ri[9][0] */ 0.,
    /* ri[9][1] */ 0.,
    /* ri[9][2] */ 0.,

/* tree prescribed motion */
    /* pres[0] */ 0.,
    /* pres[1] */ 0.,
    /* pres[2] */ 0.,
    /* pres[3] */ 0.,
    /* pres[4] */ 0.,
    /* pres[5] */ 0.,
    /* pres[6] */ 0.,
    /* pres[7] */ 0.,
    /* pres[8] */ 0.,
    /* pres[9] */ 0.,
    /* pres[10] */ 0.,
    /* pres[11] */ 0.,
    /* pres[12] */ 0.,
    /* pres[13] */ 0.,
    /* pres[14] */ 0.,
    /* pres[15] */ 0.,
    /* pres[16] */ 0.,
    /* pres[17] */ 0.,
    /* pres[18] */ 0.,
    /* pres[19] */ 0.,
    /* pres[20] */ 0.,

/* stabilization parameters */
    /* stabvel */ 0.,
    /* stabpos */ 0.,

/* miscellaneous */
    /* mfrcflg */ 0,
    /* roustate */ 0,
    /* vpkflg */ 0,
    /* inerflg */ 0,
    /* mmflg */ 0,
    /* mmlduflg */ 0,
    /* wwflg */ 0,
    /* ltauflg */ 0,
    /* fs0flg */ 0,
    /* ii */ 0,
    /* mmap[0] */ 0,
    /* mmap[1] */ 1,
    /* mmap[2] */ 2,
    /* mmap[3] */ 3,
    /* mmap[4] */ 4,
    /* mmap[5] */ 5,
    /* mmap[6] */ 6,
    /* mmap[7] */ 7,
    /* mmap[8] */ 8,
    /* mmap[9] */ 9,
    /* mmap[10] */ 10,
    /* mmap[11] */ 11,
    /* mmap[12] */ 12,
    /* mmap[13] */ 13,
    /* mmap[14] */ 14,
    /* mmap[15] */ 15,
    /* mmap[16] */ 16,
    /* mmap[17] */ 17,
    /* mmap[18] */ 18,
    /* mmap[19] */ 19,
    /* mmap[20] */ 20,

/* Which parameters were "?" (1) or "<nominal>?" (3) */
    /* gravq[0] */ 0,
    /* gravq[1] */ 0,
    /* gravq[2] */ 0,
    /* mkq[0] */ 1,
    /* mkq[1] */ 1,
    /* mkq[2] */ 1,
    /* mkq[3] */ 1,
    /* mkq[4] */ 1,
    /* mkq[5] */ 1,
    /* mkq[6] */ 1,
    /* mkq[7] */ 1,
    /* mkq[8] */ 1,
    /* mkq[9] */ 1,
    /* ikq[0][0][0] */ 1,
    /* ikq[0][0][1] */ 0,
    /* ikq[0][0][2] */ 0,
    /* ikq[0][1][0] */ 0,
    /* ikq[0][1][1] */ 1,
    /* ikq[0][1][2] */ 0,
    /* ikq[0][2][0] */ 0,
    /* ikq[0][2][1] */ 0,
    /* ikq[0][2][2] */ 1,
    /* ikq[1][0][0] */ 1,
    /* ikq[1][0][1] */ 0,
    /* ikq[1][0][2] */ 0,
    /* ikq[1][1][0] */ 0,
    /* ikq[1][1][1] */ 1,
    /* ikq[1][1][2] */ 0,
    /* ikq[1][2][0] */ 0,
    /* ikq[1][2][1] */ 0,
    /* ikq[1][2][2] */ 1,
    /* ikq[2][0][0] */ 1,
    /* ikq[2][0][1] */ 0,
    /* ikq[2][0][2] */ 0,
    /* ikq[2][1][0] */ 0,
    /* ikq[2][1][1] */ 1,
    /* ikq[2][1][2] */ 0,
    /* ikq[2][2][0] */ 0,
    /* ikq[2][2][1] */ 0,
    /* ikq[2][2][2] */ 1,
    /* ikq[3][0][0] */ 1,
    /* ikq[3][0][1] */ 0,
    /* ikq[3][0][2] */ 0,
    /* ikq[3][1][0] */ 0,
    /* ikq[3][1][1] */ 1,
    /* ikq[3][1][2] */ 0,
    /* ikq[3][2][0] */ 0,
    /* ikq[3][2][1] */ 0,
    /* ikq[3][2][2] */ 1,
    /* ikq[4][0][0] */ 1,
    /* ikq[4][0][1] */ 0,
    /* ikq[4][0][2] */ 0,
    /* ikq[4][1][0] */ 0,
    /* ikq[4][1][1] */ 1,
    /* ikq[4][1][2] */ 0,
    /* ikq[4][2][0] */ 0,
    /* ikq[4][2][1] */ 0,
    /* ikq[4][2][2] */ 1,
    /* ikq[5][0][0] */ 1,
    /* ikq[5][0][1] */ 0,
    /* ikq[5][0][2] */ 0,
    /* ikq[5][1][0] */ 0,
    /* ikq[5][1][1] */ 1,
    /* ikq[5][1][2] */ 0,
    /* ikq[5][2][0] */ 0,
    /* ikq[5][2][1] */ 0,
    /* ikq[5][2][2] */ 1,
    /* ikq[6][0][0] */ 1,
    /* ikq[6][0][1] */ 0,
    /* ikq[6][0][2] */ 0,
    /* ikq[6][1][0] */ 0,
    /* ikq[6][1][1] */ 1,
    /* ikq[6][1][2] */ 0,
    /* ikq[6][2][0] */ 0,
    /* ikq[6][2][1] */ 0,
    /* ikq[6][2][2] */ 1,
    /* ikq[7][0][0] */ 1,
    /* ikq[7][0][1] */ 0,
    /* ikq[7][0][2] */ 0,
    /* ikq[7][1][0] */ 0,
    /* ikq[7][1][1] */ 1,
    /* ikq[7][1][2] */ 0,
    /* ikq[7][2][0] */ 0,
    /* ikq[7][2][1] */ 0,
    /* ikq[7][2][2] */ 1,
    /* ikq[8][0][0] */ 1,
    /* ikq[8][0][1] */ 0,
    /* ikq[8][0][2] */ 0,
    /* ikq[8][1][0] */ 0,
    /* ikq[8][1][1] */ 1,
    /* ikq[8][1][2] */ 0,
    /* ikq[8][2][0] */ 0,
    /* ikq[8][2][1] */ 0,
    /* ikq[8][2][2] */ 1,
    /* ikq[9][0][0] */ 1,
    /* ikq[9][0][1] */ 0,
    /* ikq[9][0][2] */ 0,
    /* ikq[9][1][0] */ 0,
    /* ikq[9][1][1] */ 1,
    /* ikq[9][1][2] */ 0,
    /* ikq[9][2][0] */ 0,
    /* ikq[9][2][1] */ 0,
    /* ikq[9][2][2] */ 1,
    /* pinq[0][0] */ 0,
    /* pinq[0][1] */ 0,
    /* pinq[0][2] */ 0,
    /* pinq[1][0] */ 0,
    /* pinq[1][1] */ 0,
    /* pinq[1][2] */ 0,
    /* pinq[2][0] */ 0,
    /* pinq[2][1] */ 0,
    /* pinq[2][2] */ 0,
    /* pinq[3][0] */ 0,
    /* pinq[3][1] */ 0,
    /* pinq[3][2] */ 0,
    /* pinq[4][0] */ 0,
    /* pinq[4][1] */ 0,
    /* pinq[4][2] */ 0,
    /* pinq[5][0] */ 0,
    /* pinq[5][1] */ 0,
    /* pinq[5][2] */ 0,
    /* pinq[6][0] */ 0,
    /* pinq[6][1] */ 0,
    /* pinq[6][2] */ 0,
    /* pinq[7][0] */ 0,
    /* pinq[7][1] */ 0,
    /* pinq[7][2] */ 0,
    /* pinq[8][0] */ 0,
    /* pinq[8][1] */ 0,
    /* pinq[8][2] */ 0,
    /* pinq[9][0] */ 0,
    /* pinq[9][1] */ 0,
    /* pinq[9][2] */ 0,
    /* pinq[10][0] */ 0,
    /* pinq[10][1] */ 0,
    /* pinq[10][2] */ 0,
    /* pinq[11][0] */ 0,
    /* pinq[11][1] */ 0,
    /* pinq[11][2] */ 0,
    /* pinq[12][0] */ 0,
    /* pinq[12][1] */ 0,
    /* pinq[12][2] */ 0,
    /* pinq[13][0] */ 0,
    /* pinq[13][1] */ 0,
    /* pinq[13][2] */ 0,
    /* pinq[14][0] */ 0,
    /* pinq[14][1] */ 0,
    /* pinq[14][2] */ 0,
    /* pinq[15][0] */ 0,
    /* pinq[15][1] */ 0,
    /* pinq[15][2] */ 0,
    /* pinq[16][0] */ 0,
    /* pinq[16][1] */ 0,
    /* pinq[16][2] */ 0,
    /* pinq[17][0] */ 0,
    /* pinq[17][1] */ 0,
    /* pinq[17][2] */ 0,
    /* pinq[18][0] */ 0,
    /* pinq[18][1] */ 0,
    /* pinq[18][2] */ 0,
    /* pinq[19][0] */ 0,
    /* pinq[19][1] */ 0,
    /* pinq[19][2] */ 0,
    /* pinq[20][0] */ 0,
    /* pinq[20][1] */ 0,
    /* pinq[20][2] */ 0,
    /* rkq[0][0] */ 1,
    /* rkq[0][1] */ 1,
    /* rkq[0][2] */ 1,
    /* rkq[1][0] */ 1,
    /* rkq[1][1] */ 1,
    /* rkq[1][2] */ 1,
    /* rkq[2][0] */ 1,
    /* rkq[2][1] */ 1,
    /* rkq[2][2] */ 1,
    /* rkq[3][0] */ 1,
    /* rkq[3][1] */ 1,
    /* rkq[3][2] */ 1,
    /* rkq[4][0] */ 1,
    /* rkq[4][1] */ 1,
    /* rkq[4][2] */ 1,
    /* rkq[5][0] */ 1,
    /* rkq[5][1] */ 1,
    /* rkq[5][2] */ 1,
    /* rkq[6][0] */ 1,
    /* rkq[6][1] */ 1,
    /* rkq[6][2] */ 1,
    /* rkq[7][0] */ 1,
    /* rkq[7][1] */ 1,
    /* rkq[7][2] */ 1,
    /* rkq[8][0] */ 1,
    /* rkq[8][1] */ 1,
    /* rkq[8][2] */ 1,
    /* rkq[9][0] */ 1,
    /* rkq[9][1] */ 1,
    /* rkq[9][2] */ 1,
    /* riq[0][0] */ 1,
    /* riq[0][1] */ 1,
    /* riq[0][2] */ 1,
    /* riq[1][0] */ 1,
    /* riq[1][1] */ 1,
    /* riq[1][2] */ 1,
    /* riq[2][0] */ 1,
    /* riq[2][1] */ 1,
    /* riq[2][2] */ 1,
    /* riq[3][0] */ 1,
    /* riq[3][1] */ 1,
    /* riq[3][2] */ 1,
    /* riq[4][0] */ 1,
    /* riq[4][1] */ 1,
    /* riq[4][2] */ 1,
    /* riq[5][0] */ 1,
    /* riq[5][1] */ 1,
    /* riq[5][2] */ 1,
    /* riq[6][0] */ 1,
    /* riq[6][1] */ 1,
    /* riq[6][2] */ 1,
    /* riq[7][0] */ 1,
    /* riq[7][1] */ 1,
    /* riq[7][2] */ 1,
    /* riq[8][0] */ 1,
    /* riq[8][1] */ 1,
    /* riq[8][2] */ 1,
    /* riq[9][0] */ 1,
    /* riq[9][1] */ 1,
    /* riq[9][2] */ 1,
    /* presq[0] */ 0,
    /* presq[1] */ 0,
    /* presq[2] */ 0,
    /* presq[3] */ 0,
    /* presq[4] */ 0,
    /* presq[5] */ 0,
    /* presq[6] */ 0,
    /* presq[7] */ 0,
    /* presq[8] */ 0,
    /* presq[9] */ 0,
    /* presq[10] */ 0,
    /* presq[11] */ 0,
    /* presq[12] */ 0,
    /* presq[13] */ 0,
    /* presq[14] */ 0,
    /* presq[15] */ 0,
    /* presq[16] */ 0,
    /* presq[17] */ 0,
    /* presq[18] */ 0,
    /* presq[19] */ 0,
    /* presq[20] */ 0,
    /* stabvelq */ 3,
    /* stabposq */ 3,

/* End of values from input file */

};
sdgstate_t sdgstate;
sdglhs_t sdglhs;
sdgrhs_t sdgrhs;
sdgtemp_t sdgtemp;


void sdinit(void)
{
/*
Initialization routine


 This routine must be called before the first call to sdstate(), after
 supplying values for any `?' parameters in the input.
*/
    double sumsq,norminv;
    int i,j,k;


/* Check that all `?' parameters have been assigned values */

    for (k = 0; k < 3; k++) {
        if (gravq[k] == 1) {
            sdseterr(7,25);
        }
    }
    for (k = 0; k < 10; k++) {
        if (mkq[k] == 1) {
            sdseterr(7,26);
        }
        for (i = 0; i < 3; i++) {
            if (rkq[k][i] == 1) {
                sdseterr(7,29);
            }
            if (riq[k][i] == 1) {
                sdseterr(7,30);
            }
            for (j = 0; j < 3; j++) {
                if (ikq[k][i][j] == 1) {
                    sdseterr(7,27);
                }
            }
        }
    }
    for (k = 0; k < 21; k++) {
        for (i = 0; i < 3; i++) {
            if (pinq[k][i] == 1) {
                sdseterr(7,28);
            }
        }
    }

/* Normalize pin vectors if necessary */


/* Zero out Vpk and Wpk */

    for (i = 0; i < 21; i++) {
        for (j = i; j <= 20; j++) {
            for (k = 0; k < 3; k++) {
                Vpk[i][j][k] = 0.;
                Wpk[i][j][k] = 0.;
            }
        }
    }

/* Compute pseudobody-related constants */

    rcom[0][0] = 0.;
    rcom[0][1] = 0.;
    rcom[0][2] = 0.;
    rcom[1][0] = 0.;
    rcom[1][1] = 0.;
    rcom[1][2] = 0.;
    rcom[2][0] = 0.;
    rcom[2][1] = 0.;
    rcom[2][2] = 0.;
    rcom[3][0] = 0.;
    rcom[3][1] = 0.;
    rcom[3][2] = 0.;
    rcom[4][0] = 0.;
    rcom[4][1] = 0.;
    rcom[4][2] = 0.;
    rcom[5][0] = 0.;
    rcom[5][1] = 0.;
    rcom[5][2] = 0.;
    rcom[6][0] = 0.;
    rcom[6][1] = 0.;
    rcom[6][2] = 0.;
    rcom[7][0] = 0.;
    rcom[7][1] = 0.;
    rcom[7][2] = 0.;
    rcom[8][0] = 0.;
    rcom[8][1] = 0.;
    rcom[8][2] = 0.;
    rcom[9][0] = 0.;
    rcom[9][1] = 0.;
    rcom[9][2] = 0.;
    dik[6][0] = (ri[1][0]-rk[0][0]);
    dik[6][1] = (ri[1][1]-rk[0][1]);
    dik[6][2] = (ri[1][2]-rk[0][2]);
    dik[7][0] = (ri[2][0]-rk[1][0]);
    dik[7][1] = (ri[2][1]-rk[1][1]);
    dik[7][2] = (ri[2][2]-rk[1][2]);
    dik[8][0] = (ri[3][0]-rk[1][0]);
    dik[8][1] = (ri[3][1]-rk[1][1]);
    dik[8][2] = (ri[3][2]-rk[1][2]);
    dik[9][0] = (ri[4][0]-rk[0][0]);
    dik[9][1] = (ri[4][1]-rk[0][1]);
    dik[9][2] = (ri[4][2]-rk[0][2]);
    dik[12][0] = (ri[5][0]-rk[4][0]);
    dik[12][1] = (ri[5][1]-rk[4][1]);
    dik[12][2] = (ri[5][2]-rk[4][2]);
    dik[13][0] = (ri[6][0]-rk[5][0]);
    dik[13][1] = (ri[6][1]-rk[5][1]);
    dik[13][2] = (ri[6][2]-rk[5][2]);
    dik[15][0] = (ri[7][0]-rk[0][0]);
    dik[15][1] = (ri[7][1]-rk[0][1]);
    dik[15][2] = (ri[7][2]-rk[0][2]);
    dik[18][0] = (ri[8][0]-rk[7][0]);
    dik[18][1] = (ri[8][1]-rk[7][1]);
    dik[18][2] = (ri[8][2]-rk[7][2]);
    dik[19][0] = (ri[9][0]-rk[8][0]);
    dik[19][1] = (ri[9][1]-rk[8][1]);
    dik[19][2] = (ri[9][2]-rk[8][2]);

/* Compute mass properties-related constants */

    mtot = (mk[9]+(mk[8]+(mk[7]+(mk[6]+(mk[5]+(mk[4]+(mk[3]+(mk[2]+(mk[0]+mk[1])
      ))))))));
    mkrk[5][0][1] = -(mk[0]*rk[0][2]);
    mkrk[5][0][2] = (mk[0]*rk[0][1]);
    mkrk[5][1][0] = (mk[0]*rk[0][2]);
    mkrk[5][1][2] = -(mk[0]*rk[0][0]);
    mkrk[5][2][0] = -(mk[0]*rk[0][1]);
    mkrk[5][2][1] = (mk[0]*rk[0][0]);
    mkrk[6][0][1] = -(mk[1]*rk[1][2]);
    mkrk[6][0][2] = (mk[1]*rk[1][1]);
    mkrk[6][1][0] = (mk[1]*rk[1][2]);
    mkrk[6][1][2] = -(mk[1]*rk[1][0]);
    mkrk[6][2][0] = -(mk[1]*rk[1][1]);
    mkrk[6][2][1] = (mk[1]*rk[1][0]);
    mkrk[7][0][1] = -(mk[2]*rk[2][2]);
    mkrk[7][0][2] = (mk[2]*rk[2][1]);
    mkrk[7][1][0] = (mk[2]*rk[2][2]);
    mkrk[7][1][2] = -(mk[2]*rk[2][0]);
    mkrk[7][2][0] = -(mk[2]*rk[2][1]);
    mkrk[7][2][1] = (mk[2]*rk[2][0]);
    mkrk[8][0][1] = -(mk[3]*rk[3][2]);
    mkrk[8][0][2] = (mk[3]*rk[3][1]);
    mkrk[8][1][0] = (mk[3]*rk[3][2]);
    mkrk[8][1][2] = -(mk[3]*rk[3][0]);
    mkrk[8][2][0] = -(mk[3]*rk[3][1]);
    mkrk[8][2][1] = (mk[3]*rk[3][0]);
    mkrk[11][0][1] = -(mk[4]*rk[4][2]);
    mkrk[11][0][2] = (mk[4]*rk[4][1]);
    mkrk[11][1][0] = (mk[4]*rk[4][2]);
    mkrk[11][1][2] = -(mk[4]*rk[4][0]);
    mkrk[11][2][0] = -(mk[4]*rk[4][1]);
    mkrk[11][2][1] = (mk[4]*rk[4][0]);
    mkrk[12][0][1] = -(mk[5]*rk[5][2]);
    mkrk[12][0][2] = (mk[5]*rk[5][1]);
    mkrk[12][1][0] = (mk[5]*rk[5][2]);
    mkrk[12][1][2] = -(mk[5]*rk[5][0]);
    mkrk[12][2][0] = -(mk[5]*rk[5][1]);
    mkrk[12][2][1] = (mk[5]*rk[5][0]);
    mkrk[14][0][1] = -(mk[6]*rk[6][2]);
    mkrk[14][0][2] = (mk[6]*rk[6][1]);
    mkrk[14][1][0] = (mk[6]*rk[6][2]);
    mkrk[14][1][2] = -(mk[6]*rk[6][0]);
    mkrk[14][2][0] = -(mk[6]*rk[6][1]);
    mkrk[14][2][1] = (mk[6]*rk[6][0]);
    mkrk[17][0][1] = -(mk[7]*rk[7][2]);
    mkrk[17][0][2] = (mk[7]*rk[7][1]);
    mkrk[17][1][0] = (mk[7]*rk[7][2]);
    mkrk[17][1][2] = -(mk[7]*rk[7][0]);
    mkrk[17][2][0] = -(mk[7]*rk[7][1]);
    mkrk[17][2][1] = (mk[7]*rk[7][0]);
    mkrk[18][0][1] = -(mk[8]*rk[8][2]);
    mkrk[18][0][2] = (mk[8]*rk[8][1]);
    mkrk[18][1][0] = (mk[8]*rk[8][2]);
    mkrk[18][1][2] = -(mk[8]*rk[8][0]);
    mkrk[18][2][0] = -(mk[8]*rk[8][1]);
    mkrk[18][2][1] = (mk[8]*rk[8][0]);
    mkrk[20][0][1] = -(mk[9]*rk[9][2]);
    mkrk[20][0][2] = (mk[9]*rk[9][1]);
    mkrk[20][1][0] = (mk[9]*rk[9][2]);
    mkrk[20][1][2] = -(mk[9]*rk[9][0]);
    mkrk[20][2][0] = -(mk[9]*rk[9][1]);
    mkrk[20][2][1] = (mk[9]*rk[9][0]);
    Iko[5][0][0] = (ik[0][0][0]-((mkrk[5][0][1]*rk[0][2])-(mkrk[5][0][2]*
      rk[0][1])));
    Iko[5][0][1] = -(mkrk[5][0][2]*rk[0][0]);
    Iko[5][0][2] = (mkrk[5][0][1]*rk[0][0]);
    Iko[5][1][0] = (mkrk[5][1][2]*rk[0][1]);
    Iko[5][1][1] = (ik[0][1][1]-((mkrk[5][1][2]*rk[0][0])-(mkrk[5][1][0]*
      rk[0][2])));
    Iko[5][1][2] = -(mkrk[5][1][0]*rk[0][1]);
    Iko[5][2][0] = -(mkrk[5][2][1]*rk[0][2]);
    Iko[5][2][1] = (mkrk[5][2][0]*rk[0][2]);
    Iko[5][2][2] = (ik[0][2][2]-((mkrk[5][2][0]*rk[0][1])-(mkrk[5][2][1]*
      rk[0][0])));
    Iko[6][0][0] = (ik[1][0][0]-((mkrk[6][0][1]*rk[1][2])-(mkrk[6][0][2]*
      rk[1][1])));
    Iko[6][0][1] = -(mkrk[6][0][2]*rk[1][0]);
    Iko[6][0][2] = (mkrk[6][0][1]*rk[1][0]);
    Iko[6][1][0] = (mkrk[6][1][2]*rk[1][1]);
    Iko[6][1][1] = (ik[1][1][1]-((mkrk[6][1][2]*rk[1][0])-(mkrk[6][1][0]*
      rk[1][2])));
    Iko[6][1][2] = -(mkrk[6][1][0]*rk[1][1]);
    Iko[6][2][0] = -(mkrk[6][2][1]*rk[1][2]);
    Iko[6][2][1] = (mkrk[6][2][0]*rk[1][2]);
    Iko[6][2][2] = (ik[1][2][2]-((mkrk[6][2][0]*rk[1][1])-(mkrk[6][2][1]*
      rk[1][0])));
    Iko[7][0][0] = (ik[2][0][0]-((mkrk[7][0][1]*rk[2][2])-(mkrk[7][0][2]*
      rk[2][1])));
    Iko[7][0][1] = -(mkrk[7][0][2]*rk[2][0]);
    Iko[7][0][2] = (mkrk[7][0][1]*rk[2][0]);
    Iko[7][1][0] = (mkrk[7][1][2]*rk[2][1]);
    Iko[7][1][1] = (ik[2][1][1]-((mkrk[7][1][2]*rk[2][0])-(mkrk[7][1][0]*
      rk[2][2])));
    Iko[7][1][2] = -(mkrk[7][1][0]*rk[2][1]);
    Iko[7][2][0] = -(mkrk[7][2][1]*rk[2][2]);
    Iko[7][2][1] = (mkrk[7][2][0]*rk[2][2]);
    Iko[7][2][2] = (ik[2][2][2]-((mkrk[7][2][0]*rk[2][1])-(mkrk[7][2][1]*
      rk[2][0])));
    Iko[8][0][0] = (ik[3][0][0]-((mkrk[8][0][1]*rk[3][2])-(mkrk[8][0][2]*
      rk[3][1])));
    Iko[8][0][1] = -(mkrk[8][0][2]*rk[3][0]);
    Iko[8][0][2] = (mkrk[8][0][1]*rk[3][0]);
    Iko[8][1][0] = (mkrk[8][1][2]*rk[3][1]);
    Iko[8][1][1] = (ik[3][1][1]-((mkrk[8][1][2]*rk[3][0])-(mkrk[8][1][0]*
      rk[3][2])));
    Iko[8][1][2] = -(mkrk[8][1][0]*rk[3][1]);
    Iko[8][2][0] = -(mkrk[8][2][1]*rk[3][2]);
    Iko[8][2][1] = (mkrk[8][2][0]*rk[3][2]);
    Iko[8][2][2] = (ik[3][2][2]-((mkrk[8][2][0]*rk[3][1])-(mkrk[8][2][1]*
      rk[3][0])));
    Iko[11][0][0] = (ik[4][0][0]-((mkrk[11][0][1]*rk[4][2])-(mkrk[11][0][2]*
      rk[4][1])));
    Iko[11][0][1] = -(mkrk[11][0][2]*rk[4][0]);
    Iko[11][0][2] = (mkrk[11][0][1]*rk[4][0]);
    Iko[11][1][0] = (mkrk[11][1][2]*rk[4][1]);
    Iko[11][1][1] = (ik[4][1][1]-((mkrk[11][1][2]*rk[4][0])-(mkrk[11][1][0]*
      rk[4][2])));
    Iko[11][1][2] = -(mkrk[11][1][0]*rk[4][1]);
    Iko[11][2][0] = -(mkrk[11][2][1]*rk[4][2]);
    Iko[11][2][1] = (mkrk[11][2][0]*rk[4][2]);
    Iko[11][2][2] = (ik[4][2][2]-((mkrk[11][2][0]*rk[4][1])-(mkrk[11][2][1]*
      rk[4][0])));
    Iko[12][0][0] = (ik[5][0][0]-((mkrk[12][0][1]*rk[5][2])-(mkrk[12][0][2]*
      rk[5][1])));
    Iko[12][0][1] = -(mkrk[12][0][2]*rk[5][0]);
    Iko[12][0][2] = (mkrk[12][0][1]*rk[5][0]);
    Iko[12][1][0] = (mkrk[12][1][2]*rk[5][1]);
    Iko[12][1][1] = (ik[5][1][1]-((mkrk[12][1][2]*rk[5][0])-(mkrk[12][1][0]*
      rk[5][2])));
    Iko[12][1][2] = -(mkrk[12][1][0]*rk[5][1]);
    Iko[12][2][0] = -(mkrk[12][2][1]*rk[5][2]);
    Iko[12][2][1] = (mkrk[12][2][0]*rk[5][2]);
    Iko[12][2][2] = (ik[5][2][2]-((mkrk[12][2][0]*rk[5][1])-(mkrk[12][2][1]*
      rk[5][0])));
    Iko[14][0][0] = (ik[6][0][0]-((mkrk[14][0][1]*rk[6][2])-(mkrk[14][0][2]*
      rk[6][1])));
    Iko[14][0][1] = -(mkrk[14][0][2]*rk[6][0]);
    Iko[14][0][2] = (mkrk[14][0][1]*rk[6][0]);
    Iko[14][1][0] = (mkrk[14][1][2]*rk[6][1]);
    Iko[14][1][1] = (ik[6][1][1]-((mkrk[14][1][2]*rk[6][0])-(mkrk[14][1][0]*
      rk[6][2])));
    Iko[14][1][2] = -(mkrk[14][1][0]*rk[6][1]);
    Iko[14][2][0] = -(mkrk[14][2][1]*rk[6][2]);
    Iko[14][2][1] = (mkrk[14][2][0]*rk[6][2]);
    Iko[14][2][2] = (ik[6][2][2]-((mkrk[14][2][0]*rk[6][1])-(mkrk[14][2][1]*
      rk[6][0])));
    Iko[17][0][0] = (ik[7][0][0]-((mkrk[17][0][1]*rk[7][2])-(mkrk[17][0][2]*
      rk[7][1])));
    Iko[17][0][1] = -(mkrk[17][0][2]*rk[7][0]);
    Iko[17][0][2] = (mkrk[17][0][1]*rk[7][0]);
    Iko[17][1][0] = (mkrk[17][1][2]*rk[7][1]);
    Iko[17][1][1] = (ik[7][1][1]-((mkrk[17][1][2]*rk[7][0])-(mkrk[17][1][0]*
      rk[7][2])));
    Iko[17][1][2] = -(mkrk[17][1][0]*rk[7][1]);
    Iko[17][2][0] = -(mkrk[17][2][1]*rk[7][2]);
    Iko[17][2][1] = (mkrk[17][2][0]*rk[7][2]);
    Iko[17][2][2] = (ik[7][2][2]-((mkrk[17][2][0]*rk[7][1])-(mkrk[17][2][1]*
      rk[7][0])));
    Iko[18][0][0] = (ik[8][0][0]-((mkrk[18][0][1]*rk[8][2])-(mkrk[18][0][2]*
      rk[8][1])));
    Iko[18][0][1] = -(mkrk[18][0][2]*rk[8][0]);
    Iko[18][0][2] = (mkrk[18][0][1]*rk[8][0]);
    Iko[18][1][0] = (mkrk[18][1][2]*rk[8][1]);
    Iko[18][1][1] = (ik[8][1][1]-((mkrk[18][1][2]*rk[8][0])-(mkrk[18][1][0]*
      rk[8][2])));
    Iko[18][1][2] = -(mkrk[18][1][0]*rk[8][1]);
    Iko[18][2][0] = -(mkrk[18][2][1]*rk[8][2]);
    Iko[18][2][1] = (mkrk[18][2][0]*rk[8][2]);
    Iko[18][2][2] = (ik[8][2][2]-((mkrk[18][2][0]*rk[8][1])-(mkrk[18][2][1]*
      rk[8][0])));
    Iko[20][0][0] = (ik[9][0][0]-((mkrk[20][0][1]*rk[9][2])-(mkrk[20][0][2]*
      rk[9][1])));
    Iko[20][0][1] = -(mkrk[20][0][2]*rk[9][0]);
    Iko[20][0][2] = (mkrk[20][0][1]*rk[9][0]);
    Iko[20][1][0] = (mkrk[20][1][2]*rk[9][1]);
    Iko[20][1][1] = (ik[9][1][1]-((mkrk[20][1][2]*rk[9][0])-(mkrk[20][1][0]*
      rk[9][2])));
    Iko[20][1][2] = -(mkrk[20][1][0]*rk[9][1]);
    Iko[20][2][0] = -(mkrk[20][2][1]*rk[9][2]);
    Iko[20][2][1] = (mkrk[20][2][0]*rk[9][2]);
    Iko[20][2][2] = (ik[9][2][2]-((mkrk[20][2][0]*rk[9][1])-(mkrk[20][2][1]*
      rk[9][0])));
    sdserialno(&i);
    if (i != 30123) {
        sdseterr(7,41);
    }
    roustate = 1;
}

/* Convert state to form using 1-2-3 Euler angles for ball joints. */

void sdst2ang(double st[21],
    double stang[21])
{
    int i;

    for (i = 0; i < 21; i++) {
        stang[i] = st[i];
    }
}

/* Convert 1-2-3 form of state back to Euler parameters for ball joints. */

void sdang2st(double stang[21],
    double st[21])
{
    int i;

    for (i = 0; i < 21; i++) {
        st[i] = stang[i];
    }
}

/* Normalize Euler parameters in state. */

void sdnrmsterr(double st[21],
    double normst[21],
    int routine)
{
    int i;

    for (i = 0; i < 21; i++) {
        normst[i] = st[i];
    }
}

void sdnormst(double st[21],
    double normst[21])
{

    sdnrmsterr(st,normst,0);
}

void sdstate(double timein,
    double qin[21],
    double uin[21])
{
/*
Compute kinematic information and store it in sdgstate.

Generated 01-Jan-1999 18:58:22 by SD/FAST, Kane's formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
    int i,j,qchg,uchg;

    if ((roustate != 1) && (roustate != 2) && (roustate != 3)) {
        sdseterr(8,22);
        return;
    }
    if (roustate == 1) {
        for (i = 0; i < 21; i++) {
            if (presq[i] == 1) {
                sdseterr(8,31);
            }
        }
    }
/*
See if time or any qs have changed since last call
*/
    if ((roustate != 1) && (timein == curtim)) {
        qchg = 0;
        for (i = 0; i < 21; i++) {
            if (qin[i] != q[i]) {
                qchg = 1;
                break;
            }
        }
    } else {
        qchg = 1;
    }
/*
If time and qs are unchanged, check us
*/
    if (qchg == 0) {
        uchg = 0;
        for (i = 0; i < 21; i++) {
            if (uin[i] != u[i]) {
                uchg = 1;
                break;
            }
        }
    } else {
        uchg = 1;
    }
    curtim = timein;
    roustate = 2;
    if (qchg == 0) {
        goto skipqs;
    }
/*
Position-related variables need to be computed
*/
    vpkflg = 0;
    mmflg = 0;
    mmlduflg = 0;
    wwflg = 0;
    for (i = 0; i < 21; i++) {
        q[i] = qin[i];
    }
/*
Compute sines and cosines of q
*/
    s3 = sin(q[3]);
    c3 = cos(q[3]);
    s4 = sin(q[4]);
    c4 = cos(q[4]);
    s5 = sin(q[5]);
    c5 = cos(q[5]);
    s6 = sin(q[6]);
    c6 = cos(q[6]);
    s7 = sin(q[7]);
    c7 = cos(q[7]);
    s8 = sin(q[8]);
    c8 = cos(q[8]);
    s9 = sin(q[9]);
    c9 = cos(q[9]);
    s10 = sin(q[10]);
    c10 = cos(q[10]);
    s11 = sin(q[11]);
    c11 = cos(q[11]);
    s12 = sin(q[12]);
    c12 = cos(q[12]);
    s13 = sin(q[13]);
    c13 = cos(q[13]);
    s14 = sin(q[14]);
    c14 = cos(q[14]);
    s15 = sin(q[15]);
    c15 = cos(q[15]);
    s16 = sin(q[16]);
    c16 = cos(q[16]);
    s17 = sin(q[17]);
    c17 = cos(q[17]);
    s18 = sin(q[18]);
    c18 = cos(q[18]);
    s19 = sin(q[19]);
    c19 = cos(q[19]);
    s20 = sin(q[20]);
    c20 = cos(q[20]);
/*
Compute across-axis direction cosines Cik
*/
/*
Compute across-joint direction cosines Cib
*/
    Cib[0][0][0] = (c3*c4);
    Cib[0][0][1] = ((s5*(s4*c3))-(s3*c5));
    Cib[0][0][2] = ((s3*s5)+(c5*(s4*c3)));
    Cib[0][1][0] = (s3*c4);
    Cib[0][1][1] = ((s5*(s3*s4))+(c3*c5));
    Cib[0][1][2] = ((c5*(s3*s4))-(s5*c3));
    Cib[0][2][1] = (s5*c4);
    Cib[0][2][2] = (c4*c5);
    Cib[4][0][0] = ((c9*c11)-(s11*(s9*s10)));
    Cib[4][0][1] = -(s9*c10);
    Cib[4][0][2] = ((s11*c9)+(c11*(s9*s10)));
    Cib[4][1][0] = ((s9*c11)+(s11*(s10*c9)));
    Cib[4][1][1] = (c9*c10);
    Cib[4][1][2] = ((s9*s11)-(c11*(s10*c9)));
    Cib[4][2][0] = -(s11*c10);
    Cib[4][2][2] = (c10*c11);
    Cib[6][0][1] = (s13*s14);
    Cib[6][0][2] = (s13*c14);
    Cib[6][2][1] = (s14*c13);
    Cib[6][2][2] = (c13*c14);
    Cib[7][0][0] = ((c15*c17)-(s17*(s15*s16)));
    Cib[7][0][1] = -(s15*c16);
    Cib[7][0][2] = ((s17*c15)+(c17*(s15*s16)));
    Cib[7][1][0] = ((s15*c17)+(s17*(s16*c15)));
    Cib[7][1][1] = (c15*c16);
    Cib[7][1][2] = ((s15*s17)-(c17*(s16*c15)));
    Cib[7][2][0] = -(s17*c16);
    Cib[7][2][2] = (c16*c17);
    Cib[9][0][1] = (s19*s20);
    Cib[9][0][2] = (s19*c20);
    Cib[9][2][1] = (s20*c19);
    Cib[9][2][2] = (c19*c20);
/*
Compute gravity
*/
    gk[5][1] = -(9.8*(s5*c4));
    gk[5][2] = -(9.8*(c4*c5));
    gk[6][0] = ((9.8*(s4*c6))+(gk[5][1]*s6));
    gk[6][1] = ((gk[5][1]*c6)-(9.8*(s4*s6)));
    gk[7][0] = ((gk[6][0]*c7)-(gk[5][2]*s7));
    gk[7][2] = ((gk[5][2]*c7)+(gk[6][0]*s7));
    gk[8][0] = ((gk[6][0]*c8)-(gk[5][2]*s8));
    gk[8][2] = ((gk[5][2]*c8)+(gk[6][0]*s8));
    gk[9][0] = ((9.8*(s4*c9))+(gk[5][1]*s9));
    gk[9][1] = ((gk[5][1]*c9)-(9.8*(s4*s9)));
    gk[10][1] = ((gk[5][2]*s10)+(gk[9][1]*c10));
    gk[10][2] = ((gk[5][2]*c10)-(gk[9][1]*s10));
    gk[11][0] = ((gk[9][0]*c11)-(gk[10][2]*s11));
    gk[11][2] = ((gk[9][0]*s11)+(gk[10][2]*c11));
    gk[12][0] = ((gk[11][0]*c12)-(gk[11][2]*s12));
    gk[12][2] = ((gk[11][0]*s12)+(gk[11][2]*c12));
    gk[13][0] = ((gk[12][0]*c13)-(gk[12][2]*s13));
    gk[13][2] = ((gk[12][0]*s13)+(gk[12][2]*c13));
    gk[14][1] = ((gk[10][1]*c14)+(gk[13][2]*s14));
    gk[14][2] = ((gk[13][2]*c14)-(gk[10][1]*s14));
    gk[15][0] = ((9.8*(s4*c15))+(gk[5][1]*s15));
    gk[15][1] = ((gk[5][1]*c15)-(9.8*(s4*s15)));
    gk[16][1] = ((gk[5][2]*s16)+(gk[15][1]*c16));
    gk[16][2] = ((gk[5][2]*c16)-(gk[15][1]*s16));
    gk[17][0] = ((gk[15][0]*c17)-(gk[16][2]*s17));
    gk[17][2] = ((gk[15][0]*s17)+(gk[16][2]*c17));
    gk[18][0] = ((gk[17][0]*c18)-(gk[17][2]*s18));
    gk[18][2] = ((gk[17][0]*s18)+(gk[17][2]*c18));
    gk[19][0] = ((gk[18][0]*c19)-(gk[18][2]*s19));
    gk[19][2] = ((gk[18][0]*s19)+(gk[18][2]*c19));
    gk[20][1] = ((gk[16][1]*c20)+(gk[19][2]*s20));
    gk[20][2] = ((gk[19][2]*c20)-(gk[16][1]*s20));
/*
Compute cnk & cnb (direction cosines in N)
*/
    cnk[4][0][0] = (c3*c4);
    cnk[4][0][2] = (s4*c3);
    cnk[4][1][0] = (s3*c4);
    cnk[4][1][2] = (s3*s4);
    cnk[5][0][1] = ((cnk[4][0][2]*s5)-(s3*c5));
    cnk[5][0][2] = ((cnk[4][0][2]*c5)+(s3*s5));
    cnk[5][1][1] = ((cnk[4][1][2]*s5)+(c3*c5));
    cnk[5][1][2] = ((cnk[4][1][2]*c5)-(s5*c3));
    cnk[5][2][1] = (s5*c4);
    cnk[5][2][2] = (c4*c5);
    cnk[6][0][0] = ((cnk[4][0][0]*c6)+(cnk[5][0][1]*s6));
    cnk[6][0][1] = ((cnk[5][0][1]*c6)-(cnk[4][0][0]*s6));
    cnk[6][1][0] = ((cnk[4][1][0]*c6)+(cnk[5][1][1]*s6));
    cnk[6][1][1] = ((cnk[5][1][1]*c6)-(cnk[4][1][0]*s6));
    cnk[6][2][0] = ((cnk[5][2][1]*s6)-(s4*c6));
    cnk[6][2][1] = ((cnk[5][2][1]*c6)+(s4*s6));
    cnk[7][0][0] = ((cnk[6][0][0]*c7)-(cnk[5][0][2]*s7));
    cnk[7][0][2] = ((cnk[5][0][2]*c7)+(cnk[6][0][0]*s7));
    cnk[7][1][0] = ((cnk[6][1][0]*c7)-(cnk[5][1][2]*s7));
    cnk[7][1][2] = ((cnk[5][1][2]*c7)+(cnk[6][1][0]*s7));
    cnk[7][2][0] = ((cnk[6][2][0]*c7)-(cnk[5][2][2]*s7));
    cnk[7][2][2] = ((cnk[5][2][2]*c7)+(cnk[6][2][0]*s7));
    cnk[8][0][0] = ((cnk[6][0][0]*c8)-(cnk[5][0][2]*s8));
    cnk[8][0][2] = ((cnk[5][0][2]*c8)+(cnk[6][0][0]*s8));
    cnk[8][1][0] = ((cnk[6][1][0]*c8)-(cnk[5][1][2]*s8));
    cnk[8][1][2] = ((cnk[5][1][2]*c8)+(cnk[6][1][0]*s8));
    cnk[8][2][0] = ((cnk[6][2][0]*c8)-(cnk[5][2][2]*s8));
    cnk[8][2][2] = ((cnk[5][2][2]*c8)+(cnk[6][2][0]*s8));
    cnk[9][0][0] = ((cnk[4][0][0]*c9)+(cnk[5][0][1]*s9));
    cnk[9][0][1] = ((cnk[5][0][1]*c9)-(cnk[4][0][0]*s9));
    cnk[9][1][0] = ((cnk[4][1][0]*c9)+(cnk[5][1][1]*s9));
    cnk[9][1][1] = ((cnk[5][1][1]*c9)-(cnk[4][1][0]*s9));
    cnk[9][2][0] = ((cnk[5][2][1]*s9)-(s4*c9));
    cnk[9][2][1] = ((cnk[5][2][1]*c9)+(s4*s9));
    cnk[10][0][1] = ((cnk[5][0][2]*s10)+(cnk[9][0][1]*c10));
    cnk[10][0][2] = ((cnk[5][0][2]*c10)-(cnk[9][0][1]*s10));
    cnk[10][1][1] = ((cnk[5][1][2]*s10)+(cnk[9][1][1]*c10));
    cnk[10][1][2] = ((cnk[5][1][2]*c10)-(cnk[9][1][1]*s10));
    cnk[10][2][1] = ((cnk[5][2][2]*s10)+(cnk[9][2][1]*c10));
    cnk[10][2][2] = ((cnk[5][2][2]*c10)-(cnk[9][2][1]*s10));
    cnk[11][0][0] = ((cnk[9][0][0]*c11)-(cnk[10][0][2]*s11));
    cnk[11][0][2] = ((cnk[9][0][0]*s11)+(cnk[10][0][2]*c11));
    cnk[11][1][0] = ((cnk[9][1][0]*c11)-(cnk[10][1][2]*s11));
    cnk[11][1][2] = ((cnk[9][1][0]*s11)+(cnk[10][1][2]*c11));
    cnk[11][2][0] = ((cnk[9][2][0]*c11)-(cnk[10][2][2]*s11));
    cnk[11][2][2] = ((cnk[9][2][0]*s11)+(cnk[10][2][2]*c11));
    cnk[12][0][0] = ((cnk[11][0][0]*c12)-(cnk[11][0][2]*s12));
    cnk[12][0][2] = ((cnk[11][0][0]*s12)+(cnk[11][0][2]*c12));
    cnk[12][1][0] = ((cnk[11][1][0]*c12)-(cnk[11][1][2]*s12));
    cnk[12][1][2] = ((cnk[11][1][0]*s12)+(cnk[11][1][2]*c12));
    cnk[12][2][0] = ((cnk[11][2][0]*c12)-(cnk[11][2][2]*s12));
    cnk[12][2][2] = ((cnk[11][2][0]*s12)+(cnk[11][2][2]*c12));
    cnk[13][0][0] = ((cnk[12][0][0]*c13)-(cnk[12][0][2]*s13));
    cnk[13][0][2] = ((cnk[12][0][0]*s13)+(cnk[12][0][2]*c13));
    cnk[13][1][0] = ((cnk[12][1][0]*c13)-(cnk[12][1][2]*s13));
    cnk[13][1][2] = ((cnk[12][1][0]*s13)+(cnk[12][1][2]*c13));
    cnk[13][2][0] = ((cnk[12][2][0]*c13)-(cnk[12][2][2]*s13));
    cnk[13][2][2] = ((cnk[12][2][0]*s13)+(cnk[12][2][2]*c13));
    cnk[14][0][1] = ((cnk[10][0][1]*c14)+(cnk[13][0][2]*s14));
    cnk[14][0][2] = ((cnk[13][0][2]*c14)-(cnk[10][0][1]*s14));
    cnk[14][1][1] = ((cnk[10][1][1]*c14)+(cnk[13][1][2]*s14));
    cnk[14][1][2] = ((cnk[13][1][2]*c14)-(cnk[10][1][1]*s14));
    cnk[14][2][1] = ((cnk[10][2][1]*c14)+(cnk[13][2][2]*s14));
    cnk[14][2][2] = ((cnk[13][2][2]*c14)-(cnk[10][2][1]*s14));
    cnk[15][0][0] = ((cnk[4][0][0]*c15)+(cnk[5][0][1]*s15));
    cnk[15][0][1] = ((cnk[5][0][1]*c15)-(cnk[4][0][0]*s15));
    cnk[15][1][0] = ((cnk[4][1][0]*c15)+(cnk[5][1][1]*s15));
    cnk[15][1][1] = ((cnk[5][1][1]*c15)-(cnk[4][1][0]*s15));
    cnk[15][2][0] = ((cnk[5][2][1]*s15)-(s4*c15));
    cnk[15][2][1] = ((cnk[5][2][1]*c15)+(s4*s15));
    cnk[16][0][1] = ((cnk[5][0][2]*s16)+(cnk[15][0][1]*c16));
    cnk[16][0][2] = ((cnk[5][0][2]*c16)-(cnk[15][0][1]*s16));
    cnk[16][1][1] = ((cnk[5][1][2]*s16)+(cnk[15][1][1]*c16));
    cnk[16][1][2] = ((cnk[5][1][2]*c16)-(cnk[15][1][1]*s16));
    cnk[16][2][1] = ((cnk[5][2][2]*s16)+(cnk[15][2][1]*c16));
    cnk[16][2][2] = ((cnk[5][2][2]*c16)-(cnk[15][2][1]*s16));
    cnk[17][0][0] = ((cnk[15][0][0]*c17)-(cnk[16][0][2]*s17));
    cnk[17][0][2] = ((cnk[15][0][0]*s17)+(cnk[16][0][2]*c17));
    cnk[17][1][0] = ((cnk[15][1][0]*c17)-(cnk[16][1][2]*s17));
    cnk[17][1][2] = ((cnk[15][1][0]*s17)+(cnk[16][1][2]*c17));
    cnk[17][2][0] = ((cnk[15][2][0]*c17)-(cnk[16][2][2]*s17));
    cnk[17][2][2] = ((cnk[15][2][0]*s17)+(cnk[16][2][2]*c17));
    cnk[18][0][0] = ((cnk[17][0][0]*c18)-(cnk[17][0][2]*s18));
    cnk[18][0][2] = ((cnk[17][0][0]*s18)+(cnk[17][0][2]*c18));
    cnk[18][1][0] = ((cnk[17][1][0]*c18)-(cnk[17][1][2]*s18));
    cnk[18][1][2] = ((cnk[17][1][0]*s18)+(cnk[17][1][2]*c18));
    cnk[18][2][0] = ((cnk[17][2][0]*c18)-(cnk[17][2][2]*s18));
    cnk[18][2][2] = ((cnk[17][2][0]*s18)+(cnk[17][2][2]*c18));
    cnk[19][0][0] = ((cnk[18][0][0]*c19)-(cnk[18][0][2]*s19));
    cnk[19][0][2] = ((cnk[18][0][0]*s19)+(cnk[18][0][2]*c19));
    cnk[19][1][0] = ((cnk[18][1][0]*c19)-(cnk[18][1][2]*s19));
    cnk[19][1][2] = ((cnk[18][1][0]*s19)+(cnk[18][1][2]*c19));
    cnk[19][2][0] = ((cnk[18][2][0]*c19)-(cnk[18][2][2]*s19));
    cnk[19][2][2] = ((cnk[18][2][0]*s19)+(cnk[18][2][2]*c19));
    cnk[20][0][1] = ((cnk[16][0][1]*c20)+(cnk[19][0][2]*s20));
    cnk[20][0][2] = ((cnk[19][0][2]*c20)-(cnk[16][0][1]*s20));
    cnk[20][1][1] = ((cnk[16][1][1]*c20)+(cnk[19][1][2]*s20));
    cnk[20][1][2] = ((cnk[19][1][2]*c20)-(cnk[16][1][1]*s20));
    cnk[20][2][1] = ((cnk[16][2][1]*c20)+(cnk[19][2][2]*s20));
    cnk[20][2][2] = ((cnk[19][2][2]*c20)-(cnk[16][2][1]*s20));
    cnb[0][0][0] = cnk[4][0][0];
    cnb[0][0][1] = cnk[5][0][1];
    cnb[0][0][2] = cnk[5][0][2];
    cnb[0][1][0] = cnk[4][1][0];
    cnb[0][1][1] = cnk[5][1][1];
    cnb[0][1][2] = cnk[5][1][2];
    cnb[0][2][0] = -s4;
    cnb[0][2][1] = cnk[5][2][1];
    cnb[0][2][2] = cnk[5][2][2];
    cnb[1][0][0] = cnk[6][0][0];
    cnb[1][0][1] = cnk[6][0][1];
    cnb[1][0][2] = cnk[5][0][2];
    cnb[1][1][0] = cnk[6][1][0];
    cnb[1][1][1] = cnk[6][1][1];
    cnb[1][1][2] = cnk[5][1][2];
    cnb[1][2][0] = cnk[6][2][0];
    cnb[1][2][1] = cnk[6][2][1];
    cnb[1][2][2] = cnk[5][2][2];
    cnb[2][0][0] = cnk[7][0][0];
    cnb[2][0][1] = cnk[6][0][1];
    cnb[2][0][2] = cnk[7][0][2];
    cnb[2][1][0] = cnk[7][1][0];
    cnb[2][1][1] = cnk[6][1][1];
    cnb[2][1][2] = cnk[7][1][2];
    cnb[2][2][0] = cnk[7][2][0];
    cnb[2][2][1] = cnk[6][2][1];
    cnb[2][2][2] = cnk[7][2][2];
    cnb[3][0][0] = cnk[8][0][0];
    cnb[3][0][1] = cnk[6][0][1];
    cnb[3][0][2] = cnk[8][0][2];
    cnb[3][1][0] = cnk[8][1][0];
    cnb[3][1][1] = cnk[6][1][1];
    cnb[3][1][2] = cnk[8][1][2];
    cnb[3][2][0] = cnk[8][2][0];
    cnb[3][2][1] = cnk[6][2][1];
    cnb[3][2][2] = cnk[8][2][2];
    cnb[4][0][0] = cnk[11][0][0];
    cnb[4][0][1] = cnk[10][0][1];
    cnb[4][0][2] = cnk[11][0][2];
    cnb[4][1][0] = cnk[11][1][0];
    cnb[4][1][1] = cnk[10][1][1];
    cnb[4][1][2] = cnk[11][1][2];
    cnb[4][2][0] = cnk[11][2][0];
    cnb[4][2][1] = cnk[10][2][1];
    cnb[4][2][2] = cnk[11][2][2];
    cnb[5][0][0] = cnk[12][0][0];
    cnb[5][0][1] = cnk[10][0][1];
    cnb[5][0][2] = cnk[12][0][2];
    cnb[5][1][0] = cnk[12][1][0];
    cnb[5][1][1] = cnk[10][1][1];
    cnb[5][1][2] = cnk[12][1][2];
    cnb[5][2][0] = cnk[12][2][0];
    cnb[5][2][1] = cnk[10][2][1];
    cnb[5][2][2] = cnk[12][2][2];
    cnb[6][0][0] = cnk[13][0][0];
    cnb[6][0][1] = cnk[14][0][1];
    cnb[6][0][2] = cnk[14][0][2];
    cnb[6][1][0] = cnk[13][1][0];
    cnb[6][1][1] = cnk[14][1][1];
    cnb[6][1][2] = cnk[14][1][2];
    cnb[6][2][0] = cnk[13][2][0];
    cnb[6][2][1] = cnk[14][2][1];
    cnb[6][2][2] = cnk[14][2][2];
    cnb[7][0][0] = cnk[17][0][0];
    cnb[7][0][1] = cnk[16][0][1];
    cnb[7][0][2] = cnk[17][0][2];
    cnb[7][1][0] = cnk[17][1][0];
    cnb[7][1][1] = cnk[16][1][1];
    cnb[7][1][2] = cnk[17][1][2];
    cnb[7][2][0] = cnk[17][2][0];
    cnb[7][2][1] = cnk[16][2][1];
    cnb[7][2][2] = cnk[17][2][2];
    cnb[8][0][0] = cnk[18][0][0];
    cnb[8][0][1] = cnk[16][0][1];
    cnb[8][0][2] = cnk[18][0][2];
    cnb[8][1][0] = cnk[18][1][0];
    cnb[8][1][1] = cnk[16][1][1];
    cnb[8][1][2] = cnk[18][1][2];
    cnb[8][2][0] = cnk[18][2][0];
    cnb[8][2][1] = cnk[16][2][1];
    cnb[8][2][2] = cnk[18][2][2];
    cnb[9][0][0] = cnk[19][0][0];
    cnb[9][0][1] = cnk[20][0][1];
    cnb[9][0][2] = cnk[20][0][2];
    cnb[9][1][0] = cnk[19][1][0];
    cnb[9][1][1] = cnk[20][1][1];
    cnb[9][1][2] = cnk[20][1][2];
    cnb[9][2][0] = cnk[19][2][0];
    cnb[9][2][1] = cnk[20][2][1];
    cnb[9][2][2] = cnk[20][2][2];
/*
Compute q-related auxiliary variables
*/
    rpri[0][2] = (q[0]+ri[0][2]);
    rik[0][2] = (q[0]+ri[0][2]);
    rik[6][0] = (((ri[1][0]*c6)+(ri[1][1]*s6))-rk[1][0]);
    rik[6][1] = (((ri[1][1]*c6)-(ri[1][0]*s6))-rk[1][1]);
    rik[6][2] = (ri[1][2]-rk[1][2]);
    rik[7][0] = (((ri[2][0]*c7)-(ri[2][2]*s7))-rk[2][0]);
    rik[7][1] = (ri[2][1]-rk[2][1]);
    rik[7][2] = (((ri[2][0]*s7)+(ri[2][2]*c7))-rk[2][2]);
    rik[8][0] = (((ri[3][0]*c8)-(ri[3][2]*s8))-rk[3][0]);
    rik[8][1] = (ri[3][1]-rk[3][1]);
    rik[8][2] = (((ri[3][0]*s8)+(ri[3][2]*c8))-rk[3][2]);
    rik[9][0] = ((ri[4][0]*c9)+(ri[4][1]*s9));
    rik[9][1] = ((ri[4][1]*c9)-(ri[4][0]*s9));
    rik[12][0] = (((ri[5][0]*c12)-(ri[5][2]*s12))-rk[5][0]);
    rik[12][1] = (ri[5][1]-rk[5][1]);
    rik[12][2] = (((ri[5][0]*s12)+(ri[5][2]*c12))-rk[5][2]);
    rik[13][0] = ((ri[6][0]*c13)-(ri[6][2]*s13));
    rik[13][2] = ((ri[6][0]*s13)+(ri[6][2]*c13));
    rik[15][0] = ((ri[7][0]*c15)+(ri[7][1]*s15));
    rik[15][1] = ((ri[7][1]*c15)-(ri[7][0]*s15));
    rik[18][0] = (((ri[8][0]*c18)-(ri[8][2]*s18))-rk[8][0]);
    rik[18][1] = (ri[8][1]-rk[8][1]);
    rik[18][2] = (((ri[8][0]*s18)+(ri[8][2]*c18))-rk[8][2]);
    rik[19][0] = ((ri[9][0]*c19)-(ri[9][2]*s19));
    rik[19][2] = ((ri[9][0]*s19)+(ri[9][2]*c19));
/*
Compute rnk & rnb (mass center locations in N)
*/
    rnk[0][2] = (q[0]+ri[0][2]);
    rnk[1][1] = (q[1]+ri[0][1]);
    rnk[2][0] = (q[2]+ri[0][0]);
    rnk[5][0] = (rnk[2][0]-((cnk[5][0][2]*rk[0][2])+((cnk[4][0][0]*rk[0][0])+(
      cnk[5][0][1]*rk[0][1]))));
    rnk[5][1] = (rnk[1][1]-((cnk[5][1][2]*rk[0][2])+((cnk[4][1][0]*rk[0][0])+(
      cnk[5][1][1]*rk[0][1]))));
    rnk[5][2] = (rnk[0][2]+(((rk[0][0]*s4)-(cnk[5][2][1]*rk[0][1]))-(
      cnk[5][2][2]*rk[0][2])));
    rnk[6][0] = ((rnk[5][0]+((cnk[5][0][2]*ri[1][2])+((cnk[4][0][0]*ri[1][0])+(
      cnk[5][0][1]*ri[1][1]))))-((cnk[5][0][2]*rk[1][2])+((cnk[6][0][0]*rk[1][0]
      )+(cnk[6][0][1]*rk[1][1]))));
    rnk[6][1] = ((rnk[5][1]+((cnk[5][1][2]*ri[1][2])+((cnk[4][1][0]*ri[1][0])+(
      cnk[5][1][1]*ri[1][1]))))-((cnk[5][1][2]*rk[1][2])+((cnk[6][1][0]*rk[1][0]
      )+(cnk[6][1][1]*rk[1][1]))));
    rnk[6][2] = ((rnk[5][2]+((cnk[5][2][2]*ri[1][2])+((cnk[5][2][1]*ri[1][1])-(
      ri[1][0]*s4))))-((cnk[5][2][2]*rk[1][2])+((cnk[6][2][0]*rk[1][0])+(
      cnk[6][2][1]*rk[1][1]))));
    rnk[7][0] = ((rnk[6][0]+((cnk[5][0][2]*ri[2][2])+((cnk[6][0][0]*ri[2][0])+(
      cnk[6][0][1]*ri[2][1]))))-((cnk[7][0][2]*rk[2][2])+((cnk[6][0][1]*rk[2][1]
      )+(cnk[7][0][0]*rk[2][0]))));
    rnk[7][1] = ((rnk[6][1]+((cnk[5][1][2]*ri[2][2])+((cnk[6][1][0]*ri[2][0])+(
      cnk[6][1][1]*ri[2][1]))))-((cnk[7][1][2]*rk[2][2])+((cnk[6][1][1]*rk[2][1]
      )+(cnk[7][1][0]*rk[2][0]))));
    rnk[7][2] = ((rnk[6][2]+((cnk[5][2][2]*ri[2][2])+((cnk[6][2][0]*ri[2][0])+(
      cnk[6][2][1]*ri[2][1]))))-((cnk[7][2][2]*rk[2][2])+((cnk[6][2][1]*rk[2][1]
      )+(cnk[7][2][0]*rk[2][0]))));
    rnk[8][0] = ((rnk[6][0]+((cnk[5][0][2]*ri[3][2])+((cnk[6][0][0]*ri[3][0])+(
      cnk[6][0][1]*ri[3][1]))))-((cnk[8][0][2]*rk[3][2])+((cnk[6][0][1]*rk[3][1]
      )+(cnk[8][0][0]*rk[3][0]))));
    rnk[8][1] = ((rnk[6][1]+((cnk[5][1][2]*ri[3][2])+((cnk[6][1][0]*ri[3][0])+(
      cnk[6][1][1]*ri[3][1]))))-((cnk[8][1][2]*rk[3][2])+((cnk[6][1][1]*rk[3][1]
      )+(cnk[8][1][0]*rk[3][0]))));
    rnk[8][2] = ((rnk[6][2]+((cnk[5][2][2]*ri[3][2])+((cnk[6][2][0]*ri[3][0])+(
      cnk[6][2][1]*ri[3][1]))))-((cnk[8][2][2]*rk[3][2])+((cnk[6][2][1]*rk[3][1]
      )+(cnk[8][2][0]*rk[3][0]))));
    rnk[9][0] = (rnk[5][0]+((cnk[5][0][2]*ri[4][2])+((cnk[4][0][0]*ri[4][0])+(
      cnk[5][0][1]*ri[4][1]))));
    rnk[9][1] = (rnk[5][1]+((cnk[5][1][2]*ri[4][2])+((cnk[4][1][0]*ri[4][0])+(
      cnk[5][1][1]*ri[4][1]))));
    rnk[9][2] = (rnk[5][2]+((cnk[5][2][2]*ri[4][2])+((cnk[5][2][1]*ri[4][1])-(
      ri[4][0]*s4))));
    rnk[11][0] = (rnk[9][0]-((cnk[11][0][2]*rk[4][2])+((cnk[10][0][1]*rk[4][1])+
      (cnk[11][0][0]*rk[4][0]))));
    rnk[11][1] = (rnk[9][1]-((cnk[11][1][2]*rk[4][2])+((cnk[10][1][1]*rk[4][1])+
      (cnk[11][1][0]*rk[4][0]))));
    rnk[11][2] = (rnk[9][2]-((cnk[11][2][2]*rk[4][2])+((cnk[10][2][1]*rk[4][1])+
      (cnk[11][2][0]*rk[4][0]))));
    rnk[12][0] = ((rnk[11][0]+((cnk[11][0][2]*ri[5][2])+((cnk[10][0][1]*ri[5][1]
      )+(cnk[11][0][0]*ri[5][0]))))-((cnk[12][0][2]*rk[5][2])+((cnk[10][0][1]*
      rk[5][1])+(cnk[12][0][0]*rk[5][0]))));
    rnk[12][1] = ((rnk[11][1]+((cnk[11][1][2]*ri[5][2])+((cnk[10][1][1]*ri[5][1]
      )+(cnk[11][1][0]*ri[5][0]))))-((cnk[12][1][2]*rk[5][2])+((cnk[10][1][1]*
      rk[5][1])+(cnk[12][1][0]*rk[5][0]))));
    rnk[12][2] = ((rnk[11][2]+((cnk[11][2][2]*ri[5][2])+((cnk[10][2][1]*ri[5][1]
      )+(cnk[11][2][0]*ri[5][0]))))-((cnk[12][2][2]*rk[5][2])+((cnk[10][2][1]*
      rk[5][1])+(cnk[12][2][0]*rk[5][0]))));
    rnk[13][0] = (rnk[12][0]+((cnk[12][0][2]*ri[6][2])+((cnk[10][0][1]*ri[6][1])
      +(cnk[12][0][0]*ri[6][0]))));
    rnk[13][1] = (rnk[12][1]+((cnk[12][1][2]*ri[6][2])+((cnk[10][1][1]*ri[6][1])
      +(cnk[12][1][0]*ri[6][0]))));
    rnk[13][2] = (rnk[12][2]+((cnk[12][2][2]*ri[6][2])+((cnk[10][2][1]*ri[6][1])
      +(cnk[12][2][0]*ri[6][0]))));
    rnk[14][0] = (rnk[13][0]-((cnk[14][0][2]*rk[6][2])+((cnk[13][0][0]*rk[6][0])
      +(cnk[14][0][1]*rk[6][1]))));
    rnk[14][1] = (rnk[13][1]-((cnk[14][1][2]*rk[6][2])+((cnk[13][1][0]*rk[6][0])
      +(cnk[14][1][1]*rk[6][1]))));
    rnk[14][2] = (rnk[13][2]-((cnk[14][2][2]*rk[6][2])+((cnk[13][2][0]*rk[6][0])
      +(cnk[14][2][1]*rk[6][1]))));
    rnk[15][0] = (rnk[5][0]+((cnk[5][0][2]*ri[7][2])+((cnk[4][0][0]*ri[7][0])+(
      cnk[5][0][1]*ri[7][1]))));
    rnk[15][1] = (rnk[5][1]+((cnk[5][1][2]*ri[7][2])+((cnk[4][1][0]*ri[7][0])+(
      cnk[5][1][1]*ri[7][1]))));
    rnk[15][2] = (rnk[5][2]+((cnk[5][2][2]*ri[7][2])+((cnk[5][2][1]*ri[7][1])-(
      ri[7][0]*s4))));
    rnk[17][0] = (rnk[15][0]-((cnk[17][0][2]*rk[7][2])+((cnk[16][0][1]*rk[7][1])
      +(cnk[17][0][0]*rk[7][0]))));
    rnk[17][1] = (rnk[15][1]-((cnk[17][1][2]*rk[7][2])+((cnk[16][1][1]*rk[7][1])
      +(cnk[17][1][0]*rk[7][0]))));
    rnk[17][2] = (rnk[15][2]-((cnk[17][2][2]*rk[7][2])+((cnk[16][2][1]*rk[7][1])
      +(cnk[17][2][0]*rk[7][0]))));
    rnk[18][0] = ((rnk[17][0]+((cnk[17][0][2]*ri[8][2])+((cnk[16][0][1]*ri[8][1]
      )+(cnk[17][0][0]*ri[8][0]))))-((cnk[18][0][2]*rk[8][2])+((cnk[16][0][1]*
      rk[8][1])+(cnk[18][0][0]*rk[8][0]))));
    rnk[18][1] = ((rnk[17][1]+((cnk[17][1][2]*ri[8][2])+((cnk[16][1][1]*ri[8][1]
      )+(cnk[17][1][0]*ri[8][0]))))-((cnk[18][1][2]*rk[8][2])+((cnk[16][1][1]*
      rk[8][1])+(cnk[18][1][0]*rk[8][0]))));
    rnk[18][2] = ((rnk[17][2]+((cnk[17][2][2]*ri[8][2])+((cnk[16][2][1]*ri[8][1]
      )+(cnk[17][2][0]*ri[8][0]))))-((cnk[18][2][2]*rk[8][2])+((cnk[16][2][1]*
      rk[8][1])+(cnk[18][2][0]*rk[8][0]))));
    rnk[19][0] = (rnk[18][0]+((cnk[18][0][2]*ri[9][2])+((cnk[16][0][1]*ri[9][1])
      +(cnk[18][0][0]*ri[9][0]))));
    rnk[19][1] = (rnk[18][1]+((cnk[18][1][2]*ri[9][2])+((cnk[16][1][1]*ri[9][1])
      +(cnk[18][1][0]*ri[9][0]))));
    rnk[19][2] = (rnk[18][2]+((cnk[18][2][2]*ri[9][2])+((cnk[16][2][1]*ri[9][1])
      +(cnk[18][2][0]*ri[9][0]))));
    rnk[20][0] = (rnk[19][0]-((cnk[20][0][2]*rk[9][2])+((cnk[19][0][0]*rk[9][0])
      +(cnk[20][0][1]*rk[9][1]))));
    rnk[20][1] = (rnk[19][1]-((cnk[20][1][2]*rk[9][2])+((cnk[19][1][0]*rk[9][0])
      +(cnk[20][1][1]*rk[9][1]))));
    rnk[20][2] = (rnk[19][2]-((cnk[20][2][2]*rk[9][2])+((cnk[19][2][0]*rk[9][0])
      +(cnk[20][2][1]*rk[9][1]))));
    rnb[0][0] = rnk[5][0];
    rnb[0][1] = rnk[5][1];
    rnb[0][2] = rnk[5][2];
    rnb[1][0] = rnk[6][0];
    rnb[1][1] = rnk[6][1];
    rnb[1][2] = rnk[6][2];
    rnb[2][0] = rnk[7][0];
    rnb[2][1] = rnk[7][1];
    rnb[2][2] = rnk[7][2];
    rnb[3][0] = rnk[8][0];
    rnb[3][1] = rnk[8][1];
    rnb[3][2] = rnk[8][2];
    rnb[4][0] = rnk[11][0];
    rnb[4][1] = rnk[11][1];
    rnb[4][2] = rnk[11][2];
    rnb[5][0] = rnk[12][0];
    rnb[5][1] = rnk[12][1];
    rnb[5][2] = rnk[12][2];
    rnb[6][0] = rnk[14][0];
    rnb[6][1] = rnk[14][1];
    rnb[6][2] = rnk[14][2];
    rnb[7][0] = rnk[17][0];
    rnb[7][1] = rnk[17][1];
    rnb[7][2] = rnk[17][2];
    rnb[8][0] = rnk[18][0];
    rnb[8][1] = rnk[18][1];
    rnb[8][2] = rnk[18][2];
    rnb[9][0] = rnk[20][0];
    rnb[9][1] = rnk[20][1];
    rnb[9][2] = rnk[20][2];
/*
Compute com (system mass center location in N)
*/
    com[0] = ((1./mtot)*((mk[9]*rnk[20][0])+((mk[8]*rnk[18][0])+((mk[7]*
      rnk[17][0])+((mk[6]*rnk[14][0])+((mk[5]*rnk[12][0])+((mk[4]*rnk[11][0])+((
      mk[3]*rnk[8][0])+((mk[2]*rnk[7][0])+((mk[0]*rnk[5][0])+(mk[1]*rnk[6][0])))
      ))))))));
    com[1] = ((1./mtot)*((mk[9]*rnk[20][1])+((mk[8]*rnk[18][1])+((mk[7]*
      rnk[17][1])+((mk[6]*rnk[14][1])+((mk[5]*rnk[12][1])+((mk[4]*rnk[11][1])+((
      mk[3]*rnk[8][1])+((mk[2]*rnk[7][1])+((mk[0]*rnk[5][1])+(mk[1]*rnk[6][1])))
      ))))))));
    com[2] = ((1./mtot)*((mk[9]*rnk[20][2])+((mk[8]*rnk[18][2])+((mk[7]*
      rnk[17][2])+((mk[6]*rnk[14][2])+((mk[5]*rnk[12][2])+((mk[4]*rnk[11][2])+((
      mk[3]*rnk[8][2])+((mk[2]*rnk[7][2])+((mk[0]*rnk[5][2])+(mk[1]*rnk[6][2])))
      ))))))));
    skipqs: ;
/*
Check for locked gimbal tree joint
*/
    if ((fabs((fabs(-s4)-1.)) <= .00380530190825447)  ) {
        sdseterr(8,43);
    }
    if ((fabs((fabs(((cnk[5][2][2]*cnk[10][2][1])+((cnk[5][0][2]*cnk[10][0][1])+
      (cnk[5][1][2]*cnk[10][1][1]))))-1.)) <= .00380530190825447)  ) {
        sdseterr(8,43);
    }
    if ((fabs((fabs(((cnk[5][2][2]*cnk[16][2][1])+((cnk[5][0][2]*cnk[16][0][1])+
      (cnk[5][1][2]*cnk[16][1][1]))))-1.)) <= .00380530190825447)  ) {
        sdseterr(8,43);
    }
    if (uchg == 0) {
        goto skipus;
    }
/*
Velocity-related variables need to be computed
*/
    inerflg = 0;
    for (i = 0; i < 21; i++) {
        u[i] = uin[i];
    }
/*
Compute u-related auxiliary variables
*/
/*
Compute wk & wb (angular velocities)
*/
    wk[4][0] = -(u[3]*s4);
    wk[4][2] = (u[3]*c4);
    wk[5][0] = (u[5]+wk[4][0]);
    wk[5][1] = ((u[4]*c5)+(wk[4][2]*s5));
    wk[5][2] = ((wk[4][2]*c5)-(u[4]*s5));
    wk[6][0] = ((wk[5][0]*c6)+(wk[5][1]*s6));
    wk[6][1] = ((wk[5][1]*c6)-(wk[5][0]*s6));
    wk[6][2] = (u[6]+wk[5][2]);
    wk[7][0] = ((wk[6][0]*c7)-(wk[6][2]*s7));
    wk[7][1] = (u[7]+wk[6][1]);
    wk[7][2] = ((wk[6][0]*s7)+(wk[6][2]*c7));
    wk[8][0] = ((wk[6][0]*c8)-(wk[6][2]*s8));
    wk[8][1] = (u[8]+wk[6][1]);
    wk[8][2] = ((wk[6][0]*s8)+(wk[6][2]*c8));
    wk[9][0] = ((wk[5][0]*c9)+(wk[5][1]*s9));
    wk[9][1] = ((wk[5][1]*c9)-(wk[5][0]*s9));
    wk[9][2] = (u[9]+wk[5][2]);
    wk[10][0] = (u[10]+wk[9][0]);
    wk[10][1] = ((wk[9][1]*c10)+(wk[9][2]*s10));
    wk[10][2] = ((wk[9][2]*c10)-(wk[9][1]*s10));
    wk[11][0] = ((wk[10][0]*c11)-(wk[10][2]*s11));
    wk[11][1] = (u[11]+wk[10][1]);
    wk[11][2] = ((wk[10][0]*s11)+(wk[10][2]*c11));
    wk[12][0] = ((wk[11][0]*c12)-(wk[11][2]*s12));
    wk[12][1] = (u[12]+wk[11][1]);
    wk[12][2] = ((wk[11][0]*s12)+(wk[11][2]*c12));
    wk[13][0] = ((wk[12][0]*c13)-(wk[12][2]*s13));
    wk[13][1] = (u[13]+wk[12][1]);
    wk[13][2] = ((wk[12][0]*s13)+(wk[12][2]*c13));
    wk[14][0] = (u[14]+wk[13][0]);
    wk[14][1] = ((wk[13][1]*c14)+(wk[13][2]*s14));
    wk[14][2] = ((wk[13][2]*c14)-(wk[13][1]*s14));
    wk[15][0] = ((wk[5][0]*c15)+(wk[5][1]*s15));
    wk[15][1] = ((wk[5][1]*c15)-(wk[5][0]*s15));
    wk[15][2] = (u[15]+wk[5][2]);
    wk[16][0] = (u[16]+wk[15][0]);
    wk[16][1] = ((wk[15][1]*c16)+(wk[15][2]*s16));
    wk[16][2] = ((wk[15][2]*c16)-(wk[15][1]*s16));
    wk[17][0] = ((wk[16][0]*c17)-(wk[16][2]*s17));
    wk[17][1] = (u[17]+wk[16][1]);
    wk[17][2] = ((wk[16][0]*s17)+(wk[16][2]*c17));
    wk[18][0] = ((wk[17][0]*c18)-(wk[17][2]*s18));
    wk[18][1] = (u[18]+wk[17][1]);
    wk[18][2] = ((wk[17][0]*s18)+(wk[17][2]*c18));
    wk[19][0] = ((wk[18][0]*c19)-(wk[18][2]*s19));
    wk[19][1] = (u[19]+wk[18][1]);
    wk[19][2] = ((wk[18][0]*s19)+(wk[18][2]*c19));
    wk[20][0] = (u[20]+wk[19][0]);
    wk[20][1] = ((wk[19][1]*c20)+(wk[19][2]*s20));
    wk[20][2] = ((wk[19][2]*c20)-(wk[19][1]*s20));
    wb[0][0] = wk[5][0];
    wb[0][1] = wk[5][1];
    wb[0][2] = wk[5][2];
    wb[1][0] = wk[6][0];
    wb[1][1] = wk[6][1];
    wb[1][2] = wk[6][2];
    wb[2][0] = wk[7][0];
    wb[2][1] = wk[7][1];
    wb[2][2] = wk[7][2];
    wb[3][0] = wk[8][0];
    wb[3][1] = wk[8][1];
    wb[3][2] = wk[8][2];
    wb[4][0] = wk[11][0];
    wb[4][1] = wk[11][1];
    wb[4][2] = wk[11][2];
    wb[5][0] = wk[12][0];
    wb[5][1] = wk[12][1];
    wb[5][2] = wk[12][2];
    wb[6][0] = wk[14][0];
    wb[6][1] = wk[14][1];
    wb[6][2] = wk[14][2];
    wb[7][0] = wk[17][0];
    wb[7][1] = wk[17][1];
    wb[7][2] = wk[17][2];
    wb[8][0] = wk[18][0];
    wb[8][1] = wk[18][1];
    wb[8][2] = wk[18][2];
    wb[9][0] = wk[20][0];
    wb[9][1] = wk[20][1];
    wb[9][2] = wk[20][2];
/*
Compute auxiliary variables involving wk
*/
    Wirk[6][0] = ((ri[1][2]*wk[5][1])-(ri[1][1]*wk[5][2]));
    Wirk[6][1] = ((ri[1][0]*wk[5][2])-(ri[1][2]*wk[5][0]));
    Wirk[6][2] = ((ri[1][1]*wk[5][0])-(ri[1][0]*wk[5][1]));
    Wirk[7][0] = ((ri[2][2]*wk[6][1])-(ri[2][1]*wk[6][2]));
    Wirk[7][1] = ((ri[2][0]*wk[6][2])-(ri[2][2]*wk[6][0]));
    Wirk[7][2] = ((ri[2][1]*wk[6][0])-(ri[2][0]*wk[6][1]));
    Wirk[8][0] = ((ri[3][2]*wk[6][1])-(ri[3][1]*wk[6][2]));
    Wirk[8][1] = ((ri[3][0]*wk[6][2])-(ri[3][2]*wk[6][0]));
    Wirk[8][2] = ((ri[3][1]*wk[6][0])-(ri[3][0]*wk[6][1]));
    Wirk[9][0] = ((ri[4][2]*wk[5][1])-(ri[4][1]*wk[5][2]));
    Wirk[9][1] = ((ri[4][0]*wk[5][2])-(ri[4][2]*wk[5][0]));
    Wirk[9][2] = ((ri[4][1]*wk[5][0])-(ri[4][0]*wk[5][1]));
    Wirk[12][0] = ((ri[5][2]*wk[11][1])-(ri[5][1]*wk[11][2]));
    Wirk[12][1] = ((ri[5][0]*wk[11][2])-(ri[5][2]*wk[11][0]));
    Wirk[12][2] = ((ri[5][1]*wk[11][0])-(ri[5][0]*wk[11][1]));
    Wirk[13][0] = ((ri[6][2]*wk[12][1])-(ri[6][1]*wk[12][2]));
    Wirk[13][1] = ((ri[6][0]*wk[12][2])-(ri[6][2]*wk[12][0]));
    Wirk[13][2] = ((ri[6][1]*wk[12][0])-(ri[6][0]*wk[12][1]));
    Wirk[15][0] = ((ri[7][2]*wk[5][1])-(ri[7][1]*wk[5][2]));
    Wirk[15][1] = ((ri[7][0]*wk[5][2])-(ri[7][2]*wk[5][0]));
    Wirk[15][2] = ((ri[7][1]*wk[5][0])-(ri[7][0]*wk[5][1]));
    Wirk[18][0] = ((ri[8][2]*wk[17][1])-(ri[8][1]*wk[17][2]));
    Wirk[18][1] = ((ri[8][0]*wk[17][2])-(ri[8][2]*wk[17][0]));
    Wirk[18][2] = ((ri[8][1]*wk[17][0])-(ri[8][0]*wk[17][1]));
    Wirk[19][0] = ((ri[9][2]*wk[18][1])-(ri[9][1]*wk[18][2]));
    Wirk[19][1] = ((ri[9][0]*wk[18][2])-(ri[9][2]*wk[18][0]));
    Wirk[19][2] = ((ri[9][1]*wk[18][0])-(ri[9][0]*wk[18][1]));
    Wkrpk[5][0] = ((rk[0][1]*wk[5][2])-(rk[0][2]*wk[5][1]));
    Wkrpk[5][1] = ((rk[0][2]*wk[5][0])-(rk[0][0]*wk[5][2]));
    Wkrpk[5][2] = ((rk[0][0]*wk[5][1])-(rk[0][1]*wk[5][0]));
    Wkrpk[6][0] = ((rk[1][1]*wk[6][2])-(rk[1][2]*wk[6][1]));
    Wkrpk[6][1] = ((rk[1][2]*wk[6][0])-(rk[1][0]*wk[6][2]));
    Wkrpk[6][2] = ((rk[1][0]*wk[6][1])-(rk[1][1]*wk[6][0]));
    Wkrpk[7][0] = ((rk[2][1]*wk[7][2])-(rk[2][2]*wk[7][1]));
    Wkrpk[7][1] = ((rk[2][2]*wk[7][0])-(rk[2][0]*wk[7][2]));
    Wkrpk[7][2] = ((rk[2][0]*wk[7][1])-(rk[2][1]*wk[7][0]));
    Wkrpk[8][0] = ((rk[3][1]*wk[8][2])-(rk[3][2]*wk[8][1]));
    Wkrpk[8][1] = ((rk[3][2]*wk[8][0])-(rk[3][0]*wk[8][2]));
    Wkrpk[8][2] = ((rk[3][0]*wk[8][1])-(rk[3][1]*wk[8][0]));
    Wkrpk[11][0] = ((rk[4][1]*wk[11][2])-(rk[4][2]*wk[11][1]));
    Wkrpk[11][1] = ((rk[4][2]*wk[11][0])-(rk[4][0]*wk[11][2]));
    Wkrpk[11][2] = ((rk[4][0]*wk[11][1])-(rk[4][1]*wk[11][0]));
    Wkrpk[12][0] = ((rk[5][1]*wk[12][2])-(rk[5][2]*wk[12][1]));
    Wkrpk[12][1] = ((rk[5][2]*wk[12][0])-(rk[5][0]*wk[12][2]));
    Wkrpk[12][2] = ((rk[5][0]*wk[12][1])-(rk[5][1]*wk[12][0]));
    Wkrpk[14][0] = ((rk[6][1]*wk[14][2])-(rk[6][2]*wk[14][1]));
    Wkrpk[14][1] = ((rk[6][2]*wk[14][0])-(rk[6][0]*wk[14][2]));
    Wkrpk[14][2] = ((rk[6][0]*wk[14][1])-(rk[6][1]*wk[14][0]));
    Wkrpk[17][0] = ((rk[7][1]*wk[17][2])-(rk[7][2]*wk[17][1]));
    Wkrpk[17][1] = ((rk[7][2]*wk[17][0])-(rk[7][0]*wk[17][2]));
    Wkrpk[17][2] = ((rk[7][0]*wk[17][1])-(rk[7][1]*wk[17][0]));
    Wkrpk[18][0] = ((rk[8][1]*wk[18][2])-(rk[8][2]*wk[18][1]));
    Wkrpk[18][1] = ((rk[8][2]*wk[18][0])-(rk[8][0]*wk[18][2]));
    Wkrpk[18][2] = ((rk[8][0]*wk[18][1])-(rk[8][1]*wk[18][0]));
    Wkrpk[20][0] = ((rk[9][1]*wk[20][2])-(rk[9][2]*wk[20][1]));
    Wkrpk[20][1] = ((rk[9][2]*wk[20][0])-(rk[9][0]*wk[20][2]));
    Wkrpk[20][2] = ((rk[9][0]*wk[20][1])-(rk[9][1]*wk[20][0]));
    IkWk[5][0] = (ik[0][0][0]*wk[5][0]);
    IkWk[5][1] = (ik[0][1][1]*wk[5][1]);
    IkWk[5][2] = (ik[0][2][2]*wk[5][2]);
    WkIkWk[5][0] = ((IkWk[5][2]*wk[5][1])-(IkWk[5][1]*wk[5][2]));
    WkIkWk[5][1] = ((IkWk[5][0]*wk[5][2])-(IkWk[5][2]*wk[5][0]));
    WkIkWk[5][2] = ((IkWk[5][1]*wk[5][0])-(IkWk[5][0]*wk[5][1]));
    IkWk[6][0] = (ik[1][0][0]*wk[6][0]);
    IkWk[6][1] = (ik[1][1][1]*wk[6][1]);
    IkWk[6][2] = (ik[1][2][2]*wk[6][2]);
    WkIkWk[6][0] = ((IkWk[6][2]*wk[6][1])-(IkWk[6][1]*wk[6][2]));
    WkIkWk[6][1] = ((IkWk[6][0]*wk[6][2])-(IkWk[6][2]*wk[6][0]));
    WkIkWk[6][2] = ((IkWk[6][1]*wk[6][0])-(IkWk[6][0]*wk[6][1]));
    IkWk[7][0] = (ik[2][0][0]*wk[7][0]);
    IkWk[7][1] = (ik[2][1][1]*wk[7][1]);
    IkWk[7][2] = (ik[2][2][2]*wk[7][2]);
    WkIkWk[7][0] = ((IkWk[7][2]*wk[7][1])-(IkWk[7][1]*wk[7][2]));
    WkIkWk[7][1] = ((IkWk[7][0]*wk[7][2])-(IkWk[7][2]*wk[7][0]));
    WkIkWk[7][2] = ((IkWk[7][1]*wk[7][0])-(IkWk[7][0]*wk[7][1]));
    IkWk[8][0] = (ik[3][0][0]*wk[8][0]);
    IkWk[8][1] = (ik[3][1][1]*wk[8][1]);
    IkWk[8][2] = (ik[3][2][2]*wk[8][2]);
    WkIkWk[8][0] = ((IkWk[8][2]*wk[8][1])-(IkWk[8][1]*wk[8][2]));
    WkIkWk[8][1] = ((IkWk[8][0]*wk[8][2])-(IkWk[8][2]*wk[8][0]));
    WkIkWk[8][2] = ((IkWk[8][1]*wk[8][0])-(IkWk[8][0]*wk[8][1]));
    IkWk[11][0] = (ik[4][0][0]*wk[11][0]);
    IkWk[11][1] = (ik[4][1][1]*wk[11][1]);
    IkWk[11][2] = (ik[4][2][2]*wk[11][2]);
    WkIkWk[11][0] = ((IkWk[11][2]*wk[11][1])-(IkWk[11][1]*wk[11][2]));
    WkIkWk[11][1] = ((IkWk[11][0]*wk[11][2])-(IkWk[11][2]*wk[11][0]));
    WkIkWk[11][2] = ((IkWk[11][1]*wk[11][0])-(IkWk[11][0]*wk[11][1]));
    IkWk[12][0] = (ik[5][0][0]*wk[12][0]);
    IkWk[12][1] = (ik[5][1][1]*wk[12][1]);
    IkWk[12][2] = (ik[5][2][2]*wk[12][2]);
    WkIkWk[12][0] = ((IkWk[12][2]*wk[12][1])-(IkWk[12][1]*wk[12][2]));
    WkIkWk[12][1] = ((IkWk[12][0]*wk[12][2])-(IkWk[12][2]*wk[12][0]));
    WkIkWk[12][2] = ((IkWk[12][1]*wk[12][0])-(IkWk[12][0]*wk[12][1]));
    IkWk[14][0] = (ik[6][0][0]*wk[14][0]);
    IkWk[14][1] = (ik[6][1][1]*wk[14][1]);
    IkWk[14][2] = (ik[6][2][2]*wk[14][2]);
    WkIkWk[14][0] = ((IkWk[14][2]*wk[14][1])-(IkWk[14][1]*wk[14][2]));
    WkIkWk[14][1] = ((IkWk[14][0]*wk[14][2])-(IkWk[14][2]*wk[14][0]));
    WkIkWk[14][2] = ((IkWk[14][1]*wk[14][0])-(IkWk[14][0]*wk[14][1]));
    IkWk[17][0] = (ik[7][0][0]*wk[17][0]);
    IkWk[17][1] = (ik[7][1][1]*wk[17][1]);
    IkWk[17][2] = (ik[7][2][2]*wk[17][2]);
    WkIkWk[17][0] = ((IkWk[17][2]*wk[17][1])-(IkWk[17][1]*wk[17][2]));
    WkIkWk[17][1] = ((IkWk[17][0]*wk[17][2])-(IkWk[17][2]*wk[17][0]));
    WkIkWk[17][2] = ((IkWk[17][1]*wk[17][0])-(IkWk[17][0]*wk[17][1]));
    IkWk[18][0] = (ik[8][0][0]*wk[18][0]);
    IkWk[18][1] = (ik[8][1][1]*wk[18][1]);
    IkWk[18][2] = (ik[8][2][2]*wk[18][2]);
    WkIkWk[18][0] = ((IkWk[18][2]*wk[18][1])-(IkWk[18][1]*wk[18][2]));
    WkIkWk[18][1] = ((IkWk[18][0]*wk[18][2])-(IkWk[18][2]*wk[18][0]));
    WkIkWk[18][2] = ((IkWk[18][1]*wk[18][0])-(IkWk[18][0]*wk[18][1]));
    IkWk[20][0] = (ik[9][0][0]*wk[20][0]);
    IkWk[20][1] = (ik[9][1][1]*wk[20][1]);
    IkWk[20][2] = (ik[9][2][2]*wk[20][2]);
    WkIkWk[20][0] = ((IkWk[20][2]*wk[20][1])-(IkWk[20][1]*wk[20][2]));
    WkIkWk[20][1] = ((IkWk[20][0]*wk[20][2])-(IkWk[20][2]*wk[20][0]));
    WkIkWk[20][2] = ((IkWk[20][1]*wk[20][0])-(IkWk[20][0]*wk[20][1]));
/*
Compute temporaries for use in SDRHS
*/
    w0w0[0] = (wk[5][0]*wk[5][0]);
    w0w0[1] = (wk[6][0]*wk[6][0]);
    w0w0[2] = (wk[7][0]*wk[7][0]);
    w0w0[3] = (wk[8][0]*wk[8][0]);
    w0w0[4] = (wk[11][0]*wk[11][0]);
    w0w0[5] = (wk[12][0]*wk[12][0]);
    w0w0[6] = (wk[14][0]*wk[14][0]);
    w0w0[7] = (wk[17][0]*wk[17][0]);
    w0w0[8] = (wk[18][0]*wk[18][0]);
    w0w0[9] = (wk[20][0]*wk[20][0]);
    w1w1[0] = (wk[5][1]*wk[5][1]);
    w1w1[1] = (wk[6][1]*wk[6][1]);
    w1w1[2] = (wk[7][1]*wk[7][1]);
    w1w1[3] = (wk[8][1]*wk[8][1]);
    w1w1[4] = (wk[11][1]*wk[11][1]);
    w1w1[5] = (wk[12][1]*wk[12][1]);
    w1w1[6] = (wk[14][1]*wk[14][1]);
    w1w1[7] = (wk[17][1]*wk[17][1]);
    w1w1[8] = (wk[18][1]*wk[18][1]);
    w1w1[9] = (wk[20][1]*wk[20][1]);
    w2w2[0] = (wk[5][2]*wk[5][2]);
    w2w2[1] = (wk[6][2]*wk[6][2]);
    w2w2[2] = (wk[7][2]*wk[7][2]);
    w2w2[3] = (wk[8][2]*wk[8][2]);
    w2w2[4] = (wk[11][2]*wk[11][2]);
    w2w2[5] = (wk[12][2]*wk[12][2]);
    w2w2[6] = (wk[14][2]*wk[14][2]);
    w2w2[7] = (wk[17][2]*wk[17][2]);
    w2w2[8] = (wk[18][2]*wk[18][2]);
    w2w2[9] = (wk[20][2]*wk[20][2]);
    w0w1[0] = (wk[5][0]*wk[5][1]);
    w0w1[1] = (wk[6][0]*wk[6][1]);
    w0w1[2] = (wk[7][0]*wk[7][1]);
    w0w1[3] = (wk[8][0]*wk[8][1]);
    w0w1[4] = (wk[11][0]*wk[11][1]);
    w0w1[5] = (wk[12][0]*wk[12][1]);
    w0w1[6] = (wk[14][0]*wk[14][1]);
    w0w1[7] = (wk[17][0]*wk[17][1]);
    w0w1[8] = (wk[18][0]*wk[18][1]);
    w0w1[9] = (wk[20][0]*wk[20][1]);
    w0w2[0] = (wk[5][0]*wk[5][2]);
    w0w2[1] = (wk[6][0]*wk[6][2]);
    w0w2[2] = (wk[7][0]*wk[7][2]);
    w0w2[3] = (wk[8][0]*wk[8][2]);
    w0w2[4] = (wk[11][0]*wk[11][2]);
    w0w2[5] = (wk[12][0]*wk[12][2]);
    w0w2[6] = (wk[14][0]*wk[14][2]);
    w0w2[7] = (wk[17][0]*wk[17][2]);
    w0w2[8] = (wk[18][0]*wk[18][2]);
    w0w2[9] = (wk[20][0]*wk[20][2]);
    w1w2[0] = (wk[5][1]*wk[5][2]);
    w1w2[1] = (wk[6][1]*wk[6][2]);
    w1w2[2] = (wk[7][1]*wk[7][2]);
    w1w2[3] = (wk[8][1]*wk[8][2]);
    w1w2[4] = (wk[11][1]*wk[11][2]);
    w1w2[5] = (wk[12][1]*wk[12][2]);
    w1w2[6] = (wk[14][1]*wk[14][2]);
    w1w2[7] = (wk[17][1]*wk[17][2]);
    w1w2[8] = (wk[18][1]*wk[18][2]);
    w1w2[9] = (wk[20][1]*wk[20][2]);
    w00w11[0] = -(w0w0[0]+w1w1[0]);
    w00w11[1] = -(w0w0[1]+w1w1[1]);
    w00w11[2] = -(w0w0[2]+w1w1[2]);
    w00w11[3] = -(w0w0[3]+w1w1[3]);
    w00w11[4] = -(w0w0[4]+w1w1[4]);
    w00w11[5] = -(w0w0[5]+w1w1[5]);
    w00w11[6] = -(w0w0[6]+w1w1[6]);
    w00w11[7] = -(w0w0[7]+w1w1[7]);
    w00w11[8] = -(w0w0[8]+w1w1[8]);
    w00w11[9] = -(w0w0[9]+w1w1[9]);
    w00w22[0] = -(w0w0[0]+w2w2[0]);
    w00w22[1] = -(w0w0[1]+w2w2[1]);
    w00w22[2] = -(w0w0[2]+w2w2[2]);
    w00w22[3] = -(w0w0[3]+w2w2[3]);
    w00w22[4] = -(w0w0[4]+w2w2[4]);
    w00w22[5] = -(w0w0[5]+w2w2[5]);
    w00w22[6] = -(w0w0[6]+w2w2[6]);
    w00w22[7] = -(w0w0[7]+w2w2[7]);
    w00w22[8] = -(w0w0[8]+w2w2[8]);
    w00w22[9] = -(w0w0[9]+w2w2[9]);
    w11w22[0] = -(w1w1[0]+w2w2[0]);
    w11w22[1] = -(w1w1[1]+w2w2[1]);
    w11w22[2] = -(w1w1[2]+w2w2[2]);
    w11w22[3] = -(w1w1[3]+w2w2[3]);
    w11w22[4] = -(w1w1[4]+w2w2[4]);
    w11w22[5] = -(w1w1[5]+w2w2[5]);
    w11w22[6] = -(w1w1[6]+w2w2[6]);
    w11w22[7] = -(w1w1[7]+w2w2[7]);
    w11w22[8] = -(w1w1[8]+w2w2[8]);
    w11w22[9] = -(w1w1[9]+w2w2[9]);
/*
Compute vnk & vnb (mass center linear velocities in N)
*/
    vnk[5][0] = (u[2]+((cnk[5][0][2]*Wkrpk[5][2])+((cnk[4][0][0]*Wkrpk[5][0])+(
      cnk[5][0][1]*Wkrpk[5][1]))));
    vnk[5][1] = (u[1]+((cnk[5][1][2]*Wkrpk[5][2])+((cnk[4][1][0]*Wkrpk[5][0])+(
      cnk[5][1][1]*Wkrpk[5][1]))));
    vnk[5][2] = (u[0]+((cnk[5][2][2]*Wkrpk[5][2])+((cnk[5][2][1]*Wkrpk[5][1])-(
      Wkrpk[5][0]*s4))));
    vnk[6][0] = ((vnk[5][0]+((cnk[5][0][2]*Wirk[6][2])+((cnk[4][0][0]*Wirk[6][0]
      )+(cnk[5][0][1]*Wirk[6][1]))))+((cnk[5][0][2]*Wkrpk[6][2])+((cnk[6][0][0]*
      Wkrpk[6][0])+(cnk[6][0][1]*Wkrpk[6][1]))));
    vnk[6][1] = ((vnk[5][1]+((cnk[5][1][2]*Wirk[6][2])+((cnk[4][1][0]*Wirk[6][0]
      )+(cnk[5][1][1]*Wirk[6][1]))))+((cnk[5][1][2]*Wkrpk[6][2])+((cnk[6][1][0]*
      Wkrpk[6][0])+(cnk[6][1][1]*Wkrpk[6][1]))));
    vnk[6][2] = ((vnk[5][2]+((cnk[5][2][2]*Wirk[6][2])+((cnk[5][2][1]*Wirk[6][1]
      )-(Wirk[6][0]*s4))))+((cnk[5][2][2]*Wkrpk[6][2])+((cnk[6][2][0]*
      Wkrpk[6][0])+(cnk[6][2][1]*Wkrpk[6][1]))));
    vnk[7][0] = ((vnk[6][0]+((cnk[5][0][2]*Wirk[7][2])+((cnk[6][0][0]*Wirk[7][0]
      )+(cnk[6][0][1]*Wirk[7][1]))))+((cnk[7][0][2]*Wkrpk[7][2])+((cnk[6][0][1]*
      Wkrpk[7][1])+(cnk[7][0][0]*Wkrpk[7][0]))));
    vnk[7][1] = ((vnk[6][1]+((cnk[5][1][2]*Wirk[7][2])+((cnk[6][1][0]*Wirk[7][0]
      )+(cnk[6][1][1]*Wirk[7][1]))))+((cnk[7][1][2]*Wkrpk[7][2])+((cnk[6][1][1]*
      Wkrpk[7][1])+(cnk[7][1][0]*Wkrpk[7][0]))));
    vnk[7][2] = ((vnk[6][2]+((cnk[5][2][2]*Wirk[7][2])+((cnk[6][2][0]*Wirk[7][0]
      )+(cnk[6][2][1]*Wirk[7][1]))))+((cnk[7][2][2]*Wkrpk[7][2])+((cnk[6][2][1]*
      Wkrpk[7][1])+(cnk[7][2][0]*Wkrpk[7][0]))));
    vnk[8][0] = ((vnk[6][0]+((cnk[5][0][2]*Wirk[8][2])+((cnk[6][0][0]*Wirk[8][0]
      )+(cnk[6][0][1]*Wirk[8][1]))))+((cnk[8][0][2]*Wkrpk[8][2])+((cnk[6][0][1]*
      Wkrpk[8][1])+(cnk[8][0][0]*Wkrpk[8][0]))));
    vnk[8][1] = ((vnk[6][1]+((cnk[5][1][2]*Wirk[8][2])+((cnk[6][1][0]*Wirk[8][0]
      )+(cnk[6][1][1]*Wirk[8][1]))))+((cnk[8][1][2]*Wkrpk[8][2])+((cnk[6][1][1]*
      Wkrpk[8][1])+(cnk[8][1][0]*Wkrpk[8][0]))));
    vnk[8][2] = ((vnk[6][2]+((cnk[5][2][2]*Wirk[8][2])+((cnk[6][2][0]*Wirk[8][0]
      )+(cnk[6][2][1]*Wirk[8][1]))))+((cnk[8][2][2]*Wkrpk[8][2])+((cnk[6][2][1]*
      Wkrpk[8][1])+(cnk[8][2][0]*Wkrpk[8][0]))));
    vnk[9][0] = (vnk[5][0]+((cnk[5][0][2]*Wirk[9][2])+((cnk[4][0][0]*Wirk[9][0])
      +(cnk[5][0][1]*Wirk[9][1]))));
    vnk[9][1] = (vnk[5][1]+((cnk[5][1][2]*Wirk[9][2])+((cnk[4][1][0]*Wirk[9][0])
      +(cnk[5][1][1]*Wirk[9][1]))));
    vnk[9][2] = (vnk[5][2]+((cnk[5][2][2]*Wirk[9][2])+((cnk[5][2][1]*Wirk[9][1])
      -(Wirk[9][0]*s4))));
    vnk[11][0] = (vnk[9][0]+((cnk[11][0][2]*Wkrpk[11][2])+((cnk[10][0][1]*
      Wkrpk[11][1])+(cnk[11][0][0]*Wkrpk[11][0]))));
    vnk[11][1] = (vnk[9][1]+((cnk[11][1][2]*Wkrpk[11][2])+((cnk[10][1][1]*
      Wkrpk[11][1])+(cnk[11][1][0]*Wkrpk[11][0]))));
    vnk[11][2] = (vnk[9][2]+((cnk[11][2][2]*Wkrpk[11][2])+((cnk[10][2][1]*
      Wkrpk[11][1])+(cnk[11][2][0]*Wkrpk[11][0]))));
    vnk[12][0] = ((vnk[11][0]+((cnk[11][0][2]*Wirk[12][2])+((cnk[10][0][1]*
      Wirk[12][1])+(cnk[11][0][0]*Wirk[12][0]))))+((cnk[12][0][2]*Wkrpk[12][2])+
      ((cnk[10][0][1]*Wkrpk[12][1])+(cnk[12][0][0]*Wkrpk[12][0]))));
    vnk[12][1] = ((vnk[11][1]+((cnk[11][1][2]*Wirk[12][2])+((cnk[10][1][1]*
      Wirk[12][1])+(cnk[11][1][0]*Wirk[12][0]))))+((cnk[12][1][2]*Wkrpk[12][2])+
      ((cnk[10][1][1]*Wkrpk[12][1])+(cnk[12][1][0]*Wkrpk[12][0]))));
    vnk[12][2] = ((vnk[11][2]+((cnk[11][2][2]*Wirk[12][2])+((cnk[10][2][1]*
      Wirk[12][1])+(cnk[11][2][0]*Wirk[12][0]))))+((cnk[12][2][2]*Wkrpk[12][2])+
      ((cnk[10][2][1]*Wkrpk[12][1])+(cnk[12][2][0]*Wkrpk[12][0]))));
    vnk[13][0] = (vnk[12][0]+((cnk[12][0][2]*Wirk[13][2])+((cnk[10][0][1]*
      Wirk[13][1])+(cnk[12][0][0]*Wirk[13][0]))));
    vnk[13][1] = (vnk[12][1]+((cnk[12][1][2]*Wirk[13][2])+((cnk[10][1][1]*
      Wirk[13][1])+(cnk[12][1][0]*Wirk[13][0]))));
    vnk[13][2] = (vnk[12][2]+((cnk[12][2][2]*Wirk[13][2])+((cnk[10][2][1]*
      Wirk[13][1])+(cnk[12][2][0]*Wirk[13][0]))));
    vnk[14][0] = (vnk[13][0]+((cnk[14][0][2]*Wkrpk[14][2])+((cnk[13][0][0]*
      Wkrpk[14][0])+(cnk[14][0][1]*Wkrpk[14][1]))));
    vnk[14][1] = (vnk[13][1]+((cnk[14][1][2]*Wkrpk[14][2])+((cnk[13][1][0]*
      Wkrpk[14][0])+(cnk[14][1][1]*Wkrpk[14][1]))));
    vnk[14][2] = (vnk[13][2]+((cnk[14][2][2]*Wkrpk[14][2])+((cnk[13][2][0]*
      Wkrpk[14][0])+(cnk[14][2][1]*Wkrpk[14][1]))));
    vnk[15][0] = (vnk[5][0]+((cnk[5][0][2]*Wirk[15][2])+((cnk[4][0][0]*
      Wirk[15][0])+(cnk[5][0][1]*Wirk[15][1]))));
    vnk[15][1] = (vnk[5][1]+((cnk[5][1][2]*Wirk[15][2])+((cnk[4][1][0]*
      Wirk[15][0])+(cnk[5][1][1]*Wirk[15][1]))));
    vnk[15][2] = (vnk[5][2]+((cnk[5][2][2]*Wirk[15][2])+((cnk[5][2][1]*
      Wirk[15][1])-(Wirk[15][0]*s4))));
    vnk[17][0] = (vnk[15][0]+((cnk[17][0][2]*Wkrpk[17][2])+((cnk[16][0][1]*
      Wkrpk[17][1])+(cnk[17][0][0]*Wkrpk[17][0]))));
    vnk[17][1] = (vnk[15][1]+((cnk[17][1][2]*Wkrpk[17][2])+((cnk[16][1][1]*
      Wkrpk[17][1])+(cnk[17][1][0]*Wkrpk[17][0]))));
    vnk[17][2] = (vnk[15][2]+((cnk[17][2][2]*Wkrpk[17][2])+((cnk[16][2][1]*
      Wkrpk[17][1])+(cnk[17][2][0]*Wkrpk[17][0]))));
    vnk[18][0] = ((vnk[17][0]+((cnk[17][0][2]*Wirk[18][2])+((cnk[16][0][1]*
      Wirk[18][1])+(cnk[17][0][0]*Wirk[18][0]))))+((cnk[18][0][2]*Wkrpk[18][2])+
      ((cnk[16][0][1]*Wkrpk[18][1])+(cnk[18][0][0]*Wkrpk[18][0]))));
    vnk[18][1] = ((vnk[17][1]+((cnk[17][1][2]*Wirk[18][2])+((cnk[16][1][1]*
      Wirk[18][1])+(cnk[17][1][0]*Wirk[18][0]))))+((cnk[18][1][2]*Wkrpk[18][2])+
      ((cnk[16][1][1]*Wkrpk[18][1])+(cnk[18][1][0]*Wkrpk[18][0]))));
    vnk[18][2] = ((vnk[17][2]+((cnk[17][2][2]*Wirk[18][2])+((cnk[16][2][1]*
      Wirk[18][1])+(cnk[17][2][0]*Wirk[18][0]))))+((cnk[18][2][2]*Wkrpk[18][2])+
      ((cnk[16][2][1]*Wkrpk[18][1])+(cnk[18][2][0]*Wkrpk[18][0]))));
    vnk[19][0] = (vnk[18][0]+((cnk[18][0][2]*Wirk[19][2])+((cnk[16][0][1]*
      Wirk[19][1])+(cnk[18][0][0]*Wirk[19][0]))));
    vnk[19][1] = (vnk[18][1]+((cnk[18][1][2]*Wirk[19][2])+((cnk[16][1][1]*
      Wirk[19][1])+(cnk[18][1][0]*Wirk[19][0]))));
    vnk[19][2] = (vnk[18][2]+((cnk[18][2][2]*Wirk[19][2])+((cnk[16][2][1]*
      Wirk[19][1])+(cnk[18][2][0]*Wirk[19][0]))));
    vnk[20][0] = (vnk[19][0]+((cnk[20][0][2]*Wkrpk[20][2])+((cnk[19][0][0]*
      Wkrpk[20][0])+(cnk[20][0][1]*Wkrpk[20][1]))));
    vnk[20][1] = (vnk[19][1]+((cnk[20][1][2]*Wkrpk[20][2])+((cnk[19][1][0]*
      Wkrpk[20][0])+(cnk[20][1][1]*Wkrpk[20][1]))));
    vnk[20][2] = (vnk[19][2]+((cnk[20][2][2]*Wkrpk[20][2])+((cnk[19][2][0]*
      Wkrpk[20][0])+(cnk[20][2][1]*Wkrpk[20][1]))));
    vnb[0][0] = vnk[5][0];
    vnb[0][1] = vnk[5][1];
    vnb[0][2] = vnk[5][2];
    vnb[1][0] = vnk[6][0];
    vnb[1][1] = vnk[6][1];
    vnb[1][2] = vnk[6][2];
    vnb[2][0] = vnk[7][0];
    vnb[2][1] = vnk[7][1];
    vnb[2][2] = vnk[7][2];
    vnb[3][0] = vnk[8][0];
    vnb[3][1] = vnk[8][1];
    vnb[3][2] = vnk[8][2];
    vnb[4][0] = vnk[11][0];
    vnb[4][1] = vnk[11][1];
    vnb[4][2] = vnk[11][2];
    vnb[5][0] = vnk[12][0];
    vnb[5][1] = vnk[12][1];
    vnb[5][2] = vnk[12][2];
    vnb[6][0] = vnk[14][0];
    vnb[6][1] = vnk[14][1];
    vnb[6][2] = vnk[14][2];
    vnb[7][0] = vnk[17][0];
    vnb[7][1] = vnk[17][1];
    vnb[7][2] = vnk[17][2];
    vnb[8][0] = vnk[18][0];
    vnb[8][1] = vnk[18][1];
    vnb[8][2] = vnk[18][2];
    vnb[9][0] = vnk[20][0];
    vnb[9][1] = vnk[20][1];
    vnb[9][2] = vnk[20][2];
/*
Compute qdot (kinematical equations)
*/
    qdot[0] = u[0];
    qdot[1] = u[1];
    qdot[2] = u[2];
    qdot[3] = u[3];
    qdot[4] = u[4];
    qdot[5] = u[5];
    qdot[6] = u[6];
    qdot[7] = u[7];
    qdot[8] = u[8];
    qdot[9] = u[9];
    qdot[10] = u[10];
    qdot[11] = u[11];
    qdot[12] = u[12];
    qdot[13] = u[13];
    qdot[14] = u[14];
    qdot[15] = u[15];
    qdot[16] = u[16];
    qdot[17] = u[17];
    qdot[18] = u[18];
    qdot[19] = u[19];
    qdot[20] = u[20];
    skipus: ;
/*
Initialize applied forces and torques to zero
*/
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 3; j++) {
            ufk[i][j] = 0.;
            utk[i][j] = 0.;
        }
    }
    for (i = 0; i < 21; i++) {
        utau[i] = 0.;
    }
    ltauflg = 0;
    fs0flg = 0;
/*
 Used 0.01 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  754 adds/subtracts/negates
                   1067 multiplies
                      3 divides
                    860 assignments
*/
}

void sdqdot(double oqdot[21])
{
/*
Return position coordinate derivatives for tree joints.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(63,23);
        return;
    }
    for (i = 0; i <= 20; i++) {
        oqdot[i] = qdot[i];
    }
}

void sdu2qdot(double uin[21],
    double oqdot[21])
{
/*
Convert velocities to qdots.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(64,23);
        return;
    }
    for (i = 0; i <= 20; i++) {
        oqdot[i] = uin[i];
    }
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     21 assignments
*/
}

void sdpsstate(double lqin[1])
{

    if (roustate != 2) {
        sdseterr(9,23);
        return;
    }
}

void sddovpk(void)
{

    if (vpkflg == 0) {
/*
Compute Wpk (partial angular velocities)
*/
        Wpk[3][3][2] = 1.;
        Wpk[3][4][0] = -s4;
        Wpk[3][4][2] = c4;
        Wpk[3][5][0] = -s4;
        Wpk[3][5][1] = (s5*c4);
        Wpk[3][5][2] = (c4*c5);
        Wpk[3][6][0] = ((Wpk[3][5][1]*s6)-(s4*c6));
        Wpk[3][6][1] = ((Wpk[3][5][1]*c6)+(s4*s6));
        Wpk[3][6][2] = Wpk[3][5][2];
        Wpk[3][7][0] = ((Wpk[3][6][0]*c7)-(Wpk[3][5][2]*s7));
        Wpk[3][7][1] = Wpk[3][6][1];
        Wpk[3][7][2] = ((Wpk[3][5][2]*c7)+(Wpk[3][6][0]*s7));
        Wpk[3][8][0] = ((Wpk[3][6][0]*c8)-(Wpk[3][5][2]*s8));
        Wpk[3][8][1] = Wpk[3][6][1];
        Wpk[3][8][2] = ((Wpk[3][5][2]*c8)+(Wpk[3][6][0]*s8));
        Wpk[3][9][0] = ((Wpk[3][5][1]*s9)-(s4*c9));
        Wpk[3][9][1] = ((Wpk[3][5][1]*c9)+(s4*s9));
        Wpk[3][9][2] = Wpk[3][5][2];
        Wpk[3][10][0] = Wpk[3][9][0];
        Wpk[3][10][1] = ((Wpk[3][5][2]*s10)+(Wpk[3][9][1]*c10));
        Wpk[3][10][2] = ((Wpk[3][5][2]*c10)-(Wpk[3][9][1]*s10));
        Wpk[3][11][0] = ((Wpk[3][9][0]*c11)-(Wpk[3][10][2]*s11));
        Wpk[3][11][1] = Wpk[3][10][1];
        Wpk[3][11][2] = ((Wpk[3][9][0]*s11)+(Wpk[3][10][2]*c11));
        Wpk[3][12][0] = ((Wpk[3][11][0]*c12)-(Wpk[3][11][2]*s12));
        Wpk[3][12][1] = Wpk[3][10][1];
        Wpk[3][12][2] = ((Wpk[3][11][0]*s12)+(Wpk[3][11][2]*c12));
        Wpk[3][13][0] = ((Wpk[3][12][0]*c13)-(Wpk[3][12][2]*s13));
        Wpk[3][13][1] = Wpk[3][10][1];
        Wpk[3][13][2] = ((Wpk[3][12][0]*s13)+(Wpk[3][12][2]*c13));
        Wpk[3][14][0] = Wpk[3][13][0];
        Wpk[3][14][1] = ((Wpk[3][10][1]*c14)+(Wpk[3][13][2]*s14));
        Wpk[3][14][2] = ((Wpk[3][13][2]*c14)-(Wpk[3][10][1]*s14));
        Wpk[3][15][0] = ((Wpk[3][5][1]*s15)-(s4*c15));
        Wpk[3][15][1] = ((Wpk[3][5][1]*c15)+(s4*s15));
        Wpk[3][15][2] = Wpk[3][5][2];
        Wpk[3][16][0] = Wpk[3][15][0];
        Wpk[3][16][1] = ((Wpk[3][5][2]*s16)+(Wpk[3][15][1]*c16));
        Wpk[3][16][2] = ((Wpk[3][5][2]*c16)-(Wpk[3][15][1]*s16));
        Wpk[3][17][0] = ((Wpk[3][15][0]*c17)-(Wpk[3][16][2]*s17));
        Wpk[3][17][1] = Wpk[3][16][1];
        Wpk[3][17][2] = ((Wpk[3][15][0]*s17)+(Wpk[3][16][2]*c17));
        Wpk[3][18][0] = ((Wpk[3][17][0]*c18)-(Wpk[3][17][2]*s18));
        Wpk[3][18][1] = Wpk[3][16][1];
        Wpk[3][18][2] = ((Wpk[3][17][0]*s18)+(Wpk[3][17][2]*c18));
        Wpk[3][19][0] = ((Wpk[3][18][0]*c19)-(Wpk[3][18][2]*s19));
        Wpk[3][19][1] = Wpk[3][16][1];
        Wpk[3][19][2] = ((Wpk[3][18][0]*s19)+(Wpk[3][18][2]*c19));
        Wpk[3][20][0] = Wpk[3][19][0];
        Wpk[3][20][1] = ((Wpk[3][16][1]*c20)+(Wpk[3][19][2]*s20));
        Wpk[3][20][2] = ((Wpk[3][19][2]*c20)-(Wpk[3][16][1]*s20));
        Wpk[4][4][1] = 1.;
        Wpk[4][5][1] = c5;
        Wpk[4][5][2] = -s5;
        Wpk[4][6][0] = (s6*c5);
        Wpk[4][6][1] = (c5*c6);
        Wpk[4][6][2] = -s5;
        Wpk[4][7][0] = ((Wpk[4][6][0]*c7)+(s5*s7));
        Wpk[4][7][1] = Wpk[4][6][1];
        Wpk[4][7][2] = ((Wpk[4][6][0]*s7)-(s5*c7));
        Wpk[4][8][0] = ((Wpk[4][6][0]*c8)+(s5*s8));
        Wpk[4][8][1] = Wpk[4][6][1];
        Wpk[4][8][2] = ((Wpk[4][6][0]*s8)-(s5*c8));
        Wpk[4][9][0] = (s9*c5);
        Wpk[4][9][1] = (c5*c9);
        Wpk[4][9][2] = -s5;
        Wpk[4][10][0] = Wpk[4][9][0];
        Wpk[4][10][1] = ((Wpk[4][9][1]*c10)-(s5*s10));
        Wpk[4][10][2] = -((Wpk[4][9][1]*s10)+(s5*c10));
        Wpk[4][11][0] = ((Wpk[4][9][0]*c11)-(Wpk[4][10][2]*s11));
        Wpk[4][11][1] = Wpk[4][10][1];
        Wpk[4][11][2] = ((Wpk[4][9][0]*s11)+(Wpk[4][10][2]*c11));
        Wpk[4][12][0] = ((Wpk[4][11][0]*c12)-(Wpk[4][11][2]*s12));
        Wpk[4][12][1] = Wpk[4][10][1];
        Wpk[4][12][2] = ((Wpk[4][11][0]*s12)+(Wpk[4][11][2]*c12));
        Wpk[4][13][0] = ((Wpk[4][12][0]*c13)-(Wpk[4][12][2]*s13));
        Wpk[4][13][1] = Wpk[4][10][1];
        Wpk[4][13][2] = ((Wpk[4][12][0]*s13)+(Wpk[4][12][2]*c13));
        Wpk[4][14][0] = Wpk[4][13][0];
        Wpk[4][14][1] = ((Wpk[4][10][1]*c14)+(Wpk[4][13][2]*s14));
        Wpk[4][14][2] = ((Wpk[4][13][2]*c14)-(Wpk[4][10][1]*s14));
        Wpk[4][15][0] = (s15*c5);
        Wpk[4][15][1] = (c5*c15);
        Wpk[4][15][2] = -s5;
        Wpk[4][16][0] = Wpk[4][15][0];
        Wpk[4][16][1] = ((Wpk[4][15][1]*c16)-(s5*s16));
        Wpk[4][16][2] = -((Wpk[4][15][1]*s16)+(s5*c16));
        Wpk[4][17][0] = ((Wpk[4][15][0]*c17)-(Wpk[4][16][2]*s17));
        Wpk[4][17][1] = Wpk[4][16][1];
        Wpk[4][17][2] = ((Wpk[4][15][0]*s17)+(Wpk[4][16][2]*c17));
        Wpk[4][18][0] = ((Wpk[4][17][0]*c18)-(Wpk[4][17][2]*s18));
        Wpk[4][18][1] = Wpk[4][16][1];
        Wpk[4][18][2] = ((Wpk[4][17][0]*s18)+(Wpk[4][17][2]*c18));
        Wpk[4][19][0] = ((Wpk[4][18][0]*c19)-(Wpk[4][18][2]*s19));
        Wpk[4][19][1] = Wpk[4][16][1];
        Wpk[4][19][2] = ((Wpk[4][18][0]*s19)+(Wpk[4][18][2]*c19));
        Wpk[4][20][0] = Wpk[4][19][0];
        Wpk[4][20][1] = ((Wpk[4][16][1]*c20)+(Wpk[4][19][2]*s20));
        Wpk[4][20][2] = ((Wpk[4][19][2]*c20)-(Wpk[4][16][1]*s20));
        Wpk[5][5][0] = 1.;
        Wpk[5][6][0] = c6;
        Wpk[5][6][1] = -s6;
        Wpk[5][7][0] = (c6*c7);
        Wpk[5][7][1] = -s6;
        Wpk[5][7][2] = (s7*c6);
        Wpk[5][8][0] = (c6*c8);
        Wpk[5][8][1] = -s6;
        Wpk[5][8][2] = (s8*c6);
        Wpk[5][9][0] = c9;
        Wpk[5][9][1] = -s9;
        Wpk[5][10][0] = c9;
        Wpk[5][10][1] = -(s9*c10);
        Wpk[5][10][2] = (s9*s10);
        Wpk[5][11][0] = ((c9*c11)-(Wpk[5][10][2]*s11));
        Wpk[5][11][1] = Wpk[5][10][1];
        Wpk[5][11][2] = ((Wpk[5][10][2]*c11)+(s11*c9));
        Wpk[5][12][0] = ((Wpk[5][11][0]*c12)-(Wpk[5][11][2]*s12));
        Wpk[5][12][1] = Wpk[5][10][1];
        Wpk[5][12][2] = ((Wpk[5][11][0]*s12)+(Wpk[5][11][2]*c12));
        Wpk[5][13][0] = ((Wpk[5][12][0]*c13)-(Wpk[5][12][2]*s13));
        Wpk[5][13][1] = Wpk[5][10][1];
        Wpk[5][13][2] = ((Wpk[5][12][0]*s13)+(Wpk[5][12][2]*c13));
        Wpk[5][14][0] = Wpk[5][13][0];
        Wpk[5][14][1] = ((Wpk[5][10][1]*c14)+(Wpk[5][13][2]*s14));
        Wpk[5][14][2] = ((Wpk[5][13][2]*c14)-(Wpk[5][10][1]*s14));
        Wpk[5][15][0] = c15;
        Wpk[5][15][1] = -s15;
        Wpk[5][16][0] = c15;
        Wpk[5][16][1] = -(s15*c16);
        Wpk[5][16][2] = (s15*s16);
        Wpk[5][17][0] = ((c15*c17)-(Wpk[5][16][2]*s17));
        Wpk[5][17][1] = Wpk[5][16][1];
        Wpk[5][17][2] = ((Wpk[5][16][2]*c17)+(s17*c15));
        Wpk[5][18][0] = ((Wpk[5][17][0]*c18)-(Wpk[5][17][2]*s18));
        Wpk[5][18][1] = Wpk[5][16][1];
        Wpk[5][18][2] = ((Wpk[5][17][0]*s18)+(Wpk[5][17][2]*c18));
        Wpk[5][19][0] = ((Wpk[5][18][0]*c19)-(Wpk[5][18][2]*s19));
        Wpk[5][19][1] = Wpk[5][16][1];
        Wpk[5][19][2] = ((Wpk[5][18][0]*s19)+(Wpk[5][18][2]*c19));
        Wpk[5][20][0] = Wpk[5][19][0];
        Wpk[5][20][1] = ((Wpk[5][16][1]*c20)+(Wpk[5][19][2]*s20));
        Wpk[5][20][2] = ((Wpk[5][19][2]*c20)-(Wpk[5][16][1]*s20));
        Wpk[6][6][2] = 1.;
        Wpk[6][7][0] = -s7;
        Wpk[6][7][2] = c7;
        Wpk[6][8][0] = -s8;
        Wpk[6][8][2] = c8;
        Wpk[7][7][1] = 1.;
        Wpk[8][8][1] = 1.;
        Wpk[9][9][2] = 1.;
        Wpk[9][10][1] = s10;
        Wpk[9][10][2] = c10;
        Wpk[9][11][0] = -(s11*c10);
        Wpk[9][11][1] = s10;
        Wpk[9][11][2] = (c10*c11);
        Wpk[9][12][0] = ((Wpk[9][11][0]*c12)-(Wpk[9][11][2]*s12));
        Wpk[9][12][1] = s10;
        Wpk[9][12][2] = ((Wpk[9][11][0]*s12)+(Wpk[9][11][2]*c12));
        Wpk[9][13][0] = ((Wpk[9][12][0]*c13)-(Wpk[9][12][2]*s13));
        Wpk[9][13][1] = s10;
        Wpk[9][13][2] = ((Wpk[9][12][0]*s13)+(Wpk[9][12][2]*c13));
        Wpk[9][14][0] = Wpk[9][13][0];
        Wpk[9][14][1] = ((Wpk[9][13][2]*s14)+(s10*c14));
        Wpk[9][14][2] = ((Wpk[9][13][2]*c14)-(s10*s14));
        Wpk[10][10][0] = 1.;
        Wpk[10][11][0] = c11;
        Wpk[10][11][2] = s11;
        Wpk[10][12][0] = ((c11*c12)-(s11*s12));
        Wpk[10][12][2] = ((s11*c12)+(s12*c11));
        Wpk[10][13][0] = ((Wpk[10][12][0]*c13)-(Wpk[10][12][2]*s13));
        Wpk[10][13][2] = ((Wpk[10][12][0]*s13)+(Wpk[10][12][2]*c13));
        Wpk[10][14][0] = Wpk[10][13][0];
        Wpk[10][14][1] = (Wpk[10][13][2]*s14);
        Wpk[10][14][2] = (Wpk[10][13][2]*c14);
        Wpk[11][11][1] = 1.;
        Wpk[11][12][1] = 1.;
        Wpk[11][13][1] = 1.;
        Wpk[11][14][1] = c14;
        Wpk[11][14][2] = -s14;
        Wpk[12][12][1] = 1.;
        Wpk[12][13][1] = 1.;
        Wpk[12][14][1] = c14;
        Wpk[12][14][2] = -s14;
        Wpk[13][13][1] = 1.;
        Wpk[13][14][1] = c14;
        Wpk[13][14][2] = -s14;
        Wpk[14][14][0] = 1.;
        Wpk[15][15][2] = 1.;
        Wpk[15][16][1] = s16;
        Wpk[15][16][2] = c16;
        Wpk[15][17][0] = -(s17*c16);
        Wpk[15][17][1] = s16;
        Wpk[15][17][2] = (c16*c17);
        Wpk[15][18][0] = ((Wpk[15][17][0]*c18)-(Wpk[15][17][2]*s18));
        Wpk[15][18][1] = s16;
        Wpk[15][18][2] = ((Wpk[15][17][0]*s18)+(Wpk[15][17][2]*c18));
        Wpk[15][19][0] = ((Wpk[15][18][0]*c19)-(Wpk[15][18][2]*s19));
        Wpk[15][19][1] = s16;
        Wpk[15][19][2] = ((Wpk[15][18][0]*s19)+(Wpk[15][18][2]*c19));
        Wpk[15][20][0] = Wpk[15][19][0];
        Wpk[15][20][1] = ((Wpk[15][19][2]*s20)+(s16*c20));
        Wpk[15][20][2] = ((Wpk[15][19][2]*c20)-(s16*s20));
        Wpk[16][16][0] = 1.;
        Wpk[16][17][0] = c17;
        Wpk[16][17][2] = s17;
        Wpk[16][18][0] = ((c17*c18)-(s17*s18));
        Wpk[16][18][2] = ((s17*c18)+(s18*c17));
        Wpk[16][19][0] = ((Wpk[16][18][0]*c19)-(Wpk[16][18][2]*s19));
        Wpk[16][19][2] = ((Wpk[16][18][0]*s19)+(Wpk[16][18][2]*c19));
        Wpk[16][20][0] = Wpk[16][19][0];
        Wpk[16][20][1] = (Wpk[16][19][2]*s20);
        Wpk[16][20][2] = (Wpk[16][19][2]*c20);
        Wpk[17][17][1] = 1.;
        Wpk[17][18][1] = 1.;
        Wpk[17][19][1] = 1.;
        Wpk[17][20][1] = c20;
        Wpk[17][20][2] = -s20;
        Wpk[18][18][1] = 1.;
        Wpk[18][19][1] = 1.;
        Wpk[18][20][1] = c20;
        Wpk[18][20][2] = -s20;
        Wpk[19][19][1] = 1.;
        Wpk[19][20][1] = c20;
        Wpk[19][20][2] = -s20;
        Wpk[20][20][0] = 1.;
/*
Compute Vpk (partial velocities)
*/
        Vpk[0][0][2] = 1.;
        Vpk[0][1][2] = 1.;
        Vpk[0][2][2] = 1.;
        Vpk[0][3][2] = 1.;
        Vpk[0][4][0] = -s4;
        Vpk[0][4][2] = c4;
        Vpk[0][5][0] = -s4;
        Vpk[0][5][1] = (s5*c4);
        Vpk[0][5][2] = (c4*c5);
        Vpk[0][6][0] = ((Vpk[0][5][1]*s6)-(s4*c6));
        Vpk[0][6][1] = ((Vpk[0][5][1]*c6)+(s4*s6));
        Vpk[0][6][2] = Vpk[0][5][2];
        Vpk[0][7][0] = ((Vpk[0][6][0]*c7)-(Vpk[0][5][2]*s7));
        Vpk[0][7][1] = Vpk[0][6][1];
        Vpk[0][7][2] = ((Vpk[0][5][2]*c7)+(Vpk[0][6][0]*s7));
        Vpk[0][8][0] = ((Vpk[0][6][0]*c8)-(Vpk[0][5][2]*s8));
        Vpk[0][8][1] = Vpk[0][6][1];
        Vpk[0][8][2] = ((Vpk[0][5][2]*c8)+(Vpk[0][6][0]*s8));
        Vpk[0][9][0] = ((Vpk[0][5][1]*s9)-(s4*c9));
        Vpk[0][9][1] = ((Vpk[0][5][1]*c9)+(s4*s9));
        Vpk[0][9][2] = Vpk[0][5][2];
        Vpk[0][10][0] = Vpk[0][9][0];
        Vpk[0][10][1] = ((Vpk[0][5][2]*s10)+(Vpk[0][9][1]*c10));
        Vpk[0][10][2] = ((Vpk[0][5][2]*c10)-(Vpk[0][9][1]*s10));
        Vpk[0][11][0] = ((Vpk[0][9][0]*c11)-(Vpk[0][10][2]*s11));
        Vpk[0][11][1] = Vpk[0][10][1];
        Vpk[0][11][2] = ((Vpk[0][9][0]*s11)+(Vpk[0][10][2]*c11));
        Vpk[0][12][0] = ((Vpk[0][11][0]*c12)-(Vpk[0][11][2]*s12));
        Vpk[0][12][1] = Vpk[0][10][1];
        Vpk[0][12][2] = ((Vpk[0][11][0]*s12)+(Vpk[0][11][2]*c12));
        Vpk[0][13][0] = ((Vpk[0][12][0]*c13)-(Vpk[0][12][2]*s13));
        Vpk[0][13][1] = Vpk[0][10][1];
        Vpk[0][13][2] = ((Vpk[0][12][0]*s13)+(Vpk[0][12][2]*c13));
        Vpk[0][14][0] = Vpk[0][13][0];
        Vpk[0][14][1] = ((Vpk[0][10][1]*c14)+(Vpk[0][13][2]*s14));
        Vpk[0][14][2] = ((Vpk[0][13][2]*c14)-(Vpk[0][10][1]*s14));
        Vpk[0][15][0] = ((Vpk[0][5][1]*s15)-(s4*c15));
        Vpk[0][15][1] = ((Vpk[0][5][1]*c15)+(s4*s15));
        Vpk[0][15][2] = Vpk[0][5][2];
        Vpk[0][16][0] = Vpk[0][15][0];
        Vpk[0][16][1] = ((Vpk[0][5][2]*s16)+(Vpk[0][15][1]*c16));
        Vpk[0][16][2] = ((Vpk[0][5][2]*c16)-(Vpk[0][15][1]*s16));
        Vpk[0][17][0] = ((Vpk[0][15][0]*c17)-(Vpk[0][16][2]*s17));
        Vpk[0][17][1] = Vpk[0][16][1];
        Vpk[0][17][2] = ((Vpk[0][15][0]*s17)+(Vpk[0][16][2]*c17));
        Vpk[0][18][0] = ((Vpk[0][17][0]*c18)-(Vpk[0][17][2]*s18));
        Vpk[0][18][1] = Vpk[0][16][1];
        Vpk[0][18][2] = ((Vpk[0][17][0]*s18)+(Vpk[0][17][2]*c18));
        Vpk[0][19][0] = ((Vpk[0][18][0]*c19)-(Vpk[0][18][2]*s19));
        Vpk[0][19][1] = Vpk[0][16][1];
        Vpk[0][19][2] = ((Vpk[0][18][0]*s19)+(Vpk[0][18][2]*c19));
        Vpk[0][20][0] = Vpk[0][19][0];
        Vpk[0][20][1] = ((Vpk[0][16][1]*c20)+(Vpk[0][19][2]*s20));
        Vpk[0][20][2] = ((Vpk[0][19][2]*c20)-(Vpk[0][16][1]*s20));
        Vpk[1][1][1] = 1.;
        Vpk[1][2][1] = 1.;
        Vpk[1][3][0] = s3;
        Vpk[1][3][1] = c3;
        Vpk[1][4][0] = (s3*c4);
        Vpk[1][4][1] = c3;
        Vpk[1][4][2] = (s3*s4);
        Vpk[1][5][0] = Vpk[1][4][0];
        Vpk[1][5][1] = ((Vpk[1][4][2]*s5)+(c3*c5));
        Vpk[1][5][2] = ((Vpk[1][4][2]*c5)-(s5*c3));
        Vpk[1][6][0] = ((Vpk[1][4][0]*c6)+(Vpk[1][5][1]*s6));
        Vpk[1][6][1] = ((Vpk[1][5][1]*c6)-(Vpk[1][4][0]*s6));
        Vpk[1][6][2] = Vpk[1][5][2];
        Vpk[1][7][0] = ((Vpk[1][6][0]*c7)-(Vpk[1][5][2]*s7));
        Vpk[1][7][1] = Vpk[1][6][1];
        Vpk[1][7][2] = ((Vpk[1][5][2]*c7)+(Vpk[1][6][0]*s7));
        Vpk[1][8][0] = ((Vpk[1][6][0]*c8)-(Vpk[1][5][2]*s8));
        Vpk[1][8][1] = Vpk[1][6][1];
        Vpk[1][8][2] = ((Vpk[1][5][2]*c8)+(Vpk[1][6][0]*s8));
        Vpk[1][9][0] = ((Vpk[1][4][0]*c9)+(Vpk[1][5][1]*s9));
        Vpk[1][9][1] = ((Vpk[1][5][1]*c9)-(Vpk[1][4][0]*s9));
        Vpk[1][9][2] = Vpk[1][5][2];
        Vpk[1][10][0] = Vpk[1][9][0];
        Vpk[1][10][1] = ((Vpk[1][5][2]*s10)+(Vpk[1][9][1]*c10));
        Vpk[1][10][2] = ((Vpk[1][5][2]*c10)-(Vpk[1][9][1]*s10));
        Vpk[1][11][0] = ((Vpk[1][9][0]*c11)-(Vpk[1][10][2]*s11));
        Vpk[1][11][1] = Vpk[1][10][1];
        Vpk[1][11][2] = ((Vpk[1][9][0]*s11)+(Vpk[1][10][2]*c11));
        Vpk[1][12][0] = ((Vpk[1][11][0]*c12)-(Vpk[1][11][2]*s12));
        Vpk[1][12][1] = Vpk[1][10][1];
        Vpk[1][12][2] = ((Vpk[1][11][0]*s12)+(Vpk[1][11][2]*c12));
        Vpk[1][13][0] = ((Vpk[1][12][0]*c13)-(Vpk[1][12][2]*s13));
        Vpk[1][13][1] = Vpk[1][10][1];
        Vpk[1][13][2] = ((Vpk[1][12][0]*s13)+(Vpk[1][12][2]*c13));
        Vpk[1][14][0] = Vpk[1][13][0];
        Vpk[1][14][1] = ((Vpk[1][10][1]*c14)+(Vpk[1][13][2]*s14));
        Vpk[1][14][2] = ((Vpk[1][13][2]*c14)-(Vpk[1][10][1]*s14));
        Vpk[1][15][0] = ((Vpk[1][4][0]*c15)+(Vpk[1][5][1]*s15));
        Vpk[1][15][1] = ((Vpk[1][5][1]*c15)-(Vpk[1][4][0]*s15));
        Vpk[1][15][2] = Vpk[1][5][2];
        Vpk[1][16][0] = Vpk[1][15][0];
        Vpk[1][16][1] = ((Vpk[1][5][2]*s16)+(Vpk[1][15][1]*c16));
        Vpk[1][16][2] = ((Vpk[1][5][2]*c16)-(Vpk[1][15][1]*s16));
        Vpk[1][17][0] = ((Vpk[1][15][0]*c17)-(Vpk[1][16][2]*s17));
        Vpk[1][17][1] = Vpk[1][16][1];
        Vpk[1][17][2] = ((Vpk[1][15][0]*s17)+(Vpk[1][16][2]*c17));
        Vpk[1][18][0] = ((Vpk[1][17][0]*c18)-(Vpk[1][17][2]*s18));
        Vpk[1][18][1] = Vpk[1][16][1];
        Vpk[1][18][2] = ((Vpk[1][17][0]*s18)+(Vpk[1][17][2]*c18));
        Vpk[1][19][0] = ((Vpk[1][18][0]*c19)-(Vpk[1][18][2]*s19));
        Vpk[1][19][1] = Vpk[1][16][1];
        Vpk[1][19][2] = ((Vpk[1][18][0]*s19)+(Vpk[1][18][2]*c19));
        Vpk[1][20][0] = Vpk[1][19][0];
        Vpk[1][20][1] = ((Vpk[1][16][1]*c20)+(Vpk[1][19][2]*s20));
        Vpk[1][20][2] = ((Vpk[1][19][2]*c20)-(Vpk[1][16][1]*s20));
        Vpk[2][2][0] = 1.;
        Vpk[2][3][0] = c3;
        Vpk[2][3][1] = -s3;
        Vpk[2][4][0] = (c3*c4);
        Vpk[2][4][1] = -s3;
        Vpk[2][4][2] = (s4*c3);
        Vpk[2][5][0] = Vpk[2][4][0];
        Vpk[2][5][1] = ((Vpk[2][4][2]*s5)-(s3*c5));
        Vpk[2][5][2] = ((Vpk[2][4][2]*c5)+(s3*s5));
        Vpk[2][6][0] = ((Vpk[2][4][0]*c6)+(Vpk[2][5][1]*s6));
        Vpk[2][6][1] = ((Vpk[2][5][1]*c6)-(Vpk[2][4][0]*s6));
        Vpk[2][6][2] = Vpk[2][5][2];
        Vpk[2][7][0] = ((Vpk[2][6][0]*c7)-(Vpk[2][5][2]*s7));
        Vpk[2][7][1] = Vpk[2][6][1];
        Vpk[2][7][2] = ((Vpk[2][5][2]*c7)+(Vpk[2][6][0]*s7));
        Vpk[2][8][0] = ((Vpk[2][6][0]*c8)-(Vpk[2][5][2]*s8));
        Vpk[2][8][1] = Vpk[2][6][1];
        Vpk[2][8][2] = ((Vpk[2][5][2]*c8)+(Vpk[2][6][0]*s8));
        Vpk[2][9][0] = ((Vpk[2][4][0]*c9)+(Vpk[2][5][1]*s9));
        Vpk[2][9][1] = ((Vpk[2][5][1]*c9)-(Vpk[2][4][0]*s9));
        Vpk[2][9][2] = Vpk[2][5][2];
        Vpk[2][10][0] = Vpk[2][9][0];
        Vpk[2][10][1] = ((Vpk[2][5][2]*s10)+(Vpk[2][9][1]*c10));
        Vpk[2][10][2] = ((Vpk[2][5][2]*c10)-(Vpk[2][9][1]*s10));
        Vpk[2][11][0] = ((Vpk[2][9][0]*c11)-(Vpk[2][10][2]*s11));
        Vpk[2][11][1] = Vpk[2][10][1];
        Vpk[2][11][2] = ((Vpk[2][9][0]*s11)+(Vpk[2][10][2]*c11));
        Vpk[2][12][0] = ((Vpk[2][11][0]*c12)-(Vpk[2][11][2]*s12));
        Vpk[2][12][1] = Vpk[2][10][1];
        Vpk[2][12][2] = ((Vpk[2][11][0]*s12)+(Vpk[2][11][2]*c12));
        Vpk[2][13][0] = ((Vpk[2][12][0]*c13)-(Vpk[2][12][2]*s13));
        Vpk[2][13][1] = Vpk[2][10][1];
        Vpk[2][13][2] = ((Vpk[2][12][0]*s13)+(Vpk[2][12][2]*c13));
        Vpk[2][14][0] = Vpk[2][13][0];
        Vpk[2][14][1] = ((Vpk[2][10][1]*c14)+(Vpk[2][13][2]*s14));
        Vpk[2][14][2] = ((Vpk[2][13][2]*c14)-(Vpk[2][10][1]*s14));
        Vpk[2][15][0] = ((Vpk[2][4][0]*c15)+(Vpk[2][5][1]*s15));
        Vpk[2][15][1] = ((Vpk[2][5][1]*c15)-(Vpk[2][4][0]*s15));
        Vpk[2][15][2] = Vpk[2][5][2];
        Vpk[2][16][0] = Vpk[2][15][0];
        Vpk[2][16][1] = ((Vpk[2][5][2]*s16)+(Vpk[2][15][1]*c16));
        Vpk[2][16][2] = ((Vpk[2][5][2]*c16)-(Vpk[2][15][1]*s16));
        Vpk[2][17][0] = ((Vpk[2][15][0]*c17)-(Vpk[2][16][2]*s17));
        Vpk[2][17][1] = Vpk[2][16][1];
        Vpk[2][17][2] = ((Vpk[2][15][0]*s17)+(Vpk[2][16][2]*c17));
        Vpk[2][18][0] = ((Vpk[2][17][0]*c18)-(Vpk[2][17][2]*s18));
        Vpk[2][18][1] = Vpk[2][16][1];
        Vpk[2][18][2] = ((Vpk[2][17][0]*s18)+(Vpk[2][17][2]*c18));
        Vpk[2][19][0] = ((Vpk[2][18][0]*c19)-(Vpk[2][18][2]*s19));
        Vpk[2][19][1] = Vpk[2][16][1];
        Vpk[2][19][2] = ((Vpk[2][18][0]*s19)+(Vpk[2][18][2]*c19));
        Vpk[2][20][0] = Vpk[2][19][0];
        Vpk[2][20][1] = ((Vpk[2][16][1]*c20)+(Vpk[2][19][2]*s20));
        Vpk[2][20][2] = ((Vpk[2][19][2]*c20)-(Vpk[2][16][1]*s20));
        Vpk[3][5][0] = ((rk[0][1]*Wpk[3][5][2])-(rk[0][2]*Wpk[3][5][1]));
        Vpk[3][5][1] = -((rk[0][0]*Wpk[3][5][2])+(rk[0][2]*s4));
        Vpk[3][5][2] = ((rk[0][0]*Wpk[3][5][1])+(rk[0][1]*s4));
        VWri[3][6][0] = (Vpk[3][5][0]+((ri[1][2]*Wpk[3][5][1])-(ri[1][1]*
          Wpk[3][5][2])));
        VWri[3][6][1] = (Vpk[3][5][1]+((ri[1][0]*Wpk[3][5][2])+(ri[1][2]*s4)));
        VWri[3][6][2] = (Vpk[3][5][2]-((ri[1][0]*Wpk[3][5][1])+(ri[1][1]*s4)));
        Vpk[3][6][0] = (((rk[1][1]*Wpk[3][5][2])-(rk[1][2]*Wpk[3][6][1]))+((
          VWri[3][6][0]*c6)+(VWri[3][6][1]*s6)));
        Vpk[3][6][1] = (((rk[1][2]*Wpk[3][6][0])-(rk[1][0]*Wpk[3][5][2]))+((
          VWri[3][6][1]*c6)-(VWri[3][6][0]*s6)));
        Vpk[3][6][2] = (VWri[3][6][2]+((rk[1][0]*Wpk[3][6][1])-(rk[1][1]*
          Wpk[3][6][0])));
        VWri[3][7][0] = (Vpk[3][6][0]+((ri[2][2]*Wpk[3][6][1])-(ri[2][1]*
          Wpk[3][5][2])));
        VWri[3][7][1] = (Vpk[3][6][1]+((ri[2][0]*Wpk[3][5][2])-(ri[2][2]*
          Wpk[3][6][0])));
        VWri[3][7][2] = (Vpk[3][6][2]+((ri[2][1]*Wpk[3][6][0])-(ri[2][0]*
          Wpk[3][6][1])));
        Vpk[3][7][0] = (((rk[2][1]*Wpk[3][7][2])-(rk[2][2]*Wpk[3][6][1]))+((
          VWri[3][7][0]*c7)-(VWri[3][7][2]*s7)));
        Vpk[3][7][1] = (VWri[3][7][1]+((rk[2][2]*Wpk[3][7][0])-(rk[2][0]*
          Wpk[3][7][2])));
        Vpk[3][7][2] = (((rk[2][0]*Wpk[3][6][1])-(rk[2][1]*Wpk[3][7][0]))+((
          VWri[3][7][0]*s7)+(VWri[3][7][2]*c7)));
        VWri[3][8][0] = (Vpk[3][6][0]+((ri[3][2]*Wpk[3][6][1])-(ri[3][1]*
          Wpk[3][5][2])));
        VWri[3][8][1] = (Vpk[3][6][1]+((ri[3][0]*Wpk[3][5][2])-(ri[3][2]*
          Wpk[3][6][0])));
        VWri[3][8][2] = (Vpk[3][6][2]+((ri[3][1]*Wpk[3][6][0])-(ri[3][0]*
          Wpk[3][6][1])));
        Vpk[3][8][0] = (((rk[3][1]*Wpk[3][8][2])-(rk[3][2]*Wpk[3][6][1]))+((
          VWri[3][8][0]*c8)-(VWri[3][8][2]*s8)));
        Vpk[3][8][1] = (VWri[3][8][1]+((rk[3][2]*Wpk[3][8][0])-(rk[3][0]*
          Wpk[3][8][2])));
        Vpk[3][8][2] = (((rk[3][0]*Wpk[3][6][1])-(rk[3][1]*Wpk[3][8][0]))+((
          VWri[3][8][0]*s8)+(VWri[3][8][2]*c8)));
        VWri[3][9][0] = (Vpk[3][5][0]+((ri[4][2]*Wpk[3][5][1])-(ri[4][1]*
          Wpk[3][5][2])));
        VWri[3][9][1] = (Vpk[3][5][1]+((ri[4][0]*Wpk[3][5][2])+(ri[4][2]*s4)));
        VWri[3][9][2] = (Vpk[3][5][2]-((ri[4][0]*Wpk[3][5][1])+(ri[4][1]*s4)));
        Vpk[3][9][0] = ((VWri[3][9][0]*c9)+(VWri[3][9][1]*s9));
        Vpk[3][9][1] = ((VWri[3][9][1]*c9)-(VWri[3][9][0]*s9));
        Vpk[3][9][2] = VWri[3][9][2];
        Vpk[3][10][0] = Vpk[3][9][0];
        Vpk[3][10][1] = ((Vpk[3][9][1]*c10)+(VWri[3][9][2]*s10));
        Vpk[3][10][2] = ((VWri[3][9][2]*c10)-(Vpk[3][9][1]*s10));
        Vpk[3][11][0] = (((rk[4][1]*Wpk[3][11][2])-(rk[4][2]*Wpk[3][10][1]))+((
          Vpk[3][9][0]*c11)-(Vpk[3][10][2]*s11)));
        Vpk[3][11][1] = (Vpk[3][10][1]+((rk[4][2]*Wpk[3][11][0])-(rk[4][0]*
          Wpk[3][11][2])));
        Vpk[3][11][2] = (((rk[4][0]*Wpk[3][10][1])-(rk[4][1]*Wpk[3][11][0]))+((
          Vpk[3][9][0]*s11)+(Vpk[3][10][2]*c11)));
        VWri[3][12][0] = (Vpk[3][11][0]+((ri[5][2]*Wpk[3][10][1])-(ri[5][1]*
          Wpk[3][11][2])));
        VWri[3][12][1] = (Vpk[3][11][1]+((ri[5][0]*Wpk[3][11][2])-(ri[5][2]*
          Wpk[3][11][0])));
        VWri[3][12][2] = (Vpk[3][11][2]+((ri[5][1]*Wpk[3][11][0])-(ri[5][0]*
          Wpk[3][10][1])));
        Vpk[3][12][0] = (((rk[5][1]*Wpk[3][12][2])-(rk[5][2]*Wpk[3][10][1]))+((
          VWri[3][12][0]*c12)-(VWri[3][12][2]*s12)));
        Vpk[3][12][1] = (VWri[3][12][1]+((rk[5][2]*Wpk[3][12][0])-(rk[5][0]*
          Wpk[3][12][2])));
        Vpk[3][12][2] = (((rk[5][0]*Wpk[3][10][1])-(rk[5][1]*Wpk[3][12][0]))+((
          VWri[3][12][0]*s12)+(VWri[3][12][2]*c12)));
        VWri[3][13][0] = (Vpk[3][12][0]+((ri[6][2]*Wpk[3][10][1])-(ri[6][1]*
          Wpk[3][12][2])));
        VWri[3][13][1] = (Vpk[3][12][1]+((ri[6][0]*Wpk[3][12][2])-(ri[6][2]*
          Wpk[3][12][0])));
        VWri[3][13][2] = (Vpk[3][12][2]+((ri[6][1]*Wpk[3][12][0])-(ri[6][0]*
          Wpk[3][10][1])));
        Vpk[3][13][0] = ((VWri[3][13][0]*c13)-(VWri[3][13][2]*s13));
        Vpk[3][13][1] = VWri[3][13][1];
        Vpk[3][13][2] = ((VWri[3][13][0]*s13)+(VWri[3][13][2]*c13));
        Vpk[3][14][0] = (Vpk[3][13][0]+((rk[6][1]*Wpk[3][14][2])-(rk[6][2]*
          Wpk[3][14][1])));
        Vpk[3][14][1] = (((rk[6][2]*Wpk[3][13][0])-(rk[6][0]*Wpk[3][14][2]))+((
          Vpk[3][13][2]*s14)+(VWri[3][13][1]*c14)));
        Vpk[3][14][2] = (((rk[6][0]*Wpk[3][14][1])-(rk[6][1]*Wpk[3][13][0]))+((
          Vpk[3][13][2]*c14)-(VWri[3][13][1]*s14)));
        VWri[3][15][0] = (Vpk[3][5][0]+((ri[7][2]*Wpk[3][5][1])-(ri[7][1]*
          Wpk[3][5][2])));
        VWri[3][15][1] = (Vpk[3][5][1]+((ri[7][0]*Wpk[3][5][2])+(ri[7][2]*s4)));
        VWri[3][15][2] = (Vpk[3][5][2]-((ri[7][0]*Wpk[3][5][1])+(ri[7][1]*s4)));
        Vpk[3][15][0] = ((VWri[3][15][0]*c15)+(VWri[3][15][1]*s15));
        Vpk[3][15][1] = ((VWri[3][15][1]*c15)-(VWri[3][15][0]*s15));
        Vpk[3][15][2] = VWri[3][15][2];
        Vpk[3][16][0] = Vpk[3][15][0];
        Vpk[3][16][1] = ((Vpk[3][15][1]*c16)+(VWri[3][15][2]*s16));
        Vpk[3][16][2] = ((VWri[3][15][2]*c16)-(Vpk[3][15][1]*s16));
        Vpk[3][17][0] = (((rk[7][1]*Wpk[3][17][2])-(rk[7][2]*Wpk[3][16][1]))+((
          Vpk[3][15][0]*c17)-(Vpk[3][16][2]*s17)));
        Vpk[3][17][1] = (Vpk[3][16][1]+((rk[7][2]*Wpk[3][17][0])-(rk[7][0]*
          Wpk[3][17][2])));
        Vpk[3][17][2] = (((rk[7][0]*Wpk[3][16][1])-(rk[7][1]*Wpk[3][17][0]))+((
          Vpk[3][15][0]*s17)+(Vpk[3][16][2]*c17)));
        VWri[3][18][0] = (Vpk[3][17][0]+((ri[8][2]*Wpk[3][16][1])-(ri[8][1]*
          Wpk[3][17][2])));
        VWri[3][18][1] = (Vpk[3][17][1]+((ri[8][0]*Wpk[3][17][2])-(ri[8][2]*
          Wpk[3][17][0])));
        VWri[3][18][2] = (Vpk[3][17][2]+((ri[8][1]*Wpk[3][17][0])-(ri[8][0]*
          Wpk[3][16][1])));
        Vpk[3][18][0] = (((rk[8][1]*Wpk[3][18][2])-(rk[8][2]*Wpk[3][16][1]))+((
          VWri[3][18][0]*c18)-(VWri[3][18][2]*s18)));
        Vpk[3][18][1] = (VWri[3][18][1]+((rk[8][2]*Wpk[3][18][0])-(rk[8][0]*
          Wpk[3][18][2])));
        Vpk[3][18][2] = (((rk[8][0]*Wpk[3][16][1])-(rk[8][1]*Wpk[3][18][0]))+((
          VWri[3][18][0]*s18)+(VWri[3][18][2]*c18)));
        VWri[3][19][0] = (Vpk[3][18][0]+((ri[9][2]*Wpk[3][16][1])-(ri[9][1]*
          Wpk[3][18][2])));
        VWri[3][19][1] = (Vpk[3][18][1]+((ri[9][0]*Wpk[3][18][2])-(ri[9][2]*
          Wpk[3][18][0])));
        VWri[3][19][2] = (Vpk[3][18][2]+((ri[9][1]*Wpk[3][18][0])-(ri[9][0]*
          Wpk[3][16][1])));
        Vpk[3][19][0] = ((VWri[3][19][0]*c19)-(VWri[3][19][2]*s19));
        Vpk[3][19][1] = VWri[3][19][1];
        Vpk[3][19][2] = ((VWri[3][19][0]*s19)+(VWri[3][19][2]*c19));
        Vpk[3][20][0] = (Vpk[3][19][0]+((rk[9][1]*Wpk[3][20][2])-(rk[9][2]*
          Wpk[3][20][1])));
        Vpk[3][20][1] = (((rk[9][2]*Wpk[3][19][0])-(rk[9][0]*Wpk[3][20][2]))+((
          Vpk[3][19][2]*s20)+(VWri[3][19][1]*c20)));
        Vpk[3][20][2] = (((rk[9][0]*Wpk[3][20][1])-(rk[9][1]*Wpk[3][19][0]))+((
          Vpk[3][19][2]*c20)-(VWri[3][19][1]*s20)));
        Vpk[4][5][0] = -((rk[0][1]*s5)+(rk[0][2]*c5));
        Vpk[4][5][1] = (rk[0][0]*s5);
        Vpk[4][5][2] = (rk[0][0]*c5);
        VWri[4][6][0] = (Vpk[4][5][0]+((ri[1][1]*s5)+(ri[1][2]*c5)));
        VWri[4][6][1] = (Vpk[4][5][1]-(ri[1][0]*s5));
        VWri[4][6][2] = (Vpk[4][5][2]-(ri[1][0]*c5));
        Vpk[4][6][0] = (((VWri[4][6][0]*c6)+(VWri[4][6][1]*s6))-((rk[1][1]*s5)+(
          rk[1][2]*Wpk[4][6][1])));
        Vpk[4][6][1] = (((rk[1][0]*s5)+(rk[1][2]*Wpk[4][6][0]))+((VWri[4][6][1]*
          c6)-(VWri[4][6][0]*s6)));
        Vpk[4][6][2] = (VWri[4][6][2]+((rk[1][0]*Wpk[4][6][1])-(rk[1][1]*
          Wpk[4][6][0])));
        VWri[4][7][0] = (Vpk[4][6][0]+((ri[2][1]*s5)+(ri[2][2]*Wpk[4][6][1])));
        VWri[4][7][1] = (Vpk[4][6][1]-((ri[2][0]*s5)+(ri[2][2]*Wpk[4][6][0])));
        VWri[4][7][2] = (Vpk[4][6][2]+((ri[2][1]*Wpk[4][6][0])-(ri[2][0]*
          Wpk[4][6][1])));
        Vpk[4][7][0] = (((rk[2][1]*Wpk[4][7][2])-(rk[2][2]*Wpk[4][6][1]))+((
          VWri[4][7][0]*c7)-(VWri[4][7][2]*s7)));
        Vpk[4][7][1] = (VWri[4][7][1]+((rk[2][2]*Wpk[4][7][0])-(rk[2][0]*
          Wpk[4][7][2])));
        Vpk[4][7][2] = (((rk[2][0]*Wpk[4][6][1])-(rk[2][1]*Wpk[4][7][0]))+((
          VWri[4][7][0]*s7)+(VWri[4][7][2]*c7)));
        VWri[4][8][0] = (Vpk[4][6][0]+((ri[3][1]*s5)+(ri[3][2]*Wpk[4][6][1])));
        VWri[4][8][1] = (Vpk[4][6][1]-((ri[3][0]*s5)+(ri[3][2]*Wpk[4][6][0])));
        VWri[4][8][2] = (Vpk[4][6][2]+((ri[3][1]*Wpk[4][6][0])-(ri[3][0]*
          Wpk[4][6][1])));
        Vpk[4][8][0] = (((rk[3][1]*Wpk[4][8][2])-(rk[3][2]*Wpk[4][6][1]))+((
          VWri[4][8][0]*c8)-(VWri[4][8][2]*s8)));
        Vpk[4][8][1] = (VWri[4][8][1]+((rk[3][2]*Wpk[4][8][0])-(rk[3][0]*
          Wpk[4][8][2])));
        Vpk[4][8][2] = (((rk[3][0]*Wpk[4][6][1])-(rk[3][1]*Wpk[4][8][0]))+((
          VWri[4][8][0]*s8)+(VWri[4][8][2]*c8)));
        VWri[4][9][0] = (Vpk[4][5][0]+((ri[4][1]*s5)+(ri[4][2]*c5)));
        VWri[4][9][1] = (Vpk[4][5][1]-(ri[4][0]*s5));
        VWri[4][9][2] = (Vpk[4][5][2]-(ri[4][0]*c5));
        Vpk[4][9][0] = ((VWri[4][9][0]*c9)+(VWri[4][9][1]*s9));
        Vpk[4][9][1] = ((VWri[4][9][1]*c9)-(VWri[4][9][0]*s9));
        Vpk[4][9][2] = VWri[4][9][2];
        Vpk[4][10][0] = Vpk[4][9][0];
        Vpk[4][10][1] = ((Vpk[4][9][1]*c10)+(VWri[4][9][2]*s10));
        Vpk[4][10][2] = ((VWri[4][9][2]*c10)-(Vpk[4][9][1]*s10));
        Vpk[4][11][0] = (((rk[4][1]*Wpk[4][11][2])-(rk[4][2]*Wpk[4][10][1]))+((
          Vpk[4][9][0]*c11)-(Vpk[4][10][2]*s11)));
        Vpk[4][11][1] = (Vpk[4][10][1]+((rk[4][2]*Wpk[4][11][0])-(rk[4][0]*
          Wpk[4][11][2])));
        Vpk[4][11][2] = (((rk[4][0]*Wpk[4][10][1])-(rk[4][1]*Wpk[4][11][0]))+((
          Vpk[4][9][0]*s11)+(Vpk[4][10][2]*c11)));
        VWri[4][12][0] = (Vpk[4][11][0]+((ri[5][2]*Wpk[4][10][1])-(ri[5][1]*
          Wpk[4][11][2])));
        VWri[4][12][1] = (Vpk[4][11][1]+((ri[5][0]*Wpk[4][11][2])-(ri[5][2]*
          Wpk[4][11][0])));
        VWri[4][12][2] = (Vpk[4][11][2]+((ri[5][1]*Wpk[4][11][0])-(ri[5][0]*
          Wpk[4][10][1])));
        Vpk[4][12][0] = (((rk[5][1]*Wpk[4][12][2])-(rk[5][2]*Wpk[4][10][1]))+((
          VWri[4][12][0]*c12)-(VWri[4][12][2]*s12)));
        Vpk[4][12][1] = (VWri[4][12][1]+((rk[5][2]*Wpk[4][12][0])-(rk[5][0]*
          Wpk[4][12][2])));
        Vpk[4][12][2] = (((rk[5][0]*Wpk[4][10][1])-(rk[5][1]*Wpk[4][12][0]))+((
          VWri[4][12][0]*s12)+(VWri[4][12][2]*c12)));
        VWri[4][13][0] = (Vpk[4][12][0]+((ri[6][2]*Wpk[4][10][1])-(ri[6][1]*
          Wpk[4][12][2])));
        VWri[4][13][1] = (Vpk[4][12][1]+((ri[6][0]*Wpk[4][12][2])-(ri[6][2]*
          Wpk[4][12][0])));
        VWri[4][13][2] = (Vpk[4][12][2]+((ri[6][1]*Wpk[4][12][0])-(ri[6][0]*
          Wpk[4][10][1])));
        Vpk[4][13][0] = ((VWri[4][13][0]*c13)-(VWri[4][13][2]*s13));
        Vpk[4][13][1] = VWri[4][13][1];
        Vpk[4][13][2] = ((VWri[4][13][0]*s13)+(VWri[4][13][2]*c13));
        Vpk[4][14][0] = (Vpk[4][13][0]+((rk[6][1]*Wpk[4][14][2])-(rk[6][2]*
          Wpk[4][14][1])));
        Vpk[4][14][1] = (((rk[6][2]*Wpk[4][13][0])-(rk[6][0]*Wpk[4][14][2]))+((
          Vpk[4][13][2]*s14)+(VWri[4][13][1]*c14)));
        Vpk[4][14][2] = (((rk[6][0]*Wpk[4][14][1])-(rk[6][1]*Wpk[4][13][0]))+((
          Vpk[4][13][2]*c14)-(VWri[4][13][1]*s14)));
        VWri[4][15][0] = (Vpk[4][5][0]+((ri[7][1]*s5)+(ri[7][2]*c5)));
        VWri[4][15][1] = (Vpk[4][5][1]-(ri[7][0]*s5));
        VWri[4][15][2] = (Vpk[4][5][2]-(ri[7][0]*c5));
        Vpk[4][15][0] = ((VWri[4][15][0]*c15)+(VWri[4][15][1]*s15));
        Vpk[4][15][1] = ((VWri[4][15][1]*c15)-(VWri[4][15][0]*s15));
        Vpk[4][15][2] = VWri[4][15][2];
        Vpk[4][16][0] = Vpk[4][15][0];
        Vpk[4][16][1] = ((Vpk[4][15][1]*c16)+(VWri[4][15][2]*s16));
        Vpk[4][16][2] = ((VWri[4][15][2]*c16)-(Vpk[4][15][1]*s16));
        Vpk[4][17][0] = (((rk[7][1]*Wpk[4][17][2])-(rk[7][2]*Wpk[4][16][1]))+((
          Vpk[4][15][0]*c17)-(Vpk[4][16][2]*s17)));
        Vpk[4][17][1] = (Vpk[4][16][1]+((rk[7][2]*Wpk[4][17][0])-(rk[7][0]*
          Wpk[4][17][2])));
        Vpk[4][17][2] = (((rk[7][0]*Wpk[4][16][1])-(rk[7][1]*Wpk[4][17][0]))+((
          Vpk[4][15][0]*s17)+(Vpk[4][16][2]*c17)));
        VWri[4][18][0] = (Vpk[4][17][0]+((ri[8][2]*Wpk[4][16][1])-(ri[8][1]*
          Wpk[4][17][2])));
        VWri[4][18][1] = (Vpk[4][17][1]+((ri[8][0]*Wpk[4][17][2])-(ri[8][2]*
          Wpk[4][17][0])));
        VWri[4][18][2] = (Vpk[4][17][2]+((ri[8][1]*Wpk[4][17][0])-(ri[8][0]*
          Wpk[4][16][1])));
        Vpk[4][18][0] = (((rk[8][1]*Wpk[4][18][2])-(rk[8][2]*Wpk[4][16][1]))+((
          VWri[4][18][0]*c18)-(VWri[4][18][2]*s18)));
        Vpk[4][18][1] = (VWri[4][18][1]+((rk[8][2]*Wpk[4][18][0])-(rk[8][0]*
          Wpk[4][18][2])));
        Vpk[4][18][2] = (((rk[8][0]*Wpk[4][16][1])-(rk[8][1]*Wpk[4][18][0]))+((
          VWri[4][18][0]*s18)+(VWri[4][18][2]*c18)));
        VWri[4][19][0] = (Vpk[4][18][0]+((ri[9][2]*Wpk[4][16][1])-(ri[9][1]*
          Wpk[4][18][2])));
        VWri[4][19][1] = (Vpk[4][18][1]+((ri[9][0]*Wpk[4][18][2])-(ri[9][2]*
          Wpk[4][18][0])));
        VWri[4][19][2] = (Vpk[4][18][2]+((ri[9][1]*Wpk[4][18][0])-(ri[9][0]*
          Wpk[4][16][1])));
        Vpk[4][19][0] = ((VWri[4][19][0]*c19)-(VWri[4][19][2]*s19));
        Vpk[4][19][1] = VWri[4][19][1];
        Vpk[4][19][2] = ((VWri[4][19][0]*s19)+(VWri[4][19][2]*c19));
        Vpk[4][20][0] = (Vpk[4][19][0]+((rk[9][1]*Wpk[4][20][2])-(rk[9][2]*
          Wpk[4][20][1])));
        Vpk[4][20][1] = (((rk[9][2]*Wpk[4][19][0])-(rk[9][0]*Wpk[4][20][2]))+((
          Vpk[4][19][2]*s20)+(VWri[4][19][1]*c20)));
        Vpk[4][20][2] = (((rk[9][0]*Wpk[4][20][1])-(rk[9][1]*Wpk[4][19][0]))+((
          Vpk[4][19][2]*c20)-(VWri[4][19][1]*s20)));
        Vpk[5][5][1] = rk[0][2];
        Vpk[5][5][2] = -rk[0][1];
        VWri[5][6][1] = (rk[0][2]-ri[1][2]);
        VWri[5][6][2] = (ri[1][1]-rk[0][1]);
        Vpk[5][6][0] = ((rk[1][2]*s6)+(VWri[5][6][1]*s6));
        Vpk[5][6][1] = ((rk[1][2]*c6)+(VWri[5][6][1]*c6));
        Vpk[5][6][2] = (VWri[5][6][2]-((rk[1][0]*s6)+(rk[1][1]*c6)));
        VWri[5][7][0] = (Vpk[5][6][0]-(ri[2][2]*s6));
        VWri[5][7][1] = (Vpk[5][6][1]-(ri[2][2]*c6));
        VWri[5][7][2] = (Vpk[5][6][2]+((ri[2][0]*s6)+(ri[2][1]*c6)));
        Vpk[5][7][0] = (((rk[2][1]*Wpk[5][7][2])+(rk[2][2]*s6))+((VWri[5][7][0]*
          c7)-(VWri[5][7][2]*s7)));
        Vpk[5][7][1] = (VWri[5][7][1]+((rk[2][2]*Wpk[5][7][0])-(rk[2][0]*
          Wpk[5][7][2])));
        Vpk[5][7][2] = (((VWri[5][7][0]*s7)+(VWri[5][7][2]*c7))-((rk[2][0]*s6)+(
          rk[2][1]*Wpk[5][7][0])));
        VWri[5][8][0] = (Vpk[5][6][0]-(ri[3][2]*s6));
        VWri[5][8][1] = (Vpk[5][6][1]-(ri[3][2]*c6));
        VWri[5][8][2] = (Vpk[5][6][2]+((ri[3][0]*s6)+(ri[3][1]*c6)));
        Vpk[5][8][0] = (((rk[3][1]*Wpk[5][8][2])+(rk[3][2]*s6))+((VWri[5][8][0]*
          c8)-(VWri[5][8][2]*s8)));
        Vpk[5][8][1] = (VWri[5][8][1]+((rk[3][2]*Wpk[5][8][0])-(rk[3][0]*
          Wpk[5][8][2])));
        Vpk[5][8][2] = (((VWri[5][8][0]*s8)+(VWri[5][8][2]*c8))-((rk[3][0]*s6)+(
          rk[3][1]*Wpk[5][8][0])));
        VWri[5][9][1] = (rk[0][2]-ri[4][2]);
        VWri[5][9][2] = (ri[4][1]-rk[0][1]);
        Vpk[5][9][0] = (VWri[5][9][1]*s9);
        Vpk[5][9][1] = (VWri[5][9][1]*c9);
        Vpk[5][9][2] = VWri[5][9][2];
        Vpk[5][10][0] = Vpk[5][9][0];
        Vpk[5][10][1] = ((Vpk[5][9][1]*c10)+(VWri[5][9][2]*s10));
        Vpk[5][10][2] = ((VWri[5][9][2]*c10)-(Vpk[5][9][1]*s10));
        Vpk[5][11][0] = (((rk[4][1]*Wpk[5][11][2])-(rk[4][2]*Wpk[5][10][1]))+((
          Vpk[5][9][0]*c11)-(Vpk[5][10][2]*s11)));
        Vpk[5][11][1] = (Vpk[5][10][1]+((rk[4][2]*Wpk[5][11][0])-(rk[4][0]*
          Wpk[5][11][2])));
        Vpk[5][11][2] = (((rk[4][0]*Wpk[5][10][1])-(rk[4][1]*Wpk[5][11][0]))+((
          Vpk[5][9][0]*s11)+(Vpk[5][10][2]*c11)));
        VWri[5][12][0] = (Vpk[5][11][0]+((ri[5][2]*Wpk[5][10][1])-(ri[5][1]*
          Wpk[5][11][2])));
        VWri[5][12][1] = (Vpk[5][11][1]+((ri[5][0]*Wpk[5][11][2])-(ri[5][2]*
          Wpk[5][11][0])));
        VWri[5][12][2] = (Vpk[5][11][2]+((ri[5][1]*Wpk[5][11][0])-(ri[5][0]*
          Wpk[5][10][1])));
        Vpk[5][12][0] = (((rk[5][1]*Wpk[5][12][2])-(rk[5][2]*Wpk[5][10][1]))+((
          VWri[5][12][0]*c12)-(VWri[5][12][2]*s12)));
        Vpk[5][12][1] = (VWri[5][12][1]+((rk[5][2]*Wpk[5][12][0])-(rk[5][0]*
          Wpk[5][12][2])));
        Vpk[5][12][2] = (((rk[5][0]*Wpk[5][10][1])-(rk[5][1]*Wpk[5][12][0]))+((
          VWri[5][12][0]*s12)+(VWri[5][12][2]*c12)));
        VWri[5][13][0] = (Vpk[5][12][0]+((ri[6][2]*Wpk[5][10][1])-(ri[6][1]*
          Wpk[5][12][2])));
        VWri[5][13][1] = (Vpk[5][12][1]+((ri[6][0]*Wpk[5][12][2])-(ri[6][2]*
          Wpk[5][12][0])));
        VWri[5][13][2] = (Vpk[5][12][2]+((ri[6][1]*Wpk[5][12][0])-(ri[6][0]*
          Wpk[5][10][1])));
        Vpk[5][13][0] = ((VWri[5][13][0]*c13)-(VWri[5][13][2]*s13));
        Vpk[5][13][1] = VWri[5][13][1];
        Vpk[5][13][2] = ((VWri[5][13][0]*s13)+(VWri[5][13][2]*c13));
        Vpk[5][14][0] = (Vpk[5][13][0]+((rk[6][1]*Wpk[5][14][2])-(rk[6][2]*
          Wpk[5][14][1])));
        Vpk[5][14][1] = (((rk[6][2]*Wpk[5][13][0])-(rk[6][0]*Wpk[5][14][2]))+((
          Vpk[5][13][2]*s14)+(VWri[5][13][1]*c14)));
        Vpk[5][14][2] = (((rk[6][0]*Wpk[5][14][1])-(rk[6][1]*Wpk[5][13][0]))+((
          Vpk[5][13][2]*c14)-(VWri[5][13][1]*s14)));
        VWri[5][15][1] = (rk[0][2]-ri[7][2]);
        VWri[5][15][2] = (ri[7][1]-rk[0][1]);
        Vpk[5][15][0] = (VWri[5][15][1]*s15);
        Vpk[5][15][1] = (VWri[5][15][1]*c15);
        Vpk[5][15][2] = VWri[5][15][2];
        Vpk[5][16][0] = Vpk[5][15][0];
        Vpk[5][16][1] = ((Vpk[5][15][1]*c16)+(VWri[5][15][2]*s16));
        Vpk[5][16][2] = ((VWri[5][15][2]*c16)-(Vpk[5][15][1]*s16));
        Vpk[5][17][0] = (((rk[7][1]*Wpk[5][17][2])-(rk[7][2]*Wpk[5][16][1]))+((
          Vpk[5][15][0]*c17)-(Vpk[5][16][2]*s17)));
        Vpk[5][17][1] = (Vpk[5][16][1]+((rk[7][2]*Wpk[5][17][0])-(rk[7][0]*
          Wpk[5][17][2])));
        Vpk[5][17][2] = (((rk[7][0]*Wpk[5][16][1])-(rk[7][1]*Wpk[5][17][0]))+((
          Vpk[5][15][0]*s17)+(Vpk[5][16][2]*c17)));
        VWri[5][18][0] = (Vpk[5][17][0]+((ri[8][2]*Wpk[5][16][1])-(ri[8][1]*
          Wpk[5][17][2])));
        VWri[5][18][1] = (Vpk[5][17][1]+((ri[8][0]*Wpk[5][17][2])-(ri[8][2]*
          Wpk[5][17][0])));
        VWri[5][18][2] = (Vpk[5][17][2]+((ri[8][1]*Wpk[5][17][0])-(ri[8][0]*
          Wpk[5][16][1])));
        Vpk[5][18][0] = (((rk[8][1]*Wpk[5][18][2])-(rk[8][2]*Wpk[5][16][1]))+((
          VWri[5][18][0]*c18)-(VWri[5][18][2]*s18)));
        Vpk[5][18][1] = (VWri[5][18][1]+((rk[8][2]*Wpk[5][18][0])-(rk[8][0]*
          Wpk[5][18][2])));
        Vpk[5][18][2] = (((rk[8][0]*Wpk[5][16][1])-(rk[8][1]*Wpk[5][18][0]))+((
          VWri[5][18][0]*s18)+(VWri[5][18][2]*c18)));
        VWri[5][19][0] = (Vpk[5][18][0]+((ri[9][2]*Wpk[5][16][1])-(ri[9][1]*
          Wpk[5][18][2])));
        VWri[5][19][1] = (Vpk[5][18][1]+((ri[9][0]*Wpk[5][18][2])-(ri[9][2]*
          Wpk[5][18][0])));
        VWri[5][19][2] = (Vpk[5][18][2]+((ri[9][1]*Wpk[5][18][0])-(ri[9][0]*
          Wpk[5][16][1])));
        Vpk[5][19][0] = ((VWri[5][19][0]*c19)-(VWri[5][19][2]*s19));
        Vpk[5][19][1] = VWri[5][19][1];
        Vpk[5][19][2] = ((VWri[5][19][0]*s19)+(VWri[5][19][2]*c19));
        Vpk[5][20][0] = (Vpk[5][19][0]+((rk[9][1]*Wpk[5][20][2])-(rk[9][2]*
          Wpk[5][20][1])));
        Vpk[5][20][1] = (((rk[9][2]*Wpk[5][19][0])-(rk[9][0]*Wpk[5][20][2]))+((
          Vpk[5][19][2]*s20)+(VWri[5][19][1]*c20)));
        Vpk[5][20][2] = (((rk[9][0]*Wpk[5][20][1])-(rk[9][1]*Wpk[5][19][0]))+((
          Vpk[5][19][2]*c20)-(VWri[5][19][1]*s20)));
        Vpk[6][6][0] = rk[1][1];
        Vpk[6][6][1] = -rk[1][0];
        VWri[6][7][0] = (rk[1][1]-ri[2][1]);
        VWri[6][7][1] = (ri[2][0]-rk[1][0]);
        Vpk[6][7][0] = ((rk[2][1]*c7)+(VWri[6][7][0]*c7));
        Vpk[6][7][1] = (VWri[6][7][1]-((rk[2][0]*c7)+(rk[2][2]*s7)));
        Vpk[6][7][2] = ((rk[2][1]*s7)+(VWri[6][7][0]*s7));
        VWri[6][8][0] = (rk[1][1]-ri[3][1]);
        VWri[6][8][1] = (ri[3][0]-rk[1][0]);
        Vpk[6][8][0] = ((rk[3][1]*c8)+(VWri[6][8][0]*c8));
        Vpk[6][8][1] = (VWri[6][8][1]-((rk[3][0]*c8)+(rk[3][2]*s8)));
        Vpk[6][8][2] = ((rk[3][1]*s8)+(VWri[6][8][0]*s8));
        Vpk[7][7][0] = -rk[2][2];
        Vpk[7][7][2] = rk[2][0];
        Vpk[8][8][0] = -rk[3][2];
        Vpk[8][8][2] = rk[3][0];
        Vpk[9][11][0] = ((rk[4][1]*Wpk[9][11][2])-(rk[4][2]*s10));
        Vpk[9][11][1] = ((rk[4][2]*Wpk[9][11][0])-(rk[4][0]*Wpk[9][11][2]));
        Vpk[9][11][2] = ((rk[4][0]*s10)-(rk[4][1]*Wpk[9][11][0]));
        VWri[9][12][0] = (Vpk[9][11][0]+((ri[5][2]*s10)-(ri[5][1]*Wpk[9][11][2])
          ));
        VWri[9][12][1] = (Vpk[9][11][1]+((ri[5][0]*Wpk[9][11][2])-(ri[5][2]*
          Wpk[9][11][0])));
        VWri[9][12][2] = (Vpk[9][11][2]+((ri[5][1]*Wpk[9][11][0])-(ri[5][0]*s10)
          ));
        Vpk[9][12][0] = (((rk[5][1]*Wpk[9][12][2])-(rk[5][2]*s10))+((
          VWri[9][12][0]*c12)-(VWri[9][12][2]*s12)));
        Vpk[9][12][1] = (VWri[9][12][1]+((rk[5][2]*Wpk[9][12][0])-(rk[5][0]*
          Wpk[9][12][2])));
        Vpk[9][12][2] = (((rk[5][0]*s10)-(rk[5][1]*Wpk[9][12][0]))+((
          VWri[9][12][0]*s12)+(VWri[9][12][2]*c12)));
        VWri[9][13][0] = (Vpk[9][12][0]+((ri[6][2]*s10)-(ri[6][1]*Wpk[9][12][2])
          ));
        VWri[9][13][1] = (Vpk[9][12][1]+((ri[6][0]*Wpk[9][12][2])-(ri[6][2]*
          Wpk[9][12][0])));
        VWri[9][13][2] = (Vpk[9][12][2]+((ri[6][1]*Wpk[9][12][0])-(ri[6][0]*s10)
          ));
        Vpk[9][13][0] = ((VWri[9][13][0]*c13)-(VWri[9][13][2]*s13));
        Vpk[9][13][1] = VWri[9][13][1];
        Vpk[9][13][2] = ((VWri[9][13][0]*s13)+(VWri[9][13][2]*c13));
        Vpk[9][14][0] = (Vpk[9][13][0]+((rk[6][1]*Wpk[9][14][2])-(rk[6][2]*
          Wpk[9][14][1])));
        Vpk[9][14][1] = (((rk[6][2]*Wpk[9][13][0])-(rk[6][0]*Wpk[9][14][2]))+((
          Vpk[9][13][2]*s14)+(VWri[9][13][1]*c14)));
        Vpk[9][14][2] = (((rk[6][0]*Wpk[9][14][1])-(rk[6][1]*Wpk[9][13][0]))+((
          Vpk[9][13][2]*c14)-(VWri[9][13][1]*s14)));
        Vpk[10][11][0] = (rk[4][1]*s11);
        Vpk[10][11][1] = ((rk[4][2]*c11)-(rk[4][0]*s11));
        Vpk[10][11][2] = -(rk[4][1]*c11);
        VWri[10][12][0] = (Vpk[10][11][0]-(ri[5][1]*s11));
        VWri[10][12][1] = (Vpk[10][11][1]+((ri[5][0]*s11)-(ri[5][2]*c11)));
        VWri[10][12][2] = (Vpk[10][11][2]+(ri[5][1]*c11));
        Vpk[10][12][0] = ((rk[5][1]*Wpk[10][12][2])+((VWri[10][12][0]*c12)-(
          VWri[10][12][2]*s12)));
        Vpk[10][12][1] = (VWri[10][12][1]+((rk[5][2]*Wpk[10][12][0])-(rk[5][0]*
          Wpk[10][12][2])));
        Vpk[10][12][2] = (((VWri[10][12][0]*s12)+(VWri[10][12][2]*c12))-(
          rk[5][1]*Wpk[10][12][0]));
        VWri[10][13][0] = (Vpk[10][12][0]-(ri[6][1]*Wpk[10][12][2]));
        VWri[10][13][1] = (Vpk[10][12][1]+((ri[6][0]*Wpk[10][12][2])-(ri[6][2]*
          Wpk[10][12][0])));
        VWri[10][13][2] = (Vpk[10][12][2]+(ri[6][1]*Wpk[10][12][0]));
        Vpk[10][13][0] = ((VWri[10][13][0]*c13)-(VWri[10][13][2]*s13));
        Vpk[10][13][1] = VWri[10][13][1];
        Vpk[10][13][2] = ((VWri[10][13][0]*s13)+(VWri[10][13][2]*c13));
        Vpk[10][14][0] = (Vpk[10][13][0]+((rk[6][1]*Wpk[10][14][2])-(rk[6][2]*
          Wpk[10][14][1])));
        Vpk[10][14][1] = (((rk[6][2]*Wpk[10][13][0])-(rk[6][0]*Wpk[10][14][2]))+
          ((Vpk[10][13][2]*s14)+(VWri[10][13][1]*c14)));
        Vpk[10][14][2] = (((rk[6][0]*Wpk[10][14][1])-(rk[6][1]*Wpk[10][13][0]))+
          ((Vpk[10][13][2]*c14)-(VWri[10][13][1]*s14)));
        Vpk[11][11][0] = -rk[4][2];
        Vpk[11][11][2] = rk[4][0];
        VWri[11][12][0] = (ri[5][2]-rk[4][2]);
        VWri[11][12][2] = (rk[4][0]-ri[5][0]);
        Vpk[11][12][0] = (((VWri[11][12][0]*c12)-(VWri[11][12][2]*s12))-rk[5][2]
          );
        Vpk[11][12][2] = (rk[5][0]+((VWri[11][12][0]*s12)+(VWri[11][12][2]*c12))
          );
        VWri[11][13][0] = (ri[6][2]+Vpk[11][12][0]);
        VWri[11][13][2] = (Vpk[11][12][2]-ri[6][0]);
        Vpk[11][13][0] = ((VWri[11][13][0]*c13)-(VWri[11][13][2]*s13));
        Vpk[11][13][2] = ((VWri[11][13][0]*s13)+(VWri[11][13][2]*c13));
        Vpk[11][14][0] = (Vpk[11][13][0]-((rk[6][1]*s14)+(rk[6][2]*c14)));
        Vpk[11][14][1] = ((rk[6][0]*s14)+(Vpk[11][13][2]*s14));
        Vpk[11][14][2] = ((rk[6][0]*c14)+(Vpk[11][13][2]*c14));
        Vpk[12][12][0] = -rk[5][2];
        Vpk[12][12][2] = rk[5][0];
        VWri[12][13][0] = (ri[6][2]-rk[5][2]);
        VWri[12][13][2] = (rk[5][0]-ri[6][0]);
        Vpk[12][13][0] = ((VWri[12][13][0]*c13)-(VWri[12][13][2]*s13));
        Vpk[12][13][2] = ((VWri[12][13][0]*s13)+(VWri[12][13][2]*c13));
        Vpk[12][14][0] = (Vpk[12][13][0]-((rk[6][1]*s14)+(rk[6][2]*c14)));
        Vpk[12][14][1] = ((rk[6][0]*s14)+(Vpk[12][13][2]*s14));
        Vpk[12][14][2] = ((rk[6][0]*c14)+(Vpk[12][13][2]*c14));
        Vpk[13][14][0] = -((rk[6][1]*s14)+(rk[6][2]*c14));
        Vpk[13][14][1] = (rk[6][0]*s14);
        Vpk[13][14][2] = (rk[6][0]*c14);
        Vpk[14][14][1] = rk[6][2];
        Vpk[14][14][2] = -rk[6][1];
        Vpk[15][17][0] = ((rk[7][1]*Wpk[15][17][2])-(rk[7][2]*s16));
        Vpk[15][17][1] = ((rk[7][2]*Wpk[15][17][0])-(rk[7][0]*Wpk[15][17][2]));
        Vpk[15][17][2] = ((rk[7][0]*s16)-(rk[7][1]*Wpk[15][17][0]));
        VWri[15][18][0] = (Vpk[15][17][0]+((ri[8][2]*s16)-(ri[8][1]*
          Wpk[15][17][2])));
        VWri[15][18][1] = (Vpk[15][17][1]+((ri[8][0]*Wpk[15][17][2])-(ri[8][2]*
          Wpk[15][17][0])));
        VWri[15][18][2] = (Vpk[15][17][2]+((ri[8][1]*Wpk[15][17][0])-(ri[8][0]*
          s16)));
        Vpk[15][18][0] = (((rk[8][1]*Wpk[15][18][2])-(rk[8][2]*s16))+((
          VWri[15][18][0]*c18)-(VWri[15][18][2]*s18)));
        Vpk[15][18][1] = (VWri[15][18][1]+((rk[8][2]*Wpk[15][18][0])-(rk[8][0]*
          Wpk[15][18][2])));
        Vpk[15][18][2] = (((rk[8][0]*s16)-(rk[8][1]*Wpk[15][18][0]))+((
          VWri[15][18][0]*s18)+(VWri[15][18][2]*c18)));
        VWri[15][19][0] = (Vpk[15][18][0]+((ri[9][2]*s16)-(ri[9][1]*
          Wpk[15][18][2])));
        VWri[15][19][1] = (Vpk[15][18][1]+((ri[9][0]*Wpk[15][18][2])-(ri[9][2]*
          Wpk[15][18][0])));
        VWri[15][19][2] = (Vpk[15][18][2]+((ri[9][1]*Wpk[15][18][0])-(ri[9][0]*
          s16)));
        Vpk[15][19][0] = ((VWri[15][19][0]*c19)-(VWri[15][19][2]*s19));
        Vpk[15][19][1] = VWri[15][19][1];
        Vpk[15][19][2] = ((VWri[15][19][0]*s19)+(VWri[15][19][2]*c19));
        Vpk[15][20][0] = (Vpk[15][19][0]+((rk[9][1]*Wpk[15][20][2])-(rk[9][2]*
          Wpk[15][20][1])));
        Vpk[15][20][1] = (((rk[9][2]*Wpk[15][19][0])-(rk[9][0]*Wpk[15][20][2]))+
          ((Vpk[15][19][2]*s20)+(VWri[15][19][1]*c20)));
        Vpk[15][20][2] = (((rk[9][0]*Wpk[15][20][1])-(rk[9][1]*Wpk[15][19][0]))+
          ((Vpk[15][19][2]*c20)-(VWri[15][19][1]*s20)));
        Vpk[16][17][0] = (rk[7][1]*s17);
        Vpk[16][17][1] = ((rk[7][2]*c17)-(rk[7][0]*s17));
        Vpk[16][17][2] = -(rk[7][1]*c17);
        VWri[16][18][0] = (Vpk[16][17][0]-(ri[8][1]*s17));
        VWri[16][18][1] = (Vpk[16][17][1]+((ri[8][0]*s17)-(ri[8][2]*c17)));
        VWri[16][18][2] = (Vpk[16][17][2]+(ri[8][1]*c17));
        Vpk[16][18][0] = ((rk[8][1]*Wpk[16][18][2])+((VWri[16][18][0]*c18)-(
          VWri[16][18][2]*s18)));
        Vpk[16][18][1] = (VWri[16][18][1]+((rk[8][2]*Wpk[16][18][0])-(rk[8][0]*
          Wpk[16][18][2])));
        Vpk[16][18][2] = (((VWri[16][18][0]*s18)+(VWri[16][18][2]*c18))-(
          rk[8][1]*Wpk[16][18][0]));
        VWri[16][19][0] = (Vpk[16][18][0]-(ri[9][1]*Wpk[16][18][2]));
        VWri[16][19][1] = (Vpk[16][18][1]+((ri[9][0]*Wpk[16][18][2])-(ri[9][2]*
          Wpk[16][18][0])));
        VWri[16][19][2] = (Vpk[16][18][2]+(ri[9][1]*Wpk[16][18][0]));
        Vpk[16][19][0] = ((VWri[16][19][0]*c19)-(VWri[16][19][2]*s19));
        Vpk[16][19][1] = VWri[16][19][1];
        Vpk[16][19][2] = ((VWri[16][19][0]*s19)+(VWri[16][19][2]*c19));
        Vpk[16][20][0] = (Vpk[16][19][0]+((rk[9][1]*Wpk[16][20][2])-(rk[9][2]*
          Wpk[16][20][1])));
        Vpk[16][20][1] = (((rk[9][2]*Wpk[16][19][0])-(rk[9][0]*Wpk[16][20][2]))+
          ((Vpk[16][19][2]*s20)+(VWri[16][19][1]*c20)));
        Vpk[16][20][2] = (((rk[9][0]*Wpk[16][20][1])-(rk[9][1]*Wpk[16][19][0]))+
          ((Vpk[16][19][2]*c20)-(VWri[16][19][1]*s20)));
        Vpk[17][17][0] = -rk[7][2];
        Vpk[17][17][2] = rk[7][0];
        VWri[17][18][0] = (ri[8][2]-rk[7][2]);
        VWri[17][18][2] = (rk[7][0]-ri[8][0]);
        Vpk[17][18][0] = (((VWri[17][18][0]*c18)-(VWri[17][18][2]*s18))-rk[8][2]
          );
        Vpk[17][18][2] = (rk[8][0]+((VWri[17][18][0]*s18)+(VWri[17][18][2]*c18))
          );
        VWri[17][19][0] = (ri[9][2]+Vpk[17][18][0]);
        VWri[17][19][2] = (Vpk[17][18][2]-ri[9][0]);
        Vpk[17][19][0] = ((VWri[17][19][0]*c19)-(VWri[17][19][2]*s19));
        Vpk[17][19][2] = ((VWri[17][19][0]*s19)+(VWri[17][19][2]*c19));
        Vpk[17][20][0] = (Vpk[17][19][0]-((rk[9][1]*s20)+(rk[9][2]*c20)));
        Vpk[17][20][1] = ((rk[9][0]*s20)+(Vpk[17][19][2]*s20));
        Vpk[17][20][2] = ((rk[9][0]*c20)+(Vpk[17][19][2]*c20));
        Vpk[18][18][0] = -rk[8][2];
        Vpk[18][18][2] = rk[8][0];
        VWri[18][19][0] = (ri[9][2]-rk[8][2]);
        VWri[18][19][2] = (rk[8][0]-ri[9][0]);
        Vpk[18][19][0] = ((VWri[18][19][0]*c19)-(VWri[18][19][2]*s19));
        Vpk[18][19][2] = ((VWri[18][19][0]*s19)+(VWri[18][19][2]*c19));
        Vpk[18][20][0] = (Vpk[18][19][0]-((rk[9][1]*s20)+(rk[9][2]*c20)));
        Vpk[18][20][1] = ((rk[9][0]*s20)+(Vpk[18][19][2]*s20));
        Vpk[18][20][2] = ((rk[9][0]*c20)+(Vpk[18][19][2]*c20));
        Vpk[19][20][0] = -((rk[9][1]*s20)+(rk[9][2]*c20));
        Vpk[19][20][1] = (rk[9][0]*s20);
        Vpk[19][20][2] = (rk[9][0]*c20);
        Vpk[20][20][1] = rk[9][2];
        Vpk[20][20][2] = -rk[9][1];
        vpkflg = 1;
    }
/*
 Used 0.01 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  791 adds/subtracts/negates
                   1096 multiplies
                      0 divides
                    751 assignments
*/
}

void sddoltau(void)
{

/*
Compute effect of loop hinge torques
*/
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      0 assignments
*/
}

void sddoiner(void)
{

/*
Compute inertial accelerations and related temps
*/
    if (inerflg == 0) {
/*
Compute Otk (inertial angular acceleration)
*/
        Otk[4][0] = -(u[4]*wk[4][2]);
        Otk[4][2] = (u[4]*wk[4][0]);
        Otk[5][1] = ((Otk[4][2]*s5)+(u[5]*wk[5][2]));
        Otk[5][2] = ((Otk[4][2]*c5)-(u[5]*wk[5][1]));
        Otk[6][0] = ((u[6]*wk[6][1])+((Otk[4][0]*c6)+(Otk[5][1]*s6)));
        Otk[6][1] = (((Otk[5][1]*c6)-(Otk[4][0]*s6))-(u[6]*wk[6][0]));
        Otk[7][0] = (((Otk[6][0]*c7)-(Otk[5][2]*s7))-(u[7]*wk[7][2]));
        Otk[7][2] = ((u[7]*wk[7][0])+((Otk[5][2]*c7)+(Otk[6][0]*s7)));
        Otk[8][0] = (((Otk[6][0]*c8)-(Otk[5][2]*s8))-(u[8]*wk[8][2]));
        Otk[8][2] = ((u[8]*wk[8][0])+((Otk[5][2]*c8)+(Otk[6][0]*s8)));
        Otk[9][0] = ((u[9]*wk[9][1])+((Otk[4][0]*c9)+(Otk[5][1]*s9)));
        Otk[9][1] = (((Otk[5][1]*c9)-(Otk[4][0]*s9))-(u[9]*wk[9][0]));
        Otk[10][1] = ((u[10]*wk[10][2])+((Otk[5][2]*s10)+(Otk[9][1]*c10)));
        Otk[10][2] = (((Otk[5][2]*c10)-(Otk[9][1]*s10))-(u[10]*wk[10][1]));
        Otk[11][0] = (((Otk[9][0]*c11)-(Otk[10][2]*s11))-(u[11]*wk[11][2]));
        Otk[11][2] = ((u[11]*wk[11][0])+((Otk[9][0]*s11)+(Otk[10][2]*c11)));
        Otk[12][0] = (((Otk[11][0]*c12)-(Otk[11][2]*s12))-(u[12]*wk[12][2]));
        Otk[12][2] = ((u[12]*wk[12][0])+((Otk[11][0]*s12)+(Otk[11][2]*c12)));
        Otk[13][0] = (((Otk[12][0]*c13)-(Otk[12][2]*s13))-(u[13]*wk[13][2]));
        Otk[13][2] = ((u[13]*wk[13][0])+((Otk[12][0]*s13)+(Otk[12][2]*c13)));
        Otk[14][1] = ((u[14]*wk[14][2])+((Otk[10][1]*c14)+(Otk[13][2]*s14)));
        Otk[14][2] = (((Otk[13][2]*c14)-(Otk[10][1]*s14))-(u[14]*wk[14][1]));
        Otk[15][0] = ((u[15]*wk[15][1])+((Otk[4][0]*c15)+(Otk[5][1]*s15)));
        Otk[15][1] = (((Otk[5][1]*c15)-(Otk[4][0]*s15))-(u[15]*wk[15][0]));
        Otk[16][1] = ((u[16]*wk[16][2])+((Otk[5][2]*s16)+(Otk[15][1]*c16)));
        Otk[16][2] = (((Otk[5][2]*c16)-(Otk[15][1]*s16))-(u[16]*wk[16][1]));
        Otk[17][0] = (((Otk[15][0]*c17)-(Otk[16][2]*s17))-(u[17]*wk[17][2]));
        Otk[17][2] = ((u[17]*wk[17][0])+((Otk[15][0]*s17)+(Otk[16][2]*c17)));
        Otk[18][0] = (((Otk[17][0]*c18)-(Otk[17][2]*s18))-(u[18]*wk[18][2]));
        Otk[18][2] = ((u[18]*wk[18][0])+((Otk[17][0]*s18)+(Otk[17][2]*c18)));
        Otk[19][0] = (((Otk[18][0]*c19)-(Otk[18][2]*s19))-(u[19]*wk[19][2]));
        Otk[19][2] = ((u[19]*wk[19][0])+((Otk[18][0]*s19)+(Otk[18][2]*c19)));
        Otk[20][1] = ((u[20]*wk[20][2])+((Otk[16][1]*c20)+(Otk[19][2]*s20)));
        Otk[20][2] = (((Otk[19][2]*c20)-(Otk[16][1]*s20))-(u[20]*wk[20][1]));
/*
Compute Atk (inertial linear acceleration)
*/
        Atk[5][0] = (((Otk[5][2]*rk[0][1])-(Otk[5][1]*rk[0][2]))+((wk[5][1]*
          Wkrpk[5][2])-(wk[5][2]*Wkrpk[5][1])));
        Atk[5][1] = (((Otk[4][0]*rk[0][2])-(Otk[5][2]*rk[0][0]))+((wk[5][2]*
          Wkrpk[5][0])-(wk[5][0]*Wkrpk[5][2])));
        Atk[5][2] = (((Otk[5][1]*rk[0][0])-(Otk[4][0]*rk[0][1]))+((wk[5][0]*
          Wkrpk[5][1])-(wk[5][1]*Wkrpk[5][0])));
        AiOiWi[6][0] = (Atk[5][0]+(((Otk[5][1]*ri[1][2])-(Otk[5][2]*ri[1][1]))+(
          (Wirk[6][2]*wk[5][1])-(Wirk[6][1]*wk[5][2]))));
        AiOiWi[6][1] = (Atk[5][1]+(((Otk[5][2]*ri[1][0])-(Otk[4][0]*ri[1][2]))+(
          (Wirk[6][0]*wk[5][2])-(Wirk[6][2]*wk[5][0]))));
        AiOiWi[6][2] = (Atk[5][2]+(((Otk[4][0]*ri[1][1])-(Otk[5][1]*ri[1][0]))+(
          (Wirk[6][1]*wk[5][0])-(Wirk[6][0]*wk[5][1]))));
        Atk[6][0] = (((AiOiWi[6][0]*c6)+(AiOiWi[6][1]*s6))+(((Otk[5][2]*rk[1][1]
          )-(Otk[6][1]*rk[1][2]))+((wk[6][1]*Wkrpk[6][2])-(wk[6][2]*Wkrpk[6][1])
          )));
        Atk[6][1] = (((AiOiWi[6][1]*c6)-(AiOiWi[6][0]*s6))+(((Otk[6][0]*rk[1][2]
          )-(Otk[5][2]*rk[1][0]))+((wk[6][2]*Wkrpk[6][0])-(wk[6][0]*Wkrpk[6][2])
          )));
        Atk[6][2] = (AiOiWi[6][2]+(((Otk[6][1]*rk[1][0])-(Otk[6][0]*rk[1][1]))+(
          (wk[6][0]*Wkrpk[6][1])-(wk[6][1]*Wkrpk[6][0]))));
        AiOiWi[7][0] = (Atk[6][0]+(((Otk[6][1]*ri[2][2])-(Otk[5][2]*ri[2][1]))+(
          (Wirk[7][2]*wk[6][1])-(Wirk[7][1]*wk[6][2]))));
        AiOiWi[7][1] = (Atk[6][1]+(((Otk[5][2]*ri[2][0])-(Otk[6][0]*ri[2][2]))+(
          (Wirk[7][0]*wk[6][2])-(Wirk[7][2]*wk[6][0]))));
        AiOiWi[7][2] = (Atk[6][2]+(((Otk[6][0]*ri[2][1])-(Otk[6][1]*ri[2][0]))+(
          (Wirk[7][1]*wk[6][0])-(Wirk[7][0]*wk[6][1]))));
        Atk[7][0] = (((AiOiWi[7][0]*c7)-(AiOiWi[7][2]*s7))+(((Otk[7][2]*rk[2][1]
          )-(Otk[6][1]*rk[2][2]))+((wk[7][1]*Wkrpk[7][2])-(wk[7][2]*Wkrpk[7][1])
          )));
        Atk[7][1] = (AiOiWi[7][1]+(((Otk[7][0]*rk[2][2])-(Otk[7][2]*rk[2][0]))+(
          (wk[7][2]*Wkrpk[7][0])-(wk[7][0]*Wkrpk[7][2]))));
        Atk[7][2] = (((AiOiWi[7][0]*s7)+(AiOiWi[7][2]*c7))+(((Otk[6][1]*rk[2][0]
          )-(Otk[7][0]*rk[2][1]))+((wk[7][0]*Wkrpk[7][1])-(wk[7][1]*Wkrpk[7][0])
          )));
        AiOiWi[8][0] = (Atk[6][0]+(((Otk[6][1]*ri[3][2])-(Otk[5][2]*ri[3][1]))+(
          (Wirk[8][2]*wk[6][1])-(Wirk[8][1]*wk[6][2]))));
        AiOiWi[8][1] = (Atk[6][1]+(((Otk[5][2]*ri[3][0])-(Otk[6][0]*ri[3][2]))+(
          (Wirk[8][0]*wk[6][2])-(Wirk[8][2]*wk[6][0]))));
        AiOiWi[8][2] = (Atk[6][2]+(((Otk[6][0]*ri[3][1])-(Otk[6][1]*ri[3][0]))+(
          (Wirk[8][1]*wk[6][0])-(Wirk[8][0]*wk[6][1]))));
        Atk[8][0] = (((AiOiWi[8][0]*c8)-(AiOiWi[8][2]*s8))+(((Otk[8][2]*rk[3][1]
          )-(Otk[6][1]*rk[3][2]))+((wk[8][1]*Wkrpk[8][2])-(wk[8][2]*Wkrpk[8][1])
          )));
        Atk[8][1] = (AiOiWi[8][1]+(((Otk[8][0]*rk[3][2])-(Otk[8][2]*rk[3][0]))+(
          (wk[8][2]*Wkrpk[8][0])-(wk[8][0]*Wkrpk[8][2]))));
        Atk[8][2] = (((AiOiWi[8][0]*s8)+(AiOiWi[8][2]*c8))+(((Otk[6][1]*rk[3][0]
          )-(Otk[8][0]*rk[3][1]))+((wk[8][0]*Wkrpk[8][1])-(wk[8][1]*Wkrpk[8][0])
          )));
        AiOiWi[9][0] = (Atk[5][0]+(((Otk[5][1]*ri[4][2])-(Otk[5][2]*ri[4][1]))+(
          (Wirk[9][2]*wk[5][1])-(Wirk[9][1]*wk[5][2]))));
        AiOiWi[9][1] = (Atk[5][1]+(((Otk[5][2]*ri[4][0])-(Otk[4][0]*ri[4][2]))+(
          (Wirk[9][0]*wk[5][2])-(Wirk[9][2]*wk[5][0]))));
        AiOiWi[9][2] = (Atk[5][2]+(((Otk[4][0]*ri[4][1])-(Otk[5][1]*ri[4][0]))+(
          (Wirk[9][1]*wk[5][0])-(Wirk[9][0]*wk[5][1]))));
        Atk[9][0] = ((AiOiWi[9][0]*c9)+(AiOiWi[9][1]*s9));
        Atk[9][1] = ((AiOiWi[9][1]*c9)-(AiOiWi[9][0]*s9));
        Atk[10][1] = ((AiOiWi[9][2]*s10)+(Atk[9][1]*c10));
        Atk[10][2] = ((AiOiWi[9][2]*c10)-(Atk[9][1]*s10));
        Atk[11][0] = (((Atk[9][0]*c11)-(Atk[10][2]*s11))+(((Otk[11][2]*rk[4][1])
          -(Otk[10][1]*rk[4][2]))+((wk[11][1]*Wkrpk[11][2])-(wk[11][2]*
          Wkrpk[11][1]))));
        Atk[11][1] = (Atk[10][1]+(((Otk[11][0]*rk[4][2])-(Otk[11][2]*rk[4][0]))+
          ((wk[11][2]*Wkrpk[11][0])-(wk[11][0]*Wkrpk[11][2]))));
        Atk[11][2] = (((Atk[9][0]*s11)+(Atk[10][2]*c11))+(((Otk[10][1]*rk[4][0])
          -(Otk[11][0]*rk[4][1]))+((wk[11][0]*Wkrpk[11][1])-(wk[11][1]*
          Wkrpk[11][0]))));
        AiOiWi[12][0] = (Atk[11][0]+(((Otk[10][1]*ri[5][2])-(Otk[11][2]*ri[5][1]
          ))+((Wirk[12][2]*wk[11][1])-(Wirk[12][1]*wk[11][2]))));
        AiOiWi[12][1] = (Atk[11][1]+(((Otk[11][2]*ri[5][0])-(Otk[11][0]*ri[5][2]
          ))+((Wirk[12][0]*wk[11][2])-(Wirk[12][2]*wk[11][0]))));
        AiOiWi[12][2] = (Atk[11][2]+(((Otk[11][0]*ri[5][1])-(Otk[10][1]*ri[5][0]
          ))+((Wirk[12][1]*wk[11][0])-(Wirk[12][0]*wk[11][1]))));
        Atk[12][0] = (((AiOiWi[12][0]*c12)-(AiOiWi[12][2]*s12))+(((Otk[12][2]*
          rk[5][1])-(Otk[10][1]*rk[5][2]))+((wk[12][1]*Wkrpk[12][2])-(wk[12][2]*
          Wkrpk[12][1]))));
        Atk[12][1] = (AiOiWi[12][1]+(((Otk[12][0]*rk[5][2])-(Otk[12][2]*rk[5][0]
          ))+((wk[12][2]*Wkrpk[12][0])-(wk[12][0]*Wkrpk[12][2]))));
        Atk[12][2] = (((AiOiWi[12][0]*s12)+(AiOiWi[12][2]*c12))+(((Otk[10][1]*
          rk[5][0])-(Otk[12][0]*rk[5][1]))+((wk[12][0]*Wkrpk[12][1])-(wk[12][1]*
          Wkrpk[12][0]))));
        AiOiWi[13][0] = (Atk[12][0]+(((Otk[10][1]*ri[6][2])-(Otk[12][2]*ri[6][1]
          ))+((Wirk[13][2]*wk[12][1])-(Wirk[13][1]*wk[12][2]))));
        AiOiWi[13][1] = (Atk[12][1]+(((Otk[12][2]*ri[6][0])-(Otk[12][0]*ri[6][2]
          ))+((Wirk[13][0]*wk[12][2])-(Wirk[13][2]*wk[12][0]))));
        AiOiWi[13][2] = (Atk[12][2]+(((Otk[12][0]*ri[6][1])-(Otk[10][1]*ri[6][0]
          ))+((Wirk[13][1]*wk[12][0])-(Wirk[13][0]*wk[12][1]))));
        Atk[13][0] = ((AiOiWi[13][0]*c13)-(AiOiWi[13][2]*s13));
        Atk[13][2] = ((AiOiWi[13][0]*s13)+(AiOiWi[13][2]*c13));
        Atk[14][0] = (Atk[13][0]+(((Otk[14][2]*rk[6][1])-(Otk[14][1]*rk[6][2]))+
          ((wk[14][1]*Wkrpk[14][2])-(wk[14][2]*Wkrpk[14][1]))));
        Atk[14][1] = (((AiOiWi[13][1]*c14)+(Atk[13][2]*s14))+(((Otk[13][0]*
          rk[6][2])-(Otk[14][2]*rk[6][0]))+((wk[14][2]*Wkrpk[14][0])-(wk[14][0]*
          Wkrpk[14][2]))));
        Atk[14][2] = (((Atk[13][2]*c14)-(AiOiWi[13][1]*s14))+(((Otk[14][1]*
          rk[6][0])-(Otk[13][0]*rk[6][1]))+((wk[14][0]*Wkrpk[14][1])-(wk[14][1]*
          Wkrpk[14][0]))));
        AiOiWi[15][0] = (Atk[5][0]+(((Otk[5][1]*ri[7][2])-(Otk[5][2]*ri[7][1]))+
          ((Wirk[15][2]*wk[5][1])-(Wirk[15][1]*wk[5][2]))));
        AiOiWi[15][1] = (Atk[5][1]+(((Otk[5][2]*ri[7][0])-(Otk[4][0]*ri[7][2]))+
          ((Wirk[15][0]*wk[5][2])-(Wirk[15][2]*wk[5][0]))));
        AiOiWi[15][2] = (Atk[5][2]+(((Otk[4][0]*ri[7][1])-(Otk[5][1]*ri[7][0]))+
          ((Wirk[15][1]*wk[5][0])-(Wirk[15][0]*wk[5][1]))));
        Atk[15][0] = ((AiOiWi[15][0]*c15)+(AiOiWi[15][1]*s15));
        Atk[15][1] = ((AiOiWi[15][1]*c15)-(AiOiWi[15][0]*s15));
        Atk[16][1] = ((AiOiWi[15][2]*s16)+(Atk[15][1]*c16));
        Atk[16][2] = ((AiOiWi[15][2]*c16)-(Atk[15][1]*s16));
        Atk[17][0] = (((Atk[15][0]*c17)-(Atk[16][2]*s17))+(((Otk[17][2]*rk[7][1]
          )-(Otk[16][1]*rk[7][2]))+((wk[17][1]*Wkrpk[17][2])-(wk[17][2]*
          Wkrpk[17][1]))));
        Atk[17][1] = (Atk[16][1]+(((Otk[17][0]*rk[7][2])-(Otk[17][2]*rk[7][0]))+
          ((wk[17][2]*Wkrpk[17][0])-(wk[17][0]*Wkrpk[17][2]))));
        Atk[17][2] = (((Atk[15][0]*s17)+(Atk[16][2]*c17))+(((Otk[16][1]*rk[7][0]
          )-(Otk[17][0]*rk[7][1]))+((wk[17][0]*Wkrpk[17][1])-(wk[17][1]*
          Wkrpk[17][0]))));
        AiOiWi[18][0] = (Atk[17][0]+(((Otk[16][1]*ri[8][2])-(Otk[17][2]*ri[8][1]
          ))+((Wirk[18][2]*wk[17][1])-(Wirk[18][1]*wk[17][2]))));
        AiOiWi[18][1] = (Atk[17][1]+(((Otk[17][2]*ri[8][0])-(Otk[17][0]*ri[8][2]
          ))+((Wirk[18][0]*wk[17][2])-(Wirk[18][2]*wk[17][0]))));
        AiOiWi[18][2] = (Atk[17][2]+(((Otk[17][0]*ri[8][1])-(Otk[16][1]*ri[8][0]
          ))+((Wirk[18][1]*wk[17][0])-(Wirk[18][0]*wk[17][1]))));
        Atk[18][0] = (((AiOiWi[18][0]*c18)-(AiOiWi[18][2]*s18))+(((Otk[18][2]*
          rk[8][1])-(Otk[16][1]*rk[8][2]))+((wk[18][1]*Wkrpk[18][2])-(wk[18][2]*
          Wkrpk[18][1]))));
        Atk[18][1] = (AiOiWi[18][1]+(((Otk[18][0]*rk[8][2])-(Otk[18][2]*rk[8][0]
          ))+((wk[18][2]*Wkrpk[18][0])-(wk[18][0]*Wkrpk[18][2]))));
        Atk[18][2] = (((AiOiWi[18][0]*s18)+(AiOiWi[18][2]*c18))+(((Otk[16][1]*
          rk[8][0])-(Otk[18][0]*rk[8][1]))+((wk[18][0]*Wkrpk[18][1])-(wk[18][1]*
          Wkrpk[18][0]))));
        AiOiWi[19][0] = (Atk[18][0]+(((Otk[16][1]*ri[9][2])-(Otk[18][2]*ri[9][1]
          ))+((Wirk[19][2]*wk[18][1])-(Wirk[19][1]*wk[18][2]))));
        AiOiWi[19][1] = (Atk[18][1]+(((Otk[18][2]*ri[9][0])-(Otk[18][0]*ri[9][2]
          ))+((Wirk[19][0]*wk[18][2])-(Wirk[19][2]*wk[18][0]))));
        AiOiWi[19][2] = (Atk[18][2]+(((Otk[18][0]*ri[9][1])-(Otk[16][1]*ri[9][0]
          ))+((Wirk[19][1]*wk[18][0])-(Wirk[19][0]*wk[18][1]))));
        Atk[19][0] = ((AiOiWi[19][0]*c19)-(AiOiWi[19][2]*s19));
        Atk[19][2] = ((AiOiWi[19][0]*s19)+(AiOiWi[19][2]*c19));
        Atk[20][0] = (Atk[19][0]+(((Otk[20][2]*rk[9][1])-(Otk[20][1]*rk[9][2]))+
          ((wk[20][1]*Wkrpk[20][2])-(wk[20][2]*Wkrpk[20][1]))));
        Atk[20][1] = (((AiOiWi[19][1]*c20)+(Atk[19][2]*s20))+(((Otk[19][0]*
          rk[9][2])-(Otk[20][2]*rk[9][0]))+((wk[20][2]*Wkrpk[20][0])-(wk[20][0]*
          Wkrpk[20][2]))));
        Atk[20][2] = (((Atk[19][2]*c20)-(AiOiWi[19][1]*s20))+(((Otk[20][1]*
          rk[9][0])-(Otk[19][0]*rk[9][1]))+((wk[20][0]*Wkrpk[20][1])-(wk[20][1]*
          Wkrpk[20][0]))));
        inerflg = 1;
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  318 adds/subtracts/negates
                    384 multiplies
                      0 divides
                    103 assignments
*/
}

void sddofs0(void)
{

/*
Compute effect of all applied loads
*/
    if (fs0flg == 0) {
        sddoltau();
        sddoiner();
/*
Compute Fstar (forces)
*/
        Fstar[5][0] = ((mk[0]*(Atk[5][0]-(9.8*s4)))-ufk[0][0]);
        Fstar[5][1] = ((mk[0]*(Atk[5][1]-gk[5][1]))-ufk[0][1]);
        Fstar[5][2] = ((mk[0]*(Atk[5][2]-gk[5][2]))-ufk[0][2]);
        Fstar[6][0] = ((mk[1]*(Atk[6][0]-gk[6][0]))-ufk[1][0]);
        Fstar[6][1] = ((mk[1]*(Atk[6][1]-gk[6][1]))-ufk[1][1]);
        Fstar[6][2] = ((mk[1]*(Atk[6][2]-gk[5][2]))-ufk[1][2]);
        Fstar[7][0] = ((mk[2]*(Atk[7][0]-gk[7][0]))-ufk[2][0]);
        Fstar[7][1] = ((mk[2]*(Atk[7][1]-gk[6][1]))-ufk[2][1]);
        Fstar[7][2] = ((mk[2]*(Atk[7][2]-gk[7][2]))-ufk[2][2]);
        Fstar[8][0] = ((mk[3]*(Atk[8][0]-gk[8][0]))-ufk[3][0]);
        Fstar[8][1] = ((mk[3]*(Atk[8][1]-gk[6][1]))-ufk[3][1]);
        Fstar[8][2] = ((mk[3]*(Atk[8][2]-gk[8][2]))-ufk[3][2]);
        Fstar[11][0] = ((mk[4]*(Atk[11][0]-gk[11][0]))-ufk[4][0]);
        Fstar[11][1] = ((mk[4]*(Atk[11][1]-gk[10][1]))-ufk[4][1]);
        Fstar[11][2] = ((mk[4]*(Atk[11][2]-gk[11][2]))-ufk[4][2]);
        Fstar[12][0] = ((mk[5]*(Atk[12][0]-gk[12][0]))-ufk[5][0]);
        Fstar[12][1] = ((mk[5]*(Atk[12][1]-gk[10][1]))-ufk[5][1]);
        Fstar[12][2] = ((mk[5]*(Atk[12][2]-gk[12][2]))-ufk[5][2]);
        Fstar[14][0] = ((mk[6]*(Atk[14][0]-gk[13][0]))-ufk[6][0]);
        Fstar[14][1] = ((mk[6]*(Atk[14][1]-gk[14][1]))-ufk[6][1]);
        Fstar[14][2] = ((mk[6]*(Atk[14][2]-gk[14][2]))-ufk[6][2]);
        Fstar[17][0] = ((mk[7]*(Atk[17][0]-gk[17][0]))-ufk[7][0]);
        Fstar[17][1] = ((mk[7]*(Atk[17][1]-gk[16][1]))-ufk[7][1]);
        Fstar[17][2] = ((mk[7]*(Atk[17][2]-gk[17][2]))-ufk[7][2]);
        Fstar[18][0] = ((mk[8]*(Atk[18][0]-gk[18][0]))-ufk[8][0]);
        Fstar[18][1] = ((mk[8]*(Atk[18][1]-gk[16][1]))-ufk[8][1]);
        Fstar[18][2] = ((mk[8]*(Atk[18][2]-gk[18][2]))-ufk[8][2]);
        Fstar[20][0] = ((mk[9]*(Atk[20][0]-gk[19][0]))-ufk[9][0]);
        Fstar[20][1] = ((mk[9]*(Atk[20][1]-gk[20][1]))-ufk[9][1]);
        Fstar[20][2] = ((mk[9]*(Atk[20][2]-gk[20][2]))-ufk[9][2]);
/*
Compute Tstar (torques)
*/
        Tstar[5][0] = ((WkIkWk[5][0]+(ik[0][0][0]*Otk[4][0]))-utk[0][0]);
        Tstar[5][1] = ((WkIkWk[5][1]+(ik[0][1][1]*Otk[5][1]))-utk[0][1]);
        Tstar[5][2] = ((WkIkWk[5][2]+(ik[0][2][2]*Otk[5][2]))-utk[0][2]);
        Tstar[6][0] = ((WkIkWk[6][0]+(ik[1][0][0]*Otk[6][0]))-utk[1][0]);
        Tstar[6][1] = ((WkIkWk[6][1]+(ik[1][1][1]*Otk[6][1]))-utk[1][1]);
        Tstar[6][2] = ((WkIkWk[6][2]+(ik[1][2][2]*Otk[5][2]))-utk[1][2]);
        Tstar[7][0] = ((WkIkWk[7][0]+(ik[2][0][0]*Otk[7][0]))-utk[2][0]);
        Tstar[7][1] = ((WkIkWk[7][1]+(ik[2][1][1]*Otk[6][1]))-utk[2][1]);
        Tstar[7][2] = ((WkIkWk[7][2]+(ik[2][2][2]*Otk[7][2]))-utk[2][2]);
        Tstar[8][0] = ((WkIkWk[8][0]+(ik[3][0][0]*Otk[8][0]))-utk[3][0]);
        Tstar[8][1] = ((WkIkWk[8][1]+(ik[3][1][1]*Otk[6][1]))-utk[3][1]);
        Tstar[8][2] = ((WkIkWk[8][2]+(ik[3][2][2]*Otk[8][2]))-utk[3][2]);
        Tstar[11][0] = ((WkIkWk[11][0]+(ik[4][0][0]*Otk[11][0]))-utk[4][0]);
        Tstar[11][1] = ((WkIkWk[11][1]+(ik[4][1][1]*Otk[10][1]))-utk[4][1]);
        Tstar[11][2] = ((WkIkWk[11][2]+(ik[4][2][2]*Otk[11][2]))-utk[4][2]);
        Tstar[12][0] = ((WkIkWk[12][0]+(ik[5][0][0]*Otk[12][0]))-utk[5][0]);
        Tstar[12][1] = ((WkIkWk[12][1]+(ik[5][1][1]*Otk[10][1]))-utk[5][1]);
        Tstar[12][2] = ((WkIkWk[12][2]+(ik[5][2][2]*Otk[12][2]))-utk[5][2]);
        Tstar[14][0] = ((WkIkWk[14][0]+(ik[6][0][0]*Otk[13][0]))-utk[6][0]);
        Tstar[14][1] = ((WkIkWk[14][1]+(ik[6][1][1]*Otk[14][1]))-utk[6][1]);
        Tstar[14][2] = ((WkIkWk[14][2]+(ik[6][2][2]*Otk[14][2]))-utk[6][2]);
        Tstar[17][0] = ((WkIkWk[17][0]+(ik[7][0][0]*Otk[17][0]))-utk[7][0]);
        Tstar[17][1] = ((WkIkWk[17][1]+(ik[7][1][1]*Otk[16][1]))-utk[7][1]);
        Tstar[17][2] = ((WkIkWk[17][2]+(ik[7][2][2]*Otk[17][2]))-utk[7][2]);
        Tstar[18][0] = ((WkIkWk[18][0]+(ik[8][0][0]*Otk[18][0]))-utk[8][0]);
        Tstar[18][1] = ((WkIkWk[18][1]+(ik[8][1][1]*Otk[16][1]))-utk[8][1]);
        Tstar[18][2] = ((WkIkWk[18][2]+(ik[8][2][2]*Otk[18][2]))-utk[8][2]);
        Tstar[20][0] = ((WkIkWk[20][0]+(ik[9][0][0]*Otk[19][0]))-utk[9][0]);
        Tstar[20][1] = ((WkIkWk[20][1]+(ik[9][1][1]*Otk[20][1]))-utk[9][1]);
        Tstar[20][2] = ((WkIkWk[20][2]+(ik[9][2][2]*Otk[20][2]))-utk[9][2]);
/*
Compute fs0 (RHS ignoring constraints)
*/
        sddovpk();
        temp[0] = (((Fstar[8][2]*Vpk[0][8][2])+((Fstar[8][0]*Vpk[0][8][0])+(
          Fstar[8][1]*Vpk[0][6][1])))+(((Fstar[7][2]*Vpk[0][7][2])+((Fstar[7][0]
          *Vpk[0][7][0])+(Fstar[7][1]*Vpk[0][6][1])))+(((Fstar[5][2]*
          Vpk[0][5][2])+((Fstar[5][1]*Vpk[0][5][1])-(Fstar[5][0]*s4)))+((
          Fstar[6][2]*Vpk[0][5][2])+((Fstar[6][0]*Vpk[0][6][0])+(Fstar[6][1]*
          Vpk[0][6][1]))))));
        temp[1] = (((Fstar[17][2]*Vpk[0][17][2])+((Fstar[17][0]*Vpk[0][17][0])+(
          Fstar[17][1]*Vpk[0][16][1])))+(((Fstar[14][2]*Vpk[0][14][2])+((
          Fstar[14][0]*Vpk[0][13][0])+(Fstar[14][1]*Vpk[0][14][1])))+(((
          Fstar[12][2]*Vpk[0][12][2])+((Fstar[12][0]*Vpk[0][12][0])+(
          Fstar[12][1]*Vpk[0][10][1])))+(((Fstar[11][2]*Vpk[0][11][2])+((
          Fstar[11][0]*Vpk[0][11][0])+(Fstar[11][1]*Vpk[0][10][1])))+temp[0]))))
          ;
        fs0[0] = (utau[0]-(((Fstar[20][2]*Vpk[0][20][2])+((Fstar[20][0]*
          Vpk[0][19][0])+(Fstar[20][1]*Vpk[0][20][1])))+(((Fstar[18][2]*
          Vpk[0][18][2])+((Fstar[18][0]*Vpk[0][18][0])+(Fstar[18][1]*
          Vpk[0][16][1])))+temp[1])));
        temp[0] = (((Fstar[8][2]*Vpk[1][8][2])+((Fstar[8][0]*Vpk[1][8][0])+(
          Fstar[8][1]*Vpk[1][6][1])))+(((Fstar[7][2]*Vpk[1][7][2])+((Fstar[7][0]
          *Vpk[1][7][0])+(Fstar[7][1]*Vpk[1][6][1])))+(((Fstar[5][2]*
          Vpk[1][5][2])+((Fstar[5][0]*Vpk[1][4][0])+(Fstar[5][1]*Vpk[1][5][1])))
          +((Fstar[6][2]*Vpk[1][5][2])+((Fstar[6][0]*Vpk[1][6][0])+(Fstar[6][1]*
          Vpk[1][6][1]))))));
        temp[1] = (((Fstar[17][2]*Vpk[1][17][2])+((Fstar[17][0]*Vpk[1][17][0])+(
          Fstar[17][1]*Vpk[1][16][1])))+(((Fstar[14][2]*Vpk[1][14][2])+((
          Fstar[14][0]*Vpk[1][13][0])+(Fstar[14][1]*Vpk[1][14][1])))+(((
          Fstar[12][2]*Vpk[1][12][2])+((Fstar[12][0]*Vpk[1][12][0])+(
          Fstar[12][1]*Vpk[1][10][1])))+(((Fstar[11][2]*Vpk[1][11][2])+((
          Fstar[11][0]*Vpk[1][11][0])+(Fstar[11][1]*Vpk[1][10][1])))+temp[0]))))
          ;
        fs0[1] = (utau[1]-(((Fstar[20][2]*Vpk[1][20][2])+((Fstar[20][0]*
          Vpk[1][19][0])+(Fstar[20][1]*Vpk[1][20][1])))+(((Fstar[18][2]*
          Vpk[1][18][2])+((Fstar[18][0]*Vpk[1][18][0])+(Fstar[18][1]*
          Vpk[1][16][1])))+temp[1])));
        temp[0] = (((Fstar[8][2]*Vpk[2][8][2])+((Fstar[8][0]*Vpk[2][8][0])+(
          Fstar[8][1]*Vpk[2][6][1])))+(((Fstar[7][2]*Vpk[2][7][2])+((Fstar[7][0]
          *Vpk[2][7][0])+(Fstar[7][1]*Vpk[2][6][1])))+(((Fstar[5][2]*
          Vpk[2][5][2])+((Fstar[5][0]*Vpk[2][4][0])+(Fstar[5][1]*Vpk[2][5][1])))
          +((Fstar[6][2]*Vpk[2][5][2])+((Fstar[6][0]*Vpk[2][6][0])+(Fstar[6][1]*
          Vpk[2][6][1]))))));
        temp[1] = (((Fstar[17][2]*Vpk[2][17][2])+((Fstar[17][0]*Vpk[2][17][0])+(
          Fstar[17][1]*Vpk[2][16][1])))+(((Fstar[14][2]*Vpk[2][14][2])+((
          Fstar[14][0]*Vpk[2][13][0])+(Fstar[14][1]*Vpk[2][14][1])))+(((
          Fstar[12][2]*Vpk[2][12][2])+((Fstar[12][0]*Vpk[2][12][0])+(
          Fstar[12][1]*Vpk[2][10][1])))+(((Fstar[11][2]*Vpk[2][11][2])+((
          Fstar[11][0]*Vpk[2][11][0])+(Fstar[11][1]*Vpk[2][10][1])))+temp[0]))))
          ;
        fs0[2] = (utau[2]-(((Fstar[20][2]*Vpk[2][20][2])+((Fstar[20][0]*
          Vpk[2][19][0])+(Fstar[20][1]*Vpk[2][20][1])))+(((Fstar[18][2]*
          Vpk[2][18][2])+((Fstar[18][0]*Vpk[2][18][0])+(Fstar[18][1]*
          Vpk[2][16][1])))+temp[1])));
        temp[0] = ((((Fstar[5][2]*Vpk[3][5][2])+((Fstar[5][0]*Vpk[3][5][0])+(
          Fstar[5][1]*Vpk[3][5][1])))+((Tstar[5][2]*Wpk[3][5][2])+((Tstar[5][1]*
          Wpk[3][5][1])-(Tstar[5][0]*s4))))+(((Fstar[6][2]*Vpk[3][6][2])+((
          Fstar[6][0]*Vpk[3][6][0])+(Fstar[6][1]*Vpk[3][6][1])))+((Tstar[6][2]*
          Wpk[3][5][2])+((Tstar[6][0]*Wpk[3][6][0])+(Tstar[6][1]*Wpk[3][6][1])))
          ));
        temp[1] = ((((Fstar[8][2]*Vpk[3][8][2])+((Fstar[8][0]*Vpk[3][8][0])+(
          Fstar[8][1]*Vpk[3][8][1])))+((Tstar[8][2]*Wpk[3][8][2])+((Tstar[8][0]*
          Wpk[3][8][0])+(Tstar[8][1]*Wpk[3][6][1]))))+((((Fstar[7][2]*
          Vpk[3][7][2])+((Fstar[7][0]*Vpk[3][7][0])+(Fstar[7][1]*Vpk[3][7][1])))
          +((Tstar[7][2]*Wpk[3][7][2])+((Tstar[7][0]*Wpk[3][7][0])+(Tstar[7][1]*
          Wpk[3][6][1]))))+temp[0]));
        temp[2] = ((((Fstar[12][2]*Vpk[3][12][2])+((Fstar[12][0]*Vpk[3][12][0])+
          (Fstar[12][1]*Vpk[3][12][1])))+((Tstar[12][2]*Wpk[3][12][2])+((
          Tstar[12][0]*Wpk[3][12][0])+(Tstar[12][1]*Wpk[3][10][1]))))+((((
          Fstar[11][2]*Vpk[3][11][2])+((Fstar[11][0]*Vpk[3][11][0])+(
          Fstar[11][1]*Vpk[3][11][1])))+((Tstar[11][2]*Wpk[3][11][2])+((
          Tstar[11][0]*Wpk[3][11][0])+(Tstar[11][1]*Wpk[3][10][1]))))+temp[1]));
        temp[3] = ((((Fstar[17][2]*Vpk[3][17][2])+((Fstar[17][0]*Vpk[3][17][0])+
          (Fstar[17][1]*Vpk[3][17][1])))+((Tstar[17][2]*Wpk[3][17][2])+((
          Tstar[17][0]*Wpk[3][17][0])+(Tstar[17][1]*Wpk[3][16][1]))))+((((
          Fstar[14][2]*Vpk[3][14][2])+((Fstar[14][0]*Vpk[3][14][0])+(
          Fstar[14][1]*Vpk[3][14][1])))+((Tstar[14][2]*Wpk[3][14][2])+((
          Tstar[14][0]*Wpk[3][13][0])+(Tstar[14][1]*Wpk[3][14][1]))))+temp[2]));
        fs0[3] = (utau[3]-((((Fstar[20][2]*Vpk[3][20][2])+((Fstar[20][0]*
          Vpk[3][20][0])+(Fstar[20][1]*Vpk[3][20][1])))+((Tstar[20][2]*
          Wpk[3][20][2])+((Tstar[20][0]*Wpk[3][19][0])+(Tstar[20][1]*
          Wpk[3][20][1]))))+((((Fstar[18][2]*Vpk[3][18][2])+((Fstar[18][0]*
          Vpk[3][18][0])+(Fstar[18][1]*Vpk[3][18][1])))+((Tstar[18][2]*
          Wpk[3][18][2])+((Tstar[18][0]*Wpk[3][18][0])+(Tstar[18][1]*
          Wpk[3][16][1]))))+temp[3])));
        temp[0] = ((((Fstar[5][2]*Vpk[4][5][2])+((Fstar[5][0]*Vpk[4][5][0])+(
          Fstar[5][1]*Vpk[4][5][1])))+((Tstar[5][1]*c5)-(Tstar[5][2]*s5)))+(((
          Fstar[6][2]*Vpk[4][6][2])+((Fstar[6][0]*Vpk[4][6][0])+(Fstar[6][1]*
          Vpk[4][6][1])))+(((Tstar[6][0]*Wpk[4][6][0])+(Tstar[6][1]*Wpk[4][6][1]
          ))-(Tstar[6][2]*s5))));
        temp[1] = ((((Fstar[8][2]*Vpk[4][8][2])+((Fstar[8][0]*Vpk[4][8][0])+(
          Fstar[8][1]*Vpk[4][8][1])))+((Tstar[8][2]*Wpk[4][8][2])+((Tstar[8][0]*
          Wpk[4][8][0])+(Tstar[8][1]*Wpk[4][6][1]))))+((((Fstar[7][2]*
          Vpk[4][7][2])+((Fstar[7][0]*Vpk[4][7][0])+(Fstar[7][1]*Vpk[4][7][1])))
          +((Tstar[7][2]*Wpk[4][7][2])+((Tstar[7][0]*Wpk[4][7][0])+(Tstar[7][1]*
          Wpk[4][6][1]))))+temp[0]));
        temp[2] = ((((Fstar[12][2]*Vpk[4][12][2])+((Fstar[12][0]*Vpk[4][12][0])+
          (Fstar[12][1]*Vpk[4][12][1])))+((Tstar[12][2]*Wpk[4][12][2])+((
          Tstar[12][0]*Wpk[4][12][0])+(Tstar[12][1]*Wpk[4][10][1]))))+((((
          Fstar[11][2]*Vpk[4][11][2])+((Fstar[11][0]*Vpk[4][11][0])+(
          Fstar[11][1]*Vpk[4][11][1])))+((Tstar[11][2]*Wpk[4][11][2])+((
          Tstar[11][0]*Wpk[4][11][0])+(Tstar[11][1]*Wpk[4][10][1]))))+temp[1]));
        temp[3] = ((((Fstar[17][2]*Vpk[4][17][2])+((Fstar[17][0]*Vpk[4][17][0])+
          (Fstar[17][1]*Vpk[4][17][1])))+((Tstar[17][2]*Wpk[4][17][2])+((
          Tstar[17][0]*Wpk[4][17][0])+(Tstar[17][1]*Wpk[4][16][1]))))+((((
          Fstar[14][2]*Vpk[4][14][2])+((Fstar[14][0]*Vpk[4][14][0])+(
          Fstar[14][1]*Vpk[4][14][1])))+((Tstar[14][2]*Wpk[4][14][2])+((
          Tstar[14][0]*Wpk[4][13][0])+(Tstar[14][1]*Wpk[4][14][1]))))+temp[2]));
        fs0[4] = (utau[4]-((((Fstar[20][2]*Vpk[4][20][2])+((Fstar[20][0]*
          Vpk[4][20][0])+(Fstar[20][1]*Vpk[4][20][1])))+((Tstar[20][2]*
          Wpk[4][20][2])+((Tstar[20][0]*Wpk[4][19][0])+(Tstar[20][1]*
          Wpk[4][20][1]))))+((((Fstar[18][2]*Vpk[4][18][2])+((Fstar[18][0]*
          Vpk[4][18][0])+(Fstar[18][1]*Vpk[4][18][1])))+((Tstar[18][2]*
          Wpk[4][18][2])+((Tstar[18][0]*Wpk[4][18][0])+(Tstar[18][1]*
          Wpk[4][16][1]))))+temp[3])));
        temp[0] = (((Tstar[5][0]+((Fstar[5][1]*rk[0][2])-(Fstar[5][2]*rk[0][1]))
          )+(((Fstar[6][2]*Vpk[5][6][2])+((Fstar[6][0]*Vpk[5][6][0])+(
          Fstar[6][1]*Vpk[5][6][1])))+((Tstar[6][0]*c6)-(Tstar[6][1]*s6))))+(((
          Fstar[7][2]*Vpk[5][7][2])+((Fstar[7][0]*Vpk[5][7][0])+(Fstar[7][1]*
          Vpk[5][7][1])))+((Tstar[7][2]*Wpk[5][7][2])+((Tstar[7][0]*Wpk[5][7][0]
          )-(Tstar[7][1]*s6)))));
        temp[1] = ((((Fstar[11][2]*Vpk[5][11][2])+((Fstar[11][0]*Vpk[5][11][0])+
          (Fstar[11][1]*Vpk[5][11][1])))+((Tstar[11][2]*Wpk[5][11][2])+((
          Tstar[11][0]*Wpk[5][11][0])+(Tstar[11][1]*Wpk[5][10][1]))))+((((
          Fstar[8][2]*Vpk[5][8][2])+((Fstar[8][0]*Vpk[5][8][0])+(Fstar[8][1]*
          Vpk[5][8][1])))+((Tstar[8][2]*Wpk[5][8][2])+((Tstar[8][0]*Wpk[5][8][0]
          )-(Tstar[8][1]*s6))))+temp[0]));
        temp[2] = ((((Fstar[14][2]*Vpk[5][14][2])+((Fstar[14][0]*Vpk[5][14][0])+
          (Fstar[14][1]*Vpk[5][14][1])))+((Tstar[14][2]*Wpk[5][14][2])+((
          Tstar[14][0]*Wpk[5][13][0])+(Tstar[14][1]*Wpk[5][14][1]))))+((((
          Fstar[12][2]*Vpk[5][12][2])+((Fstar[12][0]*Vpk[5][12][0])+(
          Fstar[12][1]*Vpk[5][12][1])))+((Tstar[12][2]*Wpk[5][12][2])+((
          Tstar[12][0]*Wpk[5][12][0])+(Tstar[12][1]*Wpk[5][10][1]))))+temp[1]));
        temp[3] = ((((Fstar[18][2]*Vpk[5][18][2])+((Fstar[18][0]*Vpk[5][18][0])+
          (Fstar[18][1]*Vpk[5][18][1])))+((Tstar[18][2]*Wpk[5][18][2])+((
          Tstar[18][0]*Wpk[5][18][0])+(Tstar[18][1]*Wpk[5][16][1]))))+((((
          Fstar[17][2]*Vpk[5][17][2])+((Fstar[17][0]*Vpk[5][17][0])+(
          Fstar[17][1]*Vpk[5][17][1])))+((Tstar[17][2]*Wpk[5][17][2])+((
          Tstar[17][0]*Wpk[5][17][0])+(Tstar[17][1]*Wpk[5][16][1]))))+temp[2]));
        fs0[5] = (utau[5]-((((Fstar[20][2]*Vpk[5][20][2])+((Fstar[20][0]*
          Vpk[5][20][0])+(Fstar[20][1]*Vpk[5][20][1])))+((Tstar[20][2]*
          Wpk[5][20][2])+((Tstar[20][0]*Wpk[5][19][0])+(Tstar[20][1]*
          Wpk[5][20][1]))))+temp[3]));
        fs0[6] = (utau[6]-(((Tstar[6][2]+((Fstar[6][0]*rk[1][1])-(Fstar[6][1]*
          rk[1][0])))+(((Fstar[7][2]*Vpk[6][7][2])+((Fstar[7][0]*Vpk[6][7][0])+(
          Fstar[7][1]*Vpk[6][7][1])))+((Tstar[7][2]*c7)-(Tstar[7][0]*s7))))+(((
          Fstar[8][2]*Vpk[6][8][2])+((Fstar[8][0]*Vpk[6][8][0])+(Fstar[8][1]*
          Vpk[6][8][1])))+((Tstar[8][2]*c8)-(Tstar[8][0]*s8)))));
        fs0[7] = (utau[7]-(Tstar[7][1]+((Fstar[7][2]*rk[2][0])-(Fstar[7][0]*
          rk[2][2]))));
        fs0[8] = (utau[8]-(Tstar[8][1]+((Fstar[8][2]*rk[3][0])-(Fstar[8][0]*
          rk[3][2]))));
        temp[0] = ((((Fstar[11][2]*Vpk[9][11][2])+((Fstar[11][0]*Vpk[9][11][0])+
          (Fstar[11][1]*Vpk[9][11][1])))+((Tstar[11][2]*Wpk[9][11][2])+((
          Tstar[11][0]*Wpk[9][11][0])+(Tstar[11][1]*s10))))+(((Fstar[12][2]*
          Vpk[9][12][2])+((Fstar[12][0]*Vpk[9][12][0])+(Fstar[12][1]*
          Vpk[9][12][1])))+((Tstar[12][2]*Wpk[9][12][2])+((Tstar[12][0]*
          Wpk[9][12][0])+(Tstar[12][1]*s10)))));
        fs0[9] = (utau[9]-((((Fstar[14][2]*Vpk[9][14][2])+((Fstar[14][0]*
          Vpk[9][14][0])+(Fstar[14][1]*Vpk[9][14][1])))+((Tstar[14][2]*
          Wpk[9][14][2])+((Tstar[14][0]*Wpk[9][13][0])+(Tstar[14][1]*
          Wpk[9][14][1]))))+temp[0]));
        temp[0] = ((((Fstar[11][2]*Vpk[10][11][2])+((Fstar[11][0]*Vpk[10][11][0]
          )+(Fstar[11][1]*Vpk[10][11][1])))+((Tstar[11][0]*c11)+(Tstar[11][2]*
          s11)))+(((Fstar[12][2]*Vpk[10][12][2])+((Fstar[12][0]*Vpk[10][12][0])+
          (Fstar[12][1]*Vpk[10][12][1])))+((Tstar[12][0]*Wpk[10][12][0])+(
          Tstar[12][2]*Wpk[10][12][2]))));
        fs0[10] = (utau[10]-((((Fstar[14][2]*Vpk[10][14][2])+((Fstar[14][0]*
          Vpk[10][14][0])+(Fstar[14][1]*Vpk[10][14][1])))+((Tstar[14][2]*
          Wpk[10][14][2])+((Tstar[14][0]*Wpk[10][13][0])+(Tstar[14][1]*
          Wpk[10][14][1]))))+temp[0]));
        fs0[11] = (utau[11]-(((Tstar[11][1]+((Fstar[11][2]*rk[4][0])-(
          Fstar[11][0]*rk[4][2])))+(Tstar[12][1]+((Fstar[12][0]*Vpk[11][12][0])+
          (Fstar[12][2]*Vpk[11][12][2]))))+(((Fstar[14][2]*Vpk[11][14][2])+((
          Fstar[14][0]*Vpk[11][14][0])+(Fstar[14][1]*Vpk[11][14][1])))+((
          Tstar[14][1]*c14)-(Tstar[14][2]*s14)))));
        fs0[12] = (utau[12]-((Tstar[12][1]+((Fstar[12][2]*rk[5][0])-(
          Fstar[12][0]*rk[5][2])))+(((Fstar[14][2]*Vpk[12][14][2])+((
          Fstar[14][0]*Vpk[12][14][0])+(Fstar[14][1]*Vpk[12][14][1])))+((
          Tstar[14][1]*c14)-(Tstar[14][2]*s14)))));
        fs0[13] = (utau[13]-(((Fstar[14][2]*Vpk[13][14][2])+((Fstar[14][0]*
          Vpk[13][14][0])+(Fstar[14][1]*Vpk[13][14][1])))+((Tstar[14][1]*c14)-(
          Tstar[14][2]*s14))));
        fs0[14] = (utau[14]-(Tstar[14][0]+((Fstar[14][1]*rk[6][2])-(Fstar[14][2]
          *rk[6][1]))));
        temp[0] = ((((Fstar[17][2]*Vpk[15][17][2])+((Fstar[17][0]*Vpk[15][17][0]
          )+(Fstar[17][1]*Vpk[15][17][1])))+((Tstar[17][2]*Wpk[15][17][2])+((
          Tstar[17][0]*Wpk[15][17][0])+(Tstar[17][1]*s16))))+(((Fstar[18][2]*
          Vpk[15][18][2])+((Fstar[18][0]*Vpk[15][18][0])+(Fstar[18][1]*
          Vpk[15][18][1])))+((Tstar[18][2]*Wpk[15][18][2])+((Tstar[18][0]*
          Wpk[15][18][0])+(Tstar[18][1]*s16)))));
        fs0[15] = (utau[15]-((((Fstar[20][2]*Vpk[15][20][2])+((Fstar[20][0]*
          Vpk[15][20][0])+(Fstar[20][1]*Vpk[15][20][1])))+((Tstar[20][2]*
          Wpk[15][20][2])+((Tstar[20][0]*Wpk[15][19][0])+(Tstar[20][1]*
          Wpk[15][20][1]))))+temp[0]));
        temp[0] = ((((Fstar[17][2]*Vpk[16][17][2])+((Fstar[17][0]*Vpk[16][17][0]
          )+(Fstar[17][1]*Vpk[16][17][1])))+((Tstar[17][0]*c17)+(Tstar[17][2]*
          s17)))+(((Fstar[18][2]*Vpk[16][18][2])+((Fstar[18][0]*Vpk[16][18][0])+
          (Fstar[18][1]*Vpk[16][18][1])))+((Tstar[18][0]*Wpk[16][18][0])+(
          Tstar[18][2]*Wpk[16][18][2]))));
        fs0[16] = (utau[16]-((((Fstar[20][2]*Vpk[16][20][2])+((Fstar[20][0]*
          Vpk[16][20][0])+(Fstar[20][1]*Vpk[16][20][1])))+((Tstar[20][2]*
          Wpk[16][20][2])+((Tstar[20][0]*Wpk[16][19][0])+(Tstar[20][1]*
          Wpk[16][20][1]))))+temp[0]));
        fs0[17] = (utau[17]-(((Tstar[17][1]+((Fstar[17][2]*rk[7][0])-(
          Fstar[17][0]*rk[7][2])))+(Tstar[18][1]+((Fstar[18][0]*Vpk[17][18][0])+
          (Fstar[18][2]*Vpk[17][18][2]))))+(((Fstar[20][2]*Vpk[17][20][2])+((
          Fstar[20][0]*Vpk[17][20][0])+(Fstar[20][1]*Vpk[17][20][1])))+((
          Tstar[20][1]*c20)-(Tstar[20][2]*s20)))));
        fs0[18] = (utau[18]-((Tstar[18][1]+((Fstar[18][2]*rk[8][0])-(
          Fstar[18][0]*rk[8][2])))+(((Fstar[20][2]*Vpk[18][20][2])+((
          Fstar[20][0]*Vpk[18][20][0])+(Fstar[20][1]*Vpk[18][20][1])))+((
          Tstar[20][1]*c20)-(Tstar[20][2]*s20)))));
        fs0[19] = (utau[19]-(((Fstar[20][2]*Vpk[19][20][2])+((Fstar[20][0]*
          Vpk[19][20][0])+(Fstar[20][1]*Vpk[19][20][1])))+((Tstar[20][1]*c20)-(
          Tstar[20][2]*s20))));
        fs0[20] = (utau[20]-(Tstar[20][0]+((Fstar[20][1]*rk[9][2])-(Fstar[20][2]
          *rk[9][1]))));
        fs0flg = 1;
    }
/*
 Used 0.01 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  526 adds/subtracts/negates
                    455 multiplies
                      0 divides
                    103 assignments
*/
}

void sddomm(int routine)
{
    int dumroutine,errnum;
    int i;

    if (mmflg == 0) {
/*
Compute mass matrix (MM)
*/
        sddovpk();
        IkWpk[3][5][0] = -(ik[0][0][0]*s4);
        IkWpk[3][5][1] = (ik[0][1][1]*Wpk[3][5][1]);
        IkWpk[3][5][2] = (ik[0][2][2]*Wpk[3][5][2]);
        IkWpk[3][6][0] = (ik[1][0][0]*Wpk[3][6][0]);
        IkWpk[3][6][1] = (ik[1][1][1]*Wpk[3][6][1]);
        IkWpk[3][6][2] = (ik[1][2][2]*Wpk[3][5][2]);
        IkWpk[3][7][0] = (ik[2][0][0]*Wpk[3][7][0]);
        IkWpk[3][7][1] = (ik[2][1][1]*Wpk[3][6][1]);
        IkWpk[3][7][2] = (ik[2][2][2]*Wpk[3][7][2]);
        IkWpk[3][8][0] = (ik[3][0][0]*Wpk[3][8][0]);
        IkWpk[3][8][1] = (ik[3][1][1]*Wpk[3][6][1]);
        IkWpk[3][8][2] = (ik[3][2][2]*Wpk[3][8][2]);
        IkWpk[3][11][0] = (ik[4][0][0]*Wpk[3][11][0]);
        IkWpk[3][11][1] = (ik[4][1][1]*Wpk[3][10][1]);
        IkWpk[3][11][2] = (ik[4][2][2]*Wpk[3][11][2]);
        IkWpk[3][12][0] = (ik[5][0][0]*Wpk[3][12][0]);
        IkWpk[3][12][1] = (ik[5][1][1]*Wpk[3][10][1]);
        IkWpk[3][12][2] = (ik[5][2][2]*Wpk[3][12][2]);
        IkWpk[3][14][0] = (ik[6][0][0]*Wpk[3][13][0]);
        IkWpk[3][14][1] = (ik[6][1][1]*Wpk[3][14][1]);
        IkWpk[3][14][2] = (ik[6][2][2]*Wpk[3][14][2]);
        IkWpk[3][17][0] = (ik[7][0][0]*Wpk[3][17][0]);
        IkWpk[3][17][1] = (ik[7][1][1]*Wpk[3][16][1]);
        IkWpk[3][17][2] = (ik[7][2][2]*Wpk[3][17][2]);
        IkWpk[3][18][0] = (ik[8][0][0]*Wpk[3][18][0]);
        IkWpk[3][18][1] = (ik[8][1][1]*Wpk[3][16][1]);
        IkWpk[3][18][2] = (ik[8][2][2]*Wpk[3][18][2]);
        IkWpk[3][20][0] = (ik[9][0][0]*Wpk[3][19][0]);
        IkWpk[3][20][1] = (ik[9][1][1]*Wpk[3][20][1]);
        IkWpk[3][20][2] = (ik[9][2][2]*Wpk[3][20][2]);
        IkWpk[4][5][1] = (ik[0][1][1]*c5);
        IkWpk[4][5][2] = -(ik[0][2][2]*s5);
        IkWpk[4][6][0] = (ik[1][0][0]*Wpk[4][6][0]);
        IkWpk[4][6][1] = (ik[1][1][1]*Wpk[4][6][1]);
        IkWpk[4][6][2] = -(ik[1][2][2]*s5);
        IkWpk[4][7][0] = (ik[2][0][0]*Wpk[4][7][0]);
        IkWpk[4][7][1] = (ik[2][1][1]*Wpk[4][6][1]);
        IkWpk[4][7][2] = (ik[2][2][2]*Wpk[4][7][2]);
        IkWpk[4][8][0] = (ik[3][0][0]*Wpk[4][8][0]);
        IkWpk[4][8][1] = (ik[3][1][1]*Wpk[4][6][1]);
        IkWpk[4][8][2] = (ik[3][2][2]*Wpk[4][8][2]);
        IkWpk[4][11][0] = (ik[4][0][0]*Wpk[4][11][0]);
        IkWpk[4][11][1] = (ik[4][1][1]*Wpk[4][10][1]);
        IkWpk[4][11][2] = (ik[4][2][2]*Wpk[4][11][2]);
        IkWpk[4][12][0] = (ik[5][0][0]*Wpk[4][12][0]);
        IkWpk[4][12][1] = (ik[5][1][1]*Wpk[4][10][1]);
        IkWpk[4][12][2] = (ik[5][2][2]*Wpk[4][12][2]);
        IkWpk[4][14][0] = (ik[6][0][0]*Wpk[4][13][0]);
        IkWpk[4][14][1] = (ik[6][1][1]*Wpk[4][14][1]);
        IkWpk[4][14][2] = (ik[6][2][2]*Wpk[4][14][2]);
        IkWpk[4][17][0] = (ik[7][0][0]*Wpk[4][17][0]);
        IkWpk[4][17][1] = (ik[7][1][1]*Wpk[4][16][1]);
        IkWpk[4][17][2] = (ik[7][2][2]*Wpk[4][17][2]);
        IkWpk[4][18][0] = (ik[8][0][0]*Wpk[4][18][0]);
        IkWpk[4][18][1] = (ik[8][1][1]*Wpk[4][16][1]);
        IkWpk[4][18][2] = (ik[8][2][2]*Wpk[4][18][2]);
        IkWpk[4][20][0] = (ik[9][0][0]*Wpk[4][19][0]);
        IkWpk[4][20][1] = (ik[9][1][1]*Wpk[4][20][1]);
        IkWpk[4][20][2] = (ik[9][2][2]*Wpk[4][20][2]);
        IkWpk[5][6][0] = (ik[1][0][0]*c6);
        IkWpk[5][6][1] = -(ik[1][1][1]*s6);
        IkWpk[5][7][0] = (ik[2][0][0]*Wpk[5][7][0]);
        IkWpk[5][7][1] = -(ik[2][1][1]*s6);
        IkWpk[5][7][2] = (ik[2][2][2]*Wpk[5][7][2]);
        IkWpk[5][8][0] = (ik[3][0][0]*Wpk[5][8][0]);
        IkWpk[5][8][1] = -(ik[3][1][1]*s6);
        IkWpk[5][8][2] = (ik[3][2][2]*Wpk[5][8][2]);
        IkWpk[5][11][0] = (ik[4][0][0]*Wpk[5][11][0]);
        IkWpk[5][11][1] = (ik[4][1][1]*Wpk[5][10][1]);
        IkWpk[5][11][2] = (ik[4][2][2]*Wpk[5][11][2]);
        IkWpk[5][12][0] = (ik[5][0][0]*Wpk[5][12][0]);
        IkWpk[5][12][1] = (ik[5][1][1]*Wpk[5][10][1]);
        IkWpk[5][12][2] = (ik[5][2][2]*Wpk[5][12][2]);
        IkWpk[5][14][0] = (ik[6][0][0]*Wpk[5][13][0]);
        IkWpk[5][14][1] = (ik[6][1][1]*Wpk[5][14][1]);
        IkWpk[5][14][2] = (ik[6][2][2]*Wpk[5][14][2]);
        IkWpk[5][17][0] = (ik[7][0][0]*Wpk[5][17][0]);
        IkWpk[5][17][1] = (ik[7][1][1]*Wpk[5][16][1]);
        IkWpk[5][17][2] = (ik[7][2][2]*Wpk[5][17][2]);
        IkWpk[5][18][0] = (ik[8][0][0]*Wpk[5][18][0]);
        IkWpk[5][18][1] = (ik[8][1][1]*Wpk[5][16][1]);
        IkWpk[5][18][2] = (ik[8][2][2]*Wpk[5][18][2]);
        IkWpk[5][20][0] = (ik[9][0][0]*Wpk[5][19][0]);
        IkWpk[5][20][1] = (ik[9][1][1]*Wpk[5][20][1]);
        IkWpk[5][20][2] = (ik[9][2][2]*Wpk[5][20][2]);
        IkWpk[6][7][0] = -(ik[2][0][0]*s7);
        IkWpk[6][7][2] = (ik[2][2][2]*c7);
        IkWpk[6][8][0] = -(ik[3][0][0]*s8);
        IkWpk[6][8][2] = (ik[3][2][2]*c8);
        IkWpk[9][11][0] = (ik[4][0][0]*Wpk[9][11][0]);
        IkWpk[9][11][1] = (ik[4][1][1]*s10);
        IkWpk[9][11][2] = (ik[4][2][2]*Wpk[9][11][2]);
        IkWpk[9][12][0] = (ik[5][0][0]*Wpk[9][12][0]);
        IkWpk[9][12][1] = (ik[5][1][1]*s10);
        IkWpk[9][12][2] = (ik[5][2][2]*Wpk[9][12][2]);
        IkWpk[9][14][0] = (ik[6][0][0]*Wpk[9][13][0]);
        IkWpk[9][14][1] = (ik[6][1][1]*Wpk[9][14][1]);
        IkWpk[9][14][2] = (ik[6][2][2]*Wpk[9][14][2]);
        IkWpk[10][11][0] = (ik[4][0][0]*c11);
        IkWpk[10][11][2] = (ik[4][2][2]*s11);
        IkWpk[10][12][0] = (ik[5][0][0]*Wpk[10][12][0]);
        IkWpk[10][12][2] = (ik[5][2][2]*Wpk[10][12][2]);
        IkWpk[10][14][0] = (ik[6][0][0]*Wpk[10][13][0]);
        IkWpk[10][14][1] = (ik[6][1][1]*Wpk[10][14][1]);
        IkWpk[10][14][2] = (ik[6][2][2]*Wpk[10][14][2]);
        IkWpk[11][14][1] = (ik[6][1][1]*c14);
        IkWpk[11][14][2] = -(ik[6][2][2]*s14);
        IkWpk[12][14][1] = (ik[6][1][1]*c14);
        IkWpk[12][14][2] = -(ik[6][2][2]*s14);
        IkWpk[13][14][1] = (ik[6][1][1]*c14);
        IkWpk[13][14][2] = -(ik[6][2][2]*s14);
        IkWpk[15][17][0] = (ik[7][0][0]*Wpk[15][17][0]);
        IkWpk[15][17][1] = (ik[7][1][1]*s16);
        IkWpk[15][17][2] = (ik[7][2][2]*Wpk[15][17][2]);
        IkWpk[15][18][0] = (ik[8][0][0]*Wpk[15][18][0]);
        IkWpk[15][18][1] = (ik[8][1][1]*s16);
        IkWpk[15][18][2] = (ik[8][2][2]*Wpk[15][18][2]);
        IkWpk[15][20][0] = (ik[9][0][0]*Wpk[15][19][0]);
        IkWpk[15][20][1] = (ik[9][1][1]*Wpk[15][20][1]);
        IkWpk[15][20][2] = (ik[9][2][2]*Wpk[15][20][2]);
        IkWpk[16][17][0] = (ik[7][0][0]*c17);
        IkWpk[16][17][2] = (ik[7][2][2]*s17);
        IkWpk[16][18][0] = (ik[8][0][0]*Wpk[16][18][0]);
        IkWpk[16][18][2] = (ik[8][2][2]*Wpk[16][18][2]);
        IkWpk[16][20][0] = (ik[9][0][0]*Wpk[16][19][0]);
        IkWpk[16][20][1] = (ik[9][1][1]*Wpk[16][20][1]);
        IkWpk[16][20][2] = (ik[9][2][2]*Wpk[16][20][2]);
        IkWpk[17][20][1] = (ik[9][1][1]*c20);
        IkWpk[17][20][2] = -(ik[9][2][2]*s20);
        IkWpk[18][20][1] = (ik[9][1][1]*c20);
        IkWpk[18][20][2] = -(ik[9][2][2]*s20);
        IkWpk[19][20][1] = (ik[9][1][1]*c20);
        IkWpk[19][20][2] = -(ik[9][2][2]*s20);
        temp[0] = ((mk[3]*((Vpk[0][8][2]*Vpk[0][8][2])+((Vpk[0][6][1]*
          Vpk[0][6][1])+(Vpk[0][8][0]*Vpk[0][8][0]))))+((mk[2]*((Vpk[0][7][2]*
          Vpk[0][7][2])+((Vpk[0][6][1]*Vpk[0][6][1])+(Vpk[0][7][0]*Vpk[0][7][0])
          )))+((mk[0]*((Vpk[0][5][2]*Vpk[0][5][2])+((Vpk[0][5][1]*Vpk[0][5][1])+
          (s4*s4))))+(mk[1]*((Vpk[0][5][2]*Vpk[0][5][2])+((Vpk[0][6][0]*
          Vpk[0][6][0])+(Vpk[0][6][1]*Vpk[0][6][1])))))));
        temp[1] = ((mk[6]*((Vpk[0][14][2]*Vpk[0][14][2])+((Vpk[0][13][0]*
          Vpk[0][13][0])+(Vpk[0][14][1]*Vpk[0][14][1]))))+((mk[5]*((
          Vpk[0][12][2]*Vpk[0][12][2])+((Vpk[0][10][1]*Vpk[0][10][1])+(
          Vpk[0][12][0]*Vpk[0][12][0]))))+((mk[4]*((Vpk[0][11][2]*Vpk[0][11][2])
          +((Vpk[0][10][1]*Vpk[0][10][1])+(Vpk[0][11][0]*Vpk[0][11][0]))))+
          temp[0])));
        mm[0][0] = ((mk[9]*((Vpk[0][20][2]*Vpk[0][20][2])+((Vpk[0][19][0]*
          Vpk[0][19][0])+(Vpk[0][20][1]*Vpk[0][20][1]))))+((mk[8]*((
          Vpk[0][18][2]*Vpk[0][18][2])+((Vpk[0][16][1]*Vpk[0][16][1])+(
          Vpk[0][18][0]*Vpk[0][18][0]))))+((mk[7]*((Vpk[0][17][2]*Vpk[0][17][2])
          +((Vpk[0][16][1]*Vpk[0][16][1])+(Vpk[0][17][0]*Vpk[0][17][0]))))+
          temp[1])));
        temp[0] = ((mk[2]*((Vpk[0][7][2]*Vpk[1][7][2])+((Vpk[0][6][1]*
          Vpk[1][6][1])+(Vpk[0][7][0]*Vpk[1][7][0]))))+((mk[0]*((Vpk[0][5][2]*
          Vpk[1][5][2])+((Vpk[0][5][1]*Vpk[1][5][1])-(Vpk[1][4][0]*s4))))+(mk[1]
          *((Vpk[0][5][2]*Vpk[1][5][2])+((Vpk[0][6][0]*Vpk[1][6][0])+(
          Vpk[0][6][1]*Vpk[1][6][1]))))));
        temp[1] = ((mk[5]*((Vpk[0][12][2]*Vpk[1][12][2])+((Vpk[0][10][1]*
          Vpk[1][10][1])+(Vpk[0][12][0]*Vpk[1][12][0]))))+((mk[4]*((
          Vpk[0][11][2]*Vpk[1][11][2])+((Vpk[0][10][1]*Vpk[1][10][1])+(
          Vpk[0][11][0]*Vpk[1][11][0]))))+((mk[3]*((Vpk[0][8][2]*Vpk[1][8][2])+(
          (Vpk[0][6][1]*Vpk[1][6][1])+(Vpk[0][8][0]*Vpk[1][8][0]))))+temp[0])));
        temp[2] = ((mk[8]*((Vpk[0][18][2]*Vpk[1][18][2])+((Vpk[0][16][1]*
          Vpk[1][16][1])+(Vpk[0][18][0]*Vpk[1][18][0]))))+((mk[7]*((
          Vpk[0][17][2]*Vpk[1][17][2])+((Vpk[0][16][1]*Vpk[1][16][1])+(
          Vpk[0][17][0]*Vpk[1][17][0]))))+((mk[6]*((Vpk[0][14][2]*Vpk[1][14][2])
          +((Vpk[0][13][0]*Vpk[1][13][0])+(Vpk[0][14][1]*Vpk[1][14][1]))))+
          temp[1])));
        mm[0][1] = ((mk[9]*((Vpk[0][20][2]*Vpk[1][20][2])+((Vpk[0][19][0]*
          Vpk[1][19][0])+(Vpk[0][20][1]*Vpk[1][20][1]))))+temp[2]);
        temp[0] = ((mk[2]*((Vpk[0][7][2]*Vpk[2][7][2])+((Vpk[0][6][1]*
          Vpk[2][6][1])+(Vpk[0][7][0]*Vpk[2][7][0]))))+((mk[0]*((Vpk[0][5][2]*
          Vpk[2][5][2])+((Vpk[0][5][1]*Vpk[2][5][1])-(Vpk[2][4][0]*s4))))+(mk[1]
          *((Vpk[0][5][2]*Vpk[2][5][2])+((Vpk[0][6][0]*Vpk[2][6][0])+(
          Vpk[0][6][1]*Vpk[2][6][1]))))));
        temp[1] = ((mk[5]*((Vpk[0][12][2]*Vpk[2][12][2])+((Vpk[0][10][1]*
          Vpk[2][10][1])+(Vpk[0][12][0]*Vpk[2][12][0]))))+((mk[4]*((
          Vpk[0][11][2]*Vpk[2][11][2])+((Vpk[0][10][1]*Vpk[2][10][1])+(
          Vpk[0][11][0]*Vpk[2][11][0]))))+((mk[3]*((Vpk[0][8][2]*Vpk[2][8][2])+(
          (Vpk[0][6][1]*Vpk[2][6][1])+(Vpk[0][8][0]*Vpk[2][8][0]))))+temp[0])));
        temp[2] = ((mk[8]*((Vpk[0][18][2]*Vpk[2][18][2])+((Vpk[0][16][1]*
          Vpk[2][16][1])+(Vpk[0][18][0]*Vpk[2][18][0]))))+((mk[7]*((
          Vpk[0][17][2]*Vpk[2][17][2])+((Vpk[0][16][1]*Vpk[2][16][1])+(
          Vpk[0][17][0]*Vpk[2][17][0]))))+((mk[6]*((Vpk[0][14][2]*Vpk[2][14][2])
          +((Vpk[0][13][0]*Vpk[2][13][0])+(Vpk[0][14][1]*Vpk[2][14][1]))))+
          temp[1])));
        mm[0][2] = ((mk[9]*((Vpk[0][20][2]*Vpk[2][20][2])+((Vpk[0][19][0]*
          Vpk[2][19][0])+(Vpk[0][20][1]*Vpk[2][20][1]))))+temp[2]);
        temp[0] = ((mk[2]*((Vpk[0][7][2]*Vpk[3][7][2])+((Vpk[0][6][1]*
          Vpk[3][7][1])+(Vpk[0][7][0]*Vpk[3][7][0]))))+((mk[0]*((Vpk[0][5][2]*
          Vpk[3][5][2])+((Vpk[0][5][1]*Vpk[3][5][1])-(Vpk[3][5][0]*s4))))+(mk[1]
          *((Vpk[0][5][2]*Vpk[3][6][2])+((Vpk[0][6][0]*Vpk[3][6][0])+(
          Vpk[0][6][1]*Vpk[3][6][1]))))));
        temp[1] = ((mk[5]*((Vpk[0][12][2]*Vpk[3][12][2])+((Vpk[0][10][1]*
          Vpk[3][12][1])+(Vpk[0][12][0]*Vpk[3][12][0]))))+((mk[4]*((
          Vpk[0][11][2]*Vpk[3][11][2])+((Vpk[0][10][1]*Vpk[3][11][1])+(
          Vpk[0][11][0]*Vpk[3][11][0]))))+((mk[3]*((Vpk[0][8][2]*Vpk[3][8][2])+(
          (Vpk[0][6][1]*Vpk[3][8][1])+(Vpk[0][8][0]*Vpk[3][8][0]))))+temp[0])));
        temp[2] = ((mk[8]*((Vpk[0][18][2]*Vpk[3][18][2])+((Vpk[0][16][1]*
          Vpk[3][18][1])+(Vpk[0][18][0]*Vpk[3][18][0]))))+((mk[7]*((
          Vpk[0][17][2]*Vpk[3][17][2])+((Vpk[0][16][1]*Vpk[3][17][1])+(
          Vpk[0][17][0]*Vpk[3][17][0]))))+((mk[6]*((Vpk[0][14][2]*Vpk[3][14][2])
          +((Vpk[0][13][0]*Vpk[3][14][0])+(Vpk[0][14][1]*Vpk[3][14][1]))))+
          temp[1])));
        mm[0][3] = ((mk[9]*((Vpk[0][20][2]*Vpk[3][20][2])+((Vpk[0][19][0]*
          Vpk[3][20][0])+(Vpk[0][20][1]*Vpk[3][20][1]))))+temp[2]);
        temp[0] = ((mk[2]*((Vpk[0][7][2]*Vpk[4][7][2])+((Vpk[0][6][1]*
          Vpk[4][7][1])+(Vpk[0][7][0]*Vpk[4][7][0]))))+((mk[0]*((Vpk[0][5][2]*
          Vpk[4][5][2])+((Vpk[0][5][1]*Vpk[4][5][1])-(Vpk[4][5][0]*s4))))+(mk[1]
          *((Vpk[0][5][2]*Vpk[4][6][2])+((Vpk[0][6][0]*Vpk[4][6][0])+(
          Vpk[0][6][1]*Vpk[4][6][1]))))));
        temp[1] = ((mk[5]*((Vpk[0][12][2]*Vpk[4][12][2])+((Vpk[0][10][1]*
          Vpk[4][12][1])+(Vpk[0][12][0]*Vpk[4][12][0]))))+((mk[4]*((
          Vpk[0][11][2]*Vpk[4][11][2])+((Vpk[0][10][1]*Vpk[4][11][1])+(
          Vpk[0][11][0]*Vpk[4][11][0]))))+((mk[3]*((Vpk[0][8][2]*Vpk[4][8][2])+(
          (Vpk[0][6][1]*Vpk[4][8][1])+(Vpk[0][8][0]*Vpk[4][8][0]))))+temp[0])));
        temp[2] = ((mk[8]*((Vpk[0][18][2]*Vpk[4][18][2])+((Vpk[0][16][1]*
          Vpk[4][18][1])+(Vpk[0][18][0]*Vpk[4][18][0]))))+((mk[7]*((
          Vpk[0][17][2]*Vpk[4][17][2])+((Vpk[0][16][1]*Vpk[4][17][1])+(
          Vpk[0][17][0]*Vpk[4][17][0]))))+((mk[6]*((Vpk[0][14][2]*Vpk[4][14][2])
          +((Vpk[0][13][0]*Vpk[4][14][0])+(Vpk[0][14][1]*Vpk[4][14][1]))))+
          temp[1])));
        mm[0][4] = ((mk[9]*((Vpk[0][20][2]*Vpk[4][20][2])+((Vpk[0][19][0]*
          Vpk[4][20][0])+(Vpk[0][20][1]*Vpk[4][20][1]))))+temp[2]);
        temp[0] = ((mk[3]*((Vpk[0][8][2]*Vpk[5][8][2])+((Vpk[0][6][1]*
          Vpk[5][8][1])+(Vpk[0][8][0]*Vpk[5][8][0]))))+((mk[2]*((Vpk[0][7][2]*
          Vpk[5][7][2])+((Vpk[0][6][1]*Vpk[5][7][1])+(Vpk[0][7][0]*Vpk[5][7][0])
          )))+((mk[0]*((rk[0][2]*Vpk[0][5][1])-(rk[0][1]*Vpk[0][5][2])))+(mk[1]*
          ((Vpk[0][5][2]*Vpk[5][6][2])+((Vpk[0][6][0]*Vpk[5][6][0])+(
          Vpk[0][6][1]*Vpk[5][6][1])))))));
        temp[1] = ((mk[6]*((Vpk[0][14][2]*Vpk[5][14][2])+((Vpk[0][13][0]*
          Vpk[5][14][0])+(Vpk[0][14][1]*Vpk[5][14][1]))))+((mk[5]*((
          Vpk[0][12][2]*Vpk[5][12][2])+((Vpk[0][10][1]*Vpk[5][12][1])+(
          Vpk[0][12][0]*Vpk[5][12][0]))))+((mk[4]*((Vpk[0][11][2]*Vpk[5][11][2])
          +((Vpk[0][10][1]*Vpk[5][11][1])+(Vpk[0][11][0]*Vpk[5][11][0]))))+
          temp[0])));
        mm[0][5] = ((mk[9]*((Vpk[0][20][2]*Vpk[5][20][2])+((Vpk[0][19][0]*
          Vpk[5][20][0])+(Vpk[0][20][1]*Vpk[5][20][1]))))+((mk[8]*((
          Vpk[0][18][2]*Vpk[5][18][2])+((Vpk[0][16][1]*Vpk[5][18][1])+(
          Vpk[0][18][0]*Vpk[5][18][0]))))+((mk[7]*((Vpk[0][17][2]*Vpk[5][17][2])
          +((Vpk[0][16][1]*Vpk[5][17][1])+(Vpk[0][17][0]*Vpk[5][17][0]))))+
          temp[1])));
        mm[0][6] = ((mk[3]*((Vpk[0][8][2]*Vpk[6][8][2])+((Vpk[0][6][1]*
          Vpk[6][8][1])+(Vpk[0][8][0]*Vpk[6][8][0]))))+((mk[1]*((rk[1][1]*
          Vpk[0][6][0])-(rk[1][0]*Vpk[0][6][1])))+(mk[2]*((Vpk[0][7][2]*
          Vpk[6][7][2])+((Vpk[0][6][1]*Vpk[6][7][1])+(Vpk[0][7][0]*Vpk[6][7][0])
          )))));
        mm[0][7] = (mk[2]*((rk[2][0]*Vpk[0][7][2])-(rk[2][2]*Vpk[0][7][0])));
        mm[0][8] = (mk[3]*((rk[3][0]*Vpk[0][8][2])-(rk[3][2]*Vpk[0][8][0])));
        mm[0][9] = ((mk[6]*((Vpk[0][14][2]*Vpk[9][14][2])+((Vpk[0][13][0]*
          Vpk[9][14][0])+(Vpk[0][14][1]*Vpk[9][14][1]))))+((mk[4]*((
          Vpk[0][11][2]*Vpk[9][11][2])+((Vpk[0][10][1]*Vpk[9][11][1])+(
          Vpk[0][11][0]*Vpk[9][11][0]))))+(mk[5]*((Vpk[0][12][2]*Vpk[9][12][2])+
          ((Vpk[0][10][1]*Vpk[9][12][1])+(Vpk[0][12][0]*Vpk[9][12][0]))))));
        mm[0][10] = ((mk[6]*((Vpk[0][14][2]*Vpk[10][14][2])+((Vpk[0][13][0]*
          Vpk[10][14][0])+(Vpk[0][14][1]*Vpk[10][14][1]))))+((mk[4]*((
          Vpk[0][11][2]*Vpk[10][11][2])+((Vpk[0][10][1]*Vpk[10][11][1])+(
          Vpk[0][11][0]*Vpk[10][11][0]))))+(mk[5]*((Vpk[0][12][2]*Vpk[10][12][2]
          )+((Vpk[0][10][1]*Vpk[10][12][1])+(Vpk[0][12][0]*Vpk[10][12][0]))))));
        mm[0][11] = ((mk[6]*((Vpk[0][14][2]*Vpk[11][14][2])+((Vpk[0][13][0]*
          Vpk[11][14][0])+(Vpk[0][14][1]*Vpk[11][14][1]))))+((mk[4]*((rk[4][0]*
          Vpk[0][11][2])-(rk[4][2]*Vpk[0][11][0])))+(mk[5]*((Vpk[0][12][0]*
          Vpk[11][12][0])+(Vpk[0][12][2]*Vpk[11][12][2])))));
        mm[0][12] = ((mk[5]*((rk[5][0]*Vpk[0][12][2])-(rk[5][2]*Vpk[0][12][0])))
          +(mk[6]*((Vpk[0][14][2]*Vpk[12][14][2])+((Vpk[0][13][0]*Vpk[12][14][0]
          )+(Vpk[0][14][1]*Vpk[12][14][1])))));
        mm[0][13] = (mk[6]*((Vpk[0][14][2]*Vpk[13][14][2])+((Vpk[0][13][0]*
          Vpk[13][14][0])+(Vpk[0][14][1]*Vpk[13][14][1]))));
        mm[0][14] = (mk[6]*((rk[6][2]*Vpk[0][14][1])-(rk[6][1]*Vpk[0][14][2])));
        mm[0][15] = ((mk[9]*((Vpk[0][20][2]*Vpk[15][20][2])+((Vpk[0][19][0]*
          Vpk[15][20][0])+(Vpk[0][20][1]*Vpk[15][20][1]))))+((mk[7]*((
          Vpk[0][17][2]*Vpk[15][17][2])+((Vpk[0][16][1]*Vpk[15][17][1])+(
          Vpk[0][17][0]*Vpk[15][17][0]))))+(mk[8]*((Vpk[0][18][2]*Vpk[15][18][2]
          )+((Vpk[0][16][1]*Vpk[15][18][1])+(Vpk[0][18][0]*Vpk[15][18][0]))))));
        mm[0][16] = ((mk[9]*((Vpk[0][20][2]*Vpk[16][20][2])+((Vpk[0][19][0]*
          Vpk[16][20][0])+(Vpk[0][20][1]*Vpk[16][20][1]))))+((mk[7]*((
          Vpk[0][17][2]*Vpk[16][17][2])+((Vpk[0][16][1]*Vpk[16][17][1])+(
          Vpk[0][17][0]*Vpk[16][17][0]))))+(mk[8]*((Vpk[0][18][2]*Vpk[16][18][2]
          )+((Vpk[0][16][1]*Vpk[16][18][1])+(Vpk[0][18][0]*Vpk[16][18][0]))))));
        mm[0][17] = ((mk[9]*((Vpk[0][20][2]*Vpk[17][20][2])+((Vpk[0][19][0]*
          Vpk[17][20][0])+(Vpk[0][20][1]*Vpk[17][20][1]))))+((mk[7]*((rk[7][0]*
          Vpk[0][17][2])-(rk[7][2]*Vpk[0][17][0])))+(mk[8]*((Vpk[0][18][0]*
          Vpk[17][18][0])+(Vpk[0][18][2]*Vpk[17][18][2])))));
        mm[0][18] = ((mk[8]*((rk[8][0]*Vpk[0][18][2])-(rk[8][2]*Vpk[0][18][0])))
          +(mk[9]*((Vpk[0][20][2]*Vpk[18][20][2])+((Vpk[0][19][0]*Vpk[18][20][0]
          )+(Vpk[0][20][1]*Vpk[18][20][1])))));
        mm[0][19] = (mk[9]*((Vpk[0][20][2]*Vpk[19][20][2])+((Vpk[0][19][0]*
          Vpk[19][20][0])+(Vpk[0][20][1]*Vpk[19][20][1]))));
        mm[0][20] = (mk[9]*((rk[9][2]*Vpk[0][20][1])-(rk[9][1]*Vpk[0][20][2])));
        temp[0] = ((mk[2]*((Vpk[1][7][2]*Vpk[1][7][2])+((Vpk[1][6][1]*
          Vpk[1][6][1])+(Vpk[1][7][0]*Vpk[1][7][0]))))+((mk[0]*((Vpk[1][5][2]*
          Vpk[1][5][2])+((Vpk[1][4][0]*Vpk[1][4][0])+(Vpk[1][5][1]*Vpk[1][5][1])
          )))+(mk[1]*((Vpk[1][5][2]*Vpk[1][5][2])+((Vpk[1][6][0]*Vpk[1][6][0])+(
          Vpk[1][6][1]*Vpk[1][6][1]))))));
        temp[1] = ((mk[5]*((Vpk[1][12][2]*Vpk[1][12][2])+((Vpk[1][10][1]*
          Vpk[1][10][1])+(Vpk[1][12][0]*Vpk[1][12][0]))))+((mk[4]*((
          Vpk[1][11][2]*Vpk[1][11][2])+((Vpk[1][10][1]*Vpk[1][10][1])+(
          Vpk[1][11][0]*Vpk[1][11][0]))))+((mk[3]*((Vpk[1][8][2]*Vpk[1][8][2])+(
          (Vpk[1][6][1]*Vpk[1][6][1])+(Vpk[1][8][0]*Vpk[1][8][0]))))+temp[0])));
        temp[2] = ((mk[8]*((Vpk[1][18][2]*Vpk[1][18][2])+((Vpk[1][16][1]*
          Vpk[1][16][1])+(Vpk[1][18][0]*Vpk[1][18][0]))))+((mk[7]*((
          Vpk[1][17][2]*Vpk[1][17][2])+((Vpk[1][16][1]*Vpk[1][16][1])+(
          Vpk[1][17][0]*Vpk[1][17][0]))))+((mk[6]*((Vpk[1][14][2]*Vpk[1][14][2])
          +((Vpk[1][13][0]*Vpk[1][13][0])+(Vpk[1][14][1]*Vpk[1][14][1]))))+
          temp[1])));
        mm[1][1] = ((mk[9]*((Vpk[1][20][2]*Vpk[1][20][2])+((Vpk[1][19][0]*
          Vpk[1][19][0])+(Vpk[1][20][1]*Vpk[1][20][1]))))+temp[2]);
        temp[0] = ((mk[2]*((Vpk[1][7][2]*Vpk[2][7][2])+((Vpk[1][6][1]*
          Vpk[2][6][1])+(Vpk[1][7][0]*Vpk[2][7][0]))))+((mk[0]*((Vpk[1][5][2]*
          Vpk[2][5][2])+((Vpk[1][4][0]*Vpk[2][4][0])+(Vpk[1][5][1]*Vpk[2][5][1])
          )))+(mk[1]*((Vpk[1][5][2]*Vpk[2][5][2])+((Vpk[1][6][0]*Vpk[2][6][0])+(
          Vpk[1][6][1]*Vpk[2][6][1]))))));
        temp[1] = ((mk[5]*((Vpk[1][12][2]*Vpk[2][12][2])+((Vpk[1][10][1]*
          Vpk[2][10][1])+(Vpk[1][12][0]*Vpk[2][12][0]))))+((mk[4]*((
          Vpk[1][11][2]*Vpk[2][11][2])+((Vpk[1][10][1]*Vpk[2][10][1])+(
          Vpk[1][11][0]*Vpk[2][11][0]))))+((mk[3]*((Vpk[1][8][2]*Vpk[2][8][2])+(
          (Vpk[1][6][1]*Vpk[2][6][1])+(Vpk[1][8][0]*Vpk[2][8][0]))))+temp[0])));
        temp[2] = ((mk[8]*((Vpk[1][18][2]*Vpk[2][18][2])+((Vpk[1][16][1]*
          Vpk[2][16][1])+(Vpk[1][18][0]*Vpk[2][18][0]))))+((mk[7]*((
          Vpk[1][17][2]*Vpk[2][17][2])+((Vpk[1][16][1]*Vpk[2][16][1])+(
          Vpk[1][17][0]*Vpk[2][17][0]))))+((mk[6]*((Vpk[1][14][2]*Vpk[2][14][2])
          +((Vpk[1][13][0]*Vpk[2][13][0])+(Vpk[1][14][1]*Vpk[2][14][1]))))+
          temp[1])));
        mm[1][2] = ((mk[9]*((Vpk[1][20][2]*Vpk[2][20][2])+((Vpk[1][19][0]*
          Vpk[2][19][0])+(Vpk[1][20][1]*Vpk[2][20][1]))))+temp[2]);
        temp[0] = ((mk[2]*((Vpk[1][7][2]*Vpk[3][7][2])+((Vpk[1][6][1]*
          Vpk[3][7][1])+(Vpk[1][7][0]*Vpk[3][7][0]))))+((mk[0]*((Vpk[1][5][2]*
          Vpk[3][5][2])+((Vpk[1][4][0]*Vpk[3][5][0])+(Vpk[1][5][1]*Vpk[3][5][1])
          )))+(mk[1]*((Vpk[1][5][2]*Vpk[3][6][2])+((Vpk[1][6][0]*Vpk[3][6][0])+(
          Vpk[1][6][1]*Vpk[3][6][1]))))));
        temp[1] = ((mk[5]*((Vpk[1][12][2]*Vpk[3][12][2])+((Vpk[1][10][1]*
          Vpk[3][12][1])+(Vpk[1][12][0]*Vpk[3][12][0]))))+((mk[4]*((
          Vpk[1][11][2]*Vpk[3][11][2])+((Vpk[1][10][1]*Vpk[3][11][1])+(
          Vpk[1][11][0]*Vpk[3][11][0]))))+((mk[3]*((Vpk[1][8][2]*Vpk[3][8][2])+(
          (Vpk[1][6][1]*Vpk[3][8][1])+(Vpk[1][8][0]*Vpk[3][8][0]))))+temp[0])));
        temp[2] = ((mk[8]*((Vpk[1][18][2]*Vpk[3][18][2])+((Vpk[1][16][1]*
          Vpk[3][18][1])+(Vpk[1][18][0]*Vpk[3][18][0]))))+((mk[7]*((
          Vpk[1][17][2]*Vpk[3][17][2])+((Vpk[1][16][1]*Vpk[3][17][1])+(
          Vpk[1][17][0]*Vpk[3][17][0]))))+((mk[6]*((Vpk[1][14][2]*Vpk[3][14][2])
          +((Vpk[1][13][0]*Vpk[3][14][0])+(Vpk[1][14][1]*Vpk[3][14][1]))))+
          temp[1])));
        mm[1][3] = ((mk[9]*((Vpk[1][20][2]*Vpk[3][20][2])+((Vpk[1][19][0]*
          Vpk[3][20][0])+(Vpk[1][20][1]*Vpk[3][20][1]))))+temp[2]);
        temp[0] = ((mk[2]*((Vpk[1][7][2]*Vpk[4][7][2])+((Vpk[1][6][1]*
          Vpk[4][7][1])+(Vpk[1][7][0]*Vpk[4][7][0]))))+((mk[0]*((Vpk[1][5][2]*
          Vpk[4][5][2])+((Vpk[1][4][0]*Vpk[4][5][0])+(Vpk[1][5][1]*Vpk[4][5][1])
          )))+(mk[1]*((Vpk[1][5][2]*Vpk[4][6][2])+((Vpk[1][6][0]*Vpk[4][6][0])+(
          Vpk[1][6][1]*Vpk[4][6][1]))))));
        temp[1] = ((mk[5]*((Vpk[1][12][2]*Vpk[4][12][2])+((Vpk[1][10][1]*
          Vpk[4][12][1])+(Vpk[1][12][0]*Vpk[4][12][0]))))+((mk[4]*((
          Vpk[1][11][2]*Vpk[4][11][2])+((Vpk[1][10][1]*Vpk[4][11][1])+(
          Vpk[1][11][0]*Vpk[4][11][0]))))+((mk[3]*((Vpk[1][8][2]*Vpk[4][8][2])+(
          (Vpk[1][6][1]*Vpk[4][8][1])+(Vpk[1][8][0]*Vpk[4][8][0]))))+temp[0])));
        temp[2] = ((mk[8]*((Vpk[1][18][2]*Vpk[4][18][2])+((Vpk[1][16][1]*
          Vpk[4][18][1])+(Vpk[1][18][0]*Vpk[4][18][0]))))+((mk[7]*((
          Vpk[1][17][2]*Vpk[4][17][2])+((Vpk[1][16][1]*Vpk[4][17][1])+(
          Vpk[1][17][0]*Vpk[4][17][0]))))+((mk[6]*((Vpk[1][14][2]*Vpk[4][14][2])
          +((Vpk[1][13][0]*Vpk[4][14][0])+(Vpk[1][14][1]*Vpk[4][14][1]))))+
          temp[1])));
        mm[1][4] = ((mk[9]*((Vpk[1][20][2]*Vpk[4][20][2])+((Vpk[1][19][0]*
          Vpk[4][20][0])+(Vpk[1][20][1]*Vpk[4][20][1]))))+temp[2]);
        temp[0] = ((mk[3]*((Vpk[1][8][2]*Vpk[5][8][2])+((Vpk[1][6][1]*
          Vpk[5][8][1])+(Vpk[1][8][0]*Vpk[5][8][0]))))+((mk[2]*((Vpk[1][7][2]*
          Vpk[5][7][2])+((Vpk[1][6][1]*Vpk[5][7][1])+(Vpk[1][7][0]*Vpk[5][7][0])
          )))+((mk[0]*((rk[0][2]*Vpk[1][5][1])-(rk[0][1]*Vpk[1][5][2])))+(mk[1]*
          ((Vpk[1][5][2]*Vpk[5][6][2])+((Vpk[1][6][0]*Vpk[5][6][0])+(
          Vpk[1][6][1]*Vpk[5][6][1])))))));
        temp[1] = ((mk[6]*((Vpk[1][14][2]*Vpk[5][14][2])+((Vpk[1][13][0]*
          Vpk[5][14][0])+(Vpk[1][14][1]*Vpk[5][14][1]))))+((mk[5]*((
          Vpk[1][12][2]*Vpk[5][12][2])+((Vpk[1][10][1]*Vpk[5][12][1])+(
          Vpk[1][12][0]*Vpk[5][12][0]))))+((mk[4]*((Vpk[1][11][2]*Vpk[5][11][2])
          +((Vpk[1][10][1]*Vpk[5][11][1])+(Vpk[1][11][0]*Vpk[5][11][0]))))+
          temp[0])));
        mm[1][5] = ((mk[9]*((Vpk[1][20][2]*Vpk[5][20][2])+((Vpk[1][19][0]*
          Vpk[5][20][0])+(Vpk[1][20][1]*Vpk[5][20][1]))))+((mk[8]*((
          Vpk[1][18][2]*Vpk[5][18][2])+((Vpk[1][16][1]*Vpk[5][18][1])+(
          Vpk[1][18][0]*Vpk[5][18][0]))))+((mk[7]*((Vpk[1][17][2]*Vpk[5][17][2])
          +((Vpk[1][16][1]*Vpk[5][17][1])+(Vpk[1][17][0]*Vpk[5][17][0]))))+
          temp[1])));
        mm[1][6] = ((mk[3]*((Vpk[1][8][2]*Vpk[6][8][2])+((Vpk[1][6][1]*
          Vpk[6][8][1])+(Vpk[1][8][0]*Vpk[6][8][0]))))+((mk[1]*((rk[1][1]*
          Vpk[1][6][0])-(rk[1][0]*Vpk[1][6][1])))+(mk[2]*((Vpk[1][7][2]*
          Vpk[6][7][2])+((Vpk[1][6][1]*Vpk[6][7][1])+(Vpk[1][7][0]*Vpk[6][7][0])
          )))));
        mm[1][7] = (mk[2]*((rk[2][0]*Vpk[1][7][2])-(rk[2][2]*Vpk[1][7][0])));
        mm[1][8] = (mk[3]*((rk[3][0]*Vpk[1][8][2])-(rk[3][2]*Vpk[1][8][0])));
        mm[1][9] = ((mk[6]*((Vpk[1][14][2]*Vpk[9][14][2])+((Vpk[1][13][0]*
          Vpk[9][14][0])+(Vpk[1][14][1]*Vpk[9][14][1]))))+((mk[4]*((
          Vpk[1][11][2]*Vpk[9][11][2])+((Vpk[1][10][1]*Vpk[9][11][1])+(
          Vpk[1][11][0]*Vpk[9][11][0]))))+(mk[5]*((Vpk[1][12][2]*Vpk[9][12][2])+
          ((Vpk[1][10][1]*Vpk[9][12][1])+(Vpk[1][12][0]*Vpk[9][12][0]))))));
        mm[1][10] = ((mk[6]*((Vpk[1][14][2]*Vpk[10][14][2])+((Vpk[1][13][0]*
          Vpk[10][14][0])+(Vpk[1][14][1]*Vpk[10][14][1]))))+((mk[4]*((
          Vpk[1][11][2]*Vpk[10][11][2])+((Vpk[1][10][1]*Vpk[10][11][1])+(
          Vpk[1][11][0]*Vpk[10][11][0]))))+(mk[5]*((Vpk[1][12][2]*Vpk[10][12][2]
          )+((Vpk[1][10][1]*Vpk[10][12][1])+(Vpk[1][12][0]*Vpk[10][12][0]))))));
        mm[1][11] = ((mk[6]*((Vpk[1][14][2]*Vpk[11][14][2])+((Vpk[1][13][0]*
          Vpk[11][14][0])+(Vpk[1][14][1]*Vpk[11][14][1]))))+((mk[4]*((rk[4][0]*
          Vpk[1][11][2])-(rk[4][2]*Vpk[1][11][0])))+(mk[5]*((Vpk[1][12][0]*
          Vpk[11][12][0])+(Vpk[1][12][2]*Vpk[11][12][2])))));
        mm[1][12] = ((mk[5]*((rk[5][0]*Vpk[1][12][2])-(rk[5][2]*Vpk[1][12][0])))
          +(mk[6]*((Vpk[1][14][2]*Vpk[12][14][2])+((Vpk[1][13][0]*Vpk[12][14][0]
          )+(Vpk[1][14][1]*Vpk[12][14][1])))));
        mm[1][13] = (mk[6]*((Vpk[1][14][2]*Vpk[13][14][2])+((Vpk[1][13][0]*
          Vpk[13][14][0])+(Vpk[1][14][1]*Vpk[13][14][1]))));
        mm[1][14] = (mk[6]*((rk[6][2]*Vpk[1][14][1])-(rk[6][1]*Vpk[1][14][2])));
        mm[1][15] = ((mk[9]*((Vpk[1][20][2]*Vpk[15][20][2])+((Vpk[1][19][0]*
          Vpk[15][20][0])+(Vpk[1][20][1]*Vpk[15][20][1]))))+((mk[7]*((
          Vpk[1][17][2]*Vpk[15][17][2])+((Vpk[1][16][1]*Vpk[15][17][1])+(
          Vpk[1][17][0]*Vpk[15][17][0]))))+(mk[8]*((Vpk[1][18][2]*Vpk[15][18][2]
          )+((Vpk[1][16][1]*Vpk[15][18][1])+(Vpk[1][18][0]*Vpk[15][18][0]))))));
        mm[1][16] = ((mk[9]*((Vpk[1][20][2]*Vpk[16][20][2])+((Vpk[1][19][0]*
          Vpk[16][20][0])+(Vpk[1][20][1]*Vpk[16][20][1]))))+((mk[7]*((
          Vpk[1][17][2]*Vpk[16][17][2])+((Vpk[1][16][1]*Vpk[16][17][1])+(
          Vpk[1][17][0]*Vpk[16][17][0]))))+(mk[8]*((Vpk[1][18][2]*Vpk[16][18][2]
          )+((Vpk[1][16][1]*Vpk[16][18][1])+(Vpk[1][18][0]*Vpk[16][18][0]))))));
        mm[1][17] = ((mk[9]*((Vpk[1][20][2]*Vpk[17][20][2])+((Vpk[1][19][0]*
          Vpk[17][20][0])+(Vpk[1][20][1]*Vpk[17][20][1]))))+((mk[7]*((rk[7][0]*
          Vpk[1][17][2])-(rk[7][2]*Vpk[1][17][0])))+(mk[8]*((Vpk[1][18][0]*
          Vpk[17][18][0])+(Vpk[1][18][2]*Vpk[17][18][2])))));
        mm[1][18] = ((mk[8]*((rk[8][0]*Vpk[1][18][2])-(rk[8][2]*Vpk[1][18][0])))
          +(mk[9]*((Vpk[1][20][2]*Vpk[18][20][2])+((Vpk[1][19][0]*Vpk[18][20][0]
          )+(Vpk[1][20][1]*Vpk[18][20][1])))));
        mm[1][19] = (mk[9]*((Vpk[1][20][2]*Vpk[19][20][2])+((Vpk[1][19][0]*
          Vpk[19][20][0])+(Vpk[1][20][1]*Vpk[19][20][1]))));
        mm[1][20] = (mk[9]*((rk[9][2]*Vpk[1][20][1])-(rk[9][1]*Vpk[1][20][2])));
        temp[0] = ((mk[2]*((Vpk[2][7][2]*Vpk[2][7][2])+((Vpk[2][6][1]*
          Vpk[2][6][1])+(Vpk[2][7][0]*Vpk[2][7][0]))))+((mk[0]*((Vpk[2][5][2]*
          Vpk[2][5][2])+((Vpk[2][4][0]*Vpk[2][4][0])+(Vpk[2][5][1]*Vpk[2][5][1])
          )))+(mk[1]*((Vpk[2][5][2]*Vpk[2][5][2])+((Vpk[2][6][0]*Vpk[2][6][0])+(
          Vpk[2][6][1]*Vpk[2][6][1]))))));
        temp[1] = ((mk[5]*((Vpk[2][12][2]*Vpk[2][12][2])+((Vpk[2][10][1]*
          Vpk[2][10][1])+(Vpk[2][12][0]*Vpk[2][12][0]))))+((mk[4]*((
          Vpk[2][11][2]*Vpk[2][11][2])+((Vpk[2][10][1]*Vpk[2][10][1])+(
          Vpk[2][11][0]*Vpk[2][11][0]))))+((mk[3]*((Vpk[2][8][2]*Vpk[2][8][2])+(
          (Vpk[2][6][1]*Vpk[2][6][1])+(Vpk[2][8][0]*Vpk[2][8][0]))))+temp[0])));
        temp[2] = ((mk[8]*((Vpk[2][18][2]*Vpk[2][18][2])+((Vpk[2][16][1]*
          Vpk[2][16][1])+(Vpk[2][18][0]*Vpk[2][18][0]))))+((mk[7]*((
          Vpk[2][17][2]*Vpk[2][17][2])+((Vpk[2][16][1]*Vpk[2][16][1])+(
          Vpk[2][17][0]*Vpk[2][17][0]))))+((mk[6]*((Vpk[2][14][2]*Vpk[2][14][2])
          +((Vpk[2][13][0]*Vpk[2][13][0])+(Vpk[2][14][1]*Vpk[2][14][1]))))+
          temp[1])));
        mm[2][2] = ((mk[9]*((Vpk[2][20][2]*Vpk[2][20][2])+((Vpk[2][19][0]*
          Vpk[2][19][0])+(Vpk[2][20][1]*Vpk[2][20][1]))))+temp[2]);
        temp[0] = ((mk[2]*((Vpk[2][7][2]*Vpk[3][7][2])+((Vpk[2][6][1]*
          Vpk[3][7][1])+(Vpk[2][7][0]*Vpk[3][7][0]))))+((mk[0]*((Vpk[2][5][2]*
          Vpk[3][5][2])+((Vpk[2][4][0]*Vpk[3][5][0])+(Vpk[2][5][1]*Vpk[3][5][1])
          )))+(mk[1]*((Vpk[2][5][2]*Vpk[3][6][2])+((Vpk[2][6][0]*Vpk[3][6][0])+(
          Vpk[2][6][1]*Vpk[3][6][1]))))));
        temp[1] = ((mk[5]*((Vpk[2][12][2]*Vpk[3][12][2])+((Vpk[2][10][1]*
          Vpk[3][12][1])+(Vpk[2][12][0]*Vpk[3][12][0]))))+((mk[4]*((
          Vpk[2][11][2]*Vpk[3][11][2])+((Vpk[2][10][1]*Vpk[3][11][1])+(
          Vpk[2][11][0]*Vpk[3][11][0]))))+((mk[3]*((Vpk[2][8][2]*Vpk[3][8][2])+(
          (Vpk[2][6][1]*Vpk[3][8][1])+(Vpk[2][8][0]*Vpk[3][8][0]))))+temp[0])));
        temp[2] = ((mk[8]*((Vpk[2][18][2]*Vpk[3][18][2])+((Vpk[2][16][1]*
          Vpk[3][18][1])+(Vpk[2][18][0]*Vpk[3][18][0]))))+((mk[7]*((
          Vpk[2][17][2]*Vpk[3][17][2])+((Vpk[2][16][1]*Vpk[3][17][1])+(
          Vpk[2][17][0]*Vpk[3][17][0]))))+((mk[6]*((Vpk[2][14][2]*Vpk[3][14][2])
          +((Vpk[2][13][0]*Vpk[3][14][0])+(Vpk[2][14][1]*Vpk[3][14][1]))))+
          temp[1])));
        mm[2][3] = ((mk[9]*((Vpk[2][20][2]*Vpk[3][20][2])+((Vpk[2][19][0]*
          Vpk[3][20][0])+(Vpk[2][20][1]*Vpk[3][20][1]))))+temp[2]);
        temp[0] = ((mk[2]*((Vpk[2][7][2]*Vpk[4][7][2])+((Vpk[2][6][1]*
          Vpk[4][7][1])+(Vpk[2][7][0]*Vpk[4][7][0]))))+((mk[0]*((Vpk[2][5][2]*
          Vpk[4][5][2])+((Vpk[2][4][0]*Vpk[4][5][0])+(Vpk[2][5][1]*Vpk[4][5][1])
          )))+(mk[1]*((Vpk[2][5][2]*Vpk[4][6][2])+((Vpk[2][6][0]*Vpk[4][6][0])+(
          Vpk[2][6][1]*Vpk[4][6][1]))))));
        temp[1] = ((mk[5]*((Vpk[2][12][2]*Vpk[4][12][2])+((Vpk[2][10][1]*
          Vpk[4][12][1])+(Vpk[2][12][0]*Vpk[4][12][0]))))+((mk[4]*((
          Vpk[2][11][2]*Vpk[4][11][2])+((Vpk[2][10][1]*Vpk[4][11][1])+(
          Vpk[2][11][0]*Vpk[4][11][0]))))+((mk[3]*((Vpk[2][8][2]*Vpk[4][8][2])+(
          (Vpk[2][6][1]*Vpk[4][8][1])+(Vpk[2][8][0]*Vpk[4][8][0]))))+temp[0])));
        temp[2] = ((mk[8]*((Vpk[2][18][2]*Vpk[4][18][2])+((Vpk[2][16][1]*
          Vpk[4][18][1])+(Vpk[2][18][0]*Vpk[4][18][0]))))+((mk[7]*((
          Vpk[2][17][2]*Vpk[4][17][2])+((Vpk[2][16][1]*Vpk[4][17][1])+(
          Vpk[2][17][0]*Vpk[4][17][0]))))+((mk[6]*((Vpk[2][14][2]*Vpk[4][14][2])
          +((Vpk[2][13][0]*Vpk[4][14][0])+(Vpk[2][14][1]*Vpk[4][14][1]))))+
          temp[1])));
        mm[2][4] = ((mk[9]*((Vpk[2][20][2]*Vpk[4][20][2])+((Vpk[2][19][0]*
          Vpk[4][20][0])+(Vpk[2][20][1]*Vpk[4][20][1]))))+temp[2]);
        temp[0] = ((mk[3]*((Vpk[2][8][2]*Vpk[5][8][2])+((Vpk[2][6][1]*
          Vpk[5][8][1])+(Vpk[2][8][0]*Vpk[5][8][0]))))+((mk[2]*((Vpk[2][7][2]*
          Vpk[5][7][2])+((Vpk[2][6][1]*Vpk[5][7][1])+(Vpk[2][7][0]*Vpk[5][7][0])
          )))+((mk[0]*((rk[0][2]*Vpk[2][5][1])-(rk[0][1]*Vpk[2][5][2])))+(mk[1]*
          ((Vpk[2][5][2]*Vpk[5][6][2])+((Vpk[2][6][0]*Vpk[5][6][0])+(
          Vpk[2][6][1]*Vpk[5][6][1])))))));
        temp[1] = ((mk[6]*((Vpk[2][14][2]*Vpk[5][14][2])+((Vpk[2][13][0]*
          Vpk[5][14][0])+(Vpk[2][14][1]*Vpk[5][14][1]))))+((mk[5]*((
          Vpk[2][12][2]*Vpk[5][12][2])+((Vpk[2][10][1]*Vpk[5][12][1])+(
          Vpk[2][12][0]*Vpk[5][12][0]))))+((mk[4]*((Vpk[2][11][2]*Vpk[5][11][2])
          +((Vpk[2][10][1]*Vpk[5][11][1])+(Vpk[2][11][0]*Vpk[5][11][0]))))+
          temp[0])));
        mm[2][5] = ((mk[9]*((Vpk[2][20][2]*Vpk[5][20][2])+((Vpk[2][19][0]*
          Vpk[5][20][0])+(Vpk[2][20][1]*Vpk[5][20][1]))))+((mk[8]*((
          Vpk[2][18][2]*Vpk[5][18][2])+((Vpk[2][16][1]*Vpk[5][18][1])+(
          Vpk[2][18][0]*Vpk[5][18][0]))))+((mk[7]*((Vpk[2][17][2]*Vpk[5][17][2])
          +((Vpk[2][16][1]*Vpk[5][17][1])+(Vpk[2][17][0]*Vpk[5][17][0]))))+
          temp[1])));
        mm[2][6] = ((mk[3]*((Vpk[2][8][2]*Vpk[6][8][2])+((Vpk[2][6][1]*
          Vpk[6][8][1])+(Vpk[2][8][0]*Vpk[6][8][0]))))+((mk[1]*((rk[1][1]*
          Vpk[2][6][0])-(rk[1][0]*Vpk[2][6][1])))+(mk[2]*((Vpk[2][7][2]*
          Vpk[6][7][2])+((Vpk[2][6][1]*Vpk[6][7][1])+(Vpk[2][7][0]*Vpk[6][7][0])
          )))));
        mm[2][7] = (mk[2]*((rk[2][0]*Vpk[2][7][2])-(rk[2][2]*Vpk[2][7][0])));
        mm[2][8] = (mk[3]*((rk[3][0]*Vpk[2][8][2])-(rk[3][2]*Vpk[2][8][0])));
        mm[2][9] = ((mk[6]*((Vpk[2][14][2]*Vpk[9][14][2])+((Vpk[2][13][0]*
          Vpk[9][14][0])+(Vpk[2][14][1]*Vpk[9][14][1]))))+((mk[4]*((
          Vpk[2][11][2]*Vpk[9][11][2])+((Vpk[2][10][1]*Vpk[9][11][1])+(
          Vpk[2][11][0]*Vpk[9][11][0]))))+(mk[5]*((Vpk[2][12][2]*Vpk[9][12][2])+
          ((Vpk[2][10][1]*Vpk[9][12][1])+(Vpk[2][12][0]*Vpk[9][12][0]))))));
        mm[2][10] = ((mk[6]*((Vpk[2][14][2]*Vpk[10][14][2])+((Vpk[2][13][0]*
          Vpk[10][14][0])+(Vpk[2][14][1]*Vpk[10][14][1]))))+((mk[4]*((
          Vpk[2][11][2]*Vpk[10][11][2])+((Vpk[2][10][1]*Vpk[10][11][1])+(
          Vpk[2][11][0]*Vpk[10][11][0]))))+(mk[5]*((Vpk[2][12][2]*Vpk[10][12][2]
          )+((Vpk[2][10][1]*Vpk[10][12][1])+(Vpk[2][12][0]*Vpk[10][12][0]))))));
        mm[2][11] = ((mk[6]*((Vpk[2][14][2]*Vpk[11][14][2])+((Vpk[2][13][0]*
          Vpk[11][14][0])+(Vpk[2][14][1]*Vpk[11][14][1]))))+((mk[4]*((rk[4][0]*
          Vpk[2][11][2])-(rk[4][2]*Vpk[2][11][0])))+(mk[5]*((Vpk[2][12][0]*
          Vpk[11][12][0])+(Vpk[2][12][2]*Vpk[11][12][2])))));
        mm[2][12] = ((mk[5]*((rk[5][0]*Vpk[2][12][2])-(rk[5][2]*Vpk[2][12][0])))
          +(mk[6]*((Vpk[2][14][2]*Vpk[12][14][2])+((Vpk[2][13][0]*Vpk[12][14][0]
          )+(Vpk[2][14][1]*Vpk[12][14][1])))));
        mm[2][13] = (mk[6]*((Vpk[2][14][2]*Vpk[13][14][2])+((Vpk[2][13][0]*
          Vpk[13][14][0])+(Vpk[2][14][1]*Vpk[13][14][1]))));
        mm[2][14] = (mk[6]*((rk[6][2]*Vpk[2][14][1])-(rk[6][1]*Vpk[2][14][2])));
        mm[2][15] = ((mk[9]*((Vpk[2][20][2]*Vpk[15][20][2])+((Vpk[2][19][0]*
          Vpk[15][20][0])+(Vpk[2][20][1]*Vpk[15][20][1]))))+((mk[7]*((
          Vpk[2][17][2]*Vpk[15][17][2])+((Vpk[2][16][1]*Vpk[15][17][1])+(
          Vpk[2][17][0]*Vpk[15][17][0]))))+(mk[8]*((Vpk[2][18][2]*Vpk[15][18][2]
          )+((Vpk[2][16][1]*Vpk[15][18][1])+(Vpk[2][18][0]*Vpk[15][18][0]))))));
        mm[2][16] = ((mk[9]*((Vpk[2][20][2]*Vpk[16][20][2])+((Vpk[2][19][0]*
          Vpk[16][20][0])+(Vpk[2][20][1]*Vpk[16][20][1]))))+((mk[7]*((
          Vpk[2][17][2]*Vpk[16][17][2])+((Vpk[2][16][1]*Vpk[16][17][1])+(
          Vpk[2][17][0]*Vpk[16][17][0]))))+(mk[8]*((Vpk[2][18][2]*Vpk[16][18][2]
          )+((Vpk[2][16][1]*Vpk[16][18][1])+(Vpk[2][18][0]*Vpk[16][18][0]))))));
        mm[2][17] = ((mk[9]*((Vpk[2][20][2]*Vpk[17][20][2])+((Vpk[2][19][0]*
          Vpk[17][20][0])+(Vpk[2][20][1]*Vpk[17][20][1]))))+((mk[7]*((rk[7][0]*
          Vpk[2][17][2])-(rk[7][2]*Vpk[2][17][0])))+(mk[8]*((Vpk[2][18][0]*
          Vpk[17][18][0])+(Vpk[2][18][2]*Vpk[17][18][2])))));
        mm[2][18] = ((mk[8]*((rk[8][0]*Vpk[2][18][2])-(rk[8][2]*Vpk[2][18][0])))
          +(mk[9]*((Vpk[2][20][2]*Vpk[18][20][2])+((Vpk[2][19][0]*Vpk[18][20][0]
          )+(Vpk[2][20][1]*Vpk[18][20][1])))));
        mm[2][19] = (mk[9]*((Vpk[2][20][2]*Vpk[19][20][2])+((Vpk[2][19][0]*
          Vpk[19][20][0])+(Vpk[2][20][1]*Vpk[19][20][1]))));
        mm[2][20] = (mk[9]*((rk[9][2]*Vpk[2][20][1])-(rk[9][1]*Vpk[2][20][2])));
        temp[0] = (((mk[0]*((Vpk[3][5][2]*Vpk[3][5][2])+((Vpk[3][5][0]*
          Vpk[3][5][0])+(Vpk[3][5][1]*Vpk[3][5][1]))))+((IkWpk[3][5][2]*
          Wpk[3][5][2])+((IkWpk[3][5][1]*Wpk[3][5][1])-(IkWpk[3][5][0]*s4))))+((
          mk[1]*((Vpk[3][6][2]*Vpk[3][6][2])+((Vpk[3][6][0]*Vpk[3][6][0])+(
          Vpk[3][6][1]*Vpk[3][6][1]))))+((IkWpk[3][6][2]*Wpk[3][5][2])+((
          IkWpk[3][6][0]*Wpk[3][6][0])+(IkWpk[3][6][1]*Wpk[3][6][1])))));
        temp[1] = (((mk[2]*((Vpk[3][7][2]*Vpk[3][7][2])+((Vpk[3][7][0]*
          Vpk[3][7][0])+(Vpk[3][7][1]*Vpk[3][7][1]))))+((IkWpk[3][7][2]*
          Wpk[3][7][2])+((IkWpk[3][7][0]*Wpk[3][7][0])+(IkWpk[3][7][1]*
          Wpk[3][6][1]))))+temp[0]);
        temp[2] = (((mk[3]*((Vpk[3][8][2]*Vpk[3][8][2])+((Vpk[3][8][0]*
          Vpk[3][8][0])+(Vpk[3][8][1]*Vpk[3][8][1]))))+((IkWpk[3][8][2]*
          Wpk[3][8][2])+((IkWpk[3][8][0]*Wpk[3][8][0])+(IkWpk[3][8][1]*
          Wpk[3][6][1]))))+temp[1]);
        temp[3] = (((mk[4]*((Vpk[3][11][2]*Vpk[3][11][2])+((Vpk[3][11][0]*
          Vpk[3][11][0])+(Vpk[3][11][1]*Vpk[3][11][1]))))+((IkWpk[3][11][2]*
          Wpk[3][11][2])+((IkWpk[3][11][0]*Wpk[3][11][0])+(IkWpk[3][11][1]*
          Wpk[3][10][1]))))+temp[2]);
        temp[4] = (((mk[5]*((Vpk[3][12][2]*Vpk[3][12][2])+((Vpk[3][12][0]*
          Vpk[3][12][0])+(Vpk[3][12][1]*Vpk[3][12][1]))))+((IkWpk[3][12][2]*
          Wpk[3][12][2])+((IkWpk[3][12][0]*Wpk[3][12][0])+(IkWpk[3][12][1]*
          Wpk[3][10][1]))))+temp[3]);
        temp[5] = (((mk[6]*((Vpk[3][14][2]*Vpk[3][14][2])+((Vpk[3][14][0]*
          Vpk[3][14][0])+(Vpk[3][14][1]*Vpk[3][14][1]))))+((IkWpk[3][14][2]*
          Wpk[3][14][2])+((IkWpk[3][14][0]*Wpk[3][13][0])+(IkWpk[3][14][1]*
          Wpk[3][14][1]))))+temp[4]);
        temp[6] = (((mk[7]*((Vpk[3][17][2]*Vpk[3][17][2])+((Vpk[3][17][0]*
          Vpk[3][17][0])+(Vpk[3][17][1]*Vpk[3][17][1]))))+((IkWpk[3][17][2]*
          Wpk[3][17][2])+((IkWpk[3][17][0]*Wpk[3][17][0])+(IkWpk[3][17][1]*
          Wpk[3][16][1]))))+temp[5]);
        temp[7] = (((mk[8]*((Vpk[3][18][2]*Vpk[3][18][2])+((Vpk[3][18][0]*
          Vpk[3][18][0])+(Vpk[3][18][1]*Vpk[3][18][1]))))+((IkWpk[3][18][2]*
          Wpk[3][18][2])+((IkWpk[3][18][0]*Wpk[3][18][0])+(IkWpk[3][18][1]*
          Wpk[3][16][1]))))+temp[6]);
        mm[3][3] = (((mk[9]*((Vpk[3][20][2]*Vpk[3][20][2])+((Vpk[3][20][0]*
          Vpk[3][20][0])+(Vpk[3][20][1]*Vpk[3][20][1]))))+((IkWpk[3][20][2]*
          Wpk[3][20][2])+((IkWpk[3][20][0]*Wpk[3][19][0])+(IkWpk[3][20][1]*
          Wpk[3][20][1]))))+temp[7]);
        temp[0] = (((mk[0]*((Vpk[3][5][2]*Vpk[4][5][2])+((Vpk[3][5][0]*
          Vpk[4][5][0])+(Vpk[3][5][1]*Vpk[4][5][1]))))+((IkWpk[4][5][1]*
          Wpk[3][5][1])+(IkWpk[4][5][2]*Wpk[3][5][2])))+((mk[1]*((Vpk[3][6][2]*
          Vpk[4][6][2])+((Vpk[3][6][0]*Vpk[4][6][0])+(Vpk[3][6][1]*Vpk[4][6][1])
          )))+((IkWpk[4][6][2]*Wpk[3][5][2])+((IkWpk[4][6][0]*Wpk[3][6][0])+(
          IkWpk[4][6][1]*Wpk[3][6][1])))));
        temp[1] = (((mk[2]*((Vpk[3][7][2]*Vpk[4][7][2])+((Vpk[3][7][0]*
          Vpk[4][7][0])+(Vpk[3][7][1]*Vpk[4][7][1]))))+((IkWpk[4][7][2]*
          Wpk[3][7][2])+((IkWpk[4][7][0]*Wpk[3][7][0])+(IkWpk[4][7][1]*
          Wpk[3][6][1]))))+temp[0]);
        temp[2] = (((mk[3]*((Vpk[3][8][2]*Vpk[4][8][2])+((Vpk[3][8][0]*
          Vpk[4][8][0])+(Vpk[3][8][1]*Vpk[4][8][1]))))+((IkWpk[4][8][2]*
          Wpk[3][8][2])+((IkWpk[4][8][0]*Wpk[3][8][0])+(IkWpk[4][8][1]*
          Wpk[3][6][1]))))+temp[1]);
        temp[3] = (((mk[4]*((Vpk[3][11][2]*Vpk[4][11][2])+((Vpk[3][11][0]*
          Vpk[4][11][0])+(Vpk[3][11][1]*Vpk[4][11][1]))))+((IkWpk[4][11][2]*
          Wpk[3][11][2])+((IkWpk[4][11][0]*Wpk[3][11][0])+(IkWpk[4][11][1]*
          Wpk[3][10][1]))))+temp[2]);
        temp[4] = (((mk[5]*((Vpk[3][12][2]*Vpk[4][12][2])+((Vpk[3][12][0]*
          Vpk[4][12][0])+(Vpk[3][12][1]*Vpk[4][12][1]))))+((IkWpk[4][12][2]*
          Wpk[3][12][2])+((IkWpk[4][12][0]*Wpk[3][12][0])+(IkWpk[4][12][1]*
          Wpk[3][10][1]))))+temp[3]);
        temp[5] = (((mk[6]*((Vpk[3][14][2]*Vpk[4][14][2])+((Vpk[3][14][0]*
          Vpk[4][14][0])+(Vpk[3][14][1]*Vpk[4][14][1]))))+((IkWpk[4][14][2]*
          Wpk[3][14][2])+((IkWpk[4][14][0]*Wpk[3][13][0])+(IkWpk[4][14][1]*
          Wpk[3][14][1]))))+temp[4]);
        temp[6] = (((mk[7]*((Vpk[3][17][2]*Vpk[4][17][2])+((Vpk[3][17][0]*
          Vpk[4][17][0])+(Vpk[3][17][1]*Vpk[4][17][1]))))+((IkWpk[4][17][2]*
          Wpk[3][17][2])+((IkWpk[4][17][0]*Wpk[3][17][0])+(IkWpk[4][17][1]*
          Wpk[3][16][1]))))+temp[5]);
        temp[7] = (((mk[8]*((Vpk[3][18][2]*Vpk[4][18][2])+((Vpk[3][18][0]*
          Vpk[4][18][0])+(Vpk[3][18][1]*Vpk[4][18][1]))))+((IkWpk[4][18][2]*
          Wpk[3][18][2])+((IkWpk[4][18][0]*Wpk[3][18][0])+(IkWpk[4][18][1]*
          Wpk[3][16][1]))))+temp[6]);
        mm[3][4] = (((mk[9]*((Vpk[3][20][2]*Vpk[4][20][2])+((Vpk[3][20][0]*
          Vpk[4][20][0])+(Vpk[3][20][1]*Vpk[4][20][1]))))+((IkWpk[4][20][2]*
          Wpk[3][20][2])+((IkWpk[4][20][0]*Wpk[3][19][0])+(IkWpk[4][20][1]*
          Wpk[3][20][1]))))+temp[7]);
        temp[0] = (((mk[0]*((rk[0][2]*Vpk[3][5][1])-(rk[0][1]*Vpk[3][5][2])))-(
          ik[0][0][0]*s4))+((mk[1]*((Vpk[3][6][2]*Vpk[5][6][2])+((Vpk[3][6][0]*
          Vpk[5][6][0])+(Vpk[3][6][1]*Vpk[5][6][1]))))+((IkWpk[5][6][0]*
          Wpk[3][6][0])+(IkWpk[5][6][1]*Wpk[3][6][1]))));
        temp[1] = (((mk[2]*((Vpk[3][7][2]*Vpk[5][7][2])+((Vpk[3][7][0]*
          Vpk[5][7][0])+(Vpk[3][7][1]*Vpk[5][7][1]))))+((IkWpk[5][7][2]*
          Wpk[3][7][2])+((IkWpk[5][7][0]*Wpk[3][7][0])+(IkWpk[5][7][1]*
          Wpk[3][6][1]))))+temp[0]);
        temp[2] = (((mk[3]*((Vpk[3][8][2]*Vpk[5][8][2])+((Vpk[3][8][0]*
          Vpk[5][8][0])+(Vpk[3][8][1]*Vpk[5][8][1]))))+((IkWpk[5][8][2]*
          Wpk[3][8][2])+((IkWpk[5][8][0]*Wpk[3][8][0])+(IkWpk[5][8][1]*
          Wpk[3][6][1]))))+temp[1]);
        temp[3] = (((mk[4]*((Vpk[3][11][2]*Vpk[5][11][2])+((Vpk[3][11][0]*
          Vpk[5][11][0])+(Vpk[3][11][1]*Vpk[5][11][1]))))+((IkWpk[5][11][2]*
          Wpk[3][11][2])+((IkWpk[5][11][0]*Wpk[3][11][0])+(IkWpk[5][11][1]*
          Wpk[3][10][1]))))+temp[2]);
        temp[4] = (((mk[5]*((Vpk[3][12][2]*Vpk[5][12][2])+((Vpk[3][12][0]*
          Vpk[5][12][0])+(Vpk[3][12][1]*Vpk[5][12][1]))))+((IkWpk[5][12][2]*
          Wpk[3][12][2])+((IkWpk[5][12][0]*Wpk[3][12][0])+(IkWpk[5][12][1]*
          Wpk[3][10][1]))))+temp[3]);
        temp[5] = (((mk[6]*((Vpk[3][14][2]*Vpk[5][14][2])+((Vpk[3][14][0]*
          Vpk[5][14][0])+(Vpk[3][14][1]*Vpk[5][14][1]))))+((IkWpk[5][14][2]*
          Wpk[3][14][2])+((IkWpk[5][14][0]*Wpk[3][13][0])+(IkWpk[5][14][1]*
          Wpk[3][14][1]))))+temp[4]);
        temp[6] = (((mk[7]*((Vpk[3][17][2]*Vpk[5][17][2])+((Vpk[3][17][0]*
          Vpk[5][17][0])+(Vpk[3][17][1]*Vpk[5][17][1]))))+((IkWpk[5][17][2]*
          Wpk[3][17][2])+((IkWpk[5][17][0]*Wpk[3][17][0])+(IkWpk[5][17][1]*
          Wpk[3][16][1]))))+temp[5]);
        temp[7] = (((mk[8]*((Vpk[3][18][2]*Vpk[5][18][2])+((Vpk[3][18][0]*
          Vpk[5][18][0])+(Vpk[3][18][1]*Vpk[5][18][1]))))+((IkWpk[5][18][2]*
          Wpk[3][18][2])+((IkWpk[5][18][0]*Wpk[3][18][0])+(IkWpk[5][18][1]*
          Wpk[3][16][1]))))+temp[6]);
        mm[3][5] = (((mk[9]*((Vpk[3][20][2]*Vpk[5][20][2])+((Vpk[3][20][0]*
          Vpk[5][20][0])+(Vpk[3][20][1]*Vpk[5][20][1]))))+((IkWpk[5][20][2]*
          Wpk[3][20][2])+((IkWpk[5][20][0]*Wpk[3][19][0])+(IkWpk[5][20][1]*
          Wpk[3][20][1]))))+temp[7]);
        temp[0] = (((ik[1][2][2]*Wpk[3][5][2])+(mk[1]*((rk[1][1]*Vpk[3][6][0])-(
          rk[1][0]*Vpk[3][6][1]))))+((mk[2]*((Vpk[3][7][2]*Vpk[6][7][2])+((
          Vpk[3][7][0]*Vpk[6][7][0])+(Vpk[3][7][1]*Vpk[6][7][1]))))+((
          IkWpk[6][7][0]*Wpk[3][7][0])+(IkWpk[6][7][2]*Wpk[3][7][2]))));
        mm[3][6] = (((mk[3]*((Vpk[3][8][2]*Vpk[6][8][2])+((Vpk[3][8][0]*
          Vpk[6][8][0])+(Vpk[3][8][1]*Vpk[6][8][1]))))+((IkWpk[6][8][0]*
          Wpk[3][8][0])+(IkWpk[6][8][2]*Wpk[3][8][2])))+temp[0]);
        mm[3][7] = ((ik[2][1][1]*Wpk[3][6][1])+(mk[2]*((rk[2][0]*Vpk[3][7][2])-(
          rk[2][2]*Vpk[3][7][0]))));
        mm[3][8] = ((ik[3][1][1]*Wpk[3][6][1])+(mk[3]*((rk[3][0]*Vpk[3][8][2])-(
          rk[3][2]*Vpk[3][8][0]))));
        temp[0] = (((mk[4]*((Vpk[3][11][2]*Vpk[9][11][2])+((Vpk[3][11][0]*
          Vpk[9][11][0])+(Vpk[3][11][1]*Vpk[9][11][1]))))+((IkWpk[9][11][2]*
          Wpk[3][11][2])+((IkWpk[9][11][0]*Wpk[3][11][0])+(IkWpk[9][11][1]*
          Wpk[3][10][1]))))+((mk[5]*((Vpk[3][12][2]*Vpk[9][12][2])+((
          Vpk[3][12][0]*Vpk[9][12][0])+(Vpk[3][12][1]*Vpk[9][12][1]))))+((
          IkWpk[9][12][2]*Wpk[3][12][2])+((IkWpk[9][12][0]*Wpk[3][12][0])+(
          IkWpk[9][12][1]*Wpk[3][10][1])))));
        mm[3][9] = (((mk[6]*((Vpk[3][14][2]*Vpk[9][14][2])+((Vpk[3][14][0]*
          Vpk[9][14][0])+(Vpk[3][14][1]*Vpk[9][14][1]))))+((IkWpk[9][14][2]*
          Wpk[3][14][2])+((IkWpk[9][14][0]*Wpk[3][13][0])+(IkWpk[9][14][1]*
          Wpk[3][14][1]))))+temp[0]);
        temp[0] = (((mk[4]*((Vpk[3][11][2]*Vpk[10][11][2])+((Vpk[3][11][0]*
          Vpk[10][11][0])+(Vpk[3][11][1]*Vpk[10][11][1]))))+((IkWpk[10][11][0]*
          Wpk[3][11][0])+(IkWpk[10][11][2]*Wpk[3][11][2])))+((mk[5]*((
          Vpk[3][12][2]*Vpk[10][12][2])+((Vpk[3][12][0]*Vpk[10][12][0])+(
          Vpk[3][12][1]*Vpk[10][12][1]))))+((IkWpk[10][12][0]*Wpk[3][12][0])+(
          IkWpk[10][12][2]*Wpk[3][12][2]))));
        mm[3][10] = (((mk[6]*((Vpk[3][14][2]*Vpk[10][14][2])+((Vpk[3][14][0]*
          Vpk[10][14][0])+(Vpk[3][14][1]*Vpk[10][14][1]))))+((IkWpk[10][14][2]*
          Wpk[3][14][2])+((IkWpk[10][14][0]*Wpk[3][13][0])+(IkWpk[10][14][1]*
          Wpk[3][14][1]))))+temp[0]);
        mm[3][11] = (((mk[6]*((Vpk[3][14][2]*Vpk[11][14][2])+((Vpk[3][14][0]*
          Vpk[11][14][0])+(Vpk[3][14][1]*Vpk[11][14][1]))))+((IkWpk[11][14][1]*
          Wpk[3][14][1])+(IkWpk[11][14][2]*Wpk[3][14][2])))+(((ik[4][1][1]*
          Wpk[3][10][1])+(mk[4]*((rk[4][0]*Vpk[3][11][2])-(rk[4][2]*
          Vpk[3][11][0]))))+((ik[5][1][1]*Wpk[3][10][1])+(mk[5]*((Vpk[3][12][0]*
          Vpk[11][12][0])+(Vpk[3][12][2]*Vpk[11][12][2]))))));
        mm[3][12] = (((ik[5][1][1]*Wpk[3][10][1])+(mk[5]*((rk[5][0]*
          Vpk[3][12][2])-(rk[5][2]*Vpk[3][12][0]))))+((mk[6]*((Vpk[3][14][2]*
          Vpk[12][14][2])+((Vpk[3][14][0]*Vpk[12][14][0])+(Vpk[3][14][1]*
          Vpk[12][14][1]))))+((IkWpk[12][14][1]*Wpk[3][14][1])+(IkWpk[12][14][2]
          *Wpk[3][14][2]))));
        mm[3][13] = ((mk[6]*((Vpk[3][14][2]*Vpk[13][14][2])+((Vpk[3][14][0]*
          Vpk[13][14][0])+(Vpk[3][14][1]*Vpk[13][14][1]))))+((IkWpk[13][14][1]*
          Wpk[3][14][1])+(IkWpk[13][14][2]*Wpk[3][14][2])));
        mm[3][14] = ((ik[6][0][0]*Wpk[3][13][0])+(mk[6]*((rk[6][2]*Vpk[3][14][1]
          )-(rk[6][1]*Vpk[3][14][2]))));
        temp[0] = (((mk[7]*((Vpk[3][17][2]*Vpk[15][17][2])+((Vpk[3][17][0]*
          Vpk[15][17][0])+(Vpk[3][17][1]*Vpk[15][17][1]))))+((IkWpk[15][17][2]*
          Wpk[3][17][2])+((IkWpk[15][17][0]*Wpk[3][17][0])+(IkWpk[15][17][1]*
          Wpk[3][16][1]))))+((mk[8]*((Vpk[3][18][2]*Vpk[15][18][2])+((
          Vpk[3][18][0]*Vpk[15][18][0])+(Vpk[3][18][1]*Vpk[15][18][1]))))+((
          IkWpk[15][18][2]*Wpk[3][18][2])+((IkWpk[15][18][0]*Wpk[3][18][0])+(
          IkWpk[15][18][1]*Wpk[3][16][1])))));
        mm[3][15] = (((mk[9]*((Vpk[3][20][2]*Vpk[15][20][2])+((Vpk[3][20][0]*
          Vpk[15][20][0])+(Vpk[3][20][1]*Vpk[15][20][1]))))+((IkWpk[15][20][2]*
          Wpk[3][20][2])+((IkWpk[15][20][0]*Wpk[3][19][0])+(IkWpk[15][20][1]*
          Wpk[3][20][1]))))+temp[0]);
        temp[0] = (((mk[7]*((Vpk[3][17][2]*Vpk[16][17][2])+((Vpk[3][17][0]*
          Vpk[16][17][0])+(Vpk[3][17][1]*Vpk[16][17][1]))))+((IkWpk[16][17][0]*
          Wpk[3][17][0])+(IkWpk[16][17][2]*Wpk[3][17][2])))+((mk[8]*((
          Vpk[3][18][2]*Vpk[16][18][2])+((Vpk[3][18][0]*Vpk[16][18][0])+(
          Vpk[3][18][1]*Vpk[16][18][1]))))+((IkWpk[16][18][0]*Wpk[3][18][0])+(
          IkWpk[16][18][2]*Wpk[3][18][2]))));
        mm[3][16] = (((mk[9]*((Vpk[3][20][2]*Vpk[16][20][2])+((Vpk[3][20][0]*
          Vpk[16][20][0])+(Vpk[3][20][1]*Vpk[16][20][1]))))+((IkWpk[16][20][2]*
          Wpk[3][20][2])+((IkWpk[16][20][0]*Wpk[3][19][0])+(IkWpk[16][20][1]*
          Wpk[3][20][1]))))+temp[0]);
        mm[3][17] = (((mk[9]*((Vpk[3][20][2]*Vpk[17][20][2])+((Vpk[3][20][0]*
          Vpk[17][20][0])+(Vpk[3][20][1]*Vpk[17][20][1]))))+((IkWpk[17][20][1]*
          Wpk[3][20][1])+(IkWpk[17][20][2]*Wpk[3][20][2])))+(((ik[7][1][1]*
          Wpk[3][16][1])+(mk[7]*((rk[7][0]*Vpk[3][17][2])-(rk[7][2]*
          Vpk[3][17][0]))))+((ik[8][1][1]*Wpk[3][16][1])+(mk[8]*((Vpk[3][18][0]*
          Vpk[17][18][0])+(Vpk[3][18][2]*Vpk[17][18][2]))))));
        mm[3][18] = (((ik[8][1][1]*Wpk[3][16][1])+(mk[8]*((rk[8][0]*
          Vpk[3][18][2])-(rk[8][2]*Vpk[3][18][0]))))+((mk[9]*((Vpk[3][20][2]*
          Vpk[18][20][2])+((Vpk[3][20][0]*Vpk[18][20][0])+(Vpk[3][20][1]*
          Vpk[18][20][1]))))+((IkWpk[18][20][1]*Wpk[3][20][1])+(IkWpk[18][20][2]
          *Wpk[3][20][2]))));
        mm[3][19] = ((mk[9]*((Vpk[3][20][2]*Vpk[19][20][2])+((Vpk[3][20][0]*
          Vpk[19][20][0])+(Vpk[3][20][1]*Vpk[19][20][1]))))+((IkWpk[19][20][1]*
          Wpk[3][20][1])+(IkWpk[19][20][2]*Wpk[3][20][2])));
        mm[3][20] = ((ik[9][0][0]*Wpk[3][19][0])+(mk[9]*((rk[9][2]*Vpk[3][20][1]
          )-(rk[9][1]*Vpk[3][20][2]))));
        temp[0] = (((mk[0]*((Vpk[4][5][2]*Vpk[4][5][2])+((Vpk[4][5][0]*
          Vpk[4][5][0])+(Vpk[4][5][1]*Vpk[4][5][1]))))+((IkWpk[4][5][1]*c5)-(
          IkWpk[4][5][2]*s5)))+((mk[1]*((Vpk[4][6][2]*Vpk[4][6][2])+((
          Vpk[4][6][0]*Vpk[4][6][0])+(Vpk[4][6][1]*Vpk[4][6][1]))))+(((
          IkWpk[4][6][0]*Wpk[4][6][0])+(IkWpk[4][6][1]*Wpk[4][6][1]))-(
          IkWpk[4][6][2]*s5))));
        temp[1] = (((mk[2]*((Vpk[4][7][2]*Vpk[4][7][2])+((Vpk[4][7][0]*
          Vpk[4][7][0])+(Vpk[4][7][1]*Vpk[4][7][1]))))+((IkWpk[4][7][2]*
          Wpk[4][7][2])+((IkWpk[4][7][0]*Wpk[4][7][0])+(IkWpk[4][7][1]*
          Wpk[4][6][1]))))+temp[0]);
        temp[2] = (((mk[3]*((Vpk[4][8][2]*Vpk[4][8][2])+((Vpk[4][8][0]*
          Vpk[4][8][0])+(Vpk[4][8][1]*Vpk[4][8][1]))))+((IkWpk[4][8][2]*
          Wpk[4][8][2])+((IkWpk[4][8][0]*Wpk[4][8][0])+(IkWpk[4][8][1]*
          Wpk[4][6][1]))))+temp[1]);
        temp[3] = (((mk[4]*((Vpk[4][11][2]*Vpk[4][11][2])+((Vpk[4][11][0]*
          Vpk[4][11][0])+(Vpk[4][11][1]*Vpk[4][11][1]))))+((IkWpk[4][11][2]*
          Wpk[4][11][2])+((IkWpk[4][11][0]*Wpk[4][11][0])+(IkWpk[4][11][1]*
          Wpk[4][10][1]))))+temp[2]);
        temp[4] = (((mk[5]*((Vpk[4][12][2]*Vpk[4][12][2])+((Vpk[4][12][0]*
          Vpk[4][12][0])+(Vpk[4][12][1]*Vpk[4][12][1]))))+((IkWpk[4][12][2]*
          Wpk[4][12][2])+((IkWpk[4][12][0]*Wpk[4][12][0])+(IkWpk[4][12][1]*
          Wpk[4][10][1]))))+temp[3]);
        temp[5] = (((mk[6]*((Vpk[4][14][2]*Vpk[4][14][2])+((Vpk[4][14][0]*
          Vpk[4][14][0])+(Vpk[4][14][1]*Vpk[4][14][1]))))+((IkWpk[4][14][2]*
          Wpk[4][14][2])+((IkWpk[4][14][0]*Wpk[4][13][0])+(IkWpk[4][14][1]*
          Wpk[4][14][1]))))+temp[4]);
        temp[6] = (((mk[7]*((Vpk[4][17][2]*Vpk[4][17][2])+((Vpk[4][17][0]*
          Vpk[4][17][0])+(Vpk[4][17][1]*Vpk[4][17][1]))))+((IkWpk[4][17][2]*
          Wpk[4][17][2])+((IkWpk[4][17][0]*Wpk[4][17][0])+(IkWpk[4][17][1]*
          Wpk[4][16][1]))))+temp[5]);
        temp[7] = (((mk[8]*((Vpk[4][18][2]*Vpk[4][18][2])+((Vpk[4][18][0]*
          Vpk[4][18][0])+(Vpk[4][18][1]*Vpk[4][18][1]))))+((IkWpk[4][18][2]*
          Wpk[4][18][2])+((IkWpk[4][18][0]*Wpk[4][18][0])+(IkWpk[4][18][1]*
          Wpk[4][16][1]))))+temp[6]);
        mm[4][4] = (((mk[9]*((Vpk[4][20][2]*Vpk[4][20][2])+((Vpk[4][20][0]*
          Vpk[4][20][0])+(Vpk[4][20][1]*Vpk[4][20][1]))))+((IkWpk[4][20][2]*
          Wpk[4][20][2])+((IkWpk[4][20][0]*Wpk[4][19][0])+(IkWpk[4][20][1]*
          Wpk[4][20][1]))))+temp[7]);
        temp[0] = ((mk[0]*((rk[0][2]*Vpk[4][5][1])-(rk[0][1]*Vpk[4][5][2])))+((
          mk[1]*((Vpk[4][6][2]*Vpk[5][6][2])+((Vpk[4][6][0]*Vpk[5][6][0])+(
          Vpk[4][6][1]*Vpk[5][6][1]))))+((IkWpk[5][6][0]*Wpk[4][6][0])+(
          IkWpk[5][6][1]*Wpk[4][6][1]))));
        temp[1] = (temp[0]+((mk[2]*((Vpk[4][7][2]*Vpk[5][7][2])+((Vpk[4][7][0]*
          Vpk[5][7][0])+(Vpk[4][7][1]*Vpk[5][7][1]))))+((IkWpk[5][7][2]*
          Wpk[4][7][2])+((IkWpk[5][7][0]*Wpk[4][7][0])+(IkWpk[5][7][1]*
          Wpk[4][6][1])))));
        temp[2] = (((mk[3]*((Vpk[4][8][2]*Vpk[5][8][2])+((Vpk[4][8][0]*
          Vpk[5][8][0])+(Vpk[4][8][1]*Vpk[5][8][1]))))+((IkWpk[5][8][2]*
          Wpk[4][8][2])+((IkWpk[5][8][0]*Wpk[4][8][0])+(IkWpk[5][8][1]*
          Wpk[4][6][1]))))+temp[1]);
        temp[3] = (((mk[4]*((Vpk[4][11][2]*Vpk[5][11][2])+((Vpk[4][11][0]*
          Vpk[5][11][0])+(Vpk[4][11][1]*Vpk[5][11][1]))))+((IkWpk[5][11][2]*
          Wpk[4][11][2])+((IkWpk[5][11][0]*Wpk[4][11][0])+(IkWpk[5][11][1]*
          Wpk[4][10][1]))))+temp[2]);
        temp[4] = (((mk[5]*((Vpk[4][12][2]*Vpk[5][12][2])+((Vpk[4][12][0]*
          Vpk[5][12][0])+(Vpk[4][12][1]*Vpk[5][12][1]))))+((IkWpk[5][12][2]*
          Wpk[4][12][2])+((IkWpk[5][12][0]*Wpk[4][12][0])+(IkWpk[5][12][1]*
          Wpk[4][10][1]))))+temp[3]);
        temp[5] = (((mk[6]*((Vpk[4][14][2]*Vpk[5][14][2])+((Vpk[4][14][0]*
          Vpk[5][14][0])+(Vpk[4][14][1]*Vpk[5][14][1]))))+((IkWpk[5][14][2]*
          Wpk[4][14][2])+((IkWpk[5][14][0]*Wpk[4][13][0])+(IkWpk[5][14][1]*
          Wpk[4][14][1]))))+temp[4]);
        temp[6] = (((mk[7]*((Vpk[4][17][2]*Vpk[5][17][2])+((Vpk[4][17][0]*
          Vpk[5][17][0])+(Vpk[4][17][1]*Vpk[5][17][1]))))+((IkWpk[5][17][2]*
          Wpk[4][17][2])+((IkWpk[5][17][0]*Wpk[4][17][0])+(IkWpk[5][17][1]*
          Wpk[4][16][1]))))+temp[5]);
        temp[7] = (((mk[8]*((Vpk[4][18][2]*Vpk[5][18][2])+((Vpk[4][18][0]*
          Vpk[5][18][0])+(Vpk[4][18][1]*Vpk[5][18][1]))))+((IkWpk[5][18][2]*
          Wpk[4][18][2])+((IkWpk[5][18][0]*Wpk[4][18][0])+(IkWpk[5][18][1]*
          Wpk[4][16][1]))))+temp[6]);
        mm[4][5] = (((mk[9]*((Vpk[4][20][2]*Vpk[5][20][2])+((Vpk[4][20][0]*
          Vpk[5][20][0])+(Vpk[4][20][1]*Vpk[5][20][1]))))+((IkWpk[5][20][2]*
          Wpk[4][20][2])+((IkWpk[5][20][0]*Wpk[4][19][0])+(IkWpk[5][20][1]*
          Wpk[4][20][1]))))+temp[7]);
        temp[0] = (((mk[1]*((rk[1][1]*Vpk[4][6][0])-(rk[1][0]*Vpk[4][6][1])))-(
          ik[1][2][2]*s5))+((mk[2]*((Vpk[4][7][2]*Vpk[6][7][2])+((Vpk[4][7][0]*
          Vpk[6][7][0])+(Vpk[4][7][1]*Vpk[6][7][1]))))+((IkWpk[6][7][0]*
          Wpk[4][7][0])+(IkWpk[6][7][2]*Wpk[4][7][2]))));
        mm[4][6] = (((mk[3]*((Vpk[4][8][2]*Vpk[6][8][2])+((Vpk[4][8][0]*
          Vpk[6][8][0])+(Vpk[4][8][1]*Vpk[6][8][1]))))+((IkWpk[6][8][0]*
          Wpk[4][8][0])+(IkWpk[6][8][2]*Wpk[4][8][2])))+temp[0]);
        mm[4][7] = ((ik[2][1][1]*Wpk[4][6][1])+(mk[2]*((rk[2][0]*Vpk[4][7][2])-(
          rk[2][2]*Vpk[4][7][0]))));
        mm[4][8] = ((ik[3][1][1]*Wpk[4][6][1])+(mk[3]*((rk[3][0]*Vpk[4][8][2])-(
          rk[3][2]*Vpk[4][8][0]))));
        temp[0] = (((mk[4]*((Vpk[4][11][2]*Vpk[9][11][2])+((Vpk[4][11][0]*
          Vpk[9][11][0])+(Vpk[4][11][1]*Vpk[9][11][1]))))+((IkWpk[9][11][2]*
          Wpk[4][11][2])+((IkWpk[9][11][0]*Wpk[4][11][0])+(IkWpk[9][11][1]*
          Wpk[4][10][1]))))+((mk[5]*((Vpk[4][12][2]*Vpk[9][12][2])+((
          Vpk[4][12][0]*Vpk[9][12][0])+(Vpk[4][12][1]*Vpk[9][12][1]))))+((
          IkWpk[9][12][2]*Wpk[4][12][2])+((IkWpk[9][12][0]*Wpk[4][12][0])+(
          IkWpk[9][12][1]*Wpk[4][10][1])))));
        mm[4][9] = (((mk[6]*((Vpk[4][14][2]*Vpk[9][14][2])+((Vpk[4][14][0]*
          Vpk[9][14][0])+(Vpk[4][14][1]*Vpk[9][14][1]))))+((IkWpk[9][14][2]*
          Wpk[4][14][2])+((IkWpk[9][14][0]*Wpk[4][13][0])+(IkWpk[9][14][1]*
          Wpk[4][14][1]))))+temp[0]);
        temp[0] = (((mk[4]*((Vpk[4][11][2]*Vpk[10][11][2])+((Vpk[4][11][0]*
          Vpk[10][11][0])+(Vpk[4][11][1]*Vpk[10][11][1]))))+((IkWpk[10][11][0]*
          Wpk[4][11][0])+(IkWpk[10][11][2]*Wpk[4][11][2])))+((mk[5]*((
          Vpk[4][12][2]*Vpk[10][12][2])+((Vpk[4][12][0]*Vpk[10][12][0])+(
          Vpk[4][12][1]*Vpk[10][12][1]))))+((IkWpk[10][12][0]*Wpk[4][12][0])+(
          IkWpk[10][12][2]*Wpk[4][12][2]))));
        mm[4][10] = (((mk[6]*((Vpk[4][14][2]*Vpk[10][14][2])+((Vpk[4][14][0]*
          Vpk[10][14][0])+(Vpk[4][14][1]*Vpk[10][14][1]))))+((IkWpk[10][14][2]*
          Wpk[4][14][2])+((IkWpk[10][14][0]*Wpk[4][13][0])+(IkWpk[10][14][1]*
          Wpk[4][14][1]))))+temp[0]);
        mm[4][11] = (((mk[6]*((Vpk[4][14][2]*Vpk[11][14][2])+((Vpk[4][14][0]*
          Vpk[11][14][0])+(Vpk[4][14][1]*Vpk[11][14][1]))))+((IkWpk[11][14][1]*
          Wpk[4][14][1])+(IkWpk[11][14][2]*Wpk[4][14][2])))+(((ik[4][1][1]*
          Wpk[4][10][1])+(mk[4]*((rk[4][0]*Vpk[4][11][2])-(rk[4][2]*
          Vpk[4][11][0]))))+((ik[5][1][1]*Wpk[4][10][1])+(mk[5]*((Vpk[4][12][0]*
          Vpk[11][12][0])+(Vpk[4][12][2]*Vpk[11][12][2]))))));
        mm[4][12] = (((ik[5][1][1]*Wpk[4][10][1])+(mk[5]*((rk[5][0]*
          Vpk[4][12][2])-(rk[5][2]*Vpk[4][12][0]))))+((mk[6]*((Vpk[4][14][2]*
          Vpk[12][14][2])+((Vpk[4][14][0]*Vpk[12][14][0])+(Vpk[4][14][1]*
          Vpk[12][14][1]))))+((IkWpk[12][14][1]*Wpk[4][14][1])+(IkWpk[12][14][2]
          *Wpk[4][14][2]))));
        mm[4][13] = ((mk[6]*((Vpk[4][14][2]*Vpk[13][14][2])+((Vpk[4][14][0]*
          Vpk[13][14][0])+(Vpk[4][14][1]*Vpk[13][14][1]))))+((IkWpk[13][14][1]*
          Wpk[4][14][1])+(IkWpk[13][14][2]*Wpk[4][14][2])));
        mm[4][14] = ((ik[6][0][0]*Wpk[4][13][0])+(mk[6]*((rk[6][2]*Vpk[4][14][1]
          )-(rk[6][1]*Vpk[4][14][2]))));
        temp[0] = (((mk[7]*((Vpk[4][17][2]*Vpk[15][17][2])+((Vpk[4][17][0]*
          Vpk[15][17][0])+(Vpk[4][17][1]*Vpk[15][17][1]))))+((IkWpk[15][17][2]*
          Wpk[4][17][2])+((IkWpk[15][17][0]*Wpk[4][17][0])+(IkWpk[15][17][1]*
          Wpk[4][16][1]))))+((mk[8]*((Vpk[4][18][2]*Vpk[15][18][2])+((
          Vpk[4][18][0]*Vpk[15][18][0])+(Vpk[4][18][1]*Vpk[15][18][1]))))+((
          IkWpk[15][18][2]*Wpk[4][18][2])+((IkWpk[15][18][0]*Wpk[4][18][0])+(
          IkWpk[15][18][1]*Wpk[4][16][1])))));
        mm[4][15] = (((mk[9]*((Vpk[4][20][2]*Vpk[15][20][2])+((Vpk[4][20][0]*
          Vpk[15][20][0])+(Vpk[4][20][1]*Vpk[15][20][1]))))+((IkWpk[15][20][2]*
          Wpk[4][20][2])+((IkWpk[15][20][0]*Wpk[4][19][0])+(IkWpk[15][20][1]*
          Wpk[4][20][1]))))+temp[0]);
        temp[0] = (((mk[7]*((Vpk[4][17][2]*Vpk[16][17][2])+((Vpk[4][17][0]*
          Vpk[16][17][0])+(Vpk[4][17][1]*Vpk[16][17][1]))))+((IkWpk[16][17][0]*
          Wpk[4][17][0])+(IkWpk[16][17][2]*Wpk[4][17][2])))+((mk[8]*((
          Vpk[4][18][2]*Vpk[16][18][2])+((Vpk[4][18][0]*Vpk[16][18][0])+(
          Vpk[4][18][1]*Vpk[16][18][1]))))+((IkWpk[16][18][0]*Wpk[4][18][0])+(
          IkWpk[16][18][2]*Wpk[4][18][2]))));
        mm[4][16] = (((mk[9]*((Vpk[4][20][2]*Vpk[16][20][2])+((Vpk[4][20][0]*
          Vpk[16][20][0])+(Vpk[4][20][1]*Vpk[16][20][1]))))+((IkWpk[16][20][2]*
          Wpk[4][20][2])+((IkWpk[16][20][0]*Wpk[4][19][0])+(IkWpk[16][20][1]*
          Wpk[4][20][1]))))+temp[0]);
        mm[4][17] = (((mk[9]*((Vpk[4][20][2]*Vpk[17][20][2])+((Vpk[4][20][0]*
          Vpk[17][20][0])+(Vpk[4][20][1]*Vpk[17][20][1]))))+((IkWpk[17][20][1]*
          Wpk[4][20][1])+(IkWpk[17][20][2]*Wpk[4][20][2])))+(((ik[7][1][1]*
          Wpk[4][16][1])+(mk[7]*((rk[7][0]*Vpk[4][17][2])-(rk[7][2]*
          Vpk[4][17][0]))))+((ik[8][1][1]*Wpk[4][16][1])+(mk[8]*((Vpk[4][18][0]*
          Vpk[17][18][0])+(Vpk[4][18][2]*Vpk[17][18][2]))))));
        mm[4][18] = (((ik[8][1][1]*Wpk[4][16][1])+(mk[8]*((rk[8][0]*
          Vpk[4][18][2])-(rk[8][2]*Vpk[4][18][0]))))+((mk[9]*((Vpk[4][20][2]*
          Vpk[18][20][2])+((Vpk[4][20][0]*Vpk[18][20][0])+(Vpk[4][20][1]*
          Vpk[18][20][1]))))+((IkWpk[18][20][1]*Wpk[4][20][1])+(IkWpk[18][20][2]
          *Wpk[4][20][2]))));
        mm[4][19] = ((mk[9]*((Vpk[4][20][2]*Vpk[19][20][2])+((Vpk[4][20][0]*
          Vpk[19][20][0])+(Vpk[4][20][1]*Vpk[19][20][1]))))+((IkWpk[19][20][1]*
          Wpk[4][20][1])+(IkWpk[19][20][2]*Wpk[4][20][2])));
        mm[4][20] = ((ik[9][0][0]*Wpk[4][19][0])+(mk[9]*((rk[9][2]*Vpk[4][20][1]
          )-(rk[9][1]*Vpk[4][20][2]))));
        temp[0] = ((ik[0][0][0]+(mk[0]*((rk[0][1]*rk[0][1])+(rk[0][2]*rk[0][2]))
          ))+((mk[1]*((Vpk[5][6][2]*Vpk[5][6][2])+((Vpk[5][6][0]*Vpk[5][6][0])+(
          Vpk[5][6][1]*Vpk[5][6][1]))))+((IkWpk[5][6][0]*c6)-(IkWpk[5][6][1]*s6)
          )));
        temp[1] = (((mk[3]*((Vpk[5][8][2]*Vpk[5][8][2])+((Vpk[5][8][0]*
          Vpk[5][8][0])+(Vpk[5][8][1]*Vpk[5][8][1]))))+((IkWpk[5][8][2]*
          Wpk[5][8][2])+((IkWpk[5][8][0]*Wpk[5][8][0])-(IkWpk[5][8][1]*s6))))+(
          temp[0]+((mk[2]*((Vpk[5][7][2]*Vpk[5][7][2])+((Vpk[5][7][0]*
          Vpk[5][7][0])+(Vpk[5][7][1]*Vpk[5][7][1]))))+((IkWpk[5][7][2]*
          Wpk[5][7][2])+((IkWpk[5][7][0]*Wpk[5][7][0])-(IkWpk[5][7][1]*s6))))));
        temp[2] = (((mk[4]*((Vpk[5][11][2]*Vpk[5][11][2])+((Vpk[5][11][0]*
          Vpk[5][11][0])+(Vpk[5][11][1]*Vpk[5][11][1]))))+((IkWpk[5][11][2]*
          Wpk[5][11][2])+((IkWpk[5][11][0]*Wpk[5][11][0])+(IkWpk[5][11][1]*
          Wpk[5][10][1]))))+temp[1]);
        temp[3] = (((mk[5]*((Vpk[5][12][2]*Vpk[5][12][2])+((Vpk[5][12][0]*
          Vpk[5][12][0])+(Vpk[5][12][1]*Vpk[5][12][1]))))+((IkWpk[5][12][2]*
          Wpk[5][12][2])+((IkWpk[5][12][0]*Wpk[5][12][0])+(IkWpk[5][12][1]*
          Wpk[5][10][1]))))+temp[2]);
        temp[4] = (((mk[6]*((Vpk[5][14][2]*Vpk[5][14][2])+((Vpk[5][14][0]*
          Vpk[5][14][0])+(Vpk[5][14][1]*Vpk[5][14][1]))))+((IkWpk[5][14][2]*
          Wpk[5][14][2])+((IkWpk[5][14][0]*Wpk[5][13][0])+(IkWpk[5][14][1]*
          Wpk[5][14][1]))))+temp[3]);
        temp[5] = (((mk[7]*((Vpk[5][17][2]*Vpk[5][17][2])+((Vpk[5][17][0]*
          Vpk[5][17][0])+(Vpk[5][17][1]*Vpk[5][17][1]))))+((IkWpk[5][17][2]*
          Wpk[5][17][2])+((IkWpk[5][17][0]*Wpk[5][17][0])+(IkWpk[5][17][1]*
          Wpk[5][16][1]))))+temp[4]);
        temp[6] = (((mk[8]*((Vpk[5][18][2]*Vpk[5][18][2])+((Vpk[5][18][0]*
          Vpk[5][18][0])+(Vpk[5][18][1]*Vpk[5][18][1]))))+((IkWpk[5][18][2]*
          Wpk[5][18][2])+((IkWpk[5][18][0]*Wpk[5][18][0])+(IkWpk[5][18][1]*
          Wpk[5][16][1]))))+temp[5]);
        mm[5][5] = (((mk[9]*((Vpk[5][20][2]*Vpk[5][20][2])+((Vpk[5][20][0]*
          Vpk[5][20][0])+(Vpk[5][20][1]*Vpk[5][20][1]))))+((IkWpk[5][20][2]*
          Wpk[5][20][2])+((IkWpk[5][20][0]*Wpk[5][19][0])+(IkWpk[5][20][1]*
          Wpk[5][20][1]))))+temp[6]);
        mm[5][6] = (((mk[1]*((rk[1][1]*Vpk[5][6][0])-(rk[1][0]*Vpk[5][6][1])))+(
          (mk[2]*((Vpk[5][7][2]*Vpk[6][7][2])+((Vpk[5][7][0]*Vpk[6][7][0])+(
          Vpk[5][7][1]*Vpk[6][7][1]))))+((IkWpk[6][7][0]*Wpk[5][7][0])+(
          IkWpk[6][7][2]*Wpk[5][7][2]))))+((mk[3]*((Vpk[5][8][2]*Vpk[6][8][2])+(
          (Vpk[5][8][0]*Vpk[6][8][0])+(Vpk[5][8][1]*Vpk[6][8][1]))))+((
          IkWpk[6][8][0]*Wpk[5][8][0])+(IkWpk[6][8][2]*Wpk[5][8][2]))));
        mm[5][7] = ((mk[2]*((rk[2][0]*Vpk[5][7][2])-(rk[2][2]*Vpk[5][7][0])))-(
          ik[2][1][1]*s6));
        mm[5][8] = ((mk[3]*((rk[3][0]*Vpk[5][8][2])-(rk[3][2]*Vpk[5][8][0])))-(
          ik[3][1][1]*s6));
        temp[0] = (((mk[4]*((Vpk[5][11][2]*Vpk[9][11][2])+((Vpk[5][11][0]*
          Vpk[9][11][0])+(Vpk[5][11][1]*Vpk[9][11][1]))))+((IkWpk[9][11][2]*
          Wpk[5][11][2])+((IkWpk[9][11][0]*Wpk[5][11][0])+(IkWpk[9][11][1]*
          Wpk[5][10][1]))))+((mk[5]*((Vpk[5][12][2]*Vpk[9][12][2])+((
          Vpk[5][12][0]*Vpk[9][12][0])+(Vpk[5][12][1]*Vpk[9][12][1]))))+((
          IkWpk[9][12][2]*Wpk[5][12][2])+((IkWpk[9][12][0]*Wpk[5][12][0])+(
          IkWpk[9][12][1]*Wpk[5][10][1])))));
        mm[5][9] = (((mk[6]*((Vpk[5][14][2]*Vpk[9][14][2])+((Vpk[5][14][0]*
          Vpk[9][14][0])+(Vpk[5][14][1]*Vpk[9][14][1]))))+((IkWpk[9][14][2]*
          Wpk[5][14][2])+((IkWpk[9][14][0]*Wpk[5][13][0])+(IkWpk[9][14][1]*
          Wpk[5][14][1]))))+temp[0]);
        temp[0] = (((mk[4]*((Vpk[5][11][2]*Vpk[10][11][2])+((Vpk[5][11][0]*
          Vpk[10][11][0])+(Vpk[5][11][1]*Vpk[10][11][1]))))+((IkWpk[10][11][0]*
          Wpk[5][11][0])+(IkWpk[10][11][2]*Wpk[5][11][2])))+((mk[5]*((
          Vpk[5][12][2]*Vpk[10][12][2])+((Vpk[5][12][0]*Vpk[10][12][0])+(
          Vpk[5][12][1]*Vpk[10][12][1]))))+((IkWpk[10][12][0]*Wpk[5][12][0])+(
          IkWpk[10][12][2]*Wpk[5][12][2]))));
        mm[5][10] = (((mk[6]*((Vpk[5][14][2]*Vpk[10][14][2])+((Vpk[5][14][0]*
          Vpk[10][14][0])+(Vpk[5][14][1]*Vpk[10][14][1]))))+((IkWpk[10][14][2]*
          Wpk[5][14][2])+((IkWpk[10][14][0]*Wpk[5][13][0])+(IkWpk[10][14][1]*
          Wpk[5][14][1]))))+temp[0]);
        mm[5][11] = (((mk[6]*((Vpk[5][14][2]*Vpk[11][14][2])+((Vpk[5][14][0]*
          Vpk[11][14][0])+(Vpk[5][14][1]*Vpk[11][14][1]))))+((IkWpk[11][14][1]*
          Wpk[5][14][1])+(IkWpk[11][14][2]*Wpk[5][14][2])))+(((ik[4][1][1]*
          Wpk[5][10][1])+(mk[4]*((rk[4][0]*Vpk[5][11][2])-(rk[4][2]*
          Vpk[5][11][0]))))+((ik[5][1][1]*Wpk[5][10][1])+(mk[5]*((Vpk[5][12][0]*
          Vpk[11][12][0])+(Vpk[5][12][2]*Vpk[11][12][2]))))));
        mm[5][12] = (((ik[5][1][1]*Wpk[5][10][1])+(mk[5]*((rk[5][0]*
          Vpk[5][12][2])-(rk[5][2]*Vpk[5][12][0]))))+((mk[6]*((Vpk[5][14][2]*
          Vpk[12][14][2])+((Vpk[5][14][0]*Vpk[12][14][0])+(Vpk[5][14][1]*
          Vpk[12][14][1]))))+((IkWpk[12][14][1]*Wpk[5][14][1])+(IkWpk[12][14][2]
          *Wpk[5][14][2]))));
        mm[5][13] = ((mk[6]*((Vpk[5][14][2]*Vpk[13][14][2])+((Vpk[5][14][0]*
          Vpk[13][14][0])+(Vpk[5][14][1]*Vpk[13][14][1]))))+((IkWpk[13][14][1]*
          Wpk[5][14][1])+(IkWpk[13][14][2]*Wpk[5][14][2])));
        mm[5][14] = ((ik[6][0][0]*Wpk[5][13][0])+(mk[6]*((rk[6][2]*Vpk[5][14][1]
          )-(rk[6][1]*Vpk[5][14][2]))));
        temp[0] = (((mk[7]*((Vpk[5][17][2]*Vpk[15][17][2])+((Vpk[5][17][0]*
          Vpk[15][17][0])+(Vpk[5][17][1]*Vpk[15][17][1]))))+((IkWpk[15][17][2]*
          Wpk[5][17][2])+((IkWpk[15][17][0]*Wpk[5][17][0])+(IkWpk[15][17][1]*
          Wpk[5][16][1]))))+((mk[8]*((Vpk[5][18][2]*Vpk[15][18][2])+((
          Vpk[5][18][0]*Vpk[15][18][0])+(Vpk[5][18][1]*Vpk[15][18][1]))))+((
          IkWpk[15][18][2]*Wpk[5][18][2])+((IkWpk[15][18][0]*Wpk[5][18][0])+(
          IkWpk[15][18][1]*Wpk[5][16][1])))));
        mm[5][15] = (((mk[9]*((Vpk[5][20][2]*Vpk[15][20][2])+((Vpk[5][20][0]*
          Vpk[15][20][0])+(Vpk[5][20][1]*Vpk[15][20][1]))))+((IkWpk[15][20][2]*
          Wpk[5][20][2])+((IkWpk[15][20][0]*Wpk[5][19][0])+(IkWpk[15][20][1]*
          Wpk[5][20][1]))))+temp[0]);
        temp[0] = (((mk[7]*((Vpk[5][17][2]*Vpk[16][17][2])+((Vpk[5][17][0]*
          Vpk[16][17][0])+(Vpk[5][17][1]*Vpk[16][17][1]))))+((IkWpk[16][17][0]*
          Wpk[5][17][0])+(IkWpk[16][17][2]*Wpk[5][17][2])))+((mk[8]*((
          Vpk[5][18][2]*Vpk[16][18][2])+((Vpk[5][18][0]*Vpk[16][18][0])+(
          Vpk[5][18][1]*Vpk[16][18][1]))))+((IkWpk[16][18][0]*Wpk[5][18][0])+(
          IkWpk[16][18][2]*Wpk[5][18][2]))));
        mm[5][16] = (((mk[9]*((Vpk[5][20][2]*Vpk[16][20][2])+((Vpk[5][20][0]*
          Vpk[16][20][0])+(Vpk[5][20][1]*Vpk[16][20][1]))))+((IkWpk[16][20][2]*
          Wpk[5][20][2])+((IkWpk[16][20][0]*Wpk[5][19][0])+(IkWpk[16][20][1]*
          Wpk[5][20][1]))))+temp[0]);
        mm[5][17] = (((mk[9]*((Vpk[5][20][2]*Vpk[17][20][2])+((Vpk[5][20][0]*
          Vpk[17][20][0])+(Vpk[5][20][1]*Vpk[17][20][1]))))+((IkWpk[17][20][1]*
          Wpk[5][20][1])+(IkWpk[17][20][2]*Wpk[5][20][2])))+(((ik[7][1][1]*
          Wpk[5][16][1])+(mk[7]*((rk[7][0]*Vpk[5][17][2])-(rk[7][2]*
          Vpk[5][17][0]))))+((ik[8][1][1]*Wpk[5][16][1])+(mk[8]*((Vpk[5][18][0]*
          Vpk[17][18][0])+(Vpk[5][18][2]*Vpk[17][18][2]))))));
        mm[5][18] = (((ik[8][1][1]*Wpk[5][16][1])+(mk[8]*((rk[8][0]*
          Vpk[5][18][2])-(rk[8][2]*Vpk[5][18][0]))))+((mk[9]*((Vpk[5][20][2]*
          Vpk[18][20][2])+((Vpk[5][20][0]*Vpk[18][20][0])+(Vpk[5][20][1]*
          Vpk[18][20][1]))))+((IkWpk[18][20][1]*Wpk[5][20][1])+(IkWpk[18][20][2]
          *Wpk[5][20][2]))));
        mm[5][19] = ((mk[9]*((Vpk[5][20][2]*Vpk[19][20][2])+((Vpk[5][20][0]*
          Vpk[19][20][0])+(Vpk[5][20][1]*Vpk[19][20][1]))))+((IkWpk[19][20][1]*
          Wpk[5][20][1])+(IkWpk[19][20][2]*Wpk[5][20][2])));
        mm[5][20] = ((ik[9][0][0]*Wpk[5][19][0])+(mk[9]*((rk[9][2]*Vpk[5][20][1]
          )-(rk[9][1]*Vpk[5][20][2]))));
        mm[6][6] = (((ik[1][2][2]+(mk[1]*((rk[1][0]*rk[1][0])+(rk[1][1]*rk[1][1]
          ))))+((mk[2]*((Vpk[6][7][2]*Vpk[6][7][2])+((Vpk[6][7][0]*Vpk[6][7][0])
          +(Vpk[6][7][1]*Vpk[6][7][1]))))+((IkWpk[6][7][2]*c7)-(IkWpk[6][7][0]*
          s7))))+((mk[3]*((Vpk[6][8][2]*Vpk[6][8][2])+((Vpk[6][8][0]*
          Vpk[6][8][0])+(Vpk[6][8][1]*Vpk[6][8][1]))))+((IkWpk[6][8][2]*c8)-(
          IkWpk[6][8][0]*s8))));
        mm[6][7] = (mk[2]*((rk[2][0]*Vpk[6][7][2])-(rk[2][2]*Vpk[6][7][0])));
        mm[6][8] = (mk[3]*((rk[3][0]*Vpk[6][8][2])-(rk[3][2]*Vpk[6][8][0])));
        mm[6][9] = 0.;
        mm[6][10] = 0.;
        mm[6][11] = 0.;
        mm[6][12] = 0.;
        mm[6][13] = 0.;
        mm[6][14] = 0.;
        mm[6][15] = 0.;
        mm[6][16] = 0.;
        mm[6][17] = 0.;
        mm[6][18] = 0.;
        mm[6][19] = 0.;
        mm[6][20] = 0.;
        mm[7][7] = (ik[2][1][1]+(mk[2]*((rk[2][0]*rk[2][0])+(rk[2][2]*rk[2][2]))
          ));
        mm[7][8] = 0.;
        mm[7][9] = 0.;
        mm[7][10] = 0.;
        mm[7][11] = 0.;
        mm[7][12] = 0.;
        mm[7][13] = 0.;
        mm[7][14] = 0.;
        mm[7][15] = 0.;
        mm[7][16] = 0.;
        mm[7][17] = 0.;
        mm[7][18] = 0.;
        mm[7][19] = 0.;
        mm[7][20] = 0.;
        mm[8][8] = (ik[3][1][1]+(mk[3]*((rk[3][0]*rk[3][0])+(rk[3][2]*rk[3][2]))
          ));
        mm[8][9] = 0.;
        mm[8][10] = 0.;
        mm[8][11] = 0.;
        mm[8][12] = 0.;
        mm[8][13] = 0.;
        mm[8][14] = 0.;
        mm[8][15] = 0.;
        mm[8][16] = 0.;
        mm[8][17] = 0.;
        mm[8][18] = 0.;
        mm[8][19] = 0.;
        mm[8][20] = 0.;
        temp[0] = (((mk[4]*((Vpk[9][11][2]*Vpk[9][11][2])+((Vpk[9][11][0]*
          Vpk[9][11][0])+(Vpk[9][11][1]*Vpk[9][11][1]))))+((IkWpk[9][11][2]*
          Wpk[9][11][2])+((IkWpk[9][11][0]*Wpk[9][11][0])+(IkWpk[9][11][1]*s10))
          ))+((mk[5]*((Vpk[9][12][2]*Vpk[9][12][2])+((Vpk[9][12][0]*
          Vpk[9][12][0])+(Vpk[9][12][1]*Vpk[9][12][1]))))+((IkWpk[9][12][2]*
          Wpk[9][12][2])+((IkWpk[9][12][0]*Wpk[9][12][0])+(IkWpk[9][12][1]*s10))
          )));
        mm[9][9] = (((mk[6]*((Vpk[9][14][2]*Vpk[9][14][2])+((Vpk[9][14][0]*
          Vpk[9][14][0])+(Vpk[9][14][1]*Vpk[9][14][1]))))+((IkWpk[9][14][2]*
          Wpk[9][14][2])+((IkWpk[9][14][0]*Wpk[9][13][0])+(IkWpk[9][14][1]*
          Wpk[9][14][1]))))+temp[0]);
        temp[0] = (((mk[4]*((Vpk[9][11][2]*Vpk[10][11][2])+((Vpk[9][11][0]*
          Vpk[10][11][0])+(Vpk[9][11][1]*Vpk[10][11][1]))))+((IkWpk[10][11][0]*
          Wpk[9][11][0])+(IkWpk[10][11][2]*Wpk[9][11][2])))+((mk[5]*((
          Vpk[9][12][2]*Vpk[10][12][2])+((Vpk[9][12][0]*Vpk[10][12][0])+(
          Vpk[9][12][1]*Vpk[10][12][1]))))+((IkWpk[10][12][0]*Wpk[9][12][0])+(
          IkWpk[10][12][2]*Wpk[9][12][2]))));
        mm[9][10] = (((mk[6]*((Vpk[9][14][2]*Vpk[10][14][2])+((Vpk[9][14][0]*
          Vpk[10][14][0])+(Vpk[9][14][1]*Vpk[10][14][1]))))+((IkWpk[10][14][2]*
          Wpk[9][14][2])+((IkWpk[10][14][0]*Wpk[9][13][0])+(IkWpk[10][14][1]*
          Wpk[9][14][1]))))+temp[0]);
        mm[9][11] = (((mk[6]*((Vpk[9][14][2]*Vpk[11][14][2])+((Vpk[9][14][0]*
          Vpk[11][14][0])+(Vpk[9][14][1]*Vpk[11][14][1]))))+((IkWpk[11][14][1]*
          Wpk[9][14][1])+(IkWpk[11][14][2]*Wpk[9][14][2])))+(((ik[4][1][1]*s10)+
          (mk[4]*((rk[4][0]*Vpk[9][11][2])-(rk[4][2]*Vpk[9][11][0]))))+((
          ik[5][1][1]*s10)+(mk[5]*((Vpk[9][12][0]*Vpk[11][12][0])+(Vpk[9][12][2]
          *Vpk[11][12][2]))))));
        mm[9][12] = (((ik[5][1][1]*s10)+(mk[5]*((rk[5][0]*Vpk[9][12][2])-(
          rk[5][2]*Vpk[9][12][0]))))+((mk[6]*((Vpk[9][14][2]*Vpk[12][14][2])+((
          Vpk[9][14][0]*Vpk[12][14][0])+(Vpk[9][14][1]*Vpk[12][14][1]))))+((
          IkWpk[12][14][1]*Wpk[9][14][1])+(IkWpk[12][14][2]*Wpk[9][14][2]))));
        mm[9][13] = ((mk[6]*((Vpk[9][14][2]*Vpk[13][14][2])+((Vpk[9][14][0]*
          Vpk[13][14][0])+(Vpk[9][14][1]*Vpk[13][14][1]))))+((IkWpk[13][14][1]*
          Wpk[9][14][1])+(IkWpk[13][14][2]*Wpk[9][14][2])));
        mm[9][14] = ((ik[6][0][0]*Wpk[9][13][0])+(mk[6]*((rk[6][2]*Vpk[9][14][1]
          )-(rk[6][1]*Vpk[9][14][2]))));
        mm[9][15] = 0.;
        mm[9][16] = 0.;
        mm[9][17] = 0.;
        mm[9][18] = 0.;
        mm[9][19] = 0.;
        mm[9][20] = 0.;
        temp[0] = (((mk[4]*((Vpk[10][11][2]*Vpk[10][11][2])+((Vpk[10][11][0]*
          Vpk[10][11][0])+(Vpk[10][11][1]*Vpk[10][11][1]))))+((IkWpk[10][11][0]*
          c11)+(IkWpk[10][11][2]*s11)))+((mk[5]*((Vpk[10][12][2]*Vpk[10][12][2])
          +((Vpk[10][12][0]*Vpk[10][12][0])+(Vpk[10][12][1]*Vpk[10][12][1]))))+(
          (IkWpk[10][12][0]*Wpk[10][12][0])+(IkWpk[10][12][2]*Wpk[10][12][2]))))
          ;
        mm[10][10] = (((mk[6]*((Vpk[10][14][2]*Vpk[10][14][2])+((Vpk[10][14][0]*
          Vpk[10][14][0])+(Vpk[10][14][1]*Vpk[10][14][1]))))+((IkWpk[10][14][2]*
          Wpk[10][14][2])+((IkWpk[10][14][0]*Wpk[10][13][0])+(IkWpk[10][14][1]*
          Wpk[10][14][1]))))+temp[0]);
        mm[10][11] = (((mk[4]*((rk[4][0]*Vpk[10][11][2])-(rk[4][2]*
          Vpk[10][11][0])))+(mk[5]*((Vpk[10][12][0]*Vpk[11][12][0])+(
          Vpk[10][12][2]*Vpk[11][12][2]))))+((mk[6]*((Vpk[10][14][2]*
          Vpk[11][14][2])+((Vpk[10][14][0]*Vpk[11][14][0])+(Vpk[10][14][1]*
          Vpk[11][14][1]))))+((IkWpk[11][14][1]*Wpk[10][14][1])+(
          IkWpk[11][14][2]*Wpk[10][14][2]))));
        mm[10][12] = ((mk[5]*((rk[5][0]*Vpk[10][12][2])-(rk[5][2]*Vpk[10][12][0]
          )))+((mk[6]*((Vpk[10][14][2]*Vpk[12][14][2])+((Vpk[10][14][0]*
          Vpk[12][14][0])+(Vpk[10][14][1]*Vpk[12][14][1]))))+((IkWpk[12][14][1]*
          Wpk[10][14][1])+(IkWpk[12][14][2]*Wpk[10][14][2]))));
        mm[10][13] = ((mk[6]*((Vpk[10][14][2]*Vpk[13][14][2])+((Vpk[10][14][0]*
          Vpk[13][14][0])+(Vpk[10][14][1]*Vpk[13][14][1]))))+((IkWpk[13][14][1]*
          Wpk[10][14][1])+(IkWpk[13][14][2]*Wpk[10][14][2])));
        mm[10][14] = ((ik[6][0][0]*Wpk[10][13][0])+(mk[6]*((rk[6][2]*
          Vpk[10][14][1])-(rk[6][1]*Vpk[10][14][2]))));
        mm[10][15] = 0.;
        mm[10][16] = 0.;
        mm[10][17] = 0.;
        mm[10][18] = 0.;
        mm[10][19] = 0.;
        mm[10][20] = 0.;
        mm[11][11] = (((ik[4][1][1]+(mk[4]*((rk[4][0]*rk[4][0])+(rk[4][2]*
          rk[4][2]))))+(ik[5][1][1]+(mk[5]*((Vpk[11][12][0]*Vpk[11][12][0])+(
          Vpk[11][12][2]*Vpk[11][12][2])))))+((mk[6]*((Vpk[11][14][2]*
          Vpk[11][14][2])+((Vpk[11][14][0]*Vpk[11][14][0])+(Vpk[11][14][1]*
          Vpk[11][14][1]))))+((IkWpk[11][14][1]*c14)-(IkWpk[11][14][2]*s14))));
        mm[11][12] = ((ik[5][1][1]+(mk[5]*((rk[5][0]*Vpk[11][12][2])-(rk[5][2]*
          Vpk[11][12][0]))))+((mk[6]*((Vpk[11][14][2]*Vpk[12][14][2])+((
          Vpk[11][14][0]*Vpk[12][14][0])+(Vpk[11][14][1]*Vpk[12][14][1]))))+((
          IkWpk[12][14][1]*c14)-(IkWpk[12][14][2]*s14))));
        mm[11][13] = ((mk[6]*((Vpk[11][14][2]*Vpk[13][14][2])+((Vpk[11][14][0]*
          Vpk[13][14][0])+(Vpk[11][14][1]*Vpk[13][14][1]))))+((IkWpk[13][14][1]*
          c14)-(IkWpk[13][14][2]*s14)));
        mm[11][14] = (mk[6]*((rk[6][2]*Vpk[11][14][1])-(rk[6][1]*Vpk[11][14][2])
          ));
        mm[11][15] = 0.;
        mm[11][16] = 0.;
        mm[11][17] = 0.;
        mm[11][18] = 0.;
        mm[11][19] = 0.;
        mm[11][20] = 0.;
        mm[12][12] = ((ik[5][1][1]+(mk[5]*((rk[5][0]*rk[5][0])+(rk[5][2]*
          rk[5][2]))))+((mk[6]*((Vpk[12][14][2]*Vpk[12][14][2])+((Vpk[12][14][0]
          *Vpk[12][14][0])+(Vpk[12][14][1]*Vpk[12][14][1]))))+((IkWpk[12][14][1]
          *c14)-(IkWpk[12][14][2]*s14))));
        mm[12][13] = ((mk[6]*((Vpk[12][14][2]*Vpk[13][14][2])+((Vpk[12][14][0]*
          Vpk[13][14][0])+(Vpk[12][14][1]*Vpk[13][14][1]))))+((IkWpk[13][14][1]*
          c14)-(IkWpk[13][14][2]*s14)));
        mm[12][14] = (mk[6]*((rk[6][2]*Vpk[12][14][1])-(rk[6][1]*Vpk[12][14][2])
          ));
        mm[12][15] = 0.;
        mm[12][16] = 0.;
        mm[12][17] = 0.;
        mm[12][18] = 0.;
        mm[12][19] = 0.;
        mm[12][20] = 0.;
        mm[13][13] = ((mk[6]*((Vpk[13][14][2]*Vpk[13][14][2])+((Vpk[13][14][0]*
          Vpk[13][14][0])+(Vpk[13][14][1]*Vpk[13][14][1]))))+((IkWpk[13][14][1]*
          c14)-(IkWpk[13][14][2]*s14)));
        mm[13][14] = (mk[6]*((rk[6][2]*Vpk[13][14][1])-(rk[6][1]*Vpk[13][14][2])
          ));
        mm[13][15] = 0.;
        mm[13][16] = 0.;
        mm[13][17] = 0.;
        mm[13][18] = 0.;
        mm[13][19] = 0.;
        mm[13][20] = 0.;
        mm[14][14] = (ik[6][0][0]+(mk[6]*((rk[6][1]*rk[6][1])+(rk[6][2]*rk[6][2]
          ))));
        mm[14][15] = 0.;
        mm[14][16] = 0.;
        mm[14][17] = 0.;
        mm[14][18] = 0.;
        mm[14][19] = 0.;
        mm[14][20] = 0.;
        temp[0] = (((mk[7]*((Vpk[15][17][2]*Vpk[15][17][2])+((Vpk[15][17][0]*
          Vpk[15][17][0])+(Vpk[15][17][1]*Vpk[15][17][1]))))+((IkWpk[15][17][2]*
          Wpk[15][17][2])+((IkWpk[15][17][0]*Wpk[15][17][0])+(IkWpk[15][17][1]*
          s16))))+((mk[8]*((Vpk[15][18][2]*Vpk[15][18][2])+((Vpk[15][18][0]*
          Vpk[15][18][0])+(Vpk[15][18][1]*Vpk[15][18][1]))))+((IkWpk[15][18][2]*
          Wpk[15][18][2])+((IkWpk[15][18][0]*Wpk[15][18][0])+(IkWpk[15][18][1]*
          s16)))));
        mm[15][15] = (((mk[9]*((Vpk[15][20][2]*Vpk[15][20][2])+((Vpk[15][20][0]*
          Vpk[15][20][0])+(Vpk[15][20][1]*Vpk[15][20][1]))))+((IkWpk[15][20][2]*
          Wpk[15][20][2])+((IkWpk[15][20][0]*Wpk[15][19][0])+(IkWpk[15][20][1]*
          Wpk[15][20][1]))))+temp[0]);
        temp[0] = (((mk[7]*((Vpk[15][17][2]*Vpk[16][17][2])+((Vpk[15][17][0]*
          Vpk[16][17][0])+(Vpk[15][17][1]*Vpk[16][17][1]))))+((IkWpk[16][17][0]*
          Wpk[15][17][0])+(IkWpk[16][17][2]*Wpk[15][17][2])))+((mk[8]*((
          Vpk[15][18][2]*Vpk[16][18][2])+((Vpk[15][18][0]*Vpk[16][18][0])+(
          Vpk[15][18][1]*Vpk[16][18][1]))))+((IkWpk[16][18][0]*Wpk[15][18][0])+(
          IkWpk[16][18][2]*Wpk[15][18][2]))));
        mm[15][16] = (((mk[9]*((Vpk[15][20][2]*Vpk[16][20][2])+((Vpk[15][20][0]*
          Vpk[16][20][0])+(Vpk[15][20][1]*Vpk[16][20][1]))))+((IkWpk[16][20][2]*
          Wpk[15][20][2])+((IkWpk[16][20][0]*Wpk[15][19][0])+(IkWpk[16][20][1]*
          Wpk[15][20][1]))))+temp[0]);
        mm[15][17] = (((mk[9]*((Vpk[15][20][2]*Vpk[17][20][2])+((Vpk[15][20][0]*
          Vpk[17][20][0])+(Vpk[15][20][1]*Vpk[17][20][1]))))+((IkWpk[17][20][1]*
          Wpk[15][20][1])+(IkWpk[17][20][2]*Wpk[15][20][2])))+(((ik[7][1][1]*s16
          )+(mk[7]*((rk[7][0]*Vpk[15][17][2])-(rk[7][2]*Vpk[15][17][0]))))+((
          ik[8][1][1]*s16)+(mk[8]*((Vpk[15][18][0]*Vpk[17][18][0])+(
          Vpk[15][18][2]*Vpk[17][18][2]))))));
        mm[15][18] = (((ik[8][1][1]*s16)+(mk[8]*((rk[8][0]*Vpk[15][18][2])-(
          rk[8][2]*Vpk[15][18][0]))))+((mk[9]*((Vpk[15][20][2]*Vpk[18][20][2])+(
          (Vpk[15][20][0]*Vpk[18][20][0])+(Vpk[15][20][1]*Vpk[18][20][1]))))+((
          IkWpk[18][20][1]*Wpk[15][20][1])+(IkWpk[18][20][2]*Wpk[15][20][2]))));
        mm[15][19] = ((mk[9]*((Vpk[15][20][2]*Vpk[19][20][2])+((Vpk[15][20][0]*
          Vpk[19][20][0])+(Vpk[15][20][1]*Vpk[19][20][1]))))+((IkWpk[19][20][1]*
          Wpk[15][20][1])+(IkWpk[19][20][2]*Wpk[15][20][2])));
        mm[15][20] = ((ik[9][0][0]*Wpk[15][19][0])+(mk[9]*((rk[9][2]*
          Vpk[15][20][1])-(rk[9][1]*Vpk[15][20][2]))));
        temp[0] = (((mk[7]*((Vpk[16][17][2]*Vpk[16][17][2])+((Vpk[16][17][0]*
          Vpk[16][17][0])+(Vpk[16][17][1]*Vpk[16][17][1]))))+((IkWpk[16][17][0]*
          c17)+(IkWpk[16][17][2]*s17)))+((mk[8]*((Vpk[16][18][2]*Vpk[16][18][2])
          +((Vpk[16][18][0]*Vpk[16][18][0])+(Vpk[16][18][1]*Vpk[16][18][1]))))+(
          (IkWpk[16][18][0]*Wpk[16][18][0])+(IkWpk[16][18][2]*Wpk[16][18][2]))))
          ;
        mm[16][16] = (((mk[9]*((Vpk[16][20][2]*Vpk[16][20][2])+((Vpk[16][20][0]*
          Vpk[16][20][0])+(Vpk[16][20][1]*Vpk[16][20][1]))))+((IkWpk[16][20][2]*
          Wpk[16][20][2])+((IkWpk[16][20][0]*Wpk[16][19][0])+(IkWpk[16][20][1]*
          Wpk[16][20][1]))))+temp[0]);
        mm[16][17] = (((mk[7]*((rk[7][0]*Vpk[16][17][2])-(rk[7][2]*
          Vpk[16][17][0])))+(mk[8]*((Vpk[16][18][0]*Vpk[17][18][0])+(
          Vpk[16][18][2]*Vpk[17][18][2]))))+((mk[9]*((Vpk[16][20][2]*
          Vpk[17][20][2])+((Vpk[16][20][0]*Vpk[17][20][0])+(Vpk[16][20][1]*
          Vpk[17][20][1]))))+((IkWpk[17][20][1]*Wpk[16][20][1])+(
          IkWpk[17][20][2]*Wpk[16][20][2]))));
        mm[16][18] = ((mk[8]*((rk[8][0]*Vpk[16][18][2])-(rk[8][2]*Vpk[16][18][0]
          )))+((mk[9]*((Vpk[16][20][2]*Vpk[18][20][2])+((Vpk[16][20][0]*
          Vpk[18][20][0])+(Vpk[16][20][1]*Vpk[18][20][1]))))+((IkWpk[18][20][1]*
          Wpk[16][20][1])+(IkWpk[18][20][2]*Wpk[16][20][2]))));
        mm[16][19] = ((mk[9]*((Vpk[16][20][2]*Vpk[19][20][2])+((Vpk[16][20][0]*
          Vpk[19][20][0])+(Vpk[16][20][1]*Vpk[19][20][1]))))+((IkWpk[19][20][1]*
          Wpk[16][20][1])+(IkWpk[19][20][2]*Wpk[16][20][2])));
        mm[16][20] = ((ik[9][0][0]*Wpk[16][19][0])+(mk[9]*((rk[9][2]*
          Vpk[16][20][1])-(rk[9][1]*Vpk[16][20][2]))));
        mm[17][17] = (((ik[7][1][1]+(mk[7]*((rk[7][0]*rk[7][0])+(rk[7][2]*
          rk[7][2]))))+(ik[8][1][1]+(mk[8]*((Vpk[17][18][0]*Vpk[17][18][0])+(
          Vpk[17][18][2]*Vpk[17][18][2])))))+((mk[9]*((Vpk[17][20][2]*
          Vpk[17][20][2])+((Vpk[17][20][0]*Vpk[17][20][0])+(Vpk[17][20][1]*
          Vpk[17][20][1]))))+((IkWpk[17][20][1]*c20)-(IkWpk[17][20][2]*s20))));
        mm[17][18] = ((ik[8][1][1]+(mk[8]*((rk[8][0]*Vpk[17][18][2])-(rk[8][2]*
          Vpk[17][18][0]))))+((mk[9]*((Vpk[17][20][2]*Vpk[18][20][2])+((
          Vpk[17][20][0]*Vpk[18][20][0])+(Vpk[17][20][1]*Vpk[18][20][1]))))+((
          IkWpk[18][20][1]*c20)-(IkWpk[18][20][2]*s20))));
        mm[17][19] = ((mk[9]*((Vpk[17][20][2]*Vpk[19][20][2])+((Vpk[17][20][0]*
          Vpk[19][20][0])+(Vpk[17][20][1]*Vpk[19][20][1]))))+((IkWpk[19][20][1]*
          c20)-(IkWpk[19][20][2]*s20)));
        mm[17][20] = (mk[9]*((rk[9][2]*Vpk[17][20][1])-(rk[9][1]*Vpk[17][20][2])
          ));
        mm[18][18] = ((ik[8][1][1]+(mk[8]*((rk[8][0]*rk[8][0])+(rk[8][2]*
          rk[8][2]))))+((mk[9]*((Vpk[18][20][2]*Vpk[18][20][2])+((Vpk[18][20][0]
          *Vpk[18][20][0])+(Vpk[18][20][1]*Vpk[18][20][1]))))+((IkWpk[18][20][1]
          *c20)-(IkWpk[18][20][2]*s20))));
        mm[18][19] = ((mk[9]*((Vpk[18][20][2]*Vpk[19][20][2])+((Vpk[18][20][0]*
          Vpk[19][20][0])+(Vpk[18][20][1]*Vpk[19][20][1]))))+((IkWpk[19][20][1]*
          c20)-(IkWpk[19][20][2]*s20)));
        mm[18][20] = (mk[9]*((rk[9][2]*Vpk[18][20][1])-(rk[9][1]*Vpk[18][20][2])
          ));
        mm[19][19] = ((mk[9]*((Vpk[19][20][2]*Vpk[19][20][2])+((Vpk[19][20][0]*
          Vpk[19][20][0])+(Vpk[19][20][1]*Vpk[19][20][1]))))+((IkWpk[19][20][1]*
          c20)-(IkWpk[19][20][2]*s20)));
        mm[19][20] = (mk[9]*((rk[9][2]*Vpk[19][20][1])-(rk[9][1]*Vpk[19][20][2])
          ));
        mm[20][20] = (ik[9][0][0]+(mk[9]*((rk[9][1]*rk[9][1])+(rk[9][2]*rk[9][2]
          ))));
/*
Check for singular mass matrix
*/
        for (i = 0; i < 21; i++) {
            if (mm[i][i] < 1e-13) {
                sdseterr(routine,47);
            }
        }
        sderror(&dumroutine,&errnum);
        if (errnum == 0) {
            mmflg = 1;
        }
    }
/*
 Used 0.02 seconds CPU time,
 0 additional bytes of memory.
 Equations contain 1643 adds/subtracts/negates
                   2383 multiplies
                      0 divides
                    472 assignments
*/
}

void sddommldu(int routine)
{
    int i;
    int dumroutine,errnum;

    if (mmlduflg == 0) {
        sddomm(routine);
/*
Numerically decompose the mass matrix
*/
        sdldudcomp(21,21,mmap,1e-13,(double*)workss,works, (double*)mm, (double*)mlo,mdi);
/*
Check for singular mass matrix
*/
        for (i = 0; i < 21; i++) {
            if (mdi[i] <= 1e-13) {
                sdseterr(routine,47);
            }
        }
        sderror(&dumroutine,&errnum);
        if (errnum == 0) {
            mmlduflg = 1;
        }
    }
}

void sdlhs(int routine)
{
/* Compute all remaining state- and force-dependent quantities
*/

    roustate = 2;
    sddommldu(routine);
    sddofs0();
}

void sdmfrc(double imult[1])
{

}

void sdequivht(double tau[21])
{
/* Compute tree hinge torques to match effect of applied loads
*/
    double fstareq[21][3],tstareq[21][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(56,23);
        return;
    }
/*
Compute fstareq (forces)
*/
    fstareq[5][0] = -(ufk[0][0]+(9.8*(mk[0]*s4)));
    fstareq[5][1] = -(ufk[0][1]+(gk[5][1]*mk[0]));
    fstareq[5][2] = -(ufk[0][2]+(gk[5][2]*mk[0]));
    fstareq[6][0] = -(ufk[1][0]+(gk[6][0]*mk[1]));
    fstareq[6][1] = -(ufk[1][1]+(gk[6][1]*mk[1]));
    fstareq[6][2] = -(ufk[1][2]+(gk[5][2]*mk[1]));
    fstareq[7][0] = -(ufk[2][0]+(gk[7][0]*mk[2]));
    fstareq[7][1] = -(ufk[2][1]+(gk[6][1]*mk[2]));
    fstareq[7][2] = -(ufk[2][2]+(gk[7][2]*mk[2]));
    fstareq[8][0] = -(ufk[3][0]+(gk[8][0]*mk[3]));
    fstareq[8][1] = -(ufk[3][1]+(gk[6][1]*mk[3]));
    fstareq[8][2] = -(ufk[3][2]+(gk[8][2]*mk[3]));
    fstareq[11][0] = -(ufk[4][0]+(gk[11][0]*mk[4]));
    fstareq[11][1] = -(ufk[4][1]+(gk[10][1]*mk[4]));
    fstareq[11][2] = -(ufk[4][2]+(gk[11][2]*mk[4]));
    fstareq[12][0] = -(ufk[5][0]+(gk[12][0]*mk[5]));
    fstareq[12][1] = -(ufk[5][1]+(gk[10][1]*mk[5]));
    fstareq[12][2] = -(ufk[5][2]+(gk[12][2]*mk[5]));
    fstareq[14][0] = -(ufk[6][0]+(gk[13][0]*mk[6]));
    fstareq[14][1] = -(ufk[6][1]+(gk[14][1]*mk[6]));
    fstareq[14][2] = -(ufk[6][2]+(gk[14][2]*mk[6]));
    fstareq[17][0] = -(ufk[7][0]+(gk[17][0]*mk[7]));
    fstareq[17][1] = -(ufk[7][1]+(gk[16][1]*mk[7]));
    fstareq[17][2] = -(ufk[7][2]+(gk[17][2]*mk[7]));
    fstareq[18][0] = -(ufk[8][0]+(gk[18][0]*mk[8]));
    fstareq[18][1] = -(ufk[8][1]+(gk[16][1]*mk[8]));
    fstareq[18][2] = -(ufk[8][2]+(gk[18][2]*mk[8]));
    fstareq[20][0] = -(ufk[9][0]+(gk[19][0]*mk[9]));
    fstareq[20][1] = -(ufk[9][1]+(gk[20][1]*mk[9]));
    fstareq[20][2] = -(ufk[9][2]+(gk[20][2]*mk[9]));
/*
Compute tstareq (torques)
*/
/*
Compute taus (RHS ignoring constraints and inertial forces)
*/
    sddovpk();
    temp[0] = (((fstareq[8][2]*Vpk[0][8][2])+((fstareq[8][0]*Vpk[0][8][0])+(
      fstareq[8][1]*Vpk[0][6][1])))+(((fstareq[7][2]*Vpk[0][7][2])+((
      fstareq[7][0]*Vpk[0][7][0])+(fstareq[7][1]*Vpk[0][6][1])))+(((
      fstareq[5][2]*Vpk[0][5][2])+((fstareq[5][1]*Vpk[0][5][1])-(fstareq[5][0]*
      s4)))+((fstareq[6][2]*Vpk[0][5][2])+((fstareq[6][0]*Vpk[0][6][0])+(
      fstareq[6][1]*Vpk[0][6][1]))))));
    temp[1] = (((fstareq[17][2]*Vpk[0][17][2])+((fstareq[17][0]*Vpk[0][17][0])+(
      fstareq[17][1]*Vpk[0][16][1])))+(((fstareq[14][2]*Vpk[0][14][2])+((
      fstareq[14][0]*Vpk[0][13][0])+(fstareq[14][1]*Vpk[0][14][1])))+(((
      fstareq[12][2]*Vpk[0][12][2])+((fstareq[12][0]*Vpk[0][12][0])+(
      fstareq[12][1]*Vpk[0][10][1])))+(((fstareq[11][2]*Vpk[0][11][2])+((
      fstareq[11][0]*Vpk[0][11][0])+(fstareq[11][1]*Vpk[0][10][1])))+temp[0]))))
      ;
    tau[0] = (utau[0]-(((fstareq[20][2]*Vpk[0][20][2])+((fstareq[20][0]*
      Vpk[0][19][0])+(fstareq[20][1]*Vpk[0][20][1])))+(((fstareq[18][2]*
      Vpk[0][18][2])+((fstareq[18][0]*Vpk[0][18][0])+(fstareq[18][1]*
      Vpk[0][16][1])))+temp[1])));
    temp[0] = (((fstareq[8][2]*Vpk[1][8][2])+((fstareq[8][0]*Vpk[1][8][0])+(
      fstareq[8][1]*Vpk[1][6][1])))+(((fstareq[7][2]*Vpk[1][7][2])+((
      fstareq[7][0]*Vpk[1][7][0])+(fstareq[7][1]*Vpk[1][6][1])))+(((
      fstareq[5][2]*Vpk[1][5][2])+((fstareq[5][0]*Vpk[1][4][0])+(fstareq[5][1]*
      Vpk[1][5][1])))+((fstareq[6][2]*Vpk[1][5][2])+((fstareq[6][0]*Vpk[1][6][0]
      )+(fstareq[6][1]*Vpk[1][6][1]))))));
    temp[1] = (((fstareq[17][2]*Vpk[1][17][2])+((fstareq[17][0]*Vpk[1][17][0])+(
      fstareq[17][1]*Vpk[1][16][1])))+(((fstareq[14][2]*Vpk[1][14][2])+((
      fstareq[14][0]*Vpk[1][13][0])+(fstareq[14][1]*Vpk[1][14][1])))+(((
      fstareq[12][2]*Vpk[1][12][2])+((fstareq[12][0]*Vpk[1][12][0])+(
      fstareq[12][1]*Vpk[1][10][1])))+(((fstareq[11][2]*Vpk[1][11][2])+((
      fstareq[11][0]*Vpk[1][11][0])+(fstareq[11][1]*Vpk[1][10][1])))+temp[0]))))
      ;
    tau[1] = (utau[1]-(((fstareq[20][2]*Vpk[1][20][2])+((fstareq[20][0]*
      Vpk[1][19][0])+(fstareq[20][1]*Vpk[1][20][1])))+(((fstareq[18][2]*
      Vpk[1][18][2])+((fstareq[18][0]*Vpk[1][18][0])+(fstareq[18][1]*
      Vpk[1][16][1])))+temp[1])));
    temp[0] = (((fstareq[8][2]*Vpk[2][8][2])+((fstareq[8][0]*Vpk[2][8][0])+(
      fstareq[8][1]*Vpk[2][6][1])))+(((fstareq[7][2]*Vpk[2][7][2])+((
      fstareq[7][0]*Vpk[2][7][0])+(fstareq[7][1]*Vpk[2][6][1])))+(((
      fstareq[5][2]*Vpk[2][5][2])+((fstareq[5][0]*Vpk[2][4][0])+(fstareq[5][1]*
      Vpk[2][5][1])))+((fstareq[6][2]*Vpk[2][5][2])+((fstareq[6][0]*Vpk[2][6][0]
      )+(fstareq[6][1]*Vpk[2][6][1]))))));
    temp[1] = (((fstareq[17][2]*Vpk[2][17][2])+((fstareq[17][0]*Vpk[2][17][0])+(
      fstareq[17][1]*Vpk[2][16][1])))+(((fstareq[14][2]*Vpk[2][14][2])+((
      fstareq[14][0]*Vpk[2][13][0])+(fstareq[14][1]*Vpk[2][14][1])))+(((
      fstareq[12][2]*Vpk[2][12][2])+((fstareq[12][0]*Vpk[2][12][0])+(
      fstareq[12][1]*Vpk[2][10][1])))+(((fstareq[11][2]*Vpk[2][11][2])+((
      fstareq[11][0]*Vpk[2][11][0])+(fstareq[11][1]*Vpk[2][10][1])))+temp[0]))))
      ;
    tau[2] = (utau[2]-(((fstareq[20][2]*Vpk[2][20][2])+((fstareq[20][0]*
      Vpk[2][19][0])+(fstareq[20][1]*Vpk[2][20][1])))+(((fstareq[18][2]*
      Vpk[2][18][2])+((fstareq[18][0]*Vpk[2][18][0])+(fstareq[18][1]*
      Vpk[2][16][1])))+temp[1])));
    temp[0] = ((((fstareq[5][2]*Vpk[3][5][2])+((fstareq[5][0]*Vpk[3][5][0])+(
      fstareq[5][1]*Vpk[3][5][1])))+(((utk[0][0]*s4)-(utk[0][1]*Wpk[3][5][1]))-(
      utk[0][2]*Wpk[3][5][2])))+(((fstareq[6][2]*Vpk[3][6][2])+((fstareq[6][0]*
      Vpk[3][6][0])+(fstareq[6][1]*Vpk[3][6][1])))-((utk[1][2]*Wpk[3][5][2])+((
      utk[1][0]*Wpk[3][6][0])+(utk[1][1]*Wpk[3][6][1])))));
    temp[1] = ((((fstareq[8][2]*Vpk[3][8][2])+((fstareq[8][0]*Vpk[3][8][0])+(
      fstareq[8][1]*Vpk[3][8][1])))-((utk[3][2]*Wpk[3][8][2])+((utk[3][0]*
      Wpk[3][8][0])+(utk[3][1]*Wpk[3][6][1]))))+((((fstareq[7][2]*Vpk[3][7][2])+
      ((fstareq[7][0]*Vpk[3][7][0])+(fstareq[7][1]*Vpk[3][7][1])))-((utk[2][2]*
      Wpk[3][7][2])+((utk[2][0]*Wpk[3][7][0])+(utk[2][1]*Wpk[3][6][1]))))+
      temp[0]));
    temp[2] = ((((fstareq[12][2]*Vpk[3][12][2])+((fstareq[12][0]*Vpk[3][12][0])+
      (fstareq[12][1]*Vpk[3][12][1])))-((utk[5][2]*Wpk[3][12][2])+((utk[5][0]*
      Wpk[3][12][0])+(utk[5][1]*Wpk[3][10][1]))))+((((fstareq[11][2]*
      Vpk[3][11][2])+((fstareq[11][0]*Vpk[3][11][0])+(fstareq[11][1]*
      Vpk[3][11][1])))-((utk[4][2]*Wpk[3][11][2])+((utk[4][0]*Wpk[3][11][0])+(
      utk[4][1]*Wpk[3][10][1]))))+temp[1]));
    temp[3] = ((((fstareq[17][2]*Vpk[3][17][2])+((fstareq[17][0]*Vpk[3][17][0])+
      (fstareq[17][1]*Vpk[3][17][1])))-((utk[7][2]*Wpk[3][17][2])+((utk[7][0]*
      Wpk[3][17][0])+(utk[7][1]*Wpk[3][16][1]))))+((((fstareq[14][2]*
      Vpk[3][14][2])+((fstareq[14][0]*Vpk[3][14][0])+(fstareq[14][1]*
      Vpk[3][14][1])))-((utk[6][2]*Wpk[3][14][2])+((utk[6][0]*Wpk[3][13][0])+(
      utk[6][1]*Wpk[3][14][1]))))+temp[2]));
    tau[3] = (utau[3]-((((fstareq[20][2]*Vpk[3][20][2])+((fstareq[20][0]*
      Vpk[3][20][0])+(fstareq[20][1]*Vpk[3][20][1])))-((utk[9][2]*Wpk[3][20][2])
      +((utk[9][0]*Wpk[3][19][0])+(utk[9][1]*Wpk[3][20][1]))))+((((
      fstareq[18][2]*Vpk[3][18][2])+((fstareq[18][0]*Vpk[3][18][0])+(
      fstareq[18][1]*Vpk[3][18][1])))-((utk[8][2]*Wpk[3][18][2])+((utk[8][0]*
      Wpk[3][18][0])+(utk[8][1]*Wpk[3][16][1]))))+temp[3])));
    temp[0] = ((((fstareq[5][2]*Vpk[4][5][2])+((fstareq[5][0]*Vpk[4][5][0])+(
      fstareq[5][1]*Vpk[4][5][1])))+((utk[0][2]*s5)-(utk[0][1]*c5)))+(((
      fstareq[6][2]*Vpk[4][6][2])+((fstareq[6][0]*Vpk[4][6][0])+(fstareq[6][1]*
      Vpk[4][6][1])))+((utk[1][2]*s5)-((utk[1][0]*Wpk[4][6][0])+(utk[1][1]*
      Wpk[4][6][1])))));
    temp[1] = ((((fstareq[8][2]*Vpk[4][8][2])+((fstareq[8][0]*Vpk[4][8][0])+(
      fstareq[8][1]*Vpk[4][8][1])))-((utk[3][2]*Wpk[4][8][2])+((utk[3][0]*
      Wpk[4][8][0])+(utk[3][1]*Wpk[4][6][1]))))+((((fstareq[7][2]*Vpk[4][7][2])+
      ((fstareq[7][0]*Vpk[4][7][0])+(fstareq[7][1]*Vpk[4][7][1])))-((utk[2][2]*
      Wpk[4][7][2])+((utk[2][0]*Wpk[4][7][0])+(utk[2][1]*Wpk[4][6][1]))))+
      temp[0]));
    temp[2] = ((((fstareq[12][2]*Vpk[4][12][2])+((fstareq[12][0]*Vpk[4][12][0])+
      (fstareq[12][1]*Vpk[4][12][1])))-((utk[5][2]*Wpk[4][12][2])+((utk[5][0]*
      Wpk[4][12][0])+(utk[5][1]*Wpk[4][10][1]))))+((((fstareq[11][2]*
      Vpk[4][11][2])+((fstareq[11][0]*Vpk[4][11][0])+(fstareq[11][1]*
      Vpk[4][11][1])))-((utk[4][2]*Wpk[4][11][2])+((utk[4][0]*Wpk[4][11][0])+(
      utk[4][1]*Wpk[4][10][1]))))+temp[1]));
    temp[3] = ((((fstareq[17][2]*Vpk[4][17][2])+((fstareq[17][0]*Vpk[4][17][0])+
      (fstareq[17][1]*Vpk[4][17][1])))-((utk[7][2]*Wpk[4][17][2])+((utk[7][0]*
      Wpk[4][17][0])+(utk[7][1]*Wpk[4][16][1]))))+((((fstareq[14][2]*
      Vpk[4][14][2])+((fstareq[14][0]*Vpk[4][14][0])+(fstareq[14][1]*
      Vpk[4][14][1])))-((utk[6][2]*Wpk[4][14][2])+((utk[6][0]*Wpk[4][13][0])+(
      utk[6][1]*Wpk[4][14][1]))))+temp[2]));
    tau[4] = (utau[4]-((((fstareq[20][2]*Vpk[4][20][2])+((fstareq[20][0]*
      Vpk[4][20][0])+(fstareq[20][1]*Vpk[4][20][1])))-((utk[9][2]*Wpk[4][20][2])
      +((utk[9][0]*Wpk[4][19][0])+(utk[9][1]*Wpk[4][20][1]))))+((((
      fstareq[18][2]*Vpk[4][18][2])+((fstareq[18][0]*Vpk[4][18][0])+(
      fstareq[18][1]*Vpk[4][18][1])))-((utk[8][2]*Wpk[4][18][2])+((utk[8][0]*
      Wpk[4][18][0])+(utk[8][1]*Wpk[4][16][1]))))+temp[3])));
    temp[0] = ((((fstareq[7][2]*Vpk[5][7][2])+((fstareq[7][0]*Vpk[5][7][0])+(
      fstareq[7][1]*Vpk[5][7][1])))+(((utk[2][1]*s6)-(utk[2][0]*Wpk[5][7][0]))-(
      utk[2][2]*Wpk[5][7][2])))+((((fstareq[5][1]*rk[0][2])-(fstareq[5][2]*
      rk[0][1]))-utk[0][0])+(((fstareq[6][2]*Vpk[5][6][2])+((fstareq[6][0]*
      Vpk[5][6][0])+(fstareq[6][1]*Vpk[5][6][1])))+((utk[1][1]*s6)-(utk[1][0]*c6
      )))));
    temp[1] = ((((fstareq[11][2]*Vpk[5][11][2])+((fstareq[11][0]*Vpk[5][11][0])+
      (fstareq[11][1]*Vpk[5][11][1])))-((utk[4][2]*Wpk[5][11][2])+((utk[4][0]*
      Wpk[5][11][0])+(utk[4][1]*Wpk[5][10][1]))))+((((fstareq[8][2]*Vpk[5][8][2]
      )+((fstareq[8][0]*Vpk[5][8][0])+(fstareq[8][1]*Vpk[5][8][1])))+(((
      utk[3][1]*s6)-(utk[3][0]*Wpk[5][8][0]))-(utk[3][2]*Wpk[5][8][2])))+temp[0]
      ));
    temp[2] = ((((fstareq[14][2]*Vpk[5][14][2])+((fstareq[14][0]*Vpk[5][14][0])+
      (fstareq[14][1]*Vpk[5][14][1])))-((utk[6][2]*Wpk[5][14][2])+((utk[6][0]*
      Wpk[5][13][0])+(utk[6][1]*Wpk[5][14][1]))))+((((fstareq[12][2]*
      Vpk[5][12][2])+((fstareq[12][0]*Vpk[5][12][0])+(fstareq[12][1]*
      Vpk[5][12][1])))-((utk[5][2]*Wpk[5][12][2])+((utk[5][0]*Wpk[5][12][0])+(
      utk[5][1]*Wpk[5][10][1]))))+temp[1]));
    temp[3] = ((((fstareq[18][2]*Vpk[5][18][2])+((fstareq[18][0]*Vpk[5][18][0])+
      (fstareq[18][1]*Vpk[5][18][1])))-((utk[8][2]*Wpk[5][18][2])+((utk[8][0]*
      Wpk[5][18][0])+(utk[8][1]*Wpk[5][16][1]))))+((((fstareq[17][2]*
      Vpk[5][17][2])+((fstareq[17][0]*Vpk[5][17][0])+(fstareq[17][1]*
      Vpk[5][17][1])))-((utk[7][2]*Wpk[5][17][2])+((utk[7][0]*Wpk[5][17][0])+(
      utk[7][1]*Wpk[5][16][1]))))+temp[2]));
    tau[5] = (utau[5]-((((fstareq[20][2]*Vpk[5][20][2])+((fstareq[20][0]*
      Vpk[5][20][0])+(fstareq[20][1]*Vpk[5][20][1])))-((utk[9][2]*Wpk[5][20][2])
      +((utk[9][0]*Wpk[5][19][0])+(utk[9][1]*Wpk[5][20][1]))))+temp[3]));
    tau[6] = (utau[6]-((((fstareq[8][2]*Vpk[6][8][2])+((fstareq[8][0]*
      Vpk[6][8][0])+(fstareq[8][1]*Vpk[6][8][1])))+((utk[3][0]*s8)-(utk[3][2]*c8
      )))+((((fstareq[6][0]*rk[1][1])-(fstareq[6][1]*rk[1][0]))-utk[1][2])+(((
      fstareq[7][2]*Vpk[6][7][2])+((fstareq[7][0]*Vpk[6][7][0])+(fstareq[7][1]*
      Vpk[6][7][1])))+((utk[2][0]*s7)-(utk[2][2]*c7))))));
    tau[7] = (utau[7]-(((fstareq[7][2]*rk[2][0])-(fstareq[7][0]*rk[2][2]))-
      utk[2][1]));
    tau[8] = (utau[8]-(((fstareq[8][2]*rk[3][0])-(fstareq[8][0]*rk[3][2]))-
      utk[3][1]));
    temp[0] = ((((fstareq[11][2]*Vpk[9][11][2])+((fstareq[11][0]*Vpk[9][11][0])+
      (fstareq[11][1]*Vpk[9][11][1])))-((utk[4][2]*Wpk[9][11][2])+((utk[4][0]*
      Wpk[9][11][0])+(utk[4][1]*s10))))+(((fstareq[12][2]*Vpk[9][12][2])+((
      fstareq[12][0]*Vpk[9][12][0])+(fstareq[12][1]*Vpk[9][12][1])))-((utk[5][2]
      *Wpk[9][12][2])+((utk[5][0]*Wpk[9][12][0])+(utk[5][1]*s10)))));
    tau[9] = (utau[9]-((((fstareq[14][2]*Vpk[9][14][2])+((fstareq[14][0]*
      Vpk[9][14][0])+(fstareq[14][1]*Vpk[9][14][1])))-((utk[6][2]*Wpk[9][14][2])
      +((utk[6][0]*Wpk[9][13][0])+(utk[6][1]*Wpk[9][14][1]))))+temp[0]));
    temp[0] = ((((fstareq[11][2]*Vpk[10][11][2])+((fstareq[11][0]*Vpk[10][11][0]
      )+(fstareq[11][1]*Vpk[10][11][1])))-((utk[4][0]*c11)+(utk[4][2]*s11)))+(((
      fstareq[12][2]*Vpk[10][12][2])+((fstareq[12][0]*Vpk[10][12][0])+(
      fstareq[12][1]*Vpk[10][12][1])))-((utk[5][0]*Wpk[10][12][0])+(utk[5][2]*
      Wpk[10][12][2]))));
    tau[10] = (utau[10]-((((fstareq[14][2]*Vpk[10][14][2])+((fstareq[14][0]*
      Vpk[10][14][0])+(fstareq[14][1]*Vpk[10][14][1])))-((utk[6][2]*
      Wpk[10][14][2])+((utk[6][0]*Wpk[10][13][0])+(utk[6][1]*Wpk[10][14][1]))))+
      temp[0]));
    tau[11] = (utau[11]-((((fstareq[14][2]*Vpk[11][14][2])+((fstareq[14][0]*
      Vpk[11][14][0])+(fstareq[14][1]*Vpk[11][14][1])))+((utk[6][2]*s14)-(
      utk[6][1]*c14)))+((((fstareq[11][2]*rk[4][0])-(fstareq[11][0]*rk[4][2]))-
      utk[4][1])+(((fstareq[12][0]*Vpk[11][12][0])+(fstareq[12][2]*
      Vpk[11][12][2]))-utk[5][1]))));
    tau[12] = (utau[12]-((((fstareq[12][2]*rk[5][0])-(fstareq[12][0]*rk[5][2]))-
      utk[5][1])+(((fstareq[14][2]*Vpk[12][14][2])+((fstareq[14][0]*
      Vpk[12][14][0])+(fstareq[14][1]*Vpk[12][14][1])))+((utk[6][2]*s14)-(
      utk[6][1]*c14)))));
    tau[13] = (utau[13]-(((fstareq[14][2]*Vpk[13][14][2])+((fstareq[14][0]*
      Vpk[13][14][0])+(fstareq[14][1]*Vpk[13][14][1])))+((utk[6][2]*s14)-(
      utk[6][1]*c14))));
    tau[14] = (utau[14]-(((fstareq[14][1]*rk[6][2])-(fstareq[14][2]*rk[6][1]))-
      utk[6][0]));
    temp[0] = ((((fstareq[17][2]*Vpk[15][17][2])+((fstareq[17][0]*Vpk[15][17][0]
      )+(fstareq[17][1]*Vpk[15][17][1])))-((utk[7][2]*Wpk[15][17][2])+((
      utk[7][0]*Wpk[15][17][0])+(utk[7][1]*s16))))+(((fstareq[18][2]*
      Vpk[15][18][2])+((fstareq[18][0]*Vpk[15][18][0])+(fstareq[18][1]*
      Vpk[15][18][1])))-((utk[8][2]*Wpk[15][18][2])+((utk[8][0]*Wpk[15][18][0])+
      (utk[8][1]*s16)))));
    tau[15] = (utau[15]-((((fstareq[20][2]*Vpk[15][20][2])+((fstareq[20][0]*
      Vpk[15][20][0])+(fstareq[20][1]*Vpk[15][20][1])))-((utk[9][2]*
      Wpk[15][20][2])+((utk[9][0]*Wpk[15][19][0])+(utk[9][1]*Wpk[15][20][1]))))+
      temp[0]));
    temp[0] = ((((fstareq[17][2]*Vpk[16][17][2])+((fstareq[17][0]*Vpk[16][17][0]
      )+(fstareq[17][1]*Vpk[16][17][1])))-((utk[7][0]*c17)+(utk[7][2]*s17)))+(((
      fstareq[18][2]*Vpk[16][18][2])+((fstareq[18][0]*Vpk[16][18][0])+(
      fstareq[18][1]*Vpk[16][18][1])))-((utk[8][0]*Wpk[16][18][0])+(utk[8][2]*
      Wpk[16][18][2]))));
    tau[16] = (utau[16]-((((fstareq[20][2]*Vpk[16][20][2])+((fstareq[20][0]*
      Vpk[16][20][0])+(fstareq[20][1]*Vpk[16][20][1])))-((utk[9][2]*
      Wpk[16][20][2])+((utk[9][0]*Wpk[16][19][0])+(utk[9][1]*Wpk[16][20][1]))))+
      temp[0]));
    tau[17] = (utau[17]-((((fstareq[20][2]*Vpk[17][20][2])+((fstareq[20][0]*
      Vpk[17][20][0])+(fstareq[20][1]*Vpk[17][20][1])))+((utk[9][2]*s20)-(
      utk[9][1]*c20)))+((((fstareq[17][2]*rk[7][0])-(fstareq[17][0]*rk[7][2]))-
      utk[7][1])+(((fstareq[18][0]*Vpk[17][18][0])+(fstareq[18][2]*
      Vpk[17][18][2]))-utk[8][1]))));
    tau[18] = (utau[18]-((((fstareq[18][2]*rk[8][0])-(fstareq[18][0]*rk[8][2]))-
      utk[8][1])+(((fstareq[20][2]*Vpk[18][20][2])+((fstareq[20][0]*
      Vpk[18][20][0])+(fstareq[20][1]*Vpk[18][20][1])))+((utk[9][2]*s20)-(
      utk[9][1]*c20)))));
    tau[19] = (utau[19]-(((fstareq[20][2]*Vpk[19][20][2])+((fstareq[20][0]*
      Vpk[19][20][0])+(fstareq[20][1]*Vpk[19][20][1])))+((utk[9][2]*s20)-(
      utk[9][1]*c20))));
    tau[20] = (utau[20]-(((fstareq[20][1]*rk[9][2])-(fstareq[20][2]*rk[9][1]))-
      utk[9][0]));
/*
Op counts below do not include called subroutines
*/
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  466 adds/subtracts/negates
                    425 multiplies
                      0 divides
                     73 assignments
*/
}

void sdfs0(void)
{

/*
Compute Fs (ignoring multiplier forces)
*/
    fs[0] = fs0[0];
    fs[1] = fs0[1];
    fs[2] = fs0[2];
    fs[3] = fs0[3];
    fs[4] = fs0[4];
    fs[5] = fs0[5];
    fs[6] = fs0[6];
    fs[7] = fs0[7];
    fs[8] = fs0[8];
    fs[9] = fs0[9];
    fs[10] = fs0[10];
    fs[11] = fs0[11];
    fs[12] = fs0[12];
    fs[13] = fs0[13];
    fs[14] = fs0[14];
    fs[15] = fs0[15];
    fs[16] = fs0[16];
    fs[17] = fs0[17];
    fs[18] = fs0[18];
    fs[19] = fs0[19];
    fs[20] = fs0[20];
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     21 assignments
*/
}

void sdfsmult(void)
{
    int i;

/*
Compute Fs (multiplier-generated forces only)
*/
    for (i = 0; i < 21; i++) {
        fs[i] = 0.;
    }
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     21 assignments
*/
}

void sdfsfull(void)
{

/*
Compute Fs (including all forces)
*/
    sdfsmult();
    fs[0] = (fs[0]+fs0[0]);
    fs[1] = (fs[1]+fs0[1]);
    fs[2] = (fs[2]+fs0[2]);
    fs[3] = (fs[3]+fs0[3]);
    fs[4] = (fs[4]+fs0[4]);
    fs[5] = (fs[5]+fs0[5]);
    fs[6] = (fs[6]+fs0[6]);
    fs[7] = (fs[7]+fs0[7]);
    fs[8] = (fs[8]+fs0[8]);
    fs[9] = (fs[9]+fs0[9]);
    fs[10] = (fs[10]+fs0[10]);
    fs[11] = (fs[11]+fs0[11]);
    fs[12] = (fs[12]+fs0[12]);
    fs[13] = (fs[13]+fs0[13]);
    fs[14] = (fs[14]+fs0[14]);
    fs[15] = (fs[15]+fs0[15]);
    fs[16] = (fs[16]+fs0[16]);
    fs[17] = (fs[17]+fs0[17]);
    fs[18] = (fs[18]+fs0[18]);
    fs[19] = (fs[19]+fs0[19]);
    fs[20] = (fs[20]+fs0[20]);
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   21 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     21 assignments
*/
}

void sdfsgenmult(void)
{
    int i;

/*
Compute Fs (generic multiplier-generated forces)
*/
    for (i = 0; i < 21; i++) {
        fs[i] = 0.;
    }
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     21 assignments
*/
}

void sdfsgenfull(void)
{

/*
Compute Fs (incl generic mult & other forces)
*/
    sdfsgenmult();
    fs[0] = (fs[0]+fs0[0]);
    fs[1] = (fs[1]+fs0[1]);
    fs[2] = (fs[2]+fs0[2]);
    fs[3] = (fs[3]+fs0[3]);
    fs[4] = (fs[4]+fs0[4]);
    fs[5] = (fs[5]+fs0[5]);
    fs[6] = (fs[6]+fs0[6]);
    fs[7] = (fs[7]+fs0[7]);
    fs[8] = (fs[8]+fs0[8]);
    fs[9] = (fs[9]+fs0[9]);
    fs[10] = (fs[10]+fs0[10]);
    fs[11] = (fs[11]+fs0[11]);
    fs[12] = (fs[12]+fs0[12]);
    fs[13] = (fs[13]+fs0[13]);
    fs[14] = (fs[14]+fs0[14]);
    fs[15] = (fs[15]+fs0[15]);
    fs[16] = (fs[16]+fs0[16]);
    fs[17] = (fs[17]+fs0[17]);
    fs[18] = (fs[18]+fs0[18]);
    fs[19] = (fs[19]+fs0[19]);
    fs[20] = (fs[20]+fs0[20]);
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   21 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     21 assignments
*/
}

void sdfulltrq(double udotin[21],
    double multin[1],
    double trqout[21])
{
/* Compute hinge torques which would produce indicated udots
*/
    double fstarr[21][3],tstarr[21][3],Otkr[21][3],Atir[21][3],Atkr[21][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(61,23);
        return;
    }
/*
Account for inertial accelerations and supplied udots
*/
    Otkr[4][0] = -((u[4]*wk[4][2])+(udotin[3]*s4));
    Otkr[4][2] = ((u[4]*wk[4][0])+(udotin[3]*c4));
    Otkr[5][0] = (Otkr[4][0]+udotin[5]);
    Otkr[5][1] = ((u[5]*wk[5][2])+((Otkr[4][2]*s5)+(udotin[4]*c5)));
    Otkr[5][2] = (((Otkr[4][2]*c5)-(udotin[4]*s5))-(u[5]*wk[5][1]));
    Otkr[6][0] = ((u[6]*wk[6][1])+((Otkr[5][0]*c6)+(Otkr[5][1]*s6)));
    Otkr[6][1] = (((Otkr[5][1]*c6)-(Otkr[5][0]*s6))-(u[6]*wk[6][0]));
    Otkr[6][2] = (Otkr[5][2]+udotin[6]);
    Otkr[7][0] = (((Otkr[6][0]*c7)-(Otkr[6][2]*s7))-(u[7]*wk[7][2]));
    Otkr[7][1] = (Otkr[6][1]+udotin[7]);
    Otkr[7][2] = ((u[7]*wk[7][0])+((Otkr[6][0]*s7)+(Otkr[6][2]*c7)));
    Otkr[8][0] = (((Otkr[6][0]*c8)-(Otkr[6][2]*s8))-(u[8]*wk[8][2]));
    Otkr[8][1] = (Otkr[6][1]+udotin[8]);
    Otkr[8][2] = ((u[8]*wk[8][0])+((Otkr[6][0]*s8)+(Otkr[6][2]*c8)));
    Otkr[9][0] = ((u[9]*wk[9][1])+((Otkr[5][0]*c9)+(Otkr[5][1]*s9)));
    Otkr[9][1] = (((Otkr[5][1]*c9)-(Otkr[5][0]*s9))-(u[9]*wk[9][0]));
    Otkr[9][2] = (Otkr[5][2]+udotin[9]);
    Otkr[10][0] = (Otkr[9][0]+udotin[10]);
    Otkr[10][1] = ((u[10]*wk[10][2])+((Otkr[9][1]*c10)+(Otkr[9][2]*s10)));
    Otkr[10][2] = (((Otkr[9][2]*c10)-(Otkr[9][1]*s10))-(u[10]*wk[10][1]));
    Otkr[11][0] = (((Otkr[10][0]*c11)-(Otkr[10][2]*s11))-(u[11]*wk[11][2]));
    Otkr[11][1] = (Otkr[10][1]+udotin[11]);
    Otkr[11][2] = ((u[11]*wk[11][0])+((Otkr[10][0]*s11)+(Otkr[10][2]*c11)));
    Otkr[12][0] = (((Otkr[11][0]*c12)-(Otkr[11][2]*s12))-(u[12]*wk[12][2]));
    Otkr[12][1] = (Otkr[11][1]+udotin[12]);
    Otkr[12][2] = ((u[12]*wk[12][0])+((Otkr[11][0]*s12)+(Otkr[11][2]*c12)));
    Otkr[13][0] = (((Otkr[12][0]*c13)-(Otkr[12][2]*s13))-(u[13]*wk[13][2]));
    Otkr[13][1] = (Otkr[12][1]+udotin[13]);
    Otkr[13][2] = ((u[13]*wk[13][0])+((Otkr[12][0]*s13)+(Otkr[12][2]*c13)));
    Otkr[14][0] = (Otkr[13][0]+udotin[14]);
    Otkr[14][1] = ((u[14]*wk[14][2])+((Otkr[13][1]*c14)+(Otkr[13][2]*s14)));
    Otkr[14][2] = (((Otkr[13][2]*c14)-(Otkr[13][1]*s14))-(u[14]*wk[14][1]));
    Otkr[15][0] = ((u[15]*wk[15][1])+((Otkr[5][0]*c15)+(Otkr[5][1]*s15)));
    Otkr[15][1] = (((Otkr[5][1]*c15)-(Otkr[5][0]*s15))-(u[15]*wk[15][0]));
    Otkr[15][2] = (Otkr[5][2]+udotin[15]);
    Otkr[16][0] = (Otkr[15][0]+udotin[16]);
    Otkr[16][1] = ((u[16]*wk[16][2])+((Otkr[15][1]*c16)+(Otkr[15][2]*s16)));
    Otkr[16][2] = (((Otkr[15][2]*c16)-(Otkr[15][1]*s16))-(u[16]*wk[16][1]));
    Otkr[17][0] = (((Otkr[16][0]*c17)-(Otkr[16][2]*s17))-(u[17]*wk[17][2]));
    Otkr[17][1] = (Otkr[16][1]+udotin[17]);
    Otkr[17][2] = ((u[17]*wk[17][0])+((Otkr[16][0]*s17)+(Otkr[16][2]*c17)));
    Otkr[18][0] = (((Otkr[17][0]*c18)-(Otkr[17][2]*s18))-(u[18]*wk[18][2]));
    Otkr[18][1] = (Otkr[17][1]+udotin[18]);
    Otkr[18][2] = ((u[18]*wk[18][0])+((Otkr[17][0]*s18)+(Otkr[17][2]*c18)));
    Otkr[19][0] = (((Otkr[18][0]*c19)-(Otkr[18][2]*s19))-(u[19]*wk[19][2]));
    Otkr[19][1] = (Otkr[18][1]+udotin[19]);
    Otkr[19][2] = ((u[19]*wk[19][0])+((Otkr[18][0]*s19)+(Otkr[18][2]*c19)));
    Otkr[20][0] = (Otkr[19][0]+udotin[20]);
    Otkr[20][1] = ((u[20]*wk[20][2])+((Otkr[19][1]*c20)+(Otkr[19][2]*s20)));
    Otkr[20][2] = (((Otkr[19][2]*c20)-(Otkr[19][1]*s20))-(u[20]*wk[20][1]));
    Atkr[3][0] = ((udotin[1]*s3)+(udotin[2]*c3));
    Atkr[3][1] = ((udotin[1]*c3)-(udotin[2]*s3));
    Atkr[4][0] = ((Atkr[3][0]*c4)-(udotin[0]*s4));
    Atkr[4][2] = ((Atkr[3][0]*s4)+(udotin[0]*c4));
    Atkr[5][0] = (Atkr[4][0]+(((Otkr[5][2]*rk[0][1])-(Otkr[5][1]*rk[0][2]))+((
      wk[5][1]*Wkrpk[5][2])-(wk[5][2]*Wkrpk[5][1]))));
    Atkr[5][1] = (((Atkr[3][1]*c5)+(Atkr[4][2]*s5))+(((Otkr[5][0]*rk[0][2])-(
      Otkr[5][2]*rk[0][0]))+((wk[5][2]*Wkrpk[5][0])-(wk[5][0]*Wkrpk[5][2]))));
    Atkr[5][2] = (((Atkr[4][2]*c5)-(Atkr[3][1]*s5))+(((Otkr[5][1]*rk[0][0])-(
      Otkr[5][0]*rk[0][1]))+((wk[5][0]*Wkrpk[5][1])-(wk[5][1]*Wkrpk[5][0]))));
    Atir[6][0] = (Atkr[5][0]+(((Otkr[5][1]*ri[1][2])-(Otkr[5][2]*ri[1][1]))+((
      Wirk[6][2]*wk[5][1])-(Wirk[6][1]*wk[5][2]))));
    Atir[6][1] = (Atkr[5][1]+(((Otkr[5][2]*ri[1][0])-(Otkr[5][0]*ri[1][2]))+((
      Wirk[6][0]*wk[5][2])-(Wirk[6][2]*wk[5][0]))));
    Atir[6][2] = (Atkr[5][2]+(((Otkr[5][0]*ri[1][1])-(Otkr[5][1]*ri[1][0]))+((
      Wirk[6][1]*wk[5][0])-(Wirk[6][0]*wk[5][1]))));
    Atkr[6][0] = (((Atir[6][0]*c6)+(Atir[6][1]*s6))+(((Otkr[6][2]*rk[1][1])-(
      Otkr[6][1]*rk[1][2]))+((wk[6][1]*Wkrpk[6][2])-(wk[6][2]*Wkrpk[6][1]))));
    Atkr[6][1] = (((Atir[6][1]*c6)-(Atir[6][0]*s6))+(((Otkr[6][0]*rk[1][2])-(
      Otkr[6][2]*rk[1][0]))+((wk[6][2]*Wkrpk[6][0])-(wk[6][0]*Wkrpk[6][2]))));
    Atkr[6][2] = (Atir[6][2]+(((Otkr[6][1]*rk[1][0])-(Otkr[6][0]*rk[1][1]))+((
      wk[6][0]*Wkrpk[6][1])-(wk[6][1]*Wkrpk[6][0]))));
    Atir[7][0] = (Atkr[6][0]+(((Otkr[6][1]*ri[2][2])-(Otkr[6][2]*ri[2][1]))+((
      Wirk[7][2]*wk[6][1])-(Wirk[7][1]*wk[6][2]))));
    Atir[7][1] = (Atkr[6][1]+(((Otkr[6][2]*ri[2][0])-(Otkr[6][0]*ri[2][2]))+((
      Wirk[7][0]*wk[6][2])-(Wirk[7][2]*wk[6][0]))));
    Atir[7][2] = (Atkr[6][2]+(((Otkr[6][0]*ri[2][1])-(Otkr[6][1]*ri[2][0]))+((
      Wirk[7][1]*wk[6][0])-(Wirk[7][0]*wk[6][1]))));
    Atkr[7][0] = (((Atir[7][0]*c7)-(Atir[7][2]*s7))+(((Otkr[7][2]*rk[2][1])-(
      Otkr[7][1]*rk[2][2]))+((wk[7][1]*Wkrpk[7][2])-(wk[7][2]*Wkrpk[7][1]))));
    Atkr[7][1] = (Atir[7][1]+(((Otkr[7][0]*rk[2][2])-(Otkr[7][2]*rk[2][0]))+((
      wk[7][2]*Wkrpk[7][0])-(wk[7][0]*Wkrpk[7][2]))));
    Atkr[7][2] = (((Atir[7][0]*s7)+(Atir[7][2]*c7))+(((Otkr[7][1]*rk[2][0])-(
      Otkr[7][0]*rk[2][1]))+((wk[7][0]*Wkrpk[7][1])-(wk[7][1]*Wkrpk[7][0]))));
    Atir[8][0] = (Atkr[6][0]+(((Otkr[6][1]*ri[3][2])-(Otkr[6][2]*ri[3][1]))+((
      Wirk[8][2]*wk[6][1])-(Wirk[8][1]*wk[6][2]))));
    Atir[8][1] = (Atkr[6][1]+(((Otkr[6][2]*ri[3][0])-(Otkr[6][0]*ri[3][2]))+((
      Wirk[8][0]*wk[6][2])-(Wirk[8][2]*wk[6][0]))));
    Atir[8][2] = (Atkr[6][2]+(((Otkr[6][0]*ri[3][1])-(Otkr[6][1]*ri[3][0]))+((
      Wirk[8][1]*wk[6][0])-(Wirk[8][0]*wk[6][1]))));
    Atkr[8][0] = (((Atir[8][0]*c8)-(Atir[8][2]*s8))+(((Otkr[8][2]*rk[3][1])-(
      Otkr[8][1]*rk[3][2]))+((wk[8][1]*Wkrpk[8][2])-(wk[8][2]*Wkrpk[8][1]))));
    Atkr[8][1] = (Atir[8][1]+(((Otkr[8][0]*rk[3][2])-(Otkr[8][2]*rk[3][0]))+((
      wk[8][2]*Wkrpk[8][0])-(wk[8][0]*Wkrpk[8][2]))));
    Atkr[8][2] = (((Atir[8][0]*s8)+(Atir[8][2]*c8))+(((Otkr[8][1]*rk[3][0])-(
      Otkr[8][0]*rk[3][1]))+((wk[8][0]*Wkrpk[8][1])-(wk[8][1]*Wkrpk[8][0]))));
    Atir[9][0] = (Atkr[5][0]+(((Otkr[5][1]*ri[4][2])-(Otkr[5][2]*ri[4][1]))+((
      Wirk[9][2]*wk[5][1])-(Wirk[9][1]*wk[5][2]))));
    Atir[9][1] = (Atkr[5][1]+(((Otkr[5][2]*ri[4][0])-(Otkr[5][0]*ri[4][2]))+((
      Wirk[9][0]*wk[5][2])-(Wirk[9][2]*wk[5][0]))));
    Atir[9][2] = (Atkr[5][2]+(((Otkr[5][0]*ri[4][1])-(Otkr[5][1]*ri[4][0]))+((
      Wirk[9][1]*wk[5][0])-(Wirk[9][0]*wk[5][1]))));
    Atkr[9][0] = ((Atir[9][0]*c9)+(Atir[9][1]*s9));
    Atkr[9][1] = ((Atir[9][1]*c9)-(Atir[9][0]*s9));
    Atkr[10][1] = ((Atir[9][2]*s10)+(Atkr[9][1]*c10));
    Atkr[10][2] = ((Atir[9][2]*c10)-(Atkr[9][1]*s10));
    Atkr[11][0] = (((Atkr[9][0]*c11)-(Atkr[10][2]*s11))+(((Otkr[11][2]*rk[4][1])
      -(Otkr[11][1]*rk[4][2]))+((wk[11][1]*Wkrpk[11][2])-(wk[11][2]*Wkrpk[11][1]
      ))));
    Atkr[11][1] = (Atkr[10][1]+(((Otkr[11][0]*rk[4][2])-(Otkr[11][2]*rk[4][0]))+
      ((wk[11][2]*Wkrpk[11][0])-(wk[11][0]*Wkrpk[11][2]))));
    Atkr[11][2] = (((Atkr[9][0]*s11)+(Atkr[10][2]*c11))+(((Otkr[11][1]*rk[4][0])
      -(Otkr[11][0]*rk[4][1]))+((wk[11][0]*Wkrpk[11][1])-(wk[11][1]*Wkrpk[11][0]
      ))));
    Atir[12][0] = (Atkr[11][0]+(((Otkr[11][1]*ri[5][2])-(Otkr[11][2]*ri[5][1]))+
      ((Wirk[12][2]*wk[11][1])-(Wirk[12][1]*wk[11][2]))));
    Atir[12][1] = (Atkr[11][1]+(((Otkr[11][2]*ri[5][0])-(Otkr[11][0]*ri[5][2]))+
      ((Wirk[12][0]*wk[11][2])-(Wirk[12][2]*wk[11][0]))));
    Atir[12][2] = (Atkr[11][2]+(((Otkr[11][0]*ri[5][1])-(Otkr[11][1]*ri[5][0]))+
      ((Wirk[12][1]*wk[11][0])-(Wirk[12][0]*wk[11][1]))));
    Atkr[12][0] = (((Atir[12][0]*c12)-(Atir[12][2]*s12))+(((Otkr[12][2]*rk[5][1]
      )-(Otkr[12][1]*rk[5][2]))+((wk[12][1]*Wkrpk[12][2])-(wk[12][2]*
      Wkrpk[12][1]))));
    Atkr[12][1] = (Atir[12][1]+(((Otkr[12][0]*rk[5][2])-(Otkr[12][2]*rk[5][0]))+
      ((wk[12][2]*Wkrpk[12][0])-(wk[12][0]*Wkrpk[12][2]))));
    Atkr[12][2] = (((Atir[12][0]*s12)+(Atir[12][2]*c12))+(((Otkr[12][1]*rk[5][0]
      )-(Otkr[12][0]*rk[5][1]))+((wk[12][0]*Wkrpk[12][1])-(wk[12][1]*
      Wkrpk[12][0]))));
    Atir[13][0] = (Atkr[12][0]+(((Otkr[12][1]*ri[6][2])-(Otkr[12][2]*ri[6][1]))+
      ((Wirk[13][2]*wk[12][1])-(Wirk[13][1]*wk[12][2]))));
    Atir[13][1] = (Atkr[12][1]+(((Otkr[12][2]*ri[6][0])-(Otkr[12][0]*ri[6][2]))+
      ((Wirk[13][0]*wk[12][2])-(Wirk[13][2]*wk[12][0]))));
    Atir[13][2] = (Atkr[12][2]+(((Otkr[12][0]*ri[6][1])-(Otkr[12][1]*ri[6][0]))+
      ((Wirk[13][1]*wk[12][0])-(Wirk[13][0]*wk[12][1]))));
    Atkr[13][0] = ((Atir[13][0]*c13)-(Atir[13][2]*s13));
    Atkr[13][2] = ((Atir[13][0]*s13)+(Atir[13][2]*c13));
    Atkr[14][0] = (Atkr[13][0]+(((Otkr[14][2]*rk[6][1])-(Otkr[14][1]*rk[6][2]))+
      ((wk[14][1]*Wkrpk[14][2])-(wk[14][2]*Wkrpk[14][1]))));
    Atkr[14][1] = (((Atir[13][1]*c14)+(Atkr[13][2]*s14))+(((Otkr[14][0]*rk[6][2]
      )-(Otkr[14][2]*rk[6][0]))+((wk[14][2]*Wkrpk[14][0])-(wk[14][0]*
      Wkrpk[14][2]))));
    Atkr[14][2] = (((Atkr[13][2]*c14)-(Atir[13][1]*s14))+(((Otkr[14][1]*rk[6][0]
      )-(Otkr[14][0]*rk[6][1]))+((wk[14][0]*Wkrpk[14][1])-(wk[14][1]*
      Wkrpk[14][0]))));
    Atir[15][0] = (Atkr[5][0]+(((Otkr[5][1]*ri[7][2])-(Otkr[5][2]*ri[7][1]))+((
      Wirk[15][2]*wk[5][1])-(Wirk[15][1]*wk[5][2]))));
    Atir[15][1] = (Atkr[5][1]+(((Otkr[5][2]*ri[7][0])-(Otkr[5][0]*ri[7][2]))+((
      Wirk[15][0]*wk[5][2])-(Wirk[15][2]*wk[5][0]))));
    Atir[15][2] = (Atkr[5][2]+(((Otkr[5][0]*ri[7][1])-(Otkr[5][1]*ri[7][0]))+((
      Wirk[15][1]*wk[5][0])-(Wirk[15][0]*wk[5][1]))));
    Atkr[15][0] = ((Atir[15][0]*c15)+(Atir[15][1]*s15));
    Atkr[15][1] = ((Atir[15][1]*c15)-(Atir[15][0]*s15));
    Atkr[16][1] = ((Atir[15][2]*s16)+(Atkr[15][1]*c16));
    Atkr[16][2] = ((Atir[15][2]*c16)-(Atkr[15][1]*s16));
    Atkr[17][0] = (((Atkr[15][0]*c17)-(Atkr[16][2]*s17))+(((Otkr[17][2]*rk[7][1]
      )-(Otkr[17][1]*rk[7][2]))+((wk[17][1]*Wkrpk[17][2])-(wk[17][2]*
      Wkrpk[17][1]))));
    Atkr[17][1] = (Atkr[16][1]+(((Otkr[17][0]*rk[7][2])-(Otkr[17][2]*rk[7][0]))+
      ((wk[17][2]*Wkrpk[17][0])-(wk[17][0]*Wkrpk[17][2]))));
    Atkr[17][2] = (((Atkr[15][0]*s17)+(Atkr[16][2]*c17))+(((Otkr[17][1]*rk[7][0]
      )-(Otkr[17][0]*rk[7][1]))+((wk[17][0]*Wkrpk[17][1])-(wk[17][1]*
      Wkrpk[17][0]))));
    Atir[18][0] = (Atkr[17][0]+(((Otkr[17][1]*ri[8][2])-(Otkr[17][2]*ri[8][1]))+
      ((Wirk[18][2]*wk[17][1])-(Wirk[18][1]*wk[17][2]))));
    Atir[18][1] = (Atkr[17][1]+(((Otkr[17][2]*ri[8][0])-(Otkr[17][0]*ri[8][2]))+
      ((Wirk[18][0]*wk[17][2])-(Wirk[18][2]*wk[17][0]))));
    Atir[18][2] = (Atkr[17][2]+(((Otkr[17][0]*ri[8][1])-(Otkr[17][1]*ri[8][0]))+
      ((Wirk[18][1]*wk[17][0])-(Wirk[18][0]*wk[17][1]))));
    Atkr[18][0] = (((Atir[18][0]*c18)-(Atir[18][2]*s18))+(((Otkr[18][2]*rk[8][1]
      )-(Otkr[18][1]*rk[8][2]))+((wk[18][1]*Wkrpk[18][2])-(wk[18][2]*
      Wkrpk[18][1]))));
    Atkr[18][1] = (Atir[18][1]+(((Otkr[18][0]*rk[8][2])-(Otkr[18][2]*rk[8][0]))+
      ((wk[18][2]*Wkrpk[18][0])-(wk[18][0]*Wkrpk[18][2]))));
    Atkr[18][2] = (((Atir[18][0]*s18)+(Atir[18][2]*c18))+(((Otkr[18][1]*rk[8][0]
      )-(Otkr[18][0]*rk[8][1]))+((wk[18][0]*Wkrpk[18][1])-(wk[18][1]*
      Wkrpk[18][0]))));
    Atir[19][0] = (Atkr[18][0]+(((Otkr[18][1]*ri[9][2])-(Otkr[18][2]*ri[9][1]))+
      ((Wirk[19][2]*wk[18][1])-(Wirk[19][1]*wk[18][2]))));
    Atir[19][1] = (Atkr[18][1]+(((Otkr[18][2]*ri[9][0])-(Otkr[18][0]*ri[9][2]))+
      ((Wirk[19][0]*wk[18][2])-(Wirk[19][2]*wk[18][0]))));
    Atir[19][2] = (Atkr[18][2]+(((Otkr[18][0]*ri[9][1])-(Otkr[18][1]*ri[9][0]))+
      ((Wirk[19][1]*wk[18][0])-(Wirk[19][0]*wk[18][1]))));
    Atkr[19][0] = ((Atir[19][0]*c19)-(Atir[19][2]*s19));
    Atkr[19][2] = ((Atir[19][0]*s19)+(Atir[19][2]*c19));
    Atkr[20][0] = (Atkr[19][0]+(((Otkr[20][2]*rk[9][1])-(Otkr[20][1]*rk[9][2]))+
      ((wk[20][1]*Wkrpk[20][2])-(wk[20][2]*Wkrpk[20][1]))));
    Atkr[20][1] = (((Atir[19][1]*c20)+(Atkr[19][2]*s20))+(((Otkr[20][0]*rk[9][2]
      )-(Otkr[20][2]*rk[9][0]))+((wk[20][2]*Wkrpk[20][0])-(wk[20][0]*
      Wkrpk[20][2]))));
    Atkr[20][2] = (((Atkr[19][2]*c20)-(Atir[19][1]*s20))+(((Otkr[20][1]*rk[9][0]
      )-(Otkr[20][0]*rk[9][1]))+((wk[20][0]*Wkrpk[20][1])-(wk[20][1]*
      Wkrpk[20][0]))));
/*
Accumulate all forces and torques
*/
    fstarr[5][0] = (ufk[0][0]+(mk[0]*((9.8*s4)-Atkr[5][0])));
    fstarr[5][1] = (ufk[0][1]+(mk[0]*(gk[5][1]-Atkr[5][1])));
    fstarr[5][2] = (ufk[0][2]+(mk[0]*(gk[5][2]-Atkr[5][2])));
    fstarr[6][0] = (ufk[1][0]+(mk[1]*(gk[6][0]-Atkr[6][0])));
    fstarr[6][1] = (ufk[1][1]+(mk[1]*(gk[6][1]-Atkr[6][1])));
    fstarr[6][2] = (ufk[1][2]+(mk[1]*(gk[5][2]-Atkr[6][2])));
    fstarr[7][0] = (ufk[2][0]+(mk[2]*(gk[7][0]-Atkr[7][0])));
    fstarr[7][1] = (ufk[2][1]+(mk[2]*(gk[6][1]-Atkr[7][1])));
    fstarr[7][2] = (ufk[2][2]+(mk[2]*(gk[7][2]-Atkr[7][2])));
    fstarr[8][0] = (ufk[3][0]+(mk[3]*(gk[8][0]-Atkr[8][0])));
    fstarr[8][1] = (ufk[3][1]+(mk[3]*(gk[6][1]-Atkr[8][1])));
    fstarr[8][2] = (ufk[3][2]+(mk[3]*(gk[8][2]-Atkr[8][2])));
    fstarr[11][0] = (ufk[4][0]+(mk[4]*(gk[11][0]-Atkr[11][0])));
    fstarr[11][1] = (ufk[4][1]+(mk[4]*(gk[10][1]-Atkr[11][1])));
    fstarr[11][2] = (ufk[4][2]+(mk[4]*(gk[11][2]-Atkr[11][2])));
    fstarr[12][0] = (ufk[5][0]+(mk[5]*(gk[12][0]-Atkr[12][0])));
    fstarr[12][1] = (ufk[5][1]+(mk[5]*(gk[10][1]-Atkr[12][1])));
    fstarr[12][2] = (ufk[5][2]+(mk[5]*(gk[12][2]-Atkr[12][2])));
    fstarr[14][0] = (ufk[6][0]+(mk[6]*(gk[13][0]-Atkr[14][0])));
    fstarr[14][1] = (ufk[6][1]+(mk[6]*(gk[14][1]-Atkr[14][1])));
    fstarr[14][2] = (ufk[6][2]+(mk[6]*(gk[14][2]-Atkr[14][2])));
    fstarr[17][0] = (ufk[7][0]+(mk[7]*(gk[17][0]-Atkr[17][0])));
    fstarr[17][1] = (ufk[7][1]+(mk[7]*(gk[16][1]-Atkr[17][1])));
    fstarr[17][2] = (ufk[7][2]+(mk[7]*(gk[17][2]-Atkr[17][2])));
    fstarr[18][0] = (ufk[8][0]+(mk[8]*(gk[18][0]-Atkr[18][0])));
    fstarr[18][1] = (ufk[8][1]+(mk[8]*(gk[16][1]-Atkr[18][1])));
    fstarr[18][2] = (ufk[8][2]+(mk[8]*(gk[18][2]-Atkr[18][2])));
    fstarr[20][0] = (ufk[9][0]+(mk[9]*(gk[19][0]-Atkr[20][0])));
    fstarr[20][1] = (ufk[9][1]+(mk[9]*(gk[20][1]-Atkr[20][1])));
    fstarr[20][2] = (ufk[9][2]+(mk[9]*(gk[20][2]-Atkr[20][2])));
    tstarr[5][0] = (utk[0][0]-(WkIkWk[5][0]+(ik[0][0][0]*Otkr[5][0])));
    tstarr[5][1] = (utk[0][1]-(WkIkWk[5][1]+(ik[0][1][1]*Otkr[5][1])));
    tstarr[5][2] = (utk[0][2]-(WkIkWk[5][2]+(ik[0][2][2]*Otkr[5][2])));
    tstarr[6][0] = (utk[1][0]-(WkIkWk[6][0]+(ik[1][0][0]*Otkr[6][0])));
    tstarr[6][1] = (utk[1][1]-(WkIkWk[6][1]+(ik[1][1][1]*Otkr[6][1])));
    tstarr[6][2] = (utk[1][2]-(WkIkWk[6][2]+(ik[1][2][2]*Otkr[6][2])));
    tstarr[7][0] = (utk[2][0]-(WkIkWk[7][0]+(ik[2][0][0]*Otkr[7][0])));
    tstarr[7][1] = (utk[2][1]-(WkIkWk[7][1]+(ik[2][1][1]*Otkr[7][1])));
    tstarr[7][2] = (utk[2][2]-(WkIkWk[7][2]+(ik[2][2][2]*Otkr[7][2])));
    tstarr[8][0] = (utk[3][0]-(WkIkWk[8][0]+(ik[3][0][0]*Otkr[8][0])));
    tstarr[8][1] = (utk[3][1]-(WkIkWk[8][1]+(ik[3][1][1]*Otkr[8][1])));
    tstarr[8][2] = (utk[3][2]-(WkIkWk[8][2]+(ik[3][2][2]*Otkr[8][2])));
    tstarr[11][0] = (utk[4][0]-(WkIkWk[11][0]+(ik[4][0][0]*Otkr[11][0])));
    tstarr[11][1] = (utk[4][1]-(WkIkWk[11][1]+(ik[4][1][1]*Otkr[11][1])));
    tstarr[11][2] = (utk[4][2]-(WkIkWk[11][2]+(ik[4][2][2]*Otkr[11][2])));
    tstarr[12][0] = (utk[5][0]-(WkIkWk[12][0]+(ik[5][0][0]*Otkr[12][0])));
    tstarr[12][1] = (utk[5][1]-(WkIkWk[12][1]+(ik[5][1][1]*Otkr[12][1])));
    tstarr[12][2] = (utk[5][2]-(WkIkWk[12][2]+(ik[5][2][2]*Otkr[12][2])));
    tstarr[14][0] = (utk[6][0]-(WkIkWk[14][0]+(ik[6][0][0]*Otkr[14][0])));
    tstarr[14][1] = (utk[6][1]-(WkIkWk[14][1]+(ik[6][1][1]*Otkr[14][1])));
    tstarr[14][2] = (utk[6][2]-(WkIkWk[14][2]+(ik[6][2][2]*Otkr[14][2])));
    tstarr[17][0] = (utk[7][0]-(WkIkWk[17][0]+(ik[7][0][0]*Otkr[17][0])));
    tstarr[17][1] = (utk[7][1]-(WkIkWk[17][1]+(ik[7][1][1]*Otkr[17][1])));
    tstarr[17][2] = (utk[7][2]-(WkIkWk[17][2]+(ik[7][2][2]*Otkr[17][2])));
    tstarr[18][0] = (utk[8][0]-(WkIkWk[18][0]+(ik[8][0][0]*Otkr[18][0])));
    tstarr[18][1] = (utk[8][1]-(WkIkWk[18][1]+(ik[8][1][1]*Otkr[18][1])));
    tstarr[18][2] = (utk[8][2]-(WkIkWk[18][2]+(ik[8][2][2]*Otkr[18][2])));
    tstarr[20][0] = (utk[9][0]-(WkIkWk[20][0]+(ik[9][0][0]*Otkr[20][0])));
    tstarr[20][1] = (utk[9][1]-(WkIkWk[20][1]+(ik[9][1][1]*Otkr[20][1])));
    tstarr[20][2] = (utk[9][2]-(WkIkWk[20][2]+(ik[9][2][2]*Otkr[20][2])));
/*
Now calculate the torques
*/
    sddovpk();
    temp[0] = (((fstarr[8][2]*Vpk[0][8][2])+((fstarr[8][0]*Vpk[0][8][0])+(
      fstarr[8][1]*Vpk[0][6][1])))+(((fstarr[7][2]*Vpk[0][7][2])+((fstarr[7][0]*
      Vpk[0][7][0])+(fstarr[7][1]*Vpk[0][6][1])))+(((fstarr[5][2]*Vpk[0][5][2])+
      ((fstarr[5][1]*Vpk[0][5][1])-(fstarr[5][0]*s4)))+((fstarr[6][2]*
      Vpk[0][5][2])+((fstarr[6][0]*Vpk[0][6][0])+(fstarr[6][1]*Vpk[0][6][1])))))
      );
    temp[1] = (((fstarr[17][2]*Vpk[0][17][2])+((fstarr[17][0]*Vpk[0][17][0])+(
      fstarr[17][1]*Vpk[0][16][1])))+(((fstarr[14][2]*Vpk[0][14][2])+((
      fstarr[14][0]*Vpk[0][13][0])+(fstarr[14][1]*Vpk[0][14][1])))+(((
      fstarr[12][2]*Vpk[0][12][2])+((fstarr[12][0]*Vpk[0][12][0])+(fstarr[12][1]
      *Vpk[0][10][1])))+(((fstarr[11][2]*Vpk[0][11][2])+((fstarr[11][0]*
      Vpk[0][11][0])+(fstarr[11][1]*Vpk[0][10][1])))+temp[0]))));
    trqout[0] = -(utau[0]+(((fstarr[20][2]*Vpk[0][20][2])+((fstarr[20][0]*
      Vpk[0][19][0])+(fstarr[20][1]*Vpk[0][20][1])))+(((fstarr[18][2]*
      Vpk[0][18][2])+((fstarr[18][0]*Vpk[0][18][0])+(fstarr[18][1]*Vpk[0][16][1]
      )))+temp[1])));
    temp[0] = (((fstarr[8][2]*Vpk[1][8][2])+((fstarr[8][0]*Vpk[1][8][0])+(
      fstarr[8][1]*Vpk[1][6][1])))+(((fstarr[7][2]*Vpk[1][7][2])+((fstarr[7][0]*
      Vpk[1][7][0])+(fstarr[7][1]*Vpk[1][6][1])))+(((fstarr[5][2]*Vpk[1][5][2])+
      ((fstarr[5][0]*Vpk[1][4][0])+(fstarr[5][1]*Vpk[1][5][1])))+((fstarr[6][2]*
      Vpk[1][5][2])+((fstarr[6][0]*Vpk[1][6][0])+(fstarr[6][1]*Vpk[1][6][1])))))
      );
    temp[1] = (((fstarr[17][2]*Vpk[1][17][2])+((fstarr[17][0]*Vpk[1][17][0])+(
      fstarr[17][1]*Vpk[1][16][1])))+(((fstarr[14][2]*Vpk[1][14][2])+((
      fstarr[14][0]*Vpk[1][13][0])+(fstarr[14][1]*Vpk[1][14][1])))+(((
      fstarr[12][2]*Vpk[1][12][2])+((fstarr[12][0]*Vpk[1][12][0])+(fstarr[12][1]
      *Vpk[1][10][1])))+(((fstarr[11][2]*Vpk[1][11][2])+((fstarr[11][0]*
      Vpk[1][11][0])+(fstarr[11][1]*Vpk[1][10][1])))+temp[0]))));
    trqout[1] = -(utau[1]+(((fstarr[20][2]*Vpk[1][20][2])+((fstarr[20][0]*
      Vpk[1][19][0])+(fstarr[20][1]*Vpk[1][20][1])))+(((fstarr[18][2]*
      Vpk[1][18][2])+((fstarr[18][0]*Vpk[1][18][0])+(fstarr[18][1]*Vpk[1][16][1]
      )))+temp[1])));
    temp[0] = (((fstarr[8][2]*Vpk[2][8][2])+((fstarr[8][0]*Vpk[2][8][0])+(
      fstarr[8][1]*Vpk[2][6][1])))+(((fstarr[7][2]*Vpk[2][7][2])+((fstarr[7][0]*
      Vpk[2][7][0])+(fstarr[7][1]*Vpk[2][6][1])))+(((fstarr[5][2]*Vpk[2][5][2])+
      ((fstarr[5][0]*Vpk[2][4][0])+(fstarr[5][1]*Vpk[2][5][1])))+((fstarr[6][2]*
      Vpk[2][5][2])+((fstarr[6][0]*Vpk[2][6][0])+(fstarr[6][1]*Vpk[2][6][1])))))
      );
    temp[1] = (((fstarr[17][2]*Vpk[2][17][2])+((fstarr[17][0]*Vpk[2][17][0])+(
      fstarr[17][1]*Vpk[2][16][1])))+(((fstarr[14][2]*Vpk[2][14][2])+((
      fstarr[14][0]*Vpk[2][13][0])+(fstarr[14][1]*Vpk[2][14][1])))+(((
      fstarr[12][2]*Vpk[2][12][2])+((fstarr[12][0]*Vpk[2][12][0])+(fstarr[12][1]
      *Vpk[2][10][1])))+(((fstarr[11][2]*Vpk[2][11][2])+((fstarr[11][0]*
      Vpk[2][11][0])+(fstarr[11][1]*Vpk[2][10][1])))+temp[0]))));
    trqout[2] = -(utau[2]+(((fstarr[20][2]*Vpk[2][20][2])+((fstarr[20][0]*
      Vpk[2][19][0])+(fstarr[20][1]*Vpk[2][20][1])))+(((fstarr[18][2]*
      Vpk[2][18][2])+((fstarr[18][0]*Vpk[2][18][0])+(fstarr[18][1]*Vpk[2][16][1]
      )))+temp[1])));
    temp[0] = ((((fstarr[5][2]*Vpk[3][5][2])+((fstarr[5][0]*Vpk[3][5][0])+(
      fstarr[5][1]*Vpk[3][5][1])))+((tstarr[5][2]*Wpk[3][5][2])+((tstarr[5][1]*
      Wpk[3][5][1])-(tstarr[5][0]*s4))))+(((fstarr[6][2]*Vpk[3][6][2])+((
      fstarr[6][0]*Vpk[3][6][0])+(fstarr[6][1]*Vpk[3][6][1])))+((tstarr[6][2]*
      Wpk[3][5][2])+((tstarr[6][0]*Wpk[3][6][0])+(tstarr[6][1]*Wpk[3][6][1])))))
      ;
    temp[1] = ((((fstarr[8][2]*Vpk[3][8][2])+((fstarr[8][0]*Vpk[3][8][0])+(
      fstarr[8][1]*Vpk[3][8][1])))+((tstarr[8][2]*Wpk[3][8][2])+((tstarr[8][0]*
      Wpk[3][8][0])+(tstarr[8][1]*Wpk[3][6][1]))))+((((fstarr[7][2]*Vpk[3][7][2]
      )+((fstarr[7][0]*Vpk[3][7][0])+(fstarr[7][1]*Vpk[3][7][1])))+((
      tstarr[7][2]*Wpk[3][7][2])+((tstarr[7][0]*Wpk[3][7][0])+(tstarr[7][1]*
      Wpk[3][6][1]))))+temp[0]));
    temp[2] = ((((fstarr[12][2]*Vpk[3][12][2])+((fstarr[12][0]*Vpk[3][12][0])+(
      fstarr[12][1]*Vpk[3][12][1])))+((tstarr[12][2]*Wpk[3][12][2])+((
      tstarr[12][0]*Wpk[3][12][0])+(tstarr[12][1]*Wpk[3][10][1]))))+((((
      fstarr[11][2]*Vpk[3][11][2])+((fstarr[11][0]*Vpk[3][11][0])+(fstarr[11][1]
      *Vpk[3][11][1])))+((tstarr[11][2]*Wpk[3][11][2])+((tstarr[11][0]*
      Wpk[3][11][0])+(tstarr[11][1]*Wpk[3][10][1]))))+temp[1]));
    temp[3] = ((((fstarr[17][2]*Vpk[3][17][2])+((fstarr[17][0]*Vpk[3][17][0])+(
      fstarr[17][1]*Vpk[3][17][1])))+((tstarr[17][2]*Wpk[3][17][2])+((
      tstarr[17][0]*Wpk[3][17][0])+(tstarr[17][1]*Wpk[3][16][1]))))+((((
      fstarr[14][2]*Vpk[3][14][2])+((fstarr[14][0]*Vpk[3][14][0])+(fstarr[14][1]
      *Vpk[3][14][1])))+((tstarr[14][2]*Wpk[3][14][2])+((tstarr[14][0]*
      Wpk[3][13][0])+(tstarr[14][1]*Wpk[3][14][1]))))+temp[2]));
    trqout[3] = -(utau[3]+((((fstarr[20][2]*Vpk[3][20][2])+((fstarr[20][0]*
      Vpk[3][20][0])+(fstarr[20][1]*Vpk[3][20][1])))+((tstarr[20][2]*
      Wpk[3][20][2])+((tstarr[20][0]*Wpk[3][19][0])+(tstarr[20][1]*Wpk[3][20][1]
      ))))+((((fstarr[18][2]*Vpk[3][18][2])+((fstarr[18][0]*Vpk[3][18][0])+(
      fstarr[18][1]*Vpk[3][18][1])))+((tstarr[18][2]*Wpk[3][18][2])+((
      tstarr[18][0]*Wpk[3][18][0])+(tstarr[18][1]*Wpk[3][16][1]))))+temp[3])));
    temp[0] = ((((fstarr[5][2]*Vpk[4][5][2])+((fstarr[5][0]*Vpk[4][5][0])+(
      fstarr[5][1]*Vpk[4][5][1])))+((tstarr[5][1]*c5)-(tstarr[5][2]*s5)))+(((
      fstarr[6][2]*Vpk[4][6][2])+((fstarr[6][0]*Vpk[4][6][0])+(fstarr[6][1]*
      Vpk[4][6][1])))+(((tstarr[6][0]*Wpk[4][6][0])+(tstarr[6][1]*Wpk[4][6][1]))
      -(tstarr[6][2]*s5))));
    temp[1] = ((((fstarr[8][2]*Vpk[4][8][2])+((fstarr[8][0]*Vpk[4][8][0])+(
      fstarr[8][1]*Vpk[4][8][1])))+((tstarr[8][2]*Wpk[4][8][2])+((tstarr[8][0]*
      Wpk[4][8][0])+(tstarr[8][1]*Wpk[4][6][1]))))+((((fstarr[7][2]*Vpk[4][7][2]
      )+((fstarr[7][0]*Vpk[4][7][0])+(fstarr[7][1]*Vpk[4][7][1])))+((
      tstarr[7][2]*Wpk[4][7][2])+((tstarr[7][0]*Wpk[4][7][0])+(tstarr[7][1]*
      Wpk[4][6][1]))))+temp[0]));
    temp[2] = ((((fstarr[12][2]*Vpk[4][12][2])+((fstarr[12][0]*Vpk[4][12][0])+(
      fstarr[12][1]*Vpk[4][12][1])))+((tstarr[12][2]*Wpk[4][12][2])+((
      tstarr[12][0]*Wpk[4][12][0])+(tstarr[12][1]*Wpk[4][10][1]))))+((((
      fstarr[11][2]*Vpk[4][11][2])+((fstarr[11][0]*Vpk[4][11][0])+(fstarr[11][1]
      *Vpk[4][11][1])))+((tstarr[11][2]*Wpk[4][11][2])+((tstarr[11][0]*
      Wpk[4][11][0])+(tstarr[11][1]*Wpk[4][10][1]))))+temp[1]));
    temp[3] = ((((fstarr[17][2]*Vpk[4][17][2])+((fstarr[17][0]*Vpk[4][17][0])+(
      fstarr[17][1]*Vpk[4][17][1])))+((tstarr[17][2]*Wpk[4][17][2])+((
      tstarr[17][0]*Wpk[4][17][0])+(tstarr[17][1]*Wpk[4][16][1]))))+((((
      fstarr[14][2]*Vpk[4][14][2])+((fstarr[14][0]*Vpk[4][14][0])+(fstarr[14][1]
      *Vpk[4][14][1])))+((tstarr[14][2]*Wpk[4][14][2])+((tstarr[14][0]*
      Wpk[4][13][0])+(tstarr[14][1]*Wpk[4][14][1]))))+temp[2]));
    trqout[4] = -(utau[4]+((((fstarr[20][2]*Vpk[4][20][2])+((fstarr[20][0]*
      Vpk[4][20][0])+(fstarr[20][1]*Vpk[4][20][1])))+((tstarr[20][2]*
      Wpk[4][20][2])+((tstarr[20][0]*Wpk[4][19][0])+(tstarr[20][1]*Wpk[4][20][1]
      ))))+((((fstarr[18][2]*Vpk[4][18][2])+((fstarr[18][0]*Vpk[4][18][0])+(
      fstarr[18][1]*Vpk[4][18][1])))+((tstarr[18][2]*Wpk[4][18][2])+((
      tstarr[18][0]*Wpk[4][18][0])+(tstarr[18][1]*Wpk[4][16][1]))))+temp[3])));
    temp[0] = (((tstarr[5][0]+((fstarr[5][1]*rk[0][2])-(fstarr[5][2]*rk[0][1])))
      +(((fstarr[6][2]*Vpk[5][6][2])+((fstarr[6][0]*Vpk[5][6][0])+(fstarr[6][1]*
      Vpk[5][6][1])))+((tstarr[6][0]*c6)-(tstarr[6][1]*s6))))+(((fstarr[7][2]*
      Vpk[5][7][2])+((fstarr[7][0]*Vpk[5][7][0])+(fstarr[7][1]*Vpk[5][7][1])))+(
      (tstarr[7][2]*Wpk[5][7][2])+((tstarr[7][0]*Wpk[5][7][0])-(tstarr[7][1]*s6)
      ))));
    temp[1] = ((((fstarr[11][2]*Vpk[5][11][2])+((fstarr[11][0]*Vpk[5][11][0])+(
      fstarr[11][1]*Vpk[5][11][1])))+((tstarr[11][2]*Wpk[5][11][2])+((
      tstarr[11][0]*Wpk[5][11][0])+(tstarr[11][1]*Wpk[5][10][1]))))+((((
      fstarr[8][2]*Vpk[5][8][2])+((fstarr[8][0]*Vpk[5][8][0])+(fstarr[8][1]*
      Vpk[5][8][1])))+((tstarr[8][2]*Wpk[5][8][2])+((tstarr[8][0]*Wpk[5][8][0])-
      (tstarr[8][1]*s6))))+temp[0]));
    temp[2] = ((((fstarr[14][2]*Vpk[5][14][2])+((fstarr[14][0]*Vpk[5][14][0])+(
      fstarr[14][1]*Vpk[5][14][1])))+((tstarr[14][2]*Wpk[5][14][2])+((
      tstarr[14][0]*Wpk[5][13][0])+(tstarr[14][1]*Wpk[5][14][1]))))+((((
      fstarr[12][2]*Vpk[5][12][2])+((fstarr[12][0]*Vpk[5][12][0])+(fstarr[12][1]
      *Vpk[5][12][1])))+((tstarr[12][2]*Wpk[5][12][2])+((tstarr[12][0]*
      Wpk[5][12][0])+(tstarr[12][1]*Wpk[5][10][1]))))+temp[1]));
    temp[3] = ((((fstarr[18][2]*Vpk[5][18][2])+((fstarr[18][0]*Vpk[5][18][0])+(
      fstarr[18][1]*Vpk[5][18][1])))+((tstarr[18][2]*Wpk[5][18][2])+((
      tstarr[18][0]*Wpk[5][18][0])+(tstarr[18][1]*Wpk[5][16][1]))))+((((
      fstarr[17][2]*Vpk[5][17][2])+((fstarr[17][0]*Vpk[5][17][0])+(fstarr[17][1]
      *Vpk[5][17][1])))+((tstarr[17][2]*Wpk[5][17][2])+((tstarr[17][0]*
      Wpk[5][17][0])+(tstarr[17][1]*Wpk[5][16][1]))))+temp[2]));
    trqout[5] = -(utau[5]+((((fstarr[20][2]*Vpk[5][20][2])+((fstarr[20][0]*
      Vpk[5][20][0])+(fstarr[20][1]*Vpk[5][20][1])))+((tstarr[20][2]*
      Wpk[5][20][2])+((tstarr[20][0]*Wpk[5][19][0])+(tstarr[20][1]*Wpk[5][20][1]
      ))))+temp[3]));
    trqout[6] = -(utau[6]+(((tstarr[6][2]+((fstarr[6][0]*rk[1][1])-(fstarr[6][1]
      *rk[1][0])))+(((fstarr[7][2]*Vpk[6][7][2])+((fstarr[7][0]*Vpk[6][7][0])+(
      fstarr[7][1]*Vpk[6][7][1])))+((tstarr[7][2]*c7)-(tstarr[7][0]*s7))))+(((
      fstarr[8][2]*Vpk[6][8][2])+((fstarr[8][0]*Vpk[6][8][0])+(fstarr[8][1]*
      Vpk[6][8][1])))+((tstarr[8][2]*c8)-(tstarr[8][0]*s8)))));
    trqout[7] = -(utau[7]+(tstarr[7][1]+((fstarr[7][2]*rk[2][0])-(fstarr[7][0]*
      rk[2][2]))));
    trqout[8] = -(utau[8]+(tstarr[8][1]+((fstarr[8][2]*rk[3][0])-(fstarr[8][0]*
      rk[3][2]))));
    temp[0] = ((((fstarr[11][2]*Vpk[9][11][2])+((fstarr[11][0]*Vpk[9][11][0])+(
      fstarr[11][1]*Vpk[9][11][1])))+((tstarr[11][2]*Wpk[9][11][2])+((
      tstarr[11][0]*Wpk[9][11][0])+(tstarr[11][1]*s10))))+(((fstarr[12][2]*
      Vpk[9][12][2])+((fstarr[12][0]*Vpk[9][12][0])+(fstarr[12][1]*Vpk[9][12][1]
      )))+((tstarr[12][2]*Wpk[9][12][2])+((tstarr[12][0]*Wpk[9][12][0])+(
      tstarr[12][1]*s10)))));
    trqout[9] = -(utau[9]+((((fstarr[14][2]*Vpk[9][14][2])+((fstarr[14][0]*
      Vpk[9][14][0])+(fstarr[14][1]*Vpk[9][14][1])))+((tstarr[14][2]*
      Wpk[9][14][2])+((tstarr[14][0]*Wpk[9][13][0])+(tstarr[14][1]*Wpk[9][14][1]
      ))))+temp[0]));
    temp[0] = ((((fstarr[11][2]*Vpk[10][11][2])+((fstarr[11][0]*Vpk[10][11][0])+
      (fstarr[11][1]*Vpk[10][11][1])))+((tstarr[11][0]*c11)+(tstarr[11][2]*s11))
      )+(((fstarr[12][2]*Vpk[10][12][2])+((fstarr[12][0]*Vpk[10][12][0])+(
      fstarr[12][1]*Vpk[10][12][1])))+((tstarr[12][0]*Wpk[10][12][0])+(
      tstarr[12][2]*Wpk[10][12][2]))));
    trqout[10] = -(utau[10]+((((fstarr[14][2]*Vpk[10][14][2])+((fstarr[14][0]*
      Vpk[10][14][0])+(fstarr[14][1]*Vpk[10][14][1])))+((tstarr[14][2]*
      Wpk[10][14][2])+((tstarr[14][0]*Wpk[10][13][0])+(tstarr[14][1]*
      Wpk[10][14][1]))))+temp[0]));
    trqout[11] = -(utau[11]+(((tstarr[11][1]+((fstarr[11][2]*rk[4][0])-(
      fstarr[11][0]*rk[4][2])))+(tstarr[12][1]+((fstarr[12][0]*Vpk[11][12][0])+(
      fstarr[12][2]*Vpk[11][12][2]))))+(((fstarr[14][2]*Vpk[11][14][2])+((
      fstarr[14][0]*Vpk[11][14][0])+(fstarr[14][1]*Vpk[11][14][1])))+((
      tstarr[14][1]*c14)-(tstarr[14][2]*s14)))));
    trqout[12] = -(utau[12]+((tstarr[12][1]+((fstarr[12][2]*rk[5][0])-(
      fstarr[12][0]*rk[5][2])))+(((fstarr[14][2]*Vpk[12][14][2])+((fstarr[14][0]
      *Vpk[12][14][0])+(fstarr[14][1]*Vpk[12][14][1])))+((tstarr[14][1]*c14)-(
      tstarr[14][2]*s14)))));
    trqout[13] = -(utau[13]+(((fstarr[14][2]*Vpk[13][14][2])+((fstarr[14][0]*
      Vpk[13][14][0])+(fstarr[14][1]*Vpk[13][14][1])))+((tstarr[14][1]*c14)-(
      tstarr[14][2]*s14))));
    trqout[14] = -(utau[14]+(tstarr[14][0]+((fstarr[14][1]*rk[6][2])-(
      fstarr[14][2]*rk[6][1]))));
    temp[0] = ((((fstarr[17][2]*Vpk[15][17][2])+((fstarr[17][0]*Vpk[15][17][0])+
      (fstarr[17][1]*Vpk[15][17][1])))+((tstarr[17][2]*Wpk[15][17][2])+((
      tstarr[17][0]*Wpk[15][17][0])+(tstarr[17][1]*s16))))+(((fstarr[18][2]*
      Vpk[15][18][2])+((fstarr[18][0]*Vpk[15][18][0])+(fstarr[18][1]*
      Vpk[15][18][1])))+((tstarr[18][2]*Wpk[15][18][2])+((tstarr[18][0]*
      Wpk[15][18][0])+(tstarr[18][1]*s16)))));
    trqout[15] = -(utau[15]+((((fstarr[20][2]*Vpk[15][20][2])+((fstarr[20][0]*
      Vpk[15][20][0])+(fstarr[20][1]*Vpk[15][20][1])))+((tstarr[20][2]*
      Wpk[15][20][2])+((tstarr[20][0]*Wpk[15][19][0])+(tstarr[20][1]*
      Wpk[15][20][1]))))+temp[0]));
    temp[0] = ((((fstarr[17][2]*Vpk[16][17][2])+((fstarr[17][0]*Vpk[16][17][0])+
      (fstarr[17][1]*Vpk[16][17][1])))+((tstarr[17][0]*c17)+(tstarr[17][2]*s17))
      )+(((fstarr[18][2]*Vpk[16][18][2])+((fstarr[18][0]*Vpk[16][18][0])+(
      fstarr[18][1]*Vpk[16][18][1])))+((tstarr[18][0]*Wpk[16][18][0])+(
      tstarr[18][2]*Wpk[16][18][2]))));
    trqout[16] = -(utau[16]+((((fstarr[20][2]*Vpk[16][20][2])+((fstarr[20][0]*
      Vpk[16][20][0])+(fstarr[20][1]*Vpk[16][20][1])))+((tstarr[20][2]*
      Wpk[16][20][2])+((tstarr[20][0]*Wpk[16][19][0])+(tstarr[20][1]*
      Wpk[16][20][1]))))+temp[0]));
    trqout[17] = -(utau[17]+(((tstarr[17][1]+((fstarr[17][2]*rk[7][0])-(
      fstarr[17][0]*rk[7][2])))+(tstarr[18][1]+((fstarr[18][0]*Vpk[17][18][0])+(
      fstarr[18][2]*Vpk[17][18][2]))))+(((fstarr[20][2]*Vpk[17][20][2])+((
      fstarr[20][0]*Vpk[17][20][0])+(fstarr[20][1]*Vpk[17][20][1])))+((
      tstarr[20][1]*c20)-(tstarr[20][2]*s20)))));
    trqout[18] = -(utau[18]+((tstarr[18][1]+((fstarr[18][2]*rk[8][0])-(
      fstarr[18][0]*rk[8][2])))+(((fstarr[20][2]*Vpk[18][20][2])+((fstarr[20][0]
      *Vpk[18][20][0])+(fstarr[20][1]*Vpk[18][20][1])))+((tstarr[20][1]*c20)-(
      tstarr[20][2]*s20)))));
    trqout[19] = -(utau[19]+(((fstarr[20][2]*Vpk[19][20][2])+((fstarr[20][0]*
      Vpk[19][20][0])+(fstarr[20][1]*Vpk[19][20][1])))+((tstarr[20][1]*c20)-(
      tstarr[20][2]*s20))));
    trqout[20] = -(utau[20]+(tstarr[20][0]+((fstarr[20][1]*rk[9][2])-(
      fstarr[20][2]*rk[9][1]))));
/*
Op counts below do not include called subroutines
*/
/*
 Used 0.01 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  894 adds/subtracts/negates
                    855 multiplies
                      0 divides
                    226 assignments
*/
}

void sdcomptrq(double udotin[21],
    double trqout[21])
{
/* Compute hinge torques to produce these udots, ignoring constraints
*/
    double multin[1];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(60,23);
        return;
    }
    sdfulltrq(udotin,multin,trqout);
}

void sdmulttrq(double multin[1],
    double trqout[21])
{
/* Compute hinge trqs which would be produced by these mults.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(65,23);
        return;
    }
    for (i = 0; i < 21; i++) {
        trqout[i] = 0.;
    }
}

void sdrhs(void)
{
/*
Generated 01-Jan-1999 18:58:22 by SD/FAST, Kane's formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/

/*
Compute hinge torques for tree hinges
*/
    tauc[0] = utau[0];
    tauc[1] = utau[1];
    tauc[2] = utau[2];
    tauc[3] = utau[3];
    tauc[4] = utau[4];
    tauc[5] = utau[5];
    tauc[6] = utau[6];
    tauc[7] = utau[7];
    tauc[8] = utau[8];
    tauc[9] = utau[9];
    tauc[10] = utau[10];
    tauc[11] = utau[11];
    tauc[12] = utau[12];
    tauc[13] = utau[13];
    tauc[14] = utau[14];
    tauc[15] = utau[15];
    tauc[16] = utau[16];
    tauc[17] = utau[17];
    tauc[18] = utau[18];
    tauc[19] = utau[19];
    tauc[20] = utau[20];
    sddoiner();
/*
Compute onk & onb (angular accels in N)
*/
    Onkb[4][0] = -(udot[3]*s4);
    Onkb[4][2] = (udot[3]*c4);
    Onkb[5][0] = (Onkb[4][0]+udot[5]);
    Onkb[5][1] = ((Onkb[4][2]*s5)+(udot[4]*c5));
    Onkb[5][2] = ((Onkb[4][2]*c5)-(udot[4]*s5));
    Onkb[6][0] = ((Onkb[5][0]*c6)+(Onkb[5][1]*s6));
    Onkb[6][1] = ((Onkb[5][1]*c6)-(Onkb[5][0]*s6));
    Onkb[6][2] = (Onkb[5][2]+udot[6]);
    Onkb[7][0] = ((Onkb[6][0]*c7)-(Onkb[6][2]*s7));
    Onkb[7][1] = (Onkb[6][1]+udot[7]);
    Onkb[7][2] = ((Onkb[6][0]*s7)+(Onkb[6][2]*c7));
    Onkb[8][0] = ((Onkb[6][0]*c8)-(Onkb[6][2]*s8));
    Onkb[8][1] = (Onkb[6][1]+udot[8]);
    Onkb[8][2] = ((Onkb[6][0]*s8)+(Onkb[6][2]*c8));
    Onkb[9][0] = ((Onkb[5][0]*c9)+(Onkb[5][1]*s9));
    Onkb[9][1] = ((Onkb[5][1]*c9)-(Onkb[5][0]*s9));
    Onkb[9][2] = (Onkb[5][2]+udot[9]);
    Onkb[10][0] = (Onkb[9][0]+udot[10]);
    Onkb[10][1] = ((Onkb[9][1]*c10)+(Onkb[9][2]*s10));
    Onkb[10][2] = ((Onkb[9][2]*c10)-(Onkb[9][1]*s10));
    Onkb[11][0] = ((Onkb[10][0]*c11)-(Onkb[10][2]*s11));
    Onkb[11][1] = (Onkb[10][1]+udot[11]);
    Onkb[11][2] = ((Onkb[10][0]*s11)+(Onkb[10][2]*c11));
    Onkb[12][0] = ((Onkb[11][0]*c12)-(Onkb[11][2]*s12));
    Onkb[12][1] = (Onkb[11][1]+udot[12]);
    Onkb[12][2] = ((Onkb[11][0]*s12)+(Onkb[11][2]*c12));
    Onkb[13][0] = ((Onkb[12][0]*c13)-(Onkb[12][2]*s13));
    Onkb[13][1] = (Onkb[12][1]+udot[13]);
    Onkb[13][2] = ((Onkb[12][0]*s13)+(Onkb[12][2]*c13));
    Onkb[14][0] = (Onkb[13][0]+udot[14]);
    Onkb[14][1] = ((Onkb[13][1]*c14)+(Onkb[13][2]*s14));
    Onkb[14][2] = ((Onkb[13][2]*c14)-(Onkb[13][1]*s14));
    Onkb[15][0] = ((Onkb[5][0]*c15)+(Onkb[5][1]*s15));
    Onkb[15][1] = ((Onkb[5][1]*c15)-(Onkb[5][0]*s15));
    Onkb[15][2] = (Onkb[5][2]+udot[15]);
    Onkb[16][0] = (Onkb[15][0]+udot[16]);
    Onkb[16][1] = ((Onkb[15][1]*c16)+(Onkb[15][2]*s16));
    Onkb[16][2] = ((Onkb[15][2]*c16)-(Onkb[15][1]*s16));
    Onkb[17][0] = ((Onkb[16][0]*c17)-(Onkb[16][2]*s17));
    Onkb[17][1] = (Onkb[16][1]+udot[17]);
    Onkb[17][2] = ((Onkb[16][0]*s17)+(Onkb[16][2]*c17));
    Onkb[18][0] = ((Onkb[17][0]*c18)-(Onkb[17][2]*s18));
    Onkb[18][1] = (Onkb[17][1]+udot[18]);
    Onkb[18][2] = ((Onkb[17][0]*s18)+(Onkb[17][2]*c18));
    Onkb[19][0] = ((Onkb[18][0]*c19)-(Onkb[18][2]*s19));
    Onkb[19][1] = (Onkb[18][1]+udot[19]);
    Onkb[19][2] = ((Onkb[18][0]*s19)+(Onkb[18][2]*c19));
    Onkb[20][0] = (Onkb[19][0]+udot[20]);
    Onkb[20][1] = ((Onkb[19][1]*c20)+(Onkb[19][2]*s20));
    Onkb[20][2] = ((Onkb[19][2]*c20)-(Onkb[19][1]*s20));
    onk[5][0] = (Onkb[5][0]+Otk[4][0]);
    onk[5][1] = (Onkb[5][1]+Otk[5][1]);
    onk[5][2] = (Onkb[5][2]+Otk[5][2]);
    onk[6][0] = (Onkb[6][0]+Otk[6][0]);
    onk[6][1] = (Onkb[6][1]+Otk[6][1]);
    onk[6][2] = (Onkb[6][2]+Otk[5][2]);
    onk[7][0] = (Onkb[7][0]+Otk[7][0]);
    onk[7][1] = (Onkb[7][1]+Otk[6][1]);
    onk[7][2] = (Onkb[7][2]+Otk[7][2]);
    onk[8][0] = (Onkb[8][0]+Otk[8][0]);
    onk[8][1] = (Onkb[8][1]+Otk[6][1]);
    onk[8][2] = (Onkb[8][2]+Otk[8][2]);
    onk[11][0] = (Onkb[11][0]+Otk[11][0]);
    onk[11][1] = (Onkb[11][1]+Otk[10][1]);
    onk[11][2] = (Onkb[11][2]+Otk[11][2]);
    onk[12][0] = (Onkb[12][0]+Otk[12][0]);
    onk[12][1] = (Onkb[12][1]+Otk[10][1]);
    onk[12][2] = (Onkb[12][2]+Otk[12][2]);
    onk[14][0] = (Onkb[14][0]+Otk[13][0]);
    onk[14][1] = (Onkb[14][1]+Otk[14][1]);
    onk[14][2] = (Onkb[14][2]+Otk[14][2]);
    onk[17][0] = (Onkb[17][0]+Otk[17][0]);
    onk[17][1] = (Onkb[17][1]+Otk[16][1]);
    onk[17][2] = (Onkb[17][2]+Otk[17][2]);
    onk[18][0] = (Onkb[18][0]+Otk[18][0]);
    onk[18][1] = (Onkb[18][1]+Otk[16][1]);
    onk[18][2] = (Onkb[18][2]+Otk[18][2]);
    onk[20][0] = (Onkb[20][0]+Otk[19][0]);
    onk[20][1] = (Onkb[20][1]+Otk[20][1]);
    onk[20][2] = (Onkb[20][2]+Otk[20][2]);
    onb[0][0] = onk[5][0];
    onb[0][1] = onk[5][1];
    onb[0][2] = onk[5][2];
    onb[1][0] = onk[6][0];
    onb[1][1] = onk[6][1];
    onb[1][2] = onk[6][2];
    onb[2][0] = onk[7][0];
    onb[2][1] = onk[7][1];
    onb[2][2] = onk[7][2];
    onb[3][0] = onk[8][0];
    onb[3][1] = onk[8][1];
    onb[3][2] = onk[8][2];
    onb[4][0] = onk[11][0];
    onb[4][1] = onk[11][1];
    onb[4][2] = onk[11][2];
    onb[5][0] = onk[12][0];
    onb[5][1] = onk[12][1];
    onb[5][2] = onk[12][2];
    onb[6][0] = onk[14][0];
    onb[6][1] = onk[14][1];
    onb[6][2] = onk[14][2];
    onb[7][0] = onk[17][0];
    onb[7][1] = onk[17][1];
    onb[7][2] = onk[17][2];
    onb[8][0] = onk[18][0];
    onb[8][1] = onk[18][1];
    onb[8][2] = onk[18][2];
    onb[9][0] = onk[20][0];
    onb[9][1] = onk[20][1];
    onb[9][2] = onk[20][2];
/*
Compute acceleration dyadics
*/
    dyad[0][0][0] = w11w22[0];
    dyad[0][0][1] = (w0w1[0]-onk[5][2]);
    dyad[0][0][2] = (onk[5][1]+w0w2[0]);
    dyad[0][1][0] = (onk[5][2]+w0w1[0]);
    dyad[0][1][1] = w00w22[0];
    dyad[0][1][2] = (w1w2[0]-onk[5][0]);
    dyad[0][2][0] = (w0w2[0]-onk[5][1]);
    dyad[0][2][1] = (onk[5][0]+w1w2[0]);
    dyad[0][2][2] = w00w11[0];
    dyad[1][0][0] = w11w22[1];
    dyad[1][0][1] = (w0w1[1]-onk[6][2]);
    dyad[1][0][2] = (onk[6][1]+w0w2[1]);
    dyad[1][1][0] = (onk[6][2]+w0w1[1]);
    dyad[1][1][1] = w00w22[1];
    dyad[1][1][2] = (w1w2[1]-onk[6][0]);
    dyad[1][2][0] = (w0w2[1]-onk[6][1]);
    dyad[1][2][1] = (onk[6][0]+w1w2[1]);
    dyad[1][2][2] = w00w11[1];
    dyad[2][0][0] = w11w22[2];
    dyad[2][0][1] = (w0w1[2]-onk[7][2]);
    dyad[2][0][2] = (onk[7][1]+w0w2[2]);
    dyad[2][1][0] = (onk[7][2]+w0w1[2]);
    dyad[2][1][1] = w00w22[2];
    dyad[2][1][2] = (w1w2[2]-onk[7][0]);
    dyad[2][2][0] = (w0w2[2]-onk[7][1]);
    dyad[2][2][1] = (onk[7][0]+w1w2[2]);
    dyad[2][2][2] = w00w11[2];
    dyad[3][0][0] = w11w22[3];
    dyad[3][0][1] = (w0w1[3]-onk[8][2]);
    dyad[3][0][2] = (onk[8][1]+w0w2[3]);
    dyad[3][1][0] = (onk[8][2]+w0w1[3]);
    dyad[3][1][1] = w00w22[3];
    dyad[3][1][2] = (w1w2[3]-onk[8][0]);
    dyad[3][2][0] = (w0w2[3]-onk[8][1]);
    dyad[3][2][1] = (onk[8][0]+w1w2[3]);
    dyad[3][2][2] = w00w11[3];
    dyad[4][0][0] = w11w22[4];
    dyad[4][0][1] = (w0w1[4]-onk[11][2]);
    dyad[4][0][2] = (onk[11][1]+w0w2[4]);
    dyad[4][1][0] = (onk[11][2]+w0w1[4]);
    dyad[4][1][1] = w00w22[4];
    dyad[4][1][2] = (w1w2[4]-onk[11][0]);
    dyad[4][2][0] = (w0w2[4]-onk[11][1]);
    dyad[4][2][1] = (onk[11][0]+w1w2[4]);
    dyad[4][2][2] = w00w11[4];
    dyad[5][0][0] = w11w22[5];
    dyad[5][0][1] = (w0w1[5]-onk[12][2]);
    dyad[5][0][2] = (onk[12][1]+w0w2[5]);
    dyad[5][1][0] = (onk[12][2]+w0w1[5]);
    dyad[5][1][1] = w00w22[5];
    dyad[5][1][2] = (w1w2[5]-onk[12][0]);
    dyad[5][2][0] = (w0w2[5]-onk[12][1]);
    dyad[5][2][1] = (onk[12][0]+w1w2[5]);
    dyad[5][2][2] = w00w11[5];
    dyad[6][0][0] = w11w22[6];
    dyad[6][0][1] = (w0w1[6]-onk[14][2]);
    dyad[6][0][2] = (onk[14][1]+w0w2[6]);
    dyad[6][1][0] = (onk[14][2]+w0w1[6]);
    dyad[6][1][1] = w00w22[6];
    dyad[6][1][2] = (w1w2[6]-onk[14][0]);
    dyad[6][2][0] = (w0w2[6]-onk[14][1]);
    dyad[6][2][1] = (onk[14][0]+w1w2[6]);
    dyad[6][2][2] = w00w11[6];
    dyad[7][0][0] = w11w22[7];
    dyad[7][0][1] = (w0w1[7]-onk[17][2]);
    dyad[7][0][2] = (onk[17][1]+w0w2[7]);
    dyad[7][1][0] = (onk[17][2]+w0w1[7]);
    dyad[7][1][1] = w00w22[7];
    dyad[7][1][2] = (w1w2[7]-onk[17][0]);
    dyad[7][2][0] = (w0w2[7]-onk[17][1]);
    dyad[7][2][1] = (onk[17][0]+w1w2[7]);
    dyad[7][2][2] = w00w11[7];
    dyad[8][0][0] = w11w22[8];
    dyad[8][0][1] = (w0w1[8]-onk[18][2]);
    dyad[8][0][2] = (onk[18][1]+w0w2[8]);
    dyad[8][1][0] = (onk[18][2]+w0w1[8]);
    dyad[8][1][1] = w00w22[8];
    dyad[8][1][2] = (w1w2[8]-onk[18][0]);
    dyad[8][2][0] = (w0w2[8]-onk[18][1]);
    dyad[8][2][1] = (onk[18][0]+w1w2[8]);
    dyad[8][2][2] = w00w11[8];
    dyad[9][0][0] = w11w22[9];
    dyad[9][0][1] = (w0w1[9]-onk[20][2]);
    dyad[9][0][2] = (onk[20][1]+w0w2[9]);
    dyad[9][1][0] = (onk[20][2]+w0w1[9]);
    dyad[9][1][1] = w00w22[9];
    dyad[9][1][2] = (w1w2[9]-onk[20][0]);
    dyad[9][2][0] = (w0w2[9]-onk[20][1]);
    dyad[9][2][1] = (onk[20][0]+w1w2[9]);
    dyad[9][2][2] = w00w11[9];
/*
Compute ank & anb (mass center linear accels in N)
*/
    Ankb[3][0] = ((udot[1]*s3)+(udot[2]*c3));
    Ankb[3][1] = ((udot[1]*c3)-(udot[2]*s3));
    Ankb[4][0] = ((Ankb[3][0]*c4)-(udot[0]*s4));
    Ankb[4][2] = ((Ankb[3][0]*s4)+(udot[0]*c4));
    Ankb[5][0] = (Ankb[4][0]+((Onkb[5][2]*rk[0][1])-(Onkb[5][1]*rk[0][2])));
    Ankb[5][1] = (((Ankb[3][1]*c5)+(Ankb[4][2]*s5))+((Onkb[5][0]*rk[0][2])-(
      Onkb[5][2]*rk[0][0])));
    Ankb[5][2] = (((Ankb[4][2]*c5)-(Ankb[3][1]*s5))+((Onkb[5][1]*rk[0][0])-(
      Onkb[5][0]*rk[0][1])));
    AOnkri[6][0] = (Ankb[5][0]+((Onkb[5][1]*ri[1][2])-(Onkb[5][2]*ri[1][1])));
    AOnkri[6][1] = (Ankb[5][1]+((Onkb[5][2]*ri[1][0])-(Onkb[5][0]*ri[1][2])));
    AOnkri[6][2] = (Ankb[5][2]+((Onkb[5][0]*ri[1][1])-(Onkb[5][1]*ri[1][0])));
    Ankb[6][0] = (((AOnkri[6][0]*c6)+(AOnkri[6][1]*s6))+((Onkb[6][2]*rk[1][1])-(
      Onkb[6][1]*rk[1][2])));
    Ankb[6][1] = (((AOnkri[6][1]*c6)-(AOnkri[6][0]*s6))+((Onkb[6][0]*rk[1][2])-(
      Onkb[6][2]*rk[1][0])));
    Ankb[6][2] = (AOnkri[6][2]+((Onkb[6][1]*rk[1][0])-(Onkb[6][0]*rk[1][1])));
    AOnkri[7][0] = (Ankb[6][0]+((Onkb[6][1]*ri[2][2])-(Onkb[6][2]*ri[2][1])));
    AOnkri[7][1] = (Ankb[6][1]+((Onkb[6][2]*ri[2][0])-(Onkb[6][0]*ri[2][2])));
    AOnkri[7][2] = (Ankb[6][2]+((Onkb[6][0]*ri[2][1])-(Onkb[6][1]*ri[2][0])));
    Ankb[7][0] = (((AOnkri[7][0]*c7)-(AOnkri[7][2]*s7))+((Onkb[7][2]*rk[2][1])-(
      Onkb[7][1]*rk[2][2])));
    Ankb[7][1] = (AOnkri[7][1]+((Onkb[7][0]*rk[2][2])-(Onkb[7][2]*rk[2][0])));
    Ankb[7][2] = (((AOnkri[7][0]*s7)+(AOnkri[7][2]*c7))+((Onkb[7][1]*rk[2][0])-(
      Onkb[7][0]*rk[2][1])));
    AOnkri[8][0] = (Ankb[6][0]+((Onkb[6][1]*ri[3][2])-(Onkb[6][2]*ri[3][1])));
    AOnkri[8][1] = (Ankb[6][1]+((Onkb[6][2]*ri[3][0])-(Onkb[6][0]*ri[3][2])));
    AOnkri[8][2] = (Ankb[6][2]+((Onkb[6][0]*ri[3][1])-(Onkb[6][1]*ri[3][0])));
    Ankb[8][0] = (((AOnkri[8][0]*c8)-(AOnkri[8][2]*s8))+((Onkb[8][2]*rk[3][1])-(
      Onkb[8][1]*rk[3][2])));
    Ankb[8][1] = (AOnkri[8][1]+((Onkb[8][0]*rk[3][2])-(Onkb[8][2]*rk[3][0])));
    Ankb[8][2] = (((AOnkri[8][0]*s8)+(AOnkri[8][2]*c8))+((Onkb[8][1]*rk[3][0])-(
      Onkb[8][0]*rk[3][1])));
    AOnkri[9][0] = (Ankb[5][0]+((Onkb[5][1]*ri[4][2])-(Onkb[5][2]*ri[4][1])));
    AOnkri[9][1] = (Ankb[5][1]+((Onkb[5][2]*ri[4][0])-(Onkb[5][0]*ri[4][2])));
    AOnkri[9][2] = (Ankb[5][2]+((Onkb[5][0]*ri[4][1])-(Onkb[5][1]*ri[4][0])));
    Ankb[9][0] = ((AOnkri[9][0]*c9)+(AOnkri[9][1]*s9));
    Ankb[9][1] = ((AOnkri[9][1]*c9)-(AOnkri[9][0]*s9));
    Ankb[10][1] = ((Ankb[9][1]*c10)+(AOnkri[9][2]*s10));
    Ankb[10][2] = ((AOnkri[9][2]*c10)-(Ankb[9][1]*s10));
    Ankb[11][0] = (((Ankb[9][0]*c11)-(Ankb[10][2]*s11))+((Onkb[11][2]*rk[4][1])-
      (Onkb[11][1]*rk[4][2])));
    Ankb[11][1] = (Ankb[10][1]+((Onkb[11][0]*rk[4][2])-(Onkb[11][2]*rk[4][0])));
    Ankb[11][2] = (((Ankb[9][0]*s11)+(Ankb[10][2]*c11))+((Onkb[11][1]*rk[4][0])-
      (Onkb[11][0]*rk[4][1])));
    AOnkri[12][0] = (Ankb[11][0]+((Onkb[11][1]*ri[5][2])-(Onkb[11][2]*ri[5][1]))
      );
    AOnkri[12][1] = (Ankb[11][1]+((Onkb[11][2]*ri[5][0])-(Onkb[11][0]*ri[5][2]))
      );
    AOnkri[12][2] = (Ankb[11][2]+((Onkb[11][0]*ri[5][1])-(Onkb[11][1]*ri[5][0]))
      );
    Ankb[12][0] = (((AOnkri[12][0]*c12)-(AOnkri[12][2]*s12))+((Onkb[12][2]*
      rk[5][1])-(Onkb[12][1]*rk[5][2])));
    Ankb[12][1] = (AOnkri[12][1]+((Onkb[12][0]*rk[5][2])-(Onkb[12][2]*rk[5][0]))
      );
    Ankb[12][2] = (((AOnkri[12][0]*s12)+(AOnkri[12][2]*c12))+((Onkb[12][1]*
      rk[5][0])-(Onkb[12][0]*rk[5][1])));
    AOnkri[13][0] = (Ankb[12][0]+((Onkb[12][1]*ri[6][2])-(Onkb[12][2]*ri[6][1]))
      );
    AOnkri[13][1] = (Ankb[12][1]+((Onkb[12][2]*ri[6][0])-(Onkb[12][0]*ri[6][2]))
      );
    AOnkri[13][2] = (Ankb[12][2]+((Onkb[12][0]*ri[6][1])-(Onkb[12][1]*ri[6][0]))
      );
    Ankb[13][0] = ((AOnkri[13][0]*c13)-(AOnkri[13][2]*s13));
    Ankb[13][2] = ((AOnkri[13][0]*s13)+(AOnkri[13][2]*c13));
    Ankb[14][0] = (Ankb[13][0]+((Onkb[14][2]*rk[6][1])-(Onkb[14][1]*rk[6][2])));
    Ankb[14][1] = (((Ankb[13][2]*s14)+(AOnkri[13][1]*c14))+((Onkb[14][0]*
      rk[6][2])-(Onkb[14][2]*rk[6][0])));
    Ankb[14][2] = (((Ankb[13][2]*c14)-(AOnkri[13][1]*s14))+((Onkb[14][1]*
      rk[6][0])-(Onkb[14][0]*rk[6][1])));
    AOnkri[15][0] = (Ankb[5][0]+((Onkb[5][1]*ri[7][2])-(Onkb[5][2]*ri[7][1])));
    AOnkri[15][1] = (Ankb[5][1]+((Onkb[5][2]*ri[7][0])-(Onkb[5][0]*ri[7][2])));
    AOnkri[15][2] = (Ankb[5][2]+((Onkb[5][0]*ri[7][1])-(Onkb[5][1]*ri[7][0])));
    Ankb[15][0] = ((AOnkri[15][0]*c15)+(AOnkri[15][1]*s15));
    Ankb[15][1] = ((AOnkri[15][1]*c15)-(AOnkri[15][0]*s15));
    Ankb[16][1] = ((Ankb[15][1]*c16)+(AOnkri[15][2]*s16));
    Ankb[16][2] = ((AOnkri[15][2]*c16)-(Ankb[15][1]*s16));
    Ankb[17][0] = (((Ankb[15][0]*c17)-(Ankb[16][2]*s17))+((Onkb[17][2]*rk[7][1])
      -(Onkb[17][1]*rk[7][2])));
    Ankb[17][1] = (Ankb[16][1]+((Onkb[17][0]*rk[7][2])-(Onkb[17][2]*rk[7][0])));
    Ankb[17][2] = (((Ankb[15][0]*s17)+(Ankb[16][2]*c17))+((Onkb[17][1]*rk[7][0])
      -(Onkb[17][0]*rk[7][1])));
    AOnkri[18][0] = (Ankb[17][0]+((Onkb[17][1]*ri[8][2])-(Onkb[17][2]*ri[8][1]))
      );
    AOnkri[18][1] = (Ankb[17][1]+((Onkb[17][2]*ri[8][0])-(Onkb[17][0]*ri[8][2]))
      );
    AOnkri[18][2] = (Ankb[17][2]+((Onkb[17][0]*ri[8][1])-(Onkb[17][1]*ri[8][0]))
      );
    Ankb[18][0] = (((AOnkri[18][0]*c18)-(AOnkri[18][2]*s18))+((Onkb[18][2]*
      rk[8][1])-(Onkb[18][1]*rk[8][2])));
    Ankb[18][1] = (AOnkri[18][1]+((Onkb[18][0]*rk[8][2])-(Onkb[18][2]*rk[8][0]))
      );
    Ankb[18][2] = (((AOnkri[18][0]*s18)+(AOnkri[18][2]*c18))+((Onkb[18][1]*
      rk[8][0])-(Onkb[18][0]*rk[8][1])));
    AOnkri[19][0] = (Ankb[18][0]+((Onkb[18][1]*ri[9][2])-(Onkb[18][2]*ri[9][1]))
      );
    AOnkri[19][1] = (Ankb[18][1]+((Onkb[18][2]*ri[9][0])-(Onkb[18][0]*ri[9][2]))
      );
    AOnkri[19][2] = (Ankb[18][2]+((Onkb[18][0]*ri[9][1])-(Onkb[18][1]*ri[9][0]))
      );
    Ankb[19][0] = ((AOnkri[19][0]*c19)-(AOnkri[19][2]*s19));
    Ankb[19][2] = ((AOnkri[19][0]*s19)+(AOnkri[19][2]*c19));
    Ankb[20][0] = (Ankb[19][0]+((Onkb[20][2]*rk[9][1])-(Onkb[20][1]*rk[9][2])));
    Ankb[20][1] = (((Ankb[19][2]*s20)+(AOnkri[19][1]*c20))+((Onkb[20][0]*
      rk[9][2])-(Onkb[20][2]*rk[9][0])));
    Ankb[20][2] = (((Ankb[19][2]*c20)-(AOnkri[19][1]*s20))+((Onkb[20][1]*
      rk[9][0])-(Onkb[20][0]*rk[9][1])));
    AnkAtk[5][0] = (Ankb[5][0]+Atk[5][0]);
    AnkAtk[5][1] = (Ankb[5][1]+Atk[5][1]);
    AnkAtk[5][2] = (Ankb[5][2]+Atk[5][2]);
    ank[5][0] = ((AnkAtk[5][2]*cnk[5][0][2])+((AnkAtk[5][0]*cnk[4][0][0])+(
      AnkAtk[5][1]*cnk[5][0][1])));
    ank[5][1] = ((AnkAtk[5][2]*cnk[5][1][2])+((AnkAtk[5][0]*cnk[4][1][0])+(
      AnkAtk[5][1]*cnk[5][1][1])));
    ank[5][2] = ((AnkAtk[5][2]*cnk[5][2][2])+((AnkAtk[5][1]*cnk[5][2][1])-(
      AnkAtk[5][0]*s4)));
    AnkAtk[6][0] = (Ankb[6][0]+Atk[6][0]);
    AnkAtk[6][1] = (Ankb[6][1]+Atk[6][1]);
    AnkAtk[6][2] = (Ankb[6][2]+Atk[6][2]);
    ank[6][0] = ((AnkAtk[6][2]*cnk[5][0][2])+((AnkAtk[6][0]*cnk[6][0][0])+(
      AnkAtk[6][1]*cnk[6][0][1])));
    ank[6][1] = ((AnkAtk[6][2]*cnk[5][1][2])+((AnkAtk[6][0]*cnk[6][1][0])+(
      AnkAtk[6][1]*cnk[6][1][1])));
    ank[6][2] = ((AnkAtk[6][2]*cnk[5][2][2])+((AnkAtk[6][0]*cnk[6][2][0])+(
      AnkAtk[6][1]*cnk[6][2][1])));
    AnkAtk[7][0] = (Ankb[7][0]+Atk[7][0]);
    AnkAtk[7][1] = (Ankb[7][1]+Atk[7][1]);
    AnkAtk[7][2] = (Ankb[7][2]+Atk[7][2]);
    ank[7][0] = ((AnkAtk[7][2]*cnk[7][0][2])+((AnkAtk[7][0]*cnk[7][0][0])+(
      AnkAtk[7][1]*cnk[6][0][1])));
    ank[7][1] = ((AnkAtk[7][2]*cnk[7][1][2])+((AnkAtk[7][0]*cnk[7][1][0])+(
      AnkAtk[7][1]*cnk[6][1][1])));
    ank[7][2] = ((AnkAtk[7][2]*cnk[7][2][2])+((AnkAtk[7][0]*cnk[7][2][0])+(
      AnkAtk[7][1]*cnk[6][2][1])));
    AnkAtk[8][0] = (Ankb[8][0]+Atk[8][0]);
    AnkAtk[8][1] = (Ankb[8][1]+Atk[8][1]);
    AnkAtk[8][2] = (Ankb[8][2]+Atk[8][2]);
    ank[8][0] = ((AnkAtk[8][2]*cnk[8][0][2])+((AnkAtk[8][0]*cnk[8][0][0])+(
      AnkAtk[8][1]*cnk[6][0][1])));
    ank[8][1] = ((AnkAtk[8][2]*cnk[8][1][2])+((AnkAtk[8][0]*cnk[8][1][0])+(
      AnkAtk[8][1]*cnk[6][1][1])));
    ank[8][2] = ((AnkAtk[8][2]*cnk[8][2][2])+((AnkAtk[8][0]*cnk[8][2][0])+(
      AnkAtk[8][1]*cnk[6][2][1])));
    AnkAtk[11][0] = (Ankb[11][0]+Atk[11][0]);
    AnkAtk[11][1] = (Ankb[11][1]+Atk[11][1]);
    AnkAtk[11][2] = (Ankb[11][2]+Atk[11][2]);
    ank[11][0] = ((AnkAtk[11][2]*cnk[11][0][2])+((AnkAtk[11][0]*cnk[11][0][0])+(
      AnkAtk[11][1]*cnk[10][0][1])));
    ank[11][1] = ((AnkAtk[11][2]*cnk[11][1][2])+((AnkAtk[11][0]*cnk[11][1][0])+(
      AnkAtk[11][1]*cnk[10][1][1])));
    ank[11][2] = ((AnkAtk[11][2]*cnk[11][2][2])+((AnkAtk[11][0]*cnk[11][2][0])+(
      AnkAtk[11][1]*cnk[10][2][1])));
    AnkAtk[12][0] = (Ankb[12][0]+Atk[12][0]);
    AnkAtk[12][1] = (Ankb[12][1]+Atk[12][1]);
    AnkAtk[12][2] = (Ankb[12][2]+Atk[12][2]);
    ank[12][0] = ((AnkAtk[12][2]*cnk[12][0][2])+((AnkAtk[12][0]*cnk[12][0][0])+(
      AnkAtk[12][1]*cnk[10][0][1])));
    ank[12][1] = ((AnkAtk[12][2]*cnk[12][1][2])+((AnkAtk[12][0]*cnk[12][1][0])+(
      AnkAtk[12][1]*cnk[10][1][1])));
    ank[12][2] = ((AnkAtk[12][2]*cnk[12][2][2])+((AnkAtk[12][0]*cnk[12][2][0])+(
      AnkAtk[12][1]*cnk[10][2][1])));
    AnkAtk[14][0] = (Ankb[14][0]+Atk[14][0]);
    AnkAtk[14][1] = (Ankb[14][1]+Atk[14][1]);
    AnkAtk[14][2] = (Ankb[14][2]+Atk[14][2]);
    ank[14][0] = ((AnkAtk[14][2]*cnk[14][0][2])+((AnkAtk[14][0]*cnk[13][0][0])+(
      AnkAtk[14][1]*cnk[14][0][1])));
    ank[14][1] = ((AnkAtk[14][2]*cnk[14][1][2])+((AnkAtk[14][0]*cnk[13][1][0])+(
      AnkAtk[14][1]*cnk[14][1][1])));
    ank[14][2] = ((AnkAtk[14][2]*cnk[14][2][2])+((AnkAtk[14][0]*cnk[13][2][0])+(
      AnkAtk[14][1]*cnk[14][2][1])));
    AnkAtk[17][0] = (Ankb[17][0]+Atk[17][0]);
    AnkAtk[17][1] = (Ankb[17][1]+Atk[17][1]);
    AnkAtk[17][2] = (Ankb[17][2]+Atk[17][2]);
    ank[17][0] = ((AnkAtk[17][2]*cnk[17][0][2])+((AnkAtk[17][0]*cnk[17][0][0])+(
      AnkAtk[17][1]*cnk[16][0][1])));
    ank[17][1] = ((AnkAtk[17][2]*cnk[17][1][2])+((AnkAtk[17][0]*cnk[17][1][0])+(
      AnkAtk[17][1]*cnk[16][1][1])));
    ank[17][2] = ((AnkAtk[17][2]*cnk[17][2][2])+((AnkAtk[17][0]*cnk[17][2][0])+(
      AnkAtk[17][1]*cnk[16][2][1])));
    AnkAtk[18][0] = (Ankb[18][0]+Atk[18][0]);
    AnkAtk[18][1] = (Ankb[18][1]+Atk[18][1]);
    AnkAtk[18][2] = (Ankb[18][2]+Atk[18][2]);
    ank[18][0] = ((AnkAtk[18][2]*cnk[18][0][2])+((AnkAtk[18][0]*cnk[18][0][0])+(
      AnkAtk[18][1]*cnk[16][0][1])));
    ank[18][1] = ((AnkAtk[18][2]*cnk[18][1][2])+((AnkAtk[18][0]*cnk[18][1][0])+(
      AnkAtk[18][1]*cnk[16][1][1])));
    ank[18][2] = ((AnkAtk[18][2]*cnk[18][2][2])+((AnkAtk[18][0]*cnk[18][2][0])+(
      AnkAtk[18][1]*cnk[16][2][1])));
    AnkAtk[20][0] = (Ankb[20][0]+Atk[20][0]);
    AnkAtk[20][1] = (Ankb[20][1]+Atk[20][1]);
    AnkAtk[20][2] = (Ankb[20][2]+Atk[20][2]);
    ank[20][0] = ((AnkAtk[20][2]*cnk[20][0][2])+((AnkAtk[20][0]*cnk[19][0][0])+(
      AnkAtk[20][1]*cnk[20][0][1])));
    ank[20][1] = ((AnkAtk[20][2]*cnk[20][1][2])+((AnkAtk[20][0]*cnk[19][1][0])+(
      AnkAtk[20][1]*cnk[20][1][1])));
    ank[20][2] = ((AnkAtk[20][2]*cnk[20][2][2])+((AnkAtk[20][0]*cnk[19][2][0])+(
      AnkAtk[20][1]*cnk[20][2][1])));
    anb[0][0] = ank[5][0];
    anb[0][1] = ank[5][1];
    anb[0][2] = ank[5][2];
    anb[1][0] = ank[6][0];
    anb[1][1] = ank[6][1];
    anb[1][2] = ank[6][2];
    anb[2][0] = ank[7][0];
    anb[2][1] = ank[7][1];
    anb[2][2] = ank[7][2];
    anb[3][0] = ank[8][0];
    anb[3][1] = ank[8][1];
    anb[3][2] = ank[8][2];
    anb[4][0] = ank[11][0];
    anb[4][1] = ank[11][1];
    anb[4][2] = ank[11][2];
    anb[5][0] = ank[12][0];
    anb[5][1] = ank[12][1];
    anb[5][2] = ank[12][2];
    anb[6][0] = ank[14][0];
    anb[6][1] = ank[14][1];
    anb[6][2] = ank[14][2];
    anb[7][0] = ank[17][0];
    anb[7][1] = ank[17][1];
    anb[7][2] = ank[17][2];
    anb[8][0] = ank[18][0];
    anb[8][1] = ank[18][1];
    anb[8][2] = ank[18][2];
    anb[9][0] = ank[20][0];
    anb[9][1] = ank[20][1];
    anb[9][2] = ank[20][2];
    roustate = 3;
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  379 adds/subtracts/negates
                    342 multiplies
                      0 divides
                    384 assignments
*/
}

void sdmassmat(double mmat[21][21])
{
/* Return the system mass matrix (LHS)
*/
    int i,j;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(57,23);
        return;
    }
    sddomm(57);
    for (i = 0; i < 21; i++) {
        for (j = i; j <= 20; j++) {
            mmat[i][j] = mm[i][j];
            mmat[j][i] = mm[i][j];
        }
    }
}

void sdfrcmat(double fmat[21])
{
/* Return the system force matrix (RHS), excluding constraints
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(58,23);
        return;
    }
    sddofs0();
    for (i = 0; i < 21; i++) {
        fmat[i] = fs0[i];
    }
}

void sdpseudo(double lqout[1],
    double luout[1])
{
/*
Return pseudo-coordinates for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

void sdpsqdot(double lqdout[1])
{
/*
Return pseudo-coordinate derivatives for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

void sdpsudot(double ludout[1])
{
/*
Return pseudo-coordinate accelerations for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

void sdperr(double errs[1])
{

}

void sdverr(double errs[1])
{

}

void sdaerr(double errs[1])
{

}
int 
sdchkbnum(int routine,
    int bnum)
{

    if ((bnum < -1) || (bnum > 9)) {
        sdseterr(routine,15);
        return 1;
    }
    return 0;
}
int 
sdchkjnum(int routine,
    int jnum)
{

    if ((jnum < 0) || (jnum > 9)) {
        sdseterr(routine,16);
        return 1;
    }
    return 0;
}
int 
sdchkucnum(int routine,
    int ucnum)
{

    if ((ucnum < 0) || (ucnum > -1)) {
        sdseterr(routine,21);
        return 1;
    }
    return 0;
}
int 
sdchkjaxis(int routine,
    int jnum,
    int axnum)
{
    int maxax;

    if (sdchkjnum(routine,jnum) != 0) {
        return 1;
    }
    if ((axnum < 0) || (axnum > 6)) {
        sdseterr(routine,17);
        return 1;
    }
    maxax = njntdof[jnum]-1;
    if ((jtype[jnum] == 4) || (jtype[jnum] == 6) || (jtype[jnum] == 21)) {
        maxax = maxax+1;
    }
    if (axnum > maxax) {
        sdseterr(routine,18);
        return 1;
    }
    return 0;
}
int 
sdchkjpin(int routine,
    int jnum,
    int pinno)
{
    int maxax,pinok;

    if (sdchkjnum(routine,jnum) != 0) {
        return 1;
    }
    if ((pinno < 0) || (pinno > 5)) {
        sdseterr(routine,17);
        return 1;
    }
    if (njntdof[jnum] >= 3) {
        maxax = 2;
    } else {
        maxax = njntdof[jnum]-1;
    }
    if (jtype[jnum] == 4) {
        maxax = -1;
    }
    if (jtype[jnum] == 7) {
        maxax = 0;
    }
    pinok = 0;
    if (pinno <= maxax) {
        pinok = 1;
    }
    if (pinok == 0) {
        sdseterr(routine,18);
        return 1;
    }
    return 0;
}
int 
sdindx(int joint,
    int axis)
{
    int offs,gotit;

    if (sdchkjaxis(36,joint,axis) != 0) {
        return 0;
    }
    gotit = 0;
    if (jtype[joint] == 4) {
        if (axis == 3) {
            offs = ballq[joint];
            gotit = 1;
        }
    } else {
        if ((jtype[joint] == 6) || (jtype[joint] == 21)) {
            if (axis == 6) {
                offs = ballq[joint];
                gotit = 1;
            }
        }
    }
    if (gotit == 0) {
        offs = firstq[joint]+axis;
    }
    return offs;
}

void sdpresacc(int joint,
    int axis,
    double prval)
{

}

void sdpresvel(int joint,
    int axis,
    double prval)
{

}

void sdprespos(int joint,
    int axis,
    double prval)
{

}

void sdgetht(int joint,
    int axis,
    double *torque)
{

    if (sdchkjaxis(30,joint,axis) != 0) {
        return;
    }
    if (roustate != 3) {
        sdseterr(30,24);
        return;
    }
    *torque = tauc[sdindx(joint,axis)];
}

void sdhinget(int joint,
    int axis,
    double torque)
{

    if (sdchkjaxis(10,joint,axis) != 0) {
        return;
    }
    if (roustate != 2) {
        sdseterr(10,23);
        return;
    }
    if (mfrcflg != 0) {
        mtau[sdindx(joint,axis)] = mtau[sdindx(joint,axis)]+torque;
    } else {
        fs0flg = 0;
        utau[sdindx(joint,axis)] = utau[sdindx(joint,axis)]+torque;
    }
}

void sdpointf(int body,
    double point[3],
    double force[3])
{
    double torque[3];

    if (sdchkbnum(11,body) != 0) {
        return;
    }
    if (roustate != 2) {
        sdseterr(11,23);
        return;
    }
    if (body == -1) {
        return;
    }
    torque[0] = point[1]*force[2]-point[2]*force[1];
    torque[1] = point[2]*force[0]-point[0]*force[2];
    torque[2] = point[0]*force[1]-point[1]*force[0];
    if (mfrcflg != 0) {
        mfk[body][0] = mfk[body][0]+force[0];
        mtk[body][0] = mtk[body][0]+torque[0];
        mfk[body][1] = mfk[body][1]+force[1];
        mtk[body][1] = mtk[body][1]+torque[1];
        mfk[body][2] = mfk[body][2]+force[2];
        mtk[body][2] = mtk[body][2]+torque[2];
    } else {
        fs0flg = 0;
        ufk[body][0] = ufk[body][0]+force[0];
        utk[body][0] = utk[body][0]+torque[0];
        ufk[body][1] = ufk[body][1]+force[1];
        utk[body][1] = utk[body][1]+torque[1];
        ufk[body][2] = ufk[body][2]+force[2];
        utk[body][2] = utk[body][2]+torque[2];
    }
}

void sdbodyt(int body,
    double torque[3])
{

    if (sdchkbnum(12,body) != 0) {
        return;
    }
    if (roustate != 2) {
        sdseterr(12,23);
        return;
    }
    if (body == -1) {
        return;
    }
    if (mfrcflg != 0) {
        mtk[body][0] = mtk[body][0]+torque[0];
        mtk[body][1] = mtk[body][1]+torque[1];
        mtk[body][2] = mtk[body][2]+torque[2];
    } else {
        fs0flg = 0;
        utk[body][0] = utk[body][0]+torque[0];
        utk[body][1] = utk[body][1]+torque[1];
        utk[body][2] = utk[body][2]+torque[2];
    }
}

void sddoww(int routine)
{

    roustate = 2;
    if (wwflg == 0) {
        wwflg = 1;
    }
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      0 assignments
*/
}

void sdxudot0(int routine,
    double oudot0[21])
{
/*
Compute unconstrained equations
*/
    int i;

    sdlhs(routine);
/*
Solve equations for udots
*/
    sdfs0();
    sdldubslv(21,21,mmap,works, (double*)mlo,mdi,fs,udot);
    for (i = 0; i <= 20; i++) {
        oudot0[i] = udot[i];
    }
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     21 assignments
*/
}

void sdudot0(double oudot0[21])
{

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(66,23);
        return;
    }
    sdxudot0(66,oudot0);
}

void sdsetudot(double iudot[21])
{
/*
Assign udots and advance to stage Dynamics Ready
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(68,23);
        return;
    }
    for (i = 0; i <= 20; i++) {
        udot[i] = iudot[i];
    }
    sdrhs();
}

void sdxudotm(int routine,
    double imult[1],
    double oudotm[21])
{
/*
Compute udots due only to multipliers
*/
    int i;

    sdlhs(routine);
    for (i = 0; i <= 20; i++) {
        udot[i] = 0.;
    }
    for (i = 0; i <= 20; i++) {
        oudotm[i] = udot[i];
    }
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     42 assignments
*/
}

void sdudotm(double imult[1],
    double oudotm[21])
{

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(67,23);
        return;
    }
    sdxudotm(67,imult,oudotm);
}

void sdderiv(double oqdot[21],
    double oudot[21])
{
/*
This is the derivative section for a 10-body ground-based
system with 21 hinge degree(s) of freedom.
*/
    int i;
    double udot0[21],udot1[21];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(17,23);
        return;
    }
    if (stabvelq == 1) {
        sdseterr(17,32);
    }
    if (stabposq == 1) {
        sdseterr(17,33);
    }
    wsiz = 0;
/*
Compute unconstrained equations
*/
    sdxudot0(17,udot0);
    sdrhs();
    wrank = 0;
    for (i = 0; i <= 20; i++) {
        oqdot[i] = qdot[i];
    }
    for (i = 0; i <= 20; i++) {
        oudot[i] = udot[i];
    }
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     42 assignments
*/
}
/*
Compute residuals for use with DAE integrator
*/

void sdresid(double eqdot[21],
    double eudot[21],
    double emults[1],
    double resid[42])
{
    int i;
    double uderrs[21];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(16,23);
        return;
    }
    if (stabposq == 1) {
        sdseterr(16,33);
    }
    sdfulltrq(eudot,emults,uderrs);
    for (i = 0; i < 21; i++) {
        resid[i] = eqdot[i]-qdot[i];
    }
    for (i = 0; i < 21; i++) {
        resid[21+i] = uderrs[i];
    }
    for (i = 0; i < 21; i++) {
        udot[i] = eudot[i];
    }
    sdrhs();
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   21 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     63 assignments
*/
}

void sdmult(double omults[1],
    int *owrank,
    int omultmap[1])
{

    if (roustate != 3) {
        sdseterr(34,24);
        return;
    }
    *owrank = wrank;
}

void sdreac(double force[10][3],
    double torque[10][3])
{
/*
Generated 01-Jan-1999 18:58:22 by SD/FAST, Kane's formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/

    if (roustate != 3) {
        sdseterr(31,24);
        return;
    }
/*
Compute reaction forces for non-weld tree joints
*/
    fc[20][0] = ((mk[9]*(AnkAtk[20][0]-gk[19][0]))-ufk[9][0]);
    fc[20][1] = ((mk[9]*(AnkAtk[20][1]-gk[20][1]))-ufk[9][1]);
    fc[20][2] = ((mk[9]*(AnkAtk[20][2]-gk[20][2]))-ufk[9][2]);
    tc[20][0] = ((WkIkWk[20][0]+(ik[9][0][0]*onk[20][0]))-(utk[9][0]+((fc[20][2]
      *rk[9][1])-(fc[20][1]*rk[9][2]))));
    tc[20][1] = ((WkIkWk[20][1]+(ik[9][1][1]*onk[20][1]))-(utk[9][1]+((fc[20][0]
      *rk[9][2])-(fc[20][2]*rk[9][0]))));
    tc[20][2] = ((WkIkWk[20][2]+(ik[9][2][2]*onk[20][2]))-(utk[9][2]+((fc[20][1]
      *rk[9][0])-(fc[20][0]*rk[9][1]))));
    fccikt[20][0] = fc[20][0];
    fccikt[20][1] = ((fc[20][1]*c20)-(fc[20][2]*s20));
    fccikt[20][2] = ((fc[20][1]*s20)+(fc[20][2]*c20));
    ffk[19][0] = -fccikt[20][0];
    ffk[19][1] = -fccikt[20][1];
    ffk[19][2] = -fccikt[20][2];
    ttk[19][0] = -tc[20][0];
    ttk[19][1] = -((tc[20][1]*c20)-(tc[20][2]*s20));
    ttk[19][2] = -((tc[20][1]*s20)+(tc[20][2]*c20));
    fc[19][0] = -ffk[19][0];
    fc[19][1] = -ffk[19][1];
    fc[19][2] = -ffk[19][2];
    tc[19][0] = -ttk[19][0];
    tc[19][1] = -ttk[19][1];
    tc[19][2] = -ttk[19][2];
    fccikt[19][0] = ((fc[19][0]*c19)+(fc[19][2]*s19));
    fccikt[19][1] = fc[19][1];
    fccikt[19][2] = ((fc[19][2]*c19)-(fc[19][0]*s19));
    ffk[18][0] = (ufk[8][0]-fccikt[19][0]);
    ffk[18][1] = (ufk[8][1]-fccikt[19][1]);
    ffk[18][2] = (ufk[8][2]-fccikt[19][2]);
    ttk[18][0] = (utk[8][0]-(((fccikt[19][2]*ri[9][1])-(fccikt[19][1]*ri[9][2]))
      +((tc[19][0]*c19)+(tc[19][2]*s19))));
    ttk[18][1] = (utk[8][1]-(tc[19][1]+((fccikt[19][0]*ri[9][2])-(fccikt[19][2]*
      ri[9][0]))));
    ttk[18][2] = (utk[8][2]-(((fccikt[19][1]*ri[9][0])-(fccikt[19][0]*ri[9][1]))
      +((tc[19][2]*c19)-(tc[19][0]*s19))));
    fc[18][0] = ((mk[8]*(AnkAtk[18][0]-gk[18][0]))-ffk[18][0]);
    fc[18][1] = ((mk[8]*(AnkAtk[18][1]-gk[16][1]))-ffk[18][1]);
    fc[18][2] = ((mk[8]*(AnkAtk[18][2]-gk[18][2]))-ffk[18][2]);
    tc[18][0] = ((WkIkWk[18][0]+(ik[8][0][0]*onk[18][0]))-(ttk[18][0]+((
      fc[18][2]*rk[8][1])-(fc[18][1]*rk[8][2]))));
    tc[18][1] = ((WkIkWk[18][1]+(ik[8][1][1]*onk[18][1]))-(ttk[18][1]+((
      fc[18][0]*rk[8][2])-(fc[18][2]*rk[8][0]))));
    tc[18][2] = ((WkIkWk[18][2]+(ik[8][2][2]*onk[18][2]))-(ttk[18][2]+((
      fc[18][1]*rk[8][0])-(fc[18][0]*rk[8][1]))));
    fccikt[18][0] = ((fc[18][0]*c18)+(fc[18][2]*s18));
    fccikt[18][1] = fc[18][1];
    fccikt[18][2] = ((fc[18][2]*c18)-(fc[18][0]*s18));
    ffk[17][0] = (ufk[7][0]-fccikt[18][0]);
    ffk[17][1] = (ufk[7][1]-fccikt[18][1]);
    ffk[17][2] = (ufk[7][2]-fccikt[18][2]);
    ttk[17][0] = (utk[7][0]-(((fccikt[18][2]*ri[8][1])-(fccikt[18][1]*ri[8][2]))
      +((tc[18][0]*c18)+(tc[18][2]*s18))));
    ttk[17][1] = (utk[7][1]-(tc[18][1]+((fccikt[18][0]*ri[8][2])-(fccikt[18][2]*
      ri[8][0]))));
    ttk[17][2] = (utk[7][2]-(((fccikt[18][1]*ri[8][0])-(fccikt[18][0]*ri[8][1]))
      +((tc[18][2]*c18)-(tc[18][0]*s18))));
    fc[17][0] = ((mk[7]*(AnkAtk[17][0]-gk[17][0]))-ffk[17][0]);
    fc[17][1] = ((mk[7]*(AnkAtk[17][1]-gk[16][1]))-ffk[17][1]);
    fc[17][2] = ((mk[7]*(AnkAtk[17][2]-gk[17][2]))-ffk[17][2]);
    tc[17][0] = ((WkIkWk[17][0]+(ik[7][0][0]*onk[17][0]))-(ttk[17][0]+((
      fc[17][2]*rk[7][1])-(fc[17][1]*rk[7][2]))));
    tc[17][1] = ((WkIkWk[17][1]+(ik[7][1][1]*onk[17][1]))-(ttk[17][1]+((
      fc[17][0]*rk[7][2])-(fc[17][2]*rk[7][0]))));
    tc[17][2] = ((WkIkWk[17][2]+(ik[7][2][2]*onk[17][2]))-(ttk[17][2]+((
      fc[17][1]*rk[7][0])-(fc[17][0]*rk[7][1]))));
    fccikt[17][0] = ((fc[17][0]*c17)+(fc[17][2]*s17));
    fccikt[17][1] = fc[17][1];
    fccikt[17][2] = ((fc[17][2]*c17)-(fc[17][0]*s17));
    ffk[16][0] = -fccikt[17][0];
    ffk[16][1] = -fccikt[17][1];
    ffk[16][2] = -fccikt[17][2];
    ttk[16][0] = -((tc[17][0]*c17)+(tc[17][2]*s17));
    ttk[16][1] = -tc[17][1];
    ttk[16][2] = -((tc[17][2]*c17)-(tc[17][0]*s17));
    fc[16][0] = -ffk[16][0];
    fc[16][1] = -ffk[16][1];
    fc[16][2] = -ffk[16][2];
    tc[16][0] = -ttk[16][0];
    tc[16][1] = -ttk[16][1];
    tc[16][2] = -ttk[16][2];
    fccikt[16][0] = fc[16][0];
    fccikt[16][1] = ((fc[16][1]*c16)-(fc[16][2]*s16));
    fccikt[16][2] = ((fc[16][1]*s16)+(fc[16][2]*c16));
    ffk[15][0] = -fccikt[16][0];
    ffk[15][1] = -fccikt[16][1];
    ffk[15][2] = -fccikt[16][2];
    ttk[15][0] = -tc[16][0];
    ttk[15][1] = -((tc[16][1]*c16)-(tc[16][2]*s16));
    ttk[15][2] = -((tc[16][1]*s16)+(tc[16][2]*c16));
    fc[15][0] = -ffk[15][0];
    fc[15][1] = -ffk[15][1];
    fc[15][2] = -ffk[15][2];
    tc[15][0] = -ttk[15][0];
    tc[15][1] = -ttk[15][1];
    tc[15][2] = -ttk[15][2];
    fccikt[15][0] = ((fc[15][0]*c15)-(fc[15][1]*s15));
    fccikt[15][1] = ((fc[15][0]*s15)+(fc[15][1]*c15));
    fccikt[15][2] = fc[15][2];
    ffk[5][0] = (ufk[0][0]-fccikt[15][0]);
    ffk[5][1] = (ufk[0][1]-fccikt[15][1]);
    ffk[5][2] = (ufk[0][2]-fccikt[15][2]);
    ttk[5][0] = (utk[0][0]-(((fccikt[15][2]*ri[7][1])-(fccikt[15][1]*ri[7][2]))+
      ((tc[15][0]*c15)-(tc[15][1]*s15))));
    ttk[5][1] = (utk[0][1]-(((fccikt[15][0]*ri[7][2])-(fccikt[15][2]*ri[7][0]))+
      ((tc[15][0]*s15)+(tc[15][1]*c15))));
    ttk[5][2] = (utk[0][2]-(tc[15][2]+((fccikt[15][1]*ri[7][0])-(fccikt[15][0]*
      ri[7][1]))));
    fc[14][0] = ((mk[6]*(AnkAtk[14][0]-gk[13][0]))-ufk[6][0]);
    fc[14][1] = ((mk[6]*(AnkAtk[14][1]-gk[14][1]))-ufk[6][1]);
    fc[14][2] = ((mk[6]*(AnkAtk[14][2]-gk[14][2]))-ufk[6][2]);
    tc[14][0] = ((WkIkWk[14][0]+(ik[6][0][0]*onk[14][0]))-(utk[6][0]+((fc[14][2]
      *rk[6][1])-(fc[14][1]*rk[6][2]))));
    tc[14][1] = ((WkIkWk[14][1]+(ik[6][1][1]*onk[14][1]))-(utk[6][1]+((fc[14][0]
      *rk[6][2])-(fc[14][2]*rk[6][0]))));
    tc[14][2] = ((WkIkWk[14][2]+(ik[6][2][2]*onk[14][2]))-(utk[6][2]+((fc[14][1]
      *rk[6][0])-(fc[14][0]*rk[6][1]))));
    fccikt[14][0] = fc[14][0];
    fccikt[14][1] = ((fc[14][1]*c14)-(fc[14][2]*s14));
    fccikt[14][2] = ((fc[14][1]*s14)+(fc[14][2]*c14));
    ffk[13][0] = -fccikt[14][0];
    ffk[13][1] = -fccikt[14][1];
    ffk[13][2] = -fccikt[14][2];
    ttk[13][0] = -tc[14][0];
    ttk[13][1] = -((tc[14][1]*c14)-(tc[14][2]*s14));
    ttk[13][2] = -((tc[14][1]*s14)+(tc[14][2]*c14));
    fc[13][0] = -ffk[13][0];
    fc[13][1] = -ffk[13][1];
    fc[13][2] = -ffk[13][2];
    tc[13][0] = -ttk[13][0];
    tc[13][1] = -ttk[13][1];
    tc[13][2] = -ttk[13][2];
    fccikt[13][0] = ((fc[13][0]*c13)+(fc[13][2]*s13));
    fccikt[13][1] = fc[13][1];
    fccikt[13][2] = ((fc[13][2]*c13)-(fc[13][0]*s13));
    ffk[12][0] = (ufk[5][0]-fccikt[13][0]);
    ffk[12][1] = (ufk[5][1]-fccikt[13][1]);
    ffk[12][2] = (ufk[5][2]-fccikt[13][2]);
    ttk[12][0] = (utk[5][0]-(((fccikt[13][2]*ri[6][1])-(fccikt[13][1]*ri[6][2]))
      +((tc[13][0]*c13)+(tc[13][2]*s13))));
    ttk[12][1] = (utk[5][1]-(tc[13][1]+((fccikt[13][0]*ri[6][2])-(fccikt[13][2]*
      ri[6][0]))));
    ttk[12][2] = (utk[5][2]-(((fccikt[13][1]*ri[6][0])-(fccikt[13][0]*ri[6][1]))
      +((tc[13][2]*c13)-(tc[13][0]*s13))));
    fc[12][0] = ((mk[5]*(AnkAtk[12][0]-gk[12][0]))-ffk[12][0]);
    fc[12][1] = ((mk[5]*(AnkAtk[12][1]-gk[10][1]))-ffk[12][1]);
    fc[12][2] = ((mk[5]*(AnkAtk[12][2]-gk[12][2]))-ffk[12][2]);
    tc[12][0] = ((WkIkWk[12][0]+(ik[5][0][0]*onk[12][0]))-(ttk[12][0]+((
      fc[12][2]*rk[5][1])-(fc[12][1]*rk[5][2]))));
    tc[12][1] = ((WkIkWk[12][1]+(ik[5][1][1]*onk[12][1]))-(ttk[12][1]+((
      fc[12][0]*rk[5][2])-(fc[12][2]*rk[5][0]))));
    tc[12][2] = ((WkIkWk[12][2]+(ik[5][2][2]*onk[12][2]))-(ttk[12][2]+((
      fc[12][1]*rk[5][0])-(fc[12][0]*rk[5][1]))));
    fccikt[12][0] = ((fc[12][0]*c12)+(fc[12][2]*s12));
    fccikt[12][1] = fc[12][1];
    fccikt[12][2] = ((fc[12][2]*c12)-(fc[12][0]*s12));
    ffk[11][0] = (ufk[4][0]-fccikt[12][0]);
    ffk[11][1] = (ufk[4][1]-fccikt[12][1]);
    ffk[11][2] = (ufk[4][2]-fccikt[12][2]);
    ttk[11][0] = (utk[4][0]-(((fccikt[12][2]*ri[5][1])-(fccikt[12][1]*ri[5][2]))
      +((tc[12][0]*c12)+(tc[12][2]*s12))));
    ttk[11][1] = (utk[4][1]-(tc[12][1]+((fccikt[12][0]*ri[5][2])-(fccikt[12][2]*
      ri[5][0]))));
    ttk[11][2] = (utk[4][2]-(((fccikt[12][1]*ri[5][0])-(fccikt[12][0]*ri[5][1]))
      +((tc[12][2]*c12)-(tc[12][0]*s12))));
    fc[11][0] = ((mk[4]*(AnkAtk[11][0]-gk[11][0]))-ffk[11][0]);
    fc[11][1] = ((mk[4]*(AnkAtk[11][1]-gk[10][1]))-ffk[11][1]);
    fc[11][2] = ((mk[4]*(AnkAtk[11][2]-gk[11][2]))-ffk[11][2]);
    tc[11][0] = ((WkIkWk[11][0]+(ik[4][0][0]*onk[11][0]))-(ttk[11][0]+((
      fc[11][2]*rk[4][1])-(fc[11][1]*rk[4][2]))));
    tc[11][1] = ((WkIkWk[11][1]+(ik[4][1][1]*onk[11][1]))-(ttk[11][1]+((
      fc[11][0]*rk[4][2])-(fc[11][2]*rk[4][0]))));
    tc[11][2] = ((WkIkWk[11][2]+(ik[4][2][2]*onk[11][2]))-(ttk[11][2]+((
      fc[11][1]*rk[4][0])-(fc[11][0]*rk[4][1]))));
    fccikt[11][0] = ((fc[11][0]*c11)+(fc[11][2]*s11));
    fccikt[11][1] = fc[11][1];
    fccikt[11][2] = ((fc[11][2]*c11)-(fc[11][0]*s11));
    ffk[10][0] = -fccikt[11][0];
    ffk[10][1] = -fccikt[11][1];
    ffk[10][2] = -fccikt[11][2];
    ttk[10][0] = -((tc[11][0]*c11)+(tc[11][2]*s11));
    ttk[10][1] = -tc[11][1];
    ttk[10][2] = -((tc[11][2]*c11)-(tc[11][0]*s11));
    fc[10][0] = -ffk[10][0];
    fc[10][1] = -ffk[10][1];
    fc[10][2] = -ffk[10][2];
    tc[10][0] = -ttk[10][0];
    tc[10][1] = -ttk[10][1];
    tc[10][2] = -ttk[10][2];
    fccikt[10][0] = fc[10][0];
    fccikt[10][1] = ((fc[10][1]*c10)-(fc[10][2]*s10));
    fccikt[10][2] = ((fc[10][1]*s10)+(fc[10][2]*c10));
    ffk[9][0] = -fccikt[10][0];
    ffk[9][1] = -fccikt[10][1];
    ffk[9][2] = -fccikt[10][2];
    ttk[9][0] = -tc[10][0];
    ttk[9][1] = -((tc[10][1]*c10)-(tc[10][2]*s10));
    ttk[9][2] = -((tc[10][1]*s10)+(tc[10][2]*c10));
    fc[9][0] = -ffk[9][0];
    fc[9][1] = -ffk[9][1];
    fc[9][2] = -ffk[9][2];
    tc[9][0] = -ttk[9][0];
    tc[9][1] = -ttk[9][1];
    tc[9][2] = -ttk[9][2];
    fccikt[9][0] = ((fc[9][0]*c9)-(fc[9][1]*s9));
    fccikt[9][1] = ((fc[9][0]*s9)+(fc[9][1]*c9));
    fccikt[9][2] = fc[9][2];
    ffk[5][0] = (ffk[5][0]-fccikt[9][0]);
    ffk[5][1] = (ffk[5][1]-fccikt[9][1]);
    ffk[5][2] = (ffk[5][2]-fccikt[9][2]);
    ttk[5][0] = (ttk[5][0]-(((fccikt[9][2]*ri[4][1])-(fccikt[9][1]*ri[4][2]))+((
      tc[9][0]*c9)-(tc[9][1]*s9))));
    ttk[5][1] = (ttk[5][1]-(((fccikt[9][0]*ri[4][2])-(fccikt[9][2]*ri[4][0]))+((
      tc[9][0]*s9)+(tc[9][1]*c9))));
    ttk[5][2] = (ttk[5][2]-(tc[9][2]+((fccikt[9][1]*ri[4][0])-(fccikt[9][0]*
      ri[4][1]))));
    fc[8][0] = ((mk[3]*(AnkAtk[8][0]-gk[8][0]))-ufk[3][0]);
    fc[8][1] = ((mk[3]*(AnkAtk[8][1]-gk[6][1]))-ufk[3][1]);
    fc[8][2] = ((mk[3]*(AnkAtk[8][2]-gk[8][2]))-ufk[3][2]);
    tc[8][0] = ((WkIkWk[8][0]+(ik[3][0][0]*onk[8][0]))-(utk[3][0]+((fc[8][2]*
      rk[3][1])-(fc[8][1]*rk[3][2]))));
    tc[8][1] = ((WkIkWk[8][1]+(ik[3][1][1]*onk[8][1]))-(utk[3][1]+((fc[8][0]*
      rk[3][2])-(fc[8][2]*rk[3][0]))));
    tc[8][2] = ((WkIkWk[8][2]+(ik[3][2][2]*onk[8][2]))-(utk[3][2]+((fc[8][1]*
      rk[3][0])-(fc[8][0]*rk[3][1]))));
    fccikt[8][0] = ((fc[8][0]*c8)+(fc[8][2]*s8));
    fccikt[8][1] = fc[8][1];
    fccikt[8][2] = ((fc[8][2]*c8)-(fc[8][0]*s8));
    ffk[6][0] = (ufk[1][0]-fccikt[8][0]);
    ffk[6][1] = (ufk[1][1]-fccikt[8][1]);
    ffk[6][2] = (ufk[1][2]-fccikt[8][2]);
    ttk[6][0] = (utk[1][0]-(((fccikt[8][2]*ri[3][1])-(fccikt[8][1]*ri[3][2]))+((
      tc[8][0]*c8)+(tc[8][2]*s8))));
    ttk[6][1] = (utk[1][1]-(tc[8][1]+((fccikt[8][0]*ri[3][2])-(fccikt[8][2]*
      ri[3][0]))));
    ttk[6][2] = (utk[1][2]-(((fccikt[8][1]*ri[3][0])-(fccikt[8][0]*ri[3][1]))+((
      tc[8][2]*c8)-(tc[8][0]*s8))));
    fc[7][0] = ((mk[2]*(AnkAtk[7][0]-gk[7][0]))-ufk[2][0]);
    fc[7][1] = ((mk[2]*(AnkAtk[7][1]-gk[6][1]))-ufk[2][1]);
    fc[7][2] = ((mk[2]*(AnkAtk[7][2]-gk[7][2]))-ufk[2][2]);
    tc[7][0] = ((WkIkWk[7][0]+(ik[2][0][0]*onk[7][0]))-(utk[2][0]+((fc[7][2]*
      rk[2][1])-(fc[7][1]*rk[2][2]))));
    tc[7][1] = ((WkIkWk[7][1]+(ik[2][1][1]*onk[7][1]))-(utk[2][1]+((fc[7][0]*
      rk[2][2])-(fc[7][2]*rk[2][0]))));
    tc[7][2] = ((WkIkWk[7][2]+(ik[2][2][2]*onk[7][2]))-(utk[2][2]+((fc[7][1]*
      rk[2][0])-(fc[7][0]*rk[2][1]))));
    fccikt[7][0] = ((fc[7][0]*c7)+(fc[7][2]*s7));
    fccikt[7][1] = fc[7][1];
    fccikt[7][2] = ((fc[7][2]*c7)-(fc[7][0]*s7));
    ffk[6][0] = (ffk[6][0]-fccikt[7][0]);
    ffk[6][1] = (ffk[6][1]-fccikt[7][1]);
    ffk[6][2] = (ffk[6][2]-fccikt[7][2]);
    ttk[6][0] = (ttk[6][0]-(((fccikt[7][2]*ri[2][1])-(fccikt[7][1]*ri[2][2]))+((
      tc[7][0]*c7)+(tc[7][2]*s7))));
    ttk[6][1] = (ttk[6][1]-(tc[7][1]+((fccikt[7][0]*ri[2][2])-(fccikt[7][2]*
      ri[2][0]))));
    ttk[6][2] = (ttk[6][2]-(((fccikt[7][1]*ri[2][0])-(fccikt[7][0]*ri[2][1]))+((
      tc[7][2]*c7)-(tc[7][0]*s7))));
    fc[6][0] = ((mk[1]*(AnkAtk[6][0]-gk[6][0]))-ffk[6][0]);
    fc[6][1] = ((mk[1]*(AnkAtk[6][1]-gk[6][1]))-ffk[6][1]);
    fc[6][2] = ((mk[1]*(AnkAtk[6][2]-gk[5][2]))-ffk[6][2]);
    tc[6][0] = ((WkIkWk[6][0]+(ik[1][0][0]*onk[6][0]))-(ttk[6][0]+((fc[6][2]*
      rk[1][1])-(fc[6][1]*rk[1][2]))));
    tc[6][1] = ((WkIkWk[6][1]+(ik[1][1][1]*onk[6][1]))-(ttk[6][1]+((fc[6][0]*
      rk[1][2])-(fc[6][2]*rk[1][0]))));
    tc[6][2] = ((WkIkWk[6][2]+(ik[1][2][2]*onk[6][2]))-(ttk[6][2]+((fc[6][1]*
      rk[1][0])-(fc[6][0]*rk[1][1]))));
    fccikt[6][0] = ((fc[6][0]*c6)-(fc[6][1]*s6));
    fccikt[6][1] = ((fc[6][0]*s6)+(fc[6][1]*c6));
    fccikt[6][2] = fc[6][2];
    ffk[5][0] = (ffk[5][0]-fccikt[6][0]);
    ffk[5][1] = (ffk[5][1]-fccikt[6][1]);
    ffk[5][2] = (ffk[5][2]-fccikt[6][2]);
    ttk[5][0] = (ttk[5][0]-(((fccikt[6][2]*ri[1][1])-(fccikt[6][1]*ri[1][2]))+((
      tc[6][0]*c6)-(tc[6][1]*s6))));
    ttk[5][1] = (ttk[5][1]-(((fccikt[6][0]*ri[1][2])-(fccikt[6][2]*ri[1][0]))+((
      tc[6][0]*s6)+(tc[6][1]*c6))));
    ttk[5][2] = (ttk[5][2]-(tc[6][2]+((fccikt[6][1]*ri[1][0])-(fccikt[6][0]*
      ri[1][1]))));
    fc[5][0] = ((mk[0]*(AnkAtk[5][0]-(9.8*s4)))-ffk[5][0]);
    fc[5][1] = ((mk[0]*(AnkAtk[5][1]-gk[5][1]))-ffk[5][1]);
    fc[5][2] = ((mk[0]*(AnkAtk[5][2]-gk[5][2]))-ffk[5][2]);
    tc[5][0] = ((WkIkWk[5][0]+(ik[0][0][0]*onk[5][0]))-(ttk[5][0]+((fc[5][2]*
      rk[0][1])-(fc[5][1]*rk[0][2]))));
    tc[5][1] = ((WkIkWk[5][1]+(ik[0][1][1]*onk[5][1]))-(ttk[5][1]+((fc[5][0]*
      rk[0][2])-(fc[5][2]*rk[0][0]))));
    tc[5][2] = ((WkIkWk[5][2]+(ik[0][2][2]*onk[5][2]))-(ttk[5][2]+((fc[5][1]*
      rk[0][0])-(fc[5][0]*rk[0][1]))));
    fccikt[5][0] = fc[5][0];
    fccikt[5][1] = ((fc[5][1]*c5)-(fc[5][2]*s5));
    fccikt[5][2] = ((fc[5][1]*s5)+(fc[5][2]*c5));
    ffk[4][0] = -fccikt[5][0];
    ffk[4][1] = -fccikt[5][1];
    ffk[4][2] = -fccikt[5][2];
    ttk[4][0] = -tc[5][0];
    ttk[4][1] = -((tc[5][1]*c5)-(tc[5][2]*s5));
    ttk[4][2] = -((tc[5][1]*s5)+(tc[5][2]*c5));
    fc[4][0] = -ffk[4][0];
    fc[4][1] = -ffk[4][1];
    fc[4][2] = -ffk[4][2];
    tc[4][0] = -ttk[4][0];
    tc[4][1] = -ttk[4][1];
    tc[4][2] = -ttk[4][2];
    fccikt[4][0] = ((fc[4][0]*c4)+(fc[4][2]*s4));
    fccikt[4][1] = fc[4][1];
    fccikt[4][2] = ((fc[4][2]*c4)-(fc[4][0]*s4));
    ffk[3][0] = -fccikt[4][0];
    ffk[3][1] = -fccikt[4][1];
    ffk[3][2] = -fccikt[4][2];
    ttk[3][0] = -((tc[4][0]*c4)+(tc[4][2]*s4));
    ttk[3][1] = -tc[4][1];
    ttk[3][2] = -((tc[4][2]*c4)-(tc[4][0]*s4));
    fc[3][0] = -ffk[3][0];
    fc[3][1] = -ffk[3][1];
    fc[3][2] = -ffk[3][2];
    tc[3][0] = -ttk[3][0];
    tc[3][1] = -ttk[3][1];
    tc[3][2] = -ttk[3][2];
    fccikt[3][0] = ((fc[3][0]*c3)-(fc[3][1]*s3));
    fccikt[3][1] = ((fc[3][0]*s3)+(fc[3][1]*c3));
    fccikt[3][2] = fc[3][2];
    ffk[2][0] = -fccikt[3][0];
    ffk[2][1] = -fccikt[3][1];
    ffk[2][2] = -fccikt[3][2];
    ttk[2][0] = -((tc[3][0]*c3)-(tc[3][1]*s3));
    ttk[2][1] = -((tc[3][0]*s3)+(tc[3][1]*c3));
    ttk[2][2] = -tc[3][2];
    fc[2][0] = -ffk[2][0];
    fc[2][1] = -ffk[2][1];
    fc[2][2] = -ffk[2][2];
    tc[2][0] = -ttk[2][0];
    tc[2][1] = -ttk[2][1];
    tc[2][2] = -ttk[2][2];
    fccikt[2][0] = fc[2][0];
    fccikt[2][1] = fc[2][1];
    fccikt[2][2] = fc[2][2];
    ffk[1][0] = -fccikt[2][0];
    ffk[1][1] = -fccikt[2][1];
    ffk[1][2] = -fccikt[2][2];
    ttk[1][0] = -tc[2][0];
    ttk[1][1] = -(tc[2][1]-(fccikt[2][2]*q[2]));
    ttk[1][2] = -(tc[2][2]+(fccikt[2][1]*q[2]));
    fc[1][0] = -ffk[1][0];
    fc[1][1] = -ffk[1][1];
    fc[1][2] = -ffk[1][2];
    tc[1][0] = -ttk[1][0];
    tc[1][1] = -ttk[1][1];
    tc[1][2] = -ttk[1][2];
    fccikt[1][0] = fc[1][0];
    fccikt[1][1] = fc[1][1];
    fccikt[1][2] = fc[1][2];
    ffk[0][0] = -fccikt[1][0];
    ffk[0][1] = -fccikt[1][1];
    ffk[0][2] = -fccikt[1][2];
    ttk[0][0] = -(tc[1][0]+(fccikt[1][2]*q[1]));
    ttk[0][1] = -tc[1][1];
    ttk[0][2] = -(tc[1][2]-(fccikt[1][0]*q[1]));
    fc[0][0] = -ffk[0][0];
    fc[0][1] = -ffk[0][1];
    fc[0][2] = -ffk[0][2];
    tc[0][0] = -ttk[0][0];
    tc[0][1] = -ttk[0][1];
    tc[0][2] = -ttk[0][2];
    force[0][0] = fc[5][0];
    torque[0][0] = tc[5][0];
    force[0][1] = fc[5][1];
    torque[0][1] = tc[5][1];
    force[0][2] = fc[5][2];
    torque[0][2] = tc[5][2];
    force[1][0] = fc[6][0];
    torque[1][0] = tc[6][0];
    force[1][1] = fc[6][1];
    torque[1][1] = tc[6][1];
    force[1][2] = fc[6][2];
    torque[1][2] = tc[6][2];
    force[2][0] = fc[7][0];
    torque[2][0] = tc[7][0];
    force[2][1] = fc[7][1];
    torque[2][1] = tc[7][1];
    force[2][2] = fc[7][2];
    torque[2][2] = tc[7][2];
    force[3][0] = fc[8][0];
    torque[3][0] = tc[8][0];
    force[3][1] = fc[8][1];
    torque[3][1] = tc[8][1];
    force[3][2] = fc[8][2];
    torque[3][2] = tc[8][2];
    force[4][0] = fc[11][0];
    torque[4][0] = tc[11][0];
    force[4][1] = fc[11][1];
    torque[4][1] = tc[11][1];
    force[4][2] = fc[11][2];
    torque[4][2] = tc[11][2];
    force[5][0] = fc[12][0];
    torque[5][0] = tc[12][0];
    force[5][1] = fc[12][1];
    torque[5][1] = tc[12][1];
    force[5][2] = fc[12][2];
    torque[5][2] = tc[12][2];
    force[6][0] = fc[14][0];
    torque[6][0] = tc[14][0];
    force[6][1] = fc[14][1];
    torque[6][1] = tc[14][1];
    force[6][2] = fc[14][2];
    torque[6][2] = tc[14][2];
    force[7][0] = fc[17][0];
    torque[7][0] = tc[17][0];
    force[7][1] = fc[17][1];
    torque[7][1] = tc[17][1];
    force[7][2] = fc[17][2];
    torque[7][2] = tc[17][2];
    force[8][0] = fc[18][0];
    torque[8][0] = tc[18][0];
    force[8][1] = fc[18][1];
    torque[8][1] = tc[18][1];
    force[8][2] = fc[18][2];
    torque[8][2] = tc[18][2];
    force[9][0] = fc[20][0];
    torque[9][0] = tc[20][0];
    force[9][1] = fc[20][1];
    torque[9][1] = tc[20][1];
    force[9][2] = fc[20][2];
    torque[9][2] = tc[20][2];
/*
Compute reaction forces for tree weld joints
*/
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  496 adds/subtracts/negates
                    323 multiplies
                      0 divides
                    366 assignments
*/
}

void sdmom(double lm[3],
    double am[3],
    double *ke)
{
/*
Compute system linear and angular momentum, and kinetic energy.

Generated 01-Jan-1999 18:58:22 by SD/FAST, Kane's formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
    double lk[10][3],hnk[10][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(19,23);
        return;
    }
    lk[0][0] = (mk[0]*vnk[5][0]);
    lk[0][1] = (mk[0]*vnk[5][1]);
    lk[0][2] = (mk[0]*vnk[5][2]);
    lk[1][0] = (mk[1]*vnk[6][0]);
    lk[1][1] = (mk[1]*vnk[6][1]);
    lk[1][2] = (mk[1]*vnk[6][2]);
    lk[2][0] = (mk[2]*vnk[7][0]);
    lk[2][1] = (mk[2]*vnk[7][1]);
    lk[2][2] = (mk[2]*vnk[7][2]);
    lk[3][0] = (mk[3]*vnk[8][0]);
    lk[3][1] = (mk[3]*vnk[8][1]);
    lk[3][2] = (mk[3]*vnk[8][2]);
    lk[4][0] = (mk[4]*vnk[11][0]);
    lk[4][1] = (mk[4]*vnk[11][1]);
    lk[4][2] = (mk[4]*vnk[11][2]);
    lk[5][0] = (mk[5]*vnk[12][0]);
    lk[5][1] = (mk[5]*vnk[12][1]);
    lk[5][2] = (mk[5]*vnk[12][2]);
    lk[6][0] = (mk[6]*vnk[14][0]);
    lk[6][1] = (mk[6]*vnk[14][1]);
    lk[6][2] = (mk[6]*vnk[14][2]);
    lk[7][0] = (mk[7]*vnk[17][0]);
    lk[7][1] = (mk[7]*vnk[17][1]);
    lk[7][2] = (mk[7]*vnk[17][2]);
    lk[8][0] = (mk[8]*vnk[18][0]);
    lk[8][1] = (mk[8]*vnk[18][1]);
    lk[8][2] = (mk[8]*vnk[18][2]);
    lk[9][0] = (mk[9]*vnk[20][0]);
    lk[9][1] = (mk[9]*vnk[20][1]);
    lk[9][2] = (mk[9]*vnk[20][2]);
    hnk[0][0] = (ik[0][0][0]*wk[5][0]);
    hnk[0][1] = (ik[0][1][1]*wk[5][1]);
    hnk[0][2] = (ik[0][2][2]*wk[5][2]);
    hnk[1][0] = (ik[1][0][0]*wk[6][0]);
    hnk[1][1] = (ik[1][1][1]*wk[6][1]);
    hnk[1][2] = (ik[1][2][2]*wk[6][2]);
    hnk[2][0] = (ik[2][0][0]*wk[7][0]);
    hnk[2][1] = (ik[2][1][1]*wk[7][1]);
    hnk[2][2] = (ik[2][2][2]*wk[7][2]);
    hnk[3][0] = (ik[3][0][0]*wk[8][0]);
    hnk[3][1] = (ik[3][1][1]*wk[8][1]);
    hnk[3][2] = (ik[3][2][2]*wk[8][2]);
    hnk[4][0] = (ik[4][0][0]*wk[11][0]);
    hnk[4][1] = (ik[4][1][1]*wk[11][1]);
    hnk[4][2] = (ik[4][2][2]*wk[11][2]);
    hnk[5][0] = (ik[5][0][0]*wk[12][0]);
    hnk[5][1] = (ik[5][1][1]*wk[12][1]);
    hnk[5][2] = (ik[5][2][2]*wk[12][2]);
    hnk[6][0] = (ik[6][0][0]*wk[14][0]);
    hnk[6][1] = (ik[6][1][1]*wk[14][1]);
    hnk[6][2] = (ik[6][2][2]*wk[14][2]);
    hnk[7][0] = (ik[7][0][0]*wk[17][0]);
    hnk[7][1] = (ik[7][1][1]*wk[17][1]);
    hnk[7][2] = (ik[7][2][2]*wk[17][2]);
    hnk[8][0] = (ik[8][0][0]*wk[18][0]);
    hnk[8][1] = (ik[8][1][1]*wk[18][1]);
    hnk[8][2] = (ik[8][2][2]*wk[18][2]);
    hnk[9][0] = (ik[9][0][0]*wk[20][0]);
    hnk[9][1] = (ik[9][1][1]*wk[20][1]);
    hnk[9][2] = (ik[9][2][2]*wk[20][2]);
    lm[0] = (lk[9][0]+(lk[8][0]+(lk[7][0]+(lk[6][0]+(lk[5][0]+(lk[4][0]+(
      lk[3][0]+(lk[2][0]+(lk[0][0]+lk[1][0])))))))));
    lm[1] = (lk[9][1]+(lk[8][1]+(lk[7][1]+(lk[6][1]+(lk[5][1]+(lk[4][1]+(
      lk[3][1]+(lk[2][1]+(lk[0][1]+lk[1][1])))))))));
    lm[2] = (lk[9][2]+(lk[8][2]+(lk[7][2]+(lk[6][2]+(lk[5][2]+(lk[4][2]+(
      lk[3][2]+(lk[2][2]+(lk[0][2]+lk[1][2])))))))));
    temp[0] = ((((cnk[7][0][2]*hnk[2][2])+((cnk[6][0][1]*hnk[2][1])+(
      cnk[7][0][0]*hnk[2][0])))+((lk[2][2]*rnk[7][1])-(lk[2][1]*rnk[7][2])))+(((
      (cnk[5][0][2]*hnk[0][2])+((cnk[4][0][0]*hnk[0][0])+(cnk[5][0][1]*hnk[0][1]
      )))+((lk[0][2]*rnk[5][1])-(lk[0][1]*rnk[5][2])))+(((cnk[5][0][2]*hnk[1][2]
      )+((cnk[6][0][0]*hnk[1][0])+(cnk[6][0][1]*hnk[1][1])))+((lk[1][2]*
      rnk[6][1])-(lk[1][1]*rnk[6][2])))));
    temp[1] = ((((cnk[11][0][2]*hnk[4][2])+((cnk[10][0][1]*hnk[4][1])+(
      cnk[11][0][0]*hnk[4][0])))+((lk[4][2]*rnk[11][1])-(lk[4][1]*rnk[11][2])))+
      ((((cnk[8][0][2]*hnk[3][2])+((cnk[6][0][1]*hnk[3][1])+(cnk[8][0][0]*
      hnk[3][0])))+((lk[3][2]*rnk[8][1])-(lk[3][1]*rnk[8][2])))+temp[0]));
    temp[2] = ((((cnk[14][0][2]*hnk[6][2])+((cnk[13][0][0]*hnk[6][0])+(
      cnk[14][0][1]*hnk[6][1])))+((lk[6][2]*rnk[14][1])-(lk[6][1]*rnk[14][2])))+
      ((((cnk[12][0][2]*hnk[5][2])+((cnk[10][0][1]*hnk[5][1])+(cnk[12][0][0]*
      hnk[5][0])))+((lk[5][2]*rnk[12][1])-(lk[5][1]*rnk[12][2])))+temp[1]));
    temp[3] = ((((cnk[18][0][2]*hnk[8][2])+((cnk[16][0][1]*hnk[8][1])+(
      cnk[18][0][0]*hnk[8][0])))+((lk[8][2]*rnk[18][1])-(lk[8][1]*rnk[18][2])))+
      ((((cnk[17][0][2]*hnk[7][2])+((cnk[16][0][1]*hnk[7][1])+(cnk[17][0][0]*
      hnk[7][0])))+((lk[7][2]*rnk[17][1])-(lk[7][1]*rnk[17][2])))+temp[2]));
    am[0] = (((((cnk[20][0][2]*hnk[9][2])+((cnk[19][0][0]*hnk[9][0])+(
      cnk[20][0][1]*hnk[9][1])))+((lk[9][2]*rnk[20][1])-(lk[9][1]*rnk[20][2])))+
      temp[3])-((com[1]*lm[2])-(com[2]*lm[1])));
    temp[0] = ((((cnk[7][1][2]*hnk[2][2])+((cnk[6][1][1]*hnk[2][1])+(
      cnk[7][1][0]*hnk[2][0])))+((lk[2][0]*rnk[7][2])-(lk[2][2]*rnk[7][0])))+(((
      (cnk[5][1][2]*hnk[0][2])+((cnk[4][1][0]*hnk[0][0])+(cnk[5][1][1]*hnk[0][1]
      )))+((lk[0][0]*rnk[5][2])-(lk[0][2]*rnk[5][0])))+(((cnk[5][1][2]*hnk[1][2]
      )+((cnk[6][1][0]*hnk[1][0])+(cnk[6][1][1]*hnk[1][1])))+((lk[1][0]*
      rnk[6][2])-(lk[1][2]*rnk[6][0])))));
    temp[1] = ((((cnk[11][1][2]*hnk[4][2])+((cnk[10][1][1]*hnk[4][1])+(
      cnk[11][1][0]*hnk[4][0])))+((lk[4][0]*rnk[11][2])-(lk[4][2]*rnk[11][0])))+
      ((((cnk[8][1][2]*hnk[3][2])+((cnk[6][1][1]*hnk[3][1])+(cnk[8][1][0]*
      hnk[3][0])))+((lk[3][0]*rnk[8][2])-(lk[3][2]*rnk[8][0])))+temp[0]));
    temp[2] = ((((cnk[14][1][2]*hnk[6][2])+((cnk[13][1][0]*hnk[6][0])+(
      cnk[14][1][1]*hnk[6][1])))+((lk[6][0]*rnk[14][2])-(lk[6][2]*rnk[14][0])))+
      ((((cnk[12][1][2]*hnk[5][2])+((cnk[10][1][1]*hnk[5][1])+(cnk[12][1][0]*
      hnk[5][0])))+((lk[5][0]*rnk[12][2])-(lk[5][2]*rnk[12][0])))+temp[1]));
    temp[3] = ((((cnk[18][1][2]*hnk[8][2])+((cnk[16][1][1]*hnk[8][1])+(
      cnk[18][1][0]*hnk[8][0])))+((lk[8][0]*rnk[18][2])-(lk[8][2]*rnk[18][0])))+
      ((((cnk[17][1][2]*hnk[7][2])+((cnk[16][1][1]*hnk[7][1])+(cnk[17][1][0]*
      hnk[7][0])))+((lk[7][0]*rnk[17][2])-(lk[7][2]*rnk[17][0])))+temp[2]));
    am[1] = (((((cnk[20][1][2]*hnk[9][2])+((cnk[19][1][0]*hnk[9][0])+(
      cnk[20][1][1]*hnk[9][1])))+((lk[9][0]*rnk[20][2])-(lk[9][2]*rnk[20][0])))+
      temp[3])-((com[2]*lm[0])-(com[0]*lm[2])));
    temp[0] = ((((cnk[7][2][2]*hnk[2][2])+((cnk[6][2][1]*hnk[2][1])+(
      cnk[7][2][0]*hnk[2][0])))+((lk[2][1]*rnk[7][0])-(lk[2][0]*rnk[7][1])))+(((
      (cnk[5][2][2]*hnk[0][2])+((cnk[5][2][1]*hnk[0][1])-(hnk[0][0]*s4)))+((
      lk[0][1]*rnk[5][0])-(lk[0][0]*rnk[5][1])))+(((cnk[5][2][2]*hnk[1][2])+((
      cnk[6][2][0]*hnk[1][0])+(cnk[6][2][1]*hnk[1][1])))+((lk[1][1]*rnk[6][0])-(
      lk[1][0]*rnk[6][1])))));
    temp[1] = ((((cnk[11][2][2]*hnk[4][2])+((cnk[10][2][1]*hnk[4][1])+(
      cnk[11][2][0]*hnk[4][0])))+((lk[4][1]*rnk[11][0])-(lk[4][0]*rnk[11][1])))+
      ((((cnk[8][2][2]*hnk[3][2])+((cnk[6][2][1]*hnk[3][1])+(cnk[8][2][0]*
      hnk[3][0])))+((lk[3][1]*rnk[8][0])-(lk[3][0]*rnk[8][1])))+temp[0]));
    temp[2] = ((((cnk[14][2][2]*hnk[6][2])+((cnk[13][2][0]*hnk[6][0])+(
      cnk[14][2][1]*hnk[6][1])))+((lk[6][1]*rnk[14][0])-(lk[6][0]*rnk[14][1])))+
      ((((cnk[12][2][2]*hnk[5][2])+((cnk[10][2][1]*hnk[5][1])+(cnk[12][2][0]*
      hnk[5][0])))+((lk[5][1]*rnk[12][0])-(lk[5][0]*rnk[12][1])))+temp[1]));
    temp[3] = ((((cnk[18][2][2]*hnk[8][2])+((cnk[16][2][1]*hnk[8][1])+(
      cnk[18][2][0]*hnk[8][0])))+((lk[8][1]*rnk[18][0])-(lk[8][0]*rnk[18][1])))+
      ((((cnk[17][2][2]*hnk[7][2])+((cnk[16][2][1]*hnk[7][1])+(cnk[17][2][0]*
      hnk[7][0])))+((lk[7][1]*rnk[17][0])-(lk[7][0]*rnk[17][1])))+temp[2]));
    am[2] = (((((cnk[20][2][2]*hnk[9][2])+((cnk[19][2][0]*hnk[9][0])+(
      cnk[20][2][1]*hnk[9][1])))+((lk[9][1]*rnk[20][0])-(lk[9][0]*rnk[20][1])))+
      temp[3])-((com[0]*lm[1])-(com[1]*lm[0])));
    temp[0] = ((((hnk[0][2]*wk[5][2])+((hnk[0][0]*wk[5][0])+(hnk[0][1]*wk[5][1])
      ))+((lk[0][2]*vnk[5][2])+((lk[0][0]*vnk[5][0])+(lk[0][1]*vnk[5][1]))))+(((
      hnk[1][2]*wk[6][2])+((hnk[1][0]*wk[6][0])+(hnk[1][1]*wk[6][1])))+((
      lk[1][2]*vnk[6][2])+((lk[1][0]*vnk[6][0])+(lk[1][1]*vnk[6][1])))));
    temp[1] = ((((hnk[3][2]*wk[8][2])+((hnk[3][0]*wk[8][0])+(hnk[3][1]*wk[8][1])
      ))+((lk[3][2]*vnk[8][2])+((lk[3][0]*vnk[8][0])+(lk[3][1]*vnk[8][1]))))+(((
      (hnk[2][2]*wk[7][2])+((hnk[2][0]*wk[7][0])+(hnk[2][1]*wk[7][1])))+((
      lk[2][2]*vnk[7][2])+((lk[2][0]*vnk[7][0])+(lk[2][1]*vnk[7][1]))))+temp[0])
      );
    temp[2] = ((((hnk[5][2]*wk[12][2])+((hnk[5][0]*wk[12][0])+(hnk[5][1]*
      wk[12][1])))+((lk[5][2]*vnk[12][2])+((lk[5][0]*vnk[12][0])+(lk[5][1]*
      vnk[12][1]))))+((((hnk[4][2]*wk[11][2])+((hnk[4][0]*wk[11][0])+(hnk[4][1]*
      wk[11][1])))+((lk[4][2]*vnk[11][2])+((lk[4][0]*vnk[11][0])+(lk[4][1]*
      vnk[11][1]))))+temp[1]));
    temp[3] = ((((hnk[7][2]*wk[17][2])+((hnk[7][0]*wk[17][0])+(hnk[7][1]*
      wk[17][1])))+((lk[7][2]*vnk[17][2])+((lk[7][0]*vnk[17][0])+(lk[7][1]*
      vnk[17][1]))))+((((hnk[6][2]*wk[14][2])+((hnk[6][0]*wk[14][0])+(hnk[6][1]*
      wk[14][1])))+((lk[6][2]*vnk[14][2])+((lk[6][0]*vnk[14][0])+(lk[6][1]*
      vnk[14][1]))))+temp[2]));
    *ke = (.5*((((hnk[9][2]*wk[20][2])+((hnk[9][0]*wk[20][0])+(hnk[9][1]*
      wk[20][1])))+((lk[9][2]*vnk[20][2])+((lk[9][0]*vnk[20][0])+(lk[9][1]*
      vnk[20][1]))))+((((hnk[8][2]*wk[18][2])+((hnk[8][0]*wk[18][0])+(hnk[8][1]*
      wk[18][1])))+((lk[8][2]*vnk[18][2])+((lk[8][0]*vnk[18][0])+(lk[8][1]*
      vnk[18][1]))))+temp[3])));
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  239 adds/subtracts/negates
                    277 multiplies
                      0 divides
                     83 assignments
*/
}

void sdsys(double *mtoto,
    double cm[3],
    double icm[3][3])
{
/*
Compute system total mass, and instantaneous center of mass and
inertia matrix.

Generated 01-Jan-1999 18:58:22 by SD/FAST, Kane's formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
    double ikcnkt[21][3][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(20,23);
        return;
    }
    *mtoto = mtot;
    cm[0] = com[0];
    cm[1] = com[1];
    cm[2] = com[2];
    ikcnkt[5][0][0] = (cnk[4][0][0]*ik[0][0][0]);
    ikcnkt[5][0][1] = (cnk[4][1][0]*ik[0][0][0]);
    ikcnkt[5][0][2] = -(ik[0][0][0]*s4);
    ikcnkt[5][1][0] = (cnk[5][0][1]*ik[0][1][1]);
    ikcnkt[5][1][1] = (cnk[5][1][1]*ik[0][1][1]);
    ikcnkt[5][1][2] = (cnk[5][2][1]*ik[0][1][1]);
    ikcnkt[5][2][0] = (cnk[5][0][2]*ik[0][2][2]);
    ikcnkt[5][2][1] = (cnk[5][1][2]*ik[0][2][2]);
    ikcnkt[5][2][2] = (cnk[5][2][2]*ik[0][2][2]);
    ikcnkt[6][0][0] = (cnk[6][0][0]*ik[1][0][0]);
    ikcnkt[6][0][1] = (cnk[6][1][0]*ik[1][0][0]);
    ikcnkt[6][0][2] = (cnk[6][2][0]*ik[1][0][0]);
    ikcnkt[6][1][0] = (cnk[6][0][1]*ik[1][1][1]);
    ikcnkt[6][1][1] = (cnk[6][1][1]*ik[1][1][1]);
    ikcnkt[6][1][2] = (cnk[6][2][1]*ik[1][1][1]);
    ikcnkt[6][2][0] = (cnk[5][0][2]*ik[1][2][2]);
    ikcnkt[6][2][1] = (cnk[5][1][2]*ik[1][2][2]);
    ikcnkt[6][2][2] = (cnk[5][2][2]*ik[1][2][2]);
    ikcnkt[7][0][0] = (cnk[7][0][0]*ik[2][0][0]);
    ikcnkt[7][0][1] = (cnk[7][1][0]*ik[2][0][0]);
    ikcnkt[7][0][2] = (cnk[7][2][0]*ik[2][0][0]);
    ikcnkt[7][1][0] = (cnk[6][0][1]*ik[2][1][1]);
    ikcnkt[7][1][1] = (cnk[6][1][1]*ik[2][1][1]);
    ikcnkt[7][1][2] = (cnk[6][2][1]*ik[2][1][1]);
    ikcnkt[7][2][0] = (cnk[7][0][2]*ik[2][2][2]);
    ikcnkt[7][2][1] = (cnk[7][1][2]*ik[2][2][2]);
    ikcnkt[7][2][2] = (cnk[7][2][2]*ik[2][2][2]);
    ikcnkt[8][0][0] = (cnk[8][0][0]*ik[3][0][0]);
    ikcnkt[8][0][1] = (cnk[8][1][0]*ik[3][0][0]);
    ikcnkt[8][0][2] = (cnk[8][2][0]*ik[3][0][0]);
    ikcnkt[8][1][0] = (cnk[6][0][1]*ik[3][1][1]);
    ikcnkt[8][1][1] = (cnk[6][1][1]*ik[3][1][1]);
    ikcnkt[8][1][2] = (cnk[6][2][1]*ik[3][1][1]);
    ikcnkt[8][2][0] = (cnk[8][0][2]*ik[3][2][2]);
    ikcnkt[8][2][1] = (cnk[8][1][2]*ik[3][2][2]);
    ikcnkt[8][2][2] = (cnk[8][2][2]*ik[3][2][2]);
    ikcnkt[11][0][0] = (cnk[11][0][0]*ik[4][0][0]);
    ikcnkt[11][0][1] = (cnk[11][1][0]*ik[4][0][0]);
    ikcnkt[11][0][2] = (cnk[11][2][0]*ik[4][0][0]);
    ikcnkt[11][1][0] = (cnk[10][0][1]*ik[4][1][1]);
    ikcnkt[11][1][1] = (cnk[10][1][1]*ik[4][1][1]);
    ikcnkt[11][1][2] = (cnk[10][2][1]*ik[4][1][1]);
    ikcnkt[11][2][0] = (cnk[11][0][2]*ik[4][2][2]);
    ikcnkt[11][2][1] = (cnk[11][1][2]*ik[4][2][2]);
    ikcnkt[11][2][2] = (cnk[11][2][2]*ik[4][2][2]);
    ikcnkt[12][0][0] = (cnk[12][0][0]*ik[5][0][0]);
    ikcnkt[12][0][1] = (cnk[12][1][0]*ik[5][0][0]);
    ikcnkt[12][0][2] = (cnk[12][2][0]*ik[5][0][0]);
    ikcnkt[12][1][0] = (cnk[10][0][1]*ik[5][1][1]);
    ikcnkt[12][1][1] = (cnk[10][1][1]*ik[5][1][1]);
    ikcnkt[12][1][2] = (cnk[10][2][1]*ik[5][1][1]);
    ikcnkt[12][2][0] = (cnk[12][0][2]*ik[5][2][2]);
    ikcnkt[12][2][1] = (cnk[12][1][2]*ik[5][2][2]);
    ikcnkt[12][2][2] = (cnk[12][2][2]*ik[5][2][2]);
    ikcnkt[14][0][0] = (cnk[13][0][0]*ik[6][0][0]);
    ikcnkt[14][0][1] = (cnk[13][1][0]*ik[6][0][0]);
    ikcnkt[14][0][2] = (cnk[13][2][0]*ik[6][0][0]);
    ikcnkt[14][1][0] = (cnk[14][0][1]*ik[6][1][1]);
    ikcnkt[14][1][1] = (cnk[14][1][1]*ik[6][1][1]);
    ikcnkt[14][1][2] = (cnk[14][2][1]*ik[6][1][1]);
    ikcnkt[14][2][0] = (cnk[14][0][2]*ik[6][2][2]);
    ikcnkt[14][2][1] = (cnk[14][1][2]*ik[6][2][2]);
    ikcnkt[14][2][2] = (cnk[14][2][2]*ik[6][2][2]);
    ikcnkt[17][0][0] = (cnk[17][0][0]*ik[7][0][0]);
    ikcnkt[17][0][1] = (cnk[17][1][0]*ik[7][0][0]);
    ikcnkt[17][0][2] = (cnk[17][2][0]*ik[7][0][0]);
    ikcnkt[17][1][0] = (cnk[16][0][1]*ik[7][1][1]);
    ikcnkt[17][1][1] = (cnk[16][1][1]*ik[7][1][1]);
    ikcnkt[17][1][2] = (cnk[16][2][1]*ik[7][1][1]);
    ikcnkt[17][2][0] = (cnk[17][0][2]*ik[7][2][2]);
    ikcnkt[17][2][1] = (cnk[17][1][2]*ik[7][2][2]);
    ikcnkt[17][2][2] = (cnk[17][2][2]*ik[7][2][2]);
    ikcnkt[18][0][0] = (cnk[18][0][0]*ik[8][0][0]);
    ikcnkt[18][0][1] = (cnk[18][1][0]*ik[8][0][0]);
    ikcnkt[18][0][2] = (cnk[18][2][0]*ik[8][0][0]);
    ikcnkt[18][1][0] = (cnk[16][0][1]*ik[8][1][1]);
    ikcnkt[18][1][1] = (cnk[16][1][1]*ik[8][1][1]);
    ikcnkt[18][1][2] = (cnk[16][2][1]*ik[8][1][1]);
    ikcnkt[18][2][0] = (cnk[18][0][2]*ik[8][2][2]);
    ikcnkt[18][2][1] = (cnk[18][1][2]*ik[8][2][2]);
    ikcnkt[18][2][2] = (cnk[18][2][2]*ik[8][2][2]);
    ikcnkt[20][0][0] = (cnk[19][0][0]*ik[9][0][0]);
    ikcnkt[20][0][1] = (cnk[19][1][0]*ik[9][0][0]);
    ikcnkt[20][0][2] = (cnk[19][2][0]*ik[9][0][0]);
    ikcnkt[20][1][0] = (cnk[20][0][1]*ik[9][1][1]);
    ikcnkt[20][1][1] = (cnk[20][1][1]*ik[9][1][1]);
    ikcnkt[20][1][2] = (cnk[20][2][1]*ik[9][1][1]);
    ikcnkt[20][2][0] = (cnk[20][0][2]*ik[9][2][2]);
    ikcnkt[20][2][1] = (cnk[20][1][2]*ik[9][2][2]);
    ikcnkt[20][2][2] = (cnk[20][2][2]*ik[9][2][2]);
    temp[0] = (((mk[0]*((rnk[5][1]*rnk[5][1])+(rnk[5][2]*rnk[5][2])))+((
      cnk[5][0][2]*ikcnkt[5][2][0])+((cnk[4][0][0]*ikcnkt[5][0][0])+(
      cnk[5][0][1]*ikcnkt[5][1][0]))))+((mk[1]*((rnk[6][1]*rnk[6][1])+(rnk[6][2]
      *rnk[6][2])))+((cnk[5][0][2]*ikcnkt[6][2][0])+((cnk[6][0][0]*
      ikcnkt[6][0][0])+(cnk[6][0][1]*ikcnkt[6][1][0])))));
    temp[1] = (((mk[3]*((rnk[8][1]*rnk[8][1])+(rnk[8][2]*rnk[8][2])))+((
      cnk[8][0][2]*ikcnkt[8][2][0])+((cnk[6][0][1]*ikcnkt[8][1][0])+(
      cnk[8][0][0]*ikcnkt[8][0][0]))))+(((mk[2]*((rnk[7][1]*rnk[7][1])+(
      rnk[7][2]*rnk[7][2])))+((cnk[7][0][2]*ikcnkt[7][2][0])+((cnk[6][0][1]*
      ikcnkt[7][1][0])+(cnk[7][0][0]*ikcnkt[7][0][0]))))+temp[0]));
    temp[2] = (((mk[5]*((rnk[12][1]*rnk[12][1])+(rnk[12][2]*rnk[12][2])))+((
      cnk[12][0][2]*ikcnkt[12][2][0])+((cnk[10][0][1]*ikcnkt[12][1][0])+(
      cnk[12][0][0]*ikcnkt[12][0][0]))))+(((mk[4]*((rnk[11][1]*rnk[11][1])+(
      rnk[11][2]*rnk[11][2])))+((cnk[11][0][2]*ikcnkt[11][2][0])+((cnk[10][0][1]
      *ikcnkt[11][1][0])+(cnk[11][0][0]*ikcnkt[11][0][0]))))+temp[1]));
    temp[3] = (((mk[7]*((rnk[17][1]*rnk[17][1])+(rnk[17][2]*rnk[17][2])))+((
      cnk[17][0][2]*ikcnkt[17][2][0])+((cnk[16][0][1]*ikcnkt[17][1][0])+(
      cnk[17][0][0]*ikcnkt[17][0][0]))))+(((mk[6]*((rnk[14][1]*rnk[14][1])+(
      rnk[14][2]*rnk[14][2])))+((cnk[14][0][2]*ikcnkt[14][2][0])+((cnk[13][0][0]
      *ikcnkt[14][0][0])+(cnk[14][0][1]*ikcnkt[14][1][0]))))+temp[2]));
    icm[0][0] = ((((mk[9]*((rnk[20][1]*rnk[20][1])+(rnk[20][2]*rnk[20][2])))+((
      cnk[20][0][2]*ikcnkt[20][2][0])+((cnk[19][0][0]*ikcnkt[20][0][0])+(
      cnk[20][0][1]*ikcnkt[20][1][0]))))+(((mk[8]*((rnk[18][1]*rnk[18][1])+(
      rnk[18][2]*rnk[18][2])))+((cnk[18][0][2]*ikcnkt[18][2][0])+((cnk[16][0][1]
      *ikcnkt[18][1][0])+(cnk[18][0][0]*ikcnkt[18][0][0]))))+temp[3]))-(mtot*((
      com[1]*com[1])+(com[2]*com[2]))));
    temp[0] = ((((cnk[7][0][2]*ikcnkt[7][2][1])+((cnk[6][0][1]*ikcnkt[7][1][1])+
      (cnk[7][0][0]*ikcnkt[7][0][1])))-(mk[2]*(rnk[7][0]*rnk[7][1])))+((((
      cnk[5][0][2]*ikcnkt[5][2][1])+((cnk[4][0][0]*ikcnkt[5][0][1])+(
      cnk[5][0][1]*ikcnkt[5][1][1])))-(mk[0]*(rnk[5][0]*rnk[5][1])))+(((
      cnk[5][0][2]*ikcnkt[6][2][1])+((cnk[6][0][0]*ikcnkt[6][0][1])+(
      cnk[6][0][1]*ikcnkt[6][1][1])))-(mk[1]*(rnk[6][0]*rnk[6][1])))));
    temp[1] = ((((cnk[12][0][2]*ikcnkt[12][2][1])+((cnk[10][0][1]*
      ikcnkt[12][1][1])+(cnk[12][0][0]*ikcnkt[12][0][1])))-(mk[5]*(rnk[12][0]*
      rnk[12][1])))+((((cnk[11][0][2]*ikcnkt[11][2][1])+((cnk[10][0][1]*
      ikcnkt[11][1][1])+(cnk[11][0][0]*ikcnkt[11][0][1])))-(mk[4]*(rnk[11][0]*
      rnk[11][1])))+((((cnk[8][0][2]*ikcnkt[8][2][1])+((cnk[6][0][1]*
      ikcnkt[8][1][1])+(cnk[8][0][0]*ikcnkt[8][0][1])))-(mk[3]*(rnk[8][0]*
      rnk[8][1])))+temp[0])));
    temp[2] = ((((cnk[18][0][2]*ikcnkt[18][2][1])+((cnk[16][0][1]*
      ikcnkt[18][1][1])+(cnk[18][0][0]*ikcnkt[18][0][1])))-(mk[8]*(rnk[18][0]*
      rnk[18][1])))+((((cnk[17][0][2]*ikcnkt[17][2][1])+((cnk[16][0][1]*
      ikcnkt[17][1][1])+(cnk[17][0][0]*ikcnkt[17][0][1])))-(mk[7]*(rnk[17][0]*
      rnk[17][1])))+((((cnk[14][0][2]*ikcnkt[14][2][1])+((cnk[13][0][0]*
      ikcnkt[14][0][1])+(cnk[14][0][1]*ikcnkt[14][1][1])))-(mk[6]*(rnk[14][0]*
      rnk[14][1])))+temp[1])));
    icm[0][1] = ((mtot*(com[0]*com[1]))+((((cnk[20][0][2]*ikcnkt[20][2][1])+((
      cnk[19][0][0]*ikcnkt[20][0][1])+(cnk[20][0][1]*ikcnkt[20][1][1])))-(mk[9]*
      (rnk[20][0]*rnk[20][1])))+temp[2]));
    temp[0] = ((((cnk[7][0][2]*ikcnkt[7][2][2])+((cnk[6][0][1]*ikcnkt[7][1][2])+
      (cnk[7][0][0]*ikcnkt[7][0][2])))-(mk[2]*(rnk[7][0]*rnk[7][2])))+((((
      cnk[5][0][2]*ikcnkt[5][2][2])+((cnk[4][0][0]*ikcnkt[5][0][2])+(
      cnk[5][0][1]*ikcnkt[5][1][2])))-(mk[0]*(rnk[5][0]*rnk[5][2])))+(((
      cnk[5][0][2]*ikcnkt[6][2][2])+((cnk[6][0][0]*ikcnkt[6][0][2])+(
      cnk[6][0][1]*ikcnkt[6][1][2])))-(mk[1]*(rnk[6][0]*rnk[6][2])))));
    temp[1] = ((((cnk[12][0][2]*ikcnkt[12][2][2])+((cnk[10][0][1]*
      ikcnkt[12][1][2])+(cnk[12][0][0]*ikcnkt[12][0][2])))-(mk[5]*(rnk[12][0]*
      rnk[12][2])))+((((cnk[11][0][2]*ikcnkt[11][2][2])+((cnk[10][0][1]*
      ikcnkt[11][1][2])+(cnk[11][0][0]*ikcnkt[11][0][2])))-(mk[4]*(rnk[11][0]*
      rnk[11][2])))+((((cnk[8][0][2]*ikcnkt[8][2][2])+((cnk[6][0][1]*
      ikcnkt[8][1][2])+(cnk[8][0][0]*ikcnkt[8][0][2])))-(mk[3]*(rnk[8][0]*
      rnk[8][2])))+temp[0])));
    temp[2] = ((((cnk[18][0][2]*ikcnkt[18][2][2])+((cnk[16][0][1]*
      ikcnkt[18][1][2])+(cnk[18][0][0]*ikcnkt[18][0][2])))-(mk[8]*(rnk[18][0]*
      rnk[18][2])))+((((cnk[17][0][2]*ikcnkt[17][2][2])+((cnk[16][0][1]*
      ikcnkt[17][1][2])+(cnk[17][0][0]*ikcnkt[17][0][2])))-(mk[7]*(rnk[17][0]*
      rnk[17][2])))+((((cnk[14][0][2]*ikcnkt[14][2][2])+((cnk[13][0][0]*
      ikcnkt[14][0][2])+(cnk[14][0][1]*ikcnkt[14][1][2])))-(mk[6]*(rnk[14][0]*
      rnk[14][2])))+temp[1])));
    icm[0][2] = ((mtot*(com[0]*com[2]))+((((cnk[20][0][2]*ikcnkt[20][2][2])+((
      cnk[19][0][0]*ikcnkt[20][0][2])+(cnk[20][0][1]*ikcnkt[20][1][2])))-(mk[9]*
      (rnk[20][0]*rnk[20][2])))+temp[2]));
    icm[1][0] = icm[0][1];
    temp[0] = (((mk[0]*((rnk[5][0]*rnk[5][0])+(rnk[5][2]*rnk[5][2])))+((
      cnk[5][1][2]*ikcnkt[5][2][1])+((cnk[4][1][0]*ikcnkt[5][0][1])+(
      cnk[5][1][1]*ikcnkt[5][1][1]))))+((mk[1]*((rnk[6][0]*rnk[6][0])+(rnk[6][2]
      *rnk[6][2])))+((cnk[5][1][2]*ikcnkt[6][2][1])+((cnk[6][1][0]*
      ikcnkt[6][0][1])+(cnk[6][1][1]*ikcnkt[6][1][1])))));
    temp[1] = (((mk[3]*((rnk[8][0]*rnk[8][0])+(rnk[8][2]*rnk[8][2])))+((
      cnk[8][1][2]*ikcnkt[8][2][1])+((cnk[6][1][1]*ikcnkt[8][1][1])+(
      cnk[8][1][0]*ikcnkt[8][0][1]))))+(((mk[2]*((rnk[7][0]*rnk[7][0])+(
      rnk[7][2]*rnk[7][2])))+((cnk[7][1][2]*ikcnkt[7][2][1])+((cnk[6][1][1]*
      ikcnkt[7][1][1])+(cnk[7][1][0]*ikcnkt[7][0][1]))))+temp[0]));
    temp[2] = (((mk[5]*((rnk[12][0]*rnk[12][0])+(rnk[12][2]*rnk[12][2])))+((
      cnk[12][1][2]*ikcnkt[12][2][1])+((cnk[10][1][1]*ikcnkt[12][1][1])+(
      cnk[12][1][0]*ikcnkt[12][0][1]))))+(((mk[4]*((rnk[11][0]*rnk[11][0])+(
      rnk[11][2]*rnk[11][2])))+((cnk[11][1][2]*ikcnkt[11][2][1])+((cnk[10][1][1]
      *ikcnkt[11][1][1])+(cnk[11][1][0]*ikcnkt[11][0][1]))))+temp[1]));
    temp[3] = (((mk[7]*((rnk[17][0]*rnk[17][0])+(rnk[17][2]*rnk[17][2])))+((
      cnk[17][1][2]*ikcnkt[17][2][1])+((cnk[16][1][1]*ikcnkt[17][1][1])+(
      cnk[17][1][0]*ikcnkt[17][0][1]))))+(((mk[6]*((rnk[14][0]*rnk[14][0])+(
      rnk[14][2]*rnk[14][2])))+((cnk[14][1][2]*ikcnkt[14][2][1])+((cnk[13][1][0]
      *ikcnkt[14][0][1])+(cnk[14][1][1]*ikcnkt[14][1][1]))))+temp[2]));
    icm[1][1] = ((((mk[9]*((rnk[20][0]*rnk[20][0])+(rnk[20][2]*rnk[20][2])))+((
      cnk[20][1][2]*ikcnkt[20][2][1])+((cnk[19][1][0]*ikcnkt[20][0][1])+(
      cnk[20][1][1]*ikcnkt[20][1][1]))))+(((mk[8]*((rnk[18][0]*rnk[18][0])+(
      rnk[18][2]*rnk[18][2])))+((cnk[18][1][2]*ikcnkt[18][2][1])+((cnk[16][1][1]
      *ikcnkt[18][1][1])+(cnk[18][1][0]*ikcnkt[18][0][1]))))+temp[3]))-(mtot*((
      com[0]*com[0])+(com[2]*com[2]))));
    temp[0] = ((((cnk[7][1][2]*ikcnkt[7][2][2])+((cnk[6][1][1]*ikcnkt[7][1][2])+
      (cnk[7][1][0]*ikcnkt[7][0][2])))-(mk[2]*(rnk[7][1]*rnk[7][2])))+((((
      cnk[5][1][2]*ikcnkt[5][2][2])+((cnk[4][1][0]*ikcnkt[5][0][2])+(
      cnk[5][1][1]*ikcnkt[5][1][2])))-(mk[0]*(rnk[5][1]*rnk[5][2])))+(((
      cnk[5][1][2]*ikcnkt[6][2][2])+((cnk[6][1][0]*ikcnkt[6][0][2])+(
      cnk[6][1][1]*ikcnkt[6][1][2])))-(mk[1]*(rnk[6][1]*rnk[6][2])))));
    temp[1] = ((((cnk[12][1][2]*ikcnkt[12][2][2])+((cnk[10][1][1]*
      ikcnkt[12][1][2])+(cnk[12][1][0]*ikcnkt[12][0][2])))-(mk[5]*(rnk[12][1]*
      rnk[12][2])))+((((cnk[11][1][2]*ikcnkt[11][2][2])+((cnk[10][1][1]*
      ikcnkt[11][1][2])+(cnk[11][1][0]*ikcnkt[11][0][2])))-(mk[4]*(rnk[11][1]*
      rnk[11][2])))+((((cnk[8][1][2]*ikcnkt[8][2][2])+((cnk[6][1][1]*
      ikcnkt[8][1][2])+(cnk[8][1][0]*ikcnkt[8][0][2])))-(mk[3]*(rnk[8][1]*
      rnk[8][2])))+temp[0])));
    temp[2] = ((((cnk[18][1][2]*ikcnkt[18][2][2])+((cnk[16][1][1]*
      ikcnkt[18][1][2])+(cnk[18][1][0]*ikcnkt[18][0][2])))-(mk[8]*(rnk[18][1]*
      rnk[18][2])))+((((cnk[17][1][2]*ikcnkt[17][2][2])+((cnk[16][1][1]*
      ikcnkt[17][1][2])+(cnk[17][1][0]*ikcnkt[17][0][2])))-(mk[7]*(rnk[17][1]*
      rnk[17][2])))+((((cnk[14][1][2]*ikcnkt[14][2][2])+((cnk[13][1][0]*
      ikcnkt[14][0][2])+(cnk[14][1][1]*ikcnkt[14][1][2])))-(mk[6]*(rnk[14][1]*
      rnk[14][2])))+temp[1])));
    icm[1][2] = ((mtot*(com[1]*com[2]))+((((cnk[20][1][2]*ikcnkt[20][2][2])+((
      cnk[19][1][0]*ikcnkt[20][0][2])+(cnk[20][1][1]*ikcnkt[20][1][2])))-(mk[9]*
      (rnk[20][1]*rnk[20][2])))+temp[2]));
    icm[2][0] = icm[0][2];
    icm[2][1] = icm[1][2];
    temp[0] = (((mk[0]*((rnk[5][0]*rnk[5][0])+(rnk[5][1]*rnk[5][1])))+((
      cnk[5][2][2]*ikcnkt[5][2][2])+((cnk[5][2][1]*ikcnkt[5][1][2])-(
      ikcnkt[5][0][2]*s4))))+((mk[1]*((rnk[6][0]*rnk[6][0])+(rnk[6][1]*rnk[6][1]
      )))+((cnk[5][2][2]*ikcnkt[6][2][2])+((cnk[6][2][0]*ikcnkt[6][0][2])+(
      cnk[6][2][1]*ikcnkt[6][1][2])))));
    temp[1] = (((mk[3]*((rnk[8][0]*rnk[8][0])+(rnk[8][1]*rnk[8][1])))+((
      cnk[8][2][2]*ikcnkt[8][2][2])+((cnk[6][2][1]*ikcnkt[8][1][2])+(
      cnk[8][2][0]*ikcnkt[8][0][2]))))+(((mk[2]*((rnk[7][0]*rnk[7][0])+(
      rnk[7][1]*rnk[7][1])))+((cnk[7][2][2]*ikcnkt[7][2][2])+((cnk[6][2][1]*
      ikcnkt[7][1][2])+(cnk[7][2][0]*ikcnkt[7][0][2]))))+temp[0]));
    temp[2] = (((mk[5]*((rnk[12][0]*rnk[12][0])+(rnk[12][1]*rnk[12][1])))+((
      cnk[12][2][2]*ikcnkt[12][2][2])+((cnk[10][2][1]*ikcnkt[12][1][2])+(
      cnk[12][2][0]*ikcnkt[12][0][2]))))+(((mk[4]*((rnk[11][0]*rnk[11][0])+(
      rnk[11][1]*rnk[11][1])))+((cnk[11][2][2]*ikcnkt[11][2][2])+((cnk[10][2][1]
      *ikcnkt[11][1][2])+(cnk[11][2][0]*ikcnkt[11][0][2]))))+temp[1]));
    temp[3] = (((mk[7]*((rnk[17][0]*rnk[17][0])+(rnk[17][1]*rnk[17][1])))+((
      cnk[17][2][2]*ikcnkt[17][2][2])+((cnk[16][2][1]*ikcnkt[17][1][2])+(
      cnk[17][2][0]*ikcnkt[17][0][2]))))+(((mk[6]*((rnk[14][0]*rnk[14][0])+(
      rnk[14][1]*rnk[14][1])))+((cnk[14][2][2]*ikcnkt[14][2][2])+((cnk[13][2][0]
      *ikcnkt[14][0][2])+(cnk[14][2][1]*ikcnkt[14][1][2]))))+temp[2]));
    icm[2][2] = ((((mk[9]*((rnk[20][0]*rnk[20][0])+(rnk[20][1]*rnk[20][1])))+((
      cnk[20][2][2]*ikcnkt[20][2][2])+((cnk[19][2][0]*ikcnkt[20][0][2])+(
      cnk[20][2][1]*ikcnkt[20][1][2]))))+(((mk[8]*((rnk[18][0]*rnk[18][0])+(
      rnk[18][1]*rnk[18][1])))+((cnk[18][2][2]*ikcnkt[18][2][2])+((cnk[16][2][1]
      *ikcnkt[18][1][2])+(cnk[18][2][0]*ikcnkt[18][0][2]))))+temp[3]))-(mtot*((
      com[0]*com[0])+(com[1]*com[1]))));
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  274 adds/subtracts/negates
                    435 multiplies
                      0 divides
                    124 assignments
*/
}

void sdpos(int body,
    double pt[3],
    double loc[3])
{
/*
Return inertial frame location of a point on a body.

*/
    double pv[3];

    if (sdchkbnum(21,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(21,23);
        return;
    }
    if (body  ==  -1) {
        loc[0] = pt[0];
        loc[1] = pt[1];
        loc[2] = pt[2];
    } else {
        pv[0] = rnb[body][0]+pt[0]*cnb[body][0][0]+pt[1]*cnb[body][0][1]+pt[2]*
          cnb[body][0][2];
        pv[1] = rnb[body][1]+pt[0]*cnb[body][1][0]+pt[1]*cnb[body][1][1]+pt[2]*
          cnb[body][1][2];
        pv[2] = rnb[body][2]+pt[0]*cnb[body][2][0]+pt[1]*cnb[body][2][1]+pt[2]*
          cnb[body][2][2];
        loc[0] = pv[0];
        loc[1] = pv[1];
        loc[2] = pv[2];
    }
}

void sdvel(int body,
    double pt[3],
    double velo[3])
{
/*
Return inertial frame velocity of a point on a body.

*/
    double pv[3];

    if (sdchkbnum(22,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(22,23);
        return;
    }
    if (body  ==  -1) {
        velo[0] = 0.;
        velo[1] = 0.;
        velo[2] = 0.;
    } else {
        pv[0] = wb[body][1]*pt[2]-wb[body][2]*pt[1];
        pv[1] = wb[body][2]*pt[0]-wb[body][0]*pt[2];
        pv[2] = wb[body][0]*pt[1]-wb[body][1]*pt[0];
        velo[0] = vnb[body][0]+pv[0]*cnb[body][0][0]+pv[1]*cnb[body][0][1]+pv[2]
          *cnb[body][0][2];
        velo[1] = vnb[body][1]+pv[0]*cnb[body][1][0]+pv[1]*cnb[body][1][1]+pv[2]
          *cnb[body][1][2];
        velo[2] = vnb[body][2]+pv[0]*cnb[body][2][0]+pv[1]*cnb[body][2][1]+pv[2]
          *cnb[body][2][2];
    }
}

void sdorient(int body,
    double dircos[3][3])
{
/*
Return orientation of body w.r.t. ground frame.

*/

    if (sdchkbnum(23,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(23,23);
        return;
    }
    if (body == -1) {
        dircos[0][0] = 1.;
        dircos[0][1] = 0.;
        dircos[0][2] = 0.;
        dircos[1][0] = 0.;
        dircos[1][1] = 1.;
        dircos[1][2] = 0.;
        dircos[2][0] = 0.;
        dircos[2][1] = 0.;
        dircos[2][2] = 1.;
    } else {
        dircos[0][0] = cnb[body][0][0];
        dircos[0][1] = cnb[body][0][1];
        dircos[0][2] = cnb[body][0][2];
        dircos[1][0] = cnb[body][1][0];
        dircos[1][1] = cnb[body][1][1];
        dircos[1][2] = cnb[body][1][2];
        dircos[2][0] = cnb[body][2][0];
        dircos[2][1] = cnb[body][2][1];
        dircos[2][2] = cnb[body][2][2];
    }
}

void sdangvel(int body,
    double avel[3])
{
/*
Return angular velocity of the body.

*/

    if (sdchkbnum(24,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(24,23);
        return;
    }
    if (body == -1) {
        avel[0] = 0.;
        avel[1] = 0.;
        avel[2] = 0.;
    } else {
        avel[0] = wb[body][0];
        avel[1] = wb[body][1];
        avel[2] = wb[body][2];
    }
}

void sdtrans(int frbod,
    double ivec[3],
    int tobod,
    double ovec[3])
{
/*
Transform ivec from frbod frame to tobod frame.

*/
    double pv[3];

    if (sdchkbnum(25,frbod) != 0) {
        return;
    }
    if (sdchkbnum(25,tobod) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(25,23);
        return;
    }
    if (frbod == tobod) {
        sdvcopy(ivec,ovec);
        return;
    }
    if (frbod == -1) {
        sdvcopy(ivec,pv);
        ovec[0] = pv[0]*cnb[tobod][0][0]+pv[1]*cnb[tobod][1][0]+pv[2]*cnb[tobod
          ][2][0];
        ovec[1] = pv[0]*cnb[tobod][0][1]+pv[1]*cnb[tobod][1][1]+pv[2]*cnb[tobod
          ][2][1];
        ovec[2] = pv[0]*cnb[tobod][0][2]+pv[1]*cnb[tobod][1][2]+pv[2]*cnb[tobod
          ][2][2];
        return;
    }
    if (tobod == -1) {
        sdvcopy(ivec,pv);
        ovec[0] = pv[0]*cnb[frbod][0][0]+pv[1]*cnb[frbod][0][1]+pv[2]*cnb[frbod
          ][0][2];
        ovec[1] = pv[0]*cnb[frbod][1][0]+pv[1]*cnb[frbod][1][1]+pv[2]*cnb[frbod
          ][1][2];
        ovec[2] = pv[0]*cnb[frbod][2][0]+pv[1]*cnb[frbod][2][1]+pv[2]*cnb[frbod
          ][2][2];
        return;
    }
    pv[0] = ivec[0]*cnb[frbod][0][0]+ivec[1]*cnb[frbod][0][1]+ivec[2]*cnb[frbod
      ][0][2];
    pv[1] = ivec[0]*cnb[frbod][1][0]+ivec[1]*cnb[frbod][1][1]+ivec[2]*cnb[frbod
      ][1][2];
    pv[2] = ivec[0]*cnb[frbod][2][0]+ivec[1]*cnb[frbod][2][1]+ivec[2]*cnb[frbod
      ][2][2];
    ovec[0] = pv[0]*cnb[tobod][0][0]+pv[1]*cnb[tobod][1][0]+pv[2]*cnb[tobod][2][
      0];
    ovec[1] = pv[0]*cnb[tobod][0][1]+pv[1]*cnb[tobod][1][1]+pv[2]*cnb[tobod][2][
      1];
    ovec[2] = pv[0]*cnb[tobod][0][2]+pv[1]*cnb[tobod][1][2]+pv[2]*cnb[tobod][2][
      2];
}

void sdrel2cart(int coord,
    int body,
    double point[3],
    double linchg[3],
    double rotchg[3])
{
/* Return derivative of pt loc and body orient w.r.t. hinge rate
*/
    int x,i,gnd;
    double lin[3],pv[3];

    if ((coord < 0) || (coord > 20)) {
        sdseterr(59,45);
        return;
    }
    if (sdchkbnum(59,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(59,23);
        return;
    }
    gnd = -1;
    if (body == gnd) {
        x = -1;
    } else {
        x = firstq[body]+njntdof[body]-1;
    }
    if (x < coord) {
        sdvset(0.,0.,0.,linchg);
        sdvset(0.,0.,0.,rotchg);
        return;
    }
    sddovpk();
    for (i = 0; i < 3; i++) {
        rotchg[i] = Wpk[coord][x][i];
        lin[i] = Vpk[coord][x][i];
    }
    if (body == gnd) {
        sdvcopy(point,pv);
    } else {
        pv[0] = rcom[body][0]+point[0];
        pv[1] = rcom[body][1]+point[1];
        pv[2] = rcom[body][2]+point[2];
    }
    sdvcross(rotchg,pv,linchg);
    sdvadd(linchg,lin,linchg);
}

void sdacc(int body,
    double pt[3],
    double accel[3])
{
/*
Return linear acceleration a point of the specified body.

*/
    double pv[3];

    if (sdchkbnum(32,body) != 0) {
        return;
    }
    if (roustate != 3) {
        sdseterr(32,24);
        return;
    }
    if (body  ==  -1) {
        accel[0] = 0.;
        accel[1] = 0.;
        accel[2] = 0.;
    } else {
        pv[0] = pt[0]*dyad[body][0][0]+pt[1]*dyad[body][0][1]+pt[2]*dyad[body][0
          ][2];
        pv[1] = pt[0]*dyad[body][1][0]+pt[1]*dyad[body][1][1]+pt[2]*dyad[body][1
          ][2];
        pv[2] = pt[0]*dyad[body][2][0]+pt[1]*dyad[body][2][1]+pt[2]*dyad[body][2
          ][2];
        accel[0] = anb[body][0]+pv[0]*cnb[body][0][0]+pv[1]*cnb[body][0][1]+pv[2
          ]*cnb[body][0][2];
        accel[1] = anb[body][1]+pv[0]*cnb[body][1][0]+pv[1]*cnb[body][1][1]+pv[2
          ]*cnb[body][1][2];
        accel[2] = anb[body][2]+pv[0]*cnb[body][2][0]+pv[1]*cnb[body][2][1]+pv[2
          ]*cnb[body][2][2];
    }
}

void sdangacc(int body,
    double aacc[3])
{
/*
Return angular acceleration of the body.

*/

    if (sdchkbnum(33,body) != 0) {
        return;
    }
    if (roustate != 3) {
        sdseterr(33,24);
        return;
    }
    if (body == -1) {
        aacc[0] = 0.;
        aacc[1] = 0.;
        aacc[2] = 0.;
    } else {
        aacc[0] = onb[body][0];
        aacc[1] = onb[body][1];
        aacc[2] = onb[body][2];
    }
}

void sdgrav(double gravin[3])
{

    sdseterr(1,19);
    roustate = 0;
}

void sdmass(int body,
    double massin)
{

    if (sdchkbnum(2,body) != 0) {
        return;
    }
    if (body == -1) {
        sdseterr(2,15);
        return;
    }
    if (mkq[body] != 0) {
        mk[body] = massin;
        mkq[body] = 3;
    } else {
        sdseterr(2,19);
    }
    roustate = 0;
}

void sdiner(int body,
    double inerin[3][3])
{
    int anyques;

    if (sdchkbnum(3,body) != 0) {
        return;
    }
    if (body == -1) {
        sdseterr(3,15);
        return;
    }
    anyques = 0;
    if (ikq[body][0][0]  !=  0) {
        ik[body][0][0] = inerin[0][0];
        ikq[body][0][0] = 3;
        anyques = 1;
    }
    if (ikq[body][0][1]  !=  0) {
        ik[body][0][1] = inerin[0][1];
        ikq[body][0][1] = 3;
        ik[body][1][0] = inerin[0][1];
        ikq[body][1][0] = 3;
        anyques = 1;
    }
    if (ikq[body][0][2]  !=  0) {
        ik[body][0][2] = inerin[0][2];
        ikq[body][0][2] = 3;
        ik[body][2][0] = inerin[0][2];
        ikq[body][2][0] = 3;
        anyques = 1;
    }
    if (ikq[body][1][1]  !=  0) {
        ik[body][1][1] = inerin[1][1];
        ikq[body][1][1] = 3;
        anyques = 1;
    }
    if (ikq[body][1][2]  !=  0) {
        ik[body][1][2] = inerin[1][2];
        ikq[body][1][2] = 3;
        ik[body][2][1] = inerin[1][2];
        ikq[body][2][1] = 3;
        anyques = 1;
    }
    if (ikq[body][2][2]  !=  0) {
        ik[body][2][2] = inerin[2][2];
        ikq[body][2][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        sdseterr(3,19);
    }
    roustate = 0;
}

void sdbtj(int joint,
    double btjin[3])
{
    int anyques;

    if (sdchkjnum(4,joint) != 0) {
        return;
    }
    anyques = 0;
    if (rkq[joint][0]  !=  0) {
        rk[joint][0] = btjin[0];
        rkq[joint][0] = 3;
        anyques = 1;
    }
    if (rkq[joint][1]  !=  0) {
        rk[joint][1] = btjin[1];
        rkq[joint][1] = 3;
        anyques = 1;
    }
    if (rkq[joint][2]  !=  0) {
        rk[joint][2] = btjin[2];
        rkq[joint][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        sdseterr(4,19);
    }
    roustate = 0;
}

void sditj(int joint,
    double itjin[3])
{
    int anyques;

    if (sdchkjnum(5,joint) != 0) {
        return;
    }
    anyques = 0;
    if (riq[joint][0]  !=  0) {
        ri[joint][0] = itjin[0];
        riq[joint][0] = 3;
        anyques = 1;
    }
    if (riq[joint][1]  !=  0) {
        ri[joint][1] = itjin[1];
        riq[joint][1] = 3;
        anyques = 1;
    }
    if (riq[joint][2]  !=  0) {
        ri[joint][2] = itjin[2];
        riq[joint][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        sdseterr(5,19);
    }
    roustate = 0;
}

void sdpin(int joint,
    int pinno,
    double pinin[3])
{
    int anyques,offs;

    if (sdchkjpin(6,joint,pinno) != 0) {
        return;
    }
    anyques = 0;
    offs = firstq[joint]+pinno;
    if (jtype[joint] == 21) {
        offs = offs+3;
    }
    if (jtype[joint] == 11) {
        offs = offs+1;
    }
    if (pinq[offs][0]  !=  0) {
        pin[offs][0] = pinin[0];
        pinq[offs][0] = 3;
        anyques = 1;
    }
    if (pinq[offs][1]  !=  0) {
        pin[offs][1] = pinin[1];
        pinq[offs][1] = 3;
        anyques = 1;
    }
    if (pinq[offs][2]  !=  0) {
        pin[offs][2] = pinin[2];
        pinq[offs][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        sdseterr(6,19);
    }
    roustate = 0;
}

void sdpres(int joint,
    int axis,
    int presin)
{
    int anyques;

    if (sdchkjaxis(37,joint,axis) != 0) {
        return;
    }
    if ((presin != 0) && (presin != 1)) {
        sdseterr(37,20);
    }
    anyques = 0;
    if (presq[sdindx(joint,axis)]  !=  0) {
        if (presin  !=  0) {
            pres[sdindx(joint,axis)] = 1.;
        } else {
            pres[sdindx(joint,axis)] = 0.;
        }
        presq[sdindx(joint,axis)] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        sdseterr(37,19);
    }
    wwflg = 0;
}

void sdconschg(void)
{

    wwflg = 0;
}

void sdstab(double velin,
    double posin)
{

    stabvel = velin;
    stabvelq = 3;
    stabpos = posin;
    stabposq = 3;
}

void sdgetgrav(double gravout[3])
{

    gravout[0] = grav[0];
    gravout[1] = grav[1];
    gravout[2] = grav[2];
}

void sdgetmass(int body,
    double *massout)
{

    if (sdchkbnum(40,body) != 0) {
        return;
    }
    if (body == -1) {
        sdseterr(40,15);
        return;
    }
    *massout = mk[body];
}

void sdgetiner(int body,
    double inerout[3][3])
{

    if (sdchkbnum(41,body) != 0) {
        return;
    }
    if (body == -1) {
        sdseterr(41,15);
        return;
    }
    inerout[0][0] = ik[body][0][0];
    inerout[0][1] = ik[body][0][1];
    inerout[0][2] = ik[body][0][2];
    inerout[1][0] = ik[body][1][0];
    inerout[1][1] = ik[body][1][1];
    inerout[1][2] = ik[body][1][2];
    inerout[2][0] = ik[body][2][0];
    inerout[2][1] = ik[body][2][1];
    inerout[2][2] = ik[body][2][2];
}

void sdgetbtj(int joint,
    double btjout[3])
{

    if (sdchkjnum(42,joint) != 0) {
        return;
    }
    btjout[0] = rk[joint][0];
    btjout[1] = rk[joint][1];
    btjout[2] = rk[joint][2];
}

void sdgetitj(int joint,
    double itjout[3])
{

    if (sdchkjnum(43,joint) != 0) {
        return;
    }
    itjout[0] = ri[joint][0];
    itjout[1] = ri[joint][1];
    itjout[2] = ri[joint][2];
}

void sdgetpin(int joint,
    int pinno,
    double pinout[3])
{
    int offs;

    if (sdchkjpin(44,joint,pinno) != 0) {
        return;
    }
    offs = firstq[joint]+pinno;
    if (jtype[joint] == 21) {
        offs = offs+3;
    }
    if (jtype[joint] == 11) {
        offs = offs+1;
    }
    pinout[0] = pin[offs][0];
    pinout[1] = pin[offs][1];
    pinout[2] = pin[offs][2];
}

void sdgetpres(int joint,
    int axis,
    int *presout)
{

    if (sdchkjaxis(45,joint,axis) != 0) {
        return;
    }
    if (pres[sdindx(joint,axis)]  !=  0.) {
        *presout = 1;
    } else {
        *presout = 0;
    }
}

void sdgetstab(double *velout,
    double *posout)
{

    *velout = stabvel;
    *posout = stabpos;
}

void sdinfo(int info[50])
{

    info[0] = ground;
    info[1] = nbod;
    info[2] = ndof;
    info[3] = ncons;
    info[4] = nloop;
    info[5] = nldof;
    info[6] = nloopc;
    info[7] = nball;
    info[8] = nlball;
    info[9] = npres;
    info[10] = nuser;
    info[11] = 0;
/* info entries from 12-49 are reserved */
}

void sdjnt(int joint,
    int info[50],
    int tran[6])
{
    int i,offs;

    if (sdchkjnum(48,joint) != 0) {
        return;
    }
    info[0] = jtype[joint];
    info[1] = 0;
    offs = 0;
    info[2] = inb[joint];
    info[3] = outb[joint];
    info[4] = njntdof[joint];
    info[5] = njntc[joint];
    info[6] = njntp[joint];
    info[7] = firstq[joint];
    info[8] = ballq[joint];
    info[9] = firstm[joint];
    info[10] = firstp[joint];
/* info entries from 11-49 are reserved */

    for (i = 0; i <= 5; i++) {
        if (i  <  njntdof[joint]) {
            tran[i] = trans[offs+firstq[joint]+i];
        } else {
            tran[i] = -1;
        }
    }
}

void sdcons(int consno,
    int info[50])
{

    if (sdchkucnum(49,consno) != 0) {
        return;
    }
/* There are no user constraints in this problem. */
}

void sdgentime(int *gentm)
{

    *gentm = 185822;
}
/*
Done. CPU seconds used: 0.08  Memory used: 1753088 bytes.
Equation complexity:
  sdstate:   754 adds  1067 multiplies     3 divides   860 assignments
  sdderiv:  5638 adds  6872 multiplies    21 divides  5199 assignments
  sdresid:  2085 adds  2293 multiplies     0 divides  1424 assignments
  sdreac:    496 adds   323 multiplies     0 divides   366 assignments
  sdmom:     239 adds   277 multiplies     0 divides    83 assignments
  sdsys:     274 adds   435 multiplies     0 divides   124 assignments
*/

#undef ground 
#undef nbod 
#undef ndof 
#undef ncons 
#undef nloop 
#undef nldof 
#undef nloopc 
#undef nball 
#undef nlball 
#undef npres 
#undef nuser 
#undef jtype 
#undef inb 
#undef outb 
#undef njntdof 
#undef njntc 
#undef njntp 
#undef firstq 
#undef ballq 
#undef firstm 
#undef firstp 
#undef trans 


#undef grav 
#undef mk 
#undef ik 
#undef pin 
#undef rk 
#undef ri 
#undef pres 
#undef stabvel 
#undef stabpos 
#undef rhead 
#undef rcom 
#undef psrcomg 
#undef psrcom 
#undef mkrcomt 
#undef psmk 
#undef psik 
#undef psrk 
#undef psri 
#undef psmkg 
#undef psikg 
#undef psrkg 
#undef psrig 
#undef mtot 
#undef mfrcflg 
#undef roustate 
#undef vpkflg 
#undef inerflg 
#undef mmflg 
#undef mmlduflg 
#undef wwflg 
#undef ltauflg 
#undef fs0flg 
#undef ii 
#undef mmap 
#undef gravq 
#undef mkq 
#undef ikq 
#undef pinq 
#undef rkq 
#undef riq 
#undef presq 
#undef stabvelq 
#undef stabposq 


#undef curtim 
#undef q 
#undef qn 
#undef u 
#undef cnk 
#undef cnb 
#undef rnkg 
#undef rnk 
#undef rnb 
#undef vnk 
#undef vnb 
#undef wk 
#undef wb 
#undef com 
#undef Cik 
#undef Cib 
#undef rikt 
#undef Iko 
#undef mkrk 
#undef Wkk 
#undef Vkk 
#undef dik 
#undef rpp 
#undef rpk 
#undef rik 
#undef rik2 
#undef rpri 
#undef Wik 
#undef Vik 
#undef Wirk 
#undef rkWkk 
#undef Wkrpk 
#undef VikWkr 
#undef wbrcom 
#undef perr 
#undef verr 
#undef aerr 
#undef mult 
#undef ufk 
#undef utk 
#undef utau 
#undef mfk 
#undef mtk 
#undef mtau 
#undef uacc 
#undef uvel 
#undef upos 
#undef s3 
#undef c3 
#undef s4 
#undef c4 
#undef s5 
#undef c5 
#undef s6 
#undef c6 
#undef s7 
#undef c7 
#undef s8 
#undef c8 
#undef s9 
#undef c9 
#undef s10 
#undef c10 
#undef s11 
#undef c11 
#undef s12 
#undef c12 
#undef s13 
#undef c13 
#undef s14 
#undef c14 
#undef s15 
#undef c15 
#undef s16 
#undef c16 
#undef s17 
#undef c17 
#undef s18 
#undef c18 
#undef s19 
#undef c19 
#undef s20 
#undef c20 


#undef qdot 
#undef Otk 
#undef Atk 
#undef AiOiWi 
#undef Fstar 
#undef Tstar 
#undef fs0 
#undef Fstark 
#undef Tstark 
#undef IkWk 
#undef IkbWk 
#undef WkIkWk 
#undef WkIkbWk 
#undef gk 
#undef w0w0 
#undef w1w1 
#undef w2w2 
#undef w0w1 
#undef w0w2 
#undef w1w2 
#undef w00w11 
#undef w00w22 
#undef w11w22 
#undef ww 
#undef qraux 
#undef mm 
#undef mlo 
#undef mdi 
#undef IkWpk 
#undef works 
#undef workss 
#undef Wpk 
#undef Vpk 
#undef VWri 
#undef wmap 
#undef multmap 
#undef jpvt 
#undef wsiz 
#undef wrank 


#undef fs 
#undef udot 
#undef ank 
#undef anb 
#undef onk 
#undef onb 
#undef Onkb 
#undef AOnkri 
#undef Ankb 
#undef AnkAtk 
#undef dyrcom 
#undef ffk 
#undef ttk 
#undef fccikt 
#undef ffkb 
#undef ttkb 
#undef dyad 
#undef fc 
#undef tc 
#undef tauc 


#undef temp 
#undef tmat1 
#undef tmat2 
#undef tvec1 
#undef tvec2 
#undef tvec3 
#undef tvec4 
#undef tvec5 
#undef tsc1 
#undef tsc2 
#undef tsc3 
}