# Wifi Beacon

Wifi的心跳包

## 参考文档

* [【WiFi】beacon时槽](https://blog.csdn.net/weixin_40117614/article/details/90200380)
* [802.11的beacon帧](https://blog.csdn.net/weixin_41572450/article/details/100699101)
* [android系统中wifi省电模式下的四个基本概念：TIM、DTIM、Beacon-Interval、Listen-Interval](https://blog.csdn.net/kv110/article/details/99842619)


## Beacon

* beacon帧是一个广播帧，其没有ACK反馈，所以无法设置重传机制；
* beacon帧目的是广播AP的基本信息，所以希望所有的节点都能够有效的接收该数据，从而采用较低的速率以保证信号较差的节点也可以接收该信息；
* Beacon-Interval：这个值变大，有助于client端省电，这个值变小，有助于提高client端连接速度。
* Listen-Interval: AP 广播Beacon 的周期为Beacon-Interval，STA 可以自由选择Beacon-Interval的整数倍作为自己的Listen-Interval，比如2；
