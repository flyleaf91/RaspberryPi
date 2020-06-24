# Wifi rfkill off

默认Wifi打不开，rfkill关闭了，暂时不知道原因

## 参考文档

* [Turn WIFI on from the command line - Still off](https://www.raspberrypi.org/forums/viewtopic.php?t=206223)

## ifconfig

```bash
pi@raspberrypi:~ $ ifconfig wlan0 up
SIOCSIFFLAGS: Operation not permitted
pi@raspberrypi:~ $ sudo ifconfig wlan0 up
SIOCSIFFLAGS: Operation not possible due to RF-kill
```

## steps

* ifconfig
* sudo rfkill list all
  ```
  0: phy0: Wireless LAN
          Soft blocked: yes
          Hard blocked: no
  1: hci0: Bluetooth
          Soft blocked: no
          Hard blocked: no
  ```
* sudo rfkill unblock 0
* sudo rfkill list all
  ```
  0: phy0: Wireless LAN
          Soft blocked: no
          Hard blocked: no
  1: hci0: Bluetooth
          Soft blocked: no
          Hard blocked: no
  ```
* sudo reboot
* ifconfig
* 配置`/etc/wpa_supplicant/wpa_supplicant.conf`
