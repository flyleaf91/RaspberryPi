# Wifi Strength RSSI

Wifi信号强度RSSI(Received Signal Strength Indication)

## 参考文档

* [Android-WiFi开发之 WiFi信号强度](https://www.jianshu.com/p/cb2827c4bf17)
* [android wifi RSSI达到阈值自动断开](https://www.cnblogs.com/helloworldtoyou/p/9183905.html)
* [RSSI](https://blog.csdn.net/neilengineer/article/details/46002537/)
* [android中 获取WiFi信息并计算wifi的信号强度](https://blog.csdn.net/wang1588143/article/details/6653475)

## wpa_supplicant查看信号强度

* wpa_cli -i wlan0
  * scan_results
    ```
    bssid / frequency / signal level / flags / ssid
    04:d3:b5:e5:a3:0c       5745    -41     [WPA2-PSK-CCMP][WPS][ESS]       zengjf
    48:4c:86:6d:72:c4       5745    -55     [WPA-PSK-CCMP+TKIP][WPA2-PSK-CCMP+TKIP][WPS][ESS]       HUAWEI-F9AZ7L_HiLink
    60:3a:7c:da:c3:78       5805    -70     [WPA-PSK-CCMP][WPA2-PSK-CCMP][ESS]      NEVER_MO
    04:d3:b5:e5:a3:0d       2437    -21     [WPA2-PSK-CCMP][WPS][ESS]
    04:d3:b5:e5:a3:08       2437    -21     [WPA2-PSK-CCMP][WPS][ESS]       zengjf
    74:05:a5:9f:97:1b       2437    -57     [WPA-PSK-CCMP][WPA2-PSK-CCMP][ESS]      ali
    9c:21:6a:a9:8d:d8       2462    -56     [WPA-PSK-CCMP][WPA2-PSK-CCMP][WPS][ESS] 52-406
    54:e0:61:a9:d6:29       2452    -29     [WPA-PSK-CCMP+TKIP][WPA2-PSK-CCMP+TKIP][WPS][ESS]       ChinaNet-L267
    48:4c:86:6d:72:c0       2437    -38     [WPA-PSK-CCMP+TKIP][WPA2-PSK-CCMP+TKIP][WPS][ESS]       HUAWEI-F9AZ7L_HiLink
    50:64:2b:e7:2e:67       2417    -58     [WPA-PSK-CCMP+TKIP][WPA2-PSK-CCMP+TKIP][WPS][ESS]       Xiaomi_2E66
    84:74:60:98:bd:d8       2447    -71     [WPA-PSK-CCMP+TKIP][WPA2-PSK-CCMP+TKIP][WPS][ESS]       ChinaNet-kaGa
    78:eb:14:b2:45:6a       2412    -57     [WPA-PSK-CCMP][WPA2-PSK-CCMP][ESS]      206
    f8:df:a8:f3:77:18       2462    -66     [WPA-PSK-CCMP][WPA2-PSK-CCMP][WPS][ESS] ChinaNet-USG6
    dc:fe:18:c4:85:6d       2412    -81     [WPA-PSK-CCMP][WPA2-PSK-CCMP][ESS]      TP-LINK_304
    74:05:a5:9f:97:1d       5745    -77     [WPA-PSK-CCMP][WPA2-PSK-CCMP][ESS]      ali
    78:11:dc:58:5b:96       2462    -76     [WPA-PSK-CCMP+TKIP][WPA2-PSK-CCMP+TKIP][WPS][ESS]       xiaoluo
    48:4c:86:6d:72:c5       2437    -37     [WPA2-PSK-CCMP][WPS][ESS]
    48:4c:86:6d:72:c1       2437    -38     [WPA2-PSK-CCMP][WPS][ESS]
    c0:a5:dd:a1:28:fa       2412    -82     [WPA-PSK-CCMP][WPA2-PSK-CCMP][WPS][ESS] MERCURY_79303
    94:d9:b3:76:81:31       2437    -83     [WPA-PSK-CCMP][WPA2-PSK-CCMP][ESS]
    40:f4:20:ae:61:ca       2452    -78     [WPA-PSK-CCMP+TKIP][WPA2-PSK-CCMP+TKIP][WPS][ESS]       ChinaNet-marlon
    fc:ab:90:e1:ce:ed       2437    -80     [WPA2-PSK-CCMP][WPS][ESS]
    54:2b:de:eb:fa:7a       2412    -78     [ESS]
    7e:b5:9b:26:7a:ec       2412    -77     [WPA-PSK-CCMP][WPA2-PSK-CCMP][ESS]
    00:4b:f3:22:8c:60       2472    -79     [WPA-PSK-CCMP][WPA2-PSK-CCMP][ESS]      MERCURY_8C60
    ```
  * signal_poll
    ```
    RSSI=-41
    LINKSPEED=24
    NOISE=9999
    FREQUENCY=5745
    WIDTH=40 MHz
    CENTER_FRQ1=5755
    ```
* 如上可知，RSSI也就是signal level，Wifi Scan的时候就能获取到信号的强度信息，并提供给上层进行分析显示；

## Android Wifi Settings Show BSSID

* [开发者选项] --> [NETWORKING] --> [Enable Wi-Fi Verbose Logging] -> ON
