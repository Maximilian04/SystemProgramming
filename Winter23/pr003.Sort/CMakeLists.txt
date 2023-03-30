cmake_minimum_required(VERSION 3.0.0)
project(Prac VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(PracTestInsert
                        source/mainTest.cpp
                        source/InsertSort.cpp)
target_compile_definitions(PracTestInsert PRIVATE TESTNAME="Test-1-Insert")
add_executable(PracTestBubble
                        source/mainTest.cpp
                        source/BubbleSort.cpp)
target_compile_definitions(PracTestBubble PRIVATE TESTNAME="Test-1-Bubble")
add_executable(PracAnalytic
                        source/SizeGen.cpp
                        source/mainAnalytic.cpp)
add_executable(makeReport
                        source/mainReport.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
