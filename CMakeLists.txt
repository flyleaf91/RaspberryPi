cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(include)
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests RefBase.cpp RefBase_test.cpp StrongPointer.cpp tests.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
