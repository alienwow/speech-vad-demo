cmake_minimum_required(VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE on)
project(FileCutUtil)
set(CMAKE_BUILD_TYPE RELEASE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")

#set(CMAKE_C_STANDARD 99)
file(GLOB SRC_FILES src/*.c src/*.h thirdparty/webrtc/common_audio/*/*.c thirdparty/webrtc/rtc_base/*.c*)
include_directories(thirdparty/webrtc)

#file(GLOB SRC_FILES src_test/*.h src_test/*.c)

#add_executable(FileCutUtil ${SRC_FILES})

add_library(FileCutUtil SHARED ${SRC_FILES})

target_link_libraries(FileCutUtil pthread)