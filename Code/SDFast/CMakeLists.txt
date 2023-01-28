cmake_minimum_required(VERSION 3.0)
project(SDFastTest)
set(ROOT_PATH .)

include_directories(
    ${ROOT_PATH}/include
    ${ROOT_PATH}/../../SDK/Eigen_SDK
    ${ROOT_PATH}/../../SDK/SDFast_SDK
)

link_directories(

)

aux_source_directory(${ROOT_PATH}/src SRC_TEST)
aux_source_directory(${ROOT_PATH}/../../SDK/SDFast_SDK/SDFiles SRC_TEST)
aux_source_directory(${ROOT_PATH}/../../SDK/SDFast_SDK SRC_TEST)

add_executable(SDFastTest
    Test.cpp
    ${SRC_TEST}
)

target_link_libraries(SDFastTest

)

target_compile_definitions(SDFastTest PUBLIC
    NDEBUG
    _CNSOLE
    _UNICODE
    UNICODE
    _CRT_SECURE_NO_WARNINGS
)

target_compile_options(SDFastTest PUBLIC
    /nologo
)

# target_link_options(SDFastTest PUBLIC
#     /out:Test.exe
# )