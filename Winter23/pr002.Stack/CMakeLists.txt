cmake_minimum_required(VERSION 3.0.0)
project(Prac VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(PracTest1Arr
                        source/mainTest1Arr.cpp
                        source/StackArr.cpp)
add_executable(PracTest1List
                        source/mainTest1List.cpp
                        source/StackList.cpp)
add_executable(PracTest2Arr
                        source/mainTest2Arr.cpp
                        source/StackArr.cpp)
add_executable(PracTest2List
                        source/mainTest2List.cpp
                        source/StackList.cpp)
add_executable(PracTest3Arr
                        source/mainTest3Arr.cpp
                        source/StackArr.cpp)
add_executable(PracTest3List
                        source/mainTest3List.cpp
                        source/StackList.cpp)
add_executable(PracAnalytic
                        source/mainAnalytic.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
