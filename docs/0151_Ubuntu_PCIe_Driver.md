# Ubuntu PCIe Driver

尝试一下以前的PCIe卡在X86机器上跑起来

## 环境搭建

* cat /etc/issue
  ```
  Ubuntu 18.04.1 LTS
  ```
* sudo apt-get update && sudo apt-get install linux-headers-`uname -r`
* sudo apt-get install build-essential kernel-package libncurses5-dev libssl-dev libelf-dev 
* sudo apt-get install vim ack git
* sudo apt-get install sparse
* `uname -r`
  * 4.15.0-29-generic
* 如果需要单独下载内核：
  * sudo apt-get install linux-source-4.15.0
    * cd /usr/src
      * linux-source-4.15.0.bz2
  * ls /usr/src/
    ```
    linux-headers-4.15.0-29  linux-headers-4.15.0-29-generic  linux-source-4.15.0  linux-source-4.15.0.tar.bz2
    ```

## PCIe驱动

* 参考：
  * https://github.com/ZengjfOS/Khadas/blob/master/docs/0008_PCIe.md
  * https://github.com/ZengjfOS/Khadas/blob/master/docs/0011_Altera_PCIe.md
* 驱动：
  * https://github.com/ZengjfOS/Khadas/tree/x86_PCIe_driver
