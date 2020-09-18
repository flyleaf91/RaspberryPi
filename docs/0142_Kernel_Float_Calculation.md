# Kernel Float Calculation

内核浮点运算

## 参考文档

* [Linux 内核使用浮点问题​](https://blog.csdn.net/pen_cil/article/details/105467817)

## 简要说明

关于内核使用浮点， Robert Love’s 《Linux Kernel Development》(Linux内核设计与实现)书中提到：

```
No (Easy) Use of Floating Point

When a user-space process uses floating-point instructions, the kernel manages the transition from integer to floating point mode. What the kernel has to do when using floating-point instructions varies by architecture, but the kernel normally catches a trap and then initiates the transition from integer to floating point mode.

Unlike user-space, the kernel does not have the luxury of seamless support for floating point because it cannot easily trap itself. Using a floating point inside the kernel requires manually saving and restoring the floating point registers, among other possible chores. The short answer is: Don’t do it! Except in the rare cases, no floating-point operations are in the kernel.
```

后面这句话提到如果内核使用浮点则需要保存恢复浮点寄存器等其他杂项，这样会导致内核性能下降，所以一般不建议使用浮点，除非特殊情况。

但是Robert Love's在这里并没有讨论如何在内核中正确使用浮点，以及未正确使用浮点可能会出现什么问题。**当你需要在内核中使用浮点，如果按照用户空间的写法可能会出现一些意想不到的情况。如：程序Crash，内存越界、访问非法内存地址，浮点计算出错等稀奇古怪的问题。出现这种问题的原因是：内核由于性能原因，在内核运行的代码，内核在进行上下文切换时，不会主动保存和恢复浮点寄存器。**这样可能会导致内核在进行浮点运算时，可能会破坏此时用户空间的浮点寄存器状态，导致用户空间的fpsimd_state状态异常，随后程序的行为将变的不可控。
