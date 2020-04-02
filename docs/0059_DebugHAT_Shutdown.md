# DebugHAT Shutdown

Debug HAT Shutdown按钮

## 参考文档

* [0029_Linux_Kernel_Compile.md](0029_Linux_Kernel_Compile.md)
* [0045_SoC_Device_Tree.md](0045_SoC_Device_Tree.md)
* [0006_Device_Tree_Overlays.md](0006_Device_Tree_Overlays.md)
* [0013_dtoverlay.md](0013_dtoverlay.md)
* [0058_DebugHAT_Poweroff.md](0058_DebugHAT_Poweroff.md)
* [Raspberry pi powerdown and powerup button](https://www.stderr.nl/Blog/Hardware/RaspberryPi/PowerButton.html)


## 配置、查看

* /boot/config.txt
  ```
  [...省略]
  enable_uart=1
  dtoverlay=rpi-at24c02
  dtoverlay=gpio-poweroff,gpiopin=9,export=1
  dtoverlay=gpio-shutdown,gpio_pin=8
  dtdebug=1
  ```
* reboot
* /sys/kernel/debug/gpio
  ```
  gpiochip0: GPIOs 0-53, parent: platform/fe200000.gpio, pinctrl-bcm2835:
   gpio-8   (                    |shutdown            ) in  hi IRQ
   gpio-9   (                    |power_ctrl          ) out lo
   gpio-42  (                    |led0                ) out lo
  
  gpiochip2: GPIOs 100-101, brcmvirt-gpio, can sleep:
  
  gpiochip1: GPIOs 504-511, parent: platform/soc:firmware:gpio, raspberrypi-exp-gpio, can sleep:
   gpio-504 (BT_ON               )
   gpio-505 (WL_ON               )
   gpio-506 (PWR_LED_OFF         |led1                ) out lo
   gpio-507 (GLOBAL_RESET        )
   gpio-508 (VDD_SD_IO_SEL       |vdd-sd-io           ) out hi
   gpio-509 (CAM_GPIO            )
   gpio-510 (                    )
   gpio-511 (                    )
  ```


## 测试方法

按一下对应的按键，由高电平拉到低电平，系统会关机


## gpio-shutdown-overlay.dts

* arm/boot/dts/overlays/gpio-shutdown-overlay.dts
