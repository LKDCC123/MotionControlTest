// DRobotState.hpp
// data structure of the robot: 
// 20221222 Dcc <3120195094@bit.edu.cn>

#pragma once 
#ifndef DROBOTSTATE_HPP
#define DROBOTSTATE_HPP
#include "ControlHeaders.h"

_D_CONTROL_BEGIN

#define __DoFNum 20
class c_StateWBC {
    double dQ[__DoFNum]; // 
};

#define __JointsNum 14
class c_StateRobot {
    double dJoint[__JointsNum];
};

_D_CONTROL_END

#endif