cmake_minimum_required(VERSION 3.1)
project(fullfsm)

file(GLOB_RECURSE CORE_FILES ${CMAKE_SOURCE_DIR}/../statemachine/*.cpp)
file(GLOB_RECURSE USER_FILES ${CMAKE_SOURCE_DIR}/userstate/*.cpp)
file(GLOB_RECURSE MAIN_FILE ${CMAKE_SOURCE_DIR}/main.cpp)

# 创建主可执行文件
add_executable(${PROJECT_NAME} ${CORE_FILES} ${USER_FILES} ${MAIN_FILE})

# 包含头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/../statemachine
)

target_link_libraries(${PROJECT_NAME} -static-libstdc++ pthread)

