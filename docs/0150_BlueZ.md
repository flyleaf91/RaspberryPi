# BlueZ

可用于测试Android蓝牙通信或者协议栈修改，譬如安全方面的修改，理解just_works


## 参考文档

* [HCI Bluetooth Module SPP Connection on Linux](https://connectivity-staging.s3.us-east-2.amazonaws.com/s3fs-public/2018-10/HCI%20Bluetooth%20Module%20SPP%20Connection%20on%20Linux%20v1_0.pdf)
* [Setting Up Bluetooth Serial Port Profile on Raspberry Pi using sdptool](https://scribles.net/setting-up-bluetooth-serial-port-profile-on-raspberry-pi/)
* [Android 9.0 Bluetooth源码分析（一）蓝牙开启流程](https://www.jianshu.com/p/a150d55e29ca)
* [Android 9.0 Bluetooth源码分析（二）蓝牙扫描流程](https://www.jianshu.com/p/4ce366089c1d)
* [Android 9.0 Bluetooth源码分析（三）蓝牙配对流程](https://www.jianshu.com/p/0b748b11fa62)
* [Core_v4.2.pdf](refers/Core_v4.2.pdf)
* [Core_v5.0.pdf](refers/Core_v5.0.pdf)


## 协议栈说明

常用的两种协议栈说明如下

* BlueZ is Official Linux Bluetooth protocol stack
* Bluedroid is a stack provided by Broadcom and is now opensource in android. 


## L2CAP

https://www.amd.e-technik.uni-rostock.de/ma/gol/lectures/wirlec/bluetooth_info/l2cap.html

Two link types are supported for the Baseband layer : Synchronous Connection-Oriented (SCO) links and Asynchronous Connection-Less (ACL) links. SCO links support real-time voice traffic using reserved bandwidth. ACL links support best effort traffic. The L2CAP Specification is defined for only ACL links and no support for SCO links is planned.

如上所述，L2CAP层目前只有ACL这种链接实现

L2CAP must support protocol multiplexing because the Baseband Protocol does not support any ’type?field identifying the higher layer protocol being multiplexed above it. L2CAP must be able to distinguish between upper layer protocols such as the Service Discovery Protocol , RFCOMM , and Telephony Control.

如上所述，L2CAP层区分SDP、RFCOMM、TC协议

L2CAP负责适配基带中的上层协议，它同LM并行工作，向上层协议提供面向连接和无连接的数据服务，并提供多路复用，分段和重组操作，允许高层次的协议和应用能够以64KB的长度发送和接收数据包(L2CAP Serveice Data Units, SDU)

L2CAP提供了逻辑信道，名为L2CAP Channels，即在一个或多个逻辑链路上进行多路复用，可以认为是向上提供socket的port的那种


## SDP

https://www.amd.e-technik.uni-rostock.de/ma/gol/lectures/wirlec/bluetooth_info/sdp.html


## Bluetooth Profiles

https://www.amd.e-technik.uni-rostock.de/ma/gol/lectures/wirlec/bluetooth_info/profiles.html

![Bluetooth_Profiles_Dependence.png](images/Bluetooth_Profiles_Dependence.png)

* Generic Access Profile: 处理握手、配对、扫描、发现、安全连接，这部分貌似只能配置，他主要是Host Controller里面，和Wifi的配置差不多概念
* Serial Port Profile: 很多Profile是基于SPP Profile
* Service Discovery Protocol: 主要是提供一个查询机器支持哪些Profile信息功能；
* TCS: 了解不多


## 蓝牙控制器版本

* `hciconfig -a`
  ```
  hci0:   Type: Primary  Bus: UART
          BD Address: DC:A6:32:B2:F8:FF  ACL MTU: 1021:8  SCO MTU: 64:1
          UP RUNNING PSCAN
          RX bytes:1823697 acl:20935 sco:0 events:39002 errors:0
          TX bytes:505283 acl:20982 sco:0 commands:2828 errors:0
          Features: 0xbf 0xfe 0xcf 0xfe 0xdb 0xff 0x7b 0x87
          Packet type: DM1 DM3 DM5 DH1 DH3 DH5 HV1 HV2 HV3
          Link policy: RSWITCH SNIFF
          Link mode: SLAVE ACCEPT
          Name: 'raspberrypi'
          Class: 0x480000
          Service Classes: Capturing, Telephony
          Device Class: Miscellaneous,
          HCI Version: 5.0 (0x9)  Revision: 0x122
          LMP Version: 5.0 (0x9)  Subversion: 0x6119
          Manufacturer: Cypress Semiconductor Corporation (305)
  ```
* HCI Version: 5.0 (0x9)  Revision: 0x122
* LMP Version: 5.0 (0x9)  Subversion: 0x6119

蓝牙版本对照表如下：

 HCI version | Bluetooth version 
-------------|-------------------
 0 (0x0)     | 1.0b
 1 (0x1)     | 1.1
 2 (0x2)     | 1.2
 3 (0x3)     | 2.0
 4 (0x4)     | 2.1
 5 (0x5)     | 3.0
 6 (0x6)     | 4.0
 7 (0x7)     | 4.1
 8 (0x8)     | 4.2
 9 (0x9)     | 5.0
 10 (0xa)    | 5.1


## 蓝牙配对模式

* 参考：
  * [Raspberry BLE Encryption / Pairing](https://stackoverflow.com/questions/62147384/raspberry-ble-encryption-pairing/62242352#62242352)
  * [蓝牙配对模式？](https://www.zhihu.com/question/29076831)
    * `Numeric Comparison`：适用于两个设备都可以显示六位数字并且能够让用户输入"Yes"或"No"的情况；在这个模型中，有针对MITM的保护，故而即使知道这六位数字对解密数据也没有意义；这也是Android中蓝牙常用的配对模式。例如手机之间的配对。
    * `Just Works`：适用于两个设备都没有任何输入和输出能力的情况；它使用与数字比较相同的协议，但它不向用户显示任何数字，也不要求确认这些数字；该模型不提供针对MITM的保护。用于配对没有显示没有输入的设备，主动发起连接即可配对，用户看不到配对过程。例如连接蓝牙耳机。
    * `Passkey Entry`: 适用于一个设备具有数字键盘但没有显示器且另一个设备至少具有数字输出的情况；在配对过程中，带显示屏的设备显示一个6位数字，另一个设备必须通过键盘进行输入
    * `Out of Band`：两设备的通过别的途径交换配对信息，例如NFC等。例如一些NFC蓝牙音箱。
* 这四种配对模式，在`Classic`和`LE`中都有，这四种配对方式，除开JUSTWORK外，都可以防止这两种攻击。JUSTWORK由于不涉及人机交互，所以没法防止MITM的中间人攻击。
* BluZ对应的模式
  ```
  bluetoothctl --agent KeyboardOnly
  bluetoothctl --agent KeyboardDisplay
  bluetoothctl --agent NoInputNoOutput
  bluetoothctl --agent DisplayOnly 
  ```
  * `NoInputNoOutput`是`just_works`
* 在修改模式的时候，注意要off，再on才能生效
* 两个设备在配对过程开始时交换其IOCapability。发起方发送IOCapabilityRequest，响应设备使用IOCapabilityResponse进行应答。
* [蓝牙IO Capabilities](https://blog.csdn.net/zmk0810612124/article/details/82661041)
  * 设备的input能力  
    ![Bluetooth_IO_Input.jpg](images/Bluetooth_IO_Input.jpg)
  * 设备的output能力  
    ![Bluetooth_IO_Output.jpg](images/Bluetooth_IO_Output.jpg)
  * 设备的IO Capacity  
    ![Bluetooth_IO_Capacity.jpg](images/Bluetooth_IO_Capacity.jpg)
    * NoInputNoOutput: 设备没有输入和输出的能力
    * DisplayOnly: 设置只有输出显示的能力
    * NoInputNoOutput1: 因为没有一个配对算法可以通过yes和no出入，而且设备不支持输出，所以设备的IO能力定义为没有输入和输出
    * DisplayYesNo: 设置只有输入 YES和NO的能力，能够显示
    * KeyboardOnly: 设备可以输入0-9，确认键 和YES/NO的能力，没有显示的能力
    * KeyboardDisplay: 设备可以输入0-9，确认键 和YES/NO的能力，也有显示的能力
  * Initiator位配对发起方, Responder为配对接收方
    * [BLE协议栈 – SM](https://blog.csdn.net/comprends/article/details/99289615)  
      ![Bluetooth_Just_Works.png](images/Bluetooth_Just_Works.png)


## 查看树莓派支持profile

* sudo sdptool browse local
  ```
  Failed to connect to SDP server on FF:FF:FF:00:00:00: No such file or directory
  ```
* 参考解决方法：[Failed to connect to SDP server on FF:FF:FF:00:00:00: No such file or directory](https://raspberrypi.stackexchange.com/questions/41776/failed-to-connect-to-sdp-server-on-ffffff000000-no-such-file-or-directory)
  * /etc/systemd/system/dbus-org.bluez.service
    * ExecStart=/usr/lib/bluetooth/bluetoothd -C
  * sudo systemctl daemon-reload
  * sudo systemctl restart bluetooth
* sudo sdptool browse local
  ```
  Browsing FF:FF:FF:00:00:00 ...
  Service RecHandle: 0x10000
  Service Class ID List:
    "PnP Information" (0x1200)
  Profile Descriptor List:
    "PnP Information" (0x1200)
      Version: 0x0103
  
  Browsing FF:FF:FF:00:00:00 ...
  Service Search failed: Invalid argument
  Service Name: AVRCP CT
  Service RecHandle: 0x10001
  Service Class ID List:
    "AV Remote" (0x110e)
    "AV Remote Controller" (0x110f)                                                                                                                                                                   [0/535]
  Protocol Descriptor List:
    "L2CAP" (0x0100)
      PSM: 23
    "AVCTP" (0x0017)
      uint16: 0x0103
  Profile Descriptor List:
    "AV Remote" (0x110e)
      Version: 0x0106
  
  Service Name: AVRCP TG
  Service RecHandle: 0x10002
  Service Class ID List:
    "AV Remote Target" (0x110c)
  Protocol Descriptor List:
    "L2CAP" (0x0100)
      PSM: 23
    "AVCTP" (0x0017)
      uint16: 0x0103
  Profile Descriptor List:
    "AV Remote" (0x110e)
      Version: 0x0105
  
  Service Name: Audio Source
  Service RecHandle: 0x10003
  Service Class ID List:
    "Audio Source" (0x110a)
  Protocol Descriptor List:
    "L2CAP" (0x0100)
      PSM: 25
    "AVDTP" (0x0019)
      uint16: 0x0103
  Profile Descriptor List:
    "Advanced Audio" (0x110d)
      Version: 0x0103
  
  Service Name: Headset Voice gateway
  Service RecHandle: 0x10004
  Service Class ID List:
    "Headset Audio Gateway" (0x1112)
    "Generic Audio" (0x1203)
  Protocol Descriptor List:
    "L2CAP" (0x0100)
    "RFCOMM" (0x0003)
      Channel: 12
  Profile Descriptor List:
    "Headset" (0x1108)
      Version: 0x0102
  
  Service Name: Hands-Free Voice gateway
  Service RecHandle: 0x10005
  Service Class ID List:
    "Handsfree Audio Gateway" (0x111f)
    "Generic Audio" (0x1203)
  Protocol Descriptor List:
    "L2CAP" (0x0100)
    "RFCOMM" (0x0003)
      Channel: 13
  Profile Descriptor List:
    "Handsfree" (0x111e)
      Version: 0x0107
  ```


## 支持SPP

* sudo sdptool add SP
  ```
  Serial Port service registered
  ```
* sudo sdptool browse local
  ```
  ...省略
  
  Service Name: Serial Port
  Service Description: COM Port
  Service Provider: BlueZ
  Service RecHandle: 0x10006
  Service Class ID List:
    "Serial Port" (0x1101)
  Protocol Descriptor List:
    "L2CAP" (0x0100)
    "RFCOMM" (0x0003)
      Channel: 1
  Language Base Attr List:
    code_ISO639: 0x656e
    encoding:    0x6a
    base_offset: 0x100
  Profile Descriptor List:
    "Serial Port" (0x1101)
      Version: 0x0100
  ```


## 打开蓝牙

* btmgmt
  * power on

```sh
pi@raspberrypi:~ $ sudo btmgmt
[mgmt]# power on
hci0 Set Powered complete, settings: powered bondable ssp br/edr le secure-conn
hci0 type 7 discovering on
...省略
```


## 作为服务端生成虚拟串口

* sudo bluetoothctl
  * discoverable on
    ```
    Changing discoverable on succeeded
    [CHG] Controller DC:A6:32:B2:F8:FF Discoverable: yes
    ```
  * show
    ```
    Controller DC:A6:32:B2:F8:FF (public)
            Name: raspberrypi
            Alias: raspberrypi
            Class: 0x00480000
            Powered: yes
            Discoverable: yes
            Pairable: yes
            UUID: Headset AG                (00001112-0000-1000-8000-00805f9b34fb)
            UUID: Generic Attribute Profile (00001801-0000-1000-8000-00805f9b34fb)
            UUID: A/V Remote Control        (0000110e-0000-1000-8000-00805f9b34fb)
            UUID: Generic Access Profile    (00001800-0000-1000-8000-00805f9b34fb)
            UUID: PnP Information           (00001200-0000-1000-8000-00805f9b34fb)
            UUID: A/V Remote Control Target (0000110c-0000-1000-8000-00805f9b34fb)
            UUID: Audio Source              (0000110a-0000-1000-8000-00805f9b34fb)
            UUID: Handsfree Audio Gateway   (0000111f-0000-1000-8000-00805f9b34fb)
            Modalias: usb:v1D6Bp0246d0532
            Discovering: no
    ```
  * 查看手机蓝牙是否能扫描到`raspberrypi`
  * 一段时间后`Discoverable`会被关闭，可以通过上面的`show`命令进行查看
  * 像网卡一样ping一下设备：`sudo l2ping 56:A6:46:F7:D6:FA`
    ```
    Ping: 56:A6:46:F7:D6:FA from DC:A6:32:B2:F8:FF (data size 44) ...
    44 bytes from 56:A6:46:F7:D6:FA id 0 time 8.98ms
    44 bytes from 56:A6:46:F7:D6:FA id 1 time 42.10ms
    44 bytes from 56:A6:46:F7:D6:FA id 2 time 33.61ms
    44 bytes from 56:A6:46:F7:D6:FA id 3 time 32.41ms
    44 bytes from 56:A6:46:F7:D6:FA id 4 time 49.84ms
    44 bytes from 56:A6:46:F7:D6:FA id 5 time 179.93ms
    ^C6 sent, 6 received, 0% loss
    ```
* sudo rfcomm watch hci0
  ```
  Waiting for connection on channel 1
  Connection from 56:A6:46:F7:D6:FA to /dev/rfcomm0
  Press CTRL-C for hangup
  ```
* 打开Android蓝牙串口APP作为Client
* sudo rfcomm -a
  ```
  rfcomm0: DC:A6:32:B2:F8:FF -> 56:A6:46:F7:D6:FA channel 1 connected [reuse-dlc release-on-hup tty-attached]
  ```


## 作为客户端生成虚拟串口

* 打开Android蓝牙串口APP作为Server
* sudo bluetoothctl
  * scan on
  * pair 56:A6:46:F7:D6:FA
* 查看服务端SPP协议对应的通道：sdptool records 56:A6:46:F7:D6:FA
  * [Linux Bluez RFCOMM: Connection Refused](https://stackoverflow.com/questions/52145779/linux-bluez-rfcomm-connection-refused)
    ```
    ...省略
  
    Service Name: BlueSPP SPP
    Service RecHandle: 0x1000e
    Service Class ID List:
      "Serial Port" (0x1101)
    Protocol Descriptor List:
      "L2CAP" (0x0100)
      "RFCOMM" (0x0003)
        Channel: 4
    Profile Descriptor List:
      "Serial Port" (0x1101)
        Version: 0x0102
    ```
    * Channel: 4
* sudo rfcomm release hci0
  * [Can't create RFCOMM TTY: Address already in use](https://stackoverflow.com/questions/46735997/cant-create-rfcomm-tty-address-already-in-use)
* sudo rfcomm connect hci0 56:A6:46:F7:D6:FA 4
  ```
  Connected /dev/rfcomm0 to 56:A6:46:F7:D6:FA on channel 4
  Press CTRL-C for hangup
  ^CDisconnected
  ```
* rfcomm -a
  ```
  rfcomm0: DC:A6:32:B2:F8:FF -> 56:A6:46:F7:D6:FA channel 4 connected [reuse-dlc release-on-hup tty-attached]
  ```
* 注意`sudo sdptool browse local`是用来看本地的`channel`号，因为我们要连接的远程的服务，所以要查看远程服务的`channel`号，可以认为`channel`号是socket通信中的port号，Android手机的APP打开的这个`channel`号是不固定的，所以需要`sdptool records 56:A6:46:F7:D6:FA`查看确认一下；


## 串口通信

* sudo minicom -s
  * /dev/rfcomm0
  * 9600 8N1
* 退出：`ctrl + A` + `q`

![Bluetooth_rfcomm0_Android_SPP_Communication.png](images/Bluetooth_rfcomm0_Android_SPP_Communication.png)


## wireshark数据分析

保存蓝牙通信数据：`sudo btmon -w btsnoop_outfile`

![Bluetooth_RFCOMM_PSM_Wireshark.png](images/Bluetooth_RFCOMM_PSM_Wireshark.png)

* `Source`/`Destination`字段
  * `Controller`: 表示HCI接口下面的蓝牙控制器
  * `Host`: 表示HCI接口上面的蓝牙协议栈
  * `localhost()`: 表示本机`Profile`级别的数据
  * `remote()`或`蓝牙地址`: 表示目标机器`Profile`级别的数据


## Android BlueDroid协议栈

### 架构运行图

![fluoride_architecture.png](images/fluoride_architecture.png)

### 参考文档

* [Android 9.0 Bluetooth源码分析（一）蓝牙开启流程](https://www.jianshu.com/p/a150d55e29ca)
* [Android 9.0 Bluetooth源码分析（二）蓝牙扫描流程](https://www.jianshu.com/p/4ce366089c1d)
* [Android 9.0 Bluetooth源码分析（三）蓝牙配对流程](https://www.jianshu.com/p/0b748b11fa62)
