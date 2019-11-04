# auto sd resize

## 参考文档

* [Automatic Expand Filesystem after cloning a Rasbian image](https://www.raspberrypi.org/forums/viewtopic.php?t=174434)

## init resize

当你将下载的镜像烧录到SD卡之后，查看SD卡boot分区内容可以看到如下情况

* `/boot/cmdline.txt`
  ```
  dwc_otg.lpm_enable=0 console=serial0,115200 console=tty1 root=PARTUUID=7ee80803-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait quiet init=/usr/lib/raspi-config/init_resize.sh
  ```
* `init=/usr/lib/raspi-config/init_resize.sh`

## init_resize.sh

* `usr/lib/raspi-config/init_resize.sh`
  ```shell
  #!/bin/sh
  
  [...省略]
  
  main () {
    get_variables
  
    if ! check_variables; then
      return 1
    fi
  
    check_kernel
  
    if [ "$NOOBS" = "1" ] && [ "$NEW_KERNEL" != "1" ]; then
      BCM_MODULE=$(grep -e "^Hardware" /proc/cpuinfo | cut -d ":" -f 2 | tr -d " " | tr '[:upper:]' '[:lower:]')
      if ! modprobe "$BCM_MODULE"; then
        FAIL_REASON="Couldn't load BCM module $BCM_MODULE"
        return 1
      fi
    fi
  
    if [ "$ROOT_PART_END" -eq "$TARGET_END" ]; then
      reboot_pi
    fi
  
    if [ "$NOOBS" = "1" ]; then
      if ! parted -m "$ROOT_DEV" u s resizepart "$EXT_PART_NUM" yes "$TARGET_END"; then
        FAIL_REASON="Extended partition resize failed"
        return 1
      fi
    fi
  
    if ! parted -m "$ROOT_DEV" u s resizepart "$ROOT_PART_NUM" "$TARGET_END"; then
      FAIL_REASON="Root partition resize failed"
      return 1
    fi
  
    partprobe "$ROOT_DEV"
    fix_partuuid
  
    return 0
  }
  
  mount -t proc proc /proc
  mount -t sysfs sys /sys
  mount -t tmpfs tmp /run
  mkdir -p /run/systemd
  
  mount /boot
  mount / -o remount,rw
  
  sed -i 's| init=/usr/lib/raspi-config/init_resize\.sh||' /boot/cmdline.txt
  sed -i 's| sdhci\.debug_quirks2=4||' /boot/cmdline.txt
  
  if ! grep -q splash /boot/cmdline.txt; then
    sed -i "s/ quiet//g" /boot/cmdline.txt
  fi
  sync
  
  echo 1 > /proc/sys/kernel/sysrq
  
  if ! check_commands; then
    reboot_pi
  fi
  
  if main; then
    whiptail --infobox "Resized root filesystem. Rebooting in 5 seconds..." 20 60
    sleep 5
  else
    sleep 5
    whiptail --msgbox "Could not expand filesystem, please try raspi-config or rc_gui.\n${FAIL_REASON}" 20 60
  fi
  
  reboot_pi
  ```