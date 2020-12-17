# USB gadget serial configfs

分析Android USB gadget串口配置

## 参考文档

* [android usb gadget分析](https://blog.csdn.net/viewsky11/article/details/54319249)
* [Android USB gadget configfs学习笔记总结](https://www.cnblogs.com/hellokitty2/p/10458143.html)
* https://www.kernel.org/doc/Documentation/usb/gadget_configfs.txt
* [mtk-usb代码分析之usb gadget](https://www.cnblogs.com/ant-man/p/9508328.html)

## configfs相关配置

### configfs

* mount | grep configfs
  ```
  none on /config type configfs (rw,nosuid,nodev,noexec,relatime)
  ```

### usb配置

* device/mediatek/\<soc chip\>/init.\<soc chip\>.usb.rc
  ```
  # ...省略
  
  on boot
      # ...省略
      setprop vendor.usb.acm_port0 0
      setprop vendor.usb.acm_port1 ""
      # ...省略
  
  # ...省略
  
  on property:sys.usb.ffs.ready=1 && property:sys.usb.config=adb && \
  property:vendor.usb.acm_enable=1 && property:sys.usb.configfs=1
      write /config/usb_gadget/g1/configs/b.1/strings/0x409/configuration "adb_acm"
      write /config/usb_gadget/g1/idProduct ${vendor.usb.pid}
      write /sys/devices/platform/mt_usb/saving 1
      symlink /config/usb_gadget/g1/functions/ffs.adb /config/usb_gadget/g1/configs/b.1/f1
      symlink /config/usb_gadget/g1/functions/acm.gs${vendor.usb.acm_port0} /config/usb_gadget/g1/configs/b.1/f2
      symlink /config/usb_gadget/g1/functions/acm.gs${vendor.usb.acm_port1} /config/usb_gadget/g1/configs/b.1/f3
      write /config/usb_gadget/g1/UDC ${vendor.usb.controller}
      setprop sys.usb.state ${sys.usb.config}

  # ...省略
  ```
* getprop | grep usb

### UDC

* getprop vendor.usb.controller
  ```
  musb-hdrc
  ```
* ls -al /sys/class/udc/musb-hdrc
  ```
  lrwxrwxrwx 1 root root 0 2000-01-07 09:06 /sys/class/udc/musb-hdrc -> ../../devices/platform/mt_usb/musb-hdrc/udc/musb-hdrc
  ```

### functions

* ls -1 /config/usb_gadget/g1/functions
  ```
  accessory.gs2
  acm.gs0
  acm.gs1
  acm.gs2
  acm.gs3
  audio_source.gs3
  ffs.adb
  hid.gs0
  mass_storage.usb0
  midi.gs5
  mtp.gs0
  ptp.gs1
  via_atc.gs0
  via_ets.gs0
  via_modem.gs0
  ```

### configs

* ls -1 /config/usb_gadget/g1/configs/b.1
  ```
  -rw-r--r-- 1 root root 4096 2000-01-07 07:21 MaxPower
  -rw-r--r-- 1 root root 4096 2000-01-07 08:42 bmAttributes
  lrwxrwxrwx 1 root root    0 2000-01-07 07:27 f1 -> ../../../../usb_gadget/g1/functions/ffs.adb
  lrwxrwxrwx 1 root root    0 2000-01-07 07:27 f2 -> ../../../../usb_gadget/g1/functions/acm.gs2
  drwxr-xr-x 3 root root    0 2000-01-07 07:21 strings
  ```

### functions与configs关系

* functions定义设备；
* configs通过软链接来绑定设备使设备生效；

```
symlink /config/usb_gadget/g1/functions/ffs.adb /config/usb_gadget/g1/configs/b.1/f1
symlink /config/usb_gadget/g1/functions/acm.gs${vendor.usb.acm_port0} /config/usb_gadget/g1/configs/b.1/f2
```

## Android相关配置

* 参考文档
  * [mtk-usb代码分析之usb gadget](https://www.cnblogs.com/ant-man/p/9508328.html)
* source
  * kernel-4.9/drivers/usb/gadget/android.c
* init.rc
  * system/core/rootdir/init.usb.rc
* sys节点
  * /sys/class/android_usb/android0

