# README

树莓派应该算是目前开源硬件里学习嵌入式Linux系统最好的工具，里面的设计思路和一些工具是很值得借鉴的，这里主要使用Raspberry Pi ZERO W和Raspberry Pi 4B进行系统架构分析。

之前在使用树莓派的过程中有记录一些东西，不过没有进行全面系统性的分析，相对比较零散。

[博客园 - 随笔分类 - Raspberry Pi](https://www.cnblogs.com/zengjfgit/category/783268.html)

## ZERO W接口原理图

![docs/images/RPI_Zero_W_40_Pin.png](docs/images/RPI_Zero_W_40_Pin.png)

## 参考文档

* [Raspberry Pi](https://www.raspberrypi.org/)
* [Raspberry Pi On GitHub](https://github.com/raspberrypi)
* [Raspberry Pi Documentation](https://github.com/raspberrypi/documentation)
* [Raspberry Pi Pinout](https://pinout.xyz/pinout/uart)
* [systemd](https://github.com/systemd/systemd)
* https://github.com/ZengjfOS/Android

## 笔记文档

NO.|文件名称|摘要
:--:|:--|:--
0177| [BT_HCI_Command.md](docs/0177_BT_HCI_Command.md) | 理解蓝牙HCI命令格式，看懂QBQ认证HCI测试命令
0176| [USB_gadget_serial_configfs.md](docs/0176_USB_gadget_serial_configfs.md) | 分析Android USB gadget串口配置
0175| [SELinux_audit2allow.md](docs/0175_SELinux_audit2allow.md) | 使用audit2allow处理avc权限
0174| [Android_CMD_gtest.md](docs/0174_Android_CMD_gtest.md) | gtest单元测试so库
0173| [Hardware_Interrupts_Counter.md](docs/0173_Hardware_Interrupts_Counter.md) | 通过硬件中断统计，可以查看中断是否发生，驱动查看中断触发判定一些信息
0172| [tcp_dump.md](docs/0172_tcp_dump.md) | TCP Server抓包
0171| [Windows_ls.md](docs/0171_Windows_ls.md) | 习惯了Linux，在Windows支持ls命令
0170| [Android_cc-test.md](docs/0170_Android_cc-test.md) | 分析如何利用Android的cc-test
0169| [Android_RefBase_sp_wp.md](docs/0169_Android_RefBase_sp_wp.md) | 理解Android强指针、弱指针，将sp、wp理解为RefBase的容器更好理解
0168| [gtest.md](docs/0168_gtest.md) | 尝试使用gtest，便于以后分析Android底层test case
0167| [eth0_dhcp_Server.md](docs/0167_eth0_dhcp_Server.md) | 搭建dhcp服务用于测试
0166| [Windows_SMB_4_iPhone.md](docs/0166_Windows_SMB_4_iPhone.md) | 将iPhone中的视频和照片共享出来
0165| [Flask_OpenCV_Face_Detect.md](docs/0165_Flask_OpenCV_Face_Detect.md) | Flask作为HTTP视频流，OpenCV识别摄像头采集的人脸
0164| [Led_Button.md](docs/0164_Led_Button.md) | Led&Button板控制
0163| [esp-who.md](docs/0163_esp-who.md) | 搭建esp-who环境，测试web camera
0162| [ESP32_BREDR_SPP_Server.md](docs/0162_ESP32_BREDR_SPP_Server.md) | 理解BlueDroid(Fluoride)蓝牙协议栈，分析BREDR SPP Server工作原理
0161| [ESP32-MicroPython.md](docs/0161_ESP32-MicroPython.md) | 感觉MicroPython做玩具还是挺不错的选择，不用交叉编译，直接调试逻辑
0160| [ESP32_BLE_SPP_Server.md](docs/0160_ESP32_BLE_SPP_Server.md) | 理解BlueDroid(Fluoride)蓝牙协议栈，为了理解Android蓝牙协议栈，分析BLE SPP Server工作原理
0159| [pip_source_modify.md](docs/0159_pip_source_modify.md) | pip安装软件的时候经常会出现超时导致无法安装
0158| [ESP32-DevKitC.md](docs/0158_ESP32-DevKitC.md) | 尝试用树莓派处理ESP32-DevKitC
0157| [sha256_init_update_final.md](docs/0157_sha256_init_update_final.md) | sha256是可以分批处理输入的，满足数据不是一次性处理完的场合
0156| [Bluetooth_Core_Analyse_Pair_Bond.md](docs/0156_Bluetooth_Core_Analyse_Pair_Bond.md) | 了解蓝牙配对流程到底那里来的，谁规定的，在哪里看
0155| [Fastboot_flash_Sparse_Image.md](docs/0155_Fastboot_flash_Sparse_Image.md) | 分析fastboot命令flash文件原理，理解sparse image原理
0154| [CC2541_SimpleBLEPeripheral.md](docs/0154_CC2541_SimpleBLEPeripheral.md) | 理解单片机中的Bluetooth GATT到底是怎么工作的
0153| [btmon_HCI_ACL.md](docs/0153_btmon_HCI_ACL.md) | 理解Bluetooth HCI及BTSnoop是什么
0152| [Deep_Sleep.md](docs/0152_Deep_Sleep.md) | 深睡眠机制，貌似树莓派上没使用
0151| [Ubuntu_PCIe_Driver.md](docs/0151_Ubuntu_PCIe_Driver.md) | 尝试一下以前的PCIe卡在X86机器上跑起来
0150| [BlueZ.md](docs/0150_BlueZ.md) | 可用于测试Android蓝牙通信或者协议栈修改，譬如安全方面的修改，理解just_works
0149| [Linux_Lock.md](docs/0149_Linux_Lock.md) | 常见的几种内核驱动涉及的锁，理解原子操作比较重要
0148| [ARM_SWI.md](docs/0148_ARM_SWI.md) | SWI指令引起软件中断异常，为操作系统应用程序调用系统接口提供的一种机制
0147| [Android_AVB_vbmeta_public_key.md](docs/0147_Android_AVB_vbmeta_public_key.md) | Android AVB启动vbmeta如何确保安全？
0146| [printf_Hex_Format.md](docs/0146_printf_Hex_Format.md) | 进行二进制数据查看的时候常用的16 byte对齐输出参考
0145| [Makefile_Assignment.md](docs/0145_Makefile_Assignment.md) | Makefile赋值`=`/`:=`/`?=`/`+=`区别
0144| [Multiple_Project_Auto_Dir.md](docs/0144_Multiple_Project_Auto_Dir.md) | 解决多个Android BSP源代基准目录跳转问题
0143| [Process_Swith.md](docs/0143_Process_Swith.md) | 如果每个进程地址空间都是4G，MMU做虚拟地址映射，每次进程切换都要切换映射表？
0142| [Kernel_Float_Calculation.md](docs/0142_Kernel_Float_Calculation.md) | 内核浮点运算
0141| [ARMv8_backtrace_Analysis.md](docs/0141_ARMv8_backtrace_Analysis.md) | ARMv8汇编分析，Android backtrace分析
0140| [ARM_CPU_Refer_Docs.md](docs/0140_ARM_CPU_Refer_Docs.md) | CPU方面的一些文档参考
0139| [Linux_Splice.md](docs/0139_Linux_Splice.md) | 理解零拷贝有助于理解Android Binder通信
0138| [Wifi_Beacon.md](docs/0138_Wifi_Beacon.md) | Wifi的心跳包
0137| [dmesg_grep_realtime.md](docs/0137_dmesg_grep_realtime.md) | 像logcat那样看内核log
0136| [Wifi_Strength_RSSI.md](docs/0136_Wifi_Strength_RSSI.md) | Wifi信号强度RSSI(Received Signal Strength Indication)
0135| [Android_fstrace.md](docs/0135_Android_fstrace.md) | Android下如何使用ftrace
0134| [Capture_ftrace_event.md](docs/0134_Capture_ftrace_event.md) | 手动操作一下获取ftrace event并转换到kernelshark显示
0133| [Wireshark_Bluetooth_HCI.md](docs/0133_Wireshark_Bluetooth_HCI.md) | 使用Wireshark分析BT HCI(类比到Wifi nl80211)
0132| [Qemu.md](docs/0132_Qemu.md) | 尝试一下Qemu启动init文件系统
0131| [OP-TEE.md](docs/0131_OP-TEE.md) | 理解OP-TEE工作原理
0130| [sftp_transfer_file.md](docs/0130_sftp_transfer_file.md) | sftp上传文件
0129| [RK_jar_unpack_pack.md](docs/0129_RK_jar_unpack_pack.md) | RK镜像及Jar打包、解包
0128| [John.md](docs/0128_John.md) | 学习John破解密码怎么做的
0127| [HTTPS_SSL_Server_Client.md](docs/0127_HTTPS_SSL_Server_Client.md) | 尝试搭建自己签名服务器和访问的证书
0126| [crontab_timer_for_build.md](docs/0126_crontab_timer_for_build.md) | Linux定时编译任务，针对git
0125| [git_staged_patch.md](docs/0125_git_staged_patch.md) | 一些git补丁、撤销方法
0124| [pyusb_MTK_PL_Mode.md](docs/0124_pyusb_MTK_PL_Mode.md) | 分析MTK PL Mode选择
0123| [Write_Sort.md](docs/0123_Write_Sort.md) | 以前确实没怎么关注算法，学习一下算法，列一下写一个算法的基本架构
0122| [RSA_Modulus_Exponent_Decrypt.md](docs/0122_RSA_Modulus_Exponent_Decrypt.md) | 论证芯片签名、验签基本流程示例
0121| [RSA_HTTP_Sign.md](docs/0121_RSA_HTTP_Sign.md) | 利用HTTP请求来对HASH数进行签名
0120| [Python_C_Get_Shell_env.md](docs/0120_Python_C_Get_Shell_env.md) | 在处理Android编译镜像签名的时候用于区分环境
0119| [OpenSSL_C_Example.md](docs/0119_OpenSSL_C_Example.md) | 学习OpenSSL的使用
0118| [Wifi_rfkill_off.md](docs/0118_Wifi_rfkill_off.md) | 默认Wifi打不开，rfkill关闭了，暂时不知道原因
0117| [Jenkins.md](docs/0117_Jenkins.md) | 用Jenkins来定时编译源代码
0116| [pyc_decompile_to_py.md](docs/0116_pyc_decompile_to_py.md) | Python pyc反编译成py
0115| [Openssl_RSA_Hash_Sign.md](docs/0115_Openssl_RSA_Hash_Sign.md) | RAS Hash签名、验签
0114| [Wifi_BSSID.md](docs/0114_Wifi_BSSID.md) | 查看特定Wifi AP的BSSID(MAC ADDRESS)
0113| [MMU_Cache_VA_PA.md](docs/0113_MMU_Cache_VA_PA.md) | 内存管理中的MMC Cache相关知识
0112| [mkdtimg.md](docs/0112_mkdtimg.md) | 将Android的mkdtimg移植到树莓派上做dtbo.img验证工具
0111| [Windows_Terminal.md](docs/0111_Windows_Terminal.md) | 使用好看一点的Windows Terminal
0110| [repo_GitHub_Booster.md](docs/0110_repo_GitHub_Booster.md) | repo使用及GitHub加速
0109| [alias.md](docs/0109_alias.md) | 终端命令快捷方式
0108| [dkms.md](docs/0108_dkms.md) | Dynamic Kernel Module Support
0107| [Windows10_Mount_ext4.md](docs/0107_Windows10_Mount_ext4.md) | 重新制作系统SD卡的时候，Windows打开ext4文件系统直接配置系统还是挺重要的
0106| [Source_Compare_Tools.md](docs/0106_Source_Compare_Tools.md) | 对比源代码工具`Beyond Compare`、`WinMerge`
0105| [mirror_apt_source.md](docs/0105_mirror_apt_source.md) | 默认的源update有点慢
0104| [Android_RefBase_sp_wp.md](docs/0104_Android_RefBase_sp_wp.md) | 本来想把Android RefBase sp wp移到RPI上使用，暂时不行
0103| [fs_modify_for_developer.md](docs/0103_fs_modify_for_developer.md) | 常用的文件系统默认修改
0102| [WM8960.md](docs/0102_WM8960.md) | 分析声卡WM8960
0101| [AHRS.md](docs/0101_AHRS.md) | AHRS俗称航姿参考系统，AHRS由加速度计，磁场计，陀螺仪构成，AHRS的真正参考来自于地球的重力场和地球的磁场
0100| [Kernel_DEBUG_Macro.md](docs/0100_Kernel_DEBUG_Macro.md) | 内核模块DEBUG宏，和Android里面的NODEBUG宏一样
0099| [socketpair.md](docs/0099_socketpair.md) | socketpair用于创建一对无名的、相互连接的套接字，于进程间通信。
0098| [QTTabBar.md](docs/0098_QTTabBar.md) | Windows文件夹工具，配合battool打开文件夹，防遗忘
0097| [Kernel_Complete.md](docs/0097_Kernel_Complete.md) | 理解内核Complete同步机制
0096| [Kernel_Notifier.md](docs/0096_Kernel_Notifier.md) | 理解内核通知
0095| [Kernel_Tools_Compile.md](docs/0095_Kernel_Tools_Compile.md) | 仅仅尝试一下编译，暂时不知道用来干啥
0094| [NFC_PN532.md](docs/0094_NFC_PN532.md) | NFC PN532调试
0093| [PCM_Data_Format.md](docs/0093_PCM_Data_Format.md) | 查看wav左右声道数据存放格式，理解PCM数据流格式
0092| [Wifi_Linux_Driver.md](docs/0092_Wifi_Linux_Driver.md) | Wifi驱动加载及基本调试
0091| [systemd-journald.md](docs/0091_systemd-journald.md) | 系统日志
0090| [systemd-timesyncd.md](docs/0090_systemd-timesyncd.md) | 系统是如何同步时钟的
0089| [ftrace_I2C.md](docs/0089_ftrace_I2C.md) | 使用ftrace观察I2C，EEPROM是扩展板上的
0088| [ftrace_CPU_Frequency.md](docs/0088_ftrace_CPU_Frequency.md) | 理解CPU自动调频
0087| [strace.md](docs/0087_strace.md) | 理解strace(system call trace)系统调用跟踪
0086| [trace-cmd.md](docs/0086_trace-cmd.md) | 理解trace-cmd工作原理
0085| [netlink.md](docs/0085_netlink.md) | libnl基本使用方法
0084| [wpa_supplicant_daemon.md](docs/0084_wpa_supplicant_daemon.md) | 分析wpa_supplicant后台程序工作原理
0083| [Process_Timer.md](docs/0083_Process_Timer.md) | Linux系统常用定时器
0082| [wpa_cli.md](docs/0082_wpa_cli.md) | 分析wpa_cli的工作原理
0081| [Android_Binder.md](docs/0081_Android_Binder.md) | 移植Android Binder到树莓派
0080| [Thread_Pool.md](docs/0080_Thread_Pool.md) | 了解线程池的工作原理
0079| [Android_Init_Base_Arch.md](docs/0079_Android_Init_Base_Arch.md) | 理解Android Init进程监听子进程原理
0078| [OpenGrok.md](docs/0078_OpenGrok.md) | 在线浏览器跟代码工具OpenGrok
0077| [Large_File_Split.md](docs/0077_Large_File_Split.md) | splite分割大文件
0076| [PCM5122.md](docs/0076_PCM5122.md) | DAI：Digital Audio Interface。DAI是数字音频接口的统称，PCM是其中的一种。
0075| [Kernel_Panic_trigger.md](docs/0075_Kernel_Panic_trigger.md) | 手动触发内核Panic
0074| [Core_Files.md](docs/0074_Core_Files.md) | 经过和颖奇讨论，这个主要是应用程序Crash的时候，会自动保存堆载信息，便于调试；
0073| [MathJax.md](docs/0073_MathJax.md) | 在GitHub上渲染数学公式
0072| [RPI4_USB_Camera.md](docs/0072_RPI4_USB_Camera.md) | 测试USB Camera
0071| [WiFi_AP.md](docs/0071_WiFi_AP.md) | 由于OTA测试需要用到一个指定IP进行测试，于是暂时使用树莓派WiFI做一个AP，再加一个Apache2作为web服务端。
0070| [PWM_Counter.md](docs/0070_PWM_Counter.md) | PWM计数器
0069| [PADS.md](docs/0069_PADS.md) | 跟崔博学习一下PADS的使用方法
0068| [wav_Sound_Generator.md](docs/0068_wav_Sound_Generator.md) | C代码生成wav声音文件生成方法
0067| [xrdp.md](docs/0067_xrdp.md) | 使用远程桌面
0066| [M24128_EEPROM.md](docs/0066_M24128_EEPROM.md) | 尝试M24128 EEPROM，使用AT的驱动就行了
0065| [Continue_Show_dmesg.md](docs/0065_Continue_Show_dmesg.md) | 在终端持续显示dmesg信息
0064| [OpenVPN_Multiple_Users.md](docs/0064_OpenVPN_Multiple_Users.md) | OpenVPN多用户连接
0063| [OpenVPN.md](docs/0063_OpenVPN.md) | OpenVPN搭建
0062| [U-Boot_Compile.md](docs/0062_U-Boot_Compile.md) | 虽说树莓派4B是64bit处理器，不过目前的系统镜像貌似是运行在32bit模式的，所以不要去编译64bit的U-Boot
0061| [Sense_HAT_ATtiny88.md](docs/0061_Sense_HAT_ATtiny88.md) | 分析Sense HAT的ATtiny88 MCU代码
0060| [DebugHAT_led.md](docs/0060_DebugHAT_led.md) | DebugHAT Led控制方法
0059| [DebugHAT_Shutdown.md](docs/0059_DebugHAT_Shutdown.md) | Debug HAT Shutdown按钮
0058| [DebugHAT_Poweroff.md](docs/0058_DebugHAT_Poweroff.md) | 这里的Poweroff不是是触发系统断电的按键功能，而是这个引脚默认低电平，如果系统关机，那么会给出高电平，告诉外围电路系统断电了。
0057| [DebugHAT_AT24C02.md](docs/0057_DebugHAT_AT24C02.md) | DebugHAT AT24C02 EEPROM使用方法
0055| [Kernel_Message_To_UART_Port.md](docs/0055_Kernel_Message_To_UART_Port.md) | 将内核信息输出到Console Port
0054| [NFS.md](docs/0054_NFS.md) | 支持NFS文件系统
0053| [auto_sd_resize.md](docs/0053_auto_sd_resize.md) | 分析SD卡自动resize功能
0052| [shadowsocks.md](docs/0052_shadowsocks.md) | 搭建shadowsocks服务器
0051| [tig.md](docs/0051_tig.md) | 如果你下载了Windows版本的git，你会发现其自带了tig命令，这也就说明这个命令有多好用。
0050| [Cscope.md](docs/0050_Cscope.md) | 和ctags一样好用的代码跟踪工具
0049| [DTS_GPIO_Kernel_Driver_Interrupt.md](docs/0049_DTS_GPIO_Kernel_Driver_Interrupt.md) | GPIO口中断分析
0048| [Gitweb.md](docs/0048_Gitweb.md) | 搭建Gitweb服务
0047| [HTTP_Auth.md](docs/0047_HTTP_Auth.md) | 尝试HTTP认证
0046| [USB_Camera_udev.md](docs/0046_USB_Camera_udev.md) | USB摄像头驱动加载方法
0045| [SoC_Device_Tree.md](docs/0045_SoC_Device_Tree.md) | SoC设备树
0044| [Create_Raspbian_Image.md](docs/0044_Create_Raspbian_Image.md) | 如果你想看看树莓派镜像是如何打包出来，可以看看这个
0043| [Docker.md](docs/0043_Docker.md) | 树莓派上如何使用Docker
0042| [ROS.md](docs/0042_ROS.md) | 尝试安装ROS，不过不知道用来干什么
0041| [Add_Swap_Partition.md](docs/0041_Add_Swap_Partition.md) | 手动添加Swap分区，内存不够的时候可以尝试用用
0040| [Qt_4_OpenGL.md](docs/0040_Qt_4_OpenGL.md) | 学习使用OpenGL，但不知为何QT 5用不了
0039| [RTIMULib.md](docs/0039_RTIMULib.md) | 尝试一下RTIMULib库的使用方法
0038| [Auto_Login_Via_TTY.md](docs/0038_Auto_Login_Via_TTY.md) | 自动登录，好像没什么用处
0037| [Tensorflow_Install.md](docs/0037_Tensorflow_Install.md) | 安装Tensorflow，不过不会用
0036| [Python_Call_C_Share_Lib.md](docs/0036_Python_Call_C_Share_Lib.md) | Python直接调C共享库方法
0035| [bash_complete.md](docs/0035_bash_complete.md) | 按tab键命令自动补全功能
0034| [Gerrit.md](docs/0034_Gerrit.md) | 尝试搭建Gerrit代码服务器
0033| [MBR_GPT.md](docs/0033_MBR_GPT.md) | 分析MBR GPT分区格式
0032| [Boot_Dir_Support_SSH_Auto_Run.md](docs/0032_Boot_Dir_Support_SSH_Auto_Run.md) | 分析自动打开SSH和网络配置原理
0031| [Bluetooth_SPP.md](docs/0031_Bluetooth_SPP.md) | 尝试蓝牙串口功能
0030| [OpenCV.md](docs/0030_OpenCV.md) | 学习OpenCV的基本使用方法
0029| [Linux_Kernel_Compile.md](docs/0029_Linux_Kernel_Compile.md) | 内核编译方法
0028| [VNC_Connect.md](docs/0028_VNC_Connect.md) | 打开VNC功能
0027| [git_server.md](docs/0027_git_server.md) | 搭建git服务器
0026| [libdrm_modetest.md](docs/0026_libdrm_modetest.md) | 编译libdrm，可以用于调试drm驱动的屏
0025| [Vim_Support_Mouse_Paste.md](docs/0025_Vim_Support_Mouse_Paste.md) | Vim鼠标粘贴
0024| [Kernel_Modules.md](docs/0024_Kernel_Modules.md) | 内核模块编译
0023| [Sense_HAT.md](docs/0023_Sense_HAT.md) | Sense HAT使用方法
0022| [GPIO_Interrupt.md](docs/0022_GPIO_Interrupt.md) | GPIO中断测试方法
0021| [Auto_Send_Mail.md](docs/0021_Auto_Send_Mail.md) | Python自动发邮件
0020| [PWM.md](docs/0020_PWM.md) | 软件、硬件PWM
0019| [Kernel_Build.md](docs/0019_Kernel_Build.md) | 内核编译文档
0018| [Samba.md](docs/0018_Samba.md) | 搭建Samba服务
0017| [Internationalisation_Options.md](docs/0017_Internationalisation_Options.md) | 系统语言设置
0016| [Setup_Multiple_WiFi_Networks.md](docs/0016_Setup_Multiple_WiFi_Networks.md) | 设置Wifi账户密码
0015| [Modify_Default_Route.md](docs/0015_Modify_Default_Route.md) | 使用了usb otg转网口功能，发现原来能用的网络不能用了，找一下原因；
0014| [Ethernet_over_USB-Static_IP.md](docs/0014_Ethernet_over_USB-Static_IP.md) | 貌似不设定静态IP，这个USB OTG的IP总是会变化，有时候还会跨网段变化，所以还是设定死了比较好。
0013| [dtoverlay.md](docs/0013_dtoverlay.md) | 分析设备树overlay功能，和上篇文档一样
0012| [Dynamic_Device_Tree.md](docs/0012_Dynamic_Device_Tree.md) | 动态设备树工作原理
0011| [SPI.md](docs/0011_SPI.md) | 测试SPI基本通信
0010| [I2C_AT24C0x.md](docs/0010_I2C_AT24C0x.md) | 在FPGA上使用AT24C08，结果发现识别不到，在树莓派上测试一下情况。
0009| [systemd-sysv-generator.md](docs/0009_systemd-sysv-generator.md) | systemd是如何使用sysv的启动文件
0008| [Systemd_Advance.md](docs/0008_Systemd_Advance.md) | Systemd的基本概念及使用
0007| [Systemd_Cron_rc-local.md](docs/0007_Systemd_Cron_rc-local.md) | Systemd添加服务
0006| [Device_Tree_Overlays.md](docs/0006_Device_Tree_Overlays.md) | 简单看一下设备树Overlay
0005| [raspi-config.md](docs/0005_raspi-config.md) | raspi-config解析
0004| [Pin_Config.md](docs/0004_Pin_Config.md) | 这里需要注意后面的设备树的叠加层的理解，这里不做解释。
0003| [BIOS.md](docs/0003_BIOS.md) | 树莓派使用配置文件充当BIOS配置
0002| [Boot_Sequence.md](docs/0002_Boot_Sequence.md) | 启动时序
0001| [OTG_To_Ethernet.md](docs/0001_OTG_To_Ethernet.md) | 设置USB为OTG网卡
