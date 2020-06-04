# Wifi BSSID

查看特定Wifi AP的BSSID(MAC ADDRESS)

## 获取特定AP的BSSID

其实之前都不知道BSSID是什么，之前看过，但是忘了，由于Android系统版本问题，接口获取不到BSSID，于是现在树莓派上测试一下是不是Scan阶段就已经获取了BSSID，再在Android系统上做测试；

`wpa_cli -i wlan0`
```
> scan_results
bssid / frequency / signal level / flags / ssid
d4:68:ba:b0:37:cc       5805    -54     [WPA-EAP-CCMP][WPA2-EAP-CCMP][ESS]      CDOTA
d4:68:ba:b8:37:cc       5805    -54     [WPA-EAP-CCMP][WPA2-EAP-CCMP][ESS]
8c:a6:df:d1:a5:df       5745    -66     [WPA-PSK-CCMP][WPA2-PSK-CCMP][ESS]      TP-LINK_5G_A5DD
d4:68:ba:08:37:cc       2437    -53     [WPA-PSK-CCMP][WPA2-PSK-CCMP][ESS]      6F_TEST
d4:68:ba:38:37:cc       2437    -54     [WPA-EAP-CCMP][WPA2-EAP-CCMP][ESS]      CDOTA
28:c6:8e:71:bb:52       2417    -53     [WPA2-PSK-CCMP][WPS][ESS]       HappyFamily
d4:68:ba:40:37:cc       2437    -53     [WPA-EAP-CCMP][WPA2-EAP-CCMP][ESS]
28:c6:8e:71:bb:51       5765    -66     [WPA2-PSK-CCMP][WPS][ESS]       HappyFamily-5G
...省略
> bss CDOTA
id=0
bssid=d4:68:ba:80:37:cc
freq=5805
beacon_int=100
capabilities=0x1511
qual=0
noise=-92
level=-53
tsf=0000000000000000
...省略
```
