# USB_Camera_udev

* [uvc](https://github.com/ZengjfOS/V4L2/blob/master/docs/0001_uvc/README.md)

## 参考文档

* [devfs udev](https://github.com/ZengjfOS/LinuxSystem/blob/master/docs/0005_devfs_udev.md)
* [[基礎] Raspberry Pi 用 3G 網卡(3G USB dongle)上網](https://www.raspberrypi.com.tw/tag/udev/)
* [udev (简体中文)](https://wiki.archlinux.org/index.php/Udev_(%E7%AE%80%E4%BD%93%E4%B8%AD%E6%96%87))
* [5分钟理解udev](https://blog.csdn.net/woyimibayi/article/details/78320915)
* [Is there any documentation for udev builtins?](https://unix.stackexchange.com/questions/493771/is-there-any-documentation-for-udev-builtins)

## make menuconfig

```
 .config - Linux/arm64 4.19.71 Kernel Configuration
 > Device Drivers > Multimedia support > Media USB Adapters
  ┌─ Media USB Adapters ─┐
  │  Arrow keys navigate the menu.  <Enter> selects submenus ---> (or empty     │
  │  submenus ----).  Highlighted letters are hotkeys.  Pressing <Y> includes,  │
  │  <N> excludes, <M> modularizes features.  Press <Esc><Esc> to exit, <?> for │
  │  Help, </> for Search.  Legend: [*] built-in  [ ] excluded  <M> module  < > │
  │ ┌─┐ │
  │ │    --- Media USB Adapters                                               │ │
  │ │          *** Webcam devices ***                                         │ │
  │ │    <M>   USB Video Class (UVC)                                          │ │
  │ │    [*]     UVC input events device support                              │ │
  │ │    <M>   GSPCA based webcams  --->                                      │ │
  │ │    <M>   USB Philips Cameras                                            │ │
  │ │    [ ]     USB Philips Cameras verbose debug                            │ │
  │ │    [*]     USB Philips Cameras input events device support              │ │
  │ │    <M>   CPiA2 Video For Linux                                          │ │
  │ └─┘ │v(+)
  ├─┤
  │          <Select>    < Exit >    < Help >    < Save >    < Load >           │
  └─┘
```

## uvc module path

`drivers/media/usb/uvc/uvcvideo.ko`

## udev rules简介

* `udev`的主配置文件是`/etc/udev/udev.conf`，`udev`的主配置文件是`/etc/udev/udev.conf`。
* `udev`的规则文件一般位于`/lib/udev/rules.d/`，也可以位于`/etc/udev/rules.d/`。
* `udev`规则以管理员身份编写并保存在`/etc/udev/rules.d/`目录，其文件名必须以`.rules`结尾。各种软件包提供的规则文件位于`/lib/udev/rules.d/`。如果`/usr/lib`和`/etc`这两个目录中有同名文件，则`/etc`中的文件优先。
* 规则文件是按照字母顺序处理的，不管放在哪个目录。对于相同名字的规则文件，`/etc/udev/rules.d`比`/lib/udev/rules.d`优先。
* 规则文件必须以`.rules`作为扩展名，否则不被当作规则文件。

## udev debug:

* command line open debug info:
  * `udevadm control --log-priority=debug`
  * `udevadm control --reload-rules`
* config open debug info:
  * `/etc/udev/udev.conf`
    ```
    # see udev.conf(5) for details
    #
    # udevd is also started in the initrd.  When this file is modified you might
    # also want to rebuild the initrd, so that it will include the modified configuration.
    
    #udev_log=info
    udev_log=debug
    #children_max=
    #exec_delay=
    #event_timeout=180
    #resolve_names=early
    ```

## uvc module auto insmod

* check uvc module
  ```Console
  pi@raspberrypi:~ $ sudo su
  root@raspberrypi:/home/pi# lsmod | grep uvc
  root@raspberrypi:/home/pi# dmesg | tail
  [   24.922487] IPv6: ADDRCONF(NETDEV_UP): usb0: link is not ready
  [   25.991948] bcmgenet fd580000.genet eth0: Link is Down
  [   30.140766] IPv6: ADDRCONF(NETDEV_CHANGE): wlan0: link becomes ready
  [   32.519454] Bluetooth: BNEP (Ethernet Emulation) ver 1.3
  [   32.519460] Bluetooth: BNEP filters: protocol multicast
  [   32.519469] Bluetooth: BNEP socket layer initialized
  [   37.229178] bridge: filtering via arp/ip/ip6tables is no longer available by default. Update your scripts to load br_netfilter if you need this.
  [   37.236134] Bridge firewalling registered
  [   38.425937] IPv6: ADDRCONF(NETDEV_UP): docker0: link is not ready
  [   72.018468] fuse init (API version 7.27)
  root@raspberrypi:/home/pi# dmesg | tail -n 30
  [   10.317755] brcmfmac: power management disabled
  [   24.704024] Bluetooth: HCI UART driver ver 2.3
  [   24.704040] Bluetooth: HCI UART protocol H4 registered
  [   24.704122] Bluetooth: HCI UART protocol Three-wire (H5) registered
  [   24.704365] Bluetooth: HCI UART protocol Broadcom registered
  [   24.826516] bcmgenet: Skipping UMAC reset
  [   24.922027] bcmgenet fd580000.genet: configuring instance for external RGMII (no delay)
  [   24.922271] IPv6: ADDRCONF(NETDEV_UP): eth0: link is not ready
  [   24.922487] IPv6: ADDRCONF(NETDEV_UP): usb0: link is not ready
  [   25.991948] bcmgenet fd580000.genet eth0: Link is Down
  [   30.140766] IPv6: ADDRCONF(NETDEV_CHANGE): wlan0: link becomes ready
  [   32.519454] Bluetooth: BNEP (Ethernet Emulation) ver 1.3
  [   32.519460] Bluetooth: BNEP filters: protocol multicast
  [   32.519469] Bluetooth: BNEP socket layer initialized
  [   37.229178] bridge: filtering via arp/ip/ip6tables is no longer available by default. Update your scripts to load br_netfilter if you need this.
  [   37.236134] Bridge firewalling registered
  [   38.425937] IPv6: ADDRCONF(NETDEV_UP): docker0: link is not ready
  [   72.018468] fuse init (API version 7.27)
  [  177.289210] usb 1-1.4: new high-speed USB device number 3 using xhci_hcd
  [  177.513488] usb 1-1.4: New USB device found, idVendor=057e, idProduct=030a, bcdDevice= 9.24
  [  177.513505] usb 1-1.4: New USB device strings: Mfr=48, Product=96, SerialNumber=0
  [  177.513517] usb 1-1.4: Product: USB Camera
  [  177.513529] usb 1-1.4: Manufacturer: Guillemot Corporation
  [  177.619851] uvcvideo: Found UVC 1.00 device USB Camera (057e:030a)
  [  177.640566] uvcvideo 1-1.4:1.0: Entity type for entity Extension 4 was not initialized!
  [  177.640583] uvcvideo 1-1.4:1.0: Entity type for entity Processing 3 was not initialized!
  [  177.640597] uvcvideo 1-1.4:1.0: Entity type for entity Camera 1 was not initialized!
  [  177.640964] input: USB Camera: USB Camera as /devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0/input/input1
  [  177.641332] usbcore: registered new interface driver uvcvideo
  [  177.641342] USB Video Class driver (1.1.1)
  root@raspberrypi:/home/pi# lsmod | grep uvc
  uvcvideo               98304  0
  videobuf2_vmalloc      16384  2 uvcvideo,bcm2835_v4l2
  videobuf2_v4l2         24576  4 uvcvideo,bcm2835_codec,bcm2835_v4l2,v4l2_mem2mem
  videobuf2_common       45056  5 uvcvideo,bcm2835_codec,bcm2835_v4l2,v4l2_mem2mem,videobuf2_v4l2
  videodev              200704  7 uvcvideo,bcm2835_codec,v4l2_common,videobuf2_common,bcm2835_v4l2,v4l2_mem2mem,videobuf2_v4l2
  media                  36864  4 uvcvideo,bcm2835_codec,videodev,v4l2_mem2mem
  ```
* `/var/log/debug`
  ```
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: 1-1.4: Device (SEQNUM=1572, ACTION=add) is queued
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Validate module index
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Check if link configuration needs reloading.
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: === trie on-disk ===
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: tool version:          241
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: file size:         9875592 bytes
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: header size             80 bytes
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: strings            2072032 bytes
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: nodes              7803480 bytes
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Load module index
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: timestamp of '/etc/systemd/network' changed
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Skipping overridden file '/lib/systemd/network/99-default.link'.
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Skipping empty file: /etc/systemd/network/99-default.link
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Created link configuration context.
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: timestamp of '/etc/udev/rules.d' changed
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: timestamp of '/lib/udev/rules.d' changed
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/10-local-rpi.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/15-i2c-modprobe.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/40-scratch.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/40-usb_modeswitch.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/50-firmware.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/50-udev-default.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/55-dm.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/60-avrdude.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/60-block.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/60-bluealsa.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/60-cdrom_id.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/60-crda.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/60-drm.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/60-evdev.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/60-i2c-tools.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/60-input-id.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/60-libgphoto2-6.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/60-persistent-alsa.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/60-persistent-input.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/60-persistent-storage-dm.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/60-persistent-storage-tape.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/60-persistent-storage.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/60-persistent-v4l.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/60-rpi.gpio-common.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/60-sensor.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/60-serial.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/60-triggerhappy.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/64-btrfs.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/64-xorg-xkb.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/65-libwacom.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/69-libmtp.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/70-joystick.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/70-mouse.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/70-power-switch.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/70-touchpad.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/70-uaccess.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/71-seat.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/73-seat-late.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/73-special-net-names.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/73-usb-net-by-mac.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/75-net-description.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/75-probe_mtd.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/77-mm-cinterion-port-types.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/77-mm-dell-port-types.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/77-mm-ericsson-mbm.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/77-mm-fibocom-port-types.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/77-mm-haier-port-types.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/77-mm-huawei-net-port-types.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/77-mm-longcheer-port-types.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/77-mm-mtk-port-types.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/77-mm-nokia-port-types.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/77-mm-pcmcia-device-blacklist.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/77-mm-qdl-device-blacklist.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/77-mm-sierra.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/77-mm-simtech-port-types.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/77-mm-telit-port-types.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/77-mm-ublox-port-types.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/77-mm-usb-device-blacklist.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/77-mm-usb-serial-adapters-greylist.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/77-mm-x22x-port-types.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/77-mm-zte-port-types.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/78-sound-card.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/80-debian-compat.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/80-drivers.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/80-ifupdown.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/80-iio-sensor-proxy.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/80-libinput-device-groups.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/80-mm-candidate.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/80-net-setup-link.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/80-noobs.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/80-udisks2.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/85-hwclock.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/85-regulatory.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/89-alsa-ucm.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/90-alsa-restore.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/90-console-setup.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/90-libinput-model-quirks.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/90-mu-editor.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/90-pi-bluetooth.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/90-pulseaudio.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/95-dm-notify.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/97-hid2hci.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /etc/udev/rules.d/99-com.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Reading rules file: /lib/udev/rules.d/99-systemd.rules
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Rules contain 393216 bytes tokens (32768 * 12 bytes), 31786 bytes strings
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: 25074 strings (205180 bytes), 22053 de-duplicated (176416 bytes), 3022 trie nodes used
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Successfully forked off 'n/a' as PID 2531.
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: 1-1.4: Worker [2531] is forked for processing SEQNUM=1572.
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: 1-1.4:1.0: Device (SEQNUM=1573, ACTION=add) is queued
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: 1-1.4:1.1: Device (SEQNUM=1574, ACTION=add) is queued
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4: Processing device (SEQNUM=1572, ACTION=add)
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: 1-1.4: Device (SEQNUM=1575, ACTION=bind) is queued
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4: IMPORT builtin 'usb_id' /lib/udev/rules.d/50-udev-default.rules:13
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4: IMPORT builtin 'hwdb' /lib/udev/rules.d/50-udev-default.rules:13
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4: MODE 0664 /lib/udev/rules.d/50-udev-default.rules:45
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4: PROGRAM 'mtp-probe /sys/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4 1 3' /lib/udev/rules.d/69-libmtp.rules:2541
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: Starting 'mtp-probe /sys/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4 1 3'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: Successfully forked off '(spawn)' as PID 2532.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 'mtp-probe /sys/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4 1 3'(out) '0'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: Process 'mtp-probe /sys/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4 1 3' succeeded.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4: Handling device node '/dev/bus/usb/001/003', devnum=c189:2, mode=0664, uid=0, gid=0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4: Setting permissions /dev/bus/usb/001/003, 020664, uid=0, gid=0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4: Creating symlink '/dev/char/189:2' to '../bus/usb/001/003'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4: sd-device: Created db file '/run/udev/data/c189:2' for '/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4: Device (SEQNUM=1572, ACTION=add) processed
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4: sd-device-monitor: Passed 632 byte to netlink monitor
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: 1-1.4:1.0: sd-device-monitor: Passed 341 byte to netlink monitor
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.0: Processing device (SEQNUM=1573, ACTION=add)
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Successfully forked off 'n/a' as PID 2533.
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: 1-1.4:1.1: Worker [2533] is forked for processing SEQNUM=1574.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.0: IMPORT builtin 'hwdb' /lib/udev/rules.d/50-udev-default.rules:14
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: 1-1.4:1.1: Processing device (SEQNUM=1574, ACTION=add)
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.0: IMPORT builtin 'usb_id' /lib/udev/rules.d/60-libgphoto2-6.rules:9
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: 1-1.4:1.1: IMPORT builtin 'hwdb' /lib/udev/rules.d/50-udev-default.rules:14
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.0: Failed to access usb_interface: No such file or directory
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.0: IMPORT builtin 'usb_id' fails: No such file or directory
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.0: RUN 'kmod load $env{MODALIAS}' /lib/udev/rules.d/80-drivers.rules:5
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.0: sd-device: Created db file '/run/udev/data/+usb:1-1.4:1.0' for '/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: Loading module: usb:v057Ep030Ad0924dcEFdsc02dp01ic0Eisc01ip00in00
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: 1-1.4:1.1: IMPORT builtin 'usb_id' /lib/udev/rules.d/60-libgphoto2-6.rules:9
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: 1-1.4:1.1: Failed to access usb_interface: No such file or directory
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: 1-1.4:1.1: IMPORT builtin 'usb_id' fails: No such file or directory
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: 1-1.4:1.1: RUN 'kmod load $env{MODALIAS}' /lib/udev/rules.d/80-drivers.rules:5
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: 1-1.4:1.1: sd-device: Created db file '/run/udev/data/+usb:1-1.4:1.1' for '/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.1'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: Loading module: usb:v057Ep030Ad0924dcEFdsc02dp01ic0Eisc02ip00in01
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: Failed to find module 'usb:v057Ep030Ad0924dcEFdsc02dp01ic0Eisc02ip00in01'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: 1-1.4:1.1: Device (SEQNUM=1574, ACTION=add) processed
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: 1-1.4:1.1: sd-device-monitor: Passed 483 byte to netlink monitor
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: uvcvideo: Device (SEQNUM=1576, ACTION=add) is queued
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: uvcvideo: sd-device-monitor: Passed 132 byte to netlink monitor
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: uvcvideo: Processing device (SEQNUM=1576, ACTION=add)
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: uvcvideo: Device (SEQNUM=1576, ACTION=add) processed
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: uvcvideo: sd-device-monitor: Passed 132 byte to netlink monitor
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: 1-1.4:1.1: Device (SEQNUM=1577, ACTION=bind) is queued
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: video0: Device (SEQNUM=1578, ACTION=add) is queued
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: video1: Device (SEQNUM=1579, ACTION=add) is queued
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: Inserted module 'uvcvideo'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.0: Device (SEQNUM=1573, ACTION=add) processed
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: media1: Device (SEQNUM=1580, ACTION=add) is queued
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.0: sd-device-monitor: Passed 483 byte to netlink monitor
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: input1: Device (SEQNUM=1581, ACTION=add) is queued
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: 1-1.4: sd-device-monitor: Passed 333 byte to netlink monitor
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4: Processing device (SEQNUM=1575, ACTION=bind)
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: event1: Device (SEQNUM=1582, ACTION=add) is queued
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: 1-1.4:1.0: Device (SEQNUM=1583, ACTION=bind) is queued
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: uvcvideo: Device (SEQNUM=1584, ACTION=add) is queued
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: uvcvideo: sd-device-monitor: Passed 142 byte to netlink monitor
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4: IMPORT builtin 'usb_id' /lib/udev/rules.d/50-udev-default.rules:13
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: uvcvideo: Processing device (SEQNUM=1584, ACTION=add)
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4: IMPORT builtin 'hwdb' /lib/udev/rules.d/50-udev-default.rules:13
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: uvcvideo: Device (SEQNUM=1584, ACTION=add) processed
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: uvcvideo: sd-device-monitor: Passed 142 byte to netlink monitor
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4: PROGRAM 'mtp-probe /sys/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4 1 3' /lib/udev/rules.d/69-libmtp.rules:2541
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: Starting 'mtp-probe /sys/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4 1 3'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: Successfully forked off '(spawn)' as PID 2534.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 'mtp-probe /sys/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4 1 3'(out) '0'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: Process 'mtp-probe /sys/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4 1 3' succeeded.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4: Handling device node '/dev/bus/usb/001/003', devnum=c189:2, mode=0600, uid=0, gid=0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4: Preserve already existing symlink '/dev/char/189:2' to '../bus/usb/001/003'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4: sd-device: Created db file '/run/udev/data/c189:2' for '/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4: Device (SEQNUM=1575, ACTION=bind) processed
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4: sd-device-monitor: Passed 633 byte to netlink monitor
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: 1-1.4:1.1: sd-device-monitor: Passed 358 byte to netlink monitor
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: video0: sd-device-monitor: Passed 274 byte to netlink monitor
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: Processing device (SEQNUM=1578, ACTION=add)
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Successfully forked off 'n/a' as PID 2535.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.1: Processing device (SEQNUM=1577, ACTION=bind)
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: video1: Worker [2535] is forked for processing SEQNUM=1579.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.1: IMPORT builtin 'hwdb' /lib/udev/rules.d/50-udev-default.rules:14
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.1: IMPORT builtin 'usb_id' /lib/udev/rules.d/60-libgphoto2-6.rules:9
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Successfully forked off 'n/a' as PID 2536.
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: media1: Worker [2536] is forked for processing SEQNUM=1580.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: Processing device (SEQNUM=1579, ACTION=add)
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: Successfully forked off 'n/a' as PID 2537.
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: input1: Worker [2537] is forked for processing SEQNUM=1581.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: GROUP 44 /lib/udev/rules.d/50-udev-default.rules:32
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: IMPORT 'v4l_id /dev/video0' /lib/udev/rules.d/60-persistent-v4l.rules:7
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.1: Failed to access usb_interface: No such file or directory
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.1: IMPORT builtin 'usb_id' fails: No such file or directory
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: Starting 'v4l_id /dev/video0'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: Successfully forked off '(spawn)' as PID 2538.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: Processing device (SEQNUM=1581, ACTION=add)
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: IMPORT builtin 'hwdb' /lib/udev/rules.d/50-udev-default.rules:14
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: GROUP 44 /lib/udev/rules.d/50-udev-default.rules:32
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: IMPORT 'v4l_id /dev/video1' /lib/udev/rules.d/60-persistent-v4l.rules:7
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: Starting 'v4l_id /dev/video1'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.1: sd-device: Created db file '/run/udev/data/+usb:1-1.4:1.1' for '/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.1'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.1: Device (SEQNUM=1577, ACTION=bind) processed
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.1: sd-device-monitor: Passed 500 byte to netlink monitor
  Oct 24 10:32:17 raspberrypi systemd-udevd[2536]: media1: Processing device (SEQNUM=1580, ACTION=add)
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: No entry found from hwdb.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: IMPORT builtin 'hwdb' fails: No data available
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: IMPORT builtin 'input_id' /lib/udev/rules.d/60-input-id.rules:5
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: capabilities/ev raw kernel attribute: 3
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: capabilities/abs raw kernel attribute: 0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: capabilities/rel raw kernel attribute: 0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: capabilities/key raw kernel attribute: 100000 0 0 0 0 0 0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: properties raw kernel attribute: 0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: test_key: checking bit block 0 for any keys; found=0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: test_key: checking bit block 32 for any keys; found=0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: test_key: checking bit block 64 for any keys; found=0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: test_key: checking bit block 96 for any keys; found=0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: test_key: checking bit block 128 for any keys; found=0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: test_key: checking bit block 160 for any keys; found=0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: test_key: checking bit block 192 for any keys; found=1
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: test_key: checking bit block 224 for any keys; found=1
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: IMPORT builtin 'hwdb' /lib/udev/rules.d/60-input-id.rules:6
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: No entry found from hwdb.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: IMPORT builtin 'hwdb' fails: No data available
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: IMPORT builtin 'usb_id' /lib/udev/rules.d/60-persistent-input.rules:11
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: 1-1.4:1.0: if_class:14 protocol:0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: Successfully forked off '(spawn)' as PID 2539.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2536]: media1: GROUP 44 /lib/udev/rules.d/50-udev-default.rules:36
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: IMPORT builtin 'path_id' /lib/udev/rules.d/60-persistent-input.rules:35
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: RUN '/usr/sbin/th-cmd --socket /var/run/thd.socket --passfd --udev' /lib/udev/rules.d/60-triggerhappy.rules:4
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: RUN 'kmod load $env{MODALIAS}' /lib/udev/rules.d/80-drivers.rules:5
  Oct 24 10:32:17 raspberrypi systemd-udevd[2536]: media1: Handling device node '/dev/media1', devnum=c237:1, mode=0660, uid=0, gid=44
  Oct 24 10:32:17 raspberrypi systemd-udevd[2536]: media1: Setting permissions /dev/media1, 020660, uid=0, gid=44
  Oct 24 10:32:17 raspberrypi systemd-udevd[2536]: media1: Creating symlink '/dev/char/237:1' to '../media1'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2536]: media1: sd-device: Created empty file '/run/udev/data/c237:1' for '/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0/media1'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2536]: media1: Device (SEQNUM=1580, ACTION=add) processed
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: sd-device: Created db file '/run/udev/data/+input:input1' for '/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0/input/input1'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2536]: media1: sd-device-monitor: Passed 257 byte to netlink monitor
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: Starting '/usr/sbin/th-cmd --socket /var/run/thd.socket --passfd --udev'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: 'v4l_id /dev/video0'(out) 'ID_V4L_VERSION=2'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: 'v4l_id /dev/video0'(out) 'ID_V4L_PRODUCT=USB Camera: USB Camera'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: 'v4l_id /dev/video0'(out) 'ID_V4L_CAPABILITIES=:capture:'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: Successfully forked off '(spawn)' as PID 2540.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: Process 'v4l_id /dev/video0' succeeded.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: IMPORT builtin 'usb_id' /lib/udev/rules.d/60-persistent-v4l.rules:9
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: 1-1.4:1.0: if_class:14 protocol:0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: LINK 'v4l/by-id/usb-Guillemot_Corporation_USB_Camera-video-index0' /lib/udev/rules.d/60-persistent-v4l.rules:10
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: IMPORT builtin 'path_id' /lib/udev/rules.d/60-persistent-v4l.rules:16
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: LINK 'v4l/by-path/platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.4:1.0-video-index0' /lib/udev/rules.d/60-persistent-v4l.rules:17
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: RUN 'uaccess' /lib/udev/rules.d/73-seat-late.rules:17
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: Handling device node '/dev/video0', devnum=c81:3, mode=0660, uid=0, gid=44
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: Setting permissions /dev/video0, 020660, uid=0, gid=44
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: Creating symlink '/dev/char/81:3' to '../video0'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: Creating symlink '/dev/v4l/by-path/platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.4:1.0-video-index0' to '../../video0'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: Creating symlink '/dev/v4l/by-id/usb-Guillemot_Corporation_USB_Camera-video-index0' to '../../video0'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: sd-device: Created db file '/run/udev/data/c81:3' for '/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0/video4linux/video0'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: Device (SEQNUM=1578, ACTION=add) processed
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: sd-device-monitor: Passed 1062 byte to netlink monitor
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: 'v4l_id /dev/video1'(out) 'ID_V4L_VERSION=2'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: 'v4l_id /dev/video1'(out) 'ID_V4L_PRODUCT=USB Camera: USB Camera'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: 'v4l_id /dev/video1'(out) 'ID_V4L_CAPABILITIES=:capture:'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: Process 'v4l_id /dev/video1' succeeded.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: IMPORT builtin 'usb_id' /lib/udev/rules.d/60-persistent-v4l.rules:9
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: 1-1.4:1.0: if_class:14 protocol:0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: LINK 'v4l/by-id/usb-Guillemot_Corporation_USB_Camera-video-index1' /lib/udev/rules.d/60-persistent-v4l.rules:10
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: IMPORT builtin 'path_id' /lib/udev/rules.d/60-persistent-v4l.rules:16
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: LINK 'v4l/by-path/platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.4:1.0-video-index1' /lib/udev/rules.d/60-persistent-v4l.rules:17
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: RUN 'uaccess' /lib/udev/rules.d/73-seat-late.rules:17
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: Handling device node '/dev/video1', devnum=c81:4, mode=0660, uid=0, gid=44
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: Setting permissions /dev/video1, 020660, uid=0, gid=44
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: Creating symlink '/dev/char/81:4' to '../video1'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: Creating symlink '/dev/v4l/by-id/usb-Guillemot_Corporation_USB_Camera-video-index1' to '../../video1'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: Creating symlink '/dev/v4l/by-path/platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.4:1.0-video-index1' to '../../video1'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: sd-device: Created db file '/run/udev/data/c81:4' for '/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0/video4linux/video1'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: Process '/usr/sbin/th-cmd --socket /var/run/thd.socket --passfd --udev' succeeded.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: Device (SEQNUM=1579, ACTION=add) processed
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: sd-device-monitor: Passed 1062 byte to netlink monitor
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: Loading module: input:b0003v057Ep030Ae0924-e0,1,kD4,ramlsfw
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: Module 'evdev' is already loaded
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: Device (SEQNUM=1581, ACTION=add) processed
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: sd-device-monitor: Passed 957 byte to netlink monitor
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: event1: sd-device-monitor: Passed 276 byte to netlink monitor
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: Processing device (SEQNUM=1582, ACTION=add)
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: GROUP 105 /lib/udev/rules.d/50-udev-default.rules:29
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: IMPORT builtin 'hwdb' /lib/udev/rules.d/60-evdev.rules:8
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: No entry found from hwdb.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: IMPORT builtin 'hwdb' fails: No data available
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: IMPORT builtin 'hwdb' /lib/udev/rules.d/60-evdev.rules:17
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: No entry found from hwdb.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: IMPORT builtin 'hwdb' fails: No data available
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: IMPORT builtin 'hwdb' /lib/udev/rules.d/60-evdev.rules:21
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: No entry found from hwdb.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: IMPORT builtin 'hwdb' fails: No data available
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: IMPORT builtin 'input_id' /lib/udev/rules.d/60-input-id.rules:5
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: input1: capabilities/ev raw kernel attribute: 3
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: input1: capabilities/abs raw kernel attribute: 0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: input1: capabilities/rel raw kernel attribute: 0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: input1: capabilities/key raw kernel attribute: 100000 0 0 0 0 0 0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: input1: properties raw kernel attribute: 0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: test_key: checking bit block 0 for any keys; found=0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: test_key: checking bit block 32 for any keys; found=0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: test_key: checking bit block 64 for any keys; found=0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: test_key: checking bit block 96 for any keys; found=0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: test_key: checking bit block 128 for any keys; found=0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: test_key: checking bit block 160 for any keys; found=0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: test_key: checking bit block 192 for any keys; found=1
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: test_key: checking bit block 224 for any keys; found=1
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: IMPORT builtin 'hwdb' /lib/udev/rules.d/60-input-id.rules:6
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: No entry found from hwdb.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: IMPORT builtin 'hwdb' fails: No data available
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: IMPORT builtin 'usb_id' /lib/udev/rules.d/60-persistent-input.rules:11
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.0: if_class:14 protocol:0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: LINK 'input/by-id/usb-Guillemot_Corporation_USB_Camera-event-if00' /lib/udev/rules.d/60-persistent-input.rules:32
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: IMPORT builtin 'path_id' /lib/udev/rules.d/60-persistent-input.rules:35
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: LINK 'input/by-path/platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.4:1.0-event' /lib/udev/rules.d/60-persistent-input.rules:40
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: RUN '/usr/sbin/th-cmd --socket /var/run/thd.socket --passfd --udev' /lib/udev/rules.d/60-triggerhappy.rules:4
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: PROGRAM 'libinput-device-group /sys/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0/input/input1/event1' /lib/udev/rules.d/80-libinput-device-groups.rules:7
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: Starting 'libinput-device-group /sys/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0/input/input1/event1'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: Successfully forked off '(spawn)' as PID 2541.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 'libinput-device-group /sys/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0/input/input1/event1'(out) '3/57e/30a:usb-0000:01:00.0-1'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: Process 'libinput-device-group /sys/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0/input/input1/event1' succeeded.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: GROUP 105 /etc/udev/rules.d/99-com.rules:1
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: MODE 0660 /etc/udev/rules.d/99-com.rules:1
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: Handling device node '/dev/input/event1', devnum=c13:65, mode=0660, uid=0, gid=105
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: Setting permissions /dev/input/event1, 020660, uid=0, gid=105
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: Creating symlink '/dev/char/13:65' to '../input/event1'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: Creating symlink '/dev/input/by-id/usb-Guillemot_Corporation_USB_Camera-event-if00' to '../event1'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: Creating symlink '/dev/input/by-path/platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.4:1.0-event' to '../event1'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: sd-device: Created db file '/run/udev/data/c13:65' for '/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0/input/input1/event1'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: Starting '/usr/sbin/th-cmd --socket /var/run/thd.socket --passfd --udev'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: Successfully forked off '(spawn)' as PID 2542.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: Device (SEQNUM=1582, ACTION=add) processed
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: event1: sd-device-monitor: Passed 1041 byte to netlink monitor
  Oct 24 10:32:17 raspberrypi systemd-udevd[143]: 1-1.4:1.0: sd-device-monitor: Passed 358 byte to netlink monitor
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.0: Processing device (SEQNUM=1583, ACTION=bind)
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.0: IMPORT builtin 'hwdb' /lib/udev/rules.d/50-udev-default.rules:14
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.0: IMPORT builtin 'usb_id' /lib/udev/rules.d/60-libgphoto2-6.rules:9
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.0: Failed to access usb_interface: No such file or directory
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.0: IMPORT builtin 'usb_id' fails: No such file or directory
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.0: sd-device: Created db file '/run/udev/data/+usb:1-1.4:1.0' for '/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.0: Device (SEQNUM=1583, ACTION=bind) processed
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.0: sd-device-monitor: Passed 500 byte to netlink monitor
  Oct 24 10:32:21 raspberrypi systemd-udevd[143]: Cleanup idle workers
  Oct 24 10:32:21 raspberrypi systemd-udevd[2535]: Unload module index
  Oct 24 10:32:21 raspberrypi systemd-udevd[2537]: Unload module index
  Oct 24 10:32:21 raspberrypi systemd-udevd[2535]: Unloaded link configuration context.
  Oct 24 10:32:21 raspberrypi systemd-udevd[2537]: Unloaded link configuration context.
  Oct 24 10:32:21 raspberrypi systemd-udevd[2536]: Unload module index
  Oct 24 10:32:21 raspberrypi systemd-udevd[2533]: Unload module index
  Oct 24 10:32:21 raspberrypi systemd-udevd[2536]: Unloaded link configuration context.
  Oct 24 10:32:21 raspberrypi systemd-udevd[2533]: Unloaded link configuration context.
  Oct 24 10:32:21 raspberrypi systemd-udevd[143]: Worker [2537] exited
  Oct 24 10:32:21 raspberrypi systemd-udevd[143]: Worker [2533] exited
  Oct 24 10:32:21 raspberrypi systemd-udevd[143]: Worker [2536] exited
  Oct 24 10:32:21 raspberrypi systemd-udevd[2531]: Unload module index
  Oct 24 10:32:21 raspberrypi systemd-udevd[2531]: Unloaded link configuration context.
  Oct 24 10:32:21 raspberrypi systemd-udevd[143]: Worker [2535] exited
  Oct 24 10:32:21 raspberrypi systemd-udevd[143]: Worker [2531] exited
  ```

## 99-com.rules hacking

* `/etc/udev/rules.d/99-com.rules`
  ```
  SUBSYSTEM=="input", GROUP="input", MODE="0660"
  SUBSYSTEM=="i2c-dev", GROUP="i2c", MODE="0660"
  SUBSYSTEM=="spidev", GROUP="spi", MODE="0660"
  SUBSYSTEM=="bcm2835-gpiomem", GROUP="gpio", MODE="0660"
  
  SUBSYSTEM=="gpio", GROUP="gpio", MODE="0660"
  SUBSYSTEM=="gpio*", PROGRAM="/bin/sh -c '\
          chown -R root:gpio /sys/class/gpio && chmod -R 770 /sys/class/gpio;\
          chown -R root:gpio /sys/devices/virtual/gpio && chmod -R 770 /sys/devices/virtual/gpio;\
          chown -R root:gpio /sys$devpath && chmod -R 770 /sys$devpath\
  '"
  
  KERNEL=="ttyAMA[01]", PROGRAM="/bin/sh -c '\
          ALIASES=/proc/device-tree/aliases; \
          if cmp -s $ALIASES/uart0 $ALIASES/serial0; then \
                  echo 0;\
          elif cmp -s $ALIASES/uart0 $ALIASES/serial1; then \
                  echo 1; \
          else \
                  exit 1; \
          fi\
  '", SYMLINK+="serial%c"
  
  KERNEL=="ttyS0", PROGRAM="/bin/sh -c '\
          ALIASES=/proc/device-tree/aliases; \
          if cmp -s $ALIASES/uart1 $ALIASES/serial0; then \
                  echo 0; \
          elif cmp -s $ALIASES/uart1 $ALIASES/serial1; then \
                  echo 1; \
          else \
                  exit 1; \
          fi \
  '", SYMLINK+="serial%c"
  ```
* `SUBSYSTEM=="input", GROUP="input", MODE="0660"`
  * `udevadm info -q all -a /dev/input/mice`
    ```
    Udevadm info starts with the device specified by the devpath and then
    walks up the chain of parent devices. It prints for every device
    found, all possible attributes in the udev rules key format.
    A rule to match, can be composed by the attributes of the device
    and the attributes from one single parent device.
  
      looking at device '/devices/virtual/input/mice':
        KERNEL=="mice"
        SUBSYSTEM=="input"
        DRIVER==""
    ```
  * `ls -al /dev/input/*`
    ```
    crw-rw----  1 root input 13, 64 Oct 25 10:17 event0
    crw-rw----  1 root input 13, 63 Oct 25 10:17 mice
    ```
* `SUBSYSTEM=="i2c-dev", GROUP="i2c", MODE="0660"`
  * `udevadm info -q all -a /dev/i2c-1`
    ```
    Udevadm info starts with the device specified by the devpath and then
    walks up the chain of parent devices. It prints for every device
    found, all possible attributes in the udev rules key format.
    A rule to match, can be composed by the attributes of the device
    and the attributes from one single parent device.
    
      looking at device '/devices/platform/soc/fe804000.i2c/i2c-1/i2c-dev/i2c-1':
        KERNEL=="i2c-1"
        SUBSYSTEM=="i2c-dev"
        DRIVER==""
        ATTR{name}=="bcm2835 I2C adapter"
    
      looking at parent device '/devices/platform/soc/fe804000.i2c/i2c-1':
        KERNELS=="i2c-1"
        SUBSYSTEMS=="i2c"
        DRIVERS==""
        ATTRS{name}=="bcm2835 I2C adapter"
    
      looking at parent device '/devices/platform/soc/fe804000.i2c':
        KERNELS=="fe804000.i2c"
        SUBSYSTEMS=="platform"
        DRIVERS=="i2c-bcm2835"
        ATTRS{driver_override}=="(null)"
    
      looking at parent device '/devices/platform/soc':
        KERNELS=="soc"
        SUBSYSTEMS=="platform"
        DRIVERS==""
        ATTRS{driver_override}=="(null)"
    
      looking at parent device '/devices/platform':
        KERNELS=="platform"
        SUBSYSTEMS==""
        DRIVERS==""
    ```
  * `ls -al /dev/i2c-1`
    ```
    crw-rw---- 1 root i2c 89, 1 Oct 25 10:17 /dev/i2c-1
    ```

## 查看usb camera设备信息

* `udevadm info -a -p $(udevadm info -q path -n /dev/video0)`
  ```
  Udevadm info starts with the device specified by the devpath and then
  walks up the chain of parent devices. It prints for every device
  found, all possible attributes in the udev rules key format.
  A rule to match, can be composed by the attributes of the device
  and the attributes from one single parent device.
  
    looking at device '//devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0/video4linux/video0':
      KERNEL=="video0"
      SUBSYSTEM=="video4linux"
      DRIVER==""
      ATTR{name}=="USB Camera: USB Camera"
      ATTR{dev_debug}=="0"
      ATTR{index}=="0"
  
    looking at parent device '//devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0':
      KERNELS=="1-1.4:1.0"
      SUBSYSTEMS=="usb"
      DRIVERS=="uvcvideo"
      ATTRS{iad_bFunctionSubClass}=="03"
      ATTRS{supports_autosuspend}=="1"
      ATTRS{bInterfaceNumber}=="00"
      ATTRS{bInterfaceSubClass}=="01"
      ATTRS{iad_bFunctionClass}=="0e"
      ATTRS{bAlternateSetting}==" 0"
      ATTRS{iad_bFirstInterface}=="00"
      ATTRS{interface}=="USB Camera"
      ATTRS{bInterfaceProtocol}=="00"
      ATTRS{iad_bFunctionProtocol}=="00"
      ATTRS{bInterfaceClass}=="0e"
      ATTRS{authorized}=="1"
      ATTRS{bNumEndpoints}=="01"
      ATTRS{iad_bInterfaceCount}=="02"
  
    looking at parent device '//devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4':
      KERNELS=="1-1.4"
      SUBSYSTEMS=="usb"
      DRIVERS=="usb"
      ATTRS{bNumConfigurations}=="1"
      ATTRS{bmAttributes}=="80"
      ATTRS{quirks}=="0x0"
      ATTRS{maxchild}=="0"
      ATTRS{devnum}=="3"
      ATTRS{authorized}=="1"
      ATTRS{tx_lanes}=="1"
      ATTRS{avoid_reset_quirk}=="0"
      ATTRS{configuration}=="Guillemot Corporation"
      ATTRS{rx_lanes}=="1"
      ATTRS{product}=="USB Camera"
      ATTRS{removable}=="unknown"
      ATTRS{idProduct}=="030a"
      ATTRS{speed}=="480"
      ATTRS{bDeviceSubClass}=="02"
      ATTRS{bDeviceProtocol}=="01"
      ATTRS{devspec}=="  (null)"
      ATTRS{idVendor}=="057e"
      ATTRS{bcdDevice}=="0924"
      ATTRS{urbnum}=="29"
      ATTRS{busnum}=="1"
      ATTRS{ltm_capable}=="no"
      ATTRS{devpath}=="1.4"
      ATTRS{bMaxPower}=="500mA"
      ATTRS{bConfigurationValue}=="1"
      ATTRS{bDeviceClass}=="ef"
      ATTRS{bNumInterfaces}==" 2"
      ATTRS{version}==" 2.00"
      ATTRS{manufacturer}=="Guillemot Corporation"
      ATTRS{bMaxPacketSize0}=="64"
  
    looking at parent device '//devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1':
      KERNELS=="1-1"
      SUBSYSTEMS=="usb"
      DRIVERS=="usb"
      ATTRS{urbnum}=="40"
      ATTRS{version}==" 2.10"
      ATTRS{bNumConfigurations}=="1"
      ATTRS{devspec}=="  (null)"
      ATTRS{rx_lanes}=="1"
      ATTRS{idVendor}=="2109"
      ATTRS{bConfigurationValue}=="1"
      ATTRS{speed}=="480"
      ATTRS{bDeviceProtocol}=="01"
      ATTRS{bNumInterfaces}==" 1"
      ATTRS{bMaxPower}=="100mA"
      ATTRS{busnum}=="1"
      ATTRS{bDeviceSubClass}=="00"
      ATTRS{maxchild}=="4"
      ATTRS{bDeviceClass}=="09"
      ATTRS{bcdDevice}=="0420"
      ATTRS{idProduct}=="3431"
      ATTRS{bmAttributes}=="e0"
      ATTRS{product}=="USB2.0 Hub"
      ATTRS{quirks}=="0x0"
      ATTRS{removable}=="unknown"
      ATTRS{tx_lanes}=="1"
      ATTRS{devnum}=="2"
      ATTRS{devpath}=="1"
      ATTRS{avoid_reset_quirk}=="0"
      ATTRS{ltm_capable}=="no"
      ATTRS{configuration}==""
      ATTRS{authorized}=="1"
      ATTRS{bMaxPacketSize0}=="64"
  
    looking at parent device '//devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1':
      KERNELS=="usb1"
      SUBSYSTEMS=="usb"
      DRIVERS=="usb"
      ATTRS{idProduct}=="0002"
      ATTRS{devspec}=="  (null)"
      ATTRS{bNumInterfaces}==" 1"
      ATTRS{quirks}=="0x0"
      ATTRS{product}=="xHCI Host Controller"
      ATTRS{authorized_default}=="1"
      ATTRS{devpath}=="0"
      ATTRS{speed}=="480"
      ATTRS{manufacturer}=="Linux 4.19.71-v7l xhci-hcd"
      ATTRS{rx_lanes}=="1"
      ATTRS{authorized}=="1"
      ATTRS{devnum}=="1"
      ATTRS{urbnum}=="32"
      ATTRS{avoid_reset_quirk}=="0"
      ATTRS{bConfigurationValue}=="1"
      ATTRS{bMaxPacketSize0}=="64"
      ATTRS{removable}=="unknown"
      ATTRS{maxchild}=="1"
      ATTRS{tx_lanes}=="1"
      ATTRS{bDeviceClass}=="09"
      ATTRS{idVendor}=="1d6b"
      ATTRS{configuration}==""
      ATTRS{bNumConfigurations}=="1"
      ATTRS{version}==" 2.00"
      ATTRS{ltm_capable}=="no"
      ATTRS{bmAttributes}=="e0"
      ATTRS{bMaxPower}=="0mA"
      ATTRS{bDeviceProtocol}=="01"
      ATTRS{bDeviceSubClass}=="00"
      ATTRS{serial}=="0000:01:00.0"
      ATTRS{bcdDevice}=="0419"
      ATTRS{busnum}=="1"
      ATTRS{interface_authorized_default}=="1"
  
    looking at parent device '//devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0':
      KERNELS=="0000:01:00.0"
      SUBSYSTEMS=="pci"
      DRIVERS=="xhci_hcd"
      ATTRS{max_link_speed}=="5 GT/s"
      ATTRS{class}=="0x0c0330"
      ATTRS{broken_parity_status}=="0"
      ATTRS{revision}=="0x01"
      ATTRS{subsystem_device}=="0x3483"
      ATTRS{max_link_width}=="1"
      ATTRS{current_link_speed}=="5 GT/s"
      ATTRS{dma_mask_bits}=="64"
      ATTRS{driver_override}=="(null)"
      ATTRS{devspec}==""
      ATTRS{irq}=="56"
      ATTRS{enable}=="1"
      ATTRS{consistent_dma_mask_bits}=="64"
      ATTRS{local_cpulist}=="0-3"
      ATTRS{local_cpus}=="f"
      ATTRS{ari_enabled}=="0"
      ATTRS{device}=="0x3483"
      ATTRS{current_link_width}=="1"
      ATTRS{msi_bus}=="1"
      ATTRS{vendor}=="0x1106"
      ATTRS{subsystem_vendor}=="0x1106"
  
    looking at parent device '//devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0':
      KERNELS=="0000:00:00.0"
      SUBSYSTEMS=="pci"
      DRIVERS=="pcieport"
      ATTRS{irq}=="55"
      ATTRS{broken_parity_status}=="0"
      ATTRS{subordinate_bus_number}=="1"
      ATTRS{dma_mask_bits}=="32"
      ATTRS{secondary_bus_number}=="1"
      ATTRS{vendor}=="0x14e4"
      ATTRS{devspec}==""
      ATTRS{subsystem_vendor}=="0x0000"
      ATTRS{device}=="0x2711"
      ATTRS{revision}=="0x10"
      ATTRS{max_link_speed}=="5 GT/s"
      ATTRS{driver_override}=="(null)"
      ATTRS{enable}=="1"
      ATTRS{msi_bus}=="1"
      ATTRS{class}=="0x060400"
      ATTRS{aer_rootport_total_err_nonfatal}=="0"
      ATTRS{subsystem_device}=="0x0000"
      ATTRS{current_link_speed}=="5 GT/s"
      ATTRS{local_cpulist}=="0-3"
      ATTRS{current_link_width}=="1"
      ATTRS{max_link_width}=="1"
      ATTRS{local_cpus}=="f"
      ATTRS{consistent_dma_mask_bits}=="32"
      ATTRS{ari_enabled}=="0"
      ATTRS{aer_rootport_total_err_cor}=="0"
      ATTRS{aer_rootport_total_err_fatal}=="0"
  
    looking at parent device '//devices/platform/scb/fd500000.pcie/pci0000:00':
      KERNELS=="pci0000:00"
      SUBSYSTEMS==""
      DRIVERS==""
  
    looking at parent device '//devices/platform/scb/fd500000.pcie':
      KERNELS=="fd500000.pcie"
      SUBSYSTEMS=="platform"
      DRIVERS=="brcm-pcie"
      ATTRS{dmabounce_stats}=="m:0/0 s:0/0 f:0 s:0 b:0/0 a:0/0"
      ATTRS{driver_override}=="(null)"
  
    looking at parent device '//devices/platform/scb':
      KERNELS=="scb"
      SUBSYSTEMS=="platform"
      DRIVERS==""
      ATTRS{driver_override}=="(null)"
  
    looking at parent device '//devices/platform':
      KERNELS=="platform"
      SUBSYSTEMS==""
      DRIVERS==""
  ```

## udevadm监听USB Camera设备插入输出信息

* `udevadm monitor --environment --udev`
  ```
  monitor will print the received events for:
  UDEV - the event which udev sends out after rule processing
  
  
  UDEV  [4816.062264] add      /devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4 (usb)
  ACTION=add
  DEVPATH=/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4
  SUBSYSTEM=usb
  DEVNAME=/dev/bus/usb/001/003
  DEVTYPE=usb_device
  PRODUCT=57e/30a/924
  TYPE=239/2/1
  BUSNUM=001
  DEVNUM=003
  SEQNUM=1573
  USEC_INITIALIZED=4816060935
  ID_VENDOR=Guillemot_Corporation
  ID_VENDOR_ENC=Guillemot\x20Corporation
  ID_VENDOR_ID=057e
  ID_MODEL=USB_Camera
  ID_MODEL_ENC=USB\x20Camera
  ID_MODEL_ID=030a
  ID_REVISION=0924
  ID_SERIAL=Guillemot_Corporation_USB_Camera
  ID_BUS=usb
  ID_USB_INTERFACES=:0e0100:0e0200:
  ID_VENDOR_FROM_DATABASE=Nintendo Co., Ltd
  DRIVER=usb
  MAJOR=189
  MINOR=2
  
  UDEV  [4816.082045] add      /devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.1 (usb)
  ACTION=add
  DEVPATH=/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.1
  SUBSYSTEM=usb
  DEVTYPE=usb_interface
  PRODUCT=57e/30a/924
  TYPE=239/2/1
  INTERFACE=14/2/0
  MODALIAS=usb:v057Ep030Ad0924dcEFdsc02dp01ic0Eisc02ip00in01
  SEQNUM=1575
  USEC_INITIALIZED=4816080724
  ID_USB_CLASS_FROM_DATABASE=Miscellaneous Device
  ID_USB_PROTOCOL_FROM_DATABASE=Interface Association
  ID_VENDOR_FROM_DATABASE=Nintendo Co., Ltd
  
  UDEV  [4816.095431] add      /module/uvcvideo (module)
  ACTION=add
  DEVPATH=/module/uvcvideo
  SUBSYSTEM=module
  SEQNUM=1577
  USEC_INITIALIZED=4816095112
  
  UDEV  [4816.115822] add      /devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0 (usb)
  ACTION=add
  DEVPATH=/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0
  SUBSYSTEM=usb
  DEVTYPE=usb_interface
  PRODUCT=57e/30a/924
  TYPE=239/2/1
  INTERFACE=14/1/0
  MODALIAS=usb:v057Ep030Ad0924dcEFdsc02dp01ic0Eisc01ip00in00
  SEQNUM=1574
  USEC_INITIALIZED=4816075377
  ID_USB_CLASS_FROM_DATABASE=Miscellaneous Device
  ID_USB_PROTOCOL_FROM_DATABASE=Interface Association
  ID_VENDOR_FROM_DATABASE=Nintendo Co., Ltd
  
  UDEV  [4816.117617] add      /bus/usb/drivers/uvcvideo (drivers)
  ACTION=add
  DEVPATH=/bus/usb/drivers/uvcvideo
  SUBSYSTEM=drivers
  SEQNUM=1585
  USEC_INITIALIZED=4816117456
  
  UDEV  [4816.134049] bind     /devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4 (usb)
  ACTION=bind
  DEVPATH=/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4
  SUBSYSTEM=usb
  DEVNAME=/dev/bus/usb/001/003
  DEVTYPE=usb_device
  DRIVER=usb
  PRODUCT=57e/30a/924
  TYPE=239/2/1
  BUSNUM=001
  DEVNUM=003
  SEQNUM=1576
  USEC_INITIALIZED=4816060935
  ID_VENDOR=Guillemot_Corporation
  ID_VENDOR_ENC=Guillemot\x20Corporation
  ID_VENDOR_ID=057e
  ID_MODEL=USB_Camera
  ID_MODEL_ENC=USB\x20Camera
  ID_MODEL_ID=030a
  ID_REVISION=0924
  ID_SERIAL=Guillemot_Corporation_USB_Camera
  ID_BUS=usb
  ID_USB_INTERFACES=:0e0100:0e0200:
  ID_VENDOR_FROM_DATABASE=Nintendo Co., Ltd
  MAJOR=189
  MINOR=2
  
  UDEV  [4816.140526] bind     /devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.1 (usb)
  ACTION=bind
  DEVPATH=/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.1
  SUBSYSTEM=usb
  DEVTYPE=usb_interface
  DRIVER=uvcvideo
  PRODUCT=57e/30a/924
  TYPE=239/2/1
  INTERFACE=14/2/0
  MODALIAS=usb:v057Ep030Ad0924dcEFdsc02dp01ic0Eisc02ip00in01
  SEQNUM=1578
  USEC_INITIALIZED=4816080724
  ID_USB_CLASS_FROM_DATABASE=Miscellaneous Device
  ID_USB_PROTOCOL_FROM_DATABASE=Interface Association
  ID_VENDOR_FROM_DATABASE=Nintendo Co., Ltd
  
  UDEV  [4816.146230] add      /devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0/media1 (media)
  ACTION=add
  DEVPATH=/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0/media1
  SUBSYSTEM=media
  DEVNAME=/dev/media1
  SEQNUM=1581
  USEC_INITIALIZED=4816145917
  MAJOR=237
  MINOR=1
  
  UDEV  [4816.157084] add      /devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0/video4linux/video0 (video4linux)
  ACTION=add
  DEVPATH=/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0/video4linux/video0
  SUBSYSTEM=video4linux
  DEVNAME=/dev/video0
  SEQNUM=1579
  USEC_INITIALIZED=4816156333
  ID_V4L_VERSION=2
  ID_V4L_PRODUCT=USB Camera: USB Camera
  ID_V4L_CAPABILITIES=:capture:
  ID_VENDOR=Guillemot_Corporation
  ID_VENDOR_ENC=Guillemot\x20Corporation
  ID_VENDOR_ID=057e
  ID_MODEL=USB_Camera
  ID_MODEL_ENC=USB\x20Camera
  ID_MODEL_ID=030a
  ID_REVISION=0924
  ID_SERIAL=Guillemot_Corporation_USB_Camera
  ID_TYPE=video
  ID_BUS=usb
  ID_USB_INTERFACES=:0e0100:0e0200:
  ID_USB_INTERFACE_NUM=00
  ID_USB_DRIVER=uvcvideo
  ID_PATH=platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.4:1.0
  ID_PATH_TAG=platform-fd500000_pcie-pci-0000_01_00_0-usb-0_1_4_1_0
  ID_FOR_SEAT=video4linux-platform-fd500000_pcie-pci-0000_01_00_0-usb-0_1_4_1_0
  MAJOR=81
  MINOR=3
  DEVLINKS=/dev/v4l/by-id/usb-Guillemot_Corporation_USB_Camera-video-index0 /dev/v4l/by-path/platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.4:1.0-video-index0
  TAGS=:uaccess:seat:
  
  UDEV  [4816.159222] add      /devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0/video4linux/video1 (video4linux)
  ACTION=add
  DEVPATH=/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0/video4linux/video1
  SUBSYSTEM=video4linux
  DEVNAME=/dev/video1
  SEQNUM=1580
  USEC_INITIALIZED=4816158093
  ID_V4L_VERSION=2
  ID_V4L_PRODUCT=USB Camera: USB Camera
  ID_V4L_CAPABILITIES=:capture:
  ID_VENDOR=Guillemot_Corporation
  ID_VENDOR_ENC=Guillemot\x20Corporation
  ID_VENDOR_ID=057e
  ID_MODEL=USB_Camera
  ID_MODEL_ENC=USB\x20Camera
  ID_MODEL_ID=030a
  ID_REVISION=0924
  ID_SERIAL=Guillemot_Corporation_USB_Camera
  ID_TYPE=video
  ID_BUS=usb
  ID_USB_INTERFACES=:0e0100:0e0200:
  ID_USB_INTERFACE_NUM=00
  ID_USB_DRIVER=uvcvideo
  ID_PATH=platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.4:1.0
  ID_PATH_TAG=platform-fd500000_pcie-pci-0000_01_00_0-usb-0_1_4_1_0
  ID_FOR_SEAT=video4linux-platform-fd500000_pcie-pci-0000_01_00_0-usb-0_1_4_1_0
  MAJOR=81
  MINOR=4
  DEVLINKS=/dev/v4l/by-path/platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.4:1.0-video-index1 /dev/v4l/by-id/usb-Guillemot_Corporation_USB_Camera-video-index1
  TAGS=:uaccess:seat:
  
  UDEV  [4816.165386] add      /devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0/input/input1 (input)
  ACTION=add
  DEVPATH=/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0/input/input1
  SUBSYSTEM=input
  PRODUCT=3/57e/30a/924
  NAME="USB Camera: USB Camera"
  PHYS="usb-0000:01:00.0-1.4/button"
  PROP=0
  EV=3
  KEY=100000 0 0 0 0 0 0
  MODALIAS=input:b0003v057Ep030Ae0924-e0,1,kD4,ramlsfw
  SEQNUM=1582
  USEC_INITIALIZED=4816149568
  ID_INPUT=1
  ID_INPUT_KEY=1
  ID_VENDOR=Guillemot_Corporation
  ID_VENDOR_ENC=Guillemot\x20Corporation
  ID_VENDOR_ID=057e
  ID_MODEL=USB_Camera
  ID_MODEL_ENC=USB\x20Camera
  ID_MODEL_ID=030a
  ID_REVISION=0924
  ID_SERIAL=Guillemot_Corporation_USB_Camera
  ID_TYPE=video
  ID_BUS=usb
  ID_USB_INTERFACES=:0e0100:0e0200:
  ID_USB_INTERFACE_NUM=00
  ID_USB_DRIVER=uvcvideo
  ID_PATH=platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.4:1.0
  ID_PATH_TAG=platform-fd500000_pcie-pci-0000_01_00_0-usb-0_1_4_1_0
  ID_FOR_SEAT=input-platform-fd500000_pcie-pci-0000_01_00_0-usb-0_1_4_1_0
  TAGS=:seat:
  
  UDEV  [4816.390789] add      /devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0/input/input1/event1 (input)
  ACTION=add
  DEVPATH=/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0/input/input1/event1
  SUBSYSTEM=input
  DEVNAME=/dev/input/event1
  SEQNUM=1583
  USEC_INITIALIZED=4816286548
  ID_INPUT=1
  ID_INPUT_KEY=1
  ID_VENDOR=Guillemot_Corporation
  ID_VENDOR_ENC=Guillemot\x20Corporation
  ID_VENDOR_ID=057e
  ID_MODEL=USB_Camera
  ID_MODEL_ENC=USB\x20Camera
  ID_MODEL_ID=030a
  ID_REVISION=0924
  ID_SERIAL=Guillemot_Corporation_USB_Camera
  ID_TYPE=video
  ID_BUS=usb
  ID_USB_INTERFACES=:0e0100:0e0200:
  ID_USB_INTERFACE_NUM=00
  ID_USB_DRIVER=uvcvideo
  ID_PATH=platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.4:1.0
  ID_PATH_TAG=platform-fd500000_pcie-pci-0000_01_00_0-usb-0_1_4_1_0
  XKBMODEL=pc105
  XKBLAYOUT=us
  XKBVARIANT=
  XKBOPTIONS=
  BACKSPACE=guess
  LIBINPUT_DEVICE_GROUP=3/57e/30a:usb-0000:01:00.0-1
  MAJOR=13
  MINOR=65
  DEVLINKS=/dev/input/by-path/platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.4:1.0-event /dev/input/by-id/usb-Guillemot_Corporation_USB_Camera-event-if00
  TAGS=:power-switch:
  
  UDEV  [4816.396840] bind     /devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0 (usb)
  ACTION=bind
  DEVPATH=/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0
  SUBSYSTEM=usb
  DEVTYPE=usb_interface
  DRIVER=uvcvideo
  PRODUCT=57e/30a/924
  TYPE=239/2/1
  INTERFACE=14/1/0
  MODALIAS=usb:v057Ep030Ad0924dcEFdsc02dp01ic0Eisc01ip00in00
  SEQNUM=1584
  USEC_INITIALIZED=4816075377
  ID_USB_CLASS_FROM_DATABASE=Miscellaneous Device
  ID_USB_PROTOCOL_FROM_DATABASE=Interface Association
  ID_VENDOR_FROM_DATABASE=Nintendo Co., Ltd
  ```

## 60-persistent-v4l.rules跟踪

* `/lib/udev/rules.d/60-persistent-v4l.rules`
  ```
  # do not edit this file, it will be overwritten on update
  
  ACTION=="remove", GOTO="persistent_v4l_end"                                         # 如果是移除信息就跳转到该文件最后
  SUBSYSTEM!="video4linux", GOTO="persistent_v4l_end"                                 # 如果不是video4linux，跳转到文件最后
  ENV{MAJOR}=="", GOTO="persistent_v4l_end"                                           # 如果主设备号为空，跳转到文件最后
  
  IMPORT{program}="v4l_id $devnode"
  
  SUBSYSTEMS=="usb", IMPORT{builtin}="usb_id"
  KERNEL=="video*", ENV{ID_SERIAL}=="?*", SYMLINK+="v4l/by-id/$env{ID_BUS}-$env{ID_SERIAL}-video-index$attr{index}"
  
  # check for valid "index" number
  TEST!="index", GOTO="persistent_v4l_end"
  ATTR{index}!="?*", GOTO="persistent_v4l_end"
  
  IMPORT{builtin}="path_id"
  ENV{ID_PATH}=="?*", KERNEL=="video*|vbi*", SYMLINK+="v4l/by-path/$env{ID_PATH}-video-index$attr{index}"
  ENV{ID_PATH}=="?*", KERNEL=="audio*", SYMLINK+="v4l/by-path/$env{ID_PATH}-audio-index$attr{index}"
  
  LABEL="persistent_v4l_end"
  ```
* `/var/log/debug`
  ```
  [...省略]
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: IMPORT 'v4l_id /dev/video0' /lib/udev/rules.d/60-persistent-v4l.rules:7
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.1: Failed to access usb_interface: No such file or directory
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.1: IMPORT builtin 'usb_id' fails: No such file or directory
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: Starting 'v4l_id /dev/video0'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: Successfully forked off '(spawn)' as PID 2538.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: Processing device (SEQNUM=1581, ACTION=add)
  Oct 24 10:32:17 raspberrypi systemd-udevd[2537]: input1: IMPORT builtin 'hwdb' /lib/udev/rules.d/50-udev-default.rules:14
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: GROUP 44 /lib/udev/rules.d/50-udev-default.rules:32
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: IMPORT 'v4l_id /dev/video1' /lib/udev/rules.d/60-persistent-v4l.rules:7
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: Starting 'v4l_id /dev/video1'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.1: sd-device: Created db file '/run/udev/data/+usb:1-1.4:1.1' for '/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.1'
  [...省略]
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: Process 'v4l_id /dev/video0' succeeded.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: IMPORT builtin 'usb_id' /lib/udev/rules.d/60-persistent-v4l.rules:9
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: 1-1.4:1.0: if_class:14 protocol:0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: LINK 'v4l/by-id/usb-Guillemot_Corporation_USB_Camera-video-index0' /lib/udev/rules.d/60-persistent-v4l.rules:10
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: IMPORT builtin 'path_id' /lib/udev/rules.d/60-persistent-v4l.rules:16
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: LINK 'v4l/by-path/platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.4:1.0-video-index0' /lib/udev/rules.d/60-persistent-v4l.rules:17
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: RUN 'uaccess' /lib/udev/rules.d/73-seat-late.rules:17
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: Handling device node '/dev/video0', devnum=c81:3, mode=0660, uid=0, gid=44
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: Setting permissions /dev/video0, 020660, uid=0, gid=44
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: Creating symlink '/dev/char/81:3' to '../video0'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: Creating symlink '/dev/v4l/by-path/platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.4:1.0-video-index0' to '../../video0'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: Creating symlink '/dev/v4l/by-id/usb-Guillemot_Corporation_USB_Camera-video-index0' to '../../video0'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: sd-device: Created db file '/run/udev/data/c81:3' for '/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0/video4linux/video0'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: Device (SEQNUM=1578, ACTION=add) processed
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: video0: sd-device-monitor: Passed 1062 byte to netlink monitor
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: 'v4l_id /dev/video1'(out) 'ID_V4L_VERSION=2'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: 'v4l_id /dev/video1'(out) 'ID_V4L_PRODUCT=USB Camera: USB Camera'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: 'v4l_id /dev/video1'(out) 'ID_V4L_CAPABILITIES=:capture:'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: Process 'v4l_id /dev/video1' succeeded.
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: IMPORT builtin 'usb_id' /lib/udev/rules.d/60-persistent-v4l.rules:9
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: 1-1.4:1.0: if_class:14 protocol:0
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: LINK 'v4l/by-id/usb-Guillemot_Corporation_USB_Camera-video-index1' /lib/udev/rules.d/60-persistent-v4l.rules:10
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: IMPORT builtin 'path_id' /lib/udev/rules.d/60-persistent-v4l.rules:16
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: LINK 'v4l/by-path/platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.4:1.0-video-index1' /lib/udev/rules.d/60-persistent-v4l.rules:17
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: RUN 'uaccess' /lib/udev/rules.d/73-seat-late.rules:17
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: Handling device node '/dev/video1', devnum=c81:4, mode=0660, uid=0, gid=44
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: Setting permissions /dev/video1, 020660, uid=0, gid=44
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: Creating symlink '/dev/char/81:4' to '../video1'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: Creating symlink '/dev/v4l/by-id/usb-Guillemot_Corporation_USB_Camera-video-index1' to '../../video1'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: Creating symlink '/dev/v4l/by-path/platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.4:1.0-video-index1' to '../../video1'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2535]: video1: sd-device: Created db file '/run/udev/data/c81:4' for '/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0/video4linux/video1'
  [...省略]
  ```

## 80-drivers.rules跟踪

* `/lib/udev/rules.d/80-drivers.rules`
  ```
  # do not edit this file, it will be overwritten on update
  
  ACTION!="add", GOTO="drivers_end"                                               # 不是add，就跳转到本文件最后
  
  ENV{MODALIAS}=="?*", RUN{builtin}+="kmod load $env{MODALIAS}"
  SUBSYSTEM=="tifm", ENV{TIFM_CARD_TYPE}=="SD", RUN{builtin}+="kmod load tifm_sd"
  SUBSYSTEM=="tifm", ENV{TIFM_CARD_TYPE}=="MS", RUN{builtin}+="kmod load tifm_ms"
  SUBSYSTEM=="memstick", RUN{builtin}+="kmod load ms_block mspro_block"
  SUBSYSTEM=="i2o", RUN{builtin}+="kmod load i2o_block"
  SUBSYSTEM=="module", KERNEL=="parport_pc", RUN{builtin}+="kmod load ppdev"
  KERNEL=="mtd*ro", ENV{MTD_FTL}=="smartmedia", RUN{builtin}+="kmod load sm_ftl"
  
  LABEL="drivers_end"
  ```
* `/var/log/debug`
  ```
  [...省略]
  Oct 24 10:32:17 raspberrypi systemd-udevd[2533]: 1-1.4:1.1: RUN 'kmod load $env{MODALIAS}' /lib/udev/rules.d/80-drivers.rules:5
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: 1-1.4:1.0: sd-device: Created db file '/run/udev/data/+usb:1-1.4:1.0' for '/devices/platform/scb/fd500000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb1/1-1/1-1.4/1-1.4:1.0'
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: Loading module: usb:v057Ep030Ad0924dcEFdsc02dp01ic0Eisc01ip00in00
  [...省略]
  Oct 24 10:32:17 raspberrypi systemd-udevd[2531]: Inserted module 'uvcvideo'
  [...省略]
  ```
* `/etc/init.d/kmod`
  ```shell
  load_module() {
    local module args
    module="$1"
    args="$2"
  
    if [ "$VERBOSE" != no ]; then
      log_action_msg "Loading kernel module $module"
      modprobe $module $args || true
    else
      modprobe $module $args > /dev/null 2>&1 || true
    fi
  }
  ```
* `modprobe usb:v057Ep030Ad0924dcEFdsc02dp01ic0Eisc01ip00in00`
  ```
  root@raspberrypi:/home/pi# lsmod | grep uvc
  root@raspberrypi:/home/pi# modprobe usb:v057Ep030Ad0924dcEFdsc02dp01ic0Eisc01ip00in00
  root@raspberrypi:/home/pi# lsmod | grep uvc
  uvcvideo               98304  0
  videobuf2_vmalloc      16384  2 uvcvideo,bcm2835_v4l2
  videobuf2_v4l2         24576  4 uvcvideo,bcm2835_codec,bcm2835_v4l2,v4l2_mem2mem
  videobuf2_common       45056  5 uvcvideo,bcm2835_codec,bcm2835_v4l2,v4l2_mem2mem,videobuf2_v4l2
  videodev              200704  7 uvcvideo,bcm2835_codec,v4l2_common,videobuf2_common,bcm2835_v4l2,v4l2_mem2mem,videobuf2_v4l2
  media                  36864  4 uvcvideo,bcm2835_codec,videodev,v4l2_mem2mem
  root@raspberrypi:/home/pi#
  ```
* `/lib/modules/4.19.71-v7l/modules.alias`
  ```
  [...省略]
  alias usb:v*p*d*dc*dsc*dp*ic0Eisc01ip01in* uvcvideo
  alias usb:v*p*d*dc*dsc*dp*ic0Eisc01ip00in* uvcvideo
  [...省略]
  ```
* `drivers/media/usb/uvc/uvcvideo.mod.c`
  ```
  [...省略]
  MODULE_ALIAS("usb:v1C4Fp3000d*dc*dsc*dp*ic0Eisc01ip00in*");
  MODULE_ALIAS("usb:v2833p0201d*dc*dsc*dp*ic0Eisc01ip00in*");
  MODULE_ALIAS("usb:v2833p0211d*dc*dsc*dp*icFFisc01ip00in*");
  MODULE_ALIAS("usb:v*p*d*dc*dsc*dp*ic0Eisc01ip00in*");
  MODULE_ALIAS("usb:v*p*d*dc*dsc*dp*ic0Eisc01ip01in*");
  
  MODULE_INFO(srcversion, "C10A2D5F983795ADBA6DDB5");
  ```
