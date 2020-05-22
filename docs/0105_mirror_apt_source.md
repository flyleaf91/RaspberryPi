# mirror apt source

默认的源update有点慢

## 一、参考文k档

* [清华大学开源软件镜像站 Raspbian 镜像使用帮助](https://mirror.tuna.tsinghua.edu.cn/help/raspbian/)

## 二、处理步骤

`sudo cat /etc/apt/sources.list`
```
deb http://mirrors.tuna.tsinghua.edu.cn/raspbian/raspbian/ buster main non-free contrib rpi
deb-src http://mirrors.tuna.tsinghua.edu.cn/raspbian/raspbian/ buster main non-free contrib rpi

deb http://mirrors.tuna.tsinghua.edu.cn/raspberrypi/ buster main ui
```
