# DebugHAT AT24C02


## 参考文档

* [0029_Linux_Kernel_Compile.md](0029_Linux_Kernel_Compile.md)
* [0045_SoC_Device_Tree.md](0045_SoC_Device_Tree.md)


## Kernel Compile Steps

* `arch/arm/boot/dts/overlays/rpi-at24c02-overlay.dts`
  ```dts
  // rpi-sense HAT
  /dts-v1/;
  /plugin/;
  
  / {
          compatible = "brcm,bcm2835";
  
          fragment@0 {
                  target = <&i2c1>;
                  __overlay__ {
                          #address-cells = <1>;
                          #size-cells = <0>;
                          status = "okay";
  
                          DebugHAT@50 {
                                  compatible = "atmel,24c02";
                                  reg = <0x50>;
                                  status = "okay";
                          };
                  };
          };
  };
  ```
* `KERNEL=kernel7l`
* `make bcm2711_defconfig`
* `make -j4 dtbs`
* `sudo cp arch/arm/boot/dts/overlays/rpi-at24c02.dtbo /boot/overlays/`
* `/boot/config.txt`
  ```
  [...省略]
  dtoverlay=rpi-at24c02
  ```
* `reboot`


## device tree

* before
  ```Console
  root@raspberrypi:/proc/device-tree/soc/i2c@7e804000# ls
  '#address-cells'   compatible   phandle         reg
   clock-frequency   interrupts   pinctrl-0      '#size-cells'
   clocks            name         pinctrl-names   status
  ```
* after
  ```Console
  root@raspberrypi:/proc/device-tree/soc/i2c@7e804000# ls
  '#address-cells'   compatible    name        pinctrl-names   status
   clock-frequency   DebugHAT@50   phandle     reg
   clocks            interrupts    pinctrl-0  '#size-cells'
  ```


## Kernel module

[模块驱动会自动加载，想知道原理，请查看](0046_USB_Camera_udev.md)

```Console
root@raspberrypi:/proc/device-tree/soc/i2c@7e804000# lsmod | grep at24
at24                   20480  0
```


## 以文件的形式访问EEPROM

```Console
root@raspberrypi:/sys/devices/platform/soc/fe804000.i2c/i2c-1/1-0050# xxd eeprom
00000000: 0eff ffff ffff ffff ffff ffff ffff ffff  ................
00000010: ffff ffff ffff ffff ffff ffff ffff ffff  ................
00000020: ffff ffff ffff ffff ffff ffff ffff ffff  ................
00000030: ffff ffff ffff ffff ffff ffff ffff ffff  ................
00000040: ffff ffff ffff ffff ffff ffff ffff ffff  ................
00000050: ffff ffff ffff ffff ffff ffff ffff ffff  ................
00000060: ffff ffff ffff ffff ffff ffff ffff ffff  ................
00000070: ffff ffff ffff ffff ffff ffff ffff ffff  ................
00000080: ffff ffff ffff ffff ffff ffff ffff ffff  ................
00000090: ffff ffff ffff ffff ffff ffff ffff ffff  ................
000000a0: ffff ffff ffff ffff ffff ffff ffff ffff  ................
000000b0: ffff ffff ffff ffff ffff ffff ffff ffff  ................
000000c0: ffff ffff ffff ffff ffff ffff ffff ffff  ................
000000d0: ffff ffff ffff ffff ffff ffff ffff ffff  ................
000000e0: ffff ffff ffff ffff ffff ffff ffff ffff  ................
000000f0: ffff ffff ffff ffff ffff ffff ffff ffff  ................
```

## Overlay Compile Directly

* `rpi-at24c64-overlay.dts`
  ```
  // rpi-sense HAT
  /dts-v1/;
  /plugin/;
  
  / {
          compatible = "brcm,bcm2835";
  
          fragment@0 {
                  target = <&i2c1>;
                  __overlay__ {
                          #address-cells = <1>;
                          #size-cells = <0>;
                          status = "okay";
  
                          DebugHAT@51 {
                                  compatible = "atmel,24c64";
                                  reg = <0x51>;
                                  status = "okay";
                          };
                  };
          };
  };
  ```
* `dtc -O dtb -o rpi-at24c64.dtbo rpi-at24c64-overlay.dts`
* `sudo cp rpi-at24c64.dtbo /boot/overlays/`
* `/boot/config.txt`
  ```
  [...省略]
  dtoverlay=rpi-at24c64
  ```
* `reboot`
