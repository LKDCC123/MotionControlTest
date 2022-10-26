cmake_minimum_required(VERSION 3.2)
project(MultiThreadTest)
set(ROOT_PATH .)

include_directories(
    ${ROOT_PATH}/include
)

link_directories(
    ${ROOT_PATH}/lib
)

aux_source_directory(${ROOT_PATH}/src SRC_MultiThread)

add_executable(MultiThreadTest ${ROOT_PATH}/test.cpp
    ${SRC_MultiThread}
)

target_link_libraries(MultiThreadTest 

)

target_compile_definitions(MultiThreadTest PUBLIC
    NDEBUG
    _CONSOLE
    _UNICODE
    UNICODE
    _CRT_SECURE_NO_WARNINGS_
)

target_compile_options(MultiThreadTest PUBLIC
    /nologo
)

target_link_options(MultiThreadTest PUBLIC
    /out:MultiThreadTest.exe
)
