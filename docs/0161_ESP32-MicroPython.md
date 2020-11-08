# ESP32-MicroPython

感觉MicroPython做玩具还是挺不错的选择，不用交叉编译，直接调试逻辑

## 参考文档

* [开始在ESP32上使用MicroPython](https://docs.singtown.com/micropython/zh/latest/esp32/esp32/tutorial/intro.html)
* [ESP32 / ESP8266 运行脚本MicroPython教程](https://blog.csdn.net/ayfen/article/details/109462617)

## 固件下载

* [Firmware for Generic ESP32 module](http://micropython.org/download/esp32/)
* esptool.py --chip esp32 --port /dev/ttyUSB0 write_flash -z 0x1000 esp32-idf4-20201108-unstable-v1.13-150-gb7883ce74.bin 

## minicom python终端交互

* sudo apt-get install minicom
* 波特率：115200
* sudo minicom -s
  ```
  Welcome to minicom 2.7.1
  
  OPTIONS: I18n
  Compiled on Aug 13 2017, 15:25:34.
  Port /dev/ttyUSB0, 10:21:12
  
  Press CTRL-A Z for help on special keys
  
  ets Jul 29 2019 12:21:46
  
  rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
  configsip: 0, SPIWP:0xee
  clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
  mode:DIO, clock div:2
  load:0x3fff0018,len:4
  load:0x3fff001c,len:5148
  load:0x40078000,len:12880
  load:0x40080400,len:3484
  entry 0x40080630
  MicroPython v1.13-150-gb7883ce74 on 2020-11-08; ESP32 module with ESP32
  Type "help()" for more information.
  >>> print ("Hello World From ESP32 MicroPython")
  Hello World From ESP32 MicroPython
  >>>
  ```

## 运行脚本

* https://docs.micropython.org/en/latest/esp32/quickref.html#general-board-control
* sudo pip3 install adafruit-ampy
* main.py
  ```
  import esp
  
  print(esp.flash_size())
  ```
* ampy --port /dev/ttyUSB0 run main.py
  ```
  4194304
  ```
* 如上ampy的put命令并不会保存main.py脚本到文件系统，只是在内存中运行一下

## 开机自动运行脚本

* [运行您的首个脚本](https://docs.singtown.com/micropython/zh/latest/moxingstm32f4/moxingstm32f4/tutorial/script.html)
* ampy --port /dev/ttyUSB0 put main.py
* 重启
  * 重启前开启：sudo minicom -s
    ```
    Welcome to minicom 2.7.1
    
    OPTIONS: I18n
    Compiled on Aug 13 2017, 15:25:34.
    Port /dev/ttyUSB0, 11:18:59
    
    Press CTRL-A Z for help on special keys
    
    ets Jul 29 2019 12:21:46
    
    rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
    configsip: 0, SPIWP:0xee
    clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
    mode:DIO, clock div:2
    load:0x3fff0018,len:4
    load:0x3fff001c,len:5148
    load:0x40078000,len:12880
    load:0x40080400,len:3484
    entry 0x40080630
    4194304
    MicroPython v1.13-150-gb7883ce74 on 2020-11-08; ESP32 module with ESP32
    Type "help()" for more information.
    >>>
    ```
  * 4194304
* 查看一下文件系统main.py内容：
  ```python
  >>> import os
  >>> os.listdir()
  ['boot.py', 'data.txt', 'main.py']
  >>> f = open('main.py')
  >>> f.read()
  'import esp\n\nprint(esp.flash_size())\n'
  >>> f.close()
  >>>
  ```
