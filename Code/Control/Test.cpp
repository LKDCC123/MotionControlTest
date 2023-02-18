// Test.hpp
// test the control 
// 20230216 dcc <3120195094@bit.edu.cn>
#include <MujocoBHR_api.h>



void main() {
    // choose your model
    fnvMujocoSimuInit(1, "D:/L.B/GitHUB/MotionControlTest/SDK/Sim_SDK/Mujocolib/models/bhr7p2_origin.xml"); 

    // start simulation in a background thread
    std::thread MujocoSimThread(fnvMujocoSimuLoop); 

    // render loop in the current thread
    while (!glfwWindowShouldClose(MJwindow) && !settings.exitrequest) fnvMujocoRenderLoop();

    // end simulation
    fnvMujocoSimuEnd();
    MujocoSimThread.join();
}