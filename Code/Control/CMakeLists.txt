cmake_minimum_required(VERSION 3.0)
project(ControlTest)
set(ROOT_PATH .)

include_directories(
    ${ROOT_PATH}/include
    ${ROOT_PATH}/../../SDK/Eigen_SDK
    ${ROOT_PATH}/../../SDK/SDFast_SDK
)

link_directories(

)

aux_source_directory(
    ${ROOT_PATH}/src SRC_TEST
)

add_executable(ControlTest
    Test.cpp
    ${SRC_TEST}
)

target_link_libraries(ControlTest

)

target_compile_definitions(ControlTest PUBLIC
    NDEBUG
    _CNSOLE
    _UNICODE
    UNICODE
    _CRT_SECURE_NO_WARNINGS
)

target_compile_options(ControlTest PUBLIC
    /nologo
)

target_link_options(ControlTest PUBLIC
    /out: ControlTest.exe
)