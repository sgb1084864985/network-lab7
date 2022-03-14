#CMake最低版本号要求
cmake_minimum_required(VERSION 3.1)

#指定项目名称
project(lab7)

#指定版本信息
set(CMAKE_SYSTEM_VERSION 1)

#若是需要指定编译器路径
#set(CROSS_TOOLCHAIN_PREFIX "/path/arm-linux-")
#指定编译器
#set(CMAKE_C_COMPILER   "${CROSS_TOOLCHAIN_PREFIX}gcc")
#set(CMAKE_CXX_COMPILER "${CROSS_TOOLCHAIN_PREFIX}g++")

#使用默认路径的g++指定编译器  
set(CMAKE_CXX_COMPILER "g++") 

#指定编译选项
set(CMAKE_BUILD_TYPE Debug )

#指定编译目录
set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)


#添加子目录,这样进入源码文件src目录可以继续构建  
add_subdirectory(server)
add_executable(ServerMain ServerMain.cpp)
add_executable(ClientMain ClientMain.cpp)

target_link_libraries(ServerMain server)
target_include_directories(ServerMain PUBLIC 
    "${PROJECT_SOURCE_DIR}/server/include")

target_link_libraries(ClientMain server)
target_include_directories(ClientMain PUBLIC 
    "${PROJECT_SOURCE_DIR}/server/include")

