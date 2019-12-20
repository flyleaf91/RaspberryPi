# WiFi AP

由于OTA测试需要用到一个指定IP进行测试，于是暂时使用树莓派WiFI做一个AP，再加一个Apache2作为web服务端。

**需要注意的是如果没有做数据转发情况下，Android手机会出现连接AP没有网络，然后继续使用4G流量，导致用浏览器无法访问到WiFi的IP，所以测试的时候要关掉手机4G流量。**

## 参考文档

* [Setting up a Raspberry Pi as a Wireless Access Point](https://www.raspberrypi.org/documentation/configuration/wireless/access-point.md)
* [0047_HTTP_Auth.md](docs/0047_HTTP_Auth.md)

## steps

* sudo apt install dnsmasq hostapd
* sudo systemctl stop dnsmasq
* sudo systemctl stop hostapd
* sudo vim /etc/dhcpcd.conf
  ```
  [...省略]
  interface wlan0
      static ip_address=192.168.4.1/24
      nohook wpa_supplicant
  ```
* sudo service dhcpcd restart
* sudo mv /etc/dnsmasq.conf /etc/dnsmasq.conf.orig
* sudo vim /etc/dnsmasq.conf
  ```
  interface=wlan0      # Use the require wireless interface - usually wlan0
  dhcp-range=192.168.4.2,192.168.4.20,255.255.255.0,24h
  ```
* sudo systemctl reload dnsmasq
* sudo vim /etc/hostapd/hostapd.conf
  ```
  interface=wlan0
  driver=nl80211
  ssid=NameOfNetwork
  hw_mode=g
  channel=7
  wmm_enabled=0
  macaddr_acl=0
  auth_algs=1
  ignore_broadcast_ssid=0
  wpa=2
  wpa_passphrase=zengjf123456
  wpa_key_mgmt=WPA-PSK
  # wpa_pairwise=TKIP
  rsn_pairwise=CCMP
  ```
* sudo vim /etc/default/hostapd
  ```
  DAEMON_CONF="/etc/hostapd/hostapd.conf"
  ```
* sudo systemctl unmask hostapd
* sudo systemctl enable hostapd
* sudo systemctl start hostapd
* reboot
* sudo systemctl status hostapd
* sudo systemctl status dnsmasq
* netstat -aon | grep "80"


## Disable AP

* sudo systemctl disable hostapd
* sudo systemctl disable dnsmasq
* sudo vim /etc/dhcpcd.conf
  ```
  [...省略]
  # interface wlan0
  #     static ip_address=192.168.4.1/24
  #     nohook wpa_supplicant
  ```
* reboot