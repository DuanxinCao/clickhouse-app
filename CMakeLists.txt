cmake_minimum_required(VERSION 3.12)
project(application-example)

# Find java/jni
include(FindJava)
include(UseJava)
include(FindJNI)

#include_directories(/usr/lib/jvm/jdk1.8.0_381/include/linux)
#include_directories(/usr/lib/jvm/jdk1.8.0_381/include)
include_directories(/Library/Java/JavaVirtualMachines/jdk1.8.0_321.jdk/Contents/Home/include/)
include_directories(/Library/Java/JavaVirtualMachines/jdk1.8.0_321.jdk/Contents/Home/include/darwin)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(contribs/clickhouse-cpp)

#app
add_executable(${PROJECT_NAME} "app.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE contribs/clickhouse-cpp/ contribs/clickhouse-cpp/contrib/absl)

target_link_libraries(${PROJECT_NAME} PRIVATE clickhouse-cpp-lib)

#-------------------------------------------generate ldpsbackbend library (start)--------------------------------------
set(LDPS_BACKEND_LIBRARY_NAME ldpsbackend)

macro(add_glob cur_list)
    file(GLOB __tmp CONFIGURE_DEPENDS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${ARGN})
    list(APPEND ${cur_list} ${__tmp})
endmacro()

macro(add_headers_and_sources prefix common_path)
    add_glob(${prefix}_headers ${CMAKE_CURRENT_SOURCE_DIR} ${common_path}/*.h)
    add_glob(${prefix}_sources ${common_path}/*.cpp ${common_path}/*.c ${common_path}/*.h)

endmacro()
add_headers_and_sources(jni jni)

message("jni_sources : ${jni_sources}")
add_library(${LDPS_BACKEND_LIBRARY_NAME} SHARED
        ${jni_sources}
        core/Executor.cpp
        core/LocalBlock.cpp
        core/Noncopyable.h
        )

target_include_directories(${LDPS_BACKEND_LIBRARY_NAME} PRIVATE contribs/clickhouse-cpp/ contribs/clickhouse-cpp/contrib/absl core/)

target_link_libraries(${LDPS_BACKEND_LIBRARY_NAME} PRIVATE clickhouse-cpp-lib)
#-------------------------------------------generate ldpsbackbend library (end)----------------------------------------

add_executable(test "test.cpp")