cmake_minimum_required(VERSION 3.6)
project(ImGuiExample)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(ENABLE_OPENGL3 ON)
set(ENABLE_OPENGL2 OFF)
set(ENABLE_VULKAN OFF)

set(ENABLE_IMGUI_STBLIB ON)
set(ENABLE_IMGUI_FREETYPE ON)

#查找包依赖
find_package(PkgConfig REQUIRED)
set(IMGUI_CORE_DEPENDS_LIBS)
#固定格式
#IMGUI核心文件编译
set(IMGUI_CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/core)
file(GLOB IMGUI_CORE_FILES
    ${IMGUI_CORE_DIR}/imgui/imgui.cpp
    ${IMGUI_CORE_DIR}/imgui/imgui_demo.cpp
    ${IMGUI_CORE_DIR}/imgui/imgui_draw.cpp
    ${IMGUI_CORE_DIR}/imgui/imgui_tables.cpp
    ${IMGUI_CORE_DIR}/imgui/imgui_widgets.cpp
)
set(IMGUI_CORE_INC_DIR 
    ${IMGUI_CORE_DIR}/imgui
    ${IMGUI_CORE_DIR}/imgui/backends
)
if(ENABLE_IMGUI_STBLIB)
    file(GLOB IMGUI_STDLIB_SRC ${IMGUI_CORE_DIR}/imgui/misc/cpp/*.cpp)
    set(IMGUI_STDLIB_INC_DIR ${IMGUI_CORE_DIR}/imgui/misc/cpp/)
    list(APPEND IMGUI_CORE_FILES ${IMGUI_STDLIB_SRC})
    list(APPEND IMGUI_CORE_INC_DIR ${IMGUI_STDLIB_INC_DIR})
endif()
if(ENABLE_IMGUI_FREETYPE)
    pkg_search_module(FREETYPE REQUIRED IMPORTED_TARGET freetype2)
    add_definitions(-DIMGUI_ENABLE_FREETYPE)    
    list(APPEND IMGUI_CORE_DEPENDS_LIBS PkgConfig::FREETYPE)
    file(GLOB IMGUI_FREETYPE_SRC ${IMGUI_CORE_DIR}/imgui/misc/freetype/*.cpp)
    set(IMGUI_FREETYPE_INC_DIR ${IMGUI_CORE_DIR}/imgui/misc/freetype/)
    list(APPEND IMGUI_CORE_FILES ${IMGUI_FREETYPE_SRC})
    list(APPEND IMGUI_CORE_INC_DIR ${IMGUI_FREETYPE_INC_DIR})
endif()
#生成IMGUI的lib动态库
add_library(imgui SHARED
  ${IMGUI_CORE_FILES}
)
target_include_directories(imgui PUBLIC
    ${IMGUI_CORE_INC_DIR}
)
target_link_libraries(imgui ${IMGUI_CORE_DEPENDS_LIBS})
set(IMGUI_BACKEND_DEPENDS_LIBS imgui)
#固定格式
if(ENABLE_OPENGL3)
    file(GLOB IMGUI_BACKEND_FILES
    ${IMGUI_CORE_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${IMGUI_CORE_DIR}/imgui/backends/imgui_impl_opengl3.cpp)
    # 使用 pkg-config 查找 glfw3  OpenGL glew
    pkg_search_module(OPENGL REQUIRED IMPORTED_TARGET opengl)
    pkg_search_module(GLFW3 REQUIRED IMPORTED_TARGET glfw3)
    pkg_search_module(GLEW REQUIRED IMPORTED_TARGET glew)
    list(APPEND  IMGUI_BACKEND_DEPENDS_LIBS PkgConfig::OPENGL PkgConfig::GLFW3  PkgConfig::GLEW)
endif()

#固定句式
# 获取第三方目录下的所有子项目
set(3RD_LIBS "") #设置全局变量
set(3RD_INC_DIRS "") #设置全局变量
file(GLOB 3RD_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/3rd/*")
foreach(3RD_DIR IN LISTS 3RD_DIRS)
    get_filename_component(3RD_NAME ${3RD_DIR} NAME)
    add_subdirectory(${3RD_DIR})
endforeach()


#固定格式
file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(MAIN_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)   
#生成可执行文件
add_executable(${CMAKE_PROJECT_NAME} ${SRC} ${IMGUI_BACKEND_FILES})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${IMGUI_CORE_INC_DIR}
    ${MAIN_INC_DIR}
    ${3RD_INC_DIRS}
)
target_link_libraries(${CMAKE_PROJECT_NAME}  ${IMGUI_BACKEND_DEPENDS_LIBS} ${3RD_LIBS})

