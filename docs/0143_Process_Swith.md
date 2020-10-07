# Process Swith

如果每个进程地址空间都是4G，MMU做虚拟地址映射，每次进程切换都要切换映射表？

## 参考文档


* [内核页表和进程页表](https://blog.csdn.net/andylauren/article/details/70305863)
* [0074_Core_Files.md](0074_Core_Files.md)
* [ARM-LINUX的进程切换](http://mrhopehub.github.io/2014/11/22/ARM-LINUX-process-switch.html)

## 简要说明

* 内核页表：在内核中其实就是一段内存，存放在主内核页全局目录init_mm.pgd(swapper_pg_dir)中，硬件并不直接使用；
* 进程页表：每个进程自己的页表，放在进程自身的页目录task_struct.pgd中；
* 在保护模式下，从硬件角度看，其运行的基本对象为"进程"(或线程)，而寻址则依赖于"进程页表"，在进程调度而进行上下文切换时，会进行页表的切换：即将新进程的pgd(页目录)加载到CR3寄存器中。从这个角度看，其实是完全没有用到"内核页表"的，那么"内核页表"有什么用呢？跟"进程页表"有什么关系呢？
  * 内核页表中的内容为所有进程共享，每个进程都有自己的"进程页表"，"进程页表"中映射的线性地址包括两部分：
    * 用户态
    * 内核态
      * 内核态地址对应的相关页表项，对于所有进程来说都是相同的(因为内核空间对所有进程来说都是共享的)，而这部分页表内容其实就来源于"内核页表"，即每个进程的"进程页表"中内核态地址相关的页表项都是"内核页表"的一个拷贝。
* "内核页表"由内核自己维护并更新，

## Coredump

* 查阅文档(man 7 signal)，SIGSEGV 默认handler的动作是打印"段错误"的出错信息，并产生Core文件；
* 进程收到SIGSEGV信号产生Core文件；
* 注意g++ 编译的时候，需要使用参数-g，否则GDB 无法找到symbol 信息，从而无法定位问题；
* 进入调试模式后执行bt 以显示程序的调用栈信息；
* [0074_Core_Files.md](0074_Core_Files.md)

## signal的含义

* SIGABRT：调用abort函数时产生此信号。进程异常终止。
* SIGBUS：指示一个实现定义的硬件故障。
* SIGEMT：指示一个实现定义的硬件故障。EMT这一名字来自PDP-11的emulator trap 指令。
* SIGFPE：此信号表示一个算术运算异常，例如除以0，浮点溢出等。
* SIGILL：此信号指示进程已执行一条非法硬件指令。4.3BSD由abort函数产生此信号。SIGABRT现在被用于此。
* SIGIOT：这指示一个实现定义的硬件故障。IOT这个名字来自于PDP-11对于输入/输出TRAP(input/outputTRAP)指令的缩写。系统V的早期版本，由abort函数产生此信号。SIGABRT现在被用于此。
* SIGQUIT：当用户在终端上按退出键（一般采用Ctrl-/）时，产生此信号，并送至前台进程组中的所有进程。此信号不仅终止前台进程组（如SIGINT所做的那样），同时产生一个core文件。
* SIGSEGV：指示进程进行了一次无效的存储访问。名字SEGV表示"段违例（segmentationviolation）"。
* SIGSYS：指示一个无效的系统调用。由于某种未知原因，进程执行了一条系统调用指令，但其指示系统调用类型的参数却是无效的。
* SIGTRAP：指示一个实现定义的硬件故障。此信号名来自于PDP-11的TRAP指令。SIGXCPUSVR4和4.3+BSD支持资源限制的概念。如果进程超过了其软CPU时间限制，则产生此信号。
* SIGXFSZ：如果进程超过了其软文件长度限制，则SVR4和4.3+BSD产生此信号。

## 内存切换

进程切换是操作系统进程调度的基础，首先要能够实现切换，接下来才谈得上"多进程"、"多线程"以及调度算法等更高级的话题。（这里在说"进程切换"的时候提到多线程，并不是把概念搞混淆了。在内核里谈切换的时候，Linux并不区分进程与线程，因为这里只有task，一个进程里如果有多个线程，每一个都是一个task。内核实际上切换的就是task。所以，来自同一个进程的不同线程的task和来自不同进程的task对于内核来说并没有区别。）

Linux进程切换的核心代码是函数context_switch()，此函数的骨干内容如下：

```C
static inline void
context_switch(struct rq *rq, struct task_struct *prev, struct task_struct *next)
{
    switch_mm(oldmm, mm, next);
    switch_to(prev, next, prev);
}
 
#define switch_to(prev,next,last) \
do { \
 last = __switch_to(prev,task_thread_info(prev), task_thread_info(next)); \
} while (0)
```

其中prev是当前进程/切出进程的`task_struct`指针，next是下一进程/切入进程的`task_struct`指针。`context_switch()`主要做两件事情，一件是切换页表，另一件是切换进程上下文。分别由一个函数来实现。

### switch_mm

`switch_mm()`的作用是切换切换进程的页表，要做的最重要的事情就是把下一进程的二级页表地址pgd（物理地址）设置到CPU的CP15控制器。进程的页表pgd可以分为两部分来看，0~3G空间部分是用户空间，采用二级映射，每个进程各不相同；3G~4G空间部分是内核空间，采用一级映射，每个进程都相同，其实每个进程的这一块页表内容都是从内核的页表拷贝来的。切换页表的主要目的是切换用户空间的页表，内核空间部分都一样，不需要切换。所以，如果next是一个内核线程的话，并不会调用`switch_mm()`。

下面是经过简化的`switch_mm()`汇编代码：

```assembly
/* r0 = pgd_phys, * r1 = context_id
 */
ENTRY(cpu_v6_switch_mm)
 mov r2, #0
 orr r0, r0, #TTB_FLAGS_UP
 mcr p15, 0, r2, c7, c5, 6 @ flush BTAC/BTB
 mcr p15, 0, r2, c7, c10, 4 @ drain write buffer
 mcr p15, 0, r0, c2, c0, 0 @ write Translation Table Base Register 0
 mcr p15, 0, r1, c13, c0, 1 @ set context ID
 mov pc, lr
ENDPROC(cpu_v6_switch_mm)
```

其中第8行是最核心的一行，它把pgd的值设置给CP15的C2寄存器，C2即是"Translation Table Base Register 0"（地址转换表基地址寄存器）。

`switch_mm()`调用完之后，用户空间的内容已经是新的进程了，但这时内核空间还属于老的进程，因为CPU还在老进程的内核栈上面运行。下面要做的就是赶紧把内核空间空间也切换到新进程中去，这就是`switch_to()`所要做的。

### switch_to

`switch_to()`的作用有两个：一是要把当前所运行的进程(切出进程)的现场(包括各个通用寄存器、SP和PC)保存好；二是切换到新进程(切入进程)，即取出此前已保存的新进程的现场，并从上次保存的地方继续运行。注意，这里所说的的现场是内核空间的现场，用户空间的现场在中断刚刚发生时已经保存过。

下面是经过简化的`switch_to()`汇编代码：

```assembly
/* r0 = previous task_struct, r1 = previous thread_info, r2 = next thread_info
 */
ENTRY(__switch_to)
/* thread_info + TI_CPU_SAVE hold saved cpu context, registers value is stored */
/* now ip hold the address of the context of previous process */
 add ip, r1, #TI_CPU_SAVE
/* now r3 hold TP value of next process */
 ldr r3, [r2, #TI_TP_VALUE]
/* store current regs to prev thread_info */
 stmia ip!, {r4 - sl, fp, sp, lr} @ Store most regs on
/* store CPU_DOMAIN of next to r6 */
 ldr r6, [r2, #TI_CPU_DOMAIN]
/* set tp value and domain to cp15 */
 mcr p15, 0, r3, c13, c0, 3 @ yes, set TLS register
 mcr p15, 0, r6, c3, c0, 0 @ Set domain register
/* now r4 hold the address of the next context */
 add r4, r2, #TI_CPU_SAVE
/* put next context to registers */
 ldmia r4, {r4 - sl, fp, sp, pc} @ Load all regs saved previously
ENDPROC(__switch_to)
```

其中第10行和第19行是比较核心的代码，它们分别是保存当前cpu context以及恢复上一次保存的cpu context。这里所说的"上一次"指的是当前进程在上一次处于内核态的时候，当时在离开内核态（切出）的时候，保存了现场。

这里所说的cpu context是由结构体cpu_context所表示的，内容如下：

```assembly
struct cpu_context_save {
 __u32 r4;
 __u32 r5;
 __u32 r6;
 __u32 r7;
 __u32 r8;
 __u32 r9;
 __u32 sl;
 __u32 fp;
 __u32 sp;
 __u32 pc;
 __u32 extra[2]; /* Xscale 'acc' register, etc */
};
```

在`switch_to()`的第10行，当前正在运行的SVC模式下的各寄存器（包括r4-r9, sp, lr等等）都被保存起来。

在`switch_to()`的第19行，r4指向的是下一进程的cpu_context结构地址，这一行执行完后，cpu context中所保存的内容就被读进各个寄存器，sp和pc都被更新，现在CPU已经不在刚刚的那个内核栈上了。

第10行和第19行的寄存器列表有一处区别：第10行的最后一个寄存器是lr，即调用`__switch_to()`的返回地址；而第19行的最后一个寄存器是pc。这就是说，在切换的时候，当前进程在切回来的时候会从`__switch_to()`的下一条指令开始执行，这正是内核所需要的。
