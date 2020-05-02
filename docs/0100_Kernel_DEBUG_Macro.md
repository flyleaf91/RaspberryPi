# Kernel DEBUG Macro

内核模块DEBUG宏，和Android里面的NODEBUG宏一样

* [一、参考文档](#一参考文档)
* [二、使用方法](#二使用方法)

## 一、参考文档

* [Linux kernel debug技巧----开启DEBUG选项](http://www.wowotech.net/linux_application/kernel_debug_enable.html)

## 二、使用方法

* 其实开启DEBUG宏的方法很简单，在需要pr_debug/dev_dbg输出的模块开头，直接#define DEBUG即可；
  * init/main.c
    * #define DEBUG           /* Enable initcall_debug */
* make -j4 modules
* sudo make modules_install