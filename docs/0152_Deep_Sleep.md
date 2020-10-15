# Deep Sleep

深睡眠机制，貌似树莓派上没使用

## 参考文档

* [Android电源管理基础知识整理](https://www.jianshu.com/p/cc553c9c75b0)

## Linux系统电源状态

ACPI | State	| Linux State	Description
-----|--------|----
S0	 | On(on)	               | Working
S1	 | Standby(standby)	     | CPU and RAM are powered but not executed
S2	 | ------	               | ------
S3	 | Suspend to RAM（mem)	 | CPU is Off,RAM is powered and the running content is saved to RAM
S4	 | Suspend to Disk(disk) | All content is saved to Disk and power down
S5	 | Shutdown	             | Shutdown the system


STR(Suspend to RAM): 挂起到内存，俗称待机、睡眠（Sleep），进入该状态，系统的主要工作如下：

1. 将系统当前的运行状态等数据保存在内存中，此时仍需要向RAM供电，以保证后续快速恢复至工作状态
2. 冻结用户态的进程和内核态的任务（进入内核态的进程或内核自己的task）
3. 关闭外围设备，如显示屏、鼠标等,中断唤醒外设不会关闭，如电源键
4. CPU停止工作

Standby也属于睡眠的一种方式，属于浅睡眠。该模式下CPU并未断电，依旧可以接收处理某些特定事件，视具体设备而定，恢复至正常工作状态的速度也比STR更快，但也更为耗电。举个例子来说，以该方式进入睡眠时，后续通过点击键盘也能将系统唤醒。而以mem进入的睡眠为深度睡眠，只能通过中断唤醒设备唤醒系统，如电源键(此时按电源键，不会经过正常的开机流程的BIOS、BOOTLOAD等)，此时按键盘是无法唤醒系统的。

STD(Suspend to Disk): 挂起到硬盘，俗称休眠（Hibernation）将系统当前的运行状态等数据保存到硬盘上，并自动关机。下次开机时便从硬盘上读取之前保存的数据，恢复到休眠关机之前的状态。
譬如在休眠关机时，桌面打开了一个应用，那么下一次开机启动时，该应用也处于打开状态。而正常的关机-开机流程，该应用是不会打开的。

在新版内核中，进程freeze的功能被单独抽离出来作为一个电源状态，该状态仅仅是冻结进程，并不会使系统进入低功耗状态（如切断CPU时钟源、关闭外设供电等）。相当于是Standby状态。

## Android电源模式

`cat /sys/power/state`

```
freeze mem
```

## 处理方式

* 禁止debug工具；
* 进入飞行模式；
* 断开USB连接线；
* 通过uart口看是否杀死其他CPU，无log输出，进入mtk_spm_suspend_process；
