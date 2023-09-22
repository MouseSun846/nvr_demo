cmake_minimum_required(VERSION 3.4.1)
#给项目命名
PROJECT(nvr_demo C CXX)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)
SET(CMAKE_BUILD_TYPE Debug)
message(status ${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_SKIP_BUILD_RPATH FALSE)
# set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
# set(CMAKE_INSTALL_RPATH $ORIGIN)


# -Wall：编译器将警告所有可能的问题，以便进行更好的代码检查。
# -std：编译器使用特定的C++标准，比如-std=c++11。
# -O2：编译器将使用优化等级为2，可以提高程序的执行效率。
# -fvisibility=hidden：编译器将隐藏程序的符号，从而提高程序的安全性。
# -fstack-protector-all：开启栈保护，从而可以有效地防范栈溢出攻击。
# -fsanitize=address：开启内存地址安全检查，从而可以有效地检测出内存泄漏问题。
# -Wno-unused：禁止未使用的变量
# -Wextra：对所有合法但值得怀疑的表达式发出警告
# -Wshadow：一旦某个局部变量屏蔽了另一个局部变量,编译器就发出警告.（此警告未包含在-Wall选项中，需单独开启）
# -W选项是CMake的警告选项，用于控制CMake在构建过程中输出的警告信息级别
# -g选项是告诉CMake在生成Makefile时加入支持调试信息的编译选项，例如在gcc下生成的Makefile中会包含-g选项。
# -ggdb选项则会生成调试符号信息，以供GDB调试器使用。

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fpermissive")
set(LWS_WITH_NETWORK ON)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib/HCNetSDKCom)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)

#需要编译的文件所需要的头文件路径
set(INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../include ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${INCLUDE_PATH})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SOURCES)

add_library(nvr_lib SHARED ${SOURCES})
target_link_libraries(nvr_lib 
        analyzedata
        AudioIntercom
        HCAlarm
        HCCoreDevCfg
        HCDisplay
        HCGeneralCfgMgr
        HCIndustry
        HCPlayBack
        HCPreview
        HCVoiceTalk
        iconv2
        StreamTransClient
        SystemTransform
        AudioRender
        crypto
        HCCore
        hcnetsdk
        hpr
        NPQos
        openal
        PlayCtrl
        ssl
        SuperRender
        z
)
# Add an executable
add_executable(nvr_demo ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

target_link_libraries(nvr_demo
        nvr_lib
        pthread
        m
        rt
        dl)