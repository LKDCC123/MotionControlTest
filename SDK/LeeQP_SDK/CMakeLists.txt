cmake_minimum_required(VERSION 3.0)
project(TEST)
set(ROOT_PATH .)

include_directories(
    "${ROOT_PATH}/include"
)

link_directories(
    "${ROOT_PATH}/lib"
)

aux_source_directory("${ROOT_PATH}/src" SRC)

add_executable(TEST
    test.cpp
    ${SRC}
)

target_link_libraries(TEST
    LEigenQP_CPP.lib
)

target_compile_definitions(TEST PUBLIC
    NDEBUG
    _CONSOLE
    _UNICODE
    UNICODE
    _CRT_SECURE_NO_WARNINGS
)

target_compile_options(TEST PUBLIC
    /nologo
)

