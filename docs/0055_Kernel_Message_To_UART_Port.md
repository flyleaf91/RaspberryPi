# Kernel Message To UART Port

## 参考文档

* [How to enable boot messages over UART](https://www.raspberrypi.org/forums/viewtopic.php?t=184718)


## cmdline.txt

* enable uart:
  * `raspi-config` enable uart
  * /boot/config.txt
    ```
    [...省略]
    enable_uart=1
    ```
* `/boot/cmdline.txt`
  ```
  dwc_otg.lpm_enable=1 console=ttyS0,115200 root=PARTUUID=48597d87-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait splash plymouth.ignore-serial-consoles modules-load=dwc2,g_ether
  ```


## Kernel Message

```
[    0.000000] Booting Linux on physical CPU 0x0
[    0.000000] Linux version 4.19.71-v7l (pi@raspberrypi) (gcc version 8.3.0 (Raspbian 8.3.0-6+rpi1)) #1 SMP Mon Sep 9 12:24:09 BST 2019
[    0.000000] CPU: ARMv7 Processor [410fd083] revision 3 (ARMv7), cr=30c5383d
[    0.000000] CPU: div instructions available: patching division code
[    0.000000] CPU: PIPT / VIPT nonaliasing data cache, PIPT instruction cache
[    0.000000] OF: fdt: Machine model: Raspberry Pi 4 Model B Rev 1.1
[    0.000000] Memory policy: Data cache writealloc
[    0.000000] cma: Reserved 64 MiB at 0x0000000034000000
[    0.000000] random: get_random_bytes called from start_kernel+0xc0/0x4e0 with crng_init=0
[    0.000000] percpu: Embedded 17 pages/cpu s39436 r8192 d22004 u69632
[    0.000000] Built 1 zonelists, mobility grouping on.  Total pages: 997696
[    0.000000] Kernel command line: coherent_pool=1M 8250.nr_uarts=1 cma=64M zengjf  bcm2708_fb.fbwidth=1280 bcm2708_fb.fbheight=720 bcm2708_fb.fbswap=1 smsc95xx.macaddr=DC:A6:32:17:47:91 vc_mem.mem_base=0x3ec00000 vc_mem.mem_size=0x40000000  dwc_otg.lpm_enable=1 console=ttyS0,115200 root=PARTUUID=48597d87-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait splash plymouth.ignore-serial-consoles modules-load=dwc2,g_ether
[    0.000000] Dentry cache hash table entries: 131072 (order: 7, 524288 bytes)
[    0.000000] Inode-cache hash table entries: 65536 (order: 6, 262144 bytes)
[    0.000000] Memory: 3879936K/3997696K available (8192K kernel code, 662K rwdata, 2348K rodata, 2048K init, 848K bss, 52224K reserved, 65536K cma-reserved, 3145728K highmem)
[    0.000000] Virtual kernel memory layout:
[    0.000000]     vector  : 0xffff0000 - 0xffff1000   (   4 kB)
[    0.000000]     fixmap  : 0xffc00000 - 0xfff00000   (3072 kB)
[    0.000000]     vmalloc : 0xf0800000 - 0xff800000   ( 240 MB)
[    0.000000]     lowmem  : 0xc0000000 - 0xf0000000   ( 768 MB)
[    0.000000]     pkmap   : 0xbfe00000 - 0xc0000000   (   2 MB)
[    0.000000]     modules : 0xbf000000 - 0xbfe00000   (  14 MB)
[    0.000000]       .text : 0x(ptrval) - 0x(ptrval)   (10208 kB)
[    0.000000]       .init : 0x(ptrval) - 0x(ptrval)   (2048 kB)
[    0.000000]       .data : 0x(ptrval) - 0x(ptrval)   ( 663 kB)
[    0.000000]        .bss : 0x(ptrval) - 0x(ptrval)   ( 849 kB)
[    0.000000] SLUB: HWalign=64, Order=0-3, MinObjects=0, CPUs=4, Nodes=1
[    0.000000] ftrace: allocating 28061 entries in 83 pages
[    0.000000] rcu: Hierarchical RCU implementation.
[    0.000000] NR_IRQS: 16, nr_irqs: 16, preallocated irqs: 16
[    0.000000] GIC: Using split EOI/Deactivate mode
[    0.000000] arch_timer: cp15 timer(s) running at 54.00MHz (phys).
[    0.000000] clocksource: arch_sys_counter: mask: 0xffffffffffffff max_cycles: 0xc743ce346, max_idle_ns: 440795203123 ns
[    0.000005] sched_clock: 56 bits at 54MHz, resolution 18ns, wraps every 4398046511102ns
[    0.000021] Switching to timer-based delay loop, resolution 18ns
[    0.000245] Console: colour dummy device 80x30
[    0.000294] Calibrating delay loop (skipped), value calculated using timer frequency.. 108.00 BogoMIPS (lpj=540000)
[    0.000321] pid_max: default: 32768 minimum: 301
[    0.000588] Mount-cache hash table entries: 2048 (order: 1, 8192 bytes)
[    0.000611] Mountpoint-cache hash table entries: 2048 (order: 1, 8192 bytes)
[    0.001350] CPU: Testing write buffer coherency: ok
[    0.001743] CPU0: thread -1, cpu 0, socket 0, mpidr 80000000
[    0.002374] Setting up static identity map for 0x200000 - 0x20003c
[    0.002533] rcu: Hierarchical SRCU implementation.
[    0.003383] smp: Bringing up secondary CPUs ...
[    0.004213] CPU1: thread -1, cpu 1, socket 0, mpidr 80000001
[    0.005158] CPU2: thread -1, cpu 2, socket 0, mpidr 80000002
[    0.006064] CPU3: thread -1, cpu 3, socket 0, mpidr 80000003
[    0.006196] smp: Brought up 1 node, 4 CPUs
[    0.006226] SMP: Total of 4 processors activated (432.00 BogoMIPS).
[    0.006240] CPU: All CPU(s) started in HYP mode.
[    0.006253] CPU: Virtualization extensions available.
[    0.007002] devtmpfs: initialized
[    0.017589] VFP support v0.3: implementor 41 architecture 3 part 40 variant 8 rev 0
[    0.017796] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 19112604462750000 ns
[    0.017823] futex hash table entries: 1024 (order: 4, 65536 bytes)
[    0.019536] pinctrl core: initialized pinctrl subsystem
[    0.020363] NET: Registered protocol family 16
[    0.023219] DMA: preallocated 1024 KiB pool for atomic coherent allocations
[    0.024672] hw-breakpoint: found 5 (+1 reserved) breakpoint and 4 watchpoint registers.
[    0.024689] hw-breakpoint: maximum watchpoint size is 8 bytes.
[    0.024871] Serial: AMBA PL011 UART driver
[    0.027790] bcm2835-mbox fe00b880.mailbox: mailbox enabled
[    0.063138] bcm2835-dma fe007000.dma: DMA legacy API manager at (ptrval), dmachans=0x1
[    0.065155] vgaarb: loaded
[    0.065527] SCSI subsystem initialized
[    0.065723] usbcore: registered new interface driver usbfs
[    0.065779] usbcore: registered new interface driver hub
[    0.065877] usbcore: registered new device driver usb
[    0.080340] raspberrypi-firmware soc:firmware: Attached to firmware from 2019-07-09 14:37, variant start
[    0.090075] raspberrypi-firmware soc:firmware: Firmware hash is d2b1b7fb01475cb3914b2086299e32d724e832f1
[    0.101668] clocksource: Switched to clocksource arch_sys_counter
[    0.177068] VFS: Disk quotas dquot_6.6.0
[    0.177147] VFS: Dquot-cache hash table entries: 1024 (order 0, 4096 bytes)
[    0.177295] FS-Cache: Loaded
[    0.177474] CacheFiles: Loaded
[    0.186809] NET: Registered protocol family 2
[    0.187448] tcp_listen_portaddr_hash hash table entries: 512 (order: 0, 6144 bytes)
[    0.187478] TCP established hash table entries: 8192 (order: 3, 32768 bytes)
[    0.187540] TCP bind hash table entries: 8192 (order: 4, 65536 bytes)
[    0.187610] TCP: Hash tables configured (established 8192 bind 8192)
[    0.187728] UDP hash table entries: 512 (order: 2, 16384 bytes)
[    0.187759] UDP-Lite hash table entries: 512 (order: 2, 16384 bytes)
[    0.188059] NET: Registered pr=20 bucket_order=6
[    0.200917] FS-Cache: Netfs 'nfs' registered for caching
[    0.201414] NFS: Registering the id_resolver key type
[    0.201450] Key type id_resolver registered
[    0.201464] Key type id_legacy registered
[    0.201487] nfs4filelayout_init: NFSv4 File Layout Driver Registering...
[    0.203779] Key type asymmetric registered
[    0.203795] Asymmetric kersion 0.4 loaded (major 250)
[    0.204113] io scheduler noop registered
[    0.204129] io scheduler deadline registered (default)
[    0.204290] io scheduler cfq registered
[    0.204306] io scheduler mq-deadline registered (default)
[    0.204320] io scheduler kyber registered
[    0.247518] brcm-pcie fd500000.pcie: dmabounce: initialised - 32768 kB, threshold 0x00000000c0000000
[    0.247541] brc94] pci_bus 0000:00: root bus resource [bus 00-01]
[    0.302015] pci_bus 0000:00: root bus resource [mem 0x600000000-0x603ffffff] (bus address [0xf8000000-0xfbffffff])
[    0.304845] PCI: bus0: Fast back to back transfers disabled
[    0.304867] pci 0000:00:00.0: bridge configuration invalid ([bus 00-00]), reconfiguring
[    0.308174] PCI: bus1: Fast back to back transfers disabled
[    0.308238] pci 0000:00:00.0: BAR 8: assigned [mem 0x600000000-0x6000fffff]
[    0.308262] pci 0000:01:00.0: BAR 0: assigned [mem 0x600000000-0x600000fff 64bit]
[    0.30c:fb: FB found 1 display(s)
[    0.325105] Console: switching to colour frame buffer device 160x45
[    0.329609] bcm2708_fb soc:fb: Registered framebuffer for display 0, size 1280x720
[    0.331073] Serial: 8250/16550 driver, 1 ports, IRQ sharing enabled
[    0.333003] iproc-rng200 fe104000.rng: hwrng registered
[    0.333218] vc-mem: phys_addr:0x00000000 mem_base=0x3ec00000 menet-wol clock
[    0.356263] bcmgenet fd580000.genet: failed to get enet-eee clock
[    0.356290] bcmgenet: Skipping UMAC reset
[    0.356516] unimac-mdio unimac-mdio.-19: DMA mask not set
[    0.371699] libphy: bcmgenet MII bus: probed
[    0.412215] unimac-mdio unimac-mdio.-19: Broadcom UniMAC MDIO bus at 0x(ptrval)
[    0.413082] usbcore: registered new interface driver r8152
[    0.413145] usbcore: registered new interface driver lan78xx
[    0.413202] usbcore: registered new interface driver smsc95xx
[    0.413506] xhci_hcd 0000:01:00.0: xHCI Host Controller
[    0.413540]sb1: New USB device strings: Mfr=3, Product=2, SerialNumber=1
[    0.417119] usb usb1: Product: xHCI Host Controller
[    0.417134] usb usb1: Manufacturer: Linux 4.19.71-v7l xhci-hcd
[    0.417149] usb usb1: SerialNumber: 0000:01:00.0
[    0.417668] hub 1-0:1.0: USB hub found
[    0.417751] hub 1-0:1.0: 1 port detected
[    0.418222] xhci_hcd 0000:01:00.0: xHCI Host Controller
[    0.418249] xhci_hcd 0000:01:00.0: new USB bus registered, assigned bus number 2
[    0.418272] xhci_hcd 0000:01:00.0: Host supports USB 3.0 SuperSpeed
[    0.418679] usb usb2: New Utected
[    0.420467] dwc_otg: version 3.00a 10-AUG-2012 (platform bus)
[    0.420882] usbcore: registered new interface driver uas
[    0.420978] usbcore: registered new interface driver usb-storage
[    0.421150] mousedev: PS/2 mouse device common for all mice
[    0.422319] bcm2835-wdt bcm2835-wdt: Broadcom BCM2835 watchdog timer
[    0.422512] bcm2835-cpufreq: min=600000 max=1500000
[    0.423032] sdhci: Secure Digital Host Controller Interface driver
[    0.423046] sdhci: Copyright(c) Pierre Ossman
[    0.423425] mmc-bcm2835 fe300000.mmcnr: could not get clk, deferring probe
[    0.423780] sdhci-pltfm: SDHCI platform and OF driver helper
[    0.426713] ledtrig-cpu: registered to indicate activity on CPUs
[    0.426864] hidraw: raw HID events driver (C) J0.438525] Key type dns_resolver registered
[    0.438896] Registering SWP/SWPB emulation handler
[    0.439503] registered taskstats version 1
[    0.439525] Loading compiled-in X.509 certificates
[    0.447314] uart-pl011 fe201000.serial: cts_event_workaround enabled
[    0.447386] fe201000.serial: ttyAMA0 at MMIO 0xfe201000 (irq = 34, base_baud = 0) is a PL011 rev2
[    0.45[    1.696591] sdhci-iproc fe340000.emmc2: Linked as a consumer to regulator.1
[    1.722017] mmc1: queuing unknown CIS tuple 0x80 (2 bytes)
[    1.729201] mmc1: queuing unknown CIS tuple 0x80 (3 bytes)
[    1.736389] mmc1: queuing unknown CIS tuple 0x80 (3 bytes)
[    1.742017] mmc0: SDHCI controller on fe340000.emmc2 [fe340000.emmc2] using ADMA
[    1.751873] of_cfs_init
[    1.754425] of_cfs_init: OK
[    1.757953] Waiting for root device PARTUUID=48597d87-02...
[    1.766603] mmc1: queuing unknown CIS tuple 0x80 (7 bytes)
[    1.773827] mmc1: queuing unknown CIS tuple 0x80 (3 bytes)
[    1.826963] random: fast init done
[    1.877578] mmc1: new high speed SDIO card at address 0001
[    1.885687] mmc0: new ultra high speed DDR50 SDHC card at address 0007
[    1.893358] mmcblk0: mmc0:0007 SD32G 29.0 GiB
[    1.899135]  mmcblk0: p1 p2
[    1.911721] usb 1-1: new high-speed USB device number 2 using xhci_hcd
[    1.921139] EXT4-fs (mmcblk0p2): INFO: recovery required on readonly filesystem
[    1.928593] EXT4-fs (mmcblk0p2): write access will be enabled during recovery
[    2.094357] usb 1-1: New USB device found, idVendor=2109, idProduct=3431, bcdDevice= 4.20
[    2.102711] usb 1-1: New USB device strings: Mfr=0, Product=1, SerialNumber=0
[    2.109976] usb 1-1: Product: USB2.0 Hub
[    2.115897] hub 1-1:1.0: USB hub found
[    2.119954] hub 1-1:1.0: 4 ports detected
[   25.824878] EXT4-fs (mmcblk0p2): orphan cleanup on readonly fs
[   25.831922] EXT4-fs (mmcblk0p2): 1 orphan inode deleted
[   25.837227] EXT4-fs (mmcblk0p2): recovery complete
[   25.966316] EXT4-fs (mmcblk0p2): mounted filesystem with ordered data mode. Opts: (null)
[   25.974590] VFS: Mounted root (ext4 filesystem) readonly on device 179:2.
[   25.982605] devtmpfs: mounted
[   25.991882] Freeing unused kernel memory: 2048K
[   25.996712] Run /sbin/init as init process
[   26.532226] systemd[1]: System time before build time, advancing clock.
[   26.650485] NET: Registered protocol family 10
[   26.656186] Segment Routing with IPv6
[   26.699052] systemd[1]: systemd 241 running in system mode. (+PAM +AUDIT +SELINUX +IMA +APPARMOR +SMACK +SYSVINIT +UTMP +LIBCRYPTSETUP +GCRYPT +GNUTLS +ACL +XZ +LZ4 +SECCOMP +BLKID +ELFUTILS +KMOD -IDN2 +IDN -PCRE2 default-hierarchy=hybrid)
[   26.721424] systemd[1]: Detected architecture arm.

Welcome to Raspbian GNU/Linux 10 (buster)!

[   26.772907] systemd[1]: Set hostname to <raspberrypi>.
[   26.787889] systemd[1]: Failed to bump fs.file-max, ignoring: Invalid argument
[   27.123544] systemd[1]: File /lib/systemd/system/systemd-journald.service:12 configures an IP firewall (IPAddressDeny=any), but the local system does not support BPF/cgroup based firewalling.
[   27.140938] systemd[1]: Proceeding WITHOUT firewalling in effect! (This warning is only shown for the first loaded unit using IP firewalling.)
[   27.497438] systemd[1]: /lib/systemd/system/rpc-statd.service:13: PIDFile= references path below legacy directory /var/run/, updating /var/run/rpc.statd.pid → /run/rpc.statd.pid; please update the unit file accordingly.
[   27.649593] random: systemd: uninitialized urandom read (16 bytes read)
[   27.666220] random: systemd: uninitialized urandom read (16 bytes read)
[   27.673531] systemd[1]: Listening on fsck to fsckd communication Socket.
[  OK  ] Listening on fsck to fsckd communication Socket.
[   27.711908] random: systemd: uninitialized urandom read (16 bytes read)
[   27.719258] systemd[1]: Listening on Journal Socket.
[  OK  ] Listening on Journal Socket.
[   27.774019] systemd[1]: Condition check resulted in Journal Audit Socket being skipped.
         Mounting NFSD configuration filesystem...
         Mounting RPC Pipe File System...
[  OK  ] Created slice system-getty.slice.
[   27.885729] Installing knfsd (copyright (C) 1996 okir@monad.swb.de).
[  OK  ] Listening on RPCbind Server Activation Socket.
[  OK  ] Listening on Journal Socket (/dev/log).
         Starting Restore / save the current clock...
         Mounting Kernel Debug File System...
         Starting Create list of re…odes for the current kernel...
[  OK  ] Listening on Syslog Socket.
[  OK  ] Created slice system-systemd\x2dfsck.slice.
[  OK  ] Listening on udev Kernel Socket.
[  OK  ] Listening on udev Control Socket.
         Starting udev Coldplug all Devices...
[  OK  ] Listening on initctl Compatibility Named Pipe.
         Starting Journal Service...
[  OK  ] Reached target Swap.
[  OK  ] Set up automount Arbitrary…s File System Automount Point.
[  OK  ] Created slice system-serial\x2dgetty.slice.
[  OK  ] Started Forward Password R…uests to Wall Directory Watch.
         Mounting POSIX Message Queue File System...
         Starting Set the console keyboard layout...
[  OK  ] Created slice User and Session Slice.
[  OK  ] Reached target Slices.
         Starting Load Kernel Modules...
[  OK  ] Started Journal Service.
[  OK  ] Mounted NFSD configuration filesystem.
[   28.697600] dwc2 fe980000.usb: fe980000.usb supply vusb_d not found, using dummy regulator
[   28.706239] dwc2 fe980000.usb: Linked as a consumer to regulator.0
[   28.712565] dwc2 fe980000.usb: fe980000.usb supply vusb_a not found, using dummy regulator
[  OK  ] Mounted RPC Pipe File System.
[  OK  ] Started Restore / save the current clock.
[  OK  ] Mounted Kernel Debug File System.
[  OK  ] Started Create list of req… nodes for the current kernel.
[  OK  ] Mounted POSIX Message Queue File System.
[  OK  ] Started Set the console keyboard layout.
[   28.951835] dwc2 fe980000.usb: dwc2_check_params: Invalid parameter lpm=1
[   28.958734] dwc2 fe980000.usb: dwc2_check_params: Invalid parameter lpm_clock_gating=1
[   28.966831] dwc2 fe980000.usb: dwc2_check_params: Invalid parameter besl=1
[   28.973843] dwc2 fe980000.usb: dwc2_check_params: Invalid parameter hird_threshold_en=1
[   28.982035] dwc2 fe980000.usb: EPs: 8, dedicated fifos, 4080 entries in SPRAM
        [   28.990017] dwc2 fe980000.usb: DWC OTG Controller
 Startin[   28.995223] dwc2 fe980000.usb: new USB bus registered, assigned bus number 3
g    29.003076] dwc2 fe980000.usb: irq 38, io mem 0xfe980000
39mFile [   29.009367] usb usb3: New USB device found, idVendor=1d6b, idProduct=0002, bcdDevice= 4.19
System C[   29.018197] usb usb3: New USB device strings: Mfr=3, Product=2, SerialNumber=1
heck on [   29.026251] usb usb3: Product: DWC OTG Controller
Root Dev[   29.031734] usb usb3: Manufacturer: Linux 4.19.71-v7l dwc2_hsotg
ice.[   29.038540] usb usb3: SerialNumber: fe980000.usb
..
[   29.044597] hub 3-0:1.0: USB hub found
[   29.048494] hub 3-0:1.0: 1 port detected
         Starting pNFS block layout mapping daemon...
[   29.107810] using random self ethernet address
[   29.112409] using random host ethernet address
[ [   29.117929] usb0: HOST MAC a6:9b:c8:51:2d:7a
 OK     29.122654] usb0: MAC 62:62:72:f0:56:22
m] Start[   29.127068] using random self ethernet address
ed    29.132256] using random host ethernet address
;39mpNFS[   29.137556] g_ether gadget: Ethernet Gadget, version: Memorial Day 2008
 block l[   29.144935] g_ether gadget: g_ether ready
ayout ma[   29.149666] dwc2 fe980000.usb: bound driver g_ether
pping daemon.
[   29.182523] i2c /dev entries driver
[  OK  ] Started udev Coldplug all Devices.
[FAILED] Failed to start Load Kernel Modules.
See 'systemctl status systemd-modules-load.service' for details.
[  OK  ] Started File System Check on Root Device.
[  OK  ] Started File System Check Daemon to report status.
         Starting Remount Root and Kernel File Systems...
         Mounting Kernel Configuration File System...
         Starting Apply Kernel Variables...
         Starting Helper to synchronize boot up for ifupdown...
[  OK  ] Mounted Kernel Configuration File System.
[  OK  ] Started Apply Kernel Variables.
[  OK  ] Started Remount Root and Kernel File Systems.
[  OK  ] Started Helper to synchronize boot up for ifupdown.
         Starting Create System Users...
         Starting Flush Journal to Persistent Storage...
         Starting Load/Save Random Seed...
[  OK  ] Started Create System Users.
[  OK  ] Started Load/Save Random Seed.
         Starting Create Static Device Nodes in /dev...
[  OK  ] Started Flush Journal to Persistent Storage.
[  OK  ] Started Create Static Device Nodes in /dev.
[  OK  ] Reached target Local File Systems (Pre).
         Starting udev Kernel Device Manager...
[  OK  ] Started udev Kernel Device Manager.
         Starting Show Plymouth Boot Screen...

Raspbian GNU/Linux 10 raspberrypi ttyS0

raspberrypi login:
```