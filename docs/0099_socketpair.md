# socketpair

socketpair用于创建一对无名的、相互连接的套接字，于进程间通信。

* [一、参考文档](#一参考文档)
* [二、简述](#二简述)
* [三、测试程序](#三测试程序)

## 一、参考文档

* [socketpair的用法和理解](https://blog.csdn.net/xifens/article/details/53714814)
* [Android通信之 BitTube](https://blog.csdn.net/lincolnjunior_lj/article/details/79369301)

## 二、简述

socketpair利用socket为双方建立了全双工的通信管道(communication pipe)。通过文件描述符的复用(dup/dup2)，可以传递socket handle到另一个进程，复用它并开启通信。

Android BitTube的实现很简洁，就是一对parcel-able模式的socket，用Linux/Unix中的术语来说叫socketpair。socketpair是Linux/Unix系统中用于进程间通信的一种机制，和pipe十分类似。

## 三、测试程序

https://github.com/ZengjfOS/RaspberryPi/tree/socketpair