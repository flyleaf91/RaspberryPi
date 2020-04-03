# strace

理解strace(system call trace)系统调用跟踪

* [一、参考文档](#一参考文档)
* [二、简单测试示例](#二简单测试示例)
  * [2.1 示例print.c](#21-示例printc)
  * [2.2 测试步骤](#22-测试步骤)
  * [2.3 log.txt](#23-logtxt)
* [三、总结](#三总结)

## 一、参考文档

* [神器之strace](https://www.jianshu.com/p/33521124bdf2)
* https://wiki.st.com/stm32mpu/wiki/Strace


## 二、简单测试示例

### 2.1 示例print.c

```
#include <stdio.h>

int main() {
        printf("zengjf\n");
        fflush(stdout);

        int *ptr = NULL;
        *ptr = 10;
}
```

### 2.2 测试步骤

* gcc print.c -o print
* strace ./print > log.txt 2>&1

### 2.3 log.txt

```strace
execve("./print", ["./print"], 0xbedff580 /* 29 vars */) = 0
brk(NULL)                               = 0x15bb000
uname({sysname="Linux", nodename="raspberrypi", ...}) = 0
mmap2(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xb6fe4000
access("/etc/ld.so.preload", R_OK)      = 0
openat(AT_FDCWD, "/etc/ld.so.preload", O_RDONLY|O_LARGEFILE|O_CLOEXEC) = 3
fstat64(3, {st_mode=S_IFREG|0644, st_size=54, ...}) = 0
mmap2(NULL, 54, PROT_READ|PROT_WRITE, MAP_PRIVATE, 3, 0) = 0xb6fe3000
close(3)                                = 0
readlink("/proc/self/exe", "/home/pi/zengjf/coredump/print", 4096) = 30
openat(AT_FDCWD, "/usr/lib/arm-linux-gnueabihf/libarmmem-v7l.so", O_RDONLY|O_LARGEFILE|O_CLOEXEC) = 3
read(3, "\177ELF\1\1\1\0\0\0\0\0\0\0\0\0\3\0(\0\1\0\0\0\254\3\0\0004\0\0\0"..., 512) = 512
_llseek(3, 16748, [16748], SEEK_SET)    = 0
read(3, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 960) = 960
_llseek(3, 16424, [16424], SEEK_SET)    = 0
read(3, "A,\0\0\0aeabi\0\1\"\0\0\0\0056\0\6\6\10\1\t\2\n\3\f\1\22\4\24"..., 45) = 45
_llseek(3, 16748, [16748], SEEK_SET)    = 0
read(3, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 960) = 960
_llseek(3, 16424, [16424], SEEK_SET)    = 0
read(3, "A,\0\0\0aeabi\0\1\"\0\0\0\0056\0\6\6\10\1\t\2\n\3\f\1\22\4\24"..., 45) = 45
_llseek(3, 16748, [16748], SEEK_SET)    = 0
read(3, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 960) = 960
_llseek(3, 16424, [16424], SEEK_SET)    = 0
read(3, "A,\0\0\0aeabi\0\1\"\0\0\0\0056\0\6\6\10\1\t\2\n\3\f\1\22\4\24"..., 45) = 45
_llseek(3, 16748, [16748], SEEK_SET)    = 0
read(3, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 960) = 960
_llseek(3, 16424, [16424], SEEK_SET)    = 0
read(3, "A,\0\0\0aeabi\0\1\"\0\0\0\0056\0\6\6\10\1\t\2\n\3\f\1\22\4\24"..., 45) = 45
_llseek(3, 16748, [16748], SEEK_SET)    = 0
read(3, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 960) = 960
_llseek(3, 16424, [16424], SEEK_SET)    = 0
read(3, "A,\0\0\0aeabi\0\1\"\0\0\0\0056\0\6\6\10\1\t\2\n\3\f\1\22\4\24"..., 45) = 45
_llseek(3, 16748, [16748], SEEK_SET)    = 0
read(3, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 960) = 960
_llseek(3, 16424, [16424], SEEK_SET)    = 0
read(3, "A,\0\0\0aeabi\0\1\"\0\0\0\0056\0\6\6\10\1\t\2\n\3\f\1\22\4\24"..., 45) = 45
fstat64(3, {st_mode=S_IFREG|0644, st_size=17708, ...}) = 0
mmap2(NULL, 81964, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0xb6fa1000
mprotect(0xb6fa5000, 61440, PROT_NONE)  = 0
mmap2(0xb6fb4000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x3000) = 0xb6fb4000
close(3)                                = 0
munmap(0xb6fe3000, 54)                  = 0
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_LARGEFILE|O_CLOEXEC) = 3
fstat64(3, {st_mode=S_IFREG|0644, st_size=193780, ...}) = 0
mmap2(NULL, 193780, PROT_READ, MAP_PRIVATE, 3, 0) = 0xb6f71000
close(3)                                = 0
openat(AT_FDCWD, "/lib/arm-linux-gnueabihf/libc.so.6", O_RDONLY|O_LARGEFILE|O_CLOEXEC) = 3
read(3, "\177ELF\1\1\1\0\0\0\0\0\0\0\0\0\3\0(\0\1\0\0\0\300x\1\0004\0\0\0"..., 512) = 512
_llseek(3, 1293204, [1293204], SEEK_SET) = 0
read(3, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 2800) = 2800
_llseek(3, 1289788, [1289788], SEEK_SET) = 0
read(3, "A.\0\0\0aeabi\0\1$\0\0\0\0056\0\6\6\10\1\t\1\n\2\22\4\23\1\24"..., 47) = 47
_llseek(3, 1293204, [1293204], SEEK_SET) = 0
read(3, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 2800) = 2800
_llseek(3, 1289788, [1289788], SEEK_SET) = 0
read(3, "A.\0\0\0aeabi\0\1$\0\0\0\0056\0\6\6\10\1\t\1\n\2\22\4\23\1\24"..., 47) = 47
_llseek(3, 1293204, [1293204], SEEK_SET) = 0
read(3, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 2800) = 2800
_llseek(3, 1289788, [1289788], SEEK_SET) = 0
read(3, "A.\0\0\0aeabi\0\1$\0\0\0\0056\0\6\6\10\1\t\1\n\2\22\4\23\1\24"..., 47) = 47
_llseek(3, 1293204, [1293204], SEEK_SET) = 0
read(3, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 2800) = 2800
_llseek(3, 1289788, [1289788], SEEK_SET) = 0
read(3, "A.\0\0\0aeabi\0\1$\0\0\0\0056\0\6\6\10\1\t\1\n\2\22\4\23\1\24"..., 47) = 47
_llseek(3, 1293204, [1293204], SEEK_SET) = 0
read(3, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 2800) = 2800
_llseek(3, 1289788, [1289788], SEEK_SET) = 0
read(3, "A.\0\0\0aeabi\0\1$\0\0\0\0056\0\6\6\10\1\t\1\n\2\22\4\23\1\24"..., 47) = 47
_llseek(3, 1293204, [1293204], SEEK_SET) = 0
read(3, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 2800) = 2800
_llseek(3, 1289788, [1289788], SEEK_SET) = 0
read(3, "A.\0\0\0aeabi\0\1$\0\0\0\0056\0\6\6\10\1\t\1\n\2\22\4\23\1\24"..., 47) = 47
fstat64(3, {st_mode=S_IFREG|0755, st_size=1296004, ...}) = 0
mmap2(NULL, 1364764, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0xb6e23000
mprotect(0xb6f5b000, 65536, PROT_NONE)  = 0
mmap2(0xb6f6b000, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x138000) = 0xb6f6b000
mmap2(0xb6f6e000, 8988, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0xb6f6e000
close(3)                                = 0
set_tls(0xb6fe5150)                     = 0
mprotect(0xb6f6b000, 8192, PROT_READ)   = 0
mprotect(0xb6fb4000, 4096, PROT_READ)   = 0
mprotect(0x20000, 4096, PROT_READ)      = 0
mprotect(0xb6fe6000, 4096, PROT_READ)   = 0
munmap(0xb6f71000, 193780)              = 0
fstat64(1, {st_mode=S_IFREG|0644, st_size=5522, ...}) = 0
brk(NULL)                               = 0x15bb000
brk(0x15dc000)                          = 0x15dc000
write(1, "zengjf\n", 7zengjf
)                 = 7
--- SIGSEGV {si_signo=SIGSEGV, si_code=SEGV_MAPERR, si_addr=NULL} ---
+++ killed by SIGSEGV +++
```

* 如上可知`printf`是调用了`write`；
* 最后`si_addr=NULL`表示空指针

## 三、总结

strace跟踪系统调用主要是两种方式：
* 直接运行程序跟踪：strace <Program> [Prog_Args]
* 根据PID进行跟踪：strace -p <PID>