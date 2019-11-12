# DebugHAT Poweroff

这里的Poweroff不是是触发系统断电的按键功能，而是这个引脚默认低电平，如果系统关机，那么会给出高电平，告诉外围电路系统断电了。

## 参考文档

* [0029_Linux_Kernel_Compile.md](0029_Linux_Kernel_Compile.md)
* [0045_SoC_Device_Tree.md](0045_SoC_Device_Tree.md)
* [0006_Device_Tree_Overlays.md](0006_Device_Tree_Overlays.md)
* [0013_dtoverlay.md](0013_dtoverlay.md)


## 注意

* overlay文件中的`__overrides__`字段内容不会附加到系统`__overrides__`中去；
* `dtoverlay`加参数执行的命令，其参数只会覆盖overlay文件中的`__overrides__`；
* `dtparam`修改的是系统`__overrides__`；


## 测试方法

* `shutdown -P`；
* 采用`GPIO9`观察LED等状态；


## dts测试

* /boot/config.txt
  ```
  dtdebug=1
  ```
* sudo dtc -I fs -O dtb -o base.dtb /proc/device-tree 1>/dev/null 2>&1
* fdtdump base.dtb > base.dts
* 应用gpio-poweroff
  * sudo dtoverlay -v gpio-poweroff
    ```
    run_cmd: which dtoverlay-pre >/dev/null 2>&1 && dtoverlay-pre
    DTOVERLAY[debug]: delete_node(/__symbols__)
    DTOVERLAY[debug]: Wrote 1106 bytes to '/tmp/.dtoverlays/0_gpio-shutdown.dtbo'
    DTOVERLAY[debug]: Wrote 1106 bytes to '/sys/kernel/config/device-tree/overlays/0_gpio-shutdown/dtbo'
    run_cmd: which dtoverlay-post >/dev/null 2>&1 && dtoverlay-post
    ```
  * sudo dtoverlay -v gpio-poweroff gpiopin=26
    ```
    run_cmd: which dtoverlay-pre >/dev/null 2>&1 && dtoverlay-pre
    * dtoverlay_add: gpiopin 26
    DTOVERLAY[debug]: Found override gpiopin
    DTOVERLAY[debug]:   override gpiopin: cell target gpios @ offset 4 (size 4)
    DTOVERLAY[debug]:   override gpiopin: cell target brcm,pins @ offset 0 (size 4)
    DTOVERLAY[debug]: delete_node(/__symbols__)
    DTOVERLAY[debug]: Wrote 874 bytes to '/tmp/.dtoverlays/0_gpio-poweroff.dtbo'
    DTOVERLAY[debug]: Wrote 885 bytes to '/sys/kernel/config/device-tree/overlays/0_gpio-poweroff/dtbo'
    run_cmd: which dtoverlay-post >/dev/null 2>&1 && dtoverlay-post
    ```
* 如果需要删除刚刚应用的overlay：sudo rmdir /sys/kernel/config/device-tree/overlays/*
* /sys/kernel/debug/gpio
  ```
  gpiochip0: GPIOs 0-53, parent: platform/fe200000.gpio, pinctrl-bcm2835:
   gpio-26  (                    |power_ctrl          ) out lo
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


## gpio-poweroff-overlay.dts

* [GPIO number for CAM_GPIO0](https://www.raspberrypi.org/forums/viewtopic.php?t=222851)
* arm/boot/dts/overlays/gpio-shutdown-overlay.dts
* arm/boot/dts/overlays/gpio-poweroff-overlay.dts
  ```dts
  // Definitions for gpio-poweroff module
  /dts-v1/;
  /plugin/;
  
  / {
          compatible = "brcm,bcm2835";
  
          fragment@0 {
                  target-path = "/";
                  __overlay__ {
                          power_ctrl: power_ctrl {
                                  compatible = "gpio-poweroff";
                                  gpios = <&gpio 26 0>;
                                  force;
                          };
                  };
          };
  
          fragment@1 {
                  target = <&gpio>;
                  __overlay__ {
                          power_ctrl_pins: power_ctrl_pins {
                                  brcm,pins = <26>;
                                  brcm,function = <1>; // out
                          };
                  };
          };
  
          __overrides__ {
                  gpiopin =       <&power_ctrl>,"gpios:4",
                                  <&power_ctrl_pins>,"brcm,pins:0";
                  active_low =    <&power_ctrl>,"gpios:8";
                  input =         <&power_ctrl>,"input?";
                  export =        <&power_ctrl>,"export?";
          };
  };
  ```
* fdtdump /boot/overlays/gpio-poweroff.dtbo
  ```dts
  **** fdtdump is a low-level debugging tool, not meant for general use.
  **** If you want to decompile a dtb, you probably want
  ****     dtc -I dtb -O dts <filename>
  
  /dts-v1/;
  // magic:               0xd00dfeed
  // totalsize:           0x3e2 (994)
  // off_dt_struct:       0x38
  // off_dt_strings:      0x358
  // off_mem_rsvmap:      0x28
  // version:             17
  // last_comp_version:   16
  // boot_cpuid_phys:     0x0
  // size_dt_strings:     0x8a
  // size_dt_struct:      0x320
  
  / {
      compatible = "brcm,bcm2835";
      fragment@0 {
          target-path = "/";
          __overlay__ {
              power_ctrl {
                  compatible = "gpio-poweroff";
                  gpios = <0xffffffff 0x0000001a 0x00000000>;
                  force;
                  phandle = <0x00000001>;
              };
          };
      };
      fragment@1 {
          target = <0xffffffff>;
          __overlay__ {
              power_ctrl_pins {
                  brcm,pins = <0x0000001a>;
                  brcm,function = <0x00000001>;
                  phandle = <0x00000002>;
              };
          };
      };
      __overrides__ {
          gpiopin = <0x00000001 0x6770696f 0x733a3400 0x00000002 0x6272636d 0x2c70696e 0x733a3000>;
          active_low = <0x00000001 0x6770696f 0x733a3800>;
          input = [00 00 00 01 69 6e 70 75 74 3f 00];
          export = <0x00000001 0x6578706f 0x72743f00>;
      };
      __symbols__ {
          power_ctrl = "/fragment@0/__overlay__/power_ctrl";
          power_ctrl_pins = "/fragment@1/__overlay__/power_ctrl_pins";
      };
      __fixups__ {
          gpio = "/fragment@0/__overlay__/power_ctrl:gpios:0", "/fragment@1:target:0";
      };
      __local_fixups__ {
          __overrides__ {
              gpiopin = <0x00000000 0x0000000c>;
              active_low = <0x00000000>;
              input = <0x00000000>;
              export = <0x00000000>;
          };
      };
  };
  ```


## Driver

* drivers/power/reset/gpio-poweroff.c
  ```C
  [...省略]
  static void gpio_poweroff_do_poweroff(void)
  {
          BUG_ON(!reset_gpio);
  
          /* drive it active, also inactive->active edge */
          gpiod_direction_output(reset_gpio, 1);
          mdelay(100);
          /* drive inactive, also active->inactive edge */
          gpiod_set_value_cansleep(reset_gpio, 0);
          mdelay(100);
  
          /* drive it active, also inactive->active edge */
          gpiod_set_value_cansleep(reset_gpio, 1);
  
          /* give it some time */
          mdelay(timeout);
  
          WARN_ON(1);
  }
  [...省略]
  ```