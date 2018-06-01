cmake_minimum_required(VERSION 3.9)
execute_process(
        COMMAND git rev-parse --abbrev-ref HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the latest abbreviated commit hash of the working branch
execute_process(
        COMMAND git log -1 --format=%h
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
add_definitions("-DGIT_COMMIT_HASH=${GIT_COMMIT_HASH}")
add_definitions("-DGIT_BRANCH=${GIT_BRANCH}")
configure_file(
${CMAKE_SOURCE_DIR}/version.h.in
${CMAKE_BINARY_DIR}/utils/version.h
)
include_directories(${CMAKE_BINARY_DIR}/utils)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/version.h.in ${CMAKE_CURRENT_BINARY_DIR}/version.h @ONLY)
set(SOURCE_FILES main.cpp utils/ArgumentParser.cpp structures/Commands.h vm/VirtualMachine.cpp vm/VirtualMachine.h compiler/Compiler.cpp compiler/Compiler.h vm/Element.cpp vm/Element.h)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
add_executable(VM ${SOURCE_FILES})