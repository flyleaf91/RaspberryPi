# Kernel Complete

理解内核Complete同步机制

* [一、参考文档](#一参考文档)
* [二、示例代码](#二示例代码)
* [三、代码测试步骤](#三代码测试步骤)

## 一、参考文档

* [Linux内核同步机制之completion](https://blog.csdn.net/bullbat/article/details/7401688)

## 二、示例代码

https://github.com/ZengjfOS/RaspberryPi/tree/complete

## 三、代码测试步骤

* mknod /dev/complete c 255 0
* file /dev/complete
  ```
  /dev/complete: character special (255/0)
  ```
* 分别在两个shell中运行
  * cat /dev/complete
  * echo 0 > /dev/complete
* dmesg -w
  ```
  [14786.558343] process 6400 (cat) going to sleep
  [14794.944539] process 5460 (bash) awakening the readers...
  [14794.944579] awoken 6400 (cat)
  ```