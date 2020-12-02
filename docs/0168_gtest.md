# gtest

尝试使用gtest，便于以后分析Android底层test case

## 参考文档

* [Getting started with Google Test (GTest) on Ubuntu](https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/)
* [使用 Google Test 测试框架](http://senlinzhan.github.io/2017/10/08/gtest/)

## install

sudo apt-get install libgtest-dev

## 示例编译运行

* https://github.com/ZengjfOS/RaspberryPi/tree/gtest
* cmake CMakeLists.txt
* make
* ./runTests

```shell
pi@raspberrypi:gtest $ cmake CMakeLists.txt
-- The C compiler identification is GNU 8.3.0
-- The CXX compiler identification is GNU 8.3.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found GTest: /usr/lib/arm-linux-gnueabihf/libgtest.a
-- Configuring done
-- Generating done
-- Build files have been written to: /home/pi/zengjf/Pointer/gtest
pi@raspberrypi:gtest $ make
Scanning dependencies of target runTests
[ 50%] Building CXX object CMakeFiles/runTests.dir/tests.cpp.o
[100%] Linking CXX executable runTests
[100%] Built target runTests
pi@raspberrypi:gtest $ ./runTests
[==========] Running 2 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 2 tests from SquareRootTest
[ RUN      ] SquareRootTest.PositiveNos
[       OK ] SquareRootTest.PositiveNos (0 ms)
[ RUN      ] SquareRootTest.NegativeNos
[       OK ] SquareRootTest.NegativeNos (0 ms)
[----------] 2 tests from SquareRootTest (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test case ran. (0 ms total)
[  PASSED  ] 2 tests.
```

## CMake

```Makefile
cmake_minimum_required(VERSION 2.6)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests tests.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
```

1. cmake版本
2. 依赖库
3. 程序名及依赖文件
4. 链接库

## gtest

[使用 Google Test 测试框架](http://senlinzhan.github.io/2017/10/08/gtest/)

测试用例格式：

```CPP
TEST(test_suite_name, test_case_name) 
{
    // test body ...
}
```

测试用例示例：

```CPP
TEST(MyTest, Add) 
{
    EXPECT_EQ(1 + 1, 2);
    ASSERT_EQ(1 + 1, 2);
}
```

那么这两种断言有什么区别呢：

* 如果ASSERT_\*执行失败了，会导致当前的测试函数立即返回。而EXPECT_\*如果执行失败了，并不会导致测试函数返回。
* gtest 提供了 8 个ASSERT_*断言，分别是ASSERT_TRUE()、ASSERT_FALSE()、ASSERT_EQ()、ASSERT_NE()、ASSERT_LT()、ASSERT_LE()、ASSERT_GT()和ASSERT_GE()。
* EXPECT_*的断言同样也有 8 个，分别是ASSERT_TRUE()、ASSERT_FALSE()、EXPECT_EQ()、EXPECT_NE()、EXPECT_LT()、EXPECT_LE()、EXPECT_GT()和EXPECT_GE()。


测试ASSERT_EQ出问题：

```diff
diff --git a/tests.cpp b/tests.cpp
index dcb4c72..9732d91 100644
--- a/tests.cpp
+++ b/tests.cpp
@@ -4,7 +4,7 @@
 TEST(SquareRootTest, PositiveNos) {
     ASSERT_EQ(6, squareRoot(36.0));
     ASSERT_EQ(18.0, squareRoot(324.0));
-    ASSERT_EQ(25.4, squareRoot(645.16));
+    ASSERT_EQ(25, squareRoot(645.16));
     ASSERT_EQ(0, squareRoot(0.0));
 }

```

测试ASSERT_EQ出问题log：

```shell
[==========] Running 2 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 2 tests from SquareRootTest
[ RUN      ] SquareRootTest.PositiveNos
/home/pi/zengjf/Pointer/gtest/tests.cpp:7: Failure
Expected equality of these values:
  25
  squareRoot(645.16)
    Which is: 25.4
[  FAILED  ] SquareRootTest.PositiveNos (0 ms)
[ RUN      ] SquareRootTest.NegativeNos
[       OK ] SquareRootTest.NegativeNos (0 ms)
[----------] 2 tests from SquareRootTest (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test case ran. (1 ms total)
[  PASSED  ] 1 test.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] SquareRootTest.PositiveNos

 1 FAILED TEST
```
