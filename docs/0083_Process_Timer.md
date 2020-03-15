# Timer

## 参考文档

* [linux应用层定时器](http://blog.chinaunix.net/uid-27717694-id-3658941.html)

## Source

* https://github.com/ZengjfOS/RaspberryPi/tree/timer

## 描述

给定一个时间间隔，以间隔减少计数，时间间隔为0的时候发出信号:

* ITIMER_REAL: 发出SIGALRM信号
* ITIMER_VIRTUAL: 发出SIGVTALRM信号
* ITIMER_PROF: 发出SIGPROF信号。