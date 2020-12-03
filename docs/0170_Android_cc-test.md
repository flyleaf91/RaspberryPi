# Android cc-test

分析如何利用Android的cc-test

## 参考文档

* [Android 测试开发工作流](https://source.android.com/compatibility/tests/development?hl=zh-cn)
* [0169_Android_RefBase_sp_wp.md](0169_Android_RefBase_sp_wp.md)

## 目标

* https://github.com/ZengjfOS/RaspberryPi/blob/Android_RefBase/Android.bp#L195
* 编译Android原生的测试用例cc-test

## 编译

### mmm编译

* source build/envsetup.sh
* lunch
  * 选择自己的target
* mmm system/core/libutils/
  * 输出文件：\<Android Build Target Out Path\>/testcases/libutils_test

### atest编译

* atest --build libutils_test
  ```
  
  ==================
  Notice:
    We collect anonymous usage statistics in accordance with our Content Licenses (https://source.android.com/setup/start/licenses), Contributor License Agreement (https://opensource.google.com/docs/cla/), Privacy Policy (https://policies.google.com/privacy) and Terms of Service (https://policies.google.com/terms).
  ==================
  
  
  Finding Tests...
  Found 'libutils_test' as MODULE
  
  Building Dependencies...
  out/target/product/M50/module-info.json, atest-tradefed, tradefed-core, MODULES-IN-system-core-libutils
  
  [100% 1023/1023] Copy xml: out/target/product/<your target device>/testcases/libutils_test/libutils_test.config
  2020-12-03 14:01:07 atest_utils.py:154:INFO: Build successful
  Execution detail has saved in /tmp/atest_run_1606975126__6YCaz/test_result
  ```
* \<Android Build Target Out Path\>/testcases/libutils_test

### 测试

* 手动push的方法
  * adb push \<Android Build Target Out Path\>/testcases/libutils_test/arm64/libutils_test /data/data/
  * adb shell /data/data/libutils_test
  * adb shell /data/data/libutils_test --help
  * adb shell /data/data/libutils_test --gtest_filter=RefBase*
* atest --test libutils_test
  * 如果是在服务器上编译的，有设备没有连接到服务器，无法用这种方式直接测试；
