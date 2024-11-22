cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(MyPro_test VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含include目录
include_directories(${PROJECT_SOURCE_DIR}/include)

# 添加库目录下的源文件
# file(GLOB LIB_SOURCES "${PROJECT_SOURCE_DIR}/lib/*.cpp")

# 如果lib目录为空，设置LIB_SOURCES为空列表
if(NOT LIB_SOURCES)
    set(LIB_SOURCES "")
endif()

# 添加可执行文件
add_executable(MyPro_test ${PROJECT_SOURCE_DIR}/src/main.cpp ${LIB_SOURCES})

# 如果需要链接其他库，可以取消注释并修改以下行
# target_link_libraries(MyPro_test some_other_library)

# 打印信息以供调试
message(STATUS "Project Source Dir: ${PROJECT_SOURCE_DIR}")
message(STATUS "Library Sources: ${LIB_SOURCES}")
