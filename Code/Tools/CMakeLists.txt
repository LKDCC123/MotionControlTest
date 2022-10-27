cmake_minimum_required(VERSION 3.0)
project(MultiThreadTest)
set(ROOT_PATH .)
set(RTX64_PATH ../../SDK/RTX64_SDK/3.2/)

include_directories(
    ${ROOT_PATH}/include
    ${RTX64_PATH}/include
)

link_directories(
    ${ROOT_PATH}/lib
    ${RTX64_PATH}/lib/amd64
)

aux_source_directory(${ROOT_PATH}/src SRC_ToolsTest)

add_executable(ToolsTest ${ROOT_PATH}/test.cpp
    ${SRC_ToolsTest}
)

target_link_libraries(ToolsTest 
    RtApi.lib
)

target_compile_definitions(ToolsTest PUBLIC
    NDEBUG
    _CONSOLE
    _UNICODE
    UNICODE
    _CRT_SECURE_NO_WARNINGS_
    # __USE_RTX
)

target_compile_options(ToolsTest PUBLIC
    /nologo
)

target_link_options(ToolsTest PUBLIC
    /out:ToolsTest.exe
)
