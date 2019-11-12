# DebugHAT led


## 参考文档

* [0029_Linux_Kernel_Compile.md](0029_Linux_Kernel_Compile.md)
* [0045_SoC_Device_Tree.md](0045_SoC_Device_Tree.md)
* [0006_Device_Tree_Overlays.md](0006_Device_Tree_Overlays.md)
* [0013_dtoverlay.md](0013_dtoverlay.md)
* [0058_DebugHAT_Poweroff.md](0058_DebugHAT_Poweroff.md)
* [Raspberry pi powerdown and powerup button](https://www.stderr.nl/Blog/Hardware/RaspberryPi/PowerButton.html)


## dts

* `arch/arm/boot/dts/overlays/DebugHAT-leds-overlay.dts`
  ```
  /*
   * Device Tree overlay for Witty Pi extension board by UUGear
   *
   */
  
  /dts-v1/;
  /plugin/;
  
  / {
  
          compatible = "brcm,bcm2835";
  
          fragment@0 {
                  target = <&leds>;
                  __overlay__ {
                          compatible = "gpio-leds";
                          DebugHAT_led: DebugHAT_led {
                                  label = "DebugHAT_led";
                                  linux,default-trigger = "default-on";
                                  gpios = <&gpio 10 0>;                 // 0：默认是灭的，1：默认是亮的
                          };
                  };
          };
  
          __overrides__ {
                  led_gpio =      <&DebugHAT_led>,"gpios:4";
          };
  
  };
  ```
* `KERNEL=kernel7l`
* `make bcm2711_defconfig`
* `make -j4 dtbs`
* `cp arch/arm/boot/dts/overlays/DebugHAT-leds.dtbo /boot/overlays/`
* `/boot/config.txt`
  ```
  [...省略]
  enable_uart=1
  dtoverlay=rpi-at24c02
  dtoverlay=gpio-poweroff,gpiopin=9,export=1
  dtoverlay=gpio-shutdown,gpio_pin=8
  dtoverlay=DebugHAT-leds,led_gpio=10
  dtdebug=1
  ```
* reboot


## 查看

* /sys/kernel/debug/gpio
  ```
  gpiochip0: GPIOs 0-53, parent: platform/fe200000.gpio, pinctrl-bcm2835:
   gpio-8   (                    |shutdown            ) in  hi IRQ
   gpio-9   (                    |power_ctrl          ) out lo
   gpio-10  (                    |DebugHAT_led        ) out hi
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
* ls /sys/class/leds/DebugHAT_led/
  ```
  brightness  device  max_brightness  power  subsystem  trigger  uevent
  ```


## 测试方法

* echo 0 > brightness
* echo 1 > brightness
* 触发闪烁
  * cat trigger  
    `[none] rc-feedback kbd-scrolllock kbd-numlock kbd-capslock kbd-kanalock kbd-shiftlock kbd-altgrlock kbd-ctrllock kbd-altlock kbd-shiftllock kbd-shiftrlock kbd-ctrlllock kbd-ctrlrlock timer oneshot heartbeat backlight gpio cpu cpu0 cpu1 cpu2 cpu3 default-on input panic mmc1 mmc0 rfkill-any rfkill-none rfkill0 rfkill1`
  * echo mmc0 > trigger


