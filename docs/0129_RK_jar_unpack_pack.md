# RK jar unpack pack

RK镜像及Jar打包、解包

## RK pack unpack

* cd linux/Linux_Pack_Firmware/rockdev
* rm Image
* cp ~/update.img .
* unpack.sh
* ln -s output Image
* cp output/package-file package-file
* modify package-file: 主要是修改路径
  ```
  # NAME          Relative path
  #
  #HWDEF          HWDEF
  
  package-file    package-file
  bootloader      Image/MiniLoaderAll.bin
  parameter       Image/parameter.txt
  boot        Image/Image/boot.img
  rootfs      Image/Image/rootfs.img
  backup      Image/Image/backup.img
  # backup                backupimage/backup.img
  
  # trust       Image/trust.img
  # uboot       Image/uboot.img
  # recovery      Image/recovery.img
  # oem                   Image/oem.img
  # userdata:grow    Image/userdata.img
  # misc          Image/misc.img
  # Ҫдbackupļupdate.img
  # SELF ؼupdate.img
  # ʱSELFݣͷϢ
  # ʱSELFݡ
  
  # update-script update-script
  # recover-script        recover-script
  ```
* mount output/Image/rootfs.img /mnt
* 修改内容
* umount /mnt
* rk3308-mkupdate.sh
  * 注意这里最终生成还是update.img，也就是覆盖之前的update.img

## Jar unpack pack

* 解压：`jar xvf project.jar`
* 采用压缩方式打包：`jar -cvfM project.jar ./`
* 不采用压缩方式打包：`jar -cvfM0 project.jar ./`
* ssh
  * root
  * @@af1123@@
