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

## 笔记文档

NO.|文件名称|摘要
:--:|:--|:--
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
