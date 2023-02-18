cmake_minimum_required(VERSION 3.0)
project(ControlTest)
set(ROOT_PATH .)

include_directories(
    "${ROOT_PATH}/include"
    "${ROOT_PATH}/../SDFast/include"
    "${ROOT_PATH}/../../SDK/Eigen_SDK"
    "${ROOT_PATH}/../../SDK/SDFast_SDK"
    "${ROOT_PATH}/../../SDK/Sim_SDK/Mujocolib"
    "${ROOT_PATH}/../../SDK/LeeQP_SDK/include"
)

link_directories(
    "${ROOT_PATH}/../../SDK/Sim_SDK/Mujocolib/bin"
    "${ROOT_PATH}/../../SDK/LeeQP_SDK/lib"
)

aux_source_directory("${ROOT_PATH}/../../SDK/Sim_SDK" SRC_SIM)
aux_source_directory("${ROOT_PATH}/../../SDK/Sim_SDK/Mujocolib" SRC_SIM)
aux_source_directory("${ROOT_PATH}/../../SDK/Sim_SDK/Mujocolib/include" SRC_SIM)
aux_source_directory("${ROOT_PATH}/src" SRC_TEST)
aux_source_directory("${ROOT_PATH}/../../SDK/SDFast_SDK/SDFiles" SRC_SDFAST)
aux_source_directory("${ROOT_PATH}/../../SDK/SDFast_SDK" SRC_SDFAST)
aux_source_directory("${ROOT_PATH}/../../SDK/LeeQP_SDK/src" SRC_LEEQP)

add_executable(ControlTest
    Test.cpp
    ${SRC_SIM}
    ${SRC_TEST}
    ${SRC_SDFAST}
    ${SRC_LEEQP}
)

target_link_libraries(ControlTest PUBLIC
    glfw3.lib mujoco200.lib 
    LEigenQP_CPP.lib
)

target_compile_definitions(ControlTest PUBLIC
    NDEBUG
    _CONSOLE
    _UNICODE
    UNICODE
    _CRT_SECURE_NO_WARNINGS
)

target_compile_options(ControlTest PUBLIC
    /nologo
)

target_link_options(ControlTest PUBLIC
    # /out: ControlTest.exe
)

file(COPY "${ROOT_PATH}/../../SDK/Sim_SDK/Mujocolib/bin/mjkey.txt" DESTINATION "Debug") # COPY 后路径相对cmakelist，DESTINATION 后路径则相对于build文件夹