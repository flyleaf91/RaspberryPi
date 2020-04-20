# Kernel Tools Compile

仅仅尝试一下编译，暂时不知道用来干啥

* [一、参考文档](#一参考文档)
* [二、编译方法](#二编译方法)

## 一、参考文档

* [What are the tools in /tools folder?](https://unix.stackexchange.com/questions/377409/what-are-the-tools-in-tools-folder)

## 二、编译方法

`cd <kernel root path>`  
进入内核源代码根目录

`make tools/help`  
查看tools的帮助信息

```
Possible targets:

  acpi                   - ACPI tools
  cgroup                 - cgroup tools
  cpupower               - a tool for all things x86 CPU power
  firewire               - the userspace part of nosy, an IEEE-1394 traffic sniffer
  freefall               - laptop accelerometer program for disk protection
  gpio                   - GPIO tools
  hv                     - tools used when in Hyper-V clients
  iio                    - IIO tools
  kvm_stat               - top-like utility for displaying kvm statistics
  leds                   - LEDs  tools
  liblockdep             - user-space wrapper for kernel locking-validator
  bpf                    - misc BPF tools
  perf                   - Linux performance measurement and analysis tool
  selftests              - various kernel selftests
  spi                    - spi tools
  objtool                - an ELF object analysis tool
  tmon                   - thermal monitoring and tuning tool
  turbostat              - Intel CPU idle stats and freq reporting tool
  usb                    - USB testing tools
  virtio                 - vhost test module
  vm                     - misc vm tools
  wmi                   - WMI interface examples
  x86_energy_perf_policy - Intel energy policy tool

You can do:
 $ make -C tools/ <tool>_install

  from the kernel command line to build and install one of
  the tools above

  $ make tools/all

  builds all tools.

  $ make tools/install

  installs all tools.

Cleaning targets:

  all of the above with the "_clean" string appended cleans
    the respective build directory.
  clean: a summary clean target to clean _all_ folders
```

使用如下命令进行单独编译某一部分工具：

* make tools/usb
* make tools/iio
* make tools/gpio
* make tools/perf