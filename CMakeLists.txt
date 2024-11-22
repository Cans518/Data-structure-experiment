cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(MyPro_test VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含include目录
include_directories(${PROJECT_SOURCE_DIR}/include)

# 添加库目录下的源文件
file(GLOB LIB_SOURCES "${PROJECT_SOURCE_DIR}/lib/*.cpp")

# 添加可执行文件
add_executable(MyPro_test ${PROJECT_SOURCE_DIR}/src/main.cpp ${LIB_SOURCES})

# target_link_libraries(MyPro_test some_other_library)