VERSION(3.0)
project(MotConTest)
set(ROOT_PATH .)

include_directories(
    ${ROOT_PATH}\Code\Dynamix\include
    ${ROOT_PATH}\Code\Control\include
)
link_directories(
    ${ROOT_PATH}\Code\Dynamix\lib
    ${ROOT_PATH}\Code\Control\lib
)

aux_source_directory(
    ${ROOT_PATH}\Code\Dynamix\src SRC_Dynamix
    ${ROOT_PATH}\Code\Control\src SRC_Control
)

add_executable(MotConTest 
    ${SRC_Dynamix}
    ${SRC_Control}
)

target_link_libraries(MotConTest

)

target_compile_definitions(MotConTest

)

target_compile_options(MotConTest

)

target_link_options(MotConTest
    \OUT 

)

