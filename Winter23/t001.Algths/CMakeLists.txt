cmake_minimum_required(VERSION 3.0.0)
project(Algths VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Algths sources/02022023/002.001.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
