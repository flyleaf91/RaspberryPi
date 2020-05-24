# alias

终端命令快捷方式

## 基本使用方法

```bash
export kernel=/home/pi/zengjf/linux-rpi-4.19.y
export dts=${kernel}/arch/arm/boot/dts

alias dts="cd ${dts}"
alias kernel="cd ${kernel}"
```