# wpa_supplicant

## 参考文档

* [wpa_supplicant-devel.pdf](refers/wpa_supplicant-devel.pdf)
  * https://w1.fi/wpa_supplicant/devel/

## 编译wpa_cli

* 目前用的是Android的wpa_supplicant8源代码，测试的结果是，可以编译wpa_cli
* cd wpa_supplicant_8/wpa_supplicant
* cp defconfig .config
* make wpa_cli
  ```
  CC  wpa_cli.c
  CC  ../src/common/wpa_ctrl.c
  CC  ../src/utils/wpa_debug.c
  CC  ../src/utils/common.c
  CC  ../src/common/cli.c
  CC  ../src/utils/os_unix.c
  CC  ../src/utils/eloop.c
  CC  ../src/utils/edit_simple.c
  LD  wpa_cli
  ```
* CONFIG_CTRL_IFACE_NAMED_PIPE is not defined

## wps_cli

* [wpa_cli 命令介绍](https://blog.csdn.net/ltm157/article/details/24810685)
* 主要命令
  ```bash
  root@raspberrypi:/home/pi# wpa_cli -i wlan0
  > list_networks
  > add_network
  > set_network 3 ssid "zengjf"
  > set_network 3 psk "zjf199042"
  > select_network 3
  ```
* 完整操作及log
  ```bash
  root@raspberrypi:/home/pi# wpa_cli -i wlan0
  wpa_cli v2.8-devel
  Copyright (c) 2004-2019, Jouni Malinen <j@w1.fi> and contributors
  
  This software may be distributed under the terms of the BSD license.
  See README for more details.
  
  
  
  Interactive mode
  
  <3>CTRL-EVENT-SCAN-STARTED
  <3>CTRL-EVENT-SCAN-RESULTS
  <3>WPS-AP-AVAILABLE
  <3>CTRL-EVENT-NETWORK-NOT-FOUND
  <3>CTRL-EVENT-SCAN-STARTED
  <3>CTRL-EVENT-SCAN-RESULTS
  <3>WPS-AP-AVAILABLE
  <4>Failed to initiate sched scan
  <3>CTRL-EVENT-NETWORK-NOT-FOUND
  <3>CTRL-EVENT-SCAN-STARTED
  <3>CTRL-EVENT-SCAN-RESULTS
  <3>WPS-AP-AVAILABLE
  <4>Failed to initiate sched scan
  <3>CTRL-EVENT-NETWORK-NOT-FOUND
  <3>CTRL-EVENT-SCAN-STARTED
  <3>CTRL-EVENT-SCAN-RESULTS
  <3>WPS-AP-AVAILABLE
  <4>Failed to initiate sched scan
  <3>CTRL-EVENT-NETWORK-NOT-FOUND
  > list_networks
  network id / ssid / bssid / flags
  0       Adan    any
  1       zengjianfeng    any
  2       HUAWEI-FPHZ5J   any
  <3>CTRL-EVENT-SCAN-STARTED
  <3>CTRL-EVENT-SCAN-RESULTS
  <3>WPS-AP-AVAILABLE
  <4>Failed to initiate sched scan
  <3>CTRL-EVENT-NETWORK-NOT-FOUND
  <3>CTRL-EVENT-SCAN-STARTED
  > set
  set          set_cred     set_network
  > set
  set          set_cred     set_network
  <3>CTRL-EVENT-SCAN-RESULTS
  <3>WPS-AP-AVAILABLE
  <4>Failed to initiate sched scan
  <3>CTRL-EVENT-NETWORK-NOT-FOUND
  <3>CTRL-EVENT-SCAN-STARTED
  <3>CTRL-EVENT-SCAN-RESULTS
  <3>WPS-AP-AVAILABLE
  <4>Failed to initiate sched scan
  <3>CTRL-EVENT-NETWORK-NOT-FOUND
  > add_network
  3
  <3>CTRL-EVENT-SCAN-STARTED
  <3>CTRL-EVENT-SCAN-RESULTS
  <3>WPS-AP-AVAILABLE
  <3>CTRL-EVENT-NETWORK-NOT-FOUND
  <3>CTRL-EVENT-SCAN-STARTED
  <3>CTRL-EVENT-SCAN-RESULTS
  <3>WPS-AP-AVAILABLE  "zengj
  <3>CTRL-EVENT-NETWORK-NOT-FOUND
  > set_network 3 ssid "zengjf"
  OK
  <3>CTRL-EVENT-SCAN-STARTED
  <3>CTRL-EVENT-SCAN-RESULTS
  <3>WPS-AP-AVAILABLE
  <4>Failed to initiate sched scan
  <3>CTRL-EVENT-NETWORK-NOT-FOUND
  <3>CTRL-EVENT-SCAN-STARTED
  > set_network 3 psk "zjf199042"
  OK
  <3>CTRL-EVENT-SCAN-RESULTS
  <3>WPS-AP-AVAILABLE
  <4>Failed to initiate sched scan
  <3>CTRL-EVENT-NETWORK-NOT-FOUND
  <3>CTRL-EVENT-SCAN-STARTED
  > select_network 3
  OK
  <3>CTRL-EVENT-SCAN-RESULTS
  <3>WPS-AP-AVAILABLE
  <3>Trying to associate with SSID 'zengjf'
  <3>CTRL-EVENT-ASSOC-REJECT bssid=00:00:00:00:00:00 status_code=16
  <3>CTRL-EVENT-SCAN-STARTED
  <3>CTRL-EVENT-SCAN-RESULTS
  <3>WPS-AP-AVAILABLE
  <3>Trying to associate with SSID 'zengjf'
  <3>Associated with c4:9f:4c:b3:3b:52
  <3>CTRL-EVENT-CONNECTED - Connection to c4:9f:4c:b3:3b:52 completed [id=3 id_str=]
  <3>CTRL-EVENT-SUBNET-STATUS-UPDATE status=0
  <3>CTRL-EVENT-REGDOM-CHANGE init=COUNTRY_IE type=COUNTRY alpha2=CN
  <3>CTRL-EVENT-SCAN-STARTED
  <3>CTRL-EVENT-SCAN-RESULTS
  > quit
  ```

## 总结

* WiFi内部已经支持了各种加密方式，但由于WiFi通讯无线的特殊性，导致需要用户能够将一些加密信息加入连接中，而wpa_supplicant相当于实现了有线网卡的PHY自动握手那些工作；
* wpa_supplicant提供数据在无线链路层的数据传输方式的设置工具；
* wpa_cli是命令行用于连接WiFi的工具，他是和wpa_supplicant进行通信的；
* AP: Access Point
* STA: Station
