# Kernel Notifier

理解内核通知

* [一、参考文档](#一参考文档)
* [二、示例代码](#二示例代码)
* [三、代码测试步骤](#三代码测试步骤)
* [四、应用场合](#四应用场合)

## 一、参考文档

* [Linux内核基础--事件通知链(notifier chain)](https://blog.csdn.net/Wuhzossibility/article/details/8079025)
* [[Linux] 内核通知链 notifier](https://www.cnblogs.com/lialong1st/p/11760272.html)

## 二、示例代码

https://github.com/ZengjfOS/RaspberryPi/tree/notifier

## 三、代码测试步骤

* make
* dmesg -w
  ```
  [ 4715.305329] I'm in event_notifier_chain_init
  [ 4725.937653] I'm in notifier_chain_init
  [ 4732.489789] I'm in send_event_chain_init
  [ 4732.489803] I got the chain event, message: no_use
  [ 4740.641708] Goodbye to send_event_chain_exit
  [ 4745.106724] Goodbye to notifier_chain_exit
  [ 4753.833647] Goodbye to event_notifier_chain_exit
  ```
* insmod chain.ko
* insmod notifier.ko
* insmod event.ko
* rmmod event.ko
* rmmod notifier.ko
* rmmod chain.ko

## 四、应用场合

最典型的通知链应用就是 LCD 和 TP 之间，TP 需要根据 LCD 的亮灭来控制是否打开关闭触摸功能。通俗的讲，LCD 会创建一个函数链表，TP 会将 suspend 和 resume 函数添加到链表中，当 LCD 发生亮灭变化时，会根据情况执行链表上所有对应的函数，函数会根据不同的动作执行 TP 的 suspend 和 resume 函数。
