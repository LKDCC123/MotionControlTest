// DSDMechDefs.h
// 20221223 Dcc <3120195094@bit.edu.cn>

#pragma once
#ifndef DSMECHDEFS_H
#define DSMECHDEFS_H
#include <SDFastDefs.h>

_D_SDFAST_BEGIN

#define __BodyNum 10
#define __DoFNum 21
#define __JointNum 15
#define __MechParasNum 10

enum enBody { // body name
    midbody, uppbody, larm, rarm, lthigh, lshank, lfoot, rthigh, rshank, rfoot
};

// joint series

// 0-5:     float_z float_y float_x float_y float_p float_r 
// 6-8:     waist_0 larm_1 rarm_1 
// 9-14:    lleg_1 lleg_2 lleg_3 lleg_4 lleg_5 lleg_6
// 15-20:   rleg_1 rleg_2 rleg_3 rleg_4 rleg_5 rleg_6

_D_SDFAST_END

#endif

