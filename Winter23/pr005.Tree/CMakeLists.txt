cmake_minimum_required(VERSION 3.0.0)
project(Prac VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Test001
                        source/main001.cpp
                        source/Tree.cpp)
# target_compile_definitions(PracTestInsert PRIVATE TESTNAME="Test-1-Insert")

# add_executable(PracAnalytic
                        # source/SizeGen.cpp
                        # source/mainAnalytic.cpp)
# add_executable(makeReport
                        # source/mainReport.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
