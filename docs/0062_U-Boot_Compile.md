# U-Boot Compile

虽说树莓派4B是64bit处理器，不过目前的系统镜像貌似是运行在32bit模式的，所以不要去编译64bit的U-Boot

## 参考文档

* [RPi U-Boot](https://elinux.org/RPi_U-Boot)


## steps

* export CROSS_COMPILE=arm-linux-gnueabihf-
* make rpi_4_32b_defconfig
* make -j4
  * u-boot.bin