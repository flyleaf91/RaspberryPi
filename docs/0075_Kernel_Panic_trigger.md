# Kernel Panic trigger

手动触发内核Panic

## 参考文档

* [Linux内核崩溃panic信息反向解析和保存在文件系统目录](https://blog.csdn.net/TSZ0000/article/details/84329505)
* [Documentation sysrq.txt](https://kernel.googlesource.com/pub/scm/linux/kernel/git/pjt/test/+/v2.6.13-rc3/Documentation/sysrq.txt)
* [深入探索 Kdump，第 1 部分：带你走进 Kdump 的世界](https://www.ibm.com/developerworks/cn/linux/l-cn-kdump1/index.html)


## trigger panic steps

* sudo su
* 在串口debug port执行：dmesg -w
* echo c > /proc/sysrq-trigger
* 在串口debug port信息：
  ```
  [...省略]
  [  105.863431] sysrq: SysRq : Trigger a crash
  [  105.867620] Unable to handle kernel NULL pointer dereference at virtual address 00000000
  [  105.875935] pgd = 997cb3a6
  [  105.863431] sysrq: SysRq : Trigger a crash
  [  105.867620] Unable to handle kernel NULL pointer dereference at virtual address 00000000
  [  105.87593[  105.891486] [00000000] *pgd=280b0003, *pmd=fbe97003
  [  105.897059] Internal error: Oops: a07 [#1] SMP ARM
  [  105.901927] Modules linked in: fuse xt_conntrack ipt_MASQUERADE nf_conntrack_netlink nft_counter xt_addrtype nft_compat cmac nft_chain_nat_ipv4 nf_nat_ipv4 nf_nat nf_conntrack nf_defrag_ipv6 nf_defrag_ipv4 bnep nf_tables nfnetlink br_netfilter bridge hci_uart btbcm serdev overlay 8021q garp stp llc rfcomm bluetooth ecdh_generic at24 binfmt_misc evdev brcmfmac brcmutil sha256_generic cfg80211 rfkill raspberrypi_hwmon hwmon snd_bcm2835(C) snd_pcm snd_timer gpio_keys snd i2c_bcm2835 bcm2835_codec(C) bcm2835_v4l2(C) v4l2_mem2mem bcm2835_mmal_vchiq(C) videobuf2_dma_contig v4l2_common videobuf2_vmalloc videobuf2_memops videobuf2_v4l2 videobuf2_common videodev media vc_sm_cma(C) rpivid_mem uio_pdrv_genirq uio fixed i2c_dev usb_f_ecm g_ether usb_f_rndis u_ether libcomposite dwc2 udc_core nfsd ip_tables x_tables
  [  105.974701]  ipv6
  [  105.976669] CPU: 3 PID: 1343 Comm: bash Tainted: G         C        4.19.71-v7l #1
  [  105.984351] Hardware name: BCM2835
  [  105.987819] PC is at sysrq_handle_crash+0x2c/0x34
  [  105.992596] LR is at __handle_sysrq+0x8c/0x16c
  [  105.997106] pc : [<c06a392c>]    lr : [<c06a42ec>]    psr: 60000013
  [  106.003466] sp : e8f83e40  ip : e8f83e50  fp : e8f83e4c
  [  106.008769] r10: 00000004  r9 : 00000000  r8 : c10607fc
  [  106.014072] r7 : 00000000  r6 : 00000003  r5 : 00000063  r4 : c1010678
  [  106.020696] r3 : 00000000  r2 : 00000001  r1 : 00000000  r0 : 00000063
  [  106.027322] Flags: nZCv  IRQs on  FIQs on  Mode SVC_32  ISA ARM  Segment user
  [  106.034564] Control: 30c5383d  Table: 296d0fc0  DAC: 55555555
  [  106.040398] Process bash (pid: 1343, stack limit = 0xecd5d744)
  [  106.046318] Stack: (0xe8f83e40 to 0xe8f84000)
  [  106.050743] 3e40: e8f83e74 e8f83e50 c06a42ec c06a390c 00000002 c06a4830 00000000 c0423ea8
  [  106.059045] 3e60: b4c01999 00000000 e8f83e8c e8f83e78 c06a4878 c06a426c ef10a200 c06a4830
  [  106.067346] 3e80: e8f83eac e8f83e90 c0423f18 c06a483c c1004d88 e7545f00 e8f83f60 c0423ea8
  [  106.075648] 3ea0: e8f83f24 e8f83eb0 c03b0688 c0423eb4 5e12fb12 098967fc 5e13d9b1 00000000
  [  106.083948] 3ec0: 00000800 00000000 f00000c8 c1004d88 00000a07 c0993bf4 00000000 ef83dd80
  [  106.092249] 3ee0: e8f83f04 e8f83ef0 c0993bf4 c02932f0 00000000 ef83dd80 e8f83f24 b4c01999
  [  106.100551] 3f00: 00000002 e7545f00 01093d88 e8f83f60 00000000 00000000 e8f83f54 e8f83f28
  [  106.108852] 3f20: c03b0998 c03b064c 00000004 c03d1d14 e7545f00 c1004d88 e7545f00 01093d88
  [  106.117153] 3f40: 00000000 00000000 e8f83f94 e8f83f58 c03b0c78 c03b08f0 00000000 00000000
  [  106.125453] 3f60: 00000000 00000000 60000010 b4c01999 00000002 01093d88 b6f14d90 00000004
  [  106.133754] 3f80: c02011c4 e8f82000 e8f83fa4 e8f83f98 c03b0d04 c03b0c10 00000000 e8f83fa8
  [  106.142054] 3fa0: c0201000 c03b0cf8 00000002 01093d88 00000001 01093d88 00000002 00000000
  [  106.150355] 3fc0: 00000002 01093d88 b6f14d90 00000004 01093d88 00000002 001042a8 00000000
  [  106.158655] 3fe0: 0000006c bee0e338 b6e337b8 b6e8f944 60000010 00000001 00000000 00000000
  [  106.166967] [<c06a392c>] (sysrq_handle_crash) from [<c06a42ec>] (__handle_sysrq+0x8c/0x16c)
  [  106.175449] [<c06a42ec>] (__handle_sysrq) from [<c06a4878>] (write_sysrq_trigger+0x48/0x58)
  [  106.183933] [<c06a4878>] (write_sysrq_trigger) from [<c0423f18>] (proc_reg_write+0x70/0x98)
  [  106.192419] [<c0423f18>] (proc_reg_write) from [<c03b0688>] (__vfs_write+0x48/0x170)
  [  106.200283] [<c03b0688>] (__vfs_write) from [<c03b0998>] (vfs_write+0xb4/0x1c8)
  [  106.207705] [<c03b0998>] (vfs_write) from [<c03b0c78>] (ksys_write+0x74/0xe8)
  [  106.214951] [<c03b0c78>] (ksys_write) from [<c03b0d04>] (sys_write+0x18/0x1c)
  [  106.222199] [<c03b0d04>] (sys_write) from [<c0201000>] (ret_fast_syscall+0x0/0x28)
  [  106.229881] Exception stack(0xe8f83fa8 to 0xe8f83ff0)
  [  106.235010] 3fa0:                   00000002 01093d88 00000001 01093d88 00000002 00000000
  [  106.243312] 3fc0: 00000002 01093d88 b6f14d90 00000004 01093d88 00000002 001042a8 00000000
  [  106.251610] 3fe0: 0000006c bee0e338 b6e337b8 b6e8f944
  [  106.256742] Code: e3a02001 e5832000 f57ff04e e3a03000 (e5c32000)
  [  106.263018] ---[ end trace c08befe48aa7f291 ]---
  [  106.267713] Kernel panic - not syncing: Fatal exception
  [  106.267731] CPU2: stopping
  [  106.267745] CPU: 2 PID: 434 Comm: rs:main Q:Reg Tainted: G      D  C        4.19.71-v7l #1
  [  106.267752] Hardware name: BCM2835
  [  106.267783] [<c0212c74>] (unwind_backtrace) from [<c020d2cc>] (show_stack+0x20/0x24)
  [  106.267801] [<c020d2cc>] (show_stack) from [<c097ce30>] (dump_stack+0xcc/0x110)
  [  106.267819] [<c097ce30>] (dump_stack) from [<c02110c8>] (handle_IPI+0x368/0x3a0)
  [  106.267834] [<c02110c8>] (handle_IPI) from [<c020226c>] (gic_handle_irq+0x84/0x88)
  [  106.267846] [<c020226c>] (gic_handle_irq) from [<c02019bc>] (__irq_svc+0x5c/0x7c)
  [  106.267854] Exception stack(0xe9c47c78 to 0xe9c47cc0)
  [  106.267862] 7c60:                                                       7fffffff 00000000
  [  106.267873] 7c80: b4c01999 b4c01999 c1010658 7fffffff ffffe000 00000002 c1004d88 f492926c
  [  106.267882] 7ca0: c1004d88 e9c47d04 e9c46000 e9c47cc8 00000000 c0995da4 60000013 ffffffff
  [  106.267898] [<c02019bc>] (__irq_svc) from [<c0995da4>] (__down+0xa0/0xf4)
  [  106.267913] [<c0995da4>] (__down) from [<c0278620>] (down+0x54/0x5c)
  [  106.267928] [<c0278620>] (down) from [<c027d590>] (console_lock+0x20/0x44)
  [  106.267945] [<c027d590>] (console_lock) from [<c06b310c>] (do_con_write.part.13+0x40/0x900)
  [  106.267963] [<c06b310c>] (do_con_write.part.13) from [<c06b3a80>] (con_write+0x48/0x94)
  [  106.267978] [<c06b3a80>] (con_write) from [<c069b5a8>] (n_tty_write+0x390/0x4b8)
  [  106.267991] [<c069b5a8>] (n_tty_write) from [<c0697284>] (tty_write+0x164/0x354)
  [  106.268003] [<c0697284>] (tty_write) from [<c03b0688>] (__vfs_write+0x48/0x170)
  [  106.268016] [<c03b0688>] (__vfs_write) from [<c03b0998>] (vfs_write+0xb4/0x1c8)
  [  106.268027] [<c03b0998>] (vfs_write) from [<c03b0c78>] (ksys_write+0x74/0xe8)
  [  106.268038] [<c03b0c78>] (ksys_write) from [<c03b0d04>] (sys_write+0x18/0x1c)
  [  106.268051] [<c03b0d04>] (sys_write) from [<c0201000>] (ret_fast_syscall+0x0/0x28)
  [  106.268058] Exception stack(0xe9c47fa8 to 0xe9c47ff0)
  [  106.268067] 7fa0:                   00000087 b60400d8 0000000f b60400d8 00000087 00000000
  [  106.268077] 7fc0: 00000087 b60400d8 0000000f 00000004 000ac848 00000901 b60400d8 000ac98c
  [  106.268085] 7fe0: 00000002 b5efe238 00000000 b6eaa1bc
  [  106.268093] CPU0: stopping
  [  106.268118] CPU: 0 PID: 105 Comm: systemd-journal Tainted: G      D  C        4.19.71-v7l #1
  [  106.268124] Hardware name: BCM2835
  [  106.268149] [<c0212c74>] (unwind_backtrace) from [<c020d2cc>] (show_stack+0x20/0x24)
  [  106.268166] [<c020d2cc>] (show_stack) from [<c097ce30>] (dump_stack+0xcc/0x110)
  [  106.268182] [<c097ce30>] (dump_stack) from [<c02110c8>] (handle_IPI+0x368/0x3a0)
  [  106.268197] [<c02110c8>] (handle_IPI) from [<c020226c>] (gic_handle_irq+0x84/0x88)
  [  106.268210] [<c020226c>] (gic_handle_irq) from [<c0201d0c>] (__irq_usr+0x4c/0x60)
  [  106.268217] Exception stack(0xec5f9fb0 to 0xec5f9ff8)
  [  106.268227] 9fa0:                                     00dce89c 00d7b5fc ffffff85 554f535f
  [  106.268237] 9fc0: 5f454352 4f4e4f4d 494e4f54 49545f43 5453454d 00d7b5d8 befdf314 00d7b5d8
  [  106.268246] 9fe0: 0000001c befdf204 34373035 b6e39858 00000010 ffffffff
  [  106.268254] CPU1: stopping
  [  106.268267] CPU: 1 PID: 1310 Comm: dmesg Tainted: G      D  C        4.19.71-v7l #1
  [  106.268273] Hardware name: BCM2835
  [  106.268294] [<c0212c74>] (unwind_backtrace) from [<c020d2cc>] (show_stack+0x20/0x24)
  [  106.268312] [<c020d2cc>] (show_stack) from [<c097ce30>] (dump_stack+0xcc/0x110)
  [  106.268328] [<c097ce30>] (dump_stack) from [<c02110c8>] (handle_IPI+0x368/0x3a0)
  [  106.268342] [<c02110c8>] (handle_IPI) from [<c020226c>] (gic_handle_irq+0x84/0x88)
  [  106.268354] [<c020226c>] (gic_handle_irq) from [<c0201d0c>] (__irq_usr+0x4c/0x60)
  [  106.268361] Exception stack(0xe75a5fb0 to 0xe75a5ff8)
  [  106.268371] 5fa0:                                     00000332 014afee8 00000332 00000000
  [  106.268381] 5fc0: 00000332 014afee8 b6f1ad90 00000004 014afee8 00000332 be8a2ba8 0002d06e
  [  106.268390] 5fe0: 0000006c be8a29a8 b6e397b8 b6e95944 60000010 ffffffff
  [  106.633384] ---[ end Kernel panic - not syncing: Fatal exception ]---
  ```


## kdump

* [为树莓派编译Kdump kernel](http://weinan.io/2018/06/18/kdump.html)
* [Configuring the kernel](https://www.raspberrypi.org/documentation/linux/kernel/configuring.md)
* sudo apt-get install kdump-tools
  * 安装失败，会提示内核不支持
* arch/arm/configs/bcm2711_defconfig
* make CROSS_COMPILE=arm-linux-gnueabihf- menuconfig 
  * CONFIG_DEBUG_INFO
  * CONFIG_CRASH_DUMP
  * CONFIG_PROC_VMCORE
  * KEXEC
* 默认不支持kdump