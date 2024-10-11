cmake_minimum_required(VERSION 3.17)
project(sps)
set(CMAKE_CXX_STANDARD 17)
file(GLOB SRC
        "src/*.cpp"
        "main.cpp"
        "src/*.c"
        )
        
file(GLOB EXAMPLE "./example/*.cpp")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/inc")
include_directories(${INC_DIR})

foreach (file ${EXAMPLE})
    get_filename_component(exe_name ${file} NAME_WE)
    set(exename ${PROJECT_NAME}_${exe_name})
    add_executable(${exename} ${file} ${SRC}) 
endforeach()
add_library(${PROJECT_NAME} ${SRC})
#固定句式
#全局变量传递库名给主项目(其他三方库同样使用)
set(3RD_LIBS ${3RD_LIBS}  ${PROJECT_NAME} PARENT_SCOPE)
set(3RD_INC_DIRS ${3RD_INC_DIRS}  ${INC_DIR} PARENT_SCOPE)

