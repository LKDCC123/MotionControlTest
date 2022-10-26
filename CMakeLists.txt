VERSION(3.0)
project(MotConTest)
set(ROOT_PATH .)

include_directories(
    ${ROOT_PATH}\Code\Dynamix\include
    ${ROOT_PATH}\Code\Control\include
    ${ROOT_PATH}\Code\MultiThread\include
)
link_directories(
    ${ROOT_PATH}\Code\Dynamix\lib
    ${ROOT_PATH}\Code\Control\lib
    ${ROOT_PATH}\Code\MultiThread\lib
)

aux_source_directory(
    ${ROOT_PATH}\Code\Dynamix\src SRC_Dynamix
    ${ROOT_PATH}\Code\Control\src SRC_Control
    ${ROOT_PATH}\Code\MultiThread\src SRC_MultiThread
)

add_executable(MotConTest 
    ${SRC_Dynamix}
    ${SRC_Control}
    ${SRC_MultiThread}
)

target_link_libraries(MotConTest

)

target_compile_definitions(MotConTest
    NDEBUG
    _CONSOLE
    _UNICODE
    UNICODE
    _CRT_SECURE_NO_WARNINGS
)

target_compile_options(MotConTest
    \nologo
)

target_link_options(MotConTest
    \out: MotConTest.exe
)

