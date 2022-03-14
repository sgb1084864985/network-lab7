#查找当前目录下的所有源文件，
#并将名称保存到DIR_LIB_SRCS目录
#aux_source_directory(. DIR_LIB_SRCS)

#指定头文件目录,PROJECT_SOURCE_DIR为工程的根目录  

set(server_src_path ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(server_include_path ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(server_lib_out_path ${CMAKE_CURRENT_SOURCE_DIR}/bin)

aux_source_directory(${server_src_path} SRC_LIST)
add_library(server ${SRC_LIST})
message(status "current src files" ${SRC_LIST})
message(status "include dir" ${server_include_path})

target_include_directories(server PUBLIC ${server_include_path})

#指定可执行文件的输出目录，输出到bin下面  
SET(CMAKE_C_FLAGS "-g -lws2_32")
# link_libraries(ws2_32)

target_link_libraries(server ws2_32)
set(LIBRARY_OUTPUT_DIRECTORY ${server_lib_out_path})
