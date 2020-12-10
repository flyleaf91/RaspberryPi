# Hardware Interrupts Counter

通过硬件中断统计，可以查看中断是否发生，驱动查看中断触发判定一些信息

## 查看中断信息

cat /proc/interrupts

```
           CPU0       CPU1       CPU2       CPU3
 17:          0          0          0          0     GICv2  29 Level     arch_timer
 18:     123325      77009     109658      95752     GICv2  30 Level     arch_timer
 23:       7343          0          0          0     GICv2 114 Level     DMA IRQ
 25:          0          0          0          0     GICv2 116 Level     DMA IRQ
 26:          0          0          0          0     GICv2 117 Level     DMA IRQ
 31:       4611          0          0          0     GICv2  65 Level     fe00b880.mailbox
 34:       6648          0          0          0     GICv2 153 Level     uart-pl011
 35:         10          0          0          0     GICv2 125 Level     ttyS0
 36:          1          0          0          0     GICv2 149 Level     fe804000.i2c
 37:    1068210          0          0          0     GICv2 105 Level     fe980000.usb, fe980000.usb, dwc2_hsotg:usb3
 39:          0          0          0          0     GICv2 169 Level     brcmstb_thermal
 40:    1034378          0          0          0     GICv2 158 Level     mmc1, mmc0
 42:          0          0          0          0     GICv2  48 Level     arm-pmu
 43:          0          0          0          0     GICv2  49 Level     arm-pmu
 44:          0          0          0          0     GICv2  50 Level     arm-pmu
 45:          0          0          0          0     GICv2  51 Level     arm-pmu
 46:          0          0          0          0     GICv2 106 Level     v3d
 48:      37808          0          0          0     GICv2 189 Level     eth0
 49:         31          0          0          0     GICv2 190 Level     eth0
 55:         48          0          0          0     GICv2  66 Level     VCHIQ doorbell
 56:          0          0          0          0     GICv2 175 Level     PCIe PME, aerdrv
 57:         39          0          0          0  Brcm_MSI 524288 Edge      xhci_hcd
IPI0:          0          0          0          0  CPU wakeup interrupts
IPI1:          0          0          0          0  Timer broadcast interrupts
IPI2:      26104      40817     208753     110250  Rescheduling interrupts
IPI3:        984       3141       1986       3007  Function call interrupts
IPI4:          0          0          0          0  CPU stop interrupts
IPI5:      29560       7146      18326      22676  IRQ work interrupts
IPI6:          0          0          0          0  completion interrupts
Err:          0
```

## 中断列说明

* 逻辑中断号
* 中断在各CPU发生的次数
* 中断所属设备类名称
* 硬件中断号
* 中断处理函数。
